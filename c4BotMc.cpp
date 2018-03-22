//
// Created by aran on 22-3-2018.
//

#include "c4BotMc.h"
#include "c4.h"


unsigned const n_trials = 1000;
unsigned const mc_match = 1;
unsigned const mc_other = 1;
std::random_device rd;
std::mt19937 mt(rd());

State mcTrial(const State &board) {
    State mcBoard = board;
    std::vector<Move> moves = getMoves(board);
    while (moves.size() > 0 && getWinner(board) == Player::None) {
        std::uniform_real_distribution<double> dist(0, moves.size());
        mcBoard = doMove(mcBoard, moves[dist(mt)]);
        moves = getMoves(mcBoard);
    }

    return mcBoard;
}

void mcUpdateScores(std::array<std::array<int, 7>, 6> &scores, const State &board, const Player &player) {
    if (getWinner(board) == Player::None) return;
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == Player::None) continue;
            if (board[y][x] == player) {
                scores[y][x] += getWinner(board) == player ? mc_match : -1 * mc_other;
            } else {
                scores[y][x] -= getWinner(board) == player ? mc_match : -1 * mc_other;
            }
        }
    }
}

Move getBestMove(const std::array<std::array<int, 7>, 6> &scores, const State &board) {
    int highest = INT32_MIN;
    Move ite = getMoves(board)[0];
    for (int y = 5; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            if ((y == 5 || board[y + 1][x] != Player::None) &&
                (scores[y][x] > highest && board[y][x] == Player::None)) {
                highest = scores[y][x];
                ite = x;
            }
        }
    }
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] != Player::None) {
            }
        }
    }

    return ite;
}

static double diffclock(clock_t clock1, clock_t clock2) {
    double diffticks = clock1 - clock2;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
    return abs(diffms);
}

Move mcMove(const State &board, const Player &player, int timeout) {
    std::array<std::array<int, 7>, 6> scores = {{{0}}};
    clock_t clock1 = clock();
    clock_t clock2 = clock();
    int simsRun = 0;
    while (diffclock(clock1, clock2) < timeout * .9) {
        State completedBoard = mcTrial(board);
        mcUpdateScores(scores, completedBoard, player);
        simsRun++;
        clock2 = clock();
        std::cerr << diffclock(clock1, clock2) << std::endl;
    }
    std::cerr << simsRun << std::endl;
    std::cerr << timeout << std::endl << std::endl;

    return getBestMove(scores, board);
}
