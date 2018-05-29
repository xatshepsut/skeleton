#!/bin/sh

mkdir .dependencies
rm -rf .dependencies/*
cd .dependencies
git clone https://github.com/namark/libsimple_support
git clone https://github.com/namark/libsimple_geom
git clone https://github.com/namark/libsimple_sdlcore
git clone https://github.com/namark/libsimple_graphical
cd ..
./install_depends.sh "$@"
