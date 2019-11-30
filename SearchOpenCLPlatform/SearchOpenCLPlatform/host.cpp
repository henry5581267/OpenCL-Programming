/*
	host.cpp
	Get Info about OpenCL platform
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
	string platform_profile = platform.getInfo<CL_PLATFORM_PROFILE >();
	string platform_name = platform.getInfo<CL_PLATFORM_NAME>();
	string platform_vendor = platform.getInfo<CL_PLATFORM_VENDOR>();
	string platform_version = platform.getInfo<CL_PLATFORM_VERSION>();

	std::cout << endl << "CL_PLATFORM_PROFILE: " << platform_profile << endl;
	std::cout << "CL_PLATFORM_NAME: " << platform_name << endl;
	std::cout << "CL_PLATFORM_VENDOR: " << platform_vendor << endl;
	std::cout << "CL_PLATFORM_VERSION: " << platform_version << endl;

	// Extract device Info for a specific platform
	std::vector< cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	cl::Device device;
	string device_name;
	cl_uint device_max_compute_unit;
	cl_uint device_max_work_item_dimension;
	// Max work item in each dimension 
	// Query work item size device_max_work_item[i] i=0:2
	std::vector<::size_t> device_max_work_item;
	size_t device_max_work_group;


	for (int i = 0; i < devices.size(); i++)
	{
		device = devices[i];
		device_name = device.getInfo<CL_DEVICE_NAME>();
		device_max_compute_unit = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
		device_max_work_item_dimension = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>();
		device_max_work_item = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
		device_max_work_group = device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();

		std::cout << endl << "Device" << i << ": ";
		std::cout << "Device name: " << device_name << endl;
		std::cout << "Maximum of parallel compute units: " << device_max_compute_unit << endl;
		std::cout << "Maximum dimensions for global/local work-item IDs: " << device_max_work_item_dimension << endl;
		std::cout << "Maximum number of work-items in each dimension: " << device_max_work_item[0] << endl;
		std::cout << "Maximum number work-items in a work group: " << device_max_work_group << endl;
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