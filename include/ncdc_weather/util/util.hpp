#ifndef NCDC_WEATHER_INCLUDE_NCDC_WEATHER_UTIL_UTIL_HPP_
#define NCDC_WEATHER_INCLUDE_NCDC_WEATHER_UTIL_UTIL_HPP_

#include <algorithm>
#include <vector>
#include <chrono>
#include <string>

#include "ncdc_weather/time/time.hpp"

namespace nwpp::util {

template<typename T, typename F>
void VecFilterInPlace(std::vector<T>& vec, F filter) {
  auto pt0{vec.begin()};
  auto pt1{vec.begin()};
  for (;pt1 < vec.end(); pt1++) {
    const bool should_include{filter(*pt1)};
    if (should_include) {
      pt0++;
      if (pt1 > pt0) {
        std::swap(pt0, pt1);
      }
    }
  }
  vec.resize(vec.size() - (pt1 - pt0));
}

template<typename F>
[[nodiscard]] time::Duration Bench(F lambda, const size_t repeat = 1) {
  uint64_t res{0};
  for (size_t i{0}; i < repeat; ++i) {
    const auto start{std::chrono::high_resolution_clock::now()};
    lambda();
    const auto stop{std::chrono::high_resolution_clock::now()};
    res += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
  }
  res /= repeat;
  return {std::chrono::nanoseconds(res)};
}

}  // namespace nwpp::util

#endif  // NCDC_WEATHER_INCLUDE_NCDC_WEATHER_UTIL_UTIL_HPP_
