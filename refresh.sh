#!/bin/bash
gcc -o screensaver screensaver.c -lSDL2
cp screensaver.service ~/.config/systemd/user/
systemctl --user daemon-reload
systemctl --user enable screensaver.service
systemctl --user restart screensaver.service

