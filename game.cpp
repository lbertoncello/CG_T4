#include <iostream>

#include "game.h"
#include "calc.h"

high_resolution_clock::time_point takeOffStartTime;
high_resolution_clock::time_point sizeIncreaseStartTime;
vector<GLfloat> takeOffAcceleration;
GLfloat sizeIncreaseAcceleration;
bool beforeAirportRunwayMiddle;

Calc calc;

void Game::erasePlayerBullets()
{
    vector<Bullet *>::iterator playerBullets_it;
    for (playerBullets_it = playerBullets.begin(); playerBullets_it != playerBullets.end(); playerBullets_it++)
    {
        delete (*playerBullets_it);
    }
    playerBullets.clear();
}

void Game::eraseEnemyBullets()
{
    vector<Bullet *>::iterator enemyBullets_it;
    for (enemyBullets_it = enemyBullets.begin(); enemyBullets_it != enemyBullets.end(); enemyBullets_it++)
    {
        delete (*enemyBullets_it);
    }
    enemyBullets.clear();
}

void Game::eraseBullets()
{
    erasePlayerBullets();
    eraseEnemyBullets();
}

void Game::eraseBombs()
{
    vector<Bomb *>::iterator bombs_it;
    for (bombs_it = bombs.begin(); bombs_it != bombs.end(); bombs_it++)
    {
        delete (*bombs_it);
    }
    bombs.clear();
}

vector<GLfloat> Game::calcTakeOffAcceleration()
{
    Point initialPosition = airportRunway.getAdjustedBody().getPoint1();
    Point finalPosition = airportRunway.getAdjustedBody().getPoint2();
    vector<GLfloat> initialSpeed = calc.zerosVector(2);
    GLfloat time = TAKEOFF_TIME;

    return calc.calcAccelerationRequired(initialPosition, finalPosition, initialSpeed, time);
}

void Game::callGameOver()
{
    gameOver = true;
    this->player.setPropellerAngle(0.0);
    this->player.setSpeedNorm(0.0);

    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        flightEnemy_it->setPropellerAngle(0.0);
        flightEnemy_it->setSpeedNorm(0.0);
    }

    string text = "GAME OVER";
    Point position(-15, 0);

    drawer.drawText(text, position);
}

void Game::callGameWin()
{
    gameWin = true;
    this->player.setPropellerAngle(0.0);
    this->player.setSpeedNorm(0.0);

    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        flightEnemy_it->setPropellerAngle(0.0);
        flightEnemy_it->setSpeedNorm(0.0);
    }

    string text = "VOCE VENCEU!";
    Point position(-15, 0);

    drawer.drawText(text, position);
}

void Game::reset()
{
    player.reset();

    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        flightEnemy_it->reset();
    }

    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        terrestrialEnemies_it->reset();
    }

    eraseBullets();
    eraseBombs();
    init();
}

bool Game::checkPlayerBulletCollision(FlightEnemy &flightEnemy)
{
    vector<Bullet *>::iterator playerBullets_it;
    for (playerBullets_it = playerBullets.begin(); playerBullets_it != playerBullets.end();)
    {
        if (flightEnemy.getAdjustedBody().checkIntersection((*playerBullets_it)->getAdjustedBody()))
        {
            return true;
        }

        playerBullets_it++;
    }

    return false;
}

bool Game::checkEnemyBulletCollision()
{
    vector<Bullet *>::iterator enemyBullets_it;
    for (enemyBullets_it = enemyBullets.begin(); enemyBullets_it != enemyBullets.end();)
    {
        if (player.isFlying() && player.getAdjustedBody().checkIntersection((*enemyBullets_it)->getAdjustedBody()))
        {
            player.setDestroyed(true);
            return true;
        }

        enemyBullets_it++;
    }

    return false;
}

bool Game::checkBombCollision(Bomb *bomb)
{
    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        if (terrestrialEnemies_it->getAdjustedBody().checkIntersection(bomb->getAdjustedBody()))
        {
            terrestrialEnemies_it->setDestroyed(true);
            return true;
        }
    }

    return false;
}

void Game::init()
{
    airportRunway.setAdjustedBody(flightArea.getArea().getCenter_x(), flightArea.getArea().getCenter_y());
    player.setCurrentPosition(airportRunway.getAdjustedBody().getPoint1());
    player.setInclinationAngle(airportRunway.calcInclinationAngle());
    beforeAirportRunwayMiddle = true;
    gameOver = false;
    gameWin = false;
    initFlightEnemiesPosition();
    initTerrestrialEnemiesPosition();
    initFlightEnemiesSpeed();
}

