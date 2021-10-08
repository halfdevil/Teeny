#pragma once

#include "Core/StdHeaders.h"

enum class FileOpenMode
{
  OpenRead,
  OpenWrite,
  Create,
  Append
};

enum class SeekOrigin
{
  Beginning,
  Current,
  End
};

class File
{
public:

  File() = default;
  virtual ~File() = default;

  FileOpenMode getOpenMode() const
  {
    return mOpenMode;
  }
  
  bool canRead() const
  {
    return mOpenMode == FileOpenMode::OpenRead;
  }

  bool canWrite() const
  {
    return mOpenMode != FileOpenMode::OpenWrite;
  }

  uint32_t getSize() const
  {
    return mSize;
  }

  uint32_t getPosition() const
  {
    return mPosition;
  }

  virtual bool isEOF() const = 0;
  virtual bool seek(SeekOrigin origin, int32_t offset) = 0;
  virtual bool read(void* data, uint32_t size) = 0;
  virtual bool write(const void* data, uint32_t size) = 0;

protected:

  FileOpenMode mOpenMode{ FileOpenMode::OpenRead };
  uint32_t mSize{ 0 };
  uint32_t mPosition{ 0 };
};