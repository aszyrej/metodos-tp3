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
	
	*eigenvector = p->power_method();
	
	vector<pair<int, double> >* result = new vector<pair<int, double> >();
	
	(*result) = makePairs((*eigenvector));
	
	sort((*result).begin(),(*result).end(),cmp);
	
	imprimirResultado(cout,*result);
	
	///end punto 1 y 2
	
	
	
	delete p;
	delete eigenvector;
	delete result;
	return 0;
}