void Game::takeOff()
{
    player.setTakingOff(true);
    player.setCurrentPosition(airportRunway.getAdjustedBody().getPoint1());
    takeOffAcceleration = calcTakeOffAcceleration();
    sizeIncreaseAcceleration = calcSizeIncreaseAcceleration();
    takeOffStartTime = std::chrono::high_resolution_clock::now();
    vector<GLfloat> finalSpeed = calc.calcFinalSpeedRequired(calc.zerosVector(2), takeOffAcceleration, TAKEOFF_TIME);
    player.setSpeed(finalSpeed);
}

Point Game::currentTakeOffPosition(GLfloat time)
{
    Point initialPosition = airportRunway.getAdjustedBody().getPoint1();
    vector<GLfloat> acceleration = takeOffAcceleration;
    vector<GLfloat> initialSpeed = calc.zerosVector(2);

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, time);
}

GLfloat Game::calcSizeIncreaseAcceleration()
{
    GLfloat airportRunwayScalarSize = calc.euclideanDistance(airportRunway.getAdjustedBody().getPoint1(), airportRunway.getAdjustedBody().getPoint2());
    airportRunway.setScalarMiddle(airportRunwayScalarSize / 2.0);
    GLfloat airportRunwayScalarAcceleration = calc.calcAccelerationRequired(0.0, airportRunwayScalarSize, 0.0, TAKEOFF_TIME);

    GLfloat finalSpeed = calc.calcFinalSpeedRequired(0.0, airportRunwayScalarAcceleration, TAKEOFF_TIME);

    GLfloat initialSize = player.getBody().getRadius();
    GLfloat finalSize = 2 * initialSize;
    GLfloat initialSpeed = calc.calcInitialSpeedRequired(finalSpeed, airportRunwayScalarAcceleration, airportRunwayScalarSize / 2, airportRunwayScalarSize);
    GLfloat time = calc.calcTimeRequired(initialSpeed, finalSpeed, airportRunwayScalarAcceleration);

    return calc.calcAccelerationRequired(initialSize, finalSize, 0.0, time);
}

GLfloat Game::currentRadius(GLfloat time)
{
    GLfloat initialPosition = player.getInitialRadius();
    GLfloat acceleration = sizeIncreaseAcceleration;
    GLfloat initialSpeed = 0;

    return calc.calcCurrentPositionVariation(initialPosition, acceleration, initialSpeed, time);
}

void Game::updateTakeOff(high_resolution_clock::time_point currentTime, GLfloat takeOffTimeElapsed)
{
    Point currentPositionVariation = currentTakeOffPosition(takeOffTimeElapsed);
    Point currentPosition(player.getStartPosition().getX() + currentPositionVariation.getX(), player.getStartPosition().getY() + currentPositionVariation.getY());
    player.setCurrentPosition(currentPosition);

    if (beforeAirportRunwayMiddle == false)
    {
        duration<GLfloat> timeSpan = duration_cast<duration<GLfloat>>(currentTime - sizeIncreaseStartTime);
        GLfloat sizeIncreaseTimeElapsed = timeSpan.count();

        GLfloat newRadius = player.getInitialRadius() + currentRadius(sizeIncreaseTimeElapsed);
        player.getBody().setRadius(newRadius);
    }
    else
    {
        GLfloat distance = calc.euclideanDistance(player.getCurrentPosition(), airportRunway.getAdjustedBody().getPoint2());

        if (distance < airportRunway.getScalarMiddle())
        {
            beforeAirportRunwayMiddle = false;
            sizeIncreaseStartTime = high_resolution_clock::now();
        }
    }
}

void Game::drawFlightArea()
{
    flightArea.draw();
}

void Game::initFlightEnemiesSpeed()
{
    takeOffAcceleration = calcTakeOffAcceleration();
    sizeIncreaseAcceleration = calcSizeIncreaseAcceleration();
    takeOffStartTime = std::chrono::high_resolution_clock::now();
    vector<GLfloat> finalSpeed = calc.calcFinalSpeedRequired(calc.zerosVector(2), takeOffAcceleration, TAKEOFF_TIME);

    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        glPushMatrix();
        flightEnemy_it->setSpeed(finalSpeed);
        glPopMatrix();
    }
}

