//
//  Room.hpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#ifndef Other_hpp
#define Other_hpp

#include <stdio.h>

const int MAX_MAP_SIZE = 10;

struct Room {
    bool W, P, B, S, G;
    Room() {
        W = P = B = S = G = true;
    }
};

struct Coordinate {
    int x, y;
};

#endif /* Other_hpp */
