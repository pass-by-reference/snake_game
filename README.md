# snake_game

A snake game written in opengl.

Code snippets and tutorial by [learnopengl](https://learnopengl.com/).

## Building

I only tested and built it in linux / macOS. Haven't tried with windows, but with the CMakeList it should be possible to build.

If you want to build with windows, you might have to regenerate and replace the `glad.c` file with [here](https://glad.dav1d.de/). Also there may be linking errors. See section on [linking](https://learnopengl.com/Getting-started/Creating-a-window) for more info on how to build for windows.

**Prerequisites**

You need these prerequisites before you can build / compile

`cmake`: `v3.22.1`

`clang / clang++`: `Atleast v14.0.0`

`opengl`: `Atleast v3.3`

**Building / Compiling / Running**

To build: `bash run.sh`

To compile: `cd release && make`

To run: `cd release && ./snake`
