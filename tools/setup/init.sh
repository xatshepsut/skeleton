#!/bin/sh

mkdir .dependencies
rm -rf .dependencies/*
cd .dependencies
git clone https://github.com/namark/libsimple_support
git clone https://github.com/namark/libsimple_geom
git clone https://github.com/namark/libsimple_sdlcore
git clone https://github.com/namark/libsimple_graphical
git clone https://github.com/namark/libsimple_interactive
cd ..
./tools/setup/install.sh "$@"
