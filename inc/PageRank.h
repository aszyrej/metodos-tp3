#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include "../inc/SparseMatrix.h"
#include <iostream>
#include <vector>
#include <math.h>

class PageRank{
	public: 
		PageRank(std::istream & is);
		std::vector<double> power_method();
		void aitken_extrapolation();
		void quadratic_extrapolation();
		void mostrar(std::ostream & os);
		void hallarMatrizP();
		
		
		
		
	private:
		int n,links;
		SparseMatrix *in_graph; //ESPARSA. connection graph
		double epsilon,c;
		std::vector<double> _rank;			//eigenvector of M asociated with eigenvalue = 1
		
		double norm_uno(vector<double>& y);
		vector<double> sumaVectores(vector<double>& x,vector<double>& y);
		vector<double> vectorXescalar(vector<double>& v , double w));
		vector<double> restaVectores(vector<double>& y,vector<double>& x);
};

#endif
