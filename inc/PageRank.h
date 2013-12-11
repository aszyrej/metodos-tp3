#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include <iostream>
#include <vector>

class PageRank{
	public: 
		PageRank(istream& is);
		power_method();
		aitken_extrapolation();
		quadratic_extrapolation();
		
		
	private:
		SparseMatrix *in_graph; //ESPARSA. connection graph
		// vector<vector<double> > P; //ESPARSA.		La formamos modificando in_graph
		
		
		//construir la matriz estocastica por columnas (markov's chain)
		vector<vector<double> > M; 	//column stocastic
		
		vector<double> _rank;			//eigenvector of M asociated with eigenvalue = 1
};

#endif
