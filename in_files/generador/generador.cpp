#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */

using namespace std;

struct arista{
	int e1; 
	int e2;
	arista(int _e1,int _e2){
		e1=_e1;
		e2=_e2;
	}
};

int main()
{
	vector<arista> a;
	int random;
	int nodos;
	srand (time(NULL));
	cin>>nodos;
	cout<<nodos<<endl;
	for(int n=0; n< nodos; ++n){
		for (int j=0; j<nodos; ++j){
			arista aux(n,j);
			if (n!=j){
				random = rand() % 10;
				if (random<=2){
					a.push_back(aux);
				}
			}
		}
	}
	cout<<a.size()<<endl;
	for (int i=0;i<a.size();++i){
		cout<<a[i].e1<<" "<<a[i].e2<<endl;
	}
	return 0;
}
