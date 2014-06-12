##############################
#
# My makefile
#
###############################

-include sources.mk
-include src/Assert/Assert.mk
-include src/CLI/CLI.mk
-include src/IO/IO.mk
-include src/Logging/Logging.mk
-include src/PMCore/PMCore.mk
-include src/RandGen/RandGen.mk
-include src/STL/STL.mk
-include src/Thread/Thread.mk
-include src/PerfMon/PerfMon.mk

# Libs needed for compile
LIBS := -lpthread -lboost_system
#include dirs
SUBDIRS := \
src \
src/Thread \
src/STL \
src/RandGen \
src/PerfMon \
src/PMCore \
src/Logging \
src/IO \
src/CLI \
src/Assert\

CPP_SRCS += \
src/init.cpp

OBJS += \
src/init.o

CPP_DEPS += \
src/init.d

all: PacketMachine

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jacob/Documents/Eclipse Workspace/C++/PacketMachine-0.8/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

PacketMachine: $(OBJS)
	@echo	'Currently building: $@'
	@echo	'Calling GCC'
	g++  -o "PacketMachine" $(OBJS) $(LIBS)
	@echo	"Done"