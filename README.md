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

