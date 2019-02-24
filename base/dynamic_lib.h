// Copyright [year] <Copyright Owner>

#pragma once

#include <string>
#include <map>
#include <memory>
#include "base/macros.h"

#ifdef _MSC_VER
#include <windows.h>
#define LOAD(x) LoadLibrary(x)
#define UNLOAD(x) (void)FreeLibrary(x)
#define FIND(x, func) GetProcAddress(x, func)
#define ERROR_STR() "cannot load library: " + path
#else
#include <dlfcn.h>
#define LOAD(x) dlopen(x, RTLD_LAZY)
#define UNLOAD(x) (void)dlclose(x)
#define FIND(x, func) dlsym(x, func)
#define ERROR_STR() dlerror()
#endif

NEW_BASE_BEGIN

class dynamic_lib {

#ifdef _MSC_VER
 using lib_t = HMODULE;
#else
 using lib_t = void*;
#endif

 public:
    explicit dynamic_lib(const std::string& path) {
        lib_ = LOAD(path.c_str());
        if (!lib_) {
            throw std::runtime_error(ERROR_STR());
        }
    }

    ~dynamic_lib() {
        if (lib_) {
            (void)UNLOAD(lib_);
        }
    }

    template <typename Ret, typename... Args>
    Ret call(const std::string& func, Args&&... args) {
        using T = Ret(Args...);
        T* f = reinterpret_cast<T*>(FIND(lib_, func.c_str()));
        if (f == nullptr) {
            throw std::runtime_error("can not find function: " + func);
        }

        return f(std::forward<Args>(args)...);
    }

    lib_t lib_;
};

NEW_BASE_EXPORT void load_dynamic_lib(const std::string& path);

NEW_BASE_END
