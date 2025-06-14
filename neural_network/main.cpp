#include<iostream>
#include "neuron.hpp"
#include "matrix.hpp"
#include "neural_net.hpp"
using namespace std;

void train(NeuralNet* nn, vector<double> input, vector<double> target, int epochs)
{
	for(int i = 0; i < epochs; i++)
	{
		auto x = nn->forward(input);
		nn->setCurrentTarget(input);
        	nn->set_errors();
		nn->back_prop(input, 0.01);
		if(i == 9)
		{
			for(auto a: x)
				cout << a << " ";
			cout << endl;
		}
	}
	for(auto x: nn->get_hist_data())
		cout << x << endl;
}

int main(void)
{
	NeuralNet *nn = new NeuralNet({3, 2, 3});
	for(int i = 0; i < nn->getNumLayers()-1; i++)
	{
		cout << "weight matrix "<< i << endl;
		nn->getWeight(i)->printToConsole();
		cout << "\n------------\n";
	}
	vector<double> input = {1, 0, 1};
	
	train(nn, input, input, 100);
}
