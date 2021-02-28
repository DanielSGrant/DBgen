@echo off

for %%i in ("%~dp0.") do set "root=%%~fi"
if not exist %root%"\bin" mkdir %root%\bin

rem cmake -S . -B build & cmake --build build --config Debug &
rem copy %root%\build\Build\core\Debug\bioinformatics.exe %root%\bin & %root%\bin\bioinformatics.exe

cmake -S . -B build & cmake --build build --config Release &
copy %root%\build\Build\core\Release\bioinformatics.exe %root%\bin & %root%\bin\bioinformatics.exe
