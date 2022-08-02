#ifndef NCDC_WEATHER_INCLUDE_NCDC_WEATHER_FS_I_FS_HPP_
#define NCDC_WEATHER_INCLUDE_NCDC_WEATHER_FS_I_FS_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace nwpp::fs {

class IFile {
 public:
  virtual ~IFile() = default;
  [[nodiscard]] virtual std::vector<uint8_t> Read() const = 0;
  virtual void Write(std::vector<uint8_t>&& content) const = 0;
};

class IPath {
 public:
  virtual ~IPath() = default;

  [[nodiscard]] virtual bool Exists() const noexcept = 0;
  [[nodiscard]] virtual bool IsDir() const noexcept = 0;
  [[nodiscard]] virtual bool IsFile() const noexcept = 0;
  [[nodiscard]] virtual bool IsDot() const noexcept = 0;

  [[nodiscard]] virtual uint64_t Size() const = 0;

  [[nodiscard]] virtual std::string FullPath() const = 0;
  [[nodiscard]] virtual std::string FileName() const = 0;
  [[nodiscard]] virtual std::vector<std::unique_ptr<IPath>> SubDirs() const = 0;
  [[nodiscard]] virtual std::vector<std::unique_ptr<IPath>> Files() const = 0;

  [[nodiscard]] virtual std::optional<std::unique_ptr<IPath>> Parent() const = 0;
  [[nodiscard]] virtual std::string Stem() const = 0;
  [[nodiscard]] virtual std::string Extension() const = 0;

  [[nodiscard]] virtual bool CreateAsFile(bool create_parents, bool override_existing) const = 0;
  [[nodiscard]] virtual bool CreateAsDirectory(bool create_parents) const = 0;
};

}  // namespace nwpp::fs

#endif  // NCDC_WEATHER_INCLUDE_NCDC_WEATHER_FS_I_FS_HPP_
