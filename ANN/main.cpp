#include <iostream>
#include "ANN.h"
#include <map>
#include <vector>
#include <math.h>
int main() {

	ANN NeuralNetwork;
	std::vector< std::vector <double> > data = { 
		{ 4,5,55,7 },
		{5.2,0.3,0.4,0.001}
	};
	std::vector<double> op = { 1,2.1 };

	NeuralNetwork.add_layer(4);
	NeuralNetwork.add_layer(2);
	NeuralNetwork.add_layer(1);
	//NeuralNetwork.print();
	NeuralNetwork.fit(data, op);


	return 0;
}