#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

double sigmoid(double x) {
	return 1.0f / (1.0f + exp(-x));
}

double relu(double x) {
	if (x < 0.0f) {
		return 0;
	}
	else return x;
}

struct Node {
	double input = 1.0, output= 1.0;
};

class Layer
{
public:
	
	int num_of_nodes = 0;
	std::string activation_type = "sigmoid";
	std::vector <Node> Nodes;


	Layer(int num_nodes=1, std::string activation = "sigmoid") {
		activation_type = activation;
		num_of_nodes = num_nodes;
		Node dummy;
		for (int i = 0; i < num_nodes; ++i) {
			Nodes.push_back(dummy);
		}
	}
	

	int get_num_nodes() { return num_of_nodes; }

	void use_activate_func() {
		for (unsigned int i = 0; i < Nodes.size(); ++i) {
			double op;
			if (activation_type == "relu") op = relu(Nodes[i].input);
			else op = sigmoid(Nodes[i].input);
			Nodes[i].output = op;
		}
	}

	void print() {
		//std::cout << "Number of nodes: " << num_of_nodes << '\n';
		std::cout << "Nodes		activations" << '\n';

		for (auto i = 0; i < Nodes.size(); ++i) {
			//std::cout << Nodes[i].input << '\t' << Nodes[i].output << '\n';
			std::cout << Nodes[i].output << '\n';
		}
	}
};

