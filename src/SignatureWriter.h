/*
 * SignatureWriter.h
 *
 *  Created on: 3 нояб. 2018 г.
 *      Author: ivan
 */

#include "ConfigReader.h"
#include "BaseException.h"

#include <stdlib.h>
#include <string>

#include <boost/crc.hpp>

#include <mutex>
#include <iostream>
#include <fstream>

#ifndef SRC_SIGNATUREWRITER_H_
#define SRC_SIGNATUREWRITER_H_


namespace FileSignature
{

class FileAlreadyExists : public BaseException
{
public:
	~FileAlreadyExists() override {}
	FileAlreadyExists() = delete;
	explicit FileAlreadyExists(const std::string& filename);

	std::string what() noexcept override;

private:
	std::string _message;
};

///
/// \brief SignatureWriter class performs CRC writing to specified file
///
class SignatureWriter
{
public:
	using SignaturePartType = boost::crc_32_type;

	static SignatureWriter& instance(const std::string& signatureFilename,
			FileProcessing overwriteStrategy);

	SignatureWriter() = delete;
	~SignatureWriter() = default;

	/// \brief method for writing signature part to a specified file...
	/// \note: writing made under mutex synch-primitive
	void writeCrcForBlock(int blockCrcPosition, uint32_t crc);

private:
	SignatureWriter(const std::string& signatureFilename,
			FileProcessing overwriteStrategy);

	std::string   _fileName;
	std::ofstream _signatureFile;
	std::mutex    _mutex;

};


} // namespace FileSignature


#endif /* SRC_SIGNATUREWRITER_H_ */
