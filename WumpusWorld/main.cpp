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
    map1.readMap("map1.txt");
    Logger::mFilename = "result.txt";
    output->println("hellow");
    LogicalAgent LA(map1.startPoint, map1.mapSize, &map1);
    return 0;
}
