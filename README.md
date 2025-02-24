# Raycaster

This is a a basic raycasting demo built in C++ using a library called [raylib](https://www.raylib.com/), which provides some basic tools for game development. For this project only it's math and rendering functions were used, as the goal of this project was to learn how to implement the raycasting algorithm from scratch. 

# Background

Much of the engine is based on a [design document](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) by F. Permadi, although some of the decisions I made simply through inituition. To be specific, the primary difference between my implementation and most of the common ones is that I calculate the point of intersection between each line and player rather than arriving at the same result using grid-based math. This allows my engine to create objects of any size or shape, at the cost of performance.

# Development Enviorment 

Refer to https://github.com/raysan5/raylib/wiki to setup the development enviorment with your desired IDE. 

# Compiling to WebAssembly

- Enusre web assembly is setup correctly (You need to install emscripten as well as compile the library with some specific flags enabled, refer to https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5).)
- Run `compile_for_web.bat`

# Screenshot
![screenshot](https://github.com/user-attachments/assets/72b5cdaa-53cd-47b1-9eb1-570163e76099)
