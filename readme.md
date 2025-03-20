# Screensaver (Wayland only)

My hack job of a screensaver for Wayland. Behaviour:

- blank the screen after a period of inactivity (don't turn the screen off)
- unblank on any user activity, without asking for a password

Useful for saving OLED TV pixels, where the TV has annoying behaviour
when the output signal is turned off (like screen lockers seem to do).

Wayland doesn't come with a screensaver, and there don't seem to be any
existing packages that do what I want.

If you're using X, try XScreenSaver or gnome-screensaver.

# Installation and usage
```sh
sudo apt update
sudo apt install libsdl2-dev

# make sure the screen res is correct in screensaver.c

# test the screensaver works:
./run_screensaver.sh

# Run a service that runs the screensaver on inactivity.
# Set inactivity timeout in service.sh: TIMEOUT_MS
./install_or_update.sh
```
