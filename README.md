# PioneerEngine

A simple experimental game engine.

## Purpose

Developing your own game engine is a nice way to improve your programmer skill.
Please read the [DevLog section](docs/devlog/devlog.md)

## Features

**PioneerEngine** is a cross-platform application. It uses OpenGL 3.3 and only open-source libraries.
It also uses STL as logn as it's possible.

### Dependencies

| Library                                    | Description              | License |
|--------------------------------------------|--------------------------|---------|
| [spdlog](https://github.com/gabime/spdlog) | Fast C++ logging library | MIT     |
| [GLFW](https://github.com/glfw/glfw) | Multi-platform library for OpenGL and Vulkan development on the desktop. | zlib |
| [sigslot](https://github.com/palacaze/sigslot) | Header-only, thread safe implementation of signal-slots for C++ | MIT |
| [Dear ImGui](https://github.com/ocornut/imgui) | Bloat-free graphical user interface library | MIT |
| [GLM](https://github.com/g-truc/glm) | Header only C++ mathematics library for graphics software | MIT |

The all third-party libraries are included as submodules.

## Building

Requirements:
* git
* CMake version 3.20 and newer
* C++ compiler supporting C++17 standard

Clone this repository:
```shell
git clone --recurse-submodules git@github.com:Chumakov-Anton-I/PioneerEngine.git
```
or
```shell
git clone --recurse-submodules https://github.com/Chumakov-Anton-I/PioneerEngine.git
```

Build the application with CMake:
```shell
md build && cd build
cmake -S <path-to-source-tree> -B .
cmake --build .
```
> [!WARNING]
> Don't make your **build** directory into the source tree!

You can also open the source tree with your favorite IDE (if it supports CMake projects) and just call the building command.
