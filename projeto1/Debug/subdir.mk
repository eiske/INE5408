################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cashier.cpp \
../Client.cpp \
../Main.cpp \
../Supermarket.cpp \
../circularlist.cpp 

OBJS += \
./Cashier.o \
./Client.o \
./Main.o \
./Supermarket.o \
./circularlist.o 

CPP_DEPS += \
./Cashier.d \
./Client.d \
./Main.d \
./Supermarket.d \
./circularlist.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


