#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <ratio>
#include <chrono>

#include "playerAirplane.h"
#include "airportRunway.h"
#include "flightArea.h"
#include "flightEnemy.h"
#include "terrestrialEnemy.h"

#define TAKEOFF_TIME 4.0

using namespace std::chrono;
using namespace std;

class Game
{
    Draw draw;
    FlightArea flightArea;
    PlayerAirplane playerAirplane;
    AirportRunway airportRunway;
    vector<FlightEnemy> flightEnemies;
    vector<TerrestrialEnemy> terrestrialEnemies;
    vector<Bullet*> bullets;
    vector<Bomb*> bombs;
    GLfloat deltaIdleTime;
    bool gameOver;

    void updateTakeOff(high_resolution_clock::time_point currentTime, GLfloat takeOffTimeElapsed);
    vector<GLfloat> calcTakeOffAcceleration();
    Point currentTakeOffPosition(GLfloat time);
    GLfloat calcSizeIncreaseAcceleration();
    GLfloat currentRadius(GLfloat time);
    void drawFlightArea();
    void drawPlayerAirplane();
    void drawAirportRunway();
    void drawFlightEnemies();
    void drawTerrestrialEnemies();
    void drawBullets();
    void drawBombs();
    bool checkFlightEnemiesCollision();
    bool isPlayerAirplaneInsideFlightArea();
    void eraseBullets();
    void eraseBombs();
    bool isBulletInsideFlightArea(Bullet* bullet);
    bool isBombInsideFlightArea(Bomb *bomb);
    void callGameOver();

public:
    Game() {}

    AirportRunway &getAirportRunway()
    {
        return airportRunway;
    }

    FlightArea &getFlightArea()
    {
        return flightArea;
    }

    PlayerAirplane &getPlayerAirplane()
    {
        return playerAirplane;
    }

    bool isGameOver() {
        return this->gameOver;
    }

    void setFlightArea(FlightArea flightArea)
    {
        this->flightArea = flightArea;
    }

    void setPlayerAirplane(PlayerAirplane playerAirplane)
    {
        this->playerAirplane = playerAirplane;
    }

    void setAirportRunway(AirportRunway airportRunway)
    {
        this->airportRunway = airportRunway;
    }

    void addFlightEnemy(FlightEnemy flightEnemy)
    {
        flightEnemies.push_back(flightEnemy);
    }

    void addTerrestrialEnemy(TerrestrialEnemy terrestrialEnemy)
    {
        terrestrialEnemies.push_back(terrestrialEnemy);
    }

    bool isPlayerFlying()
    {
        return playerAirplane.isFlying();
    }

    bool isPlayerTakingOff()
    {
        return playerAirplane.isTakingOff();
    }

    void playerTakeOff()
    {
        playerAirplane.setFlying(true);
    }

    void takeOff();
    void init();
    void drawGame(GLfloat deltaIdleTime);
    void reset();
    void rotatePlayerAirplaneCannon(GLfloat moviment);
    void shoot();
    void dropBomb();
};

#endif