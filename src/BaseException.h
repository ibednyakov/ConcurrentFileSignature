/*
 * BaseException.h
 *
 *  Created on: 5 нояб. 2018 г.
 *      Author: ivan
 */

#ifndef SRC_BASEEXCEPTION_H_
#define SRC_BASEEXCEPTION_H_

#include <string>

namespace FileSignature
{

class BaseException
{
public:
	virtual ~BaseException() {}
	virtual std::string what() noexcept = 0;
};

class BaseConfigException : public BaseException
{
};

}

#endif /* SRC_BASEEXCEPTION_H_ */
