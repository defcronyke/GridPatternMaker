if exist build\ rmdir build\ /S /Q
mkdir build
cd build

SET PATH=%PATH%;C:\mingw\bin;C:\Program Files\CMake 2.8\bin;C:\SDL2-2.0.2\i686-w64-mingw32\include\SDL2;C:\SDL2-2.0.2\i686-w64-mingw32\bin;C:\SDL2_image-2.0.0\i686-w64-mingw32\include\SDL2;C:\SDL2_image-2.0.0\i686-w64-mingw32\bin;C:\Program Files\7-Zip

cmake -G "MinGW Makefiles" ..
mingw32-make

xcopy ..\lib\3rd-party\win-x86-mingw\*.* %CD%\ /E
xcopy ..\res %CD%\res\ /E
xcopy ..\examples %CD%\examples\ /E
copy ..\LICENSE %CD%\
copy ..\INSTALL %CD%\
copy ..\README.md %CD%\
if not exist %CD%\LICENSES\ xcopy ..\lib\3rd-party\win-x86_64-mingw\LICENSES %CD%\LICENSES\ /E

mkdir GridPatternMaker-v1.0.0-Win-bin-release-x86
cd GridPatternMaker-v1.0.0-Win-bin-release-x86
copy ..\gridpatternmaker.exe %CD%\
xcopy ..\..\lib\3rd-party\win-x86-mingw\*.* %CD%\ /E
xcopy ..\..\res\*.png %CD%\res\
xcopy ..\..\examples %CD%\examples\ /E
copy ..\..\LICENSE %CD%\
copy ..\..\INSTALL %CD%\
copy ..\..\README.md %CD%\
xcopy ..\LICENSES %CD%\LICENSES\ /E
cd ..

7z a GridPatternMaker-v1.0.0-Win-bin-release-x86.7z GridPatternMaker-v1.0.0-Win-bin-release-x86\
rmdir GridPatternMaker-v1.0.0-Win-bin-release-x86\ /S /Q
cd ..
