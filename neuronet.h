#include <iostream>
#include <string.h>
#include <string>
#include <vector>

class neuronet{
public:

	int ni;
	int nh;
	int no;

	class neuron{
	public:
		std::vector<double> weights;
		double bias;
		double sum(std::vector<double> inputs);
		double delta = 0;

	};

	std::vector<neuron> hidlayer;
	std::vector<neuron> outlayer;
	
	std::vector<double> inputs;
	std::vector<double> mid;
	std::vector<double> outputs;
	
	void add(std::vector<double> weights, double bias, std::string layer);
	void learning(std::vector<double> exin, std::vector<double> exout, double rate);
	void testing(std::vector<double> exin, std::vector<int> exout, std::vector<double>* a, std::vector<double>* b, std::vector<double>* c, std::vector<double>* d);
	void print();
	//neuronet(int in, int hid, int out);
};

double sig(double x);

double dsig(double x);