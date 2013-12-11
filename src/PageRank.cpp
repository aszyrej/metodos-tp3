#include "../inc/PageRank.h"
		
using namespace std;		
		
PageRank::PageRank(istream& is){
	in_graph = new SparseMatrix(is); 	//W traspuesta
}

void PageRank::hallarMatrizP(){
	in_graph->calcularP();				//P traspuesta
	in_graph->trasponer();				//P
}

void PageRank::power_method(){

}

void PageRank::aitken_extrapolation(){

}

void PageRank::quadratic_extrapolation(){

}

void PageRank::mostrar(ostream & os){
	in_graph->mostrar(os);
}
