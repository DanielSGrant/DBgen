@echo off

for %%i in ("%~dp0.") do set "root=%%~fi"
if not exist %root%"\bin" mkdir %root%\bin

cmake -S . -B build\debug & cmake --build build\debug --config Debug &
copy %root%\build\debug\project\Build\core\Debug\bioinformatics.exe %root%\bin & %root%\bin\bioinformatics.exe

rem cmake -S . -B build\release & cmake --build build\release --config Release &
rem copy %root%\build\release\project\Build\core\Release\bioinformatics.exe %root%\bin & %root%\bin\bioinformatics.exe
