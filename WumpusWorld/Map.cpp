//
//  Map.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "Map.hpp"

void Map::readMap(string filename) {
    ifstream in;
    in.open(filename.c_str());
    string s;
    in>>mapSize;
    int j;
    for (int i=mapSize; i>=1; i--) {
        in>>s;
        j = 1;
        m[j][i].setFalse();
        for (int k=0; k<s.length(); k++) {
            switch (s[k]) {
            case '.':
                j++;
                m[j][i].setFalse();
                break;
            case 'A':
                startPoint.x = j;
                startPoint.y = i;
                break;
            case 'W':
                m[j][i].W = 1;
                break;
            case 'P':
                m[j][i].P = 1;
                break;
            case 'B':
                m[j][i].B = 1;
                break;
            case 'S':
                m[j][i].S = 1;
                break;
            case 'G':
                m[j][i].G = 1;
                break;
            }
        }
    }
    in.close();
}
