################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConfigReader.cpp \
../src/Dispatcher.cpp \
../src/FileReader.cpp \
../src/FileSignature.cpp \
../src/SignatureWriter.cpp 

OBJS += \
./src/ConfigReader.o \
./src/Dispatcher.o \
./src/FileReader.o \
./src/FileSignature.o \
./src/SignatureWriter.o 

CPP_DEPS += \
./src/ConfigReader.d \
./src/Dispatcher.d \
./src/FileReader.d \
./src/FileSignature.d \
./src/SignatureWriter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/boost-1_64/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


