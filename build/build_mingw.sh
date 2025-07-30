#!/bin/bash
gcc ../source/yarnspin.c `sdl2-config --libs --cflags` -lwinmm -lopengl32 -lm -lpthread -o yarnspin.exe
cp "C:\msys64\mingw64\bin\libwinpthread-1.dll" .
