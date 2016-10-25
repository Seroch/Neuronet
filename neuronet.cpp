#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <iomanip>
#include "neuronet.h"

double sig(double x){
	return (1/(1+exp(-x)));
}

double dsig(double x){
	return (sig(x)*(1-sig(x)));
}

void neuronet::learning(std::vector<double> exin, std::vector<double> exout, double rate){
	int i, j;

	//Forward propagation
	for(i=0; i< hidlayer.size(); i++){
		mid.push_back(sig(hidlayer[i].sum(exin)));
	}

	for(i=0; i< outlayer.size(); i++){
		outputs.push_back(sig(outlayer[i].sum(mid)));
	}

	//Backward propagation

	for(i=0; i< outlayer.size(); i++){
		outlayer[i].delta = (dsig(outlayer[i].sum(mid)))*(exout[i]-outputs[i]);
	}

	for(i=0; i< hidlayer.size(); i++){

		double forward = 0;

		for(j=0; j < outlayer.size(); j++){
			forward = forward + outlayer[j].weights[i]*outlayer[j].delta;
		}

		hidlayer[i].delta = (dsig(hidlayer[i].sum(exin)))*forward;
	}

	//Updating the weights

	for(i=0; i< hidlayer.size(); i++){

		hidlayer[i].bias = hidlayer[i].bias + (rate * (-1) * hidlayer[i].delta);

		for(j=0; j < hidlayer[i].weights.size(); j++){
			hidlayer[i].weights[j] = hidlayer[i].weights[j] + (rate * exin[j] * hidlayer[i].delta);
		}
	}

	for(i=0; i< outlayer.size(); i++){

		outlayer[i].bias = outlayer[i].bias + (rate * (-1) * outlayer[i].delta);

		for(j=0; j < outlayer[i].weights.size(); j++){
			outlayer[i].weights[j] = outlayer[i].weights[j] + (rate * mid[j] * outlayer[i].delta);
		}
	}

	mid.clear();
	outputs.clear();
}

void neuronet::testing(std::vector<double> exin, std::vector<int> exout, std::vector<double>* a, std::vector<double>* b, std::vector<double>* c, std::vector<double>* d){

	int i;

	std::vector<int> intout;

	mid.clear();

	for(i=0; i< hidlayer.size(); i++){
		mid.push_back(sig(hidlayer[i].sum(exin)));
	}

	for(i=0; i< outlayer.size(); i++){

		if(sig(outlayer[i].sum(mid)) > 0.5){
			intout.push_back(1);
		}
		else{
			intout.push_back(0);
		}
	}

	a->resize(intout.size(), 0);
	b->resize(intout.size(), 0);
	c->resize(intout.size(), 0);
	d->resize(intout.size(), 0);

	for(i=0; i< intout.size(); i++){

		if(intout[i]==1 && exout[i] == 1){
			(a->at(i))++;
		}
		else if(intout[i]==1 && exout[i] == 0){
			(b->at(i))++;
		}
		else if(intout[i]==0 && exout[i] == 1){
			(c->at(i))++;
		}
		else if(intout[i]==0 && exout[i] == 0){
			(d->at(i))++;
		}
	}
}

void neuronet::add(std::vector<double> weights, double bias, std::string layer){

	neuron temp;

	temp.weights = weights;
	temp.bias = bias;

	if(layer.compare("hidden") == 0){
		hidlayer.push_back(temp);
	}
	else if(layer.compare("output") == 0){
		outlayer.push_back(temp);
	}

}

void neuronet::print(){
	int i, j;

	std::cout<< std::fixed;

	std::cout<< ni << " " << hidlayer.size() << " " << no << std::endl;

	for(i=0; i<hidlayer.size(); i++){
		std::cout<< std::setprecision(3) << hidlayer[i].bias;
		for(j=0; j<ni; j++){
			std::cout<< " " << std::setprecision(3) << hidlayer[i].weights[j];
		}
		std::cout<<std::endl;
	}

	for(i=0; i<no; i++){
		std::cout<< std::setprecision(3) << outlayer[i].bias;
		for(j=0; j<hidlayer.size(); j++){
			std::cout<< " " << std::setprecision(3) << outlayer[i].weights[j];
		}
		std::cout<<std::endl;
	}
}

double neuronet::neuron::sum(std::vector<double> inputs){
	int i;
	double result = 0;

	for(i=0; i<weights.size(); i++){

		result = result + weights[i]*inputs[i];
	}

	result = result - bias	;

	return result;
}