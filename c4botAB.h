//
// Created by aran on 22-3-2018.
//

#ifndef C4BOT_1_C4BOTAB_H
#define C4BOT_1_C4BOTAB_H

#include "c4.h"


struct AB{
    Move move;
    int score;
};
int eval(const State &board, const Player &maxPlayer);

int alphaBeta(const State &board, int ply, Player maxPlayer = Player::None, int min = -INT32_MAX, int max = INT32_MAX);

int negaMax(const State &board, int ply, Player player = Player::None, int min = -INT32_MAX, int max = INT32_MAX);

#endif //C4BOT_1_C4BOTAB_H
