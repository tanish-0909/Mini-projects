#include<iostream>
#include<vector>
#include "neural_net.hpp"
#include "matrix.hpp"
#include "neuron.hpp"
#include "layer.hpp"

using namespace std;

int NeuralNet::getNumLayers()
{
	return this->numLayers;
}

Matrix *NeuralNet::getWeight(int i)
{
	if(i >= this->numLayers-1)
	{
		cout << " FUCK Invalid input\n";
		Matrix *m = new Matrix(0, 0, true);
		return m;
	}
	return this->weights[i];
}

NeuralNet::NeuralNet(vector<int> topology)
{
	this->numLayers = topology.size();
	this->topology = topology;

	//make the layers
	for(int i = 0; i < this->numLayers; i++)
	{
		Layer *l = new Layer(topology[i]);
		this->layers.push_back(l);
	}
	
	//make the weight matrices for propagation
	
	for(int i = 0; i < this->numLayers - 1; i++)
	{
		Matrix *m = new Matrix(topology[i], topology[i+1], true);
		this->weights.push_back(m);
	}
}

vector<double> NeuralNet::forward(vector<double> input)
{
	//set the first layer to input values
	this->setCurrentInput(input);
	vector<double> a = this->layers[0]->multiplyFirstWeights(this->weights[0]);
        this->layers[1]->setValues(a);
	//now calculate the next vector using matrix multiplication
	for(int i = 1; i < this->numLayers - 1; i++)
	{
		vector<double> a = this->layers[i]->multiplyWeights(this->weights[i]);
		this->layers[i+1]->setValues(a);
	}
	vector<double> ans = this->layers[this->numLayers - 1]->getActivatedValues();
       	return ans;
}

void NeuralNet::setCurrentInput(vector<double> input)
{
	this->input = input;
	this->layers[0]->setValues(input);
}

void NeuralNet::setCurrentTarget(vector<double> target)
{
	this->target = target;
	this->errors = vector<double>(int(target.size())); 
}

void NeuralNet::back_prop(vector<double> ans, double alpha)
{
	this->setCurrentTarget(ans);
	this->set_errors();
	vector<vector<double>> deltas(this->numLayers);
	vector<double> g;
	Layer *last_layer = this->layers[this->numLayers-1];
	vector<double> a = last_layer->getDerivedValues();
	for(int i = 0; i < int(ans.size()); i++)
	{
		g.push_back(a[i]*this->errors[i]);
//		cout << g[i] << " ";
	}
//	cout << endl;

	int n = this->numLayers;
	deltas[n-1] = g;
//	cout << "hi0\n";
	for(int l = n - 2; l > 0; l--)
	{
//		cout << "l: " << l << endl;
		Layer* current = this->layers[l];
        	Layer* next = this->layers[l + 1];
        	vector<Neuron*> currentNeurons = current->getNeurons();
        	vector<Neuron*> nextNeurons = next->getNeurons();

        	vector<double> newGi = current->getDerivedValues();
//		cout << "hi1\n";
		Matrix *Wnext = this->getWeight(l-1);
		for(int i = 0; i < int(current ->getSize()); i++)
		{
			double error = 0.0;
			for(int j = 0; j < int(next->getSize()); j++)
			{
				error += Wnext->getValue(j, i) * g[j];
			}
//			cout << "error: " << error << endl;
			newGi[i] *= error; 
		}
		deltas[l] = newGi;
	}

//	cout << "hi2\n";

	for(int l = 1; l <= n-1; l++)
	{
//		cout << "l: " << l << endl;
		Layer* curr = this->layers[l];
		Layer* prev = this->layers[l-1];

		vector<double> prev_activations = prev->getActivatedValues();
		Matrix *weights_now = this->getWeight(l-1);
//		cout << "weights_values: ";
//		cout << weights_now->getValue(1, 2);
//		cout << int(prev_activations.size()) << " " << curr->getSize() << endl;	
//		cout << "hi3\n";
		for(int i = 0; i < curr->getSize(); i++)
		{
			for(int j = 0; j < int(prev_activations.size()); j++)
			{
//				cout << "aaaaaaaa\n";
				double grad = deltas[l][i]* prev_activations[j];
//				cout << i << " " << j<< "bbbbbbbb\n";
				double updated = weights_now->getValue(j, i) - alpha * grad;
//				cout << "updated: " << updated << endl;
				weights_now->setValue(j, i, updated);
//				cout << "hi4\n";
			}
		}
	}
}

void NeuralNet::set_errors() 
{
	if(this->target.size() == 0){
		cout << "No error for this Neural Net, target size = 0\n";
	}
	else if(this->target.size() != this->layers[this->numLayers-1]->getValues().size())
	{
		cout << "Mismatch in target size and output size.\n";
		cout << "target size: " << target.size() << endl;
		cout << "neuron's output size: " <<  this->layers[this->numLayers-1]->getValues().size() <<endl;
	}
	else
	{
		this->error = 0.0;
		int outLayerIndex = this->numLayers-1;
		vector <Neuron *> outputNeurons = this->layers[outLayerIndex]-> getNeurons();
		for(int i = 0; i < int(target.size()); i++)
		{
			double tempErr = (outputNeurons[i]->getActivatedVal() - target[i]);
			//tempErr = tempErr * tempErr;
			this->errors[i] = tempErr;
			this->error += tempErr;
		}
		this->historicalErrors.push_back(this->error);
	}
}
