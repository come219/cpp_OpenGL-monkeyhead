#include <iostream>

#include <glew.h>
#include <SDL.h>


#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

//int main(int argc, char **argv)
int main()
{


	//data is sent into processing
	
	//data is comprised of many dots
	//take and process the points - vertex shader
	//takes and connects the points and fill in- rasterization
	//processes the filled points creates the pixels - fragment shader
	//writes the pixels to output
	//(occuring in parallel)



	display display(800, 800, "Hello World!");



	

	Vertex vertices[] = {
							Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
							Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
							Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)),

	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./res/basicShader");

	texture texture("./res/grass.png");

	while (!display.returnisClosed())
	{


		display.clearWindow(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();
		texture.Bind(0);
		mesh.Draw();

		display.updateBuffers();

	}


	std::cout << "Hello, World!" << std::endl;





	return 0;



}