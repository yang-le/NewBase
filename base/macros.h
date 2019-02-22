// Copyright [year] <Copyright Owner>

#pragma once

#ifdef _MSC_VER
#define NEW_BASE_API __declspec(dllexport)
#else
#define NEW_BASE_API __attribute__ ((visibility ("default")))
#endif

#define NEW_BASE_BEGIN namespace nb {
#define NEW_BASE_END }

#define DISALLOW_COPY_AND_ASSIGN(classname) \
  classname(const classname &) = delete;    \
  classname &operator=(const classname &) = delete

#ifdef SINGLETON_IMPLIMENTATION
#define DECLARE_SINGLETON(classname)                                      \
 public:                                                                  \
  static classname& instance() {                                          \
    static classname instance;                                            \
    return instance;                                                      \
  }                                                                       \
                                                                          \
 private:                                                                 \
  classname() = default;                                                  \
  ~classname() = default
#else
#define DECLARE_SINGLETON(classname)                                      \
 public:                                                                  \
  static classname& instance();                                           \
                                                                          \
 private:                                                                 \
  classname() = default;                                                  \
  ~classname() = default
#endif
