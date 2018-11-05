/*
 * FileSignature.cpp
 *
 *  Created on: 21 окт. 2018 г.
 *      Author: ivan
 */

#include "ConfigReader.h"
#include "FileReader.h"
#include "Dispatcher.h"
#include "SignatureWriter.h"
#include "BaseException.h"

#include <stdlib.h>
#include <iostream>
#include <exception>

#include <memory>

int main(int argc, char* argv[])
{
	using namespace FileSignature;
	try {
		std::cout << "Start in/out initializing, configuration reading..." << std::endl;

		auto dispatcher = std::make_unique<Dispatcher>(
				std::make_unique<ConfigReader>(argc, argv));

		std::cout << "Start processing..." << std::endl;
		dispatcher->processDataConcurrently();

		std::cout << "Concurrent processing completed!" << std::endl;
	} catch (BaseConfigException& exp) {
		std::cerr << ConfigReader::getUsage() << std::endl;
		return -1;
	} catch (BaseException& exp) {
		std::cerr << exp.what() << std::endl;
		return -1;
	} catch (std::exception& exp) {
		std::cerr << exp.what() << std::endl;
		return -1;
	} catch (...) {
		std::cerr << "Unrecognized error occurred!" << std::endl;
		return -1;
	}
	return 0;
}

