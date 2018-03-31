//
// Created by aran on 29-3-2018.
//

#ifndef C4BOT_1_NEURON_H
#define C4BOT_1_NEURON_H


#include <vector>
#include "Synapse.h"

struct Synapse;

struct Neuron {
    double value = 0;
    std::vector<Synapse *> inBound;
    std::vector<Synapse *> outBound;

public:
    virtual double getValue();
};


#endif //C4BOT_1_NEURON_H
