#!/bin/sh

# A release .tar.7z archive will be created under the build directory.

mkdir -p build
cd build
cmake ..
make
strip gridpatternmaker

cp -a ../examples .
mkdir -p res
cp -a ../res/*.png res
cp -a ../LICENSE ../INSTALL ../lib/3rd-party/win-x86_64-mingw/LICENSES/ .

mkdir -p GridPatternMaker-v1.0.0-Linux-bin-release-x86_64
cd GridPatternMaker-v1.0.0-Linux-bin-release-x86_64

cp -a ../../examples .
mkdir -p res
cp -a ../../res/*.png res
cp -a ../gridpatternmaker ../../LICENSE ../../INSTALL ../../lib/3rd-party/win-x86_64-mingw/LICENSES/ .

cd ..
tar cvf GridPatternMaker-v1.0.0-Linux-bin-release-x86_64.tar GridPatternMaker-v1.0.0-Linux-bin-release-x86_64
7z a GridPatternMaker-v1.0.0-Linux-bin-release-x86_64.tar.7z GridPatternMaker-v1.0.0-Linux-bin-release-x86_64.tar
rm GridPatternMaker-v1.0.0-Linux-bin-release-x86_64.tar
rm -rf GridPatternMaker-v1.0.0-Linux-bin-release-x86_64
