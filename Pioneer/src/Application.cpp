#include <pioneer/Application.hpp>

#include <iostream>

namespace Pioneer
{

Application::Application()
{
}

Application::~Application()
{
}

void Application::exec()
{
    std::cout << "Hello, Application" << std::endl;
}

}
