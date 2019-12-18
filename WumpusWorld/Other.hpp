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

const int MAX_MAP_SIZE = 10;
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
    void print(string message) {
        out << message << "\n";
    }
    static Logger* getLogger() {
        if (mThis == NULL){
            mThis = new Logger();
            out.open(mFilename.c_str(), ios::out);
        }
        return mThis;
    }
};

#endif /* Other_hpp */
