/*
 * ConfigReader.h
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: ivan
 */

#ifndef SRC_CONFIGREADER_H_
#define SRC_CONFIGREADER_H_

#include "string"
#include "BaseException.h"

namespace FileSignature
{

///
/// \brief Configuration processing exception
class InvalidInputParameters : public BaseConfigException
{
public:
	InvalidInputParameters() = delete;
	explicit InvalidInputParameters(const std::string& message);

	~InvalidInputParameters() override {}

	std::string what() noexcept override;

private:
	std::string _message;
};

///
/// \brief InvalidParametersCount exception class for invalid params count case
class InvalidParametersCount : public BaseConfigException
{
public:
	InvalidParametersCount() = delete;
	InvalidParametersCount(int expected, int provided);

	~InvalidParametersCount() override {}

	std::string what() noexcept override;

private:
	int                _expected;
	int                _provided;

	static std::string _message;
};

enum class FileProcessing : int
{
	NotDefined,

	AskOverwriteIfExists, ///< Strategy: to ask a new name if file already exists
	AutoOverwrite,        ///< Strategy: overwrite always
	AvoidOverwriting,     ///< Strategy: avoid any overwriting

	MaxValue,
};

///
/// \brief ConfigReader class provides functionality for input configuration parsing
class ConfigReader
{
	enum
	{
		WellKnownParametersCount = 4,
		MaxAllowedBlockSize = 1*1024*1024*1024, ///< just empyric limitation(1Gb)
	};

public:
	ConfigReader() = delete;
	ConfigReader(int argc, char* argv[]);

	size_t getBlockSize() const;
	std::string getInputFilename() const;
	std::string getOutputFilename() const;
	FileProcessing getOverwriteStrategy() const;

	static std::string getUsage();

	std::string getCurrentParameters() const;

private:

	struct Configuration
	{
		size_t         blockSize = 0;
		FileProcessing overwriteStrategy = FileProcessing::AvoidOverwriting;
		std::string    inputFileName;
		std::string    outputFileName;
	} _config;

	static std::string _usageMessage;

	bool validateInput(long blockSize, int strategy);
	bool parseParameters(int argc, char* argv[]);
};

}

#endif /* SRC_CONFIGREADER_H_ */
