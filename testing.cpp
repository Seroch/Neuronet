#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "neuronet.h"

using namespace std;

neuronet neuro;

void load(string init){

	int in, hid, out;
	string first, line;
	int i, j;

	ifstream initstr(init);

	getline(initstr, first);

	istringstream iss(first);

	iss >> in >> hid >> out;

	neuro.ni = in;
	neuro.nh = hid;
	neuro.no = out;

	for(int i=0; i<hid; i++){
		double bias;
		vector<double> weights;

		getline(initstr, line);

		istringstream ist(line);

		ist >> bias;

		for(j=0; j<in; j++){
			double tmpfl;
			ist >> tmpfl;

			weights.push_back(tmpfl);
		}

		neuro.add(weights, bias, "hidden");
	
	}

	for(int i=0; i<out; i++){
		double bias;
		vector<double> weights;

		getline(initstr, line);

		istringstream ist(line);

		ist >> bias;

		for(j=0; j<hid; j++){
			double tmpfl;
			ist >> tmpfl;

			weights.push_back(tmpfl);
		}

		neuro.add(weights, bias, "output");
	}
}

void testing(string test){

	int num, in, out;
	int i, j, k;
	vector<double> inputs;
	vector<int> outputs;
	string first, line;
	//int a=0, b=0, c=0, d=0;
	vector<double> a, b, c, d;

	ifstream teststr(test);

	getline(teststr, first);

	istringstream iss(first);

	iss >> num >> in >> out;

	for(i=0; i<num; i++){

		getline(teststr, line);

		istringstream ist(line);

		for(j=0; j<in; j++){
			double tmpfl;
			ist >> tmpfl;

			inputs.push_back(tmpfl);
		}

		for(j=0; j<out; j++){
			int tmp;
			ist >> tmp;

			outputs.push_back(tmp);
		}

		neuro.testing(inputs, outputs, &a, &b, &c, &d);

		inputs.clear();
		outputs.clear();
	}

	vector<double> accuracy(a.size(),0), precision(a.size(),0), recall(a.size(),0), f1(a.size(),0);

	for(i=0; i<a.size(); i++){
		accuracy[i] =  (a[i] + d[i]) / ((a[i] + b[i] + c[i] + d[i]));
		precision[i] = (a[i]) / ((a[i] + b[i]));
		recall[i] = (a[i]) / ((a[i] + c[i]));
		f1[i] = ((2 * precision[i] * recall[i])) / ((precision[i] + recall[i]));

		cout << setprecision(3) << (int) a[i] << " " << (int) b[i] << " " << (int) c[i] << " " << (int) d[i] << fixed << " " << accuracy[i] << " " << precision[i] << " " << recall[i] << " " << f1[i] << endl;
	}

	double aa=0, bb=0, cc=0, dd=0;

	for(i=0; i<a.size(); i++){
		aa = aa + a[i];
		bb = bb + b[i];
		cc = cc + c[i];
		dd = dd + d[i];
	}

	double acc =  (aa + dd) / ((aa + bb + cc + dd));
	double prec = (aa) / ((aa + bb));
	double rec = (aa) / ((aa + cc));
	double fm1 = ((2 * prec * rec)) / ((prec + rec));

	cout<< fixed << setprecision(3) << acc << " " << prec << " " << rec << " " << fm1 << endl;

	double sumacc=0;
	double sumprec=0;
	double sumrec=0;

	for(i=0; i<a.size(); i++){
		sumacc = sumacc + accuracy[i];
		sumprec = sumprec + precision[i];
		sumrec = sumrec + recall[i];
	}

	sumacc = sumacc / i;
	sumprec = sumprec / i;
	sumrec = sumrec / i;

	double sumf1 = ((2 * sumprec * sumrec)) / ((sumprec + sumrec));

	cout<< fixed << setprecision(3) << sumacc << " " << sumprec << " " << sumrec << " " << sumf1 << endl;


}

main(){
	string net, test, output;
	int epoch;
	double rate;
	int in, hid, out;
	string first, line;
	int i, j;

	cout<< "Enter the name of the file containing the neural network: ";
	cin>>net;

	cout<< "Enter the name of the testing set file: ";
	cin>>test;

	cout<< "Enter the name of the output file: ";
	cin>>output;

	load(net);

    freopen(output.c_str(),"w",stdout);

    testing(test);
}