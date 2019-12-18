//
//  Map.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "Map.hpp"

void Map::readMap(string filename) {
    mapSize = 10;
    freopen(filename.c_str(), "r", stdin);
    string s;
    int j;
    for (int i=10; i>=1; i--) {
        cin>>s;
        j = 1;
        m[i][j].setFalse();
        for (int k=0; k<s.length(); k++) {
            switch (s[k]) {
            case '.':
                j++;
                m[i][j].setFalse();
                break;
            case 'A':
                startPoint.x = i;
                startPoint.y = j;
                break;
            case 'W':
                m[i][j].W = true;
                break;
            case 'P':
                m[i][j].P = true;
                break;
            case 'B':
                m[i][j].B = true;
                break;
            case 'S':
                m[i][j].S = true;
                break;
            case 'G':
                m[i][j].G = true;
                break;
            }
        }
    }
    fclose(stdin);
}
