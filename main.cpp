

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


/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
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

    /**
      add definitons for the script
      */
    Sqrat::ConstTable(sq.theVM())
                        .Const("True", 1)
                        .Const("False", 0);

    /**
      add global functions for the script
      */
    Sqrat::RootTable(sq.theVM()).Func("GlobalCall",
                     &RunCtx::GlobalCall);

    /**
      add classes and thir methods for the script
    */

    Sqrat::Class<Demo> cls(sq.theVM(), _SC("Demo"));
    cls.Ctor<int>();
    cls.Ctor();
    cls.Func(_SC("Method"), &Demo::Method);
    Sqrat::RootTable().Bind(_SC("Demo"), cls);

    try{
        MyScript scr = sq.compile_script(script.c_str());
        scr.run_script();

        /**
         * @brief mimics a script like arduino sketches with setup() and loop() functions
         *
         */
        Sqrat::Function f = Sqrat::RootTable().GetFunction(_SC("setup"));
        if(!f.IsNull())
        {
            Sqrat::SharedPtr<int>   srv;
            int                     rv;

            if(argc==2)
                srv = f.Evaluate<int>(nullptr);
            else
                srv = f.Evaluate<int>(argv[2]);
            if(srv.Get()==0)
            {
                throw (Sqrat::Exception("function setup must return True or False "));
            }
            else
                rv = (*srv.Get());

            if(rv == 1)
            {
                Sqrat::Function fl = Sqrat::RootTable().GetFunction(_SC("loop"));
                if(fl.IsNull())
                {
                    std::cout << "function 'var loop()' not found" << std::endl;
                }
                else
                {
                    srv = fl.Evaluate<int>();
                    if(srv.Get()==0)
                    {
                        throw (Sqrat::Exception("function loop must return True or False "));
                    }
                }
            }
        }
        else
        {
            std::cout << "function 'setup(param2)' not found " << std::endl;
        }
    }
    catch(Sqrat::Exception ex)
    {
        std::cout << "Main: " << ex.Message();
        ::msleep(50000);
    }
    return 0;
}
