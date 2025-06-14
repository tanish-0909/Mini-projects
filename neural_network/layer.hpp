#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include<iostream>
#include<vector>
#include "neuron.hpp"
#include "matrix.hpp"

using namespace std;
class Layer
{
	public:
		Layer(int size);
		int getSize() {return this->size;};
		vector<double> getValues();
		vector<double> getActivatedValues();
		vector<double> getDerivedValues();
		void setValues(vector<double> values);
		vector<double> multiplyFirstWeights(Matrix *Wmat);
		vector<double> multiplyWeights(Matrix *Wmat);
		Matrix *matrixifyVals();
		Matrix *matrixifyActivatedVals();
		Matrix *matrixifyDerivedVals();
		void setVal(int i, double val)
		{
			this->neurons[i]->setVal(val);
		};
		vector <Neuron *> getNeurons() {
			return this-> neurons;
		};

	private:
		int size;

		vector<Neuron *> neurons;
		//void setValues(vector<double> values);
		//vector<double> multiplyWeights(Matrix *Wmat);
};

#endif
