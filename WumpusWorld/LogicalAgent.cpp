//
//  LogicalAgent.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "LogicalAgent.hpp"


void LogicalAgent::makeMove() {

}
bool LogicalAgent::informB(bool state, Coordinate x) {
    Coordinate newPosition;
    if (state == true) {
        // check 4 adjacent exist Pit
        Coordinate unknownPosition(-1, -1);
        int countFalse=0;
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            if (m[newPosition.x][newPosition.y].P == 0)
                countFalse++;
            if (m[newPosition.x][newPosition.y].P == -1) {
                unknownPosition = newPosition;
            }
        }
        if (countFalse == 3 && validIndex(unknownPosition)) {
            string message = "Because 3 other adjacent Rooms of Room " + x.stringify()
            + "do not have pit";
            output->println(message);
            output->print("So, ");
            informP(true, unknownPosition);
        }
    }
    if (m[x.x][x.y].B != -1 || state == -1) return false;
    m[x.x][x.y].B = state;

    if (state) {
        string message = "Room " + x.stringify() + " has breeze";
        output->println(message);
    } else {
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informP(false, newPosition);
        }
    }
}
bool LogicalAgent::informS(bool state, Coordinate x) {
    Coordinate newPosition;
    if (state == true) {
        // check 4 adjacent exist Wumpus
        Coordinate unknownPosition(-1, -1);
        int countFalse=0;
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            if (m[newPosition.x][newPosition.y].W == 0)
                countFalse++;
            if (m[newPosition.x][newPosition.y].W == -1) {
                unknownPosition = newPosition;
            }
        }
        if (countFalse == 3 && validIndex(unknownPosition)) {
            string message = "Because 3 other adjacent Rooms of Room " + x.stringify()
            + "do not have Wumpus";
            output->println(message);
            output->print("So, ");
            informW(true, unknownPosition);
        }
    }
    if (m[x.x][x.y].S != -1 || state == -1) return false;
    m[x.x][x.y].S = state;

    if (state) {
        string message = "Room " + x.stringify() + " has stench";
        output->println(message);
    } else {
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informW(false, newPosition);
        }
    }
}
bool LogicalAgent::informW(bool state, Coordinate x) {
    if (m[x.x][x.y].W != -1) return false;
    m[x.x][x.y].W = state;

    Coordinate newPosition;
    if (state) {
        string message = "Room " + x.stringify() + " has a Wumpus";
        output->println(message);
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informS(true, newPosition);
        }
    } else {
        string message = "Room " + x.stringify() + " does not have any Wumpus";
        output->println(message);
        if (m[x.x][x.y].P == 0) {
            message = "Room " + x.stringify() + " is safe";
            output->println(message);
        }
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informS(m[newPosition.x][newPosition.y].S, newPosition);
        }
    }
}
bool LogicalAgent::informP(bool state, Coordinate x) {
    if (m[x.x][x.y].P != -1) return false;
    m[x.x][x.y].P = state;

    Coordinate newPosition;
    if (state) {
        string message = "Room " + x.stringify() + " has a pit";
        output->println(message);
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informB(true, newPosition);
        }
    } else {
        string message = "Room " + x.stringify() + " does not have any pit";
        output->println(message);
        if (m[x.x][x.y].W == 0) {
            message = "Room " + x.stringify() + " is safe";
            output->println(message);
        }
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informB(m[newPosition.x][newPosition.y].B, newPosition);
        }
    }
}
bool LogicalAgent::informG(bool state, Coordinate x) {
    if (m[x.x][x.y].G != -1) return false;
    m[x.x][x.y].G = state;
    if (state) {
        string message = "Yay, There is gold in Room " + x.stringify();
        output->print(message);
        message = "The current point is " + point;
        output->print(message);
    }
}
