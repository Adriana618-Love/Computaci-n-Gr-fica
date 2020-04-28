#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<queue>
#include<list>

#define sz(x) (int)x.size()
#define forn(i,n) for(int i=0;i<n;++i)

struct pto
{
	float x;
	float y;
};

pto Middle(pto p1, pto p2) {
	return pto{ (p1.x + p2.x) / 2,(p1.y + p2.y) / 2 };
}

bool inPolygon(pto v, std::vector<pto>& P) {
	bool c = false;
	forn(i, sz(P)) {
		int j = (i + 1) % sz(P);
		if ((P[j].y > v.y) != (P[i].y > v.y) &&
			(v.x < (P[i].x - P[j].x) * (v.y - P[j].y) / (P[i].y - P[j].y) + P[j].x))
			c = !c;
	}
	return c;
}

class Shader {
public:
	std::string VS;
	std::string FS;
	Shader(float _R, float _G, float _B, float _A = 1.0) {
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
			"uniform vec4 ourColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = outColor;\n"
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
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		return shaderProgram;
	}
};

class Color {
public:
	float R;
	float G;
	float B;
	//Shader sh;
	//int IDSH;
	Color() {
		R = 0;
		G = 0;
		B = 0;
		//IDSH = 0;
	}
	void setShader() {
	}
	void setColor(float r, float g, float b) {
		R = r;
		G = g;
		B = b;
	}
	void update() {
	}
};

class Vao {
public:
	std::vector<double> vertices;
	Vao(): vertices(){
	}
	void setVao(std::vector<pto> pts) {
		INIT(pts);
	}
	GLuint getVao() {
		return VAO;
	}
private:
	GLuint VAO;
	void INIT(std::vector<pto> &pts) {
		GLuint VBO;
		GLuint V;
		for (int i = 0; i < sz(pts); ++i) {
			vertices.push_back(pts[i].x);
			vertices.push_back(pts[i].y);
			vertices.push_back(0.0f);
		}
		glGenVertexArrays(1, &V); // we can also generate multiple VAOs or buffers at the same time
		glGenBuffers(1, &VBO);
		// first triangle setup
		// --------------------
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(0);
	}
};

class Triangle {
public:
	std::vector<pto> coor;
	Color C;
	//Vao *V;
	std::vector<Triangle*> childrens;
	Triangle() :coor(3), childrens(3) {
	}
	Triangle(pto one, pto two, pto three) : coor{ one,two,three }, childrens(3){
		//V = new Vao();
		//V->setVao(coor);
	}
	std::vector<pto> getCoor() { return coor; }
	void draw() {
		//glUseProgram(C.IDSH);
		//glBindVertexArray(V->getVao());
		//glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	std::vector<float> getVao() {
		std::vector<float> points;
		for (int i = 0; i < sz(coor); ++i) {
			points.push_back(coor[i].x);
			points.push_back(coor[i].y);
			points.push_back(0.0);
		}
		return points;
	}
	~Triangle() {
		//glDeleteVertexArrays(1, &(V->getVao()));
		
	}
};

class Sierpinski {
public:
	Triangle* I;
	std::vector<float> VAO;
	Sierpinski() {
		I = nullptr;
	}
	void insert(pto p) {
		Triangle* P = I;
		if (!search(P, p))return;
		Div(P);
	}

	void AutoDiv(Triangle *& P,int lr) {
		std::list<Triangle*> Q;/*
		std::vector<float> points = P->getVao();
		for (int i = 0; i < sz(points); ++i) {
			VAO.push_back(points[i]);
		}
		if (lvl < lr) {
			P->childrens[0] = new Triangle(P->getCoor()[0], Middle(P->getCoor()[0], P->getCoor()[1]), Middle(P->getCoor()[0], P->getCoor()[2]));
			P->childrens[1] = new Triangle(Middle(P->getCoor()[0], P->getCoor()[1]), P->getCoor()[1], Middle(P->getCoor()[1], P->getCoor()[2]));
			P->childrens[2] = new Triangle(Middle(P->getCoor()[0], P->getCoor()[2]), Middle(P->getCoor()[1], P->getCoor()[2]), P->getCoor()[2]);
			P->childrens[0]->C.setColor(P->C.R, P->C.G, P->C.B);
			P->childrens[1]->C.setColor(P->C.R, P->C.G, P->C.B);
			P->childrens[2]->C.setColor(P->C.R, P->C.G, P->C.B);
			for (int i = 0; i < 3; ++i) {
				AutoDiv(P->childrens[i],lr, lvl + 1);
			}
		}*/
		int lvl = 0;
		Q.push_back(P);
		int li = 0;
		for (int i = 0; i <= lr; ++i) {
			li += (pow(3, i));
		}
		//std::cout << li << std::endl;
		while (lvl < li) {
			P = Q.front();
			Q.pop_front();
			std::vector<float> points = P->getVao();
			for (int i = 0; i < sz(points); ++i) {
				VAO.push_back(points[i]);
			}
			P->childrens[0] = new Triangle(P->getCoor()[0], Middle(P->getCoor()[0], P->getCoor()[1]), Middle(P->getCoor()[0], P->getCoor()[2]));
			P->childrens[1] = new Triangle(Middle(P->getCoor()[0], P->getCoor()[1]), P->getCoor()[1], Middle(P->getCoor()[1], P->getCoor()[2]));
			P->childrens[2] = new Triangle(Middle(P->getCoor()[0], P->getCoor()[2]), Middle(P->getCoor()[1], P->getCoor()[2]), P->getCoor()[2]);
			P->childrens[0]->C.setColor(P->C.R, P->C.G, P->C.B);
			P->childrens[1]->C.setColor(P->C.R, P->C.G, P->C.B);
			P->childrens[2]->C.setColor(P->C.R, P->C.G, P->C.B);
			Q.push_back(P->childrens[0]);
			Q.push_back(P->childrens[1]);
			Q.push_back(P->childrens[2]);
			++lvl;
		}
	}

	void Div(Triangle*& P) {
		P->childrens[0] = new Triangle(P->getCoor()[0], Middle(P->getCoor()[0], P->getCoor()[1]), Middle(P->getCoor()[0], P->getCoor()[2]));
		P->childrens[1] = new Triangle(Middle(P->getCoor()[0], P->getCoor()[1]), P->getCoor()[1], Middle(P->getCoor()[1], P->getCoor()[2]));
		P->childrens[2] = new Triangle(Middle(P->getCoor()[0], P->getCoor()[1]), Middle(P->getCoor()[1], P->getCoor()[2]), P->getCoor()[2]);
		P->childrens[0]->C.setColor(P->C.R, P->C.G, P->C.B);
		P->childrens[1]->C.setColor(P->C.R, P->C.G, P->C.B);
		P->childrens[2]->C.setColor(P->C.R, P->C.G, P->C.B);
	}

	int search(Triangle*& P, pto p) {
		while (P) {
			if (inPolygon(p, P->coor)) {
				P = P->childrens[0];
			}
			else if (inPolygon(p, P->coor)) {
				P = P->childrens[1];
			}
			else if (inPolygon(p, P->coor)) {
				P = P->childrens[2];
			}
			else if (inPolygon(p, P->coor)) {
				//iluminar();
				return false;
			}
			else {
				return false;
			}
		}
		return true;
	}

	void qDraw(Triangle * &P) {
		if (P->childrens[0]) {
			qDraw(P->childrens[0]);
			qDraw(P->childrens[1]);
			qDraw(P->childrens[2]);
		}
		P->draw();
	}

	void Draw() {
		Triangle* P = I;
		qDraw(P);
	}
};
