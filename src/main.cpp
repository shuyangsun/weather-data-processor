#include <iostream>
#include <chrono>

#include "ncdc_weather/fs/local_fs.hpp"
#include "ncdc_weather/util/util.hpp"

int main(int argc, char **argv) {
  const nwpp::fs::LocalPath dir{"/Users/shuyang/Documents/ncdc_weather/2001"};
  std::cout << "Path: \"" << dir.FullPath() << '"' << std::endl;
  std::cout << "Exists: " << dir.Exists() << std::endl;
  std::cout << "IsDir: " << dir.IsDir() << std::endl;
  std::cout << "IsFile: " << dir.IsFile() << std::endl;
  std::cout << "IsDot: " << dir.IsDot() << std::endl;

  std::cout << "Calculating file/dir size..." << std::endl;
  uint64_t file_size{0};
  const auto dur = nwpp::util::Bench([&](){
    file_size = dir.Size();
  }, 10);
  std::cout << "Size: " << file_size / 1024 / 1024 << "MB" << ", time elapsed: " << dur.Description() << std::endl;
  return 0;
}