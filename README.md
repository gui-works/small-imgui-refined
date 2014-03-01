imgui
================================
A small multiplatform immediate mode graphical user interface with OpenGL3.2 backend.

About
-------------------------
Most of the code is pulled from: https://github.com/AdrienHerubel/imgui

Which is pulled from the recast library: http://code.google.com/p/recastnavigation/

With partial merges from: https://github.com/FlorianDeconinck/imgui/

TrueType loading and rendering is done using stb_truetype : http://nothings.org/stb/stb_truetype.h

The OpenGL backend was ported from OpenGL immediate mode to OpenGL 3.2 mainly to be compatible with Mac OS X core profile.

![Alt text](http://adrien.io/img/imgui/imgui.png)

Build
-------------------------
The only depedency is OpenGL. GLFW, GLEW are embeded with the samples.

Linux : Tested on Arch Linux, Ubuntu 12.10, Debian Wheezy with various versions of gcc

    cmake . && make
    ./sample


Mac OS X : Tested on 10.7 (Lion) with XCode 4.6. Only compatible with core profile contexts.

    cmake . && make
    ./sample

Windows : Tested on Windows 7 with Visual Studio 2008 and 2010

    cmake . -G "NMake Makefiles" && nmake

Usage
----------------------------

Check [sample.cc](sample.cc) for a detailed usage example.
