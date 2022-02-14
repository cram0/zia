# Build Zia

rm -rf build/
mkdir build/
cd build/
conan install .. --build=missing
cmake .. -G "Unix Makefiles"
cmake --build .
cd ..

# Build modules

# Network
cd modules/network
cmake -G "Unix Makefiles"
cmake --build .
cd ../../build
