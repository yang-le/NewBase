// Copyright [year] <Copyright Owner>

#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include "base/factory.h"
#include "base/macros.h"
#include "base/smart_ptr.h"

namespace nb {
namespace detail {
typedef std::map<std::string, std::unique_ptr<abstarct_factory_base>> class_factory_map;
typedef std::map<std::string, class_factory_map> base_factory_map;

NEW_BASE_EXPORT std::mutex& get_mutex();
NEW_BASE_EXPORT class_factory_map& get_class_factory_map(
    const std::string& base);

template <typename ClassObject, typename Base>
class class_factory : public abstract_factory<Base> {
 public:
  Base* produce(const std::string& /* key */) const {
    return new ClassObject;
  }
};

template <typename Derived, typename Base>
void regist_class(const std::string& class_name) {
  auto factory = utility::make_unique<class_factory<Derived, Base>>();

  {
    std::lock_guard<std::mutex> lock(detail::get_mutex());
    auto& factory_map = detail::get_class_factory_map(typeid(Base).name());
    factory_map.insert(std::make_pair(class_name, std::move(factory)));
  }
}
}  // namespace detail

template <typename Base>
Base* create_class_obj(const std::string& class_name) {
  abstract_factory<Base>* factory = nullptr;

  {
    std::lock_guard<std::mutex> lock(detail::get_mutex());
    auto& factory_map = detail::get_class_factory_map(typeid(Base).name());
    if (factory_map.find(class_name) != factory_map.end()) {
      factory =
          dynamic_cast<abstract_factory<Base>*>(factory_map[class_name].get());
    }
  }

  Base* classobj = nullptr;
  if (factory) {
    classobj = factory->produce();
  }

  return classobj;
}
}  // namespace nb

#define CLASS_FACTORY_REGIST(Derived, Base)                      \
  namespace {                                                    \
  struct class_register_##Base##_##Derived {                     \
    class_register_##Base##_##Derived() {                        \
      nb::detail::regist_class<Derived, Base>(#Derived);         \
    }                                                            \
  };                                                             \
  class_register_##Base##_##Derived register_##Base##_##Derived; \
  }
