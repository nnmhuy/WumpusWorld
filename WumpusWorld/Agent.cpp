//
//  Agent.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "Agent.hpp"

Agent::Agent(Coordinate startCoordinate, int mapSize, Map *pMap) {
    p = startCoordinate;
    point = 0;
    moveLeft = 150;
    currentDirection = 2;
    this->mapSize = mapSize;
    this->pMap = pMap;

    // set up visited
    for (int i=0; i<=mapSize; i++)
        for (int j=0; j<=mapSize; j++)
            visited[i][j] = false;
}


Room Agent::go() {
    --moveLeft;
    p.x += forwardX[currentDirection];
    p.y += forwardY[currentDirection];
    output->println("FORWARD (Enter Room " + p.stringify() + " )");
    visited[p.x][p.y] = true;
    // interact with map
    Room newRoom = pMap->goToRoom(p); // get data from map
    if (newRoom.G) point += 100;
    if (newRoom.P || newRoom.W) {
        point -= 10000;
        moveLeft = -1; // die
    }
    pMap->takeGold(p);
    return newRoom;
}

Room Agent::goTo(Coordinate finalPoint) {
    Coordinate newPosition; int i;
    for (i=0; i<4; i++) {
        newPosition.x = p.x + forwardX[i];
        newPosition.y = p.y + forwardY[i];
        if (newPosition.x == finalPoint.x && newPosition.y == finalPoint.y) break;
    }
    int countRight = (i - currentDirection + 4) % 4;
    if (countRight == 3) {
        turn(true);
    } else {
        for (int j=1; j<=countRight; j++) turn(false);
    }

}

void Agent::shot() {
    output->println("SHOT");
    Coordinate shotCoordinate;
    shotCoordinate.x = p.x + forwardX[currentDirection];
    shotCoordinate.y = p.y + forwardY[currentDirection];
    // interact with map
}

void Agent::turn(bool isLeft) {
    if (isLeft) {
        output->println("TURN_LEFT");
        currentDirection -= 1;
    } else {
        output->println("TURN_RIGHT");
        currentDirection += 1;
    }
    currentDirection = (currentDirection + 4) % 4;
}

bool Agent::validIndex(Coordinate x) {
    if (x.x < 1 && x.x > mapSize) return false;
    if (x.y < 1 && x.y > mapSize) return false;
    return true;
}
