# B-YEP-500-NCE-5-1-zia-julien.augugliaro

Build tool : `mkdir build && cd build && conan install .. --build=missing &&
cmake .. -G “Unix Makefiles” && cmake --build .`

How to load a configuration file in C++ ?
Suppose we use json files : https://github.com/nlohmann/json
To read a json from stream, we simply use `std::ifstream` and deserialize.

IMPLEMENT : https://github.com/nlohmann/json#integration

## Dependencies
## Conan
- install [conan](https://conan.io/downloads.html)
#### Windows
open `~/.conan/profiles/default`(if not exist run: `conan profile new --detect default`) in `[setting]` block add **`compiler.runtime=static`**
#### Linux/Mac (Unix)
open `~/.conan/profiles/default`(if not exist run: `conan profile new --detect default`) change **`compiler.libcxx=libstdc`** -> **`compiler.libcxx=libstdc++11`**

## PhPCGI
#### Ubuntu
```bash
sudo apt install php-cgi
```
#### Windows
- install [phpcgi-8](https://windows.php.net/downloads/releases/php-8.1.3-nts-Win32-vs16-x64.zip)


## Build Project

- ### All OS
##### The following commands only need to be executed once when the project is cloned
1. `git submodule update --init --recursive`
2. `git submodule update --recursive --remote`

- ### Linux/Mac (Unix)
1. `mkdir build`
2. `cd build`
3. `conan install .. --build=missing`
4. `cmake .. -G "Unix Makefiles"  -D CMAKE_BUILD_TYPE=Release`
5. `cmake --build . --config Release`

 one line command:
```bash
mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release && cmake --build . --config Release
```

- ### Windows
- install [Visual Studio](https://visualstudio.microsoft.com/downloads/)

1. `mkdir build`
2. `cd build`
3. `conan install .. --build=missing`
4. `cmake ..  -G "Visual Studio 17 2022" -A "x64" -D CMAKE_BUILD_TYPE=Release`
5. `cmake --build . --config Release`

 one line command(powershell only!):
```pwsh
mkdir build && cd build && conan install .. --build=missing && cmake ..  -G "Visual Studio 17 2022" -A "x64" -D CMAKE_BUILD_TYPE=Release && cmake --build . --config Release
```
