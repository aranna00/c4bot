//
// Created by aran on 29-3-2018.
//

#ifndef C4BOT_1_NETWORK_H
#define C4BOT_1_NETWORK_H


#include <vector>
#include <string>
#include <random>
#include "Neuron.h"
#include "Synapse.h"
#include "InputNeuron.h"
#include "OutputNeuron.h"
#include "c4.h"

class Network {
    std::vector<InputNeuron *> inputs;
    std::vector<OutputNeuron *> outputs;
    std::vector<std::vector<Neuron *>> layers;

public:
    static std::string MakeRandomNetwork();

    static void generateFileFromNetwork(Network network);

    void setInputValues(State &board);
    void generateNetworkFromFile(std::string filePath);

    char *orgFilename;
    int getBestValue();
};


#endif //C4BOT_1_NETWORK_H
