#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <utility>

using namespace std;

class Matrix{
	public:
		Matrix(vector<double>& y1, vector<double>& y2);
		
		factorizarQR();
		
	private:	
		vector<vector<double> > A;
		
};

#endif
