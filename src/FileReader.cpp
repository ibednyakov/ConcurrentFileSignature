/*
 * FileReader.cpp
 *
 *  Created on: 2 нояб. 2018 г.
 *      Author: ivan
 */

#include "FileReader.h"

#include <boost/filesystem.hpp>

namespace FileSignature
{

namespace
{

size_t fetchBlocksCount(const std::string& filename, size_t blockSize)
{
	using namespace boost;

    const filesystem::path filePath(filename);

	if (!filesystem::exists(filePath))
		throw InvalidFilename(filename);

	unsigned long result = filesystem::file_size(filePath);
	unsigned long reminder = result % blockSize;
	return result / blockSize + (reminder > 0 ? 1 : 0);
}

}

std::string InvalidFilename::_message = "Invalid filename specified: ";

InvalidFilename::InvalidFilename(const std::string& filename)
	: _filename(filename)
{}

std::string InvalidFilename::what() noexcept
{
	std::string message = _message + _filename;
	return message;
}

FileReader& FileReader::instance(size_t blockSize, const std::string& fileName)
{
	static FileReader fileReader(blockSize, fileName);
	return fileReader;
}

bool FileReader::getNextBlock(DataBlock& dataBlock)
{
	std::lock_guard<std::mutex> scopedLock(_mutex);
	if (_currentBlockIndex >= _estimatedBlocksCount)
		return false;
	std::vector<char> block(_blockSize, 0);
	_inputFileStream.read(&block[0], _blockSize);
	dataBlock.position = _currentBlockIndex;
	dataBlock.data.swap(block);
	++_currentBlockIndex;
	return true;
}

FileReader::FileReader(size_t blockSize, const std::string& fileName)
	: _blockSize(blockSize)
	, _fileName(fileName)
	, _currentBlockIndex(0)
	, _estimatedBlocksCount(fetchBlocksCount(fileName, blockSize))
	, _inputFileStream(_fileName, std::ios_base::in | std::ios_base::binary)
{}

}

