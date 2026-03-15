# OpenGL Showcase (WIP)

A beginner-friendly OpenGL project focused on building a visual showcase and gradually leveraging core and advanced OpenGL capabilities.

## Vision

The ultimate aim of this repository is to become an **OpenGL showcase**: a collection of scenes, effects, and rendering techniques that demonstrate what the API standard can do.

## Current Status

This project currently contains:

- A working C++ OpenGL setup using GLFW + GLAD
- Basic shaders in the `src/` folder
- Supporting libraries and references (GLM, STB, LearnOpenGL resources)

## Project Goals

- Build a stable rendering foundation (window, input, camera, shader management)
- Add reusable rendering modules (meshes, textures, materials, model loading)
- Implement advanced effects step-by-step
- Organize demos into clear showcase scenes
- Keep code readable and easy to extend

## Planned Showcase Features

- Lighting models: ambient, diffuse, specular, PBR basics
- Texturing pipeline and material workflows
- Model loading and scene composition
- Post-processing (framebuffers, bloom, tone mapping)
- Shadows (directional, point, spot)
- Skybox and environment mapping
- Instancing and performance-oriented rendering
- Optional effects: SSAO, normal/parallax mapping, deferred rendering

## Build and Run (Windows)

The workspace already includes a VS Code build task configured for g++.

### Option 1: VS Code Task

1. Open the workspace in VS Code.
2. Run the default build task: **C/C++: g+ build active file**.
3. Execute the generated binary:

```bash
./main.exe
```

### Option 2: Manual Command

Use the same command pattern as the task configuration:

```bash
C:/w64devkit/bin/g++.exe -g -std=c++17 -static -static-libgcc -static-libstdc++ \
  -I./include -L./lib \
  ./src/stbimage.c ./src/glad.c ./src/main.cpp \
  -lglfw3 -lgdi32 -lopengl32 \
  -o ./main.exe
```

Then run:

```bash
./main.exe
```

## Main Project Structure

```text
include/      Third-party headers (GLAD, GLFW, GLM, STB)
lib/          Link libraries
src/          Main source and shader files
solution/     Reference LearnOpenGL solutions and examples
source/       Upstream/source dependencies and builds
```

## Suggested Next Milestones

1. Add a camera system with mouse + keyboard controls.
2. Introduce a shader utility class and texture loader abstraction.
3. Create a scene manager to switch between showcase demos.
4. Add one advanced feature per milestone (shadows, HDR, bloom, etc.).
5. Document each new technique with screenshots and notes.

## Contribution Direction

Contributions should prioritize:

- Visual clarity and demonstration value
- Clean, modular rendering code
- Incremental features with clear documentation

## License

This repository contains multiple third-party components with their own licenses in their respective folders. Check each dependency before redistribution.
