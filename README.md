# skeleton
So far it's just a blocky scull.

# How to make it work
You'll need a C++ compiler that supports C++17 standard.
Install sdl2 somehow, either globally in the system or in the project root(include and lib folders).
Run *./init_depends.sh*, optionally providing make paramters, for example apropriate compiler command: `./init_depends.sh CXX=g++-7`
The script will clone some dependencies and install them in the project root and if all goes well you should be able to build the project:
```
make
./out/main
```
and in future update the dependencies using *./update_depends.sh* script.
