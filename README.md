# Physics Engine From Scratch

A game engine built from scratch in C++ for learning low-level programming, game development, rendering, and physics.

## Goal

The goal of this project is to understand how game engines work internally by implementing their core systems instead of relying on high-level abstractions.

The project progressively explores:

* C++ and memory management
* Mathematics and linear algebra
* Software rendering
* Rasterization
* Physics and collision detection
* 2D and 3D graphics
* OpenGL and GPU programming
* Shaders
* Game engine architecture

## Current State

The engine currently includes an SDL3 window, a CPU framebuffer, basic rasterization, and early 3D rendering.

Current implemented systems include:

* SDL3 window
* CPU framebuffer
* Pixel rendering
* Line rasterization
* Triangle rasterization
* Software rasterizer
* Early 3D rendering
* OBJ model loading

Development is currently focused on building the mathematical and rendering foundations required for the physics and engine systems.

## Roadmap

The project is being developed progressively, from low-level mathematics and software rendering to physics simulation, GPU rendering, and engine architecture.

See the complete roadmap:

**[View the full roadmap](https://github.com/S4LPICON/physics-engine-from-scratch/blob/main/ROADMAP.md)**

## Philosophy

The purpose of this project is not to create a production-ready engine.

It is an educational project focused on understanding what happens underneath the abstractions normally provided by game engines and graphics libraries.

Rather than relying on existing engine systems, the project implements core concepts from scratch whenever practical, using external libraries primarily for platform-level functionality such as window creation and presentation.
