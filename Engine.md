# CSC 581 - Game Engine - Project Milestone 1  
**Team Submission – Group No: 27**

---

## Core Architecture  

### Core Graphics Setup  
Our graphics layer uses a straightforward SDL3 pipeline. At startup, the engine initializes SDL, opens a resizable window, and creates a renderer. Control then passes to the main game loop, which handles input, updates entity locations, processes sprite animations, and manages auto-moving entities.  

A significant portion of the boilerplate came from the *Feeling-Loopy* assignment (basic init function, main loop, initial window rendering), which we later modified to include title and size handling. For sprites, entity definitions include parameters describing sprite sheet details, and the engine extracts frames and updates animations per entity using their defined animation cadence.  

📄 **References**  
- `src/engine/engine.cpp` (window and renderer setup, main loop)  

---

### Generic Entity System  
Entities represent all game objects in the engine. Each entity stores attributes like size, movement, texture, and role-based flags (`movable`, `controllable`, `affectedByGravity`, `platform`, `collidable`, `enemy`, etc.).  

- **Static and Dynamic Entities**: Different constructors are provided depending on whether the entity is static or dynamic.  
- **Path Vectors**: Auto-moving entities use path vectors (velocity applied for a fixed duration) for predictable movement.  
- **Customization**: Entities expose an `update()` function for developers to add custom logic.  

The engine maintains a list of entities and updates them on each tick, ensuring uniform handling across the game loop.  

📄 **References**  
- `src/engine/entity.cpp` (entity constructors, update handling)  
- `src/engine/engine.cpp` (entity drawing and updates)  

---

### Physics System  
The physics system uses **semi-implicit Euler integration** to simulate stable and predictable motion.  

- Each entity tracks velocity and acceleration.  
- Gravity can be toggled on/off for a platformer feel.  
- Every frame, gravity is applied (if enabled), velocities are updated, and new target positions are calculated.  
- Global gravity and timestep values are centralized, ensuring small adjustments can rebalance the system consistently.  
- Non-controllable entities (platforms, enemies) use path vectors for smooth scripted motion.  

📄 **References**  
- `src/engine/physics.cpp` (applyPhysics, gravity configuration)  

---

### Input Handling System  
Our input system is modular and extensible, moving from a simple key array to a more robust `inputDetect` class.  

- **Tracking**: Uses SDL ScanCodes to track all keys each frame.  
- **Data Structures**:  
  - `gPrev`: Key states from previous frame  
  - `gCurr`: Current frame states  
  - `gDownList`: Keys currently pressed  
- **Event Detection**: Derives whether a key is *held*, *pressed*, or *released*.  
- **Handler**: The `inputHandler` maps keys to actions in the game loop. Defaults are `WASD` for movement and `Space` for jump, but developers can redefine mappings.  
- **Mouse Support**: Handles SDL events for mouse input, extending usability to other game genres.  

📄 **References**  
- `src/engine/input.cpp` (inputDetect implementation)  
- `src/engine/input_handler.cpp` (inputHandler, key mappings)  

---

### Collision Detection System  
Collisions are handled using **axis-aligned bounding boxes (AABBs)** for efficiency and precision.  

- Each entity generates a bounding box based on position, size, and scale.  
- Movement resolution occurs in **two passes** (X then Y), backing off by the maximum penetration depth to prevent tunneling.  
- A **predictive overlap probe** checks collisions before applying movement to avoid jitter.  
- The system can handle multiple simultaneous collisions reliably.  

This design allowed us to move beyond SDL’s built-in `HasIntersection` (which only detects overlaps) to a system that can also determine collision direction and depth.  

📄 **References**  
- `src/engine/collision.cpp` (collision detection and resolution)  
- `src/engine/physics.cpp` (collision integration with physics)  

---

### Scaling System  
The scaling system gives flexibility across resolutions and rendering styles, implemented in the `ScalingMode` class.  

- **Proportional Logical Scaling**: Maintains aspect ratio via letterboxing with smooth linear scaling.  
- **Constant Pixel Scaling**: Renders textures at raw pixel sizes using nearest-neighbor filtering, preserving a retro look.  
- **Methods**:  
  - `init()` – Initialize scaling mode and resolution  
  - `apply()` – Apply scaling to renderer and textures  
  - `applyWindowSize()` – Adjust window dimensions dynamically  
  - `setMode()` – Switch between scaling modes at runtime  
  - `onMouseWheel()` – Resize window using scroll input  

Scaling toggle is mapped in the input system:  
- **Ctrl + N** → Proportional (Letterbox)  
- **Ctrl + M** → Constant Pixel  

SDL functions used:  
- `SDL_SetRenderLogicalPresentation()` – Define logical resolution & aspect ratio  
- `SDL_SetDefaultTextureScaleMode()` – Set default scaling (linear/nearest)  
- `SDL_SetTextureScaleMode()` – Apply scaling per texture  
- `SDL_SetWindowSize()` – Update actual window size  

📄 **References**  
- `src/engine/scaling.cpp` (init, apply, toggle implementations)  

---

## Team Notes  
This milestone focused on establishing the **core engine architecture**. We developed systems for graphics, entities, physics, input, collision, and scaling, ensuring that each subsystem was both functional and extensible for future iterations.  