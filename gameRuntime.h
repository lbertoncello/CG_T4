#ifndef GAME_RUNTIME_H
#define GAME_RUNTIME_H

#include <string>

#include "color.h"
#include "game.h"

using namespace std;

class GameRuntime
{
private:
    GLfloat playerAirplaneSpeedMult;
    GLfloat playerBulletSpeedMult;
    GLfloat enemyAirplaneSpeedMult;
    GLfloat enemyBulletSpeedMult;
    GLfloat enemyShotsFrequency;

    string windowTitle;
    GLint windowSize_x = 1000;
    GLint windowSize_y = 1000;
    GLint windowInitial_x_position = 100;
    GLint windowInitial_y_position = 100;

    Color backgroundColor;

    Game game;

    static bool *keyStates;
    bool isLeftMouseButtonPressed = false;
    bool isRightMouseButtonPressed = false;
    GLfloat previousX = 0;

public:
    GameRuntime() {}

    Game &getGame()
    {
        return this->game;
    }

    Color &getBackgroundColor()
    {
        return this->backgroundColor;
    }

    GLfloat getPlayerAirplaneSpeedMult()
    {
        return this->playerAirplaneSpeedMult;
    }

    GLfloat getPlayerBulletSpeedMult()
    {
        return this->playerBulletSpeedMult;
    }

    GLfloat getEnemyAirplaneSpeedMult()
    {
        return this->enemyAirplaneSpeedMult;
    }

    GLfloat getEnemyBulletSpeedMult()
    {
        return this->enemyBulletSpeedMult;
    }

    GLfloat getEnemyShotsFrequency()
    {
        return this->enemyShotsFrequency;
    }

    string getWindowTitle()
    {
        return this->windowTitle;
    }

    GLint getWindowSize_x()
    {
        return this->windowSize_x;
    }

    GLint getWindowSize_y()
    {
        return this->windowSize_y;
    }

    GLint getWindowInitial_x_position()
    {
        return this->windowInitial_x_position;
    }

    GLint getWindowInitial_y_position()
    {
        return this->windowInitial_y_position;
    }

    void setPlayerSpeedMult(GLfloat playerAirplaneSpeedMult)
    {
        this->playerAirplaneSpeedMult = playerAirplaneSpeedMult;
    }

    void setPlayerBulletSpeedMult(GLfloat playerBulletSpeedMult)
    {
        this->playerBulletSpeedMult = playerBulletSpeedMult;
    }

    void setEnemyAirplaneSpeedMult(GLfloat enemyAirplaneSpeedMult)
    {
        this->enemyAirplaneSpeedMult = enemyAirplaneSpeedMult;
    }

    void setEnemyBulletSpeedMult(GLfloat enemyBulletSpeedMult)
    {
        this->enemyBulletSpeedMult = enemyBulletSpeedMult;
    }

    void setEnemyShotsFrequency(GLfloat enemyShotsFrequency)
    {
        this->enemyShotsFrequency = enemyShotsFrequency;
    }

    void setWindowTitle(string windowTitle)
    {
        this->windowTitle = windowTitle;
    }

    void setWindowsSize_x(GLint windowSize_x)
    {
        this->windowSize_x = windowSize_x;
    }

    void setWindowsSize_y(GLint windowSize_y)
    {
        this->windowSize_y = windowSize_y;
    }

    void setBackgroundColor(Color backgroundColor)
    {
        this->backgroundColor = backgroundColor;
    }

    void keyOperations(void);
    static void keyPress(unsigned char key, GLint x, GLint y);
    static void keyUp(unsigned char key, GLint x, GLint y);
    void mouse(GLint button, GLint state, GLint x, GLint y);
    void motion(GLint x, GLint y);
    void passiveMotion(GLint x, GLint y);
};

#endif