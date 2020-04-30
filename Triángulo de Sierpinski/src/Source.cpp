#include"Header.h"
#include<iostream>
#include<algorithm>
#include<vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Sierpinski *T;

#define MAX_LEVEL 5

int level;
int wire;
int wire_Pointer;
float gX, gY;
unsigned int Pointer = 0;
bool init = false;



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window)
{

}

void processKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS)) {
		level += 1;
		if (level >= MAX_LEVEL)level = MAX_LEVEL+1;
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS)) {
		level -= 1;
		if (level <= -1)level = -1;
	}
	if (key == GLFW_KEY_W && (action == GLFW_PRESS)) {
		wire = (wire + 1) % 2;
	}
	if (key == GLFW_KEY_S && (action == GLFW_PRESS)) {
		wire_Pointer = (wire_Pointer + 1) % 2;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	gX = xpos;
	gY = ypos;
}

unsigned int SetVao(std::vector<float> coor) {
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sz(coor), &coor[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VAO;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos = 0; double ypos = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		glfwGetCursorPos(window, &xpos, &ypos);
		gX = (xpos*0.0025)-(400*0.0025);
		gY = 2.0/600.0*(600-ypos-300);
		std::vector<float> coor;
		if (T->search(T->I, pto{ gX,gY },coor)) {
			Pointer = SetVao(coor);
			init = true;
		}
		else {
			std::cout << "No hallado" << std::endl;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		init = (init + 1) % 2;
	}
}



int main()
{
	level = MAX_LEVEL;
	T = new Sierpinski();
	T->I = new Triangle(pto{-1.0,-1.0}, pto{0.0,1.0}, pto{1.0,-1.0});
	T->AutoDiv(T->I,level);
	level = MAX_LEVEL + 1;
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	Shader S(0, 0,0);
	S.setShader(99.608/100, 78.431 /100, 84.706/100);

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
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,// second Triangle
		3, 4, 5,
		6,7,8,
		9,10,11
	};
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	std::vector<float> ver = T->VAO;
	std::cout << sz(ver);
	std::cout << sz(ver);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sz(ver), &ver[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

/*PROFESOR_____NOTA*/
	/*
		TRIANGULO 1, SE CONTROLA CON R,G,B.
		TRIANGULO 2, SE CONTROLA CON T,H,N.
		SI PRESIONA CUALQUIERA DE LAS TECLAS MÁS C(cancel) EL COLOR SE BORRARÁ
		EJEMPLO SI PRESIONA R+C, EL COLOR ROJO DEL TRIÁNGULO 1 SE BORRARÁ
				SI PRESIONA N+C, EL COLOR AZUL DEL TRIÁNGULO 2 SE BORRARÁ

	*/
	// render loop
	// -----------
	std::vector<int> IDSH_por_level(level+1);
	float R = 0, G = 0, B = 0;
	for (int i = 0; i < sz(IDSH_por_level); ++i) {

		S.setShader(R, G, B);
		IDSH_por_level[i] = S.createShader();
		G += 0.1;
	}
	int IDSH[3];
	IDSH[0] = S.createShader(); S.setShader(46.667/100, 86.681/100, 87.451/100);//azul
	IDSH[1] = S.createShader(); S.setShader(0, 0, 0);//rojo
	IDSH[2] = S.createShader();// S.setShader(0, 0, 1);//verde
	S.setShader(46.667 / 100, 86.681 / 100, 87.451 / 100, 0.3);
	int IDSH_Pointer = S.createShader();
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
		// render
		// ------
		
		 // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glBindVertexArray(VAO); 
		int j = 0;
		if (wire)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		for (int i = 0; i <= level; ++i) {
			glUseProgram(IDSH_por_level[i]);
			glDrawArrays(GL_TRIANGLES, j, pow(3,i)*3);
			
			j = j+(pow(3, i) * 3);
		}
		if (init) {
			if(wire_Pointer)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(Pointer);
			glUseProgram(IDSH_Pointer);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &Pointer);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

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
