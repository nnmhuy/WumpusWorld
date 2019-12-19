//
//  LogicalAgent.hpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#ifndef LogicalAgent_hpp
#define LogicalAgent_hpp

#include <stdio.h>
#include "Agent.hpp"

class LogicalAgent : public Agent {

public:
    LogicalAgent(Coordinate startCoordinate, int mapSize, Map *pMap) : Agent(startCoordinate, mapSize, pMap) {}
    void makeMove();
    bool informW(bool state, Coordinate x);
    bool informP(bool state, Coordinate x);
    bool informB(bool state, Coordinate x);
    bool informS(bool state, Coordinate x);
    bool informG(bool state, Coordinate x);
};

#endif /* LogicalAgent_hpp */
