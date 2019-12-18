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
    void readMap(string filename);
    void printMap();
    Room goToRoom(Coordinate p) {
        Room res = m[p.x][p.y];
        m[p.x][p.y].G = false;
        return res;
    }
    void shotRoom(Coordinate p) {
        m[p.x][p.y].W = false;
    }
};

#endif /* Map_hpp */
