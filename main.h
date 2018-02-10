#ifndef MAIN_H_
#define MAIN_H_



class Device;
struct RunCtx
{
    static int GlobalCall(const char* s)
    {
        printf("demo called %s \n", s);
        return 0;
    }
};

extern RunCtx*  PCTX;
extern int      _Debug;

#endif
