#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#include <CL/cl.hpp>
#include <iostream>
#include <fstream>

int main()
{
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	
	cl::Platform platform;
	std::vector<cl::Device> devices;
	cl::Device device;

	// Use all platforms to execute the kernel
	for (cl_uint i = 0; i < platforms.size(); i++)
	{
		platform = platforms[i];
		platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

		// Use first device in first platform
		device = devices.front();

		// Read kernel from file
		std::ifstream helloWorldFile("device.cl");
		std::string src(std::istreambuf_iterator<char>(helloWorldFile), (std::istreambuf_iterator<char>()));

		cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));

		// Create context
		cl::Context context(device);

		// Create program
		cl::Program program(context, sources);

		// Build program
		cl_int err = program.build("-cl-std=CL1.2");

		// Allocate memory for kernel argurment
		char buf[16];
		cl::Buffer memBuf(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));
		cl::Kernel kernel(program, "HelloWorld", &err);
		kernel.setArg(0, memBuf);

		// Enqueue kenel
		cl::CommandQueue queue(context, device);
		queue.enqueueTask(kernel);

		// Read from memory buf
		queue.enqueueReadBuffer(memBuf, 1, 0, sizeof(buf), buf);

		std::cout << buf;

	}

	system("pause");

}