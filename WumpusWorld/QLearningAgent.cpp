//
//  QLearningAgent.cpp
//  WumpusWorld
//
//  Created by Huy Nguyen Ngoc Minh on 12/18/19.
//  Copyright © 2019 Huy Nguyen Ngoc Minh. All rights reserved.
//

#include "QLearningAgent.hpp"

void QLearningAgent::startAgent() {
    string message = "We start at Room " + p.stringify();
    output->println(message);
}

void QLearningAgent::makeMove() {
    cMap.readMap(Logger::inputFilename);
    Room currentRoom = cMap.goToRoom(p);
    State state(p, currentDirection, moveLeft, currentRoom.B, currentRoom.S);
    int bestAction = 0;
    for (int action = 1; action <= 4; ++action) {
        if (getQ(state, action) > getQ(state, bestAction)) {
            bestAction = action;
        }
    }
    NextStateByAction current;
    current.s = state;
    current.isEnd = false;
    NextStateByAction nextState = getNextState(current, bestAction);
    point += nextState.reward;
    moveLeft = nextState.s.moveLeft;
    p = nextState.s.p;
    cMap.takeGold(p);
    if (cMap.goToRoom(p).G) {
        cout << "$\nFOUND GOLD\n$\n";
    }
    currentDirection = nextState.s.direction;
    if (nextState.isEnd) {
        moveLeft = -1;
    }
    if (nextState.isEnd) {
        moveLeft = -1;
        if (!(nextState.s.p == cMap.startPoint)) {
            cout << "YEAH\n";
        } else {
            cout << "CON GA\n";
        }
    }
    cout << point << " ";
    switch (bestAction) {
        case 0:
            cout << "GO\n";
            break;
        case 1:
            cout << "TURN LEFT\n";
            break;
        case 2:
            cout << "TURN RIGHT\n";
            break;
        case 3:
            cout << "SHOT AND GO\n";
            break;
        case 4:
            moveLeft = -1;
            cout << "EXIT\n";
            break;
    }
}

void QLearningAgent::train() {
    State startState(p, 2, 150, false, false);
    for (int ite = 0; ite < number_of_iteration; ++ite) {
        cMap.readMap(Logger::inputFilename);
        NextStateByAction currentState;
        currentState.s = startState;
        currentState.isEnd = false;
        while (!currentState.isEnd) {
            if (currentState.s.p.x == 10) {
                cout << "test";
            }
            NextStateByAction maxRewardAction;
            int bestAction = 0;
            maxRewardAction.reward = -1e9;
            double prob = randDouble();
            if (prob <= epsilon) {
                int action = rand() % 5;
                maxRewardAction = getNextState(currentState, action);
                bestAction = action;
            } else {
                for (int action = 0; action <= 4; ++action) {
                    NextStateByAction rewardAction = getNextState(currentState, action);
                    if (rewardAction.reward > maxRewardAction.reward) {
                        maxRewardAction = rewardAction;
                        bestAction = action;
                    }
                    if (rewardAction.reward == maxRewardAction.reward && randDouble() >= 0.2) {
                        maxRewardAction = rewardAction;
                        bestAction = action;
                    }
                }
            }
            cMap.takeGold(currentState.s.p);

            double currentValue = getQ(currentState.s, bestAction);
            double bestValue = -1e9;

            for (int action  = 0; action <= 4; ++action) {
                bestValue = max(bestValue, getQ(maxRewardAction.s, action));
            }

//            setQ(currentState.s, bestAction, currentValue + learning_rate * (maxRewardAction.reward + discount_factor * bestValue - currentValue));
            
            setQ(currentState.s, bestAction, (1.0 - learning_rate) * currentValue + learning_rate * (maxRewardAction.reward + discount_factor * bestValue));
            
            currentState = maxRewardAction;
        }
        cout << "Iteration " << ite << " :" << currentState.reward << "\n";
    }
}


NextStateByAction QLearningAgent::getNextState(NextStateByAction inState, int action) {
    State nextState = inState.s;
    NextStateByAction nextStateByAction = inState;
    Room nextRoom;
    switch (action) {
        case 1:
            nextState.direction = (nextState.direction - 1 + 4) % 4;
            break;
        case 2:
            nextState.direction = (nextState.direction + 1 + 4) % 4;
            break;
        case 4:
            if ((pMap->startPoint == nextState.p)) {
                nextStateByAction.reward = 10;
                nextStateByAction.isEnd = true;
            } else {
                nextStateByAction.reward = -10000;
                nextStateByAction.isEnd = true;
            }
            break;
        case 3:
            nextStateByAction.reward = -150;
            nextState.p.x += forwardX[nextState.direction];
            nextState.p.y += forwardY[nextState.direction];
            nextRoom = cMap.goToRoom(nextState.p);
            if (nextState.moveLeft < 0 || !validIndex(nextState.p) || nextRoom.P || nextRoom.W) {
                nextStateByAction.isEnd = true;
                nextStateByAction.reward = -10000;
            } else {
                if (nextRoom.G) {
                    nextStateByAction.reward = 100;
                }
            }
            break;
        case 0:
            nextState.p.x += forwardX[nextState.direction];
            nextState.p.y += forwardY[nextState.direction];
            nextState.moveLeft -= 1;
            nextRoom = cMap.goToRoom(nextState.p);
            if (nextState.moveLeft < 0 || !validIndex(nextState.p) || nextRoom.P || nextRoom.W) {
                nextStateByAction.isEnd = true;
                nextStateByAction.reward = -10000;
            } else {
                if (nextRoom.G) {
                    nextStateByAction.reward = 100;
                }
            }
            break;
    }
    nextStateByAction.s = nextState;
    return nextStateByAction;
}
