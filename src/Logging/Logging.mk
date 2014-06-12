################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
src/Logging/Logging.cpp 

OBJS += \
src/Logging/Logging.o 

CPP_DEPS += \
src/Logging/Logging.d 


# Each subdirectory must supply rules for building sources it contributes
src/Logging/%.o: src/Logging/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jacob/Documents/Eclipse Workspace/C++/PacketMachine/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


