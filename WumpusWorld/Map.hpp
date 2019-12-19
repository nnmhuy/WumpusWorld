//
//  Map.hpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include "Other.hpp"

using namespace std;

class Map {
    Room m[MAX_MAP_SIZE + 1][MAX_MAP_SIZE + 1];
public:
    int mapSize;
    Coordinate startPoint;
    void readMap(string filename);
    void printMap();
    Room goToRoom(Coordinate p) {
        return m[p.x][p.y];
    }
    void takeGold(Coordinate p) {
        m[p.x][p.y].G = 0;
    }
    void shotRoom(Coordinate p) {
        m[p.x][p.y].W = 0;
    }
};

#endif /* Map_hpp */
