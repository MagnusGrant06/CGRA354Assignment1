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


private:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	GLuint vao = 0;
	GLuint vbo_pos = 0;
	GLuint vbo_norm = 0;
	GLuint ibo = 0;
};