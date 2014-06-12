################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
src/PerfMon/PerfMon.cpp 

OBJS += \
src/PerfMon/PerfMon.o 

CPP_DEPS += \
src/PerfMon/PerfMon.d 


# Each subdirectory must supply rules for building sources it contributes
src/PerfMon/%.o: ../src/PerfMon/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jacob/Documents/Eclipse Workspace/C++/PacketMachine/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


