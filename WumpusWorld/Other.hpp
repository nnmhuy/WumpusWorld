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
#include <fstream>
#include <string>
#include <iostream>
#include <string.h>
#include <stdlib.h>

const int MAX_MAP_SIZE = 12;
using namespace std;

struct Room {
    int W, P, B, S, G;
    // -1 unknown
    // 0 false
    // 1 true
    Room() {
        W = P = B = S = G = -1;
    }
    bool checkSafe() {
        if (W == 0 && P == 0) return true;
        return false;
    }
    void setFalse() {
        W = P = B = S = G = 0;
    }
};

struct Coordinate {
    int x, y;
    Coordinate() {
        x=0; y=0;
    }
    Coordinate(int x, int y) {
        this->x = x; this->y = y;
    }
    string stringify() {
//        char xS[5], yS[5];
//        itoa(x, xS, 10);
//        itoa(y, yS, 10);
//        return string(xS) + ", " + string(yS);
        return to_string(x) + ", " + to_string(y);
    }
    bool operator == (Coordinate const &obj){
        return x == obj.x && y == obj.y;
    }
};

#define output Logger::getLogger()
class Logger{
    static ofstream out;
    static Logger* mThis;
    Logger(){}
    Logger& operator=(const Logger&){ return *this; };
    Logger(const Logger&){};
public:
    static string mFilename;
    static string inputFilename;
    void println(string message) {
        out << message << "\n";
    }
    void print(string message) {
        out << message;
    }
    static Logger* getLogger();
};

double randDouble();

#endif /* Other_hpp */
