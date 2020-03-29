#pragma once
#include <map>
#include <iostream>
#include <math.h>
#include <vector>
#include "Layer.h"
#include <random>
#define BIAS 1.0f

// Sym: z -> input in neuron; a -> output of neuron; C -> Cost function; W -> weights
// Sym: delta -> dC/dz


double rand_wt_gen() {
	return static_cast <double> (rand()) / static_cast<double> (RAND_MAX / 2) - 1;
}

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

struct NeuronIndicator {
	int layer, index;

	bool operator < (const NeuronIndicator& rhs) const {
		if (layer != rhs.layer) return layer < rhs.layer;
		else return index < rhs.index;
	}
};

class ANN
{

public:
	std::map <Synapses, double> Weights;/* = {
		{{0,0,0}, -0.37901279211},
		{{0,0,1}, 0.11520505212},
		{{0,0,2}, 0.54512358213},
		{{0,1,0}, -0.02775569221},
		{{0,1,1}, -0.52161419},
		{{0,1,2}, -0.84486143},
		{{1,0,0}, -0.09770814311},
		{{1,1,0}, -0.99783149321},
		{{1,2,0}, 0.74709193331},
	};*/
	std::vector <Layer> Layers;
	int input_size = 0;

	/*ANN() {
		Layer l1(2);
		Layer l2(3);
		Layer l3(1);

		Layers.push_back(l1);
		Layers.push_back(l2);
		Layers.push_back(l3);
	}*/

	
	void add_layer(int num_nodes) {
		if (Layers.size() >= 1) {
			auto last_layer_size = Layers.back().get_num_nodes();
			for (int i = 0; i < last_layer_size; ++i) {
				for (int j = 0; j < num_nodes; ++j) {
					Synapses a = { int(Layers.size()) - 1, i, j };
					Weights[a] = rand_wt_gen();
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
		std::cout << "\nNumber of Layers : " << Layers.size() << '\n';
		std::cout << "Weights:\n";

		//Layers;
		for (auto it = Weights.begin(); it != Weights.end(); ++it) {
			std::cout << '{ ' << it->first.layer << ' , ' << it->first.initial_node << ' , ' << it->first.final_node << ' }' << " -> " << it->second << '\n';
		}

		/*for (auto i = 0; i < Layers.size(); ++i) {
			Layers[i].print();
		}*/
			
	}

	//Derivative of node output wrt input
	double da_dz(double z ) {
		return Sigmoid(z) * (1.0f - Sigmoid(z));
	}

	void fit(std::vector< std::vector <double> > input, std::vector< std::vector <double> > output,float learning_rate=0.1,  unsigned int epochs = 200) {
		//std::cout << " Input size :\t" << input.size() << '\n';
		if (input_size != input[0].size() && Layers.back().Nodes.size() != output[0].size() ) {
			std::cout << "Input size || Output size is  invalid \n";
			return;
		}
		if (input.size() != output.size()) {
			std::cout << "The number of ouput ane input iterations are not equal\n";
			return;
		}
		//print();
		for (unsigned int e = 0; e < epochs; ++e) {
			for (auto m = 0; m < input.size(); ++m) {
				for (auto n = 0; n < input[m].size(); ++n) {
					//std::cout << input[m][n] << '\n';
					Layers[0].Nodes[n].input = input[m][n];
					Layers[0].Nodes[n].output = input[m][n];
				}

				//Forward Feed here
				for (auto l = 1; l < Layers.size(); ++l) {

					auto curr_layer = Layers[l];
					auto prev_layer = Layers[l - 1];

					for (auto j = 0; j < curr_layer.Nodes.size(); ++j) {

						double temp_sum = BIAS;
						for (auto i = 0; i < prev_layer.Nodes.size(); ++i) {
							Synapses a = { l - 1, i, j };
							temp_sum += prev_layer.Nodes[i].output * Weights[a];
						}
						Layers[l].Nodes[j].input = temp_sum;
					}
					Layers[l].use_activate_func();
					//Layers[l].print();
				}
				//print();
				
				//BackPropagation here
				std::map<NeuronIndicator, double> dC_da;	//Derivatives of cost function wrt output of the node
				std::map<NeuronIndicator, double> dC_dz;	//Derivatives of cost function wrt input of the node
				std::map<Synapses, double> dC_dW;			//Derivatives of cost function wrt weights

				for (int i = Layers.size() - 1; i >= 0; --i) {
					auto temp_layer = Layers[i];
					for (int j = 0; j < temp_layer.Nodes.size(); ++j) {
						NeuronIndicator curr = { i,j };
						if (i == Layers.size()-1) {
							dC_da[curr] = temp_layer.Nodes[j].output - output[m][j];
							//std::cout << "Output Error:\n" << 0.5 * pow(temp_layer.Nodes[j].output - output[m][j], 2) << '\n';
						}
						else {
							double temp_dC_da = 0;
							for (int k = 0; k < Layers[i + 1].Nodes.size(); ++k) {
								Synapses syn = { i,j,k };
								NeuronIndicator nxt = { i + 1,k };
								temp_dC_da += Weights[syn] * dC_dz[nxt];
								dC_dW[syn] = temp_layer.Nodes[j].output * dC_dz[nxt];
							}
							dC_da[curr] = temp_dC_da;
						}
						dC_dz[curr] = da_dz(temp_layer.Nodes[j].input) * dC_da[curr];
						//std::cout << "delta:\t" << dC_dz[curr] << '\n';
					}
				}

				//Adjust the weights  here
				for (int i = 0; i < Layers.size() - 1; i++) {
					for (int j = 0; j < Layers[i].Nodes.size(); ++j) {
						for (int k = 0; k < Layers[i + 1].Nodes.size(); ++k) {
							Synapses a = { i,j,k };
							Weights[a] -= learning_rate * dC_dW[a];
							//std::cout << dC_dW[a] << '\t' << Weights[a] << '\n';
						}
					}
				}
				//print();
			}

		}
		//print();
	}

	std::vector<double> predict(std::vector<double> test_data) {

		for (int i = 0; i < test_data.size(); ++i) {
			Layers[0].Nodes[i].input = test_data[i];
			Layers[0].Nodes[i].output = test_data[i];
		}

		for (auto l = 1; l < Layers.size(); ++l) {

			auto curr_layer = Layers[l];
			auto prev_layer = Layers[l - 1];

			for (auto j = 0; j < curr_layer.Nodes.size(); ++j) {

				double temp_sum = BIAS;
				for (auto i = 0; i < prev_layer.Nodes.size(); ++i) {
					Synapses a = { l - 1, i, j };
					temp_sum += prev_layer.Nodes[i].output * Weights[a];
					
				}
				Layers[l].Nodes[j].input = temp_sum;

			}
			Layers[l].use_activate_func();
			//Layers[l].print();
		}
		auto op_layer = Layers.back();
		std::vector<double> ret;
		for (unsigned int i = 0; i < op_layer.Nodes.size(); ++i) {
			ret.push_back(op_layer.Nodes[i].output);
		}
		return ret;
	}
};