void Game::initFlightEnemiesPosition()
{
    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        glPushMatrix();
        flightEnemy_it->setCurrentPosition(Point(-flightArea.getArea().getCenter_x() + flightEnemy_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + flightEnemy_it->getBody().getCenter_y()));
        glPopMatrix();
    }
}

void Game::initTerrestrialEnemiesPosition()
{
    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        // glPushMatrix();
        // glTranslatef(-flightArea.getArea().getCenter_x() + terrestrialEnemies_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + terrestrialEnemies_it->getBody().getCenter_y(), 0.0);
        terrestrialEnemies_it->setCurrentPosition(Point(-flightArea.getArea().getCenter_x() + terrestrialEnemies_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + terrestrialEnemies_it->getBody().getCenter_y()));
        // glPopMatrix();
    }
}

void Game::drawPlayer()
{
    if (player.isTakingOff())
    {
        high_resolution_clock::time_point currentTime = high_resolution_clock::now();
        duration<GLfloat> timeSpan = duration_cast<duration<GLfloat>>(currentTime - takeOffStartTime);
        GLfloat timeElapsed = timeSpan.count();

        if (timeElapsed >= TAKEOFF_TIME)
        {
            player.setTakingOff(false);
            player.setFlying(true);
        }

        updateTakeOff(currentTime, timeElapsed);
    }

    if (!gameWin && amountOfUndamagedTerrestrialEnemies() > 0)
    {
        if (player.isFlying())
        {
            if (!player.isDestroyed() && !checkFlightEnemiesCollision() && !checkEnemyBulletCollision())
            {
                if (isPlayerInsideFlightArea(player))
                {
                    player.move(deltaIdleTime);
                }
                else
                {
                    player.teleport();

                    while (!isPlayerInsideFlightArea(player))
                    {
                        player.move(deltaIdleTime);
                    }
                }
            }
            else
            {
                callGameOver();
            }
        }
    }
    else
    {
        callGameWin();
    }

    player.draw();
}

void Game::drawAirportRunway()
{
    airportRunway.draw();
}

void Game::drawFlightEnemies()
{
    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        if (!flightEnemy_it->isDestroyed())
        {
            glPushMatrix();
            if (!gameOver && !gameWin)
            {
                if (isFlightEnemyInsideFlightArea(*flightEnemy_it))
                {
                    if (checkPlayerBulletCollision(*flightEnemy_it))
                    {
                        flightEnemy_it->setDestroyed(true);
                    }
                    else
                    {
                        if (flightEnemy_it->checkAutoShot())
                        {
                            enemyBullets.push_back(flightEnemy_it->autoShoot(deltaIdleTime));
                        }

                        flightEnemy_it->autoMove(deltaIdleTime);
                    }
                }
                else
                {
                    flightEnemy_it->teleport();

                    while (!isFlightEnemyInsideFlightArea(*flightEnemy_it))
                    {
                        flightEnemy_it->autoMove(deltaIdleTime);
                    }
                }
            }

            // glTranslatef(-flightArea.getArea().getCenter_x() + flightEnemy_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + flightEnemy_it->getBody().getCenter_y(), 0.0);
            flightEnemy_it->draw();
            glPopMatrix();
        }
    }
}

void Game::drawTerrestrialEnemies()
{
    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        // glPushMatrix();
        // glTranslatef(-flightArea.getArea().getCenter_x() + terrestrialEnemies_it->getBody().getCenter_x(), -flightArea.getArea().getCenter_y() + terrestrialEnemies_it->getBody().getCenter_y(), 0.0);
        terrestrialEnemies_it->draw();
        // glPopMatrix();
    }
}

void Game::drawPlayerBullets()
{
    glPushMatrix();

    vector<Bullet *>::iterator playerBullets_it;
    for (playerBullets_it = playerBullets.begin(); playerBullets_it != playerBullets.end();)
    {
        if (isBulletInsideFlightArea((*playerBullets_it)))
        {
            if (!isGameOver() && !isGameWin())
            {
                (*playerBullets_it)->move(deltaIdleTime);
            }

            (*playerBullets_it)->draw();
            playerBullets_it++;
        }
        else
        {
            delete (*playerBullets_it);
            playerBullets_it = playerBullets.erase(playerBullets_it);
        }
    }

    glPopMatrix();
}

