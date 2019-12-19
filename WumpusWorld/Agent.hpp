//
//  Agent.hpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#ifndef Agent_hpp
#define Agent_hpp

#include <stdio.h>
#include <iostream>
#include "Other.hpp"
#include "Map.hpp"

using namespace std;

const int forwardX[4] = {-1, 0, 1, 0};
const int forwardY[4] = {0, 1 , 0, -1};

class Agent {
protected:
    Map *pMap;
    Coordinate p;
    int mapSize;
    int point, moveLeft;
    int currentDirection; // 0123 -> LURD
    Room m[MAX_MAP_SIZE + 1][MAX_MAP_SIZE + 1];
    bool visited[MAX_MAP_SIZE+1][MAX_MAP_SIZE+1];
public:
    Agent(Coordinate startCoordinate, int mapSize, Map *pMap);
    virtual void makeMove() = 0;
    Room go();
    Room enterRoom();
    Room goTo(Coordinate finalPoint);
    void shot();
    void turn(bool isLeft);
    bool validIndex(Coordinate x);
    bool isEnd() {
        if (moveLeft <= 0) return true;
        return false;
    }
};


#endif /* Agent_hpp */
