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
#include <sys/stat.h>
#include <w32api/libloaderapi.h>
#include <zconf.h>
#include <w32api/fileapi.h>
#include <libgen.h>
#include "Neuron.h"
#include "Network.h"
#include "c4bot.h"

unsigned int countWordsInString(std::string const &str) {
    std::stringstream stream(str);
    return static_cast<unsigned int>(std::distance(std::istream_iterator<std::string>(stream),
                                                   std::istream_iterator<std::string>()));
}

void Network::generateFileFromNetwork(Network network) {
    std::ofstream OutFile;
    OutFile.open(network.orgFilename);
    for (auto &input : network.inputs) {
        for (int j = 0; j < input->outBound.size(); ++j) {

        }
    }
}

void Network::generateNetworkFromFile(std::string filePath) {
    orgFilename = basename(const_cast<char *>(filePath.c_str()));
    for (int k = 0; k < 42; ++k) {
        inputs.emplace_back(new InputNeuron);
    }
    for (int k = 0; k < 7; ++k) {
        outputs.emplace_back(new OutputNeuron);
    }

    std::ifstream inFile(filePath);
    std::string neuronCounterString;
    if (inFile.good()) {
        getline(inFile, neuronCounterString);
        getline(inFile, neuronCounterString);
    }

    inFile.seekg(0, std::ios::beg);
    long layerCounter = std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
    int neuronCounter = countWordsInString(neuronCounterString);


    for (int i = 0; i < layerCounter; ++i) {
        std::vector<Neuron *> layer;
        for (int j = 0; j < neuronCounter; ++j) {
            layer.emplace_back(new Neuron);
        }
        layers.emplace_back(layer);
    }

    inFile.seekg(0, std::ios::beg);
    std::string line;
    int currentLayer = 0;
    // loop through lines in file to get layers
    while (inFile && getline(inFile, line)) {
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        std::stringstream ssLine(line);
        std::string synapseWeights;
        int currentStartNeuron = 0;
        // loop through neurons in line to get startNeuron
        while (ssLine >> synapseWeights) {
            std::replace(synapseWeights.begin(), synapseWeights.end(), ',', ' ');
            std::stringstream ssWeights(synapseWeights);
            double weight;
            int currentEndNeuron = 0;
            // loop through synapseWeights to get weight and endNeuron
            while (ssWeights >> weight) {
                Synapse *synapse = new Synapse;
                synapse->weight = weight;
                if (currentLayer == 0) {
                    // attach neurons to synapses
                    synapse->start = inputs[currentStartNeuron];
                    synapse->end = layers[currentLayer][currentEndNeuron];

                    // attach synapses to neurons
                    inputs[currentStartNeuron]->outBound.push_back(synapse);
                    layers[currentLayer][currentEndNeuron]->inBound.push_back(synapse);
                } else if (currentLayer == layers.size()) {
                    synapse->start = layers[layers.size() - 1][currentStartNeuron];
                    synapse->end = outputs[currentEndNeuron];

                    layers[layers.size() - 1][currentStartNeuron]->outBound.push_back(synapse);
                    outputs[currentEndNeuron]->inBound.push_back(synapse);
                } else {
                    synapse->start = layers[currentLayer - 1][currentStartNeuron];
                    synapse->end = layers[currentLayer][currentEndNeuron];

                    layers[currentLayer - 1][currentStartNeuron]->outBound.push_back(synapse);
                    layers[currentLayer][currentEndNeuron]->inBound.push_back(synapse);
                }
                currentEndNeuron++;
            }
            currentStartNeuron++;
        }
        currentLayer++;
    }

    inFile.close();
}

int Network::getBestValue() {
    double best = -INFINITY;
    int bestMove = 0;
    for (int i = 0; i < outputs.size(); ++i) {
        if (best < outputs[i]->getValue()) {
            best = outputs[i]->getValue();
            bestMove = i;
        }
    }

    return bestMove;
}

void Network::setInputValues(State &board) {
    Player player = getCurrentPlayer(board);
    int neuronCounter = 0;
    for (int y = 5; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == Player::None) {
                inputs[neuronCounter]->value = 0;
            }
            if (board[y][x] == player) {
                inputs[neuronCounter]->value = 1;
            }
            if (board[y][x] == C4Bot::otherPlayer(player)) {
                inputs[neuronCounter]->value = -1;
            }
//            if (board[y][x] == Player::None) {
//                inputs[neuronCounter]->value = 1;
//            }
//            neuronCounter++;
//            if (board[y][x] == player) {
//                inputs[neuronCounter]->value = 1;
//            }
//            neuronCounter++;
//            if (board[y][x] == C4Bot::otherPlayer(player)) {
//                inputs[neuronCounter]->value = 1;
//            }
            neuronCounter++;
        }
    }
}

inline bool FileExists(const std::string &name) {
    struct stat buffer{};
    return (stat(name.c_str(), &buffer) == 0);
}

std::string Network::MakeRandomNetwork() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    std::string basePath = "Networks\\CurrentGen\\";
    CreateDirectory("Networks", NULL);
    CreateDirectory("Networks\\CurrentGen", NULL);
    int fileNumber = 0;
    std::string fileName = basePath + std::to_string(fileNumber) + ".annconf";
    while (FileExists(fileName)) {
        fileNumber++;
        fileName = basePath + std::to_string(fileNumber) + ".annconf";
    }
    std::ofstream OutFile;
    OutFile.open(fileName);
    int inputValues = 42;
    int hiddenLayers = 3;
    int nodesInLayer = 5;
    int outputValues = 7;

    // print input values
    for (int i = 0; i < inputValues; ++i) {
        for (int j = 0; j < nodesInLayer; ++j) {
            auto weight = dist(mt);
            OutFile << weight;
            if (j < 11)
                OutFile << ",";
        }
        OutFile << " ";
    }
    OutFile << "\n";

    for (int k = 0; k < hiddenLayers; ++k) {
        for (int i = 0; i < nodesInLayer; ++i) {
            for (int j = 0; j < nodesInLayer; ++j) {
                auto weight = dist(mt);
                OutFile << weight;
                if (j < 11)
                    OutFile << ",";
            }
            OutFile << " ";
        }
        OutFile << "\n";
    }

    for (int l = 0; l < nodesInLayer; ++l) {
        for (int i = 0; i < outputValues; ++i) {
            auto weight = dist(mt);
            OutFile << weight;
            if (i < 6)
                OutFile << ",";
        }
        OutFile << " ";
    }

    OutFile.close();

    return fileName;
}
