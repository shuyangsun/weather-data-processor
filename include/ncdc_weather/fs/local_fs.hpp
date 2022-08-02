#ifndef NCDC_WEATHER_INCLUDE_NCDC_WEATHER_FS_LOCAL_FS_HPP_
#define NCDC_WEATHER_INCLUDE_NCDC_WEATHER_FS_LOCAL_FS_HPP_

#include <algorithm>
#include <fstream>
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <sys/stat.h>

#include "ncdc_weather/fs/i_fs.hpp"
#include "ncdc_weather/util/util.hpp"

namespace nwpp::fs {

class LocalPath final: public IPath {
 public:
  explicit LocalPath(std::string&& path): path_{std::filesystem::absolute(path)} {}

  ~LocalPath() final = default;

  [[nodiscard]] inline bool Exists() const noexcept final {
    return std::filesystem::exists(this->path_);
  }

  [[nodiscard]] inline bool IsDir() const noexcept final {
    return std::filesystem::is_directory(this->path_);
  }

  [[nodiscard]] inline bool IsFile() const noexcept final {
    return std::filesystem::is_regular_file(this->path_);
  }

  [[nodiscard]] inline bool IsDot() const noexcept final {
    return !this->FileName().empty() && this->FileName().at(0) == '.';
  }

  [[nodiscard]] uint64_t Size() const final {
    if (!this->Exists()) {
      return 0;
    }
    if (this->IsDir()) {
      uint64_t total{0};
      for (const auto& dir: this->SubDirs()) {
        total += dir->Size();
      }
      for (const auto& file: this->Files()) {
        total += file->Size();
      }
      return total;
    }
    std::ifstream in(this->path_.c_str(), std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
  }


  [[nodiscard]] std::string FullPath() const final {
    return this->path_;
  }

  [[nodiscard]] std::string FileName() const final {
    return this->path_.filename();
  }

  [[nodiscard]] std::vector<std::unique_ptr<IPath>> SubDirs() const final {
    std::vector<std::unique_ptr<IPath>> result{};
    for (const auto& file: std::filesystem::directory_iterator(this->path_)) {
      if (file.is_directory()) {
        LocalPath cur{std::string{file.path().c_str()}};
        result.emplace_back(std::make_unique<LocalPath>(cur));
      }
    }
    return result;
  }

  [[nodiscard]] std::vector<std::unique_ptr<IPath>> Files() const final {
    std::vector<std::unique_ptr<IPath>> result{};
    for (const auto& file: std::filesystem::directory_iterator(this->path_)) {
      if (file.is_regular_file()) {
        LocalPath cur{std::string{file.path().c_str()}};
        result.emplace_back(std::make_unique<LocalPath>(cur));
      }
    }
    return result;
  }

  [[nodiscard]] std::optional<std::unique_ptr<IPath>> Parent() const final {
    return std::make_unique<LocalPath>(this->path_.parent_path());
  }

  [[nodiscard]] std::string Stem() const final {
    return this->path_.stem();
  }

  [[nodiscard]] std::string Extension() const final {
    return this->path_.extension();
  }

  [[nodiscard]] bool CreateAsFile(const bool create_parents, const bool override_existing) const final {
    if (this->Exists()) {
      if (override_existing) {
        std::filesystem::remove(this->path_);
      } else {
        return false;
      }
    }
    if (!this->Parent().has_value()) {
      return false;
    }
    if (this->Parent() && create_parents) {
      const auto _{this->Parent().value()->CreateAsDirectory(true)};
    }
    std::ofstream ofs(this->path_);
    ofs.close();
    return true;
  }

  [[nodiscard]] bool CreateAsDirectory(const bool create_parents) const final {
    if (this->Exists()) {
      return false;
    }
    return std::filesystem::create_directories(this->path_);
  }

 private:
  std::filesystem::path path_;
};

class LocalFile: public IFile {
 public:
  explicit LocalFile(const LocalPath& path): path_{path.FullPath()}, fsize_{path.Size()} {
    if (!(path.Exists() && path.IsFile())) {
      throw std::invalid_argument("File does not exist.");
    }
  }

  [[nodiscard]] std::vector<uint8_t> Read() const final {
    constexpr uint64_t DEFAULT_BUFFER_SIZE{64 * 1024};
    std::vector<uint8_t> buffer(DEFAULT_BUFFER_SIZE);
    const uint64_t read_len{std::min(DEFAULT_BUFFER_SIZE, this->fsize_)};
  }

  void Write(std::vector<uint8_t>&& content) const final {}

 private:
  LocalPath path_;
  uint64_t fsize_;
};


}  // namespace nwpp::fs

#endif  // NCDC_WEATHER_INCLUDE_NCDC_WEATHER_FS_LOCAL_FS_HPP_
