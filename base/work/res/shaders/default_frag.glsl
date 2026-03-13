#version 330 core

// uniform data
uniform mat4 uProjectionMatrix;
uniform mat4 uModelViewMatrix;
uniform vec3 color;
uniform vec3 light_position;

// viewspace data (this must match the output of the vertex shader)
in VertexData {
	vec3 position;
	vec3 normal;
} f_in;

// framebuffer output
out vec4 fb_color;

void main() {
	// calculate shading
	//color is no longer hard coded and is controlled by user
	vec3 surfaceColor = color;
	//eye is no longer used as we use custom user input for light direction
	//vec3 eye = normalize(-f_in.position); // direction towards the eye
	float light = dot(light_position,normalize(f_in.normal)); // difference between the surface normal and direction towards the eye
	vec3 finalColor = mix(surfaceColor / 4, surfaceColor, light);

	// output to the frambuffer
	fb_color = vec4(finalColor, 1);
}
