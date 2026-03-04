#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <sstream>

#include "objfile.hpp"

using std::string;
void ObjFile::loadOBJ(string filepath) {
	
	std::ifstream file(filepath);
	string currentLine;
	int i;
	while (std::getline(file, currentLine)) {
		
		std::istringstream stringStream(currentLine);
		string str;

		stringStream >> str;

		float v1, v2, v3;
		stringStream >> v1 >> v2 >> v3;

		if (str == "v") {
			vertices.push_back(glm::vec3(v1, v2, v3));
		}
		else if (str == "vt") {
			normals.push_back(glm::vec3(v1, v2, v3));

		}
		else if (str == "f") {
			indices.push_back(i++);

		}
		else {
			continue;
		}
	}

}

void ObjFile::build() {

}
void ObjFile::draw() {

}
void ObjFile::destroy() {

}

void ObjFile::printMeshData() {

}