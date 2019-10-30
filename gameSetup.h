#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "tinyxml.h"
#include "gameRuntime.h"
#include "parametersReading.h"

using namespace std;

class GameSetup
{
private:
    GameRuntime gameRuntime;
    ParametersReading parametersReading;
    GLfloat currentIdleTime;
    GLfloat lastIdleTime;
    GLfloat deltaIdleTime;

public:
    GameSetup() {}

    GameRuntime &getGameRuntime()
    {
        return this->gameRuntime;
    }

    bool initRuntimeParameters(string filename, string arenaFilename);
    bool initArenaFile();
    void display(void);
    void idle(void);
    void init(void);
};

#endif