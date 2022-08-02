#include <iostream>
#include <chrono>

#include "ncdc_weather/fs/local_fs.hpp"

int main(int argc, char **argv) {
  const nwpp::fs::LocalPath dir{"/Users/shuyang/Documents/ncdc_weather/2001"};
  std::cout << "Path: \"" << dir.FullPath() << '"' << std::endl;
  std::cout << "Exists: " << dir.Exists() << std::endl;
  std::cout << "IsDir: " << dir.IsDir() << std::endl;
  std::cout << "IsFile: " << dir.IsFile() << std::endl;
  std::cout << "IsDot: " << dir.IsDot() << std::endl;

  std::cout << "Calculating file/dir size..." << std::endl;
  const auto start{std::chrono::high_resolution_clock::now()};
  const auto file_size{dir.Size()};
  const auto stop{std::chrono::high_resolution_clock::now()};
  const auto dur = stop - start;
  const auto dur_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
  std::cout << "Size: " << file_size / 1024 / 1024 << "MB" << ", time elapsed: " << dur_ms << "ms." << std::endl;
  return 0;
}