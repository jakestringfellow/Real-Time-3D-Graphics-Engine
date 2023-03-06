// Main source file for the program's loop
#include "SDLGraphicsProgram.hpp"

int main(int argc, char** argv){

	// Create the SDL Graphics Program
	SDLGraphicsProgram mySDLGraphicsProgram(1280,720);
	
	// Run the graphics program until quit
	mySDLGraphicsProgram.Loop();
	
	return 0;
}
