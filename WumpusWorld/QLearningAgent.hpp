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
#include "Agent.hpp"

#define SA pair<state, int>
#define State first
#define Action second

struct state {
    Coordinate x, y;
    int direction, moveLeft;
    bool b, s;
};

// State: x, y, direction, moveLeft, breeze, stench
// Action: 0_go, 1_turn_left, 2_turn_right, 3_shot, 4_exit

class QLearningAgent : public Agent {
    map <SA, double> qMatrix;
public:
    QLearningAgent(Coordinate startCoordinate, int mapSize, Map *pMap) : Agent(startCoordinate, mapSize, pMap) {
        initMatrix();
    }
    void initMatrix();
    void startAgent();
    void makeMove();
    void returnHome();
    void train();
};


#endif /* QLearningAgent_hpp */
