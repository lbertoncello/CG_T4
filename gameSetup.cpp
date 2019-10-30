#include "gameSetup.h"

void GameSetup::display(void)
{
    /* Limpar todos os pixels */
    glClear(GL_COLOR_BUFFER_BIT);

    gameRuntime.getGame().drawGame(deltaIdleTime);

    /* Não esperar */
    glutSwapBuffers();
}

void GameSetup::idle(void)
{
    gameRuntime.keyOperations();

    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    deltaIdleTime = (currentIdleTime - lastIdleTime) / 1000;
    lastIdleTime = currentIdleTime;

    glutPostRedisplay();
}

void GameSetup::init(void)
{
    gameRuntime.getGame().init();

    glClearColor(gameRuntime.getBackgroundColor().getR(), gameRuntime.getBackgroundColor().getG(), gameRuntime.getBackgroundColor().getB(), 0.0);

    /* Inicializa sistema de viz */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            -gameRuntime.getGame().getFlightArea().getArea().getRadius(),
            -1, 1);

    currentIdleTime = glutGet(GLUT_ELAPSED_TIME);
    lastIdleTime = glutGet(GLUT_ELAPSED_TIME);
}

bool GameSetup::initRuntimeParameters(string filename, string arenaFilename)
{
    this->parametersReading.setGameRuntime(&this->gameRuntime);
    this->parametersReading.setArenaFilename(arenaFilename);

    return parametersReading.parametersInit(filename.c_str());
}

bool GameSetup::initArenaFile()
{
    return this->parametersReading.readArenaFile();
}
