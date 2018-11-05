/*
 * ConfigReader.cpp
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: ivan
 */

#include "ConfigReader.h"

#include <iostream>
#include <sstream>

namespace FileSignature
{

std::string ConfigReader::_usageMessage = "Usage: FileSignature <blockSize> \
<InputFilename> <OutputFilename> [<OverwriteStrategy>]\n     Where \
OverwriteStrategy one of (0 - AskOverwriteIfExists, 1 - AutoOverwrite, \
2 - AvoidOverwriting [default])";

std::string InvalidParametersCount::_message = "Invalid count (Min expected/provided): ";

InvalidParametersCount::InvalidParametersCount(int expected, int provided)
	: _expected(expected)
	, _provided(provided)
{}

std::string InvalidParametersCount::what() noexcept
{
	std::stringstream ss;
	ss << _message;
	ss << _expected;
	ss << "/";
	ss << _provided;
	return ss.str();
}

InvalidInputParameters::InvalidInputParameters(const std::string& message)
	: _message(message)
{}

ConfigReader::ConfigReader(int argc, char* argv[])
{
	if (argc < WellKnownParametersCount)
		throw InvalidParametersCount(argc, WellKnownParametersCount);

	if (!parseParameters(argc, argv))
		throw InvalidInputParameters("");

	std::cout << "Parsing completed!" << std::endl;
}

std::string ConfigReader::getUsage()
{
	return _usageMessage;
}

size_t ConfigReader::getBlockSize() const
{
	return _config.blockSize;
}

std::string ConfigReader::getInputFilename() const
{
	return _config.inputFileName;
}

std::string ConfigReader::getOutputFilename() const
{
	return _config.outputFileName;
}

FileProcessing ConfigReader::getOverwriteStrategy() const
{
	return _config.overwriteStrategy;
}

std::string InvalidInputParameters::what() noexcept
{
	return _message;
}

bool ConfigReader::validateInput(long blockSize, int strategy)
{
	if ((0 < blockSize && blockSize < MaxAllowedBlockSize) &&
		(static_cast<int>(FileProcessing::NotDefined) < strategy &&
				strategy < static_cast<int>(FileProcessing::MaxValue)))
			return true;
	return false;
}

std::string ConfigReader::getCurrentParameters() const
{
	return "BlockSize=" + std::to_string(getBlockSize()) + " InputFile=" + getInputFilename() + " Output=" + getOutputFilename();
}

bool ConfigReader::parseParameters(int argc, char* argv[])
{
	const long blockSize = std::stoul(argv[1]);
	_config.inputFileName = argv[2];
	_config.outputFileName = argv[3];

	const int strategy = (argc > 4) ? std::stoi(argv[4]) :
			static_cast<int>(FileProcessing::AvoidOverwriting);

	if (validateInput(blockSize, strategy))
	{
		_config.blockSize = blockSize;
		_config.overwriteStrategy = static_cast<FileProcessing>(strategy);
		return true;
	}
	return false;
}

}
