/*COPYRIGTH ALONSO VALDIVIA 2020 UCSP*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include"Header.h"


#define sz(x) (int)x.size()


float R, G, B;

/*CLASS SHADER, ALLOW ME TO HANDLE CREATION OF MANY SHADER PROGRAMS*/
class Shader {
public:
	std::string VS;
	std::string FS;
	Shader(float _R,float _G,float _B,float _A=1.0) {
		std::string R = std::to_string(_R) + "f";
		std::string G = std::to_string(_G) + "f";
		std::string B = std::to_string(_B) + "f";
		std::string A = std::to_string(_A) + "f";
		VS="#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		FS = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(" + R + ", " + G + ", " + B + ", " + A + ");\n"
			"}\n\0";
	}
	void setShader(float _R, float _G, float _B, float _A = 1.0) {
		std::string R = std::to_string(_R) + "f";
		std::string G = std::to_string(_G) + "f";
		std::string B = std::to_string(_B) + "f";
		std::string A = std::to_string(_A) + "f";
		VS = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";
		FS = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = vec4(" + R + ", " + G + ", " + B + ", " + A + ");\n"
			"}\n\0";
	}
	int createShader() {
		const char* vertexShaderSource = VS.c_str();
		const char* fragmentShaderSource = FS.c_str();
		// build and compile our shader program
	// ------------------------------------
	// vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		// link shaders
		int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return shaderProgram;
	}
};

/*OBSOLET CLASS*/
class Triangle {
public:
	float R;
	float G;
	float B;
	Shader sh;
	int IDSH;
	Triangle():sh(0,0,0){
		R = 0;
		G = 0;
		B = 0;
		IDSH = 0;
	}
	void setShader() {
		glDeleteProgram(IDSH);
		IDSH = sh.createShader();
	}
	void setColor(float r,float g,float b) {
		R = r;
		G = g;
		B = b;
		update();
	}
	void update() {
		sh.setShader(R, G, B);
		setShader();
	}
};

//Triangle T1, T2;
Poligon T(3);
Poligon T2(6);
GLM veronica;
unsigned int TEST,TEST2;

unsigned int SetVao(std::vector<float> coor);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		
	}
}

void processKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_R && (action == GLFW_PRESS || action==GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_G && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_B && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_T && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_H && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		veronica.Translate(T, pto{ .0,0.1,0,1 });
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.Translate(T2, pto{ .0,0.1,0,1 });
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		veronica.Translate(T, pto{ .0,-0.1,0,1 });
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.Translate(T2, pto{ .0,-0.1,0,1 });
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		veronica.Translate(T, pto{ -.1,0.0,0,1 });
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.Translate(T2, pto{ -.1,0.0,0,1 });
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		veronica.Translate(T, pto{ .1,0.0,0,1 });
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.Translate(T2, pto{ .1,0.0,0,1 });
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		veronica.Escalate(T, pto{ 0.8,0.8,0.8,1 });
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.Escalate(T2, pto{ 0.8,0.8,0.8,1 });
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		veronica.Escalate(T, pto{ 1.2,1.2,1.2,1 });
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.Escalate(T2, pto{ 1.2,1.2,1.2,1 });
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		veronica.RotateOnX(T, 0.785398);
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.RotateOnX(T2, 0.785398);
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		veronica.RotateOnY(T, 0.785398);
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.RotateOnY(T2, 0.785398);
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		veronica.RotateOnZ(T, 0.785398);
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.RotateOnZ(T2, 0.785398);
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		veronica.RotateOnOr(T, 0.785398);
		std::vector<float> to_vao = T.raw();
		glDeleteProgram(TEST);
		TEST = SetVao(to_vao);
		veronica.RotateOnOr(T2, 0.785398);
		std::vector<float> to_vao2 = T2.raw();
		glDeleteProgram(TEST2);
		TEST2 = SetVao(to_vao2);
	}
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

std::string Red = "1.0f";

