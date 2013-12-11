#ifndef _SPARSE_H_
#define _SPARSE_H_

#include <iostream>
#include <vector>
#include <list>
#include <pair>

class SparseMatrix{
	public:
		SparseMatrix(istream& is);
		double& elem(int i, int j);
		void transponer();
		vector<double> multiplicarXvector(vector<double> v);
		void multiplicarXescalar(double x);
		
		
	private:
		//vector<double> values;
		//vector<int> columns;
		//vector<int> rowIndex;
		int n;					//cuadrada
		int cant_nonzero;
		
		//vector<int> outdegree;
		
		vector<list<pair<double, int> > > vil;
};


#endif