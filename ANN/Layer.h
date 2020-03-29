#pragma once
#include <vector>
#include <math.h>
#include <iostream>

double Sigmoid(double x) {
	return 1.0f / (1.0f + exp(-x));
}

struct Node {
	double input = 1.0, output= 1.0;
};

class Layer
{
public:
	Layer(int num_nodes=1, bool is_input_layer = false) {
		input_layer = is_input_layer;
		num_of_nodes = num_nodes;
		Node dummy;
		for (int i = 0; i < num_nodes; ++i) {
			Nodes.push_back(dummy);
		}
	}
	int num_of_nodes = 0;
	bool input_layer;
	std::vector <Node> Nodes;

	int get_num_nodes() { return num_of_nodes; }

	void use_activate_func() {
		if (input_layer)
			for (unsigned int i = 0; i < Nodes.size(); ++i) {
				Nodes[i].output = Nodes[i].input;
			}
		else
			for (unsigned int i = 0; i < Nodes.size(); ++i) {
				auto op = Sigmoid(Nodes[i].input);
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

