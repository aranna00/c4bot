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
        score += 1000000;
    } else if (getWinner(board) == otherPlayer(player)) {
        score -= 1000000;
    }

    // check 2 horizontal
    for (int y = 0; y < 6; ++y) {
        for (int x = 1; x < 7; ++x) {
            if (board[y][x] == board[y][x - 1]) {
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

                if (board[y][x] == player) {
                    score += 100 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 100 * multi;
                }
            }
        }
    }

    // check 3 horizontal
    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (board[y][x] == board[y][x + 1] && board[y][x] == board[y][x + 2]) {
                int multi = 0;

                // check if its possible to win from these stones
                if (x - 1 > 0 && board[y][x - 1] == Player::None) {
                    multi = 1;
                }
                if (x + 3 < 5 && board[y][x + 3] == Player::None) {
                    multi = 1;
                }

                if (board[y][x] == player) {
                    score += 10000 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 10000 * multi;
                }
            }
        }
    }

    // check 2 vertical
    for (int y = 5; y > 0; --y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == board[y - 1][x]) {
                int multi = 0;
                if (y - 2 > 0) {
                    if (board[y - 2][x] == Player::None) {
                        multi = 1;
                    }
                }

                if (board[y][x] == player) {
                    score += 100 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 100 * multi;
                }
            }
        }
    }

    // check 3 vertical
    for (int y = 5; y < 1; --y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] == board[y - 1][x] && board[y][x] == board[y - 2][x]) {
                int multi = 0;
                if (y - 3 > 0) {
                    if (board[y - 3][x] == Player::None) {
                        multi = 1;
                    }
                }

                if (board[y][x] == player) {
                    score += 10000 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 10000 * multi;
                }
            }
        }
    }

    // check 2 top left to bottom right
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (board[y][x] == board[y + 1][x + 1]) {
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
                if (board[y][x] == player) {
                    score += 100 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 100 * multi;
                }
            }
        }
    }

    // check 3 top left to bottom right
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (board[y][x] == board[y + 1][x + 1] && board[y][x] == board[y + 2][x + 2]) {
                int multi = 0;
                if (y - 1 > 0 && x - 1 > 0 && board[y - 1][x - 1] == Player::None) {
                    multi = 1;
                }
                if (board[y + 3][x + 3] == Player::None) {
                    multi = 1;
                }
                if (board[y][x] == player) {
                    score += 10000 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 10000 * multi;
                }
            }
        }
    }

    // check 2 bottom left to top right
    for (int y = 5; y > 3; --y) {
        for (int x = 0; x < 4; ++x) {
            if (board[y][x] == board[y - 1][x + 1]) {
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
                if (board[y][x] == player) {
                    score += 100 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 100 * multi;
                }
            }
        }
    }

    // check 3 bottom left to top right
    for (int y = 5; y > 3; --y) {
        for (int x = 0; x < 4; ++x) {
            if (board[y][x] == board[y - 1][x + 1] && board[y][x] == board[y - 2][x + 2]) {
                int multi = 0;
                if (y + 1 > 3 && x - 1 > 0 && board[y + 1][x - 1] == Player::None) {
                    multi = 1;
                }
                if (board[y - 3][x + 3] == Player::None) {
                    multi = 1;
                }

                if (board[y][x] == player) {
                    score += 10000 * multi;
                } else if (board[y][x] == otherPlayer(player)) {
                    score -= 10000 * multi;
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

        std::cerr << bestAB.score << std::endl;

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

        std::cerr << bestAB.score << std::endl;

        return bestAB.move;
    }
}