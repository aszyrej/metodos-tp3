#include "../inc/PageRank.h"
		
using namespace std;		
		
PageRank::PageRank(istream& is){
	is >> n;
	is >> links;
	
	in_graph = new SparseMatrix(is,n,links); 	//W traspuesta
	
	for (int i = 0; i < n; i++) v.push_back(1.0/n);
	epsilon = 1e-6;
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
	cout << "iteracion final " << i << endl;
	return x;
}

//void PageRank::aitken_extrapolation(){

vector<double> PageRank::quadratic_extrapolation(vector<double>& x_kmenos3, vector<double>& x_kmenos2, vector<double>& x_kmenos1, vector<double>& x_k){
	vector<double> res;
	vector<vector<double> > ys;
	
	ys.push_back(restaVectores(x_kmenos2, x_kmenos3));
	ys.push_back(restaVectores(x_kmenos1, x_kmenos3));
	ys.push_back(restaVectores(x_k, x_kmenos3));
	
	Matrix Y = Matrix(ys[0],ys[1]);
	pair<Matrix*,Matrix*> qr = Y.factorizarQR(); 	//encuentra Qtraspuesta y R
	vector<double> y_k = vectorXescalar(ys[2],(-1));
	
	Matrix Qt_por_y = Matrix(y_k);
	Qt_por_y = Qt_por_y.productoMatrices(*(qr.first),Qt_por_y);
	double gamma1;
	double gamma2;
	double gamma3 = 1.0;
	
	gamma2 = Qt_por_y.elem(1,0) / (*(qr.second)).elem(1,1);
	gamma1 = (Qt_por_y.elem(0,0) - ((*(qr.second)).elem(0,1) * gamma2)) / (*(qr.second)).elem(0,0);
	
	double beta0 = gamma1 + gamma2 + gamma3;
	double beta1 = gamma2 + gamma3;
	double beta2 = gamma3;
	
	vector<double> v1 = vectorXescalar(x_kmenos2,beta0);
	vector<double> v2 = vectorXescalar(x_kmenos1,beta1);
	vector<double> v3 = vectorXescalar(x_k,beta2);
	
	res = sumaVectores(v3,sumaVectores(v1,v2));
	
	delete qr.first;
	delete qr.second;
	return res;
}

vector<double> PageRank::quadratic_extrapolation_opt(vector<double>& x_kmenos3, vector<double>& x_kmenos2, vector<double>& x_kmenos1, vector<double>& x_k){
	vector<double> res;
	vector<vector<double> > ys;
	
	ys.push_back(restaVectores(x_kmenos2, x_kmenos3));
	ys.push_back(restaVectores(x_kmenos1, x_kmenos3));
	ys.push_back(restaVectores(x_k, x_kmenos3));
	
	Matrix Y = Matrix(ys[0],ys[1]);
	vector<double> y_k = vectorXescalar(ys[2],(-1));
	
	pair<Matrix*,Matrix*> qr = Y.factorizarQRopt(y_k); 	//encuentra Qtraspuesta*-y_k <matriz vector nx1> y R <matriz nx2>
	
	
	//~ Matrix Qt_por_y = Matrix(y_k);
	//~ Qt_por_y = Qt_por_y.productoMatrices(*(qr.first),Qt_por_y);
	Matrix Qt_por_y = *(qr.first);
	double gamma1;
	double gamma2;
	double gamma3 = 1.0;
	
	gamma2 = Qt_por_y.elem(1,0) / (*(qr.second)).elem(1,1);
	gamma1 = (Qt_por_y.elem(0,0) - ((*(qr.second)).elem(0,1) * gamma2)) / (*(qr.second)).elem(0,0);
	
	double beta0 = gamma1 + gamma2 + gamma3;
	double beta1 = gamma2 + gamma3;
	double beta2 = gamma3;
	
	vector<double> v1 = vectorXescalar(x_kmenos2,beta0);
	vector<double> v2 = vectorXescalar(x_kmenos1,beta1);
	vector<double> v3 = vectorXescalar(x_k,beta2);
	
	res = sumaVectores(v3,sumaVectores(v1,v2));
	
	delete qr.first;
	delete qr.second;
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
			x_k = quadratic_extrapolation_opt(x_kmenos3, x_kmenos2, x_kmenos1, x_k);
			x_k = vectorXescalar(x_k, (1.0 / norm_uno(x_k)));
		}
		
		i++;			//luego del if.
		
		if(i%200 == 0) cout << "delta : " << delta << endl;
	}while(!(delta < epsilon));
	//~ }while(i <= 3);
	//~ cout << endl << norm_dos(x_k) << endl;
	//~ cout << endl << norm_uno(x_k) << endl;
	//~ x_k = vectorXescalar(x_k, (1.0 / norm_uno(x_k)));
	//~ cout << endl << norm_dos(x_k) << endl;	
	//~ cout << endl << norm_uno(x_k) << endl;	
	cout << endl << "iteracion final " << i << endl;	
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

double PageRank::norm_dos(vector<double> y){
	double res = 0;
	for(unsigned int i = 0; i < y.size(); i++){
		res = res + (y[i] * y[i]);
	}
	return sqrt(res);
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
