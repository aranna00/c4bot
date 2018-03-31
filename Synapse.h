//
// Created by aran on 29-3-2018.
//

#ifndef C4BOT_1_SYNAPSE_H
#define C4BOT_1_SYNAPSE_H


#include "Neuron.h"

struct Neuron;

struct Synapse {
    Neuron *start;
    Neuron *end;
    double weight;
};


#endif //C4BOT_1_SYNAPSE_H
