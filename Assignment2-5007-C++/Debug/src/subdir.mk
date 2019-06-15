################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Message.cpp \
../src/MessagePriorityQueue.cpp \
../src/MessageQueue.cpp 

OBJS += \
./src/Message.o \
./src/MessagePriorityQueue.o \
./src/MessageQueue.o 

CPP_DEPS += \
./src/Message.d \
./src/MessagePriorityQueue.d \
./src/MessageQueue.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


