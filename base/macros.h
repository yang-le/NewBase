// Copyright [year] <Copyright Owner>

#pragma once

#ifdef _MSC_VER
#define NEW_BASE_EXPORT __declspec(dllexport)
#else
#define NEW_BASE_EXPORT __attribute__((visibility("default")))
#endif

#define DISALLOW_COPY_AND_ASSIGN(classname) \
  classname(const classname &) = delete;    \
  classname &operator=(const classname &) = delete

// I was considered to use Mayers' singleton like following

// template<typename T>
// class singleton
//{
// public:
//    static T& getInstance()
//    {
//        static T value;
//        return value;
//    }
//
// private:
//    singleton();
//    ~singleton();
//};

// But it seems not to work well across Dlls.
// To keep things simple, I came up with the following defines.
// see https://isocpp.org/wiki/faq/ctors#construct-on-first-use-v2.

#define DEFINE_SINGLETON(classname)               \
  classname &classname::instance() {              \
    static classname *instance = new classname(); \
    return *instance;                             \
  }

#define DECLARE_SINGLETON(classname)            \
 public:                                        \
  NEW_BASE_EXPORT static classname &instance(); \
                                                \
 private:                                       \
  classname();                                  \
  ~classname()
