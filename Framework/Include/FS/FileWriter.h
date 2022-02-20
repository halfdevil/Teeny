#pragma once

#include "FS/File.h"

class FileWriter
{
public:

	FileWriter(File& file)
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
	bool write(const T* data)
	{
		return mFile->write(data, sizeof(T));
	}

	template <typename T>
	bool write(const T* data, uint32_t count)
	{
		return mFile->write(data, sizeof(T) * count);
	}

	bool seek(SeekOrigin origin, uint32_t offset);

private:

	File& mFile;
};