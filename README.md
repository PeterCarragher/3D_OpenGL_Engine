# OpenGL-Engine
Simple graphics engine implemented using C++ with the OpenGL libraries.

FOR DEMO:
  To move, use the arrow keys.  
  To look around, use the mouse. 
  To turn the torch on/off, press 'F'.

REQUIREMENTS:
  Visual Studio 2015 (will add CMakeList for generating project files and makefiles on Unix)

Libraries (all binaries built for 32x packaged with repo in Dependencies folder):
  GLEW   -> extension wrangler for OpenGL.  
  GLFW   -> utilities library.  
  SOIL   -> image loader. 
  ASSIMP -> model loader. 
  GLM    -> maths library for linear algebra. 

Features: 
  Model loader using ASSIMP library which loads multiple formats (.obj, .3ds, .dae, etc.).  
  Camera wrapper class which sets up the view matrix and process's keyboard/mouse input.  
  Lighting shader using the Phong lighting model. 
  3 lighting casters implemented (directional, spotlight, point light). 
  
Future Features:  
  Optimise Model loader and matrix operations with CUDA.  
  Implement physics engine. 
  Use cubemaps for skyboxs. 
  Add anti-aliasing for imported models.  
  Add advanced features to the shader - bump/normal maps, ambient occlusion etc. 
  Add CMakeList for cross platform support 
