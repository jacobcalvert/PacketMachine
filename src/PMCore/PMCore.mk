################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
src/PMCore/PacketFlow.cpp \
src/PMCore/PacketFlowMgr.cpp 

OBJS += \
src/PMCore/PacketFlow.o \
src/PMCore/PacketFlowMgr.o 

CPP_DEPS += \
src/PMCore/PacketFlow.d \
src/PMCore/PacketFlowMgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/PMCore/%.o: ../src/PMCore/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jacob/Documents/Eclipse Workspace/C++/PacketMachine/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


