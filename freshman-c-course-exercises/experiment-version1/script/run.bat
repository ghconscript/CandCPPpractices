@echo off
pushd .
if not exist build (
 md build
)
cd build
cmake -G"MinGW Makefiles" ..
mingw32-make.exe -j
if %errorlevel% neq 0 (
 echo There was an error during the build step.
)
popd