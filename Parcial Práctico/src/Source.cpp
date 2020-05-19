/*COPYRIGTH ALONSO VALDIVIA 2020 UCSP*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include<vector>
#include <stdlib.h>
#include<string>
#include<algorithm>
#include<utility>
#include<iomanip>
#include<Windows.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono> 
#include<stdio.h>
#include<map>
#include"Header.h"


#define sz(x) (int)x.size()


float R, G, B;

std::vector<std::vector<float>> MambaNegra;
int NrOp = 0;
std::vector<std::string> Titles(16);

int TIME = 100;

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
	void ModeUniform(std::string Variable) {
		VS = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos, 1.0);\n"
			"}\0";
		FS = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"uniform vec4 "+Variable+";\n"
			"void main()\n"
			"{\n"
			"   FragColor = "+Variable+";\n"
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
bool stop;
Poligon T(3);
Poligon T2(6); pto F{ .4,.0,.0,1 };
Poligon T3(6);
std::vector<Poligon> Por_el_veinte;
std::vector<int> VAOS;
std::map<int,char> Config;
std::vector<int> COLOR;
std::vector<int> ConfigMove;
std::vector<std::pair<int,int>> Vars_to_Trans;
float gX, gY;
GLM veronica;
unsigned int TEST,TEST2,TEST3;

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
		Config[1] = 'R';
	}
	if (key == GLFW_KEY_G && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_B && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
	}
	if (key == GLFW_KEY_T && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		Config[1] = 'T';
	}
	if (key == GLFW_KEY_M && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		TIME += 100;
	}
	if (key == GLFW_KEY_N && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		TIME -= 100;
		if (TIME < 0)TIME = 0;
	}
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		Config[1] = 'D';
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		
	}
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		Config[3] = 'G';
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		Config[3] = 'B';
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		Config[3] = 'R';
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		std::cout << "Tu configuracion actual, Llena todos los campos para que funcione" << std::endl;
		std::cout << "FIGURA = " << Config[1] << ' ' << "MOVIMIENTO = " << Config[2] << ' ' << "COLOR = " << Config[3] << std::endl;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		stop = (stop + 1) % 2;
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		Config[2] = 'S';
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		Config[2] = 'R';
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		Config[2] = 'T';
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
    "   gl_Position = vec4(aPos, 1.0);\n"
	"}\0";
std::string Frg_T1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
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

void Scale(int i) {
	if (i) {
		veronica.Escalate(T, pto{ 0.8,0.8,0.8,1 });
		//std::cout << "i" << std::endl;
	}
	else {
		veronica.Escalate(T, pto{ 1.25,1.25,1.25,1 });
		//std::cout << "d" << std::endl;
	}
	std::vector<float> to_vao = T.raw();
	glDeleteProgram(TEST);
	TEST = SetVao(to_vao);
}

void Scale(Poligon &TT, int &My_vao,int i) {
	if (i) {
		veronica.Escalate(TT, pto{ 0.8,0.8,0.8,1 });
		//std::cout << "i" << std::endl;
	}
	else {
		veronica.Escalate(TT, pto{ 1.25,1.25,1.25,1 });
		//std::cout << "d" << std::endl;
	}
	std::vector<float> to_vao = TT.raw();
	glDeleteProgram(My_vao);
	My_vao = SetVao(to_vao);
}

 

void Rotate() {
	F = veronica.ROnOr(F, to_rad(20));
	float Tri[] = {
			F.coor[0] - 0.1 , F.coor[1] - 0.1 , 0.0f,  // left 
			F.coor[0] - 0.1 ,  F.coor[1] + 0.1 , 0.0f,  // right
			F.coor[0] + 0.1 ,  F.coor[1] + 0.1 , 0.0f,
			F.coor[0] + 0.1 , F.coor[1] + 0.1 , 0.0f,  // left 
			F.coor[0] + 0.1 ,  F.coor[1] - 0.1 , 0.0f,  // right
			F.coor[0] - 0.1 ,  F.coor[1] - 0.1 , 0.0f// top 
	};
	T2.setPoints(Tri, 18);
	std::vector<float> to_vao = T2.raw();
	glDeleteProgram(TEST2);
	TEST2 = SetVao(to_vao);
}

void Rotate(Poligon &TT, int &My_vao) {
	veronica.RotateOnOr(TT, to_rad(20));
	std::vector<float> to_vao = TT.raw();
	glDeleteProgram(My_vao);
	My_vao = SetVao(to_vao);
}

pto trans_buffer[4] = {
	pto{ 0.1,0.0,0,0.0 },
	pto{ 0.0,0.1,0.0,0 },
	pto{ -0.1,0.0,0,00 },  
	pto{ 0.0,-0.1,0,00 }
};

void Translate(int &i,int &coor) {
	veronica.Translate(T3, trans_buffer[i]);
	//std::cout << coor << std::endl;
	std::vector<float> to_vao = T3.raw();
	glDeleteProgram(TEST3);
	TEST3 = SetVao(to_vao);
	for (int j = 0; j < sz(T3.Points); ++j) {
		if (abs(T3.Points[j].coor[coor]) >= 0.9) {i = (i + 1) % 4; coor = (coor + 1) % 2; return; }
	}
}

void Translate(Poligon &TT, int &My_vao, int& i, int& coor) {
	veronica.Translate(TT, trans_buffer[i]);
	//std::cout << coor << std::endl;
	std::vector<float> to_vao = TT.raw();
	glDeleteProgram(My_vao);
	My_vao = SetVao(to_vao);
	for (int j = 0; j < sz(TT.Points); ++j) {
		if (abs(TT.Points[j].coor[coor]) >= 0.9) { i = (i + 1) % 4; coor = (coor + 1) % 2; return; }
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos = 0; double ypos = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		glfwGetCursorPos(window, &xpos, &ypos);
		gX = (xpos * 0.0025) - (400 * 0.0025);
		gY = 2.0 / 600.0 * (600 - ypos - 300);
		
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		gX = (xpos * 0.0025) - (400 * 0.0025);
		gY = 2.0 / 600.0 * (600 - ypos - 300);
		//std::cout << "PRESS" << std::endl;
		if (Config[1] == 'T') {
			Por_el_veinte.push_back(Poligon(3));
			float Tri[] = {
			gX-0.1 , gY-0.1 , 0.0f,  // left 
			gX ,  gY+0.1 , 0.0f,  // right
			gX+0.1 ,  gY-0.1 , 0.0f  // top 
			};
			Por_el_veinte[sz(Por_el_veinte) - 1].setPoints(Tri, 9);
			std::vector<float> to_vao = Por_el_veinte[sz(Por_el_veinte) - 1].raw();
			VAOS.push_back(0);
			VAOS[sz(VAOS) - 1] = SetVao(to_vao);
		}
		else if (Config[1] == 'R') {
			Por_el_veinte.push_back(Poligon(6));
			float Tri[] = {
			gX-0.1 , gY-0.1 , 0.0f,  // left 
			gX-0.1 ,  gY+0.1 , 0.0f,  // right
			gX+0.1 ,  gY+0.1 , 0.0f,
			gX+0.1 , gY+0.1 , 0.0f,  // left 
			gX+0.1 ,  gY-0.1 , 0.0f,  // right
			gX-0.1 ,  gY-0.1 , 0.0f// top 
			};
			Por_el_veinte[sz(Por_el_veinte) - 1].setPoints(Tri, 18);
			std::vector<float> to_vao = Por_el_veinte[sz(Por_el_veinte) - 1].raw();
			VAOS.push_back(0);
			VAOS[sz(VAOS) - 1] = SetVao(to_vao);
		}
		else if (Config[1] == 'D') {
			Por_el_veinte.push_back(Poligon(6));
			float Tri[] = {
			gX - 0.1 , gY, 0.0f,  // left 
			gX ,  gY + 0.1 , 0.0f,  // right
			gX + 0.1 ,  gY , 0.0f,
			gX + 0.1 , gY , 0.0f,  // left 
			gX ,  gY - 0.1 , 0.0f,  // right
			gX - 0.1 ,  gY , 0.0f// top 
			};
			Por_el_veinte[sz(Por_el_veinte) - 1].setPoints(Tri, 18);
			std::vector<float> to_vao = Por_el_veinte[sz(Por_el_veinte) - 1].raw();
			VAOS.push_back(0);
			VAOS[sz(VAOS) - 1] = SetVao(to_vao);
		}
		if (Config[2] == 'T') {
			ConfigMove.push_back(3);
			Vars_to_Trans.push_back({ 0,0 });
			//std::cout << "T" << std::endl;
		}
		else if (Config[2] == 'S') {
			ConfigMove.push_back(1);
		}
		else if (Config[2] == 'R') {
			ConfigMove.push_back(2);
		}
		if (Config[3] == 'R') {
			COLOR.push_back(1);
		}
		else if (Config[3] == 'G') {
			COLOR.push_back(2);
		}
		else if (Config[3] == 'B') {
			COLOR.push_back(3);
		}
	}
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
	Config[2] = 'N';
	Config[1] = 'N';
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
	Shader Sh(0,0,0);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float firstTriangle[] = {
		0.0f , 0.1f , 0.0f,  // left 
		0.1f ,  -0.1f , 0.0f,  // right
		 -0.1f ,  -0.1f , 0.0f  // top 
	};
	T.setPoints(firstTriangle, 9);
	std::vector<float> to_vao = T.raw();
	TEST = SetVao(to_vao);
	int ISH = Sh.createShader();
	int ISH2 = Sh.createShader();
	int ISH3 = Sh.createShader();
	float secondTriangle[] = {
	    0.3f,  0.1f, 0.0f,  // left
	    0.5f,  0.1f, 0.0f,  // right
	    0.5f, -0.1f, 0.0f,
	    0.5f, -0.1f, 0.0f,  // left
	    0.3f, -0.1f, 0.0f,  // right
	    0.3f,  0.1f, 0.0f// top 
	};
	T2.setPoints(secondTriangle,18);
	std::vector<float> to_vao2 = T2.raw();
	TEST2 = SetVao(to_vao2);
	float thirdTriangle[] = {
		0.7f,  0.0f, 0.0f,  // left
		0.8f,  0.1f, 0.0f,  // right
		0.9f,  0.0f, 0.0f,
		0.9f,  0.0f, 0.0f,  // left
		0.8f, -0.1f, 0.0f,  // right
		0.7f,  0.0f, 0.0f// top 
	};
	T3.setPoints(thirdTriangle, 18);
	std::vector<float> to_vao3 = T3.raw();
	TEST3 = SetVao(to_vao3);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Deje esto apropósito para que vea el mensaje de arriba, solo borrelo y verá que todo compila
	stop = false;
	int si = 0;
	int ti = 0;
	int ti2 = 0;
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
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		//std::cout<<nave.vertices[0];
		float timeValue = glfwGetTime();
		float redValue = sin(timeValue) / 2.0f + 0.5f;
		glDeleteProgram(ISH);
		Sh.setShader(redValue, 0, 0);
		ISH = Sh.createShader();
		glUseProgram(ISH);
		glBindVertexArray(TEST);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		glDeleteProgram(ISH2);
		Sh.setShader(0, greenValue, 0);
		ISH2 = Sh.createShader();
		glUseProgram(ISH2);
		glBindVertexArray(TEST2);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		timeValue = glfwGetTime();
		float blueValue = sin(timeValue) / 2.0f + 0.5f;
		glDeleteProgram(ISH3);
		Sh.setShader(0, 0, blueValue);
		ISH3 = Sh.createShader();
		glUseProgram(ISH3);
		glBindVertexArray(TEST3);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		for (int iii = 0; iii < sz(VAOS); ++iii) {
			if (COLOR[iii] == 1)glUseProgram(ISH);
			else if (COLOR[iii] == 2)glUseProgram(ISH2);
			else if (COLOR[iii] == 3)glUseProgram(ISH3);
			glBindVertexArray(VAOS[iii]);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		// then we draw the second triangle using the data from the second VAO
		// when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
		// this call should output a yellow triangle
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		if (!stop) {
			Scale(si);
			si = (si + 1) % 2;
			Rotate();
			Translate(ti, ti2);
			int TEST22 = TEST2;
			Scale(T2, TEST22, si);
			TEST22 = TEST3;
			Scale(T3, TEST22, si);
			int iiii = 0;
			//std::cout << sz(Vars_to_Trans) << std::endl;
			for (int iii = 0; iii < sz(ConfigMove); ++iii) {
				if (ConfigMove[iii] == 2)Rotate(Por_el_veinte[iii], VAOS[iii]);
				else if (ConfigMove[iii] == 1)Scale(Por_el_veinte[iii], VAOS[iii], si);
				else if (ConfigMove[iii] == 3){Translate(Por_el_veinte[iii], VAOS[iii], Vars_to_Trans[iiii].first, Vars_to_Trans[iiii].second); iiii++;}
			}
		}
		// -------------------------------------------------------------------------------
		std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
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