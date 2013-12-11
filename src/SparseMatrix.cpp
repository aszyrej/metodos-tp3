#include "../inc/SparseMatrix.h"

SparseMatrix::SparseMatrix(istream& is){
	is >> n;			//num paginas
	is >> cant_nonzero;	//num links
	
	list<pair<double,int> > l;
	for(int i = 0; i < n; i++){
		vil.push_back(l);			//inicializo todas las filas como vacias.
	}
	
	int p_src, p_dst;	//existe link de p_src a p_dst
	for (int i = 0; i < cant_nonzero; i++){	//para cada link
		is >> p_src;
		is >> p_dst; 
		//queremos hallar W tq wij = 1 si la pagina j tiene un link a la pagina i
		//construimos primero W transpuesta pues los datos de entrada nos vienen perfecto para eso
		//ignoramos autolinks
		if(p_src != p_dst){				///en teoria se cumple siempre
			//SparseMatrix[p_src-1][p_dst-1] = 1
			pair<double,int> val = make_pair(1.0,p_dst-1);
			vil[p_src-1].push_back(val);
		}
	}
	
	/*
//	for(int i = 0; i < n; i++){
//		outdegree.push_back(0);		//inicializo outdegree para cada pag
//	}
	outdegree = vector<int>(n,0);
	
	int p_src, p_dst;	//existe link de p_src a p_dst
	int p_anterior = -999;
		
	for (int i = 0; i < cant_nonzero; i++){	//para cada link
		is >> p_src;
		is >> p_dst; 
		//queremos hallar W tq wij = 1 si la pagina j tiene un link a la pagina i
		//construimos primero W transpuesta pues los datos de entrada nos vienen perfecto para eso
		//ignoramos autolinks
		if(p_src != p_dst){
			//SM[p_src-1][p_dst-1] = 1
			outdegree[p_src-1]++; 
			
			values.push_back(1);
			if(p_anterior != p_src){
				rowIndex.push_back(values.length()-1);
			}
			columns.push_back(p_dst-1);
			
			p_anterior = p_src;
		}
	}
	rowIndex.push_back(cant_nonzero); //primer y ultimo valor hardcodeados
	*/
}

double& elem(int i, int j){
	if(vil[i].empty()) return 0;
	for (list<int>::iterator it = vil[i].begin(); it != vil[i].end(); ++it){
		if(*it.second = j) return *it.first;
	}
	return 0;
}

void SparseMatrix::transponer(){
	
	
}

vector<double> SparseMatrix::multiplicarXvector(vector<double> v){ 



}


void SparseMatrix::multiplicarXescalar(double x){

}