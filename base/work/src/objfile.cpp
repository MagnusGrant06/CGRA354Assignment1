#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <fstream>
#include <string>
#include <sstream>

#include "objfile.hpp"

// filepath for testing
// C:\Users\magnu\projects\CGRA354_Framework\base\work\res\assets\teapot.obj

using std::string;

void ObjFile::loadOBJ(string filepath) {

	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;
	std::vector<int> temp_indices;
	std::ifstream file(filepath);
	string currentLine;
	while (std::getline(file, currentLine)) {
		
		std::istringstream stringStream(currentLine);
		string str;

		stringStream >> str;

		//load vertex positions from file into temporary vector
		if (str == "v") {
			float v1, v2, v3;
			stringStream >> v1 >> v2 >> v3;
			temp_positions.push_back(glm::vec3(v1, v2, v3));
		}

		//load vertex normals from file into temporary vector
		else if (str == "vn") {
			float v1, v2, v3;
			stringStream >> v1 >> v2 >> v3;
			temp_normals.push_back(glm::vec3(v1, v2, v3));

		}
		//load face information into temporary vector
		else if (str == "f") {
			string triplet;
			while (stringStream >> triplet) {
				std::istringstream tripletStream(triplet);
				string token;

				while (std::getline(tripletStream, token, '/')) {
					temp_indices.push_back(std::stoi(token)-1);
				}
			}

		}
		else {
			continue;
		}
	}

	//loop through temp lists and create list of vertex to lookup in build
	for (int i = 0; i < temp_indices.size()-2; i+=3) {
		vertices.push_back(Vertex(temp_positions[temp_indices[i]], temp_normals[temp_indices[i + 2]]));
		indices.push_back(vertices.size()-1);
	}

}

void ObjFile::build() {

	if (vao != 0) return;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);

	//i use one vbo storing all my custom vector objects
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	//i then tell opengl how to step through my vertex struct with these lines
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

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
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	vao = 0;
}

void ObjFile::printMeshData() {
	for (int index : indices) {
		std::cout << "Index: " << index << std::endl;
	}
	for (Vertex v : vertices) {
		std::cout << "Vertex Position: " << v.position.x << ", " << v.position.y << ", " <<v.position.z << std::endl;
		std::cout << "Vertex Normal: " << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << std::endl;
	}
}