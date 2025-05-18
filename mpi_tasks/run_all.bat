@echo off
setlocal enabledelayedexpansion

if not exist build mkdir build
cd build

for %%F in (../*.cpp) do (
    echo Compiling %%~nF...
    mpicxx ../%%~nF.cpp -o %%~nF.exe
)

echo.
echo Running tasks...

for %%T in (14 15 16 17 18 19 20 21 22 ^
            23 24 25 26 27 28 29 30 31 32) do (
    echo.
    echo --- Running %%T ---
    mpiexec -n 4 %%T.exe
)

cd ..
echo.
echo All tasks completed.
pause