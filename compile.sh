#!/bin/bash

mkdir -p $PWD/build;
cd $PWD/build && cmake .. && cmake --build .;
cd $PWD/Build/core && ./dbgen;
