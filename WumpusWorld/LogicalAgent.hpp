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
    void makeMove();
    void informW(bool state, int x, int y);
    void informP(bool state, int x, int y);
    void informB(bool state, int x, int y);
    void informS(bool state, int x, int y);
    void informG(bool state, int x, int y);
};

#endif /* LogicalAgent_hpp */
