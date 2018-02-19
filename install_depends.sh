#!/bin/sh
cd .dependencies

cd libsimple_support
make install PREFIX=../../  "$@"
make install PREFIX=../libsimple_graphical
cd ..

cd libsimple_geom
make install PREFIX=../../  "$@"
make install PREFIX=../libsimple_graphical
cd ..

cd libsimple_graphical
make install PREFIX=../../ "$@"
cd ..

cd ..
