#include "FS/FileWriter.h"

bool FileWriter::seek(SeekOrigin origin, uint32_t offset)
{
  return mFile.seek(origin, offset);
}