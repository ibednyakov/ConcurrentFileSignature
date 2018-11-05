/*
 * Dispatcher.h
 *
 *  Created on: 3 нояб. 2018 г.
 *      Author: ivan
 */

#ifndef SRC_DISPATCHER_H_
#define SRC_DISPATCHER_H_

#include "ConfigReader.h"
#include "FileReader.h"
#include "SignatureWriter.h"

#include <boost/crc.hpp>

#include <memory>

namespace FileSignature
{

/// \brief Dispatcher class manages file-signature processing by separating it
/// between available executors;
class Dispatcher
{
public:
	Dispatcher() = delete;
	explicit Dispatcher(std::unique_ptr<ConfigReader>&& configuration);
	~Dispatcher() = default;

	/// \brief main Dispatcher API function: starts concurrent execution
	void processDataConcurrently();

private:
	std::unique_ptr<ConfigReader>        _configuration;
	FileReader&                          _fileReader;
	SignatureWriter&                     _signatureWriter;

	unsigned processData();
};

}

#endif /* SRC_DISPATCHER_H_ */
