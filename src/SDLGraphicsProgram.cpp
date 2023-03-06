#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::string> defaultFaces 
{
    "skyboxTextures/px.ppm",
    "skyboxTextures/nx.ppm",
    "skyboxTextures/py.ppm",
    "skyboxTextures/ny.ppm",
    "skyboxTextures/pz.ppm",
    "skyboxTextures/nz.ppm"
};
std::vector<std::string> blueClouds
{
    "skyboxTextures/bluecloud_lf.jpg",
    "skyboxTextures/bluecloud_rt.jpg",
    "skyboxTextures/bluecloud_up.jpg",
    "skyboxTextures/bluecloud_dn.jpg",
    "skyboxTextures/bluecloud_ft.jpg",
    "skyboxTextures/bluecloud_bk.jpg",
};
std::vector<std::string> spaceRed
{
    "skyboxTextures/bkg3_right1.png",
    "skyboxTextures/bkg3_left2.png",
    "skyboxTextures/bkg3_top3.png",
    "skyboxTextures/bkg3_bottom4.png",
    "skyboxTextures/bkg3_front5.png",
    "skyboxTextures/bkg3_back6.png",
};
std::vector<std::string> snow
{
    "skyboxTextures/snow_px.jpg",
    "skyboxTextures/snow_nx.jpg",
    "skyboxTextures/snow_py.jpg",
    "skyboxTextures/snow_ny.jpg",
    "skyboxTextures/snow_pz.jpg",
    "skyboxTextures/snow_nz.jpg",
};
std::vector<std::string> night
{
    "skyboxTextures/night_px.jpg",
    "skyboxTextures/night_nx.jpg",
    "skyboxTextures/night_py.jpg",
    "skyboxTextures/night_ny.jpg",
    "skyboxTextures/night_pz.jpg",
    "skyboxTextures/night_nz.jpg",
};
std::vector<std::string> tutorial
{
    "skyboxTextures/right.jpg",
    "skyboxTextures/left.jpg",
    "skyboxTextures/top.jpg",
    "skyboxTextures/bottom.jpg",
    "skyboxTextures/front.jpg",
    "skyboxTextures/back.jpg",
};

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	m_window = NULL;

	m_width = w;
	m_height = h;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();


    // Setup our Renderer
    m_renderer = new Renderer(w,h); 

    // Set up Skybox
    m_skybox = new Object();
    m_skybox->SetSkyboxTexture(defaultFaces);
    m_skybox->MakeSkybox();   
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    }
    delete m_skybox;

    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL(){
	//Success flag
	bool success = true;

	return success;
}

// Create the Moon
//Object* sphere3;
//SceneNode* Moon;
//Create the Earth
Object* sphere2;
SceneNode* Earth;
// Create the Sun
Object* sphere;
SceneNode* Sun;

// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::Loop(){

    // ================== Initialize the planets ===============
    static float rotate = 0.0f;

    // Create new geometry for Earth's Moon
    //sphere3 = new Sphere();
    //sphere3->LoadTexture("rock.ppm");
    // Create a new node using sphere3 as the geometry
    //Moon = new SceneNode(sphere3);

    // Create the Earth
    sphere2 = new Sphere();
    sphere2->LoadTexture("planetTextures/planet.ppm");
    Earth = new SceneNode(sphere2);

    // Create the Sun
    sphere = new Sphere();
    sphere->LoadTexture("planetTextures/rock.ppm");
    Sun = new SceneNode(sphere);


    // Render our scene starting from the sun.
    m_renderer->setRoot(Sun);
    // Make the planets each a child of the Sun
    Sun->AddChild(Earth);

    // Set a default position for our camera
    m_renderer->GetCamera(0)->SetCameraEyePosition(0.0f,0.0f,20.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 5.0f;

    // While application is running
    while(!quit){

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboard input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
              m_renderer->GetCamera(0)->MouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            m_renderer->GetCamera(0)->MoveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            m_renderer->GetCamera(0)->MoveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            m_renderer->GetCamera(0)->MoveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            m_renderer->GetCamera(0)->MoveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
                            break;
                        case SDLK_RCTRL:
                            m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
                            break;

			case SDLK_0:
			    m_skybox->SetSkyboxTexture(defaultFaces);
			    m_skybox->MakeSkybox();
			    break;

			case SDLK_1:
			    m_skybox->SetSkyboxTexture(blueClouds);			    
			    m_skybox->MakeSkybox();
			    break;  

			 case SDLK_2:
                            m_skybox->SetSkyboxTexture(night);
                            m_skybox->MakeSkybox();      
                            break;  

			 case SDLK_3:
                            m_skybox->SetSkyboxTexture(snow);
                            m_skybox->MakeSkybox();     
                            break;  
			 case SDLK_4:
                            m_skybox->SetSkyboxTexture(spaceRed);
                            m_skybox->MakeSkybox();
                            break;		 
			 case SDLK_5:
                            m_skybox->SetSkyboxTexture(tutorial);
                            m_skybox->MakeSkybox();
                            break;
                    }	
                break;
            }
        } // End SDL_PollEvent loop.
	
	static float rot = 0;
	rot+=1;
	if(rot>360){rot=0;}
	
        Sun->GetLocalTransform().LoadIdentity();		
        Sun->GetLocalTransform().Rotate(rot*0.01,0.0f,1.0f,0.0f);
	Sun->GetLocalTransform().Scale(3.0f, 3.0f,3.0f);

        Earth->GetLocalTransform().LoadIdentity();		
        // ... transform the Earth 
	Earth->GetLocalTransform().Scale(0.4f, 0.4f, 0.4f);       
	Earth->GetLocalTransform().Translate(20.0f, 0.0f, 0.0f);
	Earth->GetLocalTransform().Rotate(rot*0.05,0.0f,1.0f,0.0f);


        // Update our scene through our renderer
        m_renderer->Update();
        // Render our scene using our selected renderer
        m_renderer->Render();

	
	// Render the skybox !
	m_skybox->RenderSkybox(m_renderer->GetCamera(0), m_width*1.2, m_height*1.2);
		

        // Delay to slow things down just a bit!
        SDL_Delay(50);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
