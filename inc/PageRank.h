#ifndef __PAGERANK_H__
#define __PAGERANK_H__

class PageRank{
	public: 
		PageRank();
		power_method();
		aitken_extrapolation();
		quadratic_extrapolation();
		
		
	private:
		vector<vector<double> > in_graph;
		
		
		//construir la matriz estocastica por columnas (markov's chain)
		vector<vector<double> > M; 	//column stocastic
		
		vector<double> _rank;			//eigenvector of M asociated with eigenvalue = 1
};

#endif
