#!/bin/bash

mkdir -p build

cd build

if [ ! -d "vcokg" ]
    then git clone https://github.com/Microsoft/vcpkg.git 
fi

cd vcpkg

if hash vcpkg 2>/dev/null 
then 
    ./bootstrap-vcpkg.sh 
fi

VCPKG_COMMAND=vcpkg install --recurse
# Add your library ports here. 
$VCPKG_COMMAND boost-dynamic-bitset boost-integer boost-functional boost-move magic-enum
cd ..

cmake -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --target ALL_BUILD --config Release
cd ..