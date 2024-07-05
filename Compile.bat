set DIR="."

for /R %DIR% %%f in (*.cpp) do ( 
g++ %%f -std=c++14 -o %%~dpnf.exe
)

pause