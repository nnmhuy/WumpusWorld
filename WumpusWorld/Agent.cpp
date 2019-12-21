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
    output->println("FORWARD (Enter Room " + p.stringify() + ")");
    return enterRoom();
}

Room Agent::enterRoom() {
    visited[p.x][p.y] = true;
    // interact with map
    Room newRoom = pMap->goToRoom(p); // get data from map
    if (newRoom.G) point += 100;
    if (newRoom.P || newRoom.W) {
        point -= 10000;
        moveLeft = -1; // die
        string message = "Oh no, there is a ";
        if (newRoom.P == 1) message += "pit in this room";
        else message += "Wumpus in this room";
        output->println(message);
    }
    if (newRoom.G == 1) {
        currentGold = true;
        pMap->takeGold(p);
        newRoom.G = 0;
        string message = "Yay, There is gold in Room " + p.stringify();
        output->println(message);
//        char pointString[5];
//        itoa(point, pointString, 10);
        message = "The current score is: " + to_string(point);
        output->println(message);
    } else currentGold = false;
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
    return go();
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
    if (x.x < 1 || x.x > mapSize) return false;
    if (x.y < 1 || x.y > mapSize) return false;
    return true;
}

void Agent::draw() {
//    if (system("CLS")) system("clear");
    for (int i=mapSize; i>=1; i--) {
        for (int j=1; j<=mapSize; j++) {
            if (visited[j][i] == false) {
                //system("COLOR F8"); // gray
                cout<<" ?  |";
                continue;
            }
            if (m[j][i].W == 1) {
                //system("COLOR F0"); // black
                cout<<" W  |";
                continue;
            }
            if (m[j][i].P == 1) {
                //system("COLOR F0"); // black
                cout<<" P  |";
                continue;
            }
            if (j == p.x && i == p.y) {
                cout<<"T";
            } else {
                cout<<" ";
            }
            if (currentGold == true && j == p.x && i == p.y) cout<<"G";
            else cout<<" ";

            if (m[j][i].B == 1) cout<<"B";
            else cout<<" ";
            if (m[j][i].S == 1) cout<<"S";
            else cout<<" ";
            cout<<"|";
        }
        //system("COLOR 00");
        cout<<" \n";
        for (int j=1; j<=mapSize; j++) {
            cout<<"_____";
        }
        cout<<"\n";
    }
    cout<<"\n";
    cout<<"The current point is: " <<point <<"\n";
    if (moveLeft > 0)
        cout<<"The number of move have used: "<< 150-moveLeft <<"\n";
    else cout<<"The game is end\n";
    cout<<"Press any key to continue\n";
}
