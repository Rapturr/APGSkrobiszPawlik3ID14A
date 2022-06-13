// Include GLFW
#include <glfw3.h>
//extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

int scene = 0;
int getSceneChoice(){
	return scene;
}
// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 6, 5 ); 
glm::vec3 getcameraposition(){
	return position;
}
void setposition(glm::vec3 pos){
	position = pos;
}
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;


// Direction : Spherical coordinates to Cartesian coordinates conversion
glm::vec3 direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
);
glm::vec3 movdir = vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		0,
		cos(verticalAngle) * cos(horizontalAngle)
);

	glm::vec3 getDirection(){
		return direction;
	}

void computeMatricesFromInputs(GLFWwindow* window){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	movdir = vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		0,
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);

	glm::vec3 moveup = glm::vec3(
		0,
		3.14f / 2.0f,
		0
	);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		//position += direction * deltaTime * speed;
		position += movdir * deltaTime * speed * 2.0f;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		//position -= direction * deltaTime * speed;
		position -= movdir * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_0 ) == GLFW_PRESS){
		scene = 0;
	}
	if (glfwGetKey( window, GLFW_KEY_1 ) == GLFW_PRESS){
		scene = 1;
	}
	if (glfwGetKey( window, GLFW_KEY_2 ) == GLFW_PRESS){
		scene = 2;
	}
	if (glfwGetKey( window, GLFW_KEY_3 ) == GLFW_PRESS){
		scene = 3;
	}
	if (glfwGetKey( window, GLFW_KEY_4 ) == GLFW_PRESS){
		scene = 4;
	}
	if (glfwGetKey( window, GLFW_KEY_5 ) == GLFW_PRESS){
		scene = 5;
	}
	// Move up
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += moveup * deltaTime * speed;
	}
	// Move down
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position -= moveup * deltaTime * speed;
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}