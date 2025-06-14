#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include <iostream>

using namespace std;

class Neuron
{
	public:

		//constructor 
		Neuron(double val);
		
		void setVal(double v);	
		void activate(); // Fast sigmoid activation
		//f(x) = x / (1 + |x|) defn of fast sigmoid
		void ReLU();
		//derivative for fast sigmoid function 
		//f'(x) = f(x) * (1 - x)
		void derive();
		void deriveRelu();

		//sone getter functions
		double getVal();
		double getActivatedVal();
		double getDerivedVal();


	private:
		double val;
		double activatedVal;
		double derivedVal; // approx derivate of the activatedVal
		
};

#endif
