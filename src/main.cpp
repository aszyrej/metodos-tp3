#include <iostream>
#include "../inc/PageRank.h"
#include <utility>
#include <algorithm>

using namespace std;

bool cmp(pair<int,double> i, pair<int,double> j){
	return i.second > j.second;
}

vector<pair<int, double> > makePairs(vector<double>& v){
	vector<pair<int, double> > res;
	for (int i = 0; i < (int)v.size(); i++){
		res.push_back(make_pair(i+1,v[i]));
	}
	return res;
}

void imprimirResultado(ostream& os ,vector<pair<int, double> >& v){
	for(int i = 0; i < (int)v.size(); i++){
		os << v[i].first << " " << v[i].second << endl;
	}
}

int main(int argc, char **argv)
{
	
	PageRank* p = new PageRank(cin);
		
	p->hallarMatrizP();
	vector<double>* eigenvector = new vector<double>();
	
	p->generar_cP();		//P = cP
	
	///begin parte 1
	
	/** /
	*eigenvector = p->power_method();
	
	vector<pair<int, double> >* result = new vector<pair<int, double> >();
	
	(*result) = makePairs((*eigenvector));
	
	sort(result->begin(),result->end(),cmp);
	
	imprimirResultado(cout,*result);
	
	delete eigenvector;
	delete result;
	/**/
	///end punto 1 y 2
	cout << endl;	
	///begin punto 3
	
	vector<double>* eigenvector2 = new vector<double>();
	*eigenvector2 = p->quadratic_extrapolation_method();
	
	vector<pair<int, double> >* result2 = new vector<pair<int, double> >();
	
	(*result2) = makePairs((*eigenvector2));
	
	sort(result2->begin(),result2->end(),cmp);
	
	imprimirResultado(cout,*result2);
	
	delete eigenvector2;
	delete result2;
	
	///end punto 3
	
	delete p;
	
	return 0;
	
	/**/
	///debug Matrix
	/** /
	
	Matrix* m = new Matrix(cin);
	
	m->mostrar(cout);		
	
	cout << endl;
	pair<Matrix*,Matrix*> qr;
	qr = m->factorizarQR();
	
	qr.first->mostrar(cout);		
	
	cout << endl;
	
	qr.second->mostrar(cout);		
	
	cout << endl;
	
	Matrix prod = (qr.first)->trasponer();
	prod = m->productoMatrices(prod,*(qr.second));
	
	prod.mostrar(cout);
	
	delete qr.first;
	delete qr.second;
	delete m;
	return 0;
	/ **/
}
