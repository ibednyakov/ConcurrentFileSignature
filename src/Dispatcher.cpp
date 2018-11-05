/*
 * Dispatcher.cpp
 *
 *  Created on: 3 нояб. 2018 г.
 *      Author: ivan
 */

#include "Dispatcher.h"

#include <thread>
#include <future>
#include <vector>

namespace FileSignature
{

Dispatcher::Dispatcher(std::unique_ptr<ConfigReader>&& configuration)
	: _configuration(std::move(configuration))
	, _fileReader(FileReader::instance(_configuration->getBlockSize(),
			_configuration->getInputFilename()))
	, _signatureWriter(SignatureWriter::instance(
			_configuration->getOutputFilename(), _configuration->getOverwriteStrategy()))
{
	std::cout << _configuration->getCurrentParameters() << std::endl;
}

unsigned Dispatcher::processData()
{
	using namespace boost;
	unsigned iterationsCount = 0;
	DataBlock processingBlock;
	while (_fileReader.getNextBlock(processingBlock))
	{
		crc_32_type crcOptimalCalculator;
		crcOptimalCalculator.process_bytes(
				&processingBlock.data[0], processingBlock.data.size());
		_signatureWriter.writeCrcForBlock(processingBlock.position * sizeof(uint32_t),
				static_cast<uint32_t>(crcOptimalCalculator.checksum()));
		++iterationsCount;
	}
	return iterationsCount;
}

void Dispatcher::processDataConcurrently()
{
	const auto n = std::thread::hardware_concurrency() > 0 ?
		std::thread::hardware_concurrency() : 1; // for the case when hardware_concurrency undefined

	std::cout << "Start data processing on " << n << " concurrent threads" << std::endl;

	std::vector<std::future<unsigned>> result;
	result.resize(n);
	for (unsigned i = 0; i < n; ++i)
	{
		result[i] = std::async(std::launch::async, [this] ()
		{
			return processData();
		});
	}

	/// waiting for processing completed:
	for (unsigned i = 0; i < n; ++i)
	{
		std::cout << result[i].get() << " ";
	}
	std::cout << std::endl << "done!" << std::endl;
}

}
