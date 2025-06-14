#ifndef _NEURAL_NET_HPP_
#define _NEURAL_NET_HPP_

#include<iostream>
#include<vector>
#include "matrix.hpp"
#include "neuron.hpp"
#include "layer.hpp"

using namespace std;

class NeuralNet
{
	public:
		NeuralNet(vector<int> topology);
		int getNumLayers();
		Matrix *getWeight(int i); //after ith layer
		void setCurrentInput(vector<double> input );
		vector<double> forward( vector<double> input );
		void back_prop(vector<double> answer, double alpha);
		vector<double> get_hist_data() { return this-> historicalErrors; };
		void set_errors();
		double getTotalError() { return this->error; };
		vector<double> getErrors() { return this->errors; };
		void setCurrentTarget(vector<double> target);

		
	private:
		vector<int> topology; // len = len(topology)
		int numLayers;
		vector<double> input;
		vector<Layer *> layers; //len = len(topology)
		vector<Matrix *> weights; //len = len(topology) - 1
		vector<double> target;
		double error;
		vector<double> errors;
		vector<double> historicalErrors;
};

#endif
