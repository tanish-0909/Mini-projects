#include "layer.hpp"
#include<vector>

Layer::Layer(int size) { // constructor
	this->size = size;

	for(int i = 0; i < size; i++)
	{
		Neuron *n = new Neuron(0.00);
		this->neurons.push_back(n);
	}
}

void Layer::setValues(vector<double> val)
{
	if(this->size != int(val.size()))
	{
		cout << "mismatch in size of layer and values" << this->size << " v/s " << val.size() <<endl;
		return;
	}
	for(int i = 0; i < this->size; i++)
	{
		this->neurons[i]->setVal(val[i]);
//		cout << "setting value: " << this->neurons[i]->getVal();
	}
}

vector<double> Layer::multiplyFirstWeights(Matrix *Wmat)
{
	if(this->size != Wmat->getNumRows())
	{
		cout << "Mismatch in size of multiplication matrix: (" << Wmat->getNumRows() << ", " << Wmat->getNumCols() << ") and layer input: "<<this->size<<endl;
		return {};
	}
	vector<double> ans;
	for(int i = 0; i < Wmat->getNumCols(); i++)
	{
		double a = 0.0;
		for(int j = 0; j < this->size; j++)
		{
			a = a + Wmat->getValue(j, i) * this->neurons[j]->getVal();
		}
        //      cout << "a: " <<a << endl;
                ans.push_back(a);
        }
        return ans;
}

vector<double> Layer::multiplyWeights(Matrix *Wmat)
{

	if(this->size != Wmat->getNumRows())
	{
		cout << "Mismatch in size of multiplication matrix: (" << Wmat->getNumRows() << ", " << Wmat->getNumCols() << ") and layer input: "<<this->size<<endl;
		return {};
	}
	vector<double> ans;
	for(int i = 0; i < Wmat->getNumCols(); i++)
	{
		double a = 0.0;
		for(int j = 0; j < this->size; j++)
		{
			a = a + Wmat->getValue(j, i) * this->neurons[j]->getActivatedVal();
		}
	//	cout << "a: " <<a << endl;
		ans.push_back(a);
	}
	return ans;
}

vector<double> Layer::getValues()
{
	vector<double> a;
	for(int i = 0; i < this->size; i++)
		a.push_back(this->neurons[i]->getVal());
	return a;
}

vector<double> Layer::getActivatedValues()
{
        vector<double> a;
        for(int i = 0; i < this->size; i++)
                a.push_back(this->neurons[i]->getActivatedVal());
        return a;
}

vector<double> Layer::getDerivedValues()
{
        vector<double> a;
        for(int i = 0; i < this->size; i++)
                a.push_back(this->neurons[i]->getDerivedVal());
        return a;
}

Matrix *Layer::matrixifyVals()
{
	Matrix *m = new Matrix(1, this->size, false);
	for(int i = 0; i < this->size; i++)
	{
		m->setValue(0, i, this->neurons[i]->getVal());
	}
	return m;
}

Matrix *Layer::matrixifyActivatedVals()
{
	Matrix *m = new Matrix(1, this->size, false);
	for(int i = 0; i < this->size; i++)
        {
                m->setValue(0, i, this->neurons[i]->getActivatedVal());
        }
	return m;
}

Matrix *Layer::matrixifyDerivedVals()
{
	Matrix *m = new Matrix(1, this->size, false);
	for(int i = 0; i < this->size; i++)
        {
                m->setValue(0, i, this->neurons[i]->getDerivedVal());
        }
	return m;
}

