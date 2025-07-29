#!/bin/bash
gcc ../source/yarnspin.c `sdl2-config --libs --cflags` -lGLEW -lGL -lm -lpthread
