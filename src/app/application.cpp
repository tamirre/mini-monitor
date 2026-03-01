#include "application.hpp"

Application::Application()
{
	std::cout << "Mini Energy Monitor starting..." << std::endl;
}

Application::~Application()
{
	std::cout << "Shutting down..." << std::endl;
}	

void Application::run()
{
	std::cout << "Running..." << std::endl;
	std::this_thread::sleep_for(1s);
}

