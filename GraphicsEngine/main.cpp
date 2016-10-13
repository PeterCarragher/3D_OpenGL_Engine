#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "globals.h"
#include "shader.h"
#include "model.h"

#include <iostream>

//Fucntion prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

bool keys[1024];
bool torchOn = false;
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
GLfloat lastX = 400, lastY = 300; //CURSOR initial position
bool firstMouse = true;
Camera camera(glm::vec3(3.0f, -0.3f, -3.9f), glm::vec3(0.0f, 1.0f, 0.0f), -180.f, 0.f);
glm::vec3 lightPos = glm::vec3(1.2f, 2.0f, -2.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

int main(){ 

	//-----------------SET UP AND INITIALISE GLFW & GLEW------------------//
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GraphicsEngine", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	if (window == NULL){

		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;

	}
	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){

		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;

	}

	//------------------VERTEX DATA AND VAO'S------------------//

	GLfloat cubeVertices[] {
		// Positions           // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	glm::vec3 cubePositions[] {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	GLuint indices[]{  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	glm::vec3 pointLightPositions[] {
		glm::vec3(2.217, 1.0714, 4.066)
	};
	glm::vec3 spotLightPositions[] {
	//  position                         direction
		glm::vec3(-2.405, 0.14, -1.106), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(2.801, 0.14, -0.949), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(3.637, -1.4, 0.954), glm::vec3(-0.737, -0.216, 0.641)
	};
	int NUM_SPOT_LIGHTS = 3;

	GLuint cubeVBO; //sets up openGL object, cubeVBO
	glGenBuffers(1, &cubeVBO); //binds buffer with ID 1 to cubeVBO

	//light VAO
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); //how to interpret vertex data
	glEnableVertexAttribArray(0); //vertex attributes are defauly disabled. enable attribute 0 (layout)
	glBindVertexArray(0);

	//set openGL attributes
	glViewport(0, 0, WIDTH, HEIGHT); //set viewport on current window context
	glEnable(GL_DEPTH_TEST);

	//Compile shaders
	Shader lightingShader("simpleShader.vert", "simpleLightShader.frag");

	//register callbacks via GLFW
	glfwSetKeyCallback(window, key_callback); //key_callback is regiestered to window context
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //WIREFRAME POLYGONS
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//load models
	Model flashlight("Assets/Models/Lights/Flashlight/flashlight.obj");
	Model scene("Assets/Models/scene/scene.obj");
	

	//---------------GAME LOOP-------------------//
	while (!glfwWindowShouldClose(window)){

		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		do_movement();

		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.Use();   
		// Transformation matrices
		glm::mat4 model;
		glm::mat4 projection = glm::perspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetCameraViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Set the lighting uniforms
		//directional light
		/*
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"), camera.getPos().x, camera.getPos().y, camera.getPos().z);*/
		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), spotLightPositions[0].x, spotLightPositions[0].y-0.5, spotLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.25f, 0.3f, 0.25f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.25f, 0.3f, 0.25f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.009);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.0032);
		
		//spotlight for flashlight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].position"), camera.getPos().x, camera.getPos().y, camera.getPos().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].direction"), camera.getDir().x, camera.getDir().y, camera.getDir().z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].innerCutOff"), glm::cos(glm::radians(20.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].outerCutOff"), glm::cos(glm::radians(35.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].linear"), 0.009);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight[0].quadratic"), 0.0032);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight[0].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "spotLight[0].torchOn"), torchOn);
		
		for (int x = 0; x < NUM_SPOT_LIGHTS*2; x+=2){
			float flicker; 
			if (x == 0) {
				flicker = 1;
			}
			else{
				flicker = floor((sin(glfwGetTime() * 20) / 2 + 0.5) + 0.7);
			}
			glm::vec3 pos = spotLightPositions[x]; 
			glm::vec3 dir = spotLightPositions[x + 1];
			string name = "spotLight[" + to_string((x / 2) + 1) + "].";
			glUniform3f(glGetUniformLocation(lightingShader.Program, (name + "position").c_str()), pos.x, pos.y, pos.z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (name + "direction").c_str()), dir.x, dir.y, dir.z);
			glUniform1f(glGetUniformLocation(lightingShader.Program, (name + "innerCutOff").c_str()), glm::cos(glm::radians(30.0f)));
			glUniform1f(glGetUniformLocation(lightingShader.Program, (name + "outerCutOff").c_str()), glm::cos(glm::radians(50.0f)));
			glUniform1f(glGetUniformLocation(lightingShader.Program, (name + "constant").c_str()), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, (name + "linear").c_str()), 0.009);
			glUniform1f(glGetUniformLocation(lightingShader.Program, (name + "quadratic").c_str()), 0.0032);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (name + "diffuse").c_str()), flicker*0.5f, flicker*0.45f, flicker*0.5f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (name + "ambient").c_str()), flicker*0.02f, flicker*0.05f, flicker*0.02f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, (name + "specular").c_str()), 0.5f, 0.45f, 0.5f);
			glUniform1i(glGetUniformLocation(lightingShader.Program, (name + "torchOn").c_str()), true);
			
		}
		
		// Draw the loaded wood_house
		
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		scene.Draw(lightingShader);
		
		//draw torch on character
		model = glm::mat4();
		model = glm::translate(model, camera.getPos());
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(camera.getYaw()+90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(camera.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-0.1f, 0.2f, 0.0f)); //place near hand
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		flashlight.Draw(lightingShader);

		glBindVertexArray(0);
		glfwSwapBuffers(window); 

	}
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &cubeVBO);
	glfwTerminate(); //cleans up GLFW allocations
	return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){

	//if escape pressed, windowShouldClose = true
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
	if (action == GLFW_PRESS && key  == GLFW_KEY_F)
		torchOn = !torchOn;
	if (action == GLFW_PRESS && key == GLFW_KEY_L){
		std::cout << "\nPOSITION \n --------- \nx: " << camera.getPos().x << "\ny: " << camera.getPos().y << "\nz: " << camera.getPos().z
			<< "\n\nDIRECTION \n --------- \nx: " << camera.getDir().x << "\ny: " << camera.getDir().y << "\nz: " << camera.getDir().z << endl;
	}
}

void do_movement()
{
	
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboardInput(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboardInput(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboardInput(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboardInput(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseInput(xoffset, yoffset, GL_TRUE);
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){

	camera.ProcessScrollInput(yoffset);

}