vector<double> PageRank::power_method(){
	double delta;
	vector<double> x = v;
	vector<double> y;
	double w;

	int i = 0;
	do{
		//x = Ax
		y = in_graph->multiplicarXvector(x);
		w = norm_uno(x) - norm_uno(y);
		y = sumaVectores(y,vectorXescalar(v,w));
		
		delta = norm_uno(restaVectores(y,x));
		x = y;
		i++;
		//~ if(i%200 == 0) cout << "delta : " << delta << endl;
	}while(!(delta < epsilon));
	cout << i << endl;
	return x;
}


//ESTO ES VIEJO, hace cuentas ineficientes
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

//ESTE ES EL OPTIMIZADO. HACE CUENTAS EFICIENTES
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
				
		if((i>=3) && (i%50 == 0)){	//chequear guarda. Variar segun experimentacion
			x_k = quadratic_extrapolation_opt(x_kmenos3, x_kmenos2, x_kmenos1, x_k);
			x_k = vectorXescalar(x_k, (1.0 / norm_uno(x_k)));
		}
		
		i++;			//luego del if.
		
		//~ if(i%200 == 0) cout << "delta : " << delta << endl;
	}while(!(delta < epsilon));
	cout << i << endl;	
	return x_k;
}

