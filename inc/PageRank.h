#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include "../inc/SparseMatrix.h"
#include <iostream>
#include <vector>

class PageRank{
	public: 
		PageRank(std::istream & is);
		void power_method();
		void aitken_extrapolation();
		void quadratic_extrapolation();
		void mostrar(std::ostream & os);
		void hallarMatrizP();
		
	private:
		SparseMatrix *in_graph; //ESPARSA. connection graph
		// vector<vector<double> > P; //ESPARSA.		La formamos modificando in_graph
		
		
		//construir la matriz estocastica por columnas (markov's chain)
		std::vector<std::vector<double> > M; 	//column stocastic
		
		std::vector<double> _rank;			//eigenvector of M asociated with eigenvalue = 1
};

#endif
