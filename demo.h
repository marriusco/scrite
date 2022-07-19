#ifndef DEMO_H
#define DEMO_H

#include <sqrat.h>
#include <iostream>

class Demo
{
    int _some;
public:
    Demo();
    Demo(int custom);
    virtual ~Demo();

    int Method(int k, const char* s);
    int Method2(int k);
    int call_from_cpp(time_t);

private:
    Sqrat::Object   _o;
};

#endif // DEMO_H
