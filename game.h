#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <ratio>
#include <chrono>

#include "player.h"
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
    Player player;
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
    void drawPlayer();
    void drawAirportRunway();
    void drawFlightEnemies();
    void drawTerrestrialEnemies();
    void drawBullets();
    void drawBombs();
    bool checkFlightEnemiesCollision();
    bool isPlayerInsideFlightArea(Player& player);
    bool isFlightEnemyInsideFlightArea(FlightEnemy& flightEnemy);
    void eraseBullets();
    void eraseBombs();
    bool isBulletInsideFlightArea(Bullet* bullet);
    bool isBombInsideFlightArea(Bomb *bomb);
    void callGameOver();
    void initFlightEnemiesSpeed();
    void initFlightEnemiesPosition();
    void initTerrestrialEnemiesPosition();
    GLfloat calcFinalSpeed();
    bool checkBulletCollision(FlightEnemy& FlightEnemy);
    bool checkBombCollision(Bomb* bomb);

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

    Player &getPlayer()
    {
        return player;
    }

    bool isGameOver() {
        return this->gameOver;
    }

    void setFlightArea(FlightArea flightArea)
    {
        this->flightArea = flightArea;
    }

    void setPlayer(Player player)
    {
        this->player = player;
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
        return player.isFlying();
    }

    bool isPlayerTakingOff()
    {
        return player.isTakingOff();
    }

    void playerTakeOff()
    {
        player.setFlying(true);
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