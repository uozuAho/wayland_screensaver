# Screensaver (Wayland only)

Wayland doesn't come with a screensaver, and there don't seem to be any
existing packages that do what I want:

- blank the screen after a period of inactivity (don't turn the screen off)
- unblank on any user activity, without asking for a password

If you're using X, try XScreenSaver or gnome-screensaver.

# Installation and usage
```sh
sudo apt update
sudo apt install libsdl2-dev
mkdir -p ~/.icons/hidden_cursor/cursors
cp left_ptr ~/.icons/hidden_cursor/cursors/

# make sure the screen res is correct in screensaver.c
./refresh.sh
```

