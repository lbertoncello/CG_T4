#ifndef PARAMETERS_READING_H
#define PARAMETERS_READING_H

#include "tinyxml.h"
#include "gameRuntime.h"

class ParametersReading
{
private:
    string arenaFilename;
    GameRuntime* gameRuntime;

public:
    ParametersReading() {}

    ParametersReading(GameRuntime* gameRuntime, string arenaFilename)
    {
        this->gameRuntime = gameRuntime;
        this->arenaFilename = arenaFilename;
    }

    void setGameRuntime(GameRuntime* gameRuntime)
    {
        this->gameRuntime = gameRuntime;
    }

    void setArenaFilename(string arenaFilename)
    {
        this->arenaFilename = arenaFilename;
    }

    void arenaInit(TiXmlElement *application);
    void jogadorInit(TiXmlElement *application);
    bool parametersInit(const char *filename);
    void windowInit(GLfloat x_size, GLfloat y_size);
    void readCircle(TiXmlElement *circle);
    Color readSVGRGBColor(string style);
    void readLine(TiXmlElement *line);
    bool readArenaFile();
};

#endif