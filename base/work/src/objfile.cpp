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
	int i = 0;
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

	if (vao != 0) return;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo_pos);
	glGenBuffers(1, &vbo_norm);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_norm);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}
void ObjFile::draw() {
	if (vao == 0) return;

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
void ObjFile::destroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo_pos);
	glDeleteBuffers(1, &vbo_norm);
	glDeleteBuffers(1, &ibo);
	vao = 0;
}

void ObjFile::printMeshData() {

}