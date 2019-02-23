#pragma once

#include <string>
#include <map>
#include <functional>
#include <memory>
#include "base/macros.h"

NEW_BASE_BEGIN

class abstarct_factory_base {
    // this base class is used to hide the template parameters.
public:
    virtual ~abstarct_factory_base() = default;
};

template <typename Product>
class abstract_factory : public abstarct_factory_base {
public:
    std::unique_ptr<Product> produce_unique(const std::string& key = "") const
    {
        return std::unique_ptr<Product>(produce(key));
    }

    std::shared_ptr<Product> produce_shared(const std::string& key = "") const
    {
        return std::shared_ptr<Product>(produce(key));
    }

private:
    virtual Product* produce(const std::string& key = "") const = 0;
};

NEW_BASE_END
