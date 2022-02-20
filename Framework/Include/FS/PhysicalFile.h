#pragma once

#include "FS/File.h"
#include <fstream>

class PhysicalFile : public File
{
public:

	PhysicalFile() = default;
	virtual ~PhysicalFile()
	{
		close();
	}

	virtual bool isEOF() const override
	{
		return mFile.eof();
	}

	virtual void open(const std::string& fileName, FileOpenMode openMode);
	virtual void close();

	virtual bool seek(SeekOrigin origin, int32_t offset) override;
	virtual bool read(void* data, uint32_t size) override;
	virtual bool write(const void* data, uint32_t size) override;

private:

	std::string mFileName;
	std::fstream mFile;
};