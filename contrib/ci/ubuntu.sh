#!/bin/sh
set -e
set -x

#evaluate using Ubuntu's buildflags
eval "$(dpkg-buildflags --export=sh)"
#filter out -Bsymbolic-functions
export LDFLAGS=$(dpkg-buildflags --get LDFLAGS | sed "s/-Wl,-Bsymbolic-functions\s//")

rm -rf build
meson build --werror -Dman=false
#build with clang and -Werror
ninja -C build test -v

#make docs available outside of docker
ninja -C build install -v
mkdir -p dist/docs
cp build/docs/libfwupd/* dist/docs -R

#run static analysis (these mostly won't be critical)
ninja -C build scan-build -v
