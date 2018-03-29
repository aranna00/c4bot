//
// Created by aran on 29-3-2018.
//

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <array>
#include <iterator>
#include "Neuron.h"
#include "Network.h"

unsigned int countWordsInString(std::string const &str) {
    std::stringstream stream(str);
    return std::distance(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>());
}

void Network::generateFileFromNetwork() {

}

void Network::generateNetworkFromFile(std::string filePath) {
    inputs.emplace_back();
    inputs.emplace_back();
    inputs.emplace_back();
    inputs.emplace_back();

    outputs.emplace_back();
    outputs.emplace_back();
    outputs.emplace_back();
    outputs.emplace_back();

    std::ifstream inFile(filePath);
    std::string neuronCounterString;
    if (inFile.good()) {
        getline(inFile, neuronCounterString);
    }

    long layerCounter = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
    int neuronCounter = countWordsInString(neuronCounterString);


    for (int i = 0; i < layerCounter; ++i) {
        std::vector<Neuron> layer;
        for (int j = 0; j < neuronCounter; ++j) {
            Neuron neuron;
            layer.push_back(neuron);
        }
        layers.emplace_back(layer);
    }

    std::string line;
    int currentLayer = 0;
    // loop through lines in file to get layers
    while (inFile >> line) {
        std::stringstream ssLine(line);
        std::string synapseWeights;
        int currentStartNeuron = 0;
        // loop through neurons in line to get startNeuron
        while (ssLine >> synapseWeights) {
            std::replace(synapseWeights.begin(), synapseWeights.end(), ',', ' ');
            std::stringstream ssWeights(synapseWeights);
            int weight;
            int currentEndNeuron = 0;
            // loop through synapseWeights to get weight and endNeuron
            while (ssWeights >> weight) {
                Synapse synapse;
                synapse.weight = weight;
                if (currentLayer == 0) {
                    synapse.start = inputs[currentStartNeuron];
                    synapse.end = layers[0][currentEndNeuron];
                } else if (currentLayer == layers.size() - 1) {
                    synapse.start = layers[layers.size() - 1][currentStartNeuron];
                    synapse.end = outputs[currentEndNeuron];
                } else {
                    synapse.start = layers[currentLayer][currentStartNeuron];
                    synapse.end = layers[currentLayer][currentEndNeuron + 1];
                }
                currentEndNeuron++;
            }
            currentStartNeuron++;
        }
        currentLayer++;
    }

    inFile.close();
}
