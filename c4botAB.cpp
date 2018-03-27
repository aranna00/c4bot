//
// Created by aran on 22-3-2018.
//

#include "c4botAB.h"

int maxPly = 7;

Player otherPlayer(Player player) {
    if (player == Player::O) {
        return Player::X;
    } else {
        return Player::O;
    }
}

int eval(const State &board, const Player &maxPlayer) {
    int score = 0;
    if (getWinner(board) == maxPlayer) {
        score = 1000000;
    } else if (getWinner(board) == otherPlayer(maxPlayer)) {
        score = -1000000;
    }


    // add individual scores
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == maxPlayer) {
                score++;
            } else if (board[y][x] == otherPlayer(maxPlayer)) {
                score--;
            }
            if (board[y][x] != Player::None) {
                continue;
            }
            if (y < 6 && x < 7) {
                if (board[y][x] == board[y][x - 1]) {
                    if (board[y][x] == board[y][x + 2]) {
                        int multi = 0;

                        // check if its possible to win from these stones
                        if (x - 1 > 0 && board[y][x - 1] == Player::None) {
                            multi = 1;
                        }
                        if (x + 3 < 5 && board[y][x + 3] == Player::None) {
                            multi = 1;
                        }

                        if (board[y][x] == maxPlayer) {
                            score += 10000 * multi;
                        } else if (board[y][x] == otherPlayer(maxPlayer)) {
                            score -= 10000 * multi;
                        }
                        goto checkVertical;
                    }
                    int multi = 0;
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

                    if (board[y][x] == maxPlayer) {
                        score += 100 * multi;
                    } else if (board[y][x] == otherPlayer(maxPlayer)) {
                        score -= 100 * multi;
                    }
                }
            }

            checkVertical:
            {
                if (y > 0 && x < 7) {
                    if (board[y][x] == board[y - 1][x]) {
                        if (board[y][x] == board[y - 2][x]) {
                            int multi = 0;
                            if (y - 3 > 0) {
                                if (board[y - 3][x] == Player::None) {
                                    multi = 1;
                                }
                            }

                            if (board[y][x] == maxPlayer) {
                                score += 10000 * multi;
                            } else if (board[y][x] == otherPlayer(maxPlayer)) {
                                score -= 10000 * multi;
                            }
                            goto checkTLtBR;
                        }
                        int multi = 0;
                        if (y - 2 > 0) {
                            if (board[y - 2][x] == Player::None) {
                                multi = 1;
                            }
                        }

                        if (board[y][x] == maxPlayer) {
                            score += 100 * multi;
                        } else if (board[y][x] == otherPlayer(maxPlayer)) {
                            score -= 100 * multi;
                        }
                    }
                }
            }
            // check top left to bottom right
            checkTLtBR:
            {
                if (y < 3 && x < 4) {
                    if (board[y][x] == board[y + 1][x + 1]) {
                        if (board[y][x] == board[y + 2][x + 2]) {
                            int multi = 0;
                            if (y - 1 > 0 && x - 1 > 0 && board[y - 1][x - 1] == Player::None) {
                                multi = 1;
                            }
                            if (board[y + 3][x + 3] == Player::None) {
                                multi = 1;
                            }
                            if (board[y][x] == maxPlayer) {
                                score += 10000 * multi;
                            } else if (board[y][x] == otherPlayer(maxPlayer)) {
                                score -= 10000 * multi;
                            }
                            goto checkBLtTR;
                        }
                        int multi = 0;
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
                        if (board[y][x] == maxPlayer) {
                            score += 100 * multi;
                        } else if (board[y][x] == otherPlayer(maxPlayer)) {
                            score -= 100 * multi;
                        }
                    }
                }
            }
            // check bottom left to top right
            checkBLtTR:
            {
                if (y > 3 && x < 4) {
                    if (board[y][x] == board[y - 1][x + 1]) {
                        if (board[y][x] == board[y - 2][x + 2]) {
                            int multi = 0;
                            if (y + 1 > 3 && x - 1 > 0 && board[y + 1][x - 1] == Player::None) {
                                multi = 1;
                            }
                            if (board[y - 3][x + 3] == Player::None) {
                                multi = 1;
                            }

                            if (board[y][x] == maxPlayer) {
                                score += 10000 * multi;
                            } else if (board[y][x] == otherPlayer(maxPlayer)) {
                                score -= 10000 * multi;
                            }
                            continue;
                        }
                        int multi = 0;
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
                        if (board[y][x] == maxPlayer) {
                            score += 100 * multi;
                        } else if (board[y][x] == otherPlayer(maxPlayer)) {
                            score -= 100 * multi;
                        }
                    }
                }
            }
        }
    }

    return score;
}

static double diffclock(clock_t clock1, clock_t clock2) {
    double diffticks = clock1 - clock2;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
    return abs(diffms);
}

int alphaBeta(const State &board, int ply, Player maxPlayer, int min, int max) {

    clock_t clock1 = clock();
    if (board[5][3] == Player::None) {
        return 3;
    }
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

        std::cerr << clock() - clock1 << std::endl;

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