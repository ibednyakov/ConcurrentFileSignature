/*
 * DataBlock.h
 *
 *  Created on: 2 нояб. 2018 г.
 *      Author: ivan
 */

#ifndef SRC_DATABLOCK_H_
#define SRC_DATABLOCK_H_

#include "BaseException.h"

#include <vector>
#include <stdint.h>
#include <string>

namespace FileSignature
{

class InvalidBlock : public BaseException
{
public:
	~InvalidBlock() override {}

	std::string what() noexcept override
	{
		return "Invalid position detected!";
	}
};

enum
{
	InvalidPosition = -1,
};

struct DataBlock
{
	std::vector<char>    data;
	int                  position = InvalidPosition; ///< describes position of the block in a file
};

}

#endif /* SRC_DATABLOCK_H_ */
