#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
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

void training(string train, int epoch, double rate){

	int num, in, out;
	int i, j, k;
	vector<double> inputs;
	vector<double> outputs;
	string first, line;

	ifstream trainstr(train);

	getline(trainstr, first);

	istringstream iss(first);

	iss >> num >> in >> out;

	for(int i=0; i<num; i++){

		getline(trainstr, line);

		istringstream ist(line);

		for(j=0; j<in; j++){
			double tmpfl;
			ist >> tmpfl;

			inputs.push_back(tmpfl);
		}

		for(j=0; j<out; j++){
			double tmpfl;
			ist >> tmpfl;

			outputs.push_back(tmpfl);
		}

		neuro.learning(inputs, outputs, rate);

		inputs.clear();
		outputs.clear();
		ist.clear();
	}

	trainstr.clear();
	trainstr.close();
}

main(){
	string init, train, output;
	int epoch;
	double rate;
	int in, hid, out;
	string first, line;
	int i, j;

	cout<< "Enter the name of the file containing the initial neural network: ";
	cin>>init;

	cout<< "Enter the name of the training set file: ";
	cin>>train;

	cout<< "Enter the name of the output file: ";
	cin>>output;

	cout<< "Enter the number of epochs: ";
	cin>>epoch;

	cout<< "Enter the learning rate: ";
	cin>>rate;

	load(init);

	for(i=0; i<epoch; i++){
		training(train, epoch, rate);
	}

    freopen(output.c_str(),"w",stdout);

	neuro.print();

}