//
//  main.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include <iostream>
#include <string>
#include "Map.hpp"
#include "LogicalAgent.hpp"
#include "QLearningAgent.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    Map map1;
    map1.readMap("map1.txt");
    Logger::mFilename = "result2.txt";
    output->print("hellow");
    return 0;
}
