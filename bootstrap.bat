
if not exist "build" mkdir build
cd build
if not exist "vcpkg" git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
if not exist "vcpkg.exe" call bootstrap-vcpkg.bat

set VCPKG_DEFAULT_TRIPLET=x64-windows
vcpkg install --recurse boost-dynamic-bitset boost-integer boost-functional boost-move magic-enum
cd ..

cmake -Ax64 -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --target ALL_BUILD --config Release
cd ..
