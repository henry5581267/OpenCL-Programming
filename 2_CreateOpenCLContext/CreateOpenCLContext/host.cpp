/*
	host.cpp
	Create OpenCL context 
	About C++ wraper, pleaser refer https://github.khronos.org/OpenCL-CLHPP/index.html
*/

// Add you host code
#include <CL/cl.hpp>
#include <iostream>

using namespace std;

void displayPlatformInfo(cl::Platform platform)
{

	cl_int error = 0;


	// We invoke the API getInfo twice for each
	// parameter we're trying to extract from Platform and device

	// Extract device Info for a specific platform
	std::vector< cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	cl::Device device;
	cl_uint ref_count = 0;

	std::cout << endl << "Number of OpenCL devices: " << devices.size() << endl;
	for (int i = 0; i < devices.size(); i++)
	{
		device = devices[i];
		// Create Context for each device
		static cl::Context context(device);
		ref_count = context.getInfo<CL_CONTEXT_REFERENCE_COUNT>();

		std::cout << endl << "Device" << i << endl;
		std::cout <<"Reference count of device: " << ref_count << endl;
	}
	std::cout << "--------------------------" << endl;
}

int main()
{
	cl_uint num_platform = 0;
	cl_int error = 0;

	/*
		Get number of platform
	*/

	std::vector< cl::Platform> platforms;
	error = cl::Platform::get(&platforms); // get is static function

	if (error < 0)
	{
	std:perror("Unable to find any openCL platform");
		exit(EXIT_FAILURE);
	}

	// Update number of platform
	num_platform = platforms.size();
	std::cout << "Number of OpenCl platforms found: " << num_platform << endl;


	cl::Platform platform;

	for (int i = 0; i < num_platform; i++)
	{
		platform = platforms[i];
		std::cout << endl << "Platform" << i;
		displayPlatformInfo(platform);
	}

	system("pause");

}