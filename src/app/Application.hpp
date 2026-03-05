#ifndef APPLICATION_HPP
#define APPLICATION_HPP
									  
#include "../database/Database.hpp"

#include <random>

struct Configuration {
	std::string host;
	std::string dbName;
	std::string user;
	std::string pass;
};

class Application
{
	Database database;
	Configuration config;
	bool running;
	std::mt19937 randomGenerator;
	public:
		Application();
		~Application() noexcept;

		// Disable copy constructor and assignment operator
		// by explicitly deleting them
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
		// Disable move constructor and assignment operator
		// by explicitly deleting them
		Application(Application&&) = delete;
		Application& operator=(Application&&) = delete;

		void run();
		int readConfig(const std::string& path);
		void printLastMeasurements(const int& count);
};

#endif // APPLICATION_HPP
