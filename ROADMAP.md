# Roadmap

The project is developed progressively, starting from low-level mathematics and software rendering and eventually building a physics-based game engine.

## Phase 1 — Core & Mathematics

* [x] C++ project structure
* [x] SDL3 window
* [ ] RAII and resource management
* [ ] Vector2
* [ ] Vector3
* [ ] Matrix3
* [ ] Matrix4
* [ ] Transform
* [ ] Quaternion
* [ ] Time management

## Phase 2 — CPU Renderer

### 2D

* [x] CPU framebuffer
* [x] Pixel rendering
* [x] Line rasterization
* [ ] Circle rasterization
* [ ] Rectangle rasterization
* [x] Triangle rasterization
* [ ] Triangle interpolation
* [ ] Alpha blending
* [ ] Texture sampling

### 3D

* [x] Basic 3D rendering
* [ ] Model transformations
* [ ] View transformations
* [ ] Perspective projection
* [x] Depth buffer
* [x] Backface culling
* [ ] Clipping
* [x] Mesh representation
* [ ] Indexed geometry
* [x] OBJ loading
* [ ] Vertex normals
* [ ] UV coordinates
* [ ] Basic software lighting

## Phase 3 — Physics 2D

### Dynamics

* [ ] Rigid bodies
* [ ] Mass
* [ ] Forces
* [ ] Gravity
* [ ] Acceleration
* [ ] Velocity
* [ ] Euler integration
* [ ] Fixed timestep

### Collision Detection

* [ ] AABB
* [ ] Circle
* [ ] AABB vs AABB
* [ ] Circle vs Circle
* [ ] Circle vs AABB
* [ ] Collision normals
* [ ] Penetration depth
* [ ] Contact points
* [ ] Broad phase
* [ ] Narrow phase

### Collision Resolution

* [ ] Position correction
* [ ] Impulse resolution
* [ ] Restitution
* [ ] Friction
* [ ] Static bodies
* [ ] Dynamic bodies

### Rotational Dynamics

* [ ] Angular velocity
* [ ] Torque
* [ ] Moment of inertia
* [ ] Angular acceleration
* [ ] Rotational impulse
* [ ] Rotational friction

## Phase 4 — Physics Sandbox

* [ ] Spawn rigid bodies
* [ ] Static platforms
* [ ] Gravity controls
* [ ] Physics debugging
* [ ] Collider visualization
* [ ] Contact visualization
* [ ] Velocity visualization
* [ ] Pause / resume
* [ ] Single-step simulation
* [ ] Physics reset

## Phase 5 — Engine Core

* [ ] Application
* [ ] Game loop
* [ ] Input system
* [ ] Time system
* [ ] Logging
* [ ] Scene
* [ ] Entity
* [ ] Transform
* [ ] Component system
* [ ] Camera
* [ ] Resource management

## Phase 6 — GPU Rendering

* [ ] OpenGL context
* [ ] Vertex buffers
* [ ] Index buffers
* [ ] Vertex arrays
* [ ] Vertex shaders
* [ ] Fragment shaders
* [ ] Uniforms
* [ ] Textures
* [ ] Depth testing
* [ ] Blending
* [ ] GPU mesh rendering

## Phase 7 — Materials & Lighting

* [ ] Materials
* [ ] Diffuse lighting
* [ ] Specular lighting
* [ ] Directional lights
* [ ] Point lights
* [ ] Spot lights
* [ ] Normal mapping
* [ ] Shadow mapping
* [ ] Skybox

## Phase 8 — Physics 3D

* [ ] 3D rigid bodies
* [ ] Sphere collider
* [ ] Box collider
* [ ] Plane collider
* [ ] Capsule collider
* [ ] Broad phase
* [ ] Narrow phase
* [ ] Contact manifolds
* [ ] 3D impulse solver
* [ ] Friction
* [ ] Angular dynamics
* [ ] GJK
* [ ] EPA

## Phase 9 — Assets & Engine Tools

* [ ] Asset manager
* [ ] Model loading
* [ ] Texture loading
* [ ] Material loading
* [ ] Shader management
* [ ] Scene serialization
* [ ] Debug renderer
* [ ] Physics debug renderer
* [ ] Profiler
* [ ] Frame statistics

## Phase 10 — Audio & Game Systems

* [ ] Audio system
* [ ] Spatial audio
* [ ] Input abstraction
* [ ] Game state
* [ ] Event system
* [ ] Particle system
* [ ] Basic UI

## Phase 11 — Performance

* [ ] CPU profiling
* [ ] Memory profiling
* [ ] Spatial partitioning
* [ ] SIMD experiments
* [ ] Multithreaded jobs
* [ ] Job system
* [ ] Parallel physics experiments

## Phase 12 — Demonstration Game

Build a small game using only the engine's own systems.

Possible projects:

* Physics sandbox
* Breakout
* Pong
* Platformer
* Physics-based puzzle
* Simple vehicle simulation

The final goal is not to compete with existing engines.

The goal is to understand the systems that make a game engine work.
