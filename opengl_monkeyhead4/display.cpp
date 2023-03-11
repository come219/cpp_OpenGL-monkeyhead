#include "display.h"
#include <SDL_image.h>


display::display(int width, int height, const std::string& title)
{


	//std::cout << "Constructor!" << std::endl;



	//Initialize SDL

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{

		std::cerr << "SDL failed to initialize!" << std::endl;

		


	}
	else
	{

		std::cerr << "SDL initialized!" << std::endl;


	}


	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != IMG_INIT_PNG)
	{
		std::cerr << "SDL_image failed to initialize!" << std::endl;

		

	}


	//colour space
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	//size allocation
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//extra buffer(s) size
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	//create main window
	main_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//establish opengl context
	main_glContext = SDL_GL_CreateContext(main_window);


	//check glew
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{

		std::cerr << "Glew failed to initialize" << std::endl;


	}

	//open window
	main_isClosed = false;





}


display::~display()
{

	//std::cout << "Deconstructor!" << std::endl;


	//close opengl context
	SDL_GL_DeleteContext(main_glContext);


	//destroy sdl window
	SDL_DestroyWindow(main_window);

	//close sdl
	SDL_Quit();

}



void display::updateBuffers()
{

	//swap window into buffer
	SDL_GL_SwapWindow(main_window);



	//action listener
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{

		//close window with [x]
		if (e.type == SDL_QUIT)
		{
			main_isClosed = true;

		}


	}



}



bool display::returnisClosed()
{
	//return main window boolean
	return main_isClosed;


}


void display::clearWindow(float r, float g, float b, float a)
{


	//set colour to window and assign
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);



}
