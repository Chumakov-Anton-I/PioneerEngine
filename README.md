# PioneerEngine

A simple game engine

## Purpose

Developing your own game engine is a nice way to improve your programmer skill. Please read the [DevLog section](docs/devlog.md)

## Features

**PioneerEngine** is a cross-platform application. It uses OpenGL 3.3 and only open-source libraries.
It also uses STL as logn as it's possible.

## Building

Requirements:
* CMake version at least 3.20
* C++ compiler supports C++17 standard

Clone this repository:
```
git clone git@github.com:Chumakov-Anton-I/PioneerEngine.git
```
or
```
git clone https://github.com/Chumakov-Anton-I/PioneerEngine.git
```

Build the application with CMake:
```
md build && cd build
cmake -S <path-to-source-tree> -B .
cmake --build .
```
Don't make your **build** directory into the source tree.

You can also open the source tree with your favorite IDE (if it supports CMake projects) and just call the building command.
