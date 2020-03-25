#pragma once
#include <map>
#include <iostream>
#include <math.h>
#include <vector>
//#include <iterator>
#include "Layer.h"


struct Synapses {
	int layer, initial_node, final_node;
};

class ANN
{

public:
	std::map <Synapses, float> Weights;
	std::vector <Layer> Layers;
	//int output_nodes=1;
	Layer OutputLayer;

	//ANN(int input_layer_nodes) {
	//	Layer op_layer(1);
	//	OutputLayer = op_layer;
	//	//OutputLayer.add_nodes(1);
	//}

	void updates_synapses() {
		Weights.clear();
		for (unsigned int i = 0; i <= Layers.size(); ++i) {
			//for(unsigned int j = 0; j <)
		}
	}
	
	void add_layer(int num_nodes) {
		Layer dummy(num_nodes);
		//dummy.add_nodes(num_nodes);
		Layers.push_back(dummy);
		if (Layers.size() > 1) {
			int last_layer_size = Layers.back().get_num_nodes();
			for (int i = 0; i < last_layer_size; ++i) {
				for (int j = 0; j < num_nodes; ++j) {
					Synapses a = { int(Layers.size()) - 2, i, j };
					Weights.insert(std::pair<Synapses, float>(a, 1.0f));
				}
			}
		}
	}


	void print() {
		std::cout << "Number of Layers" << Layers.size() << '\n';
		std::cout << "Weights\n";
		for (auto it = Weights.begin(); it != Weights.end(); ++it) {
			std::cout << '{' << it->first.layer << ' , ' << it->first.initial_node << ' , ' << it->first.final_node << ' }' << " -> " << it->second;
		}
	}
};

