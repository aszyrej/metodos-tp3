#include <iostream>
#include "../inc/PageRank.h"

using namespace std;

int main(int argc, char **argv)
{
	PageRank* p = new PageRank(cin);
		
	p->hallarMatrizP();
	vector<double> eigenvector = p->power_method();
	///end punto 1 y 2
	
	
	
	
	delete p;
	return 0;
}
