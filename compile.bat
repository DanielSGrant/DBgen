@echo off
rem cmake -S . -B build/release && cmake --build build/release --config Release  && %cd%/build/release/project/Build/core/Release/bioinformatics.exe
cmake -S . -B build/debug && cmake --build build/debug --config Debug && %cd%/build/debug/project/Build/core/Debug/bioinformatics.exe
