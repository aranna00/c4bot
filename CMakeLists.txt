cmake_minimum_required(VERSION 3.9)
project(c4bot_1_)

set(CMAKE_CXX_STANDARD 11)

add_executable(c4bot_1_
        c4.cpp
        c4.h

        c4BotMc.cpp
        c4BotMc.h

        c4botAB.cpp
        c4botAB.h

        c4bot.cpp
        c4bot.h
        main.cpp
        Makefile
        Synapse.cpp Synapse.h Neuron.cpp Neuron.h Network.cpp Network.h InputNeuron.h OutputNeuron.h)
