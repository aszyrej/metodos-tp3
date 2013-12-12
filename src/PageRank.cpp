#include "../inc/PageRank.h"
		
using namespace std;		
		
PageRank::PageRank(istream& is){
	is >> n;
	is >> links;
	
	in_graph = new SparseMatrix(is,n,links); 	//W traspuesta
	
	epsilon = 0.0000000001;
	c = 0.15;
}

void PageRank::hallarMatrizP(){
	in_graph->calcularP();				//P traspuesta
	in_graph->trasponer();				//P
}y

vector<double> PageRank::power_method(){
	double delta;
	vector<double> x;
	vector<double> y;
	double w;
	for (int i = 0; i < n; i++) x.push_back(1.0/n);
	in_graph->multiplicarXescalar(c); 		//P = cP
	
	do{
		//x = Ax
		y = in_graph->multiplicarXvector(x);
		w = norm_uno(x) - norm_uno(y);
		y = sumaVectores(y,vectorXescalar(v,w));
		
		delta = norm_uno(restaVectores(y,x))
	
	}while(!(delta < epsilon));
	
	return x;
}

void PageRank::aitken_extrapolation(){

}

void PageRank::quadratic_extrapolation(){

}

void PageRank::mostrar(ostream & os){
	in_graph->mostrar(os);
}


double PageRank::norm_uno(vector<double>& y){
	double res = 0;
	for(int i = 0; i < y.size(); i++){
		res = res + abs(y[i]);
	}
	return res;
}

vector<double> PageRank::sumaVectores(vector<double>& x,vector<double>& y){
	vector<double> res;
	for(int i = 0; i < y.size(); i++){
		res.push_back(x[i] + y[i]);
	}
	return res;
}

vector<double> PageRank::vectorXescalar(vector<double>& v , double w)){
	vector<double> res;
	for(int i = 0; i < v.size(); i++){
		res.push_back(v[i] * w);
	}
	return res;	
}
		
vector<double> PageRank::restaVectores(vector<double>& y,vector<double>& x){
	vector<double> res;
	for(int i = 0; i < y.size(); i++){
		res.push_back(y[i] - x[i]);
	}
	return res;
}
