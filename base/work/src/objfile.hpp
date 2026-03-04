#pragma once


#include <iostream>
#include <vector>
#include <glm/glm.hpp>


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

};