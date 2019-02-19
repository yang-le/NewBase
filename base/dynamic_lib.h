// Copyright [year] <Copyright Owner>

#pragma once

#include <string>
#include <map>
#include <memory>

#ifdef _WIN32
#include <windows.h>
using lib_t = HMODULE;
#define LOAD(x) LoadLibrary(x)
#define UNLOAD(x) (void)FreeLibrary(x)
#define FIND(x, func) GetProcAddress(x, func)
#else
#include <dlfcn.h>
using lib_t = void*;
#define LOAD(x) dlopen(x, RTLD_LAZY)
#define UNLOAD(x) (void)dlclose(x)
#define FIND(x, func) dlsym(x, func)
#endif

class dynamic_lib {
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
    typename Ret call(const std::string& func, Args&&... args) {
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
    __declspec(dllexport) dynamic_lib_map& get_dynamic_lib_map();
}

void load_dynamic_lib(const std::string& path) {
    auto& map = detail::get_dynamic_lib_map();
    if (map.find(path) == map.end()) {
        map.emplace(path, std::make_unique<dynamic_lib>(path));
    }
}
