# B-YEP-500-NCE-5-1-zia-julien.augugliaro

Build tool : `mkdir build && cd build && conan install .. --build=missing &&
cmake .. -G “Unix Makefiles” && cmake --build .`

How to load a configuration file in C++ ?
Suppose we use json files : https://github.com/nlohmann/json
To read a json from stream, we simply use `std::ifstream` and deserialize.
IMPLEMENT : https://github.com/nlohmann/json#integration
