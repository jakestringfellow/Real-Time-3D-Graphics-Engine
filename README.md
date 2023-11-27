# 3D Graphics Engine with Real-Time Rendering

<img align="right" src="https://user-images.githubusercontent.com/98133775/207860960-6d09561f-93ae-4663-aa24-b004edfebdf5.png" width="360px" alt="picture">

<img align="center" src="https://github.com/Fall22Graphics/finalproject-graphics-fa2022-jakestringfellow/blob/main/Screen%20Shot%202022-12-15%20at%205.49.28%20AM.png" width="360px" alt="picture">

## Introduction:
* This project introduces a sophisticated 3D graphics engine capable of real-time rendering, designed to craft dynamic, visually striking 3D scenes. Utilizing cutting-edge graphics programming techniques, the engine features custom shaders for realistic lighting and material properties, delivering high-quality visual experiences.

## Key Features: 
* Custom Shader Implementation: Developed using GLSL (OpenGL Shading Language), the custom shaders, including vertex and fragment shaders, enable advanced       rendering techniques. These encompass diffuse and ambient reflection, and specular highlights, culminating in lifelike lighting and material effects.
* Geometry Processing Pipeline: Facilitates the addition of vertices, indices, and texture coordinates, supporting the construction of intricate 3D models and scenes.
* Interactive Camera Controls: Features mouse-based look functionality and movement controls, offering users an intuitive means to navigate and explore 3D environments.
* Texture Mapping: Incorporates support for diffuse maps, augmenting realism by applying textures to object surfaces.
* Graphics Mathematics: Employs mathematical concepts like vector transformations, normal calculations, and specular reflection calculations to achieve precise and visually compelling outputs.
* Achieves skybox effect through the use of cubemaps, giving the illusion of a depth to the scenes surroundings.
* The cubemap textures are made from a panoramic image converted into 6 different images to represent the 6 inward-facing 
  faces of the skybox. The camera and rendered objects are positioned within this skybox.
                       
## Technologies used:  
* OpenGL - Open Graphics Library
* GLAD - OpenGL Load Library
* GLSL - GL Shading Language: Used to write vertex and fragment shaders for models and skybox

## How to install and run: 
* download repository locally
*                         run "python3 build.py" to build the program
*                         run the executable with "./project"


## Acknowledgements: 
* Significant code provided in by Professor Mike Shah during Fall 2022 Computer Graphics course
* Acknowledged in relevant files
