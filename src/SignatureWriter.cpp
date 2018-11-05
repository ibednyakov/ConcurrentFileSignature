/*
 * SignatureWriter.cpp
 *
 *  Created on: 3 нояб. 2018 г.
 *      Author: ivan
 */

#include "SignatureWriter.h"
#include "DataBlock.h"

#include <boost/filesystem.hpp>

namespace FileSignature
{

namespace
{

std::string verifiedFilename(const std::string& outputFilename,
		FileProcessing overwriteStrategy)
{
	std::string resultingFilename = outputFilename;

	switch(overwriteStrategy)
	{
	case FileProcessing::AskOverwriteIfExists:
		while(boost::filesystem::exists(boost::filesystem::path(resultingFilename)))
		{
			std::cout << "Specified signature file " << resultingFilename <<
					" already exists. Please provide another filename..." << std::endl;
			std::cin >> resultingFilename;
		}
		break;
	case FileProcessing::AutoOverwrite:
		break;
	case FileProcessing::AvoidOverwriting:
		if (boost::filesystem::exists(boost::filesystem::path(resultingFilename)))
			throw FileAlreadyExists(resultingFilename);
		break;
	case FileProcessing::NotDefined:
	case FileProcessing::MaxValue:
		break;
	}
	return resultingFilename;
}

} // namespace


FileAlreadyExists::FileAlreadyExists(const std::string& filename)
	: _message(filename)
{}

std::string FileAlreadyExists::what() noexcept
{
	static std::string baseMessage("File already exists: ");
	return baseMessage + _message;
}

SignatureWriter& SignatureWriter::instance(const std::string& signatureFilename,
		FileProcessing overwriteStrategy)
{
	static SignatureWriter signatureWriter(signatureFilename, overwriteStrategy);
	return signatureWriter;
}

void SignatureWriter::writeCrcForBlock(int blockCrcPosition, uint32_t crc)
{
	if (blockCrcPosition == InvalidPosition)
		throw InvalidBlock();
	std::lock_guard<std::mutex> scopedLock(_mutex);
	if (_signatureFile.tellp() != blockCrcPosition)
		_signatureFile.seekp(blockCrcPosition);
	_signatureFile.write(reinterpret_cast<const char*>(&crc), sizeof(uint32_t));
}

SignatureWriter::SignatureWriter(const std::string& signatureFilename, FileProcessing overwriteStrategy)
	: _fileName(verifiedFilename(signatureFilename, overwriteStrategy))
	, _signatureFile(_fileName, std::ios_base::out | std::ios_base::binary)
{}


} // namespace FileSignature

