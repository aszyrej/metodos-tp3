#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

class Matrix{
	public:
		Matrix(vector<double>& y1, vector<double>& y2);
		Matrix(vector<double>& y1);
		Matrix(istream& is);
		Matrix(int n);
		Matrix(int n, int m);
		Matrix(const Matrix& m);
		double elem(int i, int j);
		
		//debug
		Matrix trasponer();
		
		
		Matrix productoMatrices(Matrix& m1, Matrix& m2);
		Matrix productoMatrices(Matrix& m1); //m1 * this
		Matrix multiplicarXescalar(Matrix& m1, double escalar);
		Matrix restaMatrices(Matrix& m1, Matrix& m2);
		Matrix restaMatrices(Matrix& m1); //this - m1
		pair<Matrix*,Matrix*> factorizarQR();
		pair<Matrix*,Matrix*> factorizarQRopt(vector<double>& y_t);
		
		double norma_dos(); //Uso: Matriz vector, n filas 1 columna... seria norma_dos de vectores dentro del modulo matriz
		
		int dame_filas(){ return filas; } 
		int dame_columnas(){ return columnas; }
		
		void mostrar(ostream& os);
		Matrix cargar(istream& is);
		
	private:	
		int filas; 
		int columnas;
		vector<vector<double> > A;
		//vector<vector<double> >* Q;
		//vector<vector<double> >* R;
		
};

#endif
