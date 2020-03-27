#pragma once
#include <map>
#include <iostream>
#include <math.h>
#include <vector>
#include <iterator>
#include "Layer.h"


struct Synapses {
	int layer, initial_node, final_node;

	bool operator <(const Synapses& rhs) const
	{
		if(layer != rhs.layer)
			return layer < rhs.layer;
		else {
			if (initial_node != rhs.initial_node)
				return initial_node < rhs.initial_node;
			else return final_node < rhs.final_node;
		}
	}
};

class ANN
{

public:
	std::map <Synapses, double> Weights;
	std::vector <Layer> Layers;
	Layer OutputLayer;
	int input_size = 0;

	//ANN(int input_layer_nodes) {
	//	Layer op_layer(1);
	//	OutputLayer = op_layer;
	//	OutputLayer.add_nodes(1);
	//}

	void updates_synapses() {
		Weights.clear();
		for (auto i = 0; i <= Layers.size(); ++i) {
			//for(unsigned int j = 0; j <)
		}
	}
	
	void add_layer(int num_nodes) {
		if (Layers.size() >= 1) {
			auto last_layer_size = Layers.back().get_num_nodes();
			for (int i = 0; i < last_layer_size; ++i) {
				for (int j = 0; j < num_nodes; ++j) {
					Synapses a = { int(Layers.size()) - 1, i, j };
					Weights.insert({a, 1.0f});
				}
			}
		}
		Layer dummy(num_nodes);
		if (Layers.size() == 0) {
			input_size = num_nodes;
			dummy.input_layer = true;
		}
		Layers.push_back(dummy);
	}


	void print() {
		std::cout << "Number of Layers : " << Layers.size() << '\n';
		std::cout << "Weights:\n";
		//Layers;
		/*for (auto it = Weights.begin(); it != Weights.end(); ++it) {
			std::cout << '{ ' << it->first.layer << ' , ' << it->first.initial_node << ' , ' << it->first.final_node << ' }' << " -> " << it->second << '\n';
		}*/

		for (auto i = 0; i < Layers.size(); ++i) {
			Layers[i].print();
		}
			
	}

	void fit(std::vector< std::vector <double> > input, std::vector<double> output,float learning_rate=0.01,  unsigned int epochs = 100) {
		std::cout << " Input size :\t" << input.size() << '\n';
		if (input_size != input[0].size() && Layers.back().Nodes.size() != output.size() ) {
			std::cout << "Input size || Output size is  invalid \n";
			return;
		}
		for (auto m = 0; m < input.size(); ++m) {
			for (auto n = 0; n < input[m].size(); ++n) {
				
				Layers[0].Nodes[n].input = input[m][n];
				Layers[0].Nodes[n].output = input[m][n];
			}

			for (auto l = 1; l < Layers.size(); ++l) {

				auto curr_layer = Layers[l];
				auto prev_layer = Layers[l - 1];

				for (auto j = 0; j < curr_layer.Nodes.size(); ++j) {

					double temp_sum = 0.0f;
					for (auto i = 0; i < prev_layer.Nodes.size(); ++i) {
						Synapses a = { l - 1, i, j };
						temp_sum += prev_layer.Nodes[i].output * Weights[a];
					}
					Layers[l].Nodes[j].input = temp_sum;
					Layers[l].use_activate_func();
				}
			}

			print();
		}


	}
};

