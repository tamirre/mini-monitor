#include "Application.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <fstream>
									  
Application::Application()
{
	std::cout << "Mini Energy Monitor starting..." << std::endl;

	randomGenerator.seed(std::random_device{}());

	const std::string path = "./config.env";
	if (readConfig(path) == 0) 
	{
		database.init(config.host, config.dbName, config.user, config.pass);
	} else {
		throw std::runtime_error("Cannot open config file: " + path);
	}
}

Application::~Application()
{
	std::cout << "Shutting down..." << std::endl;
}	

int Application::readConfig(const std::string path)
{
	std::ifstream file(path);
    if (!file) return 1;

    std::string key, value;
    while (file >> key >> value) {  // extract key and value directly
        if (key == "host")   config.host   = value;
        else if (key == "dbName") config.dbName = value;
        else if (key == "user")   config.user   = value;
        else if (key == "pass")   config.pass   = value;
    }

    std::cout << "host: "     << config.host
              << ", dbName: " << config.dbName
              << ", user: "   << config.user
              << ", pass: "   << config.pass << std::endl;

	return 0;
}

void Application::run()
{
	std::cout << "Running..." << std::endl;
	running = true;

	// MOCKUP MEASUREMENTS
	int measurementCount = 0;
	std::uniform_int_distribution<int> deviceDist(1, 2);
	std::uniform_real_distribution<float> currentDist(0.0, 100.0);
	std::uniform_real_distribution<float> voltageDist(215.0, 245.0);
	while(running) {
		Measurement measurement = {
			.deviceID = deviceDist(randomGenerator),
			.deviceName = "",
			.timeStamp = "",
			.current = currentDist(randomGenerator),
			.voltage = voltageDist(randomGenerator),
		};
		database.insertMeasurement(measurement);
		if(++measurementCount >= 5) running = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}	
	printLastMeasurements(10);
	// Only for testing 
	database.cleanDatabase();
}

void Application::printLastMeasurements(int count)
{
	std::vector<Measurement> measurements = database.getLastMeasurements(count);
	std::cout
		<< std::left
		<< std::setw(10) << "deviceID" << " | "
		<< std::setw(10) << "deviceName" << " | "
		<< std::setw(30) << "timeStamp" << " | "
		<< std::setw(10) << "current" << " | "
		<< std::setw(10) << "voltage" << "\n";
	for (auto & m : measurements)
	{
		std::cout
			<< std::left
			<< std::setw(10) << m.deviceID << " | "
			<< std::setw(10) << m.deviceName << " | "
			<< std::setw(30) << m.timeStamp << " | "
			<< std::setw(10) << std::fixed << std::setprecision(2) << m.current << " | "
			<< std::setw(10) << std::fixed << std::setprecision(2) << m.voltage << "\n";
	}
}

