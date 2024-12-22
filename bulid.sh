#!/bin/bash
export PATH=/mingw64/bin:/usr/bin:$PATH
export PKG_CONFIG_PATH=/mingw64/lib/pkgconfig
gcc $(pkg-config --cflags gtk4) -o test_gtk test_gtk.c $(pkg-config --libs gtk4)
