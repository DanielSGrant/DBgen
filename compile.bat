@echo off

for %%i in ("%~dp0.") do set "root=%%~fi"
if not exist %root%"\bin" mkdir %root%\bin

rem cmake -S . -B build & cmake --build build --config Debug &
rem copy %root%\build\Build\core\Debug\DBgen.exe %root%\bin & %root%\bin\DBgen.exe

cmake -S . -B build & cmake --build build --config Release &
copy %root%\build\Build\core\Release\DBgen.exe %root%\bin & %root%\bin\DBgen.exe