void Game::drawEnemyBullets()
{
    glPushMatrix();

    vector<Bullet *>::iterator enemyBullets_it;
    for (enemyBullets_it = enemyBullets.begin(); enemyBullets_it != enemyBullets.end();)
    {
        if (isBulletInsideFlightArea((*enemyBullets_it)))
        {
            if (!isGameOver() && !isGameWin())
            {
                (*enemyBullets_it)->move(deltaIdleTime);
            }

            (*enemyBullets_it)->draw();
            enemyBullets_it++;
        }
        else
        {
            delete (*enemyBullets_it);
            enemyBullets_it = enemyBullets.erase(enemyBullets_it);
        }
    }

    glPopMatrix();
}

void Game::drawBullets()
{
    drawPlayerBullets();
    drawEnemyBullets();
}

void Game::drawBombs()
{
    glPushMatrix();

    vector<Bomb *>::iterator bombs_it;
    for (bombs_it = bombs.begin(); bombs_it != bombs.end();)
    {
        if (isBombInsideFlightArea((*bombs_it)))
        {
            if (!isGameOver() && !isGameWin())
            {
                (*bombs_it)->updateSize();
            }

            if (!(*bombs_it)->isOnTheGround())
            {
                if (!isGameOver() && !isGameWin())
                {
                    (*bombs_it)->move(deltaIdleTime);
                }

                (*bombs_it)->draw();
                bombs_it++;
            }
            else
            {
                checkBombCollision(*bombs_it);

                delete (*bombs_it);
                bombs_it = bombs.erase(bombs_it);
            }
        }
        else
        {
            delete (*bombs_it);
            bombs_it = bombs.erase(bombs_it);
        }
    }

    glPopMatrix();
}

void Game::drawGame(GLfloat deltaIdleTime)
{
    this->deltaIdleTime = deltaIdleTime;

    drawFlightArea();
    drawTerrestrialEnemies();
    drawFlightEnemies();
    drawAirportRunway();
    drawBombs();
    drawPlayer();
    drawBullets();
    drawScoreboard();
}

GLint Game::amountOfUndamagedTerrestrialEnemies()
{
    int amount = 0;

    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        if (!terrestrialEnemies_it->isDestroyed())
        {
            amount++;
        }
    }

    return amount;
}

GLint Game::amountOfDamagedTerrestrialEnemies()
{
    int amount = 0;

    vector<TerrestrialEnemy>::iterator terrestrialEnemies_it;
    for (terrestrialEnemies_it = terrestrialEnemies.begin(); terrestrialEnemies_it != terrestrialEnemies.end(); terrestrialEnemies_it++)
    {
        if (terrestrialEnemies_it->isDestroyed())
        {
            amount++;
        }
    }

    return amount;
}

void Game::drawScoreboard()
{
    string scoreboard = "ELIMINADAS: " + to_string(amountOfDamagedTerrestrialEnemies()) + " | RESTANTES: " + to_string(amountOfUndamagedTerrestrialEnemies());
    Point position(125, -270);

    drawer.drawText(scoreboard, position);
}

bool Game::isBulletInsideFlightArea(Bullet *bullet)
{
    return flightArea.getArea().isPointInCircle(bullet->getCurrentPositionAdjusted());
}

bool Game::isBombInsideFlightArea(Bomb *bomb)
{
    return flightArea.getArea().isPointInCircle(bomb->getCurrentPositionAdjusted());
}

bool Game::checkFlightEnemiesCollision()
{
    vector<FlightEnemy>::iterator flightEnemy_it;
    for (flightEnemy_it = flightEnemies.begin(); flightEnemy_it != flightEnemies.end(); flightEnemy_it++)
    {
        if (!flightEnemy_it->isDestroyed() && player.checkIntersection(flightArea.getArea(),
                                                                       Circle(flightEnemy_it->getCurrentPositionAdjusted(), flightEnemy_it->getBody().getRadius()),
                                                                       deltaIdleTime))
        {
            player.setDestroyed(true);
            return true;
        }
    }

    return false;
}

bool Game::isFlightEnemyInsideFlightArea(FlightEnemy &flightEnemy)
{
    return flightArea.getArea().isPointInCircle(flightEnemy.getCurrentPositionAdjusted());
}

bool Game::isPlayerInsideFlightArea(Player &player)
{
    return flightArea.getArea().isPointInCircle(player.getCurrentPositionAdjusted());
}

void Game::rotatePlayerAirplaneCannon(GLfloat moviment)
{
    this->player.rotateCannon(moviment, deltaIdleTime);
}

void Game::shoot()
{
    playerBullets.push_back(this->player.shoot(deltaIdleTime));
}

void Game::dropBomb()
{
    bombs.push_back(this->player.dropBomb(deltaIdleTime));
}