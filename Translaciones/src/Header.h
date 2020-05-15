#pragma once
#include<cmath>
#include<vector>

#define sz(x) (int)x.size()

/*POINT, SAVE A VERTEX*/
struct pto
{
	float coor[4];
	int n = 4;
};

void PrintPTO(pto p) {
	for (int i = 0; i < p.n; ++i) {
		std::cout << p.coor[i] << ' ';
	}
	std::cout << std::endl;
}

void PrintM(std::vector<std::vector<float>> M) {
	for (int i = 0; i < sz(M); ++i) {
		for (int j = 0; j < sz(M[i]); ++j) {
			std::cout << M[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

/*CLASS MATRIX, BUILD MANY TYPES OF REQUIRED MATRIX*/
class Matrix {
public:
	std::vector<std::vector<float>> onX(float angle) {
		std::vector<std::vector<float>> M(4, std::vector<float>(4, 0));
		M[0][0] = 1;             M[3][3] = 1;
		M[1][1] = cos(angle);    M[1][2] = -sin(angle);
		M[2][2] = cos(angle);    M[2][1] = sin(angle);
		return M;
	}
	std::vector<std::vector<float>> onY(float angle) {
		std::vector<std::vector<float>> M(4, std::vector<float>(4, 0));
		M[0][0] = cos(angle);    M[3][3] = 1;
		M[1][1] = 1;             M[0][2] = sin(angle);
		M[2][2] = cos(angle);    M[2][0] = -sin(angle);
		return M;
	}
	std::vector<std::vector<float>> onZ(float angle) {
		std::vector<std::vector<float>> M(4, std::vector<float>(4, 0));
		M[0][0] = cos(angle);    M[3][3] = 1;
		M[1][1] = cos(angle);    M[0][1] = -sin(angle);
		M[2][2] = 1;             M[1][0] = sin(angle);
		return M;
	}
	std::vector<std::vector<float>> onOr(float angle) {
		std::vector<std::vector<float>> M(3, std::vector<float>(3, 0));
		M[0][0] = cos(angle);    M[2][2] = 1;
		M[1][1] = cos(angle);    M[0][1] = sin(angle);
		M[1][0] = -sin(angle);
		return M;
	}
	/*EXPERIMENTAL*/
	std::vector<std::vector<float>> Tr(pto T) {
		std::vector<std::vector<float>> M(4, std::vector<float>(4, 0));
		M[0][0] = M[1][1] = M[2][2] = M[3][3] = 1;
		M[0][3] = T.coor[0];      M[2][3] = T.coor[2];
		M[1][3] = T.coor[1];      M[3][3] = 1;
	}
	std::vector<std::vector<float>> Sc(pto T) {
		std::vector<std::vector<float>> M(4, std::vector<float>(4, 0));
		M[0][0] = T.coor[0];      M[2][2] = T.coor[2];
		M[1][1] = T.coor[1];      M[3][3] = 1;
	}
};

/*TRIVIAL FUNCTION OF MATRIX MULTIPLICATION*/
pto mul(pto A, std::vector<std::vector<float>> M) {
	pto R{0,0,0,1};
	for (int i = 0; i < sz(M); ++i) {
		float r = 0.0;
		for (int j = 0; j < sz(M[0]); ++j) {
			r += (A.coor[j] * M[i][j]);
		}
		R.coor[i] = r;
	}
	if (sz(M) == 3) {
		R.coor[2] = 0;
	}
	return R;
}

/*CLASS POLIGON, WITH ANY NUMBER OF VERTEXS IN 3D*/
class Poligon {
public:
	std::vector<pto> Points;
	Poligon(int n) :Points(n) {

	}
	void setPoints(float _p[],int tam) {
		int j = 0;
		for (int i = 0; i < tam; i += 3) {
			Points[j] = pto{ _p[i],_p[i + 1],_p[i + 2],1 }; ++j;
		}
	}
	std::vector<float> raw() {
		std::vector<float> R(sz(Points) * 3);
		int j = 0;
		for (int i = 0; i < sz(Points); ++i) {
			R[j] = Points[i].coor[0];
			R[j + 1] = Points[i].coor[1];
			R[j + 2] = Points[i].coor[2];
			j += 3;
		}
		return R;
	}
};

class GLM {
public:
	Matrix Linda;
	/*OPTIMIZACION*/
	pto translation(pto A, pto T) {
		pto R;
		for (int i = 0; i < A.n; ++i) {
			R.coor[i] = A.coor[i] + T.coor[i];
		}
		return R;
	}
	pto scale(pto A, pto S) {
		pto R;
		for (int i = 0; i < A.n; ++i) {
			R.coor[i] = A.coor[i]*S.coor[i];
		}
		return R;
	}
	/*TRIVIAL*/
	pto identity(pto A) {
		return A;
	}
	/*OPERATIONS ON ONE POINT*/
	pto ROnX(pto A, float angle) {
		return mul(A, Linda.onX(angle));
	}
	pto ROnY(pto A, float angle) {
		return mul(A,Linda.onY(angle));
	}
	pto ROnZ(pto A, float angle) {
		return mul(A, Linda.onZ(angle));
	}
	pto ROnOr(pto A, float angle) {
		return mul(A, Linda.onOr(angle));
	}
	/*OPERATION ON ONE POLIGON*/
	void Translate(Poligon &P, pto Tr) {
		for (int i = 0; i < sz(P.Points); ++i) {
			P.Points[i] = translation(P.Points[i], Tr);
		}
	}
	void Escalate(Poligon& P, pto Sc) {
		for (int i = 0; i < sz(P.Points); ++i) {
			P.Points[i] = scale(P.Points[i], Sc);
		}
	}
	void RotateOnX(Poligon& P, float angle) {
		for (int i = 0; i < sz(P.Points); ++i) {
			P.Points[i] = ROnX(P.Points[i], angle);
		}
	}
	void RotateOnY(Poligon& P, float angle) {
		for (int i = 0; i < sz(P.Points); ++i) {
			P.Points[i] = ROnY(P.Points[i], angle);
		}
	}
	void RotateOnZ(Poligon& P, float angle) {
		for (int i = 0; i < sz(P.Points); ++i) {
			P.Points[i] = ROnZ(P.Points[i], angle);
		}
	}
	void RotateOnOr(Poligon& P, float angle) {
		for (int i = 0; i < sz(P.Points); ++i) {
			P.Points[i] = ROnOr(P.Points[i], angle);
		}
	}
};