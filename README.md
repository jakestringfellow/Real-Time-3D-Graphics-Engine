# Skybox Showcase

<img align="right" src="https://user-images.githubusercontent.com/98133775/207860960-6d09561f-93ae-4663-aa24-b004edfebdf5.png" width="360px" alt="picture">

<img align="center" src="https://github.com/Fall22Graphics/finalproject-graphics-fa2022-jakestringfellow/blob/main/Screen%20Shot%202022-12-15%20at%205.49.28%20AM.png" width="360px" alt="picture">


## Project Description: 
* Project showcasing the different types of environments one can make when using cubemaps. Skyboxes are a method of creating
  backgrounds commonly used in 3D computer graphics scenes to give the user an illusion of depth.
* The cubemap textures are made from a panoramic image converted into 6 different images to represent the 6 inward-facing 
  faces of the skybox. The camera and rendered objects are positioned within this skybox. 
* No matter where in the world the camera moves to or rotates towards, a skybox texture will be rendered in the scene's background.
* Objects in the scene are rendered for scale (in this case a Sun and orbiting moon).
                       
## Technologies used:  
* OpenGL - Open Graphics Library
* SDL - Simple DirectMedia Layer
* GLAD - OpenGL Load Library
* GLSL - GL Shading Language: Used to write vertex and fragment shaders for models and skybox

## How to install and run: 
* download repository locally
*                         run "python3 build.py" to build the program
*                         run the executable with "./project"


## Acknowledgements: 
* Significant code provided in by Professor Mike Shah during Fall 2022 Computer Graphics course
* Acknowledged in relevant files
