#ifndef NCDC_WEATHER_INCLUDE_NCDC_WEATHER_TIME_TIME_HPP_
#define NCDC_WEATHER_INCLUDE_NCDC_WEATHER_TIME_TIME_HPP_

#include <chrono>
#include <cstdint>
#include <string>
#include <exception>
#include <cmath>
#include <array>
#include <sstream>

namespace nwpp::time {

namespace {
using ChronotDuration = decltype(
    std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now()
);

constexpr std::array<uint16_t, 5> DUR_CONVERSION_RATIO{1000, 1000, 1000, 60, 60};
constexpr std::array<char const *, 6> DUR_UNIT_STR{"ns", "μs", "ms", "s", "m", "h"};

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return out.str();
}

} // anonymous namespace

enum class DurUnit: std::uint8_t {
  NanoSec = 0,
  MicroSec,
  MilliSec,
  Second,
  Minute,
  Hour,
};

class Duration {
 public:
  Duration(ChronotDuration &&dur): nano_sec_{
    std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count()
  } {}
  ~Duration() = default;

  [[nodiscard]] std::string Description() const {
    double res{static_cast<double>(this->nano_sec_)};
    size_t i{0};
    while (i < DUR_CONVERSION_RATIO.size()) {
      const double cur{res / DUR_CONVERSION_RATIO[i]};
      if (cur < 1) {
        break;
      }
      res = cur;
      ++i;
    }
    if (i <= 0) {
      return std::to_string(this->nano_sec_) + DUR_UNIT_STR[i];
    }
    return to_string_with_precision(res, 2) + DUR_UNIT_STR[i];
  }

 private:
  long long nano_sec_;
};

};  // namespace nwpp::time

#endif  // NCDC_WEATHER_INCLUDE_NCDC_WEATHER_TIME_TIME_HPP_
