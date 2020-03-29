#include <iostream>
#include "ANN.h"
#include <vector>
#include <math.h>

//THE NEURAL NETWORK IS USED TO TRAIN THE LOGIC GATES
int main() {

	ANN NeuralNetwork;
	std::vector< std::vector <double> > data = { 
		{1,1},
		{0,1},
		{1,0},
		{0,0}
	};
	std::vector< std::vector <double> > op = { {0},{1},{1},{1} };

	NeuralNetwork.add_layer(2);
	NeuralNetwork.add_layer(3);
	NeuralNetwork.add_layer(1);
	//NeuralNetwork.print();
	NeuralNetwork.fit(data, op, 0.1, 1000);
	std::vector<double> test = { 1,1};
	std::vector<double> test_res = NeuralNetwork.predict(test);
	std::cout << "The output of NAND Gate with inputs: " << test[0] << "," << test[1] << '\n';
	for(unsigned int i=0; i< test_res.size(); ++i)
		std::cout << round(test_res[i]) << '\n';

	//NeuralNetwork.print();
	return 0;
}