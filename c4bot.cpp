// c4bot.cpp
// Aswin van Woudenberg

#include "c4bot.h"
#include <sstream>

unsigned const n_trials = 1000;
unsigned const mc_match = 1;
unsigned const mc_other = 1;
std::random_device rd;
std::mt19937 mt(rd());

State mcTrial(const State &board) {
    State mcBoard = board;
    std::vector<Move> moves = getMoves(board);
    while (moves.size() > 0 && getWinner(board) == Player::None) {
        std::uniform_int_distribution<double> dist(0.0, moves.size());
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
    int highest = -1 * n_trials * (mc_match + mc_other);
    Move ite = getMoves(board)[0];
    for (int y = 5; y >= 0; --y) {
        for (int x = 0; x < 7; ++x) {
            if (
                    (y == 5 || board[y + 1][x] != Player::None)
                    && (scores[y][x] > highest && board[y][x] == Player::None)
                    ) {
                highest = scores[y][x];
                ite = x;
            }
        }
    }

    for (int y = 0; y < 6; ++y) {
        for (int x = 0; x < 7; ++x) {
            if (board[y][x] != Player::None) {
                std::cerr << board[y][x] << "\t";
            } else {
                std::cerr << scores[y][x] << "\t";
            }
        }
        std::cerr << std::endl;
    }
    std::cerr << std::endl;
    std::cerr << std::endl;


    return ite;
}

Move mcMove(const State &board, const Player &player) {
    std::array<std::array<int, 7>, 6> scores = {{{0}}};
    for (unsigned int i = 0; i < n_trials; ++i) {
        State completedBoard = mcTrial(board);
        mcUpdateScores(scores, completedBoard, player);
    }
    return getBestMove(scores, board);
}

void C4Bot::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<std::string> command = split(line, ' ');
        if (command[0] == "settings") {
            setting(command[1], command[2]);
        } else if (command[0] == "update" && command[1] == "game") {
            update(command[2], command[3]);
        } else if (command[0] == "action" && command[1] == "move") {
            move(std::stoi(command[2]));
        } else {
            std::cerr << "Unknown command: " << line << std::endl;
        }
    }
}

void C4Bot::move(int timeout) {
    Player player;
    if (your_botid == 0) {
        player = Player::X;
    } else {
        player = Player::O;
    }
    // Do something more intelligent here instead of returning a random move
//	std::vector<Move> moves = getMoves(state);
//	std::cout << "place_disc " << *select_randomly(moves.begin(), moves.end()) << std::endl;
    std::cout << "place_disc " << mcMove(state, player) << std::endl;
}

void C4Bot::update(std::string &key, std::string &value) {
    if (key == "round") {
        round = std::stoi(value);
    } else if (key == "field") {
        int row = 0;
        int col = 0;
        std::vector<std::string> fields = split(value, ',');
        for (std::string &field : fields) {
            if (field == "0") {
                state[row][col] = Player::X;
            } else if (field == "1") {
                state[row][col] = Player::O;
            } else {
                state[row][col] = Player::None;
            }
            col++;
            if (col == 7) {
                row++;
                col = 0;
            }
        }
    }
}

void C4Bot::setting(std::string &key, std::string &value) {
    if (key == "timebank") {
        timebank = std::stoi(value);
    } else if (key == "time_per_move") {
        time_per_move = std::stoi(value);
    } else if (key == "player_names") {
        std::vector<std::string> names = split(value, ',');
        player_names[0] = names[0];
        player_names[1] = names[1];
    } else if (key == "your_bot") {
        your_bot = value;
    } else if (key == "your_botid") {
        your_botid = std::stoi(value);
    } else if (key == "field_columns") {
        field_columns = std::stoi(value);
    } else if (key == "field_rows") {
        field_rows = std::stoi(value);
    }
}

std::vector<std::string> C4Bot::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

