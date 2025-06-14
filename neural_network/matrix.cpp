#include<iostream>
#include "matrix.hpp"
#include<vector>
#include<random>

Matrix::Matrix(int numRows, int numCols, bool isRandom)
{
	this->numRows = numRows;
	this->numCols = numCols;
	this->isRandom = isRandom;

	for(int i = 0; i < numRows; i++)
	{
		vector<double> colVals;
		for(int j = 0; j < numCols; j++)
		{
			double r = 0.0;
			if(isRandom) {
				r = this->generateRandomNumber();
			}
			colVals.push_back(r);

		}
		this->values.push_back(colVals);
	}
}

double Matrix::generateRandomNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);

	return dis(gen);
}

void Matrix::printToConsole(){
	for(auto colVec: this->values){
		for(auto r: colVec)
			cout << r << "\t";
		cout << endl;
	}
}

void Matrix::setValue(int r, int c, double v)
{
	this->values[r][c] = v;	
}	

double Matrix::getValue(int r, int c)
{
	return this->values[r][c];
}

Matrix *Matrix::transpose(){
	Matrix *mT = new Matrix(this->numCols, this->numRows, false);
	for(int i = 0; i < this->numRows; i++)
	{
		for(int j = 0; j < this->numCols; j++)
		{
			mT->setValue(j, i, this->values[i][j]);
		}
	}
	return mT;
}
