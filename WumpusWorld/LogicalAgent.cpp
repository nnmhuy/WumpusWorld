//
//  LogicalAgent.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "LogicalAgent.hpp"

void LogicalAgent::getMoreKnowledge(Room r) {
    informB(r.B, p);
    informP(r.P, p);
    informS(r.S, p);
    informW(r.W, p);
}
void LogicalAgent::startAgent() {
    Room initRoom = enterRoom();
    string message = "We start at Room " + p.stringify();
    output->println(message);
    getMoreKnowledge(initRoom);
}
void LogicalAgent::makeMove() {
    //find the nearest safe room
    Coordinate qRoom[mapSize*mapSize*2], parentRoom[mapSize+1][mapSize+1];
    bool currentVisited[mapSize+1][mapSize+1], canFindSafe = false;
    memset(currentVisited, false, sizeof currentVisited);
    int l=1, r=1, distance[mapSize+1][mapSize+1];
    qRoom[1] = p; parentRoom[p.x][p.y] = Coordinate(-1, -1);
    currentVisited[p.x][p.y] = true;
    distance[p.x][p.y] = 0;
    Coordinate currentRoom, newRoom, nearestRoom(-1,-1), home = pMap->startPoint;
    while (l <= r) {
        currentRoom = qRoom[l]; l++;
        for (int i=0; i<4; i++) {
            newRoom.x = currentRoom.x + forwardX[i];
            newRoom.y = currentRoom.y + forwardY[i];
            if (!validIndex(newRoom)) continue;
            if (currentVisited[newRoom.x][newRoom.y]) continue;
            if (m[newRoom.x][newRoom.y].checkSafe()) {
                r++; qRoom[r]=newRoom;
                parentRoom[newRoom.x][newRoom.y] = currentRoom;
                currentVisited[newRoom.x][newRoom.y] = true;
                distance[newRoom.x][newRoom.y] = distance[currentRoom.x][currentRoom.y] + 1;
                if (visited[newRoom.x][newRoom.y] == false && canFindSafe == false) {
                    canFindSafe = true;
                    nearestRoom = newRoom;
                }
            }
        }
    }
    //get the path
    bool returnHomeMode = false;
    string message;
    if (!canFindSafe) {
        message = "There are not any safe Rooms to go, let's return home";
        output->println(message);
        returnHomeMode = true;
    }
    if (distance[home.x][home.y] == moveLeft && returnHomeMode == false) {
        message = "Oh no, time's up, let's go to the cave door";
        output->println(message);
        returnHomeMode = true;
    }
    if (returnHomeMode) {
        r=0; currentRoom = home;
        while (distance[currentRoom.x][currentRoom.y] > 0) {
            r++; qRoom[r] = currentRoom;
            currentRoom = parentRoom[currentRoom.x][currentRoom.y];
        }
        for (int i=r; i>=1; i--) {
            goTo(qRoom[i]);
        }
        returnHome();
        return;
    }

    if (flyingMode == false) {
        flyingMode = true;
        message = "The nearest safe Room is " + nearestRoom.stringify();
        output->println(message);
    }
    currentRoom = nearestRoom;
    while (distance[currentRoom.x][currentRoom.y] > 1) {
        currentRoom = parentRoom[currentRoom.x][currentRoom.y];
    }
    //go to that room
    if (currentRoom.x == nearestRoom.x && currentRoom.y == nearestRoom.y) {
        Room nextRoom = goTo(currentRoom);
        getMoreKnowledge(nextRoom);
        flyingMode = false;
    } else {
        goTo(currentRoom);
    }
}

void LogicalAgent::returnHome() {
    string message;
    char pointString[5];
    itoa(point, pointString, 10);
    message = "The final score is: " + string(pointString);
    output->println(message);
    moveLeft = -1;
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
            + " do not have pit";
            output->println(message);
            output->print("So, ");
            informP(true, unknownPosition);
        }
    }
    if (m[x.x][x.y].B != -1) return false;
    m[x.x][x.y].B = state;

    if (state) {
        string message = "Room " + x.stringify() + " has breeze";
        output->println(message);
    } else {
        string message = "Room " + x.stringify() + " does not have any breeze";
        output->println(message);
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informP(false, newPosition);
        }
    }
    return true;
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
            + " do not have Wumpus";
            output->println(message);
            output->print("So, ");
            informW(true, unknownPosition);
        }
    }
    if (m[x.x][x.y].S != -1) return false;
    m[x.x][x.y].S = state;

    if (state) {
        string message = "Room " + x.stringify() + " has stench";
        output->println(message);
    } else {
        string message = "Room " + x.stringify() + " does not have any stench";
        output->println(message);
        for (int i=0; i<4; i++) {
            newPosition.x = x.x + forwardX[i];
            newPosition.y = x.y + forwardY[i];
            if (!validIndex(newPosition)) continue;
            informW(false, newPosition);
        }
    }
    return true;
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
            if (m[newPosition.x][newPosition.y].S == -1) continue;
            informS(m[newPosition.x][newPosition.y].S, newPosition);
        }
    }
    return true;
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
            if (m[newPosition.x][newPosition.y].B == -1) continue;
            informB(m[newPosition.x][newPosition.y].B, newPosition);
        }
    }
    return true;
}
bool LogicalAgent::informG(bool state, Coordinate x) {
    if (m[x.x][x.y].G != -1) return false;
    m[x.x][x.y].G = state;
    if (state) {
        string message = "Yay, There is gold in Room " + x.stringify();
        output->println(message);
        message = "The current point is " + point;
        output->println(message);
    }
    return true;
}
