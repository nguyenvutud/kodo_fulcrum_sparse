################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/encode_decode_fulcrum_sparse.cpp 

OBJS += \
./src/encode_decode_fulcrum_sparse.o 

CPP_DEPS += \
./src/encode_decode_fulcrum_sparse.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/storage-20a331/2.1.0/src -I/home/nguyenvu/dev/kodo-fulcrum/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/boost-abe3de/2.1.0 -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/cpuid-4d8071/4.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/kodo-core-de4387/4.0.1/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/kodo-rlnc-7d74ae/4.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/meta-768c5a/2.1.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/sak-1bdcea/15.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/recycle-b2469b/2.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/hex-4d9037/3.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/endian-30a816/3.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/platform-bccd32/2.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/tables-c83c83/6.0.0/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/gtest-5c3bfe/3.0.0 -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/fifi-8960fd/24.0.0/src -I/home/nguyenvu/cpp_workspace/kodo_fulcrum_sparse/src -I/home/nguyenvu/dev/kodo-fulcrum/bundle_dependencies/allocate-7c9f51/1.0.0/src -O0 -g3 -Wall -std=c++11 -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


