#include "FS/FileReader.h"

bool FileReader::seek(SeekOrigin origin, uint32_t offset)
{
	return mFile.seek(origin, offset);
}