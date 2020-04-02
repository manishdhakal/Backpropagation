#include <iostream>
#include "ANN.h"
#include <vector>

//THE NEURAL NETWORK IS USED TO TRAIN THE LOGIC GATES
int main() {

	ANN NeuralNetwork;
	std::vector< std::vector <double> > data = { 
		{0,1},
		{1,0},
		{0,0},
		{1,1}
	};
	std::vector< std::vector <double> > op = { {1},{1},{0},{0} };

	NeuralNetwork.add_layer(2);
	NeuralNetwork.add_layer(4, "relu");
	NeuralNetwork.add_layer(1, "sigmoid");
	NeuralNetwork.is_valid();
	NeuralNetwork.print();
	NeuralNetwork.fit(data, op, 0.1, 2000);
	std::vector< std::vector <double> >::iterator it;
	for (unsigned int i = 0; i < data.size(); i++) {
		auto it = data[i];
		std::vector<double> test_res = NeuralNetwork.predict(it);
		std::cout << "The output of XOR Gate with inputs: " << it[0] << "," << it[1] << '\n';
		for (unsigned int i = 0; i < test_res.size(); ++i)
			std::cout << round(test_res[i]) << '\n';
	}
	std::vector<double> test = { 1,1};
	

	NeuralNetwork.print();
	return 0;
}