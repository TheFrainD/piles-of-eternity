#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace res {
class ResourceManager {
public:
    ResourceManager() = default;

    template <typename ResourceType, typename LoaderType, typename... Args>
    std::shared_ptr<ResourceType> load_resource(const std::string &name,
                                                Args &&...args) {
        if (resources_.contains(name)) {
            return std::static_pointer_cast<ResourceType>(resources_[name]);
        }

        LoaderType loader;
        std::shared_ptr<ResourceType> resource =
            loader(std::forward<Args>(args)...);
        resources_[name] = resource;

        return resource;
    }

    template <typename ResourceType>
    std::shared_ptr<ResourceType> get_resource(const std::string &name) {
        if (resources_.contains(name)) {
            return std::static_pointer_cast<std::shared_ptr<ResourceType>>(
                resources_[name]);
        }

        return nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<void>> resources_;
};

}  // namespace res