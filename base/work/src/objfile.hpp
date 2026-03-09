#pragma once


#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "opengl.hpp"

class ObjFile {

public:

	void loadOBJ(std::string filepath);
	
	void build();
	void draw();
	void destroy();

	void printMeshData();

	//custom Vertex struct to reduce code size in concrete implementation
	struct Vertex {
		glm::vec3 position;
		//glm::vec3 texture;
		glm::vec3 normal;
	};
	
private:

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	GLuint vao = 0;
	GLuint vbo = 0;
	GLuint ibo = 0;
};