#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include "../inc/SparseMatrix.h"
#include <iostream>
#include <vector>

class PageRank{
	public: 
		PageRank(std::istream & is);
		vector<double> power_method();
		void aitken_extrapolation();
		void quadratic_extrapolation();
		void mostrar(std::ostream & os);
		void hallarMatrizP();
		
	private:
		SparseMatrix *in_graph; //ESPARSA. connection graph
			
		std::vector<double> _rank;			//eigenvector of M asociated with eigenvalue = 1
};

#endif
