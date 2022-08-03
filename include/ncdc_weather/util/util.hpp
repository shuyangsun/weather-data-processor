#ifndef NCDC_WEATHER_INCLUDE_NCDC_WEATHER_UTIL_UTIL_HPP_
#define NCDC_WEATHER_INCLUDE_NCDC_WEATHER_UTIL_UTIL_HPP_

#include <algorithm>
#include <vector>
#include <chrono>

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

using Duration = decltype(std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now());

template<typename F>
[[nodiscard]] Duration Bench(F lambda) {
  const auto start{std::chrono::high_resolution_clock::now()};
  lambda();
  const auto stop{std::chrono::high_resolution_clock::now()};
  return stop - start;
}

}  // namespace nwpp::util

#endif  // NCDC_WEATHER_INCLUDE_NCDC_WEATHER_UTIL_UTIL_HPP_
