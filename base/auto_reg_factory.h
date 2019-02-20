#pragma once

#include "base/factory.h"
#include "base/macros.h"

NEW_BASE_BEGIN

namespace todo {
template <typename Product>
class auto_reg_factory : public abstract_factory<Product> {
public:
    template <typename T>
    struct register_handler {
        template <typename... Args>
        register_handler(const std::string& key, Args&&... args) {
            auto_reg_factory<Product>::instance().map_.emplace(key, [&] {
                return new T(std::forward<Args...>(args)...);
            });
        }
    };

    virtual Product* produce(const std::string& key) const override {
        if (map_.find(key) == map_.end()) {
            return nullptr;
        }

        return map_.at(key)();
    };

private:
    std::map<std::string, std::function<Product*()>> map_;

    DECLARE_SINGLETON(auto_reg_factory);
};
}

NEW_BASE_END

#define REGIST_PRODUCT(Base, T, key, ...) \
    namespace { auto_reg_factory<Base>::register_handler<T> handler_##Base##_##T##_##key(#key, ##__VA_ARGS__); }
#define REGIST_PRODUCT_SIMPLE(T, key, ...) REGIST_PRODUCT(T, T, key, ##__VA_ARGS__)
