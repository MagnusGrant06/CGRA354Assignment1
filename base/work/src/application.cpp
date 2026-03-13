
// std
#include <iostream>
#include <string>
#include <chrono>

// glm
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// project
#include "application.hpp"
#include "cgra/cgra_gui.hpp"
#include "cgra/cgra_shader.hpp"

#include "objfile.hpp"

using namespace std;
using namespace cgra;
using namespace glm;


Application::Application(GLFWwindow *window) : m_window(window) {
	
	// build the shader
	shader_builder color_sb;
	color_sb.set_shader(GL_VERTEX_SHADER, CGRA_SRCDIR + std::string("//res//shaders//default_vert.glsl"));
	color_sb.set_shader(GL_FRAGMENT_SHADER, CGRA_SRCDIR + std::string("//res//shaders//default_frag.glsl"));
	m_shader = color_sb.build();

	// build the mesh for the triangle
	//m_model.setup();
		
}


void Application::render() {
	
	// retrieve the window hieght
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height); 

	m_windowsize = vec2(width, height); // update window size
	glViewport(0, 0, width, height); // set the viewport to draw to the entire window

	// clear the back-buffer
	glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	// enable flags for normal/forward rendering
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS);

	// calculate the projection and view matrix
	mat4 proj = perspective(1.f, float(width) / height, 0.1f, 1000.f);
	mat4 view = translate(mat4(1), vec3(0, -5, -20));
	view = rotate(view, glm::radians(180.0f), vec3(0, 1, 0));

	// set shader and upload variables
	glUseProgram(m_shader);
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "uProjectionMatrix"), 1, false, value_ptr(proj));
	glUniformMatrix4fv(glGetUniformLocation(m_shader, "uModelViewMatrix"), 1, false, value_ptr(view));

	//custom vector for holding user inputted information for color
	GLint col = glGetUniformLocation(m_shader, "color");
	glUniform3f(col, colors[0], colors[1], colors[2]);

	//custom vector for holding user inputted information for light position
	GLint light_y = glGetUniformLocation(m_shader, "light_position");
	glUniform3f(light_y, (float)light_width, (float)light_height, (float)light_depth);


	// draw the model
	//m_model.draw();
	my_object.draw();
}


void Application::renderGUI() {

	// setup window
	ImGui::SetNextWindowPos(ImVec2(5, 5), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(500, 160), ImGuiSetCond_Once);
	ImGui::Begin("Mesh loader", 0);

	// Loading buttons
	static char filename[512] = "";
	ImGui::InputText("", filename, 512);
	ImGui::SameLine();
	if (ImGui::Button("Load")) {
		// TODO load mesh from 'filename'
		my_object.loadOBJ(filename);
		my_object.build();
	}

	ImGui::SameLine();
	if (ImGui::Button("Print")) {
		// TODO print mesh data
		my_object.printMeshData();
	}

	ImGui::SameLine();
	if (ImGui::Button("Unload")) {
		// TODO unload mesh
		my_object.destroy();
	}

	ImGui::NewLine();
	ImGui::ColorEdit3("Pick Color", colors);

	//two sliders for moving light around object
	ImGui::SliderFloat("Change Vertical Rotation of light", &light_height, -1.0, 1.0);
	ImGui::SliderFloat("Change Horizontal Rotation of light", &light_width, -1.0, 1.0);
	ImGui::SliderFloat("Change Z Rotation of light", &light_depth, -1.0, 1.0);

	// finish creating window
	ImGui::End();
}


void Application::cursorPosCallback(double xpos, double ypos) {
	(void)xpos, ypos; // currently un-used
}


void Application::mouseButtonCallback(int button, int action, int mods) {
	(void)button, action, mods; // currently un-used
}


void Application::scrollCallback(double xoffset, double yoffset) {
	(void)xoffset, yoffset; // currently un-used
}


void Application::keyCallback(int key, int scancode, int action, int mods) {
	(void)key, (void)scancode, (void)action, (void)mods; // currently un-used
}


void Application::charCallback(unsigned int c) {
	(void)c; // currently un-used
}