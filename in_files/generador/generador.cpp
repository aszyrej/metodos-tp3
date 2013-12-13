#include <iostream>
#include <sstream> 
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */

using namespace std;

int main()
{
	FILE * myfile;
	myfile = fopen("salida.txt","w");
	int random;
	int nodos;
	int contador=0;
	srand (time(NULL));
	cin>>nodos;
	
	stringstream ss1;
	stringstream ss2;
	ss1 << nodos;
	string str1;
	string str2;
	
	str1 = ss1.str()+"\n";
	ss1.str("");
	ss2.str("");
	const char *chr1;
	chr1 = str1.c_str();
	fputs (chr1 , myfile);
	fputs ("                                            \n" , myfile);
	
	for(int n=0; n<nodos; ++n){
		for (int j=0; j<nodos; j+=20){
			if (n!=j){
				random = rand() % 10;
				if (random<=1){
					ss1 << n;
					ss2 << j;
					str1 = ss1.str();
					str2 = ss2.str();
					ss1.str("");
					ss2.str("");
					str1=str1+" "+str2+"\n";
					chr1 = str1.c_str();	
					fputs (chr1 , myfile);			
					contador++;
				}
			}
		}
	}
	int res=1;
	while(nodos!=0){
		res++;
		nodos=nodos/10;
	}
	cout<<contador<<endl;
	fseek(myfile, res, SEEK_SET);
	ss1 << contador;
	str1 = ss1.str();
	chr1 = str1.c_str();
	fputs (chr1, myfile);
	fclose(myfile);

	return 0;
}
