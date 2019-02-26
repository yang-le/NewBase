// Copyright [year] <Copyright Owner>

#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace nb {

class abstarct_factory_base {
  // this base class is used to hide the template parameters.
 public:
  virtual ~abstarct_factory_base() {};
};

template <typename Product>
class abstract_factory : public abstarct_factory_base {
 public:
  virtual Product* produce(const std::string& /* key */ = "") const = 0;

  std::unique_ptr<Product> produce_unique(const std::string& key = "") const {
    return std::unique_ptr<Product>(produce(key));
  }

  std::shared_ptr<Product> produce_shared(const std::string& key = "") const {
    return std::shared_ptr<Product>(produce(key));
  }
};

}  // namespace nb
