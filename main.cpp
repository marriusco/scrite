

#include <unistd.h>
#include <string>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqwrap.h"
#include "sqratConst.h"
#include "main.h"

#ifdef __linux
#   include <set>
#   include <sys/ioctl.h>
#   include <termios.h>
#   include <libgen.h>
#else
#   include <stdlib.h>
#   include <stdio.h>
#endif
#include "demo.h"

RunCtx*             PCTX = 0;
int                 _Debug = 0;
sq_api*                 SQ_PTRS;
Sqrat::Function*    RunFoo;
time_t              Interval = 1000;
Demo*               PDemo;   // this is built in script and we hold apointer here to call methid by name

inline time_t gtc(void)
{
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now))
        return 0;
    return time_t(now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0);
}

static int run(Sqrat::Function& f, time_t interval)
{
    RunFoo = new Sqrat::Function(f);
    Interval = interval;
    return 0;
}


int main(int argc, char *argv[])
{
    SqEnv               sq;
    std::string         script;
    std::cout << "Scrite ver: 0.0.1-"<<__DATE__<<"\r\n";

    if(argc < 2)
    {
        std::cout << "pass a script name \n";
        return 1;
    }
    else
    {
        script = argv[1];
    }

    sq.acquire();


    sqrat_newapi(&SQ_PTRS);
    /**
      add definitons for the script
      */
    Sqrat::ConstTable(sq.theVM())
                        .Const("True", 1)
                        .Const("False", 0);

    /**
      add global functions for the script
      */
    Sqrat::RootTable(sq.theVM()).Functor("GlobalCall", &RunCtx::GlobalCall);

    /**
      add classes and thir methods for the script
    */
    Sqrat::Class<Demo> cls(sq.theVM(), _SC("Demo"));
    cls.Ctor<int>();
    cls.Ctor();
    cls.Functor(_SC("Method"), &Demo::Method);
    cls.Functor(_SC("Method2"), &Demo::Method2);
    Sqrat::RootTable().Bind(_SC("Demo"), cls);

    // global run
    Sqrat::RootTable(sq.theVM()).Functor("run", &run);


    try{
        MyScript scr = sq.compile_script(script.c_str());
        scr.run_script();

        // main call from script
        Sqrat::Function f = Sqrat::RootTable().GetFunction(_SC("main"));
        if(!f.IsNull())
        {
            Sqrat::SharedPtr<int>   srv;
            int                     rv;

            if(argc==2)
                srv = f.Fcall<int>(0);
            else
                srv = f.Fcall<int>(argv[2]);
            if(srv.Get()==0)
            {
                throw (Sqrat::Exception("function setup must return True or False "));
            }
            else
                rv = (*srv.Get());

            if(rv == 1)
            {
                time_t now,then=0;
                while(rv)
                {
                    now = ::gtc();
                    if(now - then > Interval)
                    {
                        srv = RunFoo->Fcall<int>(now);
                        rv = (*srv.Get());
                        then = now;

                        PDemo->call_from_cpp(now);
                    }
                }
            }
        }
        else
        {
            std::cout << "function 'setup(param2)' not found " << std::endl;
        }
        delete RunFoo;
    }
    catch(Sqrat::Exception ex)
    {
        std::cout << "Main: " << ex.Message();
        ::msleep(5000);
    }
    return 0;
}
