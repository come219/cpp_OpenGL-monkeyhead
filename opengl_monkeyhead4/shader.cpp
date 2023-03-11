#include "shader.h"

//shader load and error check
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);

static GLuint CreateShader(const std::string& text, GLenum shaderType);


Shader::Shader(const std::string& fileName)
{

	//ctor

	//create allocation for program and store id
	main_program = glCreateProgram();


	//create the shaders and allocated space
	main_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	main_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{

		glAttachShader(main_program, main_shaders[i]);

	}

	//tells what opengl to read in shader program
	glBindAttribLocation(main_program, 0, "position");


	//check and link program
	glLinkProgram(main_program);
	CheckShaderError(main_program, GL_LINK_STATUS, true, "Error: Program failed to link!");

	//check and validate program
	glValidateProgram(main_program);
	CheckShaderError(main_program, GL_VALIDATE_STATUS, true, "Error: Program failed to validate!");

}



Shader::~Shader()
{

	//dtor



	//delete shaders
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{

		glDetachShader(main_program, main_shaders[i]);
		glDeleteShader(main_shaders[i]);

	}


	//delete program
	glDeleteProgram(main_program);




}

void Shader::Bind()
{
	glUseProgram(main_program);

}


static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{

		std::cout << "Error: shader creation failed" << std::endl;
	}


	const GLchar* shaderSourceStrings[1];

	GLint shaderSourceStringsLengths[1];


	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringsLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);
	glCompileShader(shader);


	//gl shader program compile check
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: opengl shader failed to compile!");

	return shader;

}

//load and check shader
static std::string LoadShader(const std::string& fileName)
{

	std::ifstream file;

	file.open((fileName).c_str());

	std::string output;
	std::string line;


	if (file.is_open())
	{

		while (file.good())
		{

			getline(file, line);
			output.append(line + "\n");


		}


	}
	else
	{

		std::cerr << "Unable to load shader!" << std::endl;

	}

	return output;


}



//return shader error   
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };


	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{

		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}

		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}


		std::cerr << errorMessage << ": " << error << std::endl;


	}



}
