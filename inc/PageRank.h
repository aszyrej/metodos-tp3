#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include "../inc/SparseMatrix.h"
#include <iostream>
#include <vector>
#include <cmath>

class PageRank{
	public: 
		PageRank(std::istream & is);
		std::vector<double> power_method();
		//void aitken_extrapolation();
		std::vector<double> quadratic_extrapolation(std::vector<double>& x_kmenos3, std::vector<double>& x_kmenos2, std::vector<double>& x_kmenos1, std::vector<double>& x_k);
		std::vector<double> quadratic_extrapolation_method();
		void mostrar(std::ostream & os);
		void hallarMatrizP();
		void generar_cP();
		
		int cant_nodos(){ return n; }
		int cant_links(){ return links; }
		
		
	private:
		int n,links;
		SparseMatrix *in_graph; //ESPARSA. connection graph
		double epsilon,c;
		std::vector<double> _rank;			//eigenvector of M asociated with eigenvalue = 1
		std::vector<double> v;
		
		double norm_uno(std::vector<double> y);
		std::vector<double> sumaVectores(std::vector<double>& x,std::vector<double> y);
		std::vector<double> vectorXescalar(std::vector<double>& v , double w);
		std::vector<double> restaVectores(std::vector<double>& y,std::vector<double>& x);
};

#endif
