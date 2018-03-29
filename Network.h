//
// Created by aran on 29-3-2018.
//

#ifndef C4BOT_1_NETWORK_H
#define C4BOT_1_NETWORK_H


#include <vector>
#include <string>
#include "Neuron.h"
#include "Synapse.h"

class Network {
    std::vector<Neuron *> inputs;
    std::vector<Neuron *> outputs;
    std::vector<std::vector<Neuron *>> layers;

    void generateFileFromNetwork();

public:
    void generateNetworkFromFile(std::string filePath);
};


#endif //C4BOT_1_NETWORK_H
