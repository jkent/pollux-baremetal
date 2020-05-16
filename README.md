POLLUX Baremetal
================

POLLUX Baremetal is a development system for the POLLUX VR3520F and LF1000 System On a Chip (SoC) platform.  It includes low level bootstrap code to get up and running quickly.  Features and be enabled and disabled easily via `make config` in a project directory.

Getting started
---------------

You need to have an arm-none-eabi toolchain installed and in your path.  On Ubuntu and Debian you can use the provided toolchain package:

```sh
sudo apt-get install gcc-arm-none-eabi
```

Alternatively (and recommended) you can build a toolchain using [crosstool-ng](https://crosstool-ng.github.io/).  You also need build-essential and python3-serial installed.

When checking out the repository, you need to use --recursive.  Clone like so:

```sh
git clone --recurisve https://github.com/jkent/pollux-baremetal baremetal
```

Now, within your shell, you need to source the export.sh script in any terminal you wish to use baremetal in.

```sh
source baremetal/export.sh
```

This sets up the necessary paths and environment variables.  You're all set!

In the baremetal/examples directory, there are a few projects which you can try, copy and use for the base of your own programs.

Just run `make run` within their directory and they'll be built and automatically loaded via [micromon](https://github.com/jkent/pollux-micromon).