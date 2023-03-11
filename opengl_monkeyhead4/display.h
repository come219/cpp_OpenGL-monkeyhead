#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>


#include <SDL.h>
#include <glew.h>




class display

{

public:

	display(int width, int height, const std::string& title);

	virtual ~display();

	void clearWindow(float r, float g, float b, float a);

	void updateBuffers();

	bool returnisClosed();



protected:



private:

	display(const display& other) {}

	void operator=(const display& other) {}

	SDL_Window* main_window;

	SDL_GLContext main_glContext;


	bool main_isClosed;

};

#endif //DISPLAY_H