# scrite
scripting engine template C++ / Squirrel

template for squirrel embedded script engine

```cpp
      /**
      export global functions to script
      */
    Sqrat::RootTable(sq.theVM()).Func("GlobalCall",
                     &RunCtx::GlobalCall);

    /**
      export classes to script
    */

    Sqrat::Class<Demo> cls(sq.theVM(), _SC("Demo"));
    cls.Ctor<int>();
    cls.Ctor();
    cls.Func(_SC("Method"), &Demo::Method);
    Sqrat::RootTable().Bind(_SC("Demo"), cls);
```



###  You can check my reverse ssh online service and online key value database at 

[reverse ssh as a service](http://www.mylinuz.com)

[key value database as a service](https://www.meeiot.org)


