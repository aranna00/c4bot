//
// Created by aran on 22-3-2018.
//

#include "c4botAB.h"

int maxPly = 7;
int evalCount = 0;

Player otherPlayer(Player player) {
    if (player == Player::O) {
        return Player::X;
    } else {
        return Player::O;
    }
}

int checkHorizontal(State board, int y, int x) {
    if (board[y][x] == board[y][x + 1]) {
        int multi = 0;
        if (board[y][x] == board[y][x + 2]) {

            // check if its possible to win from these stones
            if (x - 1 > 0 && board[y][x - 1] == Player::None) {
                multi = 1;
            }
            if (x + 3 < 5 && board[y][x + 3] == Player::None) {
                multi = 1;
            }

            return 10000 * multi;
        }
        // check if its possible to win from these stones
        if (x + 2 < 7 && board[y][x + 1] == Player::None && board[y][x + 2] == Player::None) {
            multi = 1;
        }
        if (x - 2 > 0 && x + 2 < 7 && board[y][x - 2] == Player::None && board[y][x + 1] == Player::None) {
            multi = 1;
        }
        if (x - 3 > 0 && board[y][x - 3] == Player::None && board[y][x - 2] == Player::None) {
            multi = 1;
        }

        return 100 * multi;
    }
}

int checkVertical(State board, int y, int x) {
    if (board[y][x] == board[y - 1][x]) {
        int multi = 0;
        if (board[y][x] == board[y - 2][x]) {
            if (y - 3 > 0) {
                if (board[y - 3][x] == Player::None) {
                    multi = 1;
                }
            }

            return 10000 * multi;
        }
        if (y - 2 > 0) {
            if (board[y - 2][x] == Player::None) {
                multi = 1;
            }
        }

        return 100 * multi;
    }
}

int checkTLtBR(State board, int y, int x) {
    if (board[y][x] == board[y + 1][x + 1]) {
        int multi = 0;
        if (board[y][x] == board[y + 2][x + 2]) {
            if (y - 1 > 0 && x - 1 > 0 && board[y - 1][x - 1] == Player::None) {
                multi = 1;
            }
            if (board[y + 3][x + 3] == Player::None) {
                multi = 1;
            }

            return 10000 * multi;
        }
        if (y - 2 > 0 && x - 2 > 0 && board[y - 2][x - 2] == Player::None &&
            board[y - 1][x - 1] == Player::None) {
            multi = 1;
        }
        if (y - 1 > 0 && x - 1 > 0 && board[y - 1][x - 1] == Player::None &&
            board[y + 2][x + 2] == Player::None) {
            multi = 1;
        }
        if (board[y + 2][x + 2] == Player::None && board[y + 3][x + 3] == Player::None) {
            multi = 1;
        }

        return 100 * multi;
    }
}

int checkBLtTR(State board, int y, int x) {
    if (board[y][x] == board[y - 1][x + 1]) {
        int multi = 0;
        if (board[y][x] == board[y - 2][x + 2]) {
            if (y + 1 > 3 && x - 1 > 0 && board[y + 1][x - 1] == Player::None) {
                multi = 1;
            }
            if (board[y - 3][x + 3] == Player::None) {
                multi = 1;
            }

            return 10000 * multi;
        }
        if (y + 2 > 3 && x - 2 > 0 && board[y + 2][x - 2] == Player::None &&
            board[y + 1][x - 1] == Player::None) {
            multi = 1;
        }
        if (y + 1 > 3 && x - 1 > 0 && board[y + 1][x - 1] == Player::None &&
            board[y - 2][x + 2] == Player::None) {
            multi = 1;
        }
        if (board[y - 2][x + 2] == Player::None && board[y - 3][x + 3] == Player::None) {
            multi = 1;
        }

        return 100 * multi;
    }
}

int eval(const State &board, const Player &maxPlayer) {
    evalCount++;
    int score = 0;
    if (getWinner(board) == maxPlayer) {
        score = 1000000;
    } else if (getWinner(board) == otherPlayer(maxPlayer)) {
        score = -1000000;
    }


    // add individual scores
    for (int y = 5; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == Player::None) {
                continue;
            }
            int multi = 0;

            if (board[y][x] == maxPlayer) {
                multi = 1;
            } else if (board[y][x] == otherPlayer(maxPlayer)) {
                multi = -1;
            }
            score += multi;

            if (x <= 4) {
                score += checkHorizontal(board, y, x) * multi;
            }
            if (y >= 3) {
                score += checkVertical(board, y, x) * multi;
            }

            if (x < 4) {
                if (y < 4) {
                    score += checkTLtBR(board, y, x) * multi;
                }

                if (y > 4) {
                    score += checkBLtTR(board, y, x) * multi;
                }
            }
        }
    }

    return score;
}

int alphaBeta(const State &board, int ply, Player maxPlayer, int min, int max) {
    if (board[5][3] == Player::None) {
        return 3;
    }

    if (maxPlayer == Player::None) {
        maxPly = ply;
        maxPlayer = getCurrentPlayer(board);
    }

    std::vector<Move> moves = getMoves(board);

    if (moves.empty() || ply == 0 || getWinner(board) != Player::None) {
        int score = eval(board, maxPlayer);
        return score;
    }

    AB bestAB;
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

        if (ply < maxPly) {
            return bestAB.score;
        }

        return bestAB.move;
    }
}

int negaMax(const State &board, int ply, Player maxPlayer, int min, int max) {
    if (board[5][3] == Player::None) {
        return 3;
    }

    if (maxPlayer == Player::None) {
        maxPly = ply;
        maxPlayer = getCurrentPlayer(board);
    }

    std::vector<Move> moves = getMoves(board);

    if (moves.empty() || ply == 0 || getWinner(board) != Player::None) {
        int score = eval(board, getCurrentPlayer(board));
        return score;
    }

    AB bestAB;
    for (Move move : moves) {
        int localScore = -negaMax(doMove(board, move), ply - 1, maxPlayer, -max, -min);
        if (bestAB.score < localScore) {
            bestAB.score = localScore;
            bestAB.move = move;
        }
        min = min > localScore ? min : localScore;
        if (min > max)break;
    }
}