#pragma once

#include "FS/File.h"

class FileReader
{
public:

  FileReader(File& file)
    : mFile(file)
  { 
  }

  uint32_t getSize() const 
  {
    return mFile.getSize();
  }

  uint32_t getPosition() const
  {
    return mFile.getPosition();
  }

  template <typename T>
  bool read(T* data)
  {
    return mFile.read(data, sizeof(T));
  }

  template <typename T>
  bool read(T* data, uint32_t count)
  {
    return mFile.read(data, sizeof(T) * count);
  }

  bool seek(SeekOrigin origin, uint32_t offset);

private:

  File& mFile;
};