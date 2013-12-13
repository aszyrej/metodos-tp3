#include "../inc/Matrix.h"
#include <cmath>


using namespace std;

Matrix::Matrix(vector<double>& y1, vector<double>& y2){
	filas = (int) y1.size();
	columnas = 2;
	vector<double> v;
	for(int i = 0; i<filas; i++){
		A.push_back(v);
		A[i].push_back(y1[i]);
		A[i].push_back(y2[i]);
	}
}

Matrix::Matrix(vector<double>& y1){
	filas = (int) y1.size();
	columnas = 1;
	vector<double> v;
	for(int i = 0; i<filas; i++){
		A.push_back(v);
		A[i].push_back(y1[i]);
	}
}

Matrix::Matrix(istream& is){
	double elem;
	is >> filas;
	is >> columnas;
	
	vector<double> fila;
	for(int i = 0; i < columnas; i++){
		fila.push_back(0.0);
	}

	for(int i = 0; i < filas; i++){
		A.push_back(fila);
	}

	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++){
			is >> elem;
			this->A[i][j] = elem;
		}
	}
}

Matrix::Matrix(int n){
	filas = n;
	columnas = filas;
	vector<double> v;
	for(int i = 0; i < n; i++){
		v.push_back(0.0);
	}

	for(int i = 0; i < n; i++){
		A.push_back(v);
	}
	
	for(int i = 0; i < n; i++){
		A[i][i] = 1.0;
	}
	
}

Matrix::Matrix(const Matrix& m){
	filas = m.filas;
	columnas = m.columnas;

	for(int i = 0; i < filas; i++){
		A.push_back(m.A[i]);
	}
}

Matrix::Matrix(int n, int m){
	filas = n;
	columnas = m;
	vector<double> fila;
	for(int i = 0; i < columnas; i++){
		fila.push_back(0.0);
	}

	for(int i = 0; i < filas; i++){
		A.push_back(fila);
	}

}

double Matrix::elem(int i, int j){
	return A[i][j];
}

Matrix Matrix::productoMatrices(Matrix& m1, Matrix& m2){
	Matrix res = Matrix(m1.filas, m2.columnas);
	double acum;
	for(int i = 0; i < res.filas; i++){
		for(int j = 0; j < res.columnas; j++){	
			acum = 0;
			for( int k = 0; k < m1.columnas; k++){
				acum = acum + m1.elem(i,k) * m2.elem(k,j);
			}
			res.A[i][j] = acum;
		}
	}
	return res;
}

Matrix Matrix::productoMatrices(Matrix& m1){
	Matrix res = Matrix(m1.filas, this->columnas);
	double acum;
	for(int i = 0; i < res.filas; i++){
		for(int j = 0; j < res.columnas; j++){	
			acum = 0;
			for( int k = 0; k < m1.columnas; k++){
				acum = acum + m1.elem(i,k) * this->elem(k,j);
			}
			res.A[i][j] = acum;
		}
	}
	return res;
}

Matrix Matrix::multiplicarXescalar(Matrix& m1, double escalar){
	Matrix res = Matrix(m1);
	for(int i = 0; i < res.filas; i++){
		for(int j = 0; j < res.columnas; j++){
			res.A[i][j] = res.A[i][j] * escalar;
		}	
	}
	return res;
}
//calcula la norma dos de una "matriz" de n filas y 1 columna como si fuera un vector.
double Matrix::norma_dos(){
	double res = 0;
	for(int i = 0; i<filas ; i++){
		res = res + (A[i][0] * A[i][0]);
	}
	res = sqrt(res);
	return res;
}

Matrix Matrix::restaMatrices(Matrix& m1, Matrix& m2){
	Matrix res = Matrix(m1);
	for(int i = 0; i < res.filas; i++){
		for(int j = 0; j < res.columnas; j++){
			res.A[i][j] = m1.A[i][j] - m2.A[i][j];
		}	
	}
	return res;	
}

Matrix Matrix::restaMatrices(Matrix& m1){
	Matrix res = Matrix(m1);
	for(int i = 0; i < res.filas; i++){
		for(int j = 0; j < res.columnas; j++){
			res.A[i][j] = this->A[i][j] - m1.A[i][j];
		}	
	}
	return res;	
}

pair<Matrix*,Matrix*> Matrix::factorizarQR(){
	pair<Matrix*,Matrix*> res;
	
	Matrix u = Matrix(filas,1);
	Matrix u_t = Matrix(1,filas);
	
	for(int i = 0; i < filas; i++){
		u.A[i][0] = this->A[i][0];
	}
	u.A[0][0] = u.A[0][0] - u.norma_dos();
	u = multiplicarXescalar(u,1.0/u.norma_dos());
	
	for(int i = 0; i < filas; i++){
		u_t.A[0][i] = u.A[i][0];
	}
	
	Matrix uu_t = productoMatrices(u,u_t);
	uu_t = multiplicarXescalar(uu_t,2); //2uu_t
	Matrix Q1 = Matrix(filas); //I^nxn
	Q1 = restaMatrices(Q1,uu_t);
	
	Matrix R = productoMatrices(Q1);			//Q1 * this  -> Q1 * A
	
	///fin primer paso
	
	u.A[0][0] = 0;
	
	for(int i = 1; i < filas; i++){
		u.A[i][0] = R.A[i][1];
		//u_t.A[0][i] = this->A[i][1];
	}
	
	u.A[1][0] = u.A[1][0] - u.norma_dos();
	u = multiplicarXescalar(u,1.0/u.norma_dos());
	
	for(int i = 0; i < filas; i++){
		u_t.A[0][i] = u.A[i][0];
	}
	
	uu_t = productoMatrices(u,u_t);
	//uu_t.mostrar(cout);
	uu_t = multiplicarXescalar(uu_t,2); //2uu_t
	Matrix Q2 = Matrix(filas); //I^nxn
	Q2 = restaMatrices(Q2,uu_t);
	
	R = productoMatrices(Q2,R);
	
	///fin segundo paso
	
	Matrix Q_t = productoMatrices(Q2,Q1);
	
	Matrix* R_res = new Matrix(R);
	Matrix* Qt_res = new Matrix(Q_t);
	res = make_pair(Qt_res, R_res);
	
	return res;
}

