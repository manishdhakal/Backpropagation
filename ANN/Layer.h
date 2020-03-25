#pragma once
//#include "Node.h"
#include <vector>
#include <math.h>
#include <iostream>

float Sigmoid(float x) {
	float res = 1.0f / (1 + (float)exp(x));
	return res;
}

struct Node {
	float input, output;
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

	void add_nodes(int num) {
		num_of_nodes = num;
		Node dummy;
		for (int i = 0; i < num; ++i) {
			Nodes.push_back(dummy);
		}
	}

	int get_num_nodes() { return num_of_nodes; }

	void use_activate_func() {
		for (unsigned int i = 0; i < Nodes.size(); ++i) {
			Nodes[i].output = Sigmoid(Nodes[i].input);
		}
	}

	void print() {
		std::cout << "Number of nodes" << num_of_nodes << '\n';
		std::cout << "Nodes		x	 y" << '\n';

	}
};

