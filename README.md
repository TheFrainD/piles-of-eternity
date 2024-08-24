# Piles of Eternity

### Building
```
mkdir build
cd build
cmake -G Ninja \
        -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=third-party/cmake-conan/conan_provider.cmake \
        -DCMAKE_BUILD_TYPE=Release ..
```