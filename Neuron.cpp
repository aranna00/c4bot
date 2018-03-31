//
// Created by aran on 29-3-2018.
//
#include <cmath>
#include <iostream>
#include "Neuron.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double Neuron::getValue() {
    if (value == 0) {
        double tempVal = 0;
        for (Synapse *synIn : inBound) {
            tempVal += synIn->weight * synIn->start->getValue();
        }

//        value = atan(M_PI*tempVal/2)*2/M_PI;
//        value = atan(tempVal);
//        value = 1/(1+exp(-tempVal));
//        value = 1/sqrt(1+pow(tempVal,2));
//        value = erf(sqrt(M_PI)*tempVal/2);
//        value = tanh(tempVal);
        value = tempVal / (1 + abs(tempVal));
        std::cerr << value << std::endl;
    }

    return value;
}
