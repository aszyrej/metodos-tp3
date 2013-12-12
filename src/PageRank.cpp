#include "../inc/PageRank.h"
		
using namespace std;		
		
PageRank::PageRank(istream& is){
	is >> n;
	is >> links;
	
	in_graph = new SparseMatrix(is,n,links); 	//W traspuesta
	
	epsilon = 0.0000000001;
}

void PageRank::hallarMatrizP(){
	in_graph->calcularP();				//P traspuesta
	in_graph->trasponer();				//P
}

vector<double> PageRank::power_method(){
	double delta = 999;
	vector<double> x;
	for (int i = 0; i < n; i++) x.push_back(1.0/n);
	do{
		
	}while(delta < epsilon);
	
	return x;
}

void PageRank::aitken_extrapolation(){

}

void PageRank::quadratic_extrapolation(){

}

void PageRank::mostrar(ostream & os){
	in_graph->mostrar(os);
}
