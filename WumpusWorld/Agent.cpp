//
//  Agent.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "Agent.hpp"

Agent::Agent(Coordinate startCoordinate, int mapSize) {
    p = startCoordinate;
    point = 0;
    moveLeft = 150;
    currentDirection = 2;
    this->mapSize = mapSize;
}


Room Agent::go() {
    cout << "FORWARD" << "\n";
    --moveLeft;
    p.x += forwardX[currentDirection];
    p.y += forwardY[currentDirection];
    // interact with map
    Room newRoom; // get data from map
    if (newRoom.G) point += 100;
    if (newRoom.P || newRoom.W) {
        point -= 10000;
        moveLeft = -1; // die
    }
    return newRoom;
}

void Agent::shot() {
    cout << "SHOT" << "\n";
    Coordinate shotCoordinate;
    shotCoordinate.x = p.x + forwardX[currentDirection];
    shotCoordinate.y = p.y + forwardY[currentDirection];
    // interact with map
}

void Agent::turn(bool isLeft) {
    if (isLeft) {
        cout << "TURN_LEFT" << "\n";
        currentDirection -= 1;
    } else {
        cout << "TURN_RIGHT" << "\n";
        currentDirection += 1;
    }
    currentDirection = (currentDirection + 4) % 4;
}
