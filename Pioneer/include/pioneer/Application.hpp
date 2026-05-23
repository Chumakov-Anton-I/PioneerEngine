#ifndef PIONEER_APPLICATION_HPP
#define PIONEER_APPLICATION_HPP

#include <pioneer/Support.hpp>

namespace Pioneer
{

class PIONEER_API Application
{
public:
    Application();
    virtual ~Application();

    virtual void exec();
};

}

#endif // !PIONEER_APPLICATION_HPP
