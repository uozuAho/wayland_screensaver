#!/bin/bash
gcc -o screensaver screensaver.c -lSDL2
cp screensaver.service ~/.config/systemd/user/
mkdir -p ~/.icons/hidden_cursor/cursors
cp left_ptr ~/.icons/hidden_cursor/cursors/

systemctl --user daemon-reload
systemctl --user enable screensaver.service
systemctl --user restart screensaver.service

