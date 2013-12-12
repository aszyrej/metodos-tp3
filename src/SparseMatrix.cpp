#include "../inc/SparseMatrix.h"

using namespace std;

SparseMatrix::SparseMatrix(istream& is, int nodos, int links){
	n = nodos;			//num paginas
	cant_nonzero = links;	//num links
	
	list<pair<double,int> > l;
	for(int i = 0; i < n; i++){
		vil.push_back(l);			//inicializo todas las filas como vacias.
	}
	
	int p_src, p_dst;	//existe link de p_src a p_dst
	for (int i = 0; i < cant_nonzero; i++){	//para cada link
		is >> p_src;
		is >> p_dst; 
		//queremos hallar W tq wij = 1 si la pagina j tiene un link a la pagina i
		//construimos primero W traspuesta pues los datos de entrada nos vienen perfecto para eso
		
		//ignoramos autolinks
		
		if(p_src != p_dst){				///en teoria se cumple siempre
			//SparseMatrix[p_src-1][p_dst-1] = 1
			pair<double,int> val = make_pair(1.0,p_dst-1);
			vil[p_src-1].push_back(val);
		}
	}
}

double SparseMatrix::elem(int i, int j){
	if(vil[i].empty()) return 0.0;
	for (list<pair<double,int> >::iterator it = vil[i].begin(); it != vil[i].end(); ++it){
		if((*it).second == j) return (*it).first;
	}
	return 0.0;
}

void SparseMatrix::trasponer(){
	vector<list<pair<double, int> > >* vil_t = new vector<list<pair<double, int> > >();
	list<pair<double,int> > l;
	for(int i = 0; i < n; i++){
		vil_t->push_back(l);			//inicializo todas las filas como vacias.
	}
	
	for(int i = 0; i < n; i++){
		for (list<pair<double,int> >::iterator it = vil[i].begin(); it != vil[i].end(); ++it){
			(*vil_t)[(*it).second].push_back(make_pair((*it).first,i));
		}
	}
	vil = *vil_t;
	delete vil_t;
}

vector<double> SparseMatrix::multiplicarXvector(vector<double>& v){ 
	vector<double> res;
	double xi = 0;
	for(int i = 0; i < n; i++){
		for (list<pair<double,int> >::iterator it = vil[i].begin(); it != vil[i].end(); ++it){
			xi = xi + ((*it).first * v[(*it).second]);
		}
		res.push_back(xi);
		xi = 0;
	}
	return res;
}


void SparseMatrix::multiplicarXescalar(double x){
	for(int i = 0; i < n; i++){
		for (list<pair<double,int> >::iterator it = vil[i].begin(); it != vil[i].end(); ++it){
			(*it).first = (*it).first * x;
		}
	}
}

void SparseMatrix::calcularP(){
	for(int i = 0; i < n; i++){
		double nj = (double) vil[i].size();
		for (list<pair<double,int> >::iterator it = vil[i].begin(); it != vil[i].end(); ++it){
			(*it).first = (*it).first / nj;
		}
	}
}

void SparseMatrix::mostrar(ostream& os){
	for(int i = 0; i < n; i++){
		os << "[ ";
		for(int j = 0; j < n; j++){
			os << "| " << elem(i,j) << " |";
		}
		os << " ]" << endl;
	}
	os << endl;
}	
