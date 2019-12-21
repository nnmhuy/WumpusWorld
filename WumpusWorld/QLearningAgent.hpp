//
//  QLearningAgent.hpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#ifndef QLearningAgent_hpp
#define QLearningAgent_hpp

#include <stdio.h>
#include <map>
#include <time.h>
#include <stdlib.h>
#include "Agent.hpp"
#include "Map.hpp"
#include "Other.hpp"

#define SA pair<State, int>
#define Sta first
#define Act second

const double epsilon = 0.2;
const double learning_rate = 0.5;
const double discount_factor = 0.9;
const double number_of_iteration = 100000;

struct State {
    Coordinate p;
    int direction, moveLeft;
    bool b, s;
    State() = default;
    State(Coordinate p, int direction, int moveLeft, bool b, bool s) {
        this->p = p;
        this->direction = direction;
        this->moveLeft = moveLeft;
        this->b = b;
        this->s = s;
    }
};

struct NextStateByAction {
    State s;
    bool isEnd;
    double reward;
    NextStateByAction() {
        reward = 0;
        isEnd = false;
    }
};

// State: x, y, direction, moveLeft, breeze, stench
// Action: 0_go, 1_turn_left, 2_turn_right, 3_shot, 4_exit


static double qMatrix[11][11][4][2][2][5][151];

class QLearningAgent : public Agent {
//    map <SA, double> qMatrix;
    Map cMap;
public:
    QLearningAgent(Coordinate startCoordinate, int mapSize, Map *pMap) : Agent(startCoordinate, mapSize, pMap) {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 11; ++j) {
                for (int k = 0; k < 4; ++k) {
//                    for (int r = 0; r <= 150; ++r)
                    for (int l = 0; l <= 1; ++l) {
                        for (int p = 0; p <= 1; ++p) {
                            for (int a = 0; a <= 5; ++a) {
                                for (int r = 0; r <= 150; ++r) {
                                    qMatrix[i][j][k][l][p][a][r] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    void startAgent();
    void makeMove();
    void returnHome();
    void train();
    void setQ(State s, int action, double value) {
        qMatrix[s.p.x][s.p.y][s.direction][s.b][s.s][action][s.moveLeft] = value;
    }
    double getQ(State s, int action) {
        return qMatrix[s.p.x][s.p.y][s.direction][s.b][s.s][action][s.moveLeft];
    }
    NextStateByAction getNextState(NextStateByAction inState, int action);
};


#endif /* QLearningAgent_hpp */
