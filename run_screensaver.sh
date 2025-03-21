#!/bin/bash
set -e

gcc -o screensaver screensaver.c -lSDL2
./screensaver
