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
#else
#include <dlfcn.h>
#define LOAD(x) dlopen(x, RTLD_LAZY)
#define UNLOAD(x) (void)dlclose(x)
#define FIND(x, func) dlsym(x, func)
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
        load(path);
    }

    ~dynamic_lib() {
        unload();
    }

    void load(const std::string& path) {
        lib_ = LOAD(path.c_str());
        if (!lib_) {
            throw std::runtime_error("can not load library: " + path);
        }
    }

    void unload() {
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

namespace detail {
    using dynamic_lib_map = std::map<std::string, std::unique_ptr<dynamic_lib>>;
    NEW_BASE_API dynamic_lib_map& get_dynamic_lib_map();
}

NEW_BASE_API void load_dynamic_lib(const std::string& path);

NEW_BASE_END
