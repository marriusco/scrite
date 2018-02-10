
#include <stdio.h>
#include "demo.h"

Demo::Demo():_some(0)
{
}

Demo::Demo(int custom):_some(custom)
{

}


int Demo::Method(int k, const char* s)
{
    printf(" Demo::Method called %d %s \n",k, s);
    return 0;
}

