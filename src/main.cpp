#include <iostream>
#include "../inc/PageRank.h"

using namespace std;

int main(int argc, char **argv)
{
	PageRank* p = new PageRank(cin);
	
	p->mostrar(cout);
	
	p->hallarMatrizP();
	
	p->mostrar(cout);
	
	delete p;
	return 0;
}
