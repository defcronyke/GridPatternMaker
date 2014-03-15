if exist build\ rmdir build\ /S /Q
mkdir build
cd build

SET PATH=%PATH%;C:\mingw64\bin;C:\Program Files (x86)\CMake 2.8\bin;C:\SDL2-2.0.2\x86_64-w64-mingw32\include\SDL2;C:\SDL2-2.0.2\x86_64-w64-mingw32\bin;C:\SDL2_image-2.0.0\x86_64-w64-mingw32\include\SDL2;C:\SDL2_image-2.0.0\x86_64-w64-mingw32\bin;C:\Program Files\7-Zip

cmake -G "MinGW Makefiles" ..
mingw32-make

xcopy ..\lib\3rd-party\win-x86_64-mingw\*.* %CD%\ /E
xcopy ..\res %CD%\res\ /E
xcopy ..\examples %CD%\examples\ /E
copy ..\LICENSE %CD%\
copy ..\INSTALL %CD%\
copy ..\README.md %CD%\
if not exist %CD%\LICENSES\ xcopy ..\lib\3rd-party\win-x86_64-mingw\LICENSES %CD%\LICENSES\ /E

mkdir GridPatternMaker-v1.0.0-Win-bin-release-x86_64
cd GridPatternMaker-v1.0.0-Win-bin-release-x86_64
copy ..\gridpatternmaker.exe %CD%\
xcopy ..\..\lib\3rd-party\win-x86_64-mingw\*.* %CD%\ /E
xcopy ..\..\res\*.png %CD%\res\
xcopy ..\..\examples %CD%\examples\ /E
copy ..\..\LICENSE %CD%\
copy ..\..\INSTALL %CD%\
copy ..\..\README.md %CD%\
cd ..

7z a GridPatternMaker-v1.0.0-Win-bin-release-x86_64.7z GridPatternMaker-v1.0.0-Win-bin-release-x86_64\
rmdir GridPatternMaker-v1.0.0-Win-bin-release-x86_64\ /S /Q
cd ..
