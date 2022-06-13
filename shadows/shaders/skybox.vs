#version 400 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 modelPos;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 pos;
uniform bool skybox = false;
void main(){

	// Output position of the vertex, in clip space : MVP * position

	gl_Position =  MVP * vec4(vertexPosition_modelspace+pos,1);

	//gl_Position =  projection * view * vec4(vertexPosition_modelspace+pos,1);
	UV = vertexUV;
	modelPos = vertexPosition_modelspace;
}

