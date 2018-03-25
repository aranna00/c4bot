//
// Created by aran on 22-3-2018.
//

#include "c4botAB.h"

int maxPly = 5;

Player otherPlayer(Player player) {
    if (player == Player::O) {
        return Player::X;
    } else {
        return Player::O;
    }
}

int eval(const State &board, const Player &player) {
    int score = 0;
    // add individual scores
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == player) {
                score++;
            } else if (board[y][x] == otherPlayer(player)) {
                score--;
            }
        }
    }

    // add winner scores
    if (getWinner(board) == player) {
        score += 1000;
    } else if (getWinner(board) == otherPlayer(player)) {
        score -= 1000;
    }

    // check horizontal
    for (int yH = 0; yH < 5; ++yH) {
        for (int xH = 0; xH < 6; ++xH) {
            if (board[yH][xH] == board[yH][xH+1]) {
                int mult = 1;
                if(xH+2<5) {
                    if (board[yH][xH] == board[yH][xH + 2]) {
                        mult = 10;
                    }
                }
                if (board[yH][xH] == player) {
                    score += 10*mult;
                } else if (board[yH][xH] == otherPlayer(player)) {
                    score -= 10*mult;
                }
            }
        }
    }

    // check vertical
    for (int xV = 0; xV < 5; ++xV) {
        for (int yV = 0; yV < 6; ++yV) {
            if (board[xV][yV] == board[xV][yV+1]) {
                int mult = 1;
                if(yV+2<6) {
                    if (board[xV][yV] == board[xV][yV + 2]) {
                        mult = 10;
                    }
                }
                if (board[xV][yV] == player) {
                    score += 10*mult;
                } else if (board[xV][yV] == otherPlayer(player)) {
                    score -= 10*mult;
                }
            }
        }
    }
    // check diagonals top-left to bottom-right
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 5; ++x) {
            if(board[y][x] == board[y+1][x+1]){
                
            }
        }
    }

    return score;
}

int alphaBeta(const State &board, int ply, Player maxPlayer, int min, int max) {
    AB bestAB;
    if (maxPlayer == Player::None) {
        maxPly = ply;
        maxPlayer = getCurrentPlayer(board);
    }

    std::vector<Move> moves = getMoves(board);

    if (moves.empty() || ply == 0) {
        int score = eval(board, maxPlayer);
        return score;
    }

    if (maxPlayer == getCurrentPlayer(board)) {
        bestAB.score = min;
        for (int move:getMoves(board)) {
            State newBoard = doMove(board, move);
            int evalScore = alphaBeta(newBoard, ply - 1, maxPlayer, bestAB.score, max);
            if (evalScore > bestAB.score) {
                bestAB.score = evalScore;
                bestAB.move = move;
            }
            if (bestAB.score > max) {
                return max;
            }
        }

        if (ply != maxPly)
            return bestAB.score;

        return bestAB.move;
    } else {
        bestAB.score = max;
        for (int move:getMoves(board)) {
            State newBoard = doMove(board, move);
            int evalScore = alphaBeta(newBoard, ply - 1, maxPlayer, min, bestAB.score);
            if (evalScore < bestAB.score) {
                bestAB.score = evalScore;
                bestAB.move = move;
            }
            if (bestAB.score < min) {
                return min;
            };
        }

        if (ply != maxPly)
            return bestAB.score;

        return bestAB.move;
    }
}