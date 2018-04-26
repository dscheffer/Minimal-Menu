# Minimal Menu
Minimal Menu is as the name suggests a minimal system menu for Plasma5. The plasmoid is inspired by macOS's apple menu.

<i>Note: Minimal menu only fully works on Ubuntu based systems like KDE neon at the moment.</i>

![alt text](screenshot.png "Screenshot")

## Tested on 
Ubuntu 16.04 with
- Plasma 5.12.4
- KDE Frameworks 5.45.0
- Qt 5.10.0

## Requirements
Build:
- libkf5activitiesstats-dev >= 5.45.0
- libkf5config-dev >= 5.45.0
- libkf5plasma-dev >= 5.45.0
- Qt >= 5.10

Runtime:
- kde-cli-tools >= 5.12.4

## Build & Install
Run these instructions to build and install the plasmoid.
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DKDE_INSTALL_LIBDIR=lib -DKDE_INSTALL_USE_QT_SYS_PATHS=ON -Dgtest_disable_pthreads=ON  ..
make
make install
```
## Test
Tests can be run after build from inside the build directory using:
```
make && make test
```

If the plasmoid is installed it can also be run using the plasmoidviewer before adding it to the desktop.
```
plasmoidviewer --applet /usr/local/share/plasma/plasmoids/dscheffer.minimalmenu
```