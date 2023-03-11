#include "mesh.h"



Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{

	//number of things to draw
	m_drawCount = numVertices;

	//generate array
	glGenVertexArrays(1, &m_vertexArrayObject);

	//bind vertexes to arrays
	glBindVertexArray(m_vertexArrayObject);

	//apply buffer to array
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	//make buffers act as an array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);


	//put data and put on gpu
	//size of for how big
	//make data static
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);


	//give attribute to array
	glEnableVertexAttribArray(0);


	//how tell opengl to read arttibute as an aray
	//which attribute is trying to interpt
	//how many piece of data
	//tell how data is stored
	//normalize?
	//skipping effect, continuous
	//how much it needs to start from beginning
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//stop binding, vertex is no longer affected
	glBindVertexArray(0);

}


Mesh::~Mesh()
{



}


void Mesh::Draw()
{

	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);


}