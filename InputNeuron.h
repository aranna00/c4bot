//
// Created by Aran on 31/03/2018.
//

#ifndef C4BOT_1_INPUT_H
#define C4BOT_1_INPUT_H


#include "Neuron.h"

class InputNeuron : public Neuron {
public:
    double getValue() override {
        return value;
    }

    void setValue(float valueIn) {
        value = valueIn;
    }
};


#endif //C4BOT_1_INPUT_H
