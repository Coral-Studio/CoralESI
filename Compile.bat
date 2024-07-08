@echo off

cd /d %~dp0

set DIR="."

for /R %DIR% %%f in (*.cpp) do (
    echo Compiling %%f
    g++ "%%f" -std=c++14 -o "%%~dpnf.exe"
)

echo Done.

pause