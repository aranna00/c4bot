//
// Created by aran on 22-3-2018.
//

#ifndef C4BOT_1_C4BOTMC_H
#define C4BOT_1_C4BOTMC_H

#include <random>
#include "c4.h"

State mcTrial(const State &board);
void mcUpdateScores(std::array<std::array<int, 7>, 6> &scores, const State &board, const Player &player);
Move getBestMove(const std::array<std::array<int, 7>, 6> &scores, const State &board);
Move mcMove(const State &board, const Player &player, int timeout);

#endif //C4BOT_1_C4BOTMC_H
