//
//  Room.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "Other.hpp"

string Logger::mFilename = "result.txt";
Logger* Logger::mThis = NULL;
ofstream Logger::out;
Logger* Logger::getLogger(){
    if (mThis == NULL){
        mThis = new Logger();
        out.open(mFilename.c_str(), ios::out);
    }
    return mThis;
}
