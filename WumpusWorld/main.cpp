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
    Map map1;
    map1.readMap("map5.txt");
    Logger::mFilename = "logical-result5.txt";
    map1.readMap("map.txt");
    Logger::inputFilename = "map.txt";
    Logger::mFilename = "result.txt";
//    LogicalAgent la(map1.startPoint, map1.mapSize, &map1);
//    la.startAgent();
////    char c;
//    while (la.isEnd() == false) {
//        la.draw();
//        cin.get();
//        la.makeMove();
//    }
//    la.draw();

    QLearningAgent qa(map1.startPoint, map1.mapSize, &map1);
    qa.train();
    LogicalAgent la(map1.startPoint, map1.mapSize, &map1);
    while (qa.isEnd() == false) {
        qa.makeMove();
    }
    return 0;
}
