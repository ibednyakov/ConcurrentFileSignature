/*
 * FileReader.h
 *
 *  Created on: 2 нояб. 2018 г.
 *      Author: ivan
 */

#ifndef SRC_FILEREADER_H_
#define SRC_FILEREADER_H_

#include "DataBlock.h"
#include "BaseException.h"

#include <stdlib.h>
#include <string>
#include <vector>
#include <mutex>

#include <fstream>
#include <iostream>

namespace FileSignature
{

/// \brief InvalidFilename exception class for invalid input filename case
class InvalidFilename : public BaseException
{
public:
	InvalidFilename() = delete;
	explicit InvalidFilename(const std::string& filename);
	~InvalidFilename() override {}

	std::string what() noexcept override;

private:
	static std::string _message;
	std::string        _filename;
};

/// \brief FileReader class provides input file reading functionality
class FileReader
{
public:
	FileReader() = delete;
	~FileReader() = default;
	static FileReader& instance(size_t blockSize, const std::string& fileName);

	/// \brief reads data-block under mutex
	bool getNextBlock(DataBlock& dataBlock);

private:
	FileReader(size_t blockSize, const std::string& fileName);

	size_t                _blockSize = 0;
	std::string           _fileName;
	unsigned              _currentBlockIndex = 0;
	size_t                _estimatedBlocksCount = 0;
	std::fstream          _inputFileStream;

	std::mutex            _mutex;
};

}

#endif /* SRC_FILEREADER_H_ */
