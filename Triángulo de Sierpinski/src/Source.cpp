#include"Header.h"
#include<iostream>
#include<algorithm>
#include<vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Sierpinski *T;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window)
{
	
}

void processKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	int level = 4;
	T = new Sierpinski();
	T->I = new Triangle(pto{-1.0,-1.0}, pto{0.0,1.0}, pto{1.0,-1.0});
	T->AutoDiv(T->I,level);
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
	//glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
	std::vector<float> ver = T->VAO;
	/*for (int i = 0; i < sz(ver); i+=3) {
		std::cout << ver[i] << ' ' << ver[i + 1] << ' ' << ver[i + 2] << std::endl;
	}*/
	
	
	//float vertices[1024];
	std::cout << sz(ver);
	//std::reverse(ver.begin(), ver.end());
	//std::copy(ver.begin(), ver.end(), vertices);
	std::cout << sz(ver);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*sz(ver), &ver[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call 

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

/*PROFESOR_____NOTA*/
	/*
		TRIANGULO 1, SE CONTROLA CON R,G,B.
		TRIANGULO 2, SE CONTROLA CON T,H,N.
		SI PRESIONA CUALQUIERA DE LAS TECLAS M�S C(cancel) EL COLOR SE BORRAR�
		EJEMPLO SI PRESIONA R+C, EL COLOR ROJO DEL TRI�NGULO 1 SE BORRAR�
				SI PRESIONA N+C, EL COLOR AZUL DEL TRI�NGULO 2 SE BORRAR�

	*/
	//Deje esto aprop�sito para que vea el mensaje de arriba, solo borrelo y ver� que todo compila
	// render loop
	// -----------
	std::vector<int> IDSH_por_level(level+1);
	float R = 0, G = 0, B = 0;
	for (int i = 0; i < level+1; ++i) {

		S.setShader(R, G, B);
		IDSH_por_level[i] = S.createShader();
		G += 0.1;
	}
	int IDSH[3];
	IDSH[0] = S.createShader(); S.setShader(46.667/100, 86.681/100, 87.451/100);//azul
	IDSH[1] = S.createShader(); S.setShader(0, 0, 0);//rojo
	IDSH[2] = S.createShader();// S.setShader(0, 0, 1);//verde
	int color = 0;
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
		
		 // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glBindVertexArray(VAO); 
		int j = 0;
		color = 0;
		int click = 0;
		for (int i = 0; i <= level; ++i) {
			//std::cout << j << ' ' << pow(3, i) * 3 << std::endl;
			glUseProgram(IDSH_por_level[i]);
			if(click)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//click = (click + 1) % 2;
			glDrawArrays(GL_TRIANGLES, j, j+pow(3,i)*3);
			
			j = j+(pow(3, i) * 3);
			color = (color + 1) % 3;
		}
		
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
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
