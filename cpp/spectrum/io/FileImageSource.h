// Copyright (c) Facebook, Inc. and its affiliates.
//
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <spectrum/io/IEncodedImageSource.h>

#include <cstddef>
#include <fstream>
#include <string>

namespace facebook {
namespace spectrum {
namespace io {

/**
 * An encoded image source that reads from a file at the specific path.
 */
class FileImageSource : public IEncodedImageSource {
 private:
  std::ifstream ifs;
  std::size_t totalBytesRead = 0;

 public:
  /**
   * Creates a file image source for the given path.
   *
   * @throws SpectrumException if the input stream cannot be initialized
   * (e.g. insufficient permissions, ...).
   */
  explicit FileImageSource(const std::string& path);
  FileImageSource(const FileImageSource&) = delete;
#if !defined(__ANDROID__) || defined(_LIBCPP_VERSION)
  // gnustl doesn't mark std::ifstream as movable, and since we have a
  // std::ifstream member variable we can't then use the default move
  // constructor. We can remove the conditional after we've switched to libc++.
  FileImageSource(FileImageSource&&) = default;
#endif

  ~FileImageSource() override = default;

  std::size_t read(char* const destination, const std::size_t length) override;
  std::size_t getTotalBytesRead() const override;
  std::size_t available() override;
};

} // namespace io
} // namespace spectrum
} // namespace facebook
