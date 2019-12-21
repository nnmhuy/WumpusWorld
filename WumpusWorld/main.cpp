//
//  main.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include <iostream>
#include <string>
#include "LogicalAgent.hpp"
#include "QLearningAgent.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    int method = 1;
    string mapName;
    
    cout << "Please input map name: ";
    cin >> mapName;
    cout << "Please choose running algorithm (1.Logic, 2: Q Learning): ";
    cin >> method;
    
    Map map1;
    map1.readMap("map.txt");
    Logger::inputFilename = "map.txt";
    Logger::mFilename = "result.txt";
    
    if (method != 2) {
        LogicalAgent la(map1.startPoint, map1.mapSize, &map1);
        la.startAgent();
    //    char c;
        while (la.isEnd() == false) {
            la.draw();
            cin.get();
            la.makeMove();
        }
        la.draw();
    } else {
        QLearningAgent qa(map1.startPoint, map1.mapSize, &map1);
        qa.train();
        LogicalAgent la(map1.startPoint, map1.mapSize, &map1);
        while (qa.isEnd() == false) {
            qa.makeMove();
        }
    }
    return 0;
}
