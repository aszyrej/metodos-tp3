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
	/**/
	PageRank* p = new PageRank(cin);	
	p->hallarMatrizP();
	p->generar_cP();		//P = cP
	
	///begin parte 1
	/**/
	/**/
	//~ vector<double>* eigenvector = new vector<double>();
	//~ *eigenvector = p->power_method();
	
	/*imprime resultados*/
	
	/*vector<pair<int, double> >* result = new vector<pair<int, double> >();
	(*result) = makePairs((*eigenvector));
	sort(result->begin(),result->end(),cmp);
	imprimirResultado(cout,*result);*/
	
	//~ delete eigenvector;
	//~ delete result;
	/**/
	///end punto 1 y 2
	//~ cout << endl;	
	///begin punto 3
	
	vector<double>* eigenvector2 = new vector<double>();
	*eigenvector2 = p->quadratic_extrapolation_method();
	
	/*imprime resultados*/
	/*vector<pair<int, double> >* result2 = new vector<pair<int, double> >();
	(*result2) = makePairs((*eigenvector2));
	sort(result2->begin(),result2->end(),cmp);
	imprimirResultado(cout,*result2);*/
	
	delete eigenvector2;
	//~ delete result2;
	
	///end punto 3
	
	delete p;
	
	return 0;
	
	/**/
	///debug Matrix
	/** /
	
	Matrix* m = new Matrix(cin);
	
	m->mostrar(cout);		
	vector<double> nada;
	for(int i = 0; i < m->dame_filas(); i++) nada.push_back(2);
	cout << endl;
	pair<Matrix*,Matrix*> qr;
	pair<Matrix*,Matrix*> qr2;
	qr = m->factorizarQR();
	qr.second->mostrar(cout);	
	
	qr2 = m->factorizarQRopt(nada);
	
	//qr.first->mostrar(cout);
	
	cout << endl;
	
	qr.second->mostrar(cout);		
	cout << endl;
	qr2.second->mostrar(cout);		
	
	cout << endl;
	cout << "ahora vemos Q" << endl;
	cout << endl;
	
	Matrix menosyt = Matrix(nada);
	Matrix Q = qr.first->productoMatrices(*(qr.first),menosyt);
	Q.mostrar(cout);
	cout << endl;	
	qr2.first->mostrar(cout);
	
	//Matrix prod = (qr.first)->trasponer();
	//prod = m->productoMatrices(prod,*(qr.second));
	
	//prod.mostrar(cout);
	
	delete qr.first;
	delete qr2.first;
	delete qr.second;
	delete qr2.second;
	delete m;
	return 0;
	/ **/
}