pair<Matrix*,Matrix*> Matrix::factorizarQRopt(vector<double>& y_k){ //recibe menos y_k
	pair<Matrix*,Matrix*> res; //quiero devolver Qt_por_menos_y_k y R
	
	Matrix u = Matrix(filas,1);
	Matrix u_t = Matrix(1,filas);
	
	for(int i = 0; i < filas; i++){
		u.A[i][0] = this->A[i][0];
	}
	u.A[0][0] = u.A[0][0] - u.norma_dos();
	u = multiplicarXescalar(u,1.0/u.norma_dos());
	
	for(int i = 0; i < filas; i++){
		u_t.A[0][i] = u.A[i][0];
	}
	//tenemos y_k, u y u_t
	Matrix Y_k = Matrix(y_k);
	
	//b'
	Matrix u_t_Y_k = productoMatrices(u_t,Y_k); //u_t_por_Y_k
	u_t_Y_k = productoMatrices(u,u_t_Y_k); //u_u_t_por_Y_k
	u_t_Y_k = multiplicarXescalar(u_t_Y_k,2);
	u_t_Y_k = restaMatrices(Y_k,u_t_Y_k);
	///b' = u_t_Y_k
	//R1:
	Matrix u_t_por_A = productoMatrices(u_t);
	u_t_por_A = productoMatrices(u,u_t_por_A); //u_u_t_por_A
	u_t_por_A = multiplicarXescalar(u_t_por_A,2); //2u_u_t_por_A
	u_t_por_A = restaMatrices(u_t_por_A); 
	///R1 = u_t_por_A
	
	
	
	//~ Matrix uu_t = productoMatrices(u,u_t);
	//~ uu_t = multiplicarXescalar(uu_t,2); //2uu_t
	//~ Matrix Q1 = Matrix(filas); //I^nxn
	//~ Q1 = restaMatrices(Q1,uu_t);
	//~ 
	//~ Matrix R = productoMatrices(Q1);			//Q1 * this  -> Q1 * A
	
	
	
	
	///fin primer paso
	
	u.A[0][0] = 0;
	
	for(int i = 1; i < filas; i++){
		u.A[i][0] = u_t_por_A.A[i][1];
		//u_t.A[0][i] = this->A[i][1];
	}
	
	u.A[1][0] = u.A[1][0] - u.norma_dos();
	u = multiplicarXescalar(u,1.0/u.norma_dos());
	
	for(int i = 0; i < filas; i++){
		u_t.A[0][i] = u.A[i][0];
	}
	
	//tenemos b' y R1
	///b' = u_t_Y_k
	///R1 = u_t_por_A
	//b''
	Matrix b = productoMatrices(u_t, u_t_Y_k); //u_t_por_Y_k
	b = productoMatrices(u,b); //u_u_t_por_Y_k
	b = multiplicarXescalar(b,2);
	b = restaMatrices(u_t_Y_k,b);

	//R:
	Matrix R = productoMatrices(u_t,u_t_por_A);
	R = productoMatrices(u,R); //u_u_t_por_A
	R = multiplicarXescalar(R,2); //2u_u_t_por_A
	R = restaMatrices(u_t_por_A,R); 

	
	//~ uu_t = productoMatrices(u,u_t);
	//~ //uu_t.mostrar(cout);
	//~ uu_t = multiplicarXescalar(uu_t,2); //2uu_t
	//~ Matrix Q2 = Matrix(filas); //I^nxn
	//~ Q2 = restaMatrices(Q2,uu_t);
	//~ 
	//~ R = productoMatrices(Q2,R);
	
	///fin segundo paso
	
	//~ Matrix Q_t = productoMatrices(Q2,Q1);
	
	Matrix* R_res = new Matrix(R);
	Matrix* Qt_res = new Matrix(b);
	res = make_pair(Qt_res, R_res);
	
	return res;
}

void Matrix::mostrar(ostream& os){
	for(int i = 0; i < filas; i++){
		os << "[ ";
		for(int j = 0; j < columnas; j++){
			os << "| " << elem(i,j) << " |";
		}
		os << " ]" << endl;
	}
	os << endl;
}
Matrix Matrix::trasponer(){
	Matrix res = Matrix(columnas,filas);
	for(int i = 0; i < columnas; i++){
		for(int j = 0; j < filas; j++){
			res.A[i][j] = this->A[j][i];
		}
	}
	return res;
}
