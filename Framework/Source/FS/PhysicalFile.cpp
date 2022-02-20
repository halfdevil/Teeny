#include "FS/PhysicalFile.h"
#include "Core/Core.h"

void PhysicalFile::open(const std::string& fileName, FileOpenMode openMode)
{
	std::ios_base::openmode fileMode = std::ios::binary;

	switch (openMode)
	{
	case FileOpenMode::OpenRead:
		fileMode = std::ios::in | fileMode;
		break;

	case FileOpenMode::OpenWrite:
	case FileOpenMode::Create:
		fileMode = std::ios::out | fileMode;
		break;

	case FileOpenMode::Append:
		fileMode = std::ios::app | fileMode;
		break;

	default:
		break;
	}

	mFile.open(fileName, fileMode);
	FATAL(mFile.good(), "Unable to open file: %s", fileName.c_str());

	mFile.seekg(0, mFile.end);
	mSize = static_cast<uint32_t>(mFile.tellg());
	mFile.seekg(0, mFile.beg);

	mFileName = fileName;
	mOpenMode = openMode;
}

void PhysicalFile::close()
{
	if (mFile.is_open())
	{
		mFile.close();
	}
}

bool PhysicalFile::seek(SeekOrigin origin, int32_t offset)
{
	switch (origin)
	{
	case SeekOrigin::Beginning:
		mFile.seekg(offset, mFile.beg);
		break;

	case SeekOrigin::Current:
		mFile.seekg(offset, mFile.cur);
		break;

	case SeekOrigin::End:
		mFile.seekg(offset, mFile.end);
		break;

	default:
		break;
	}

	return true;
}

bool PhysicalFile::read(void* data, uint32_t size)
{
	if (!canRead())
	{
		LOGERROR("File not opened for reading: %s", mFileName.c_str());
		return false;
	}

	mFile.read(reinterpret_cast<char*>(data), size);
	if (!mFile.good())
	{
		LOGERROR("Error reading from file: %s", mFileName.c_str());
		return false;
	}

	return true;
}

bool PhysicalFile::write(const void* data, uint32_t size)
{
	if (!canWrite())
	{
		LOGERROR("File not opened for writing: %s", mFileName.c_str());
		return false;
	}

	mFile.write(reinterpret_cast<const char*>(data), size);
	if (!mFile.good())
	{
		LOGERROR("Error writing to file: %s", mFileName.c_str());
		return false;
	}

	return true;
}