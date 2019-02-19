#pragma once

#include <map>
#include <mutex>
#include <memory>
#include "base/factory.h"

template <typename ClassObject, typename Base>
class class_factory : public abstract_factory<Base> {
public:
    virtual Base* produce(const std::string&) const override { return new ClassObject; }
};

namespace detail {
    using class_factory_map = std::map<std::string, std::unique_ptr<abstarct_factory_base>>;
    using base_factory_map = std::map<std::string, class_factory_map>;

    __declspec(dllexport) std::mutex& get_mutex();
    __declspec(dllexport) base_factory_map& get_base_to_class_factory_map();

    class_factory_map& get_class_factory_map(const std::string& base) {
        auto& base_map = get_base_to_class_factory_map();
        if (base_map.find(base) == base_map.end()) {
            base_map.emplace(base, class_factory_map());
        }

        return base_map[base];
    }

    template <typename Derived, typename Base>
    void regist_class(const std::string& class_name) {
        auto factory = std::make_unique<class_factory<Derived, Base>>();

        {
            std::lock_guard<std::mutex> lock(get_mutex());
            auto& factory_map = get_class_factory_map(typeid(Base).name());
            factory_map.emplace(class_name, std::move(factory));
        }
    }
}

template <typename Base>
Base* create_class_obj(const std::string& class_name) {
    abstract_factory<Base>* factory = nullptr;

    {
        std::lock_guard<std::mutex> lock(detail::get_mutex());
        auto& factory_map = detail::get_class_factory_map(typeid(Base).name());
        if (factory_map.find(class_name) != factory_map.end()) {
            factory = dynamic_cast<abstract_factory<Base>*>(factory_map[class_name].get());
        }
    }

    Base* classobj = nullptr;
    if (factory) {
        classobj = factory->produce();
    }

    return classobj;
}

#define CLASS_FACTORY_REGIST(Derived, Base) \
namespace {                                                                 \
struct class_register_##Base##_##Derived {                                  \
    class_register_##Base##_##Derived() {                                   \
        detail::regist_class<Derived, Base>(#Derived);                      \
    }                                                                       \
};                                                                          \
class_register_##Base##_##Derived register_##Base##_##Derived;              \
}