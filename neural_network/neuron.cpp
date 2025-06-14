#include "neuron.hpp"

//Constructor

Neuron::Neuron(double val) {
	this->val = val;
	activate();
	derive();

}

void Neuron::setVal(double Val) {
	this->val = Val;
	activate();
	derive();
}
double Neuron::getVal(){
	return this->val;
}
double Neuron::getActivatedVal(){
        return this->val;
}
double Neuron::getDerivedVal(){
        return this->val;
}

double myabs(double x) 
{
	if(x > 0) return x;
	else return -1 * x;
}

void Neuron::ReLU(){
	if(this->val >= 0)
		this->activatedVal = this->val;
	else
		this->activatedVal = 0;
}

void Neuron::activate() { //fast sigmoid
	this->activatedVal = this->val / (1 + myabs(this->val)); 
}

void Neuron:: derive() {
	this->derivedVal = this->activatedVal * (1 - this->activatedVal);
}

void Neuron::deriveRelu(){
	if(activatedVal > 0)
		this->derivedVal = 1;
	else
		this->derivedVal = 0;
}


