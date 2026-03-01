#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <chrono>
#include <thread>
using namespace std::chrono_literals; // Enables 100ms, 1s, etc.
									  
class Application
{
	public:
		Application();
		~Application();

		void run();
};

#endif // APPLICATION_HPP
