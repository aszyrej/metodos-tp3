#include "../inc/PageRank.h"
		
using namespace std;		
		
PageRank::PageRank(istream& is){
	is >> n;
	is >> links;
	
	in_graph = new SparseMatrix(is,n,links); 	//W traspuesta
	
	for (int i = 0; i < n; i++) v.push_back(1.0/n);
	epsilon = 1e-5;
	c = 1;
}

void PageRank::hallarMatrizP(){
	in_graph->calcularP();				//P traspuesta
	in_graph->trasponer();				//P
}

void PageRank::generar_cP(){
	in_graph->multiplicarXescalar(c); 
}

vector<double> PageRank::power_method(){
	double delta;
	vector<double> x = v;
	vector<double> y;
	double w;

	//in_graph->multiplicarXescalar(c); 		//P = cP already done in main
	// in_graph = cP
	int i = 0;
	do{
		//x = Ax
		y = in_graph->multiplicarXvector(x);
		w = norm_uno(x) - norm_uno(y);
		y = sumaVectores(y,vectorXescalar(v,w));
		
		delta = norm_uno(restaVectores(y,x));
		x = y;
		i++;
		if(i%200 == 0) cout << "delta : " << delta << endl;
	}while(!(delta < epsilon));
	
	return x;
}

//void PageRank::aitken_extrapolation(){

std::vector<double> PageRank::quadratic_extrapolation(std::vector<double>&, std::vector<double>&, std::vector<double>&, std::vector<double>&){
	vector<double> res;
	vector<vector<double> >* ys = new 	vector<vector<double> >();
	
	for(int i = 0; i<3 ; i++){
		(*ys)
	}
	
	return res;
}

vector<double> PageRank::quadratic_extrapolation_method(){
	double delta;
	vector<double> x_k = v;
	vector<double> x_kmenos1 = x_k;
	vector<double> x_kmenos2 = x_k;
	vector<double> x_kmenos3 = x_k;
	vector<double> y;
	double w;

	//in_graph->multiplicarXescalar(c); 		//P = cP already done in main
	// in_graph = cP
	int i = 0;
	
	do{
		//x = Ax
		y = in_graph->multiplicarXvector(x_k);
		w = norm_uno(x_k) - norm_uno(y);
		y = sumaVectores(y,vectorXescalar(v,w));
		
		delta = norm_uno(restaVectores(y,x_k));
		
		x_kmenos3 = x_kmenos2;
		x_kmenos2 = x_kmenos1;
		x_kmenos1 = x_k;
		x_k = y;
				
		if((i>=3) && (i%10 == 0)){	//chequear guarda. Variar segun experimentacion
			x_k = quadratic_extrapolation(x_kmenos3, x_kmenos2, x_kmenos1, x_k);
		}
		
		i++;			//luego del if.
		
		if(i%200 == 0) cout << "delta : " << delta << endl;
	}while(!(delta < epsilon));
	
	return x_k;
}


void PageRank::mostrar(ostream & os){
	in_graph->mostrar(os);
}


double PageRank::norm_uno(vector<double> y){
	double res = 0;
	for(unsigned int i = 0; i < y.size(); i++){
		res = res + abs(y[i]);
	}
	return res;
}

vector<double> PageRank::sumaVectores(vector<double>& x,vector<double> y){
	vector<double> res;
	for(unsigned int i = 0; i < y.size(); i++){
		res.push_back(x[i] + y[i]);
	}
	return res;
}

vector<double> PageRank::vectorXescalar(vector<double>& v , double w){
	vector<double> res;
	for(unsigned int i = 0; i < v.size(); i++){
		res.push_back(v[i] * w);
	}
	return res;	
}
		
vector<double> PageRank::restaVectores(vector<double>& y,vector<double>& x){
	vector<double> res;
	for(unsigned int i = 0; i < y.size(); i++){
		res.push_back(y[i] - x[i]);
	}
	return res;
}