std::string Vtx_T1="#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
std::string Frg_T1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4("+Red+", 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
std::string Vtx_T2;
std::string Frg_T2;

const char* vertexShaderSource = Vtx_T1.c_str();
const char* fragmentShaderSource = Frg_T1.c_str();

/*CREAT A SHADER IN ELEGANT FORM*/
int CreateShader() {
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

/*CREATE A VAO ID IN ELEGANT FORM, ADMITS STD::VECTOR<FLOAT> WHICH ALLOWS IT TO BE DYNAMIC*/
unsigned int SetVao(std::vector<float> coor) {
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sz(coor), &coor[0], GL_STATIC_DRAW);//Basta con cambiar esto para jugar con la figura XD.

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VAO;
}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Create Shader


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float firstTriangle[] = {
		0.75f , -0.5f , 0.0f,  // left 
		0.25f ,  0.5f , 0.0f,  // right
		 0.0f ,  -0.5f , 0.0f  // top 
	};
	T.setPoints(firstTriangle, 9);
	std::vector<float> to_vao = T.raw();
	TEST = SetVao(to_vao);
	int ISH = CreateShader();
	float secondTriangle[] = {
	   -0.7f, -1.0f, 0.0f,  // left
	   -0.7f, -0.5f, 0.0f,  // right
	   -0.2f, -0.5f, 0.0f,
	   -0.7f, -1.0f, 0.0f,  // left
	   -0.2f, -0.5f, 0.0f,  // right
	   -0.2f, -1.0f, 0.0f// top 
	};
	T2.setPoints(secondTriangle,18);
	std::vector<float> to_vao2 = T2.raw();
	TEST2 = SetVao(to_vao2);
	/*
	// first triangle setup
	// --------------------
	// glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
	// second triangle setup
	// ---------------------
	// glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

	//------SECCIÓN DE PRUEBAS---------------------------------------------------
	/*GLM Veronica;
	pto F{ -0.1, 0.0,0.0,1 };
	pto S{ 0.0,0.1,0.0,1 };
	pto T{ .1,0.0,0.0,1 };*/
	//##########TRANSLATION#########PRUEBA EXITOSA!!!
	/*pto Tr{ 0.1,.1,0.0 };
	F = Veronica.translation(F, Tr);
	S = Veronica.translation(S, Tr);
	T = Veronica.translation(T, Tr);*/
	//##########SCALA################PRUEBA EXITOSA!!!
	/*pto Sc{ 2,3,1 };
	F = Veronica.scale(F, Sc);
	S = Veronica.scale(S, Sc);
	T = Veronica.scale(T, Sc);*/
	//##########ROTATE ON X#########PRUEBA PENDIENTE 80% EXITOSA!!!
	/*F = Veronica.ROnX(F, 10);
	S = Veronica.ROnX(S, 10);
	T = Veronica.ROnX(T, 10);*/
	//++++++++VARIABLE'S PRINT+++++++++++++++++++
	/*std::cout << F.coor[0] << ' ' << F.coor[1] << ' ' << F.coor[2] << ' ' << F.coor[3] << std::endl;
	std::cout << S.coor[0] << ' ' << S.coor[1] << ' ' << S.coor[2] << ' ' << S.coor[3] << std::endl;
	std::cout << T.coor[0] << ' ' << T.coor[1] << ' ' << T.coor[2] << ' ' << T.coor[3] << std::endl;*/
	//****************************************************************************
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::cout << "CONTROLOES" << std::endl;
	std::cout << "R = Rotacion en el origen (45°)" << std::endl;
	std::cout << "X = Rotacion en el eje X  (45°)" << std::endl;
	std::cout << "Y = Rotacion en el eje Y  (45°)" << std::endl;
	std::cout << "Z = Rotacion en el eje Z  (45°)" << std::endl;
	std::cout << "N = Escala que maximiza   (+20%)" << std::endl;
	std::cout << "M = Escala que minimiza   (-20%)" << std::endl;
	std::cout << "UP,DOWN,LEFT,RIGHT = Translacion en la dirección de la flecha (+/- 0.1)" << std::endl;
	//Deje esto apropósito para que vea el mensaje de arriba, solo borrelo y verá que todo compila
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		glfwSetKeyCallback(window, processKey);
		//std::cout<<nave.vertices[0];
		// render
		// ------
		glUseProgram(ISH);
		glBindVertexArray(TEST);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(TEST2);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// draw the first triangle using the data from our first VAO
	// this call should output an orange triangle
		// then we draw the second triangle using the data from the second VAO
		// when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
		// this call should output a yellow triangle
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1,&TEST);
	glDeleteProgram(ISH);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}