#ifndef _SPARSE_H_
#define _SPARSE_H_

#include <iostream>
#include <vector>
#include <list>
#include <utility>

class SparseMatrix{
	public:
		SparseMatrix(std::istream& is);
		double elem(int i, int j);
		void trasponer();
		std::vector<double> multiplicarXvector(std::vector<double>& v);
		void multiplicarXescalar(double x);
		void mostrar(std::ostream& os);
		void calcularP();
		
	private:
		//vector<double> values;
		//vector<int> columns;
		//vector<int> rowIndex;
		int n;					//cuadrada
		int cant_nonzero;
		
		//vector<int> outdegree;
		
		std::vector<std::list<std::pair<double, int> > > vil;
};


#endif
