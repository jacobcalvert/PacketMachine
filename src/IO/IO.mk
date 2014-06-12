################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
src/IO/PrintStream.cpp 

OBJS += \
src/IO/PrintStream.o 

CPP_DEPS += \
src/IO/PrintStream.d 


# Each subdirectory must supply rules for building sources it contributes
src/IO/%.o: src/IO/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jacob/Documents/Eclipse Workspace/C++/PacketMachine/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


