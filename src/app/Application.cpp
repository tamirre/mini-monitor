#include "Application.hpp"

#include <iostream>
#include <chrono>
#include <thread>
									  
Application::Application()
{
	std::cout << "Mini Energy Monitor starting..." << std::endl;

	std::string host = "localhost";
	std::string dbName = "mini_monitor";
	std::string user = "mini_user";
	std::string pass = "mini_pass";
	database.init(host, dbName, user, pass);
}

Application::~Application()
{
	std::cout << "Shutting down..." << std::endl;
	database.cleanDatabase(1);
}	

void Application::run()
{
	std::cout << "Running..." << std::endl;

	for (int i = 0; i < 3; i++)
	{
		Measurement measurement = {
			.deviceID = 1,
			.deviceName = "",
			.timeStamp = "",
			.current = 5.0,
			.voltage = 230.0,
		};
		std::this_thread::sleep_for(std::chrono::seconds(1));
		database.insertMeasurement(measurement);
	}
	printLastMeasurements(10);
}

void Application::printLastMeasurements(int count)
{
	std::vector<Measurement> measurements = database.getLastMeasurements(count);
	for (auto & m : measurements)
	{
		std::cout
			<< m.deviceID << " | "
			<< m.deviceName << " | "
			<< m.timeStamp << " | "
			<< m.current << " | "
			<< m.voltage << "\n";
	}
}

