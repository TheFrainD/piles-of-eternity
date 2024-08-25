#include <iostream>

#include "resource/resource_manager.h"

struct MyResource {
    int b;

    explicit MyResource(int a) : b(a) {}

    ~MyResource() { std::cout << "MyResource destroyed!\n"; }
};

struct MyResourceLoader {
    using ResultType = std::shared_ptr<MyResource>;

    ResultType operator()(int a) { return std::make_shared<MyResource>(a); }
};

int main(int argc, char *args[]) {
    auto my_res =
        res::g_resource_manager.loadResource<MyResource, MyResourceLoader>(
            "my_res", 42);
    std::cout << "b: " << my_res->b << '\n';
    return 0;
}
