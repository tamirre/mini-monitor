#ifndef APPLICATION_HPP
#define APPLICATION_HPP
									  
#include "../database/Database.hpp"

class Application
{
	Database database;
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
		void printLastMeasurements(int count);
};

#endif // APPLICATION_HPP
