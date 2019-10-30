#include "parametersReading.h"

    void ParametersReading::arenaInit(TiXmlElement *application)
    {
        TiXmlElement *arquivoArena = application->FirstChildElement("arquivoDaArena");
        string filename = arquivoArena->FirstChildElement("nome")->GetText();
        string format = arquivoArena->FirstChildElement("tipo")->GetText();
        string path = arquivoArena->FirstChildElement("caminho")->GetText();

        arenaFilename += path + "/" + filename + "." + format;
    }

    void ParametersReading::jogadorInit(TiXmlElement *application)
    {
        TiXmlElement *jogador = application->FirstChildElement("jogador");
        TiXmlAttribute *jogadorAttribute = jogador->FirstAttribute();

        while (jogadorAttribute)
        {
            if (strcmp(jogadorAttribute->Name(), "vel") == 0)
            {
                this->gameRuntime->setPlayerAirplaneSpeedMult(stof(jogadorAttribute->Value()));
            } else if (strcmp(jogadorAttribute->Name(), "velTiro") == 0)
            {
                this->gameRuntime->setBulletSpeedMult(stof(jogadorAttribute->Value()));
            }

            jogadorAttribute = jogadorAttribute->Next();
        }
    }

    bool ParametersReading::parametersInit(const char *filename)
    {
        TiXmlDocument doc(filename);
        bool loadOkay = doc.LoadFile();

        if (loadOkay)
        {
            TiXmlElement *application = doc.RootElement();

            arenaInit(application);
            jogadorInit(application);

            return true;
        }
        else
        {
            cout << "Failed to load file" << endl;

            return false;
        }
    }

    void ParametersReading::windowInit(GLfloat x_size, GLfloat y_size)
    {
        this->gameRuntime->setWindowsSize_x(x_size);
        this->gameRuntime->setWindowsSize_y(y_size);
    }

    void ParametersReading::readCircle(TiXmlElement *circle)
    {
        TiXmlAttribute *circleAttribute = circle->FirstAttribute();
        Circle _circle;
        string color;

        while (circleAttribute)
        {
            if (strcmp(circleAttribute->Name(), "cx") == 0)
            {
                _circle.setCenter_x(stof(circleAttribute->Value()));
            }
            else if (strcmp(circleAttribute->Name(), "cy") == 0)
            {
                _circle.setCenter_y(stof(circleAttribute->Value()));
            }
            else if (strcmp(circleAttribute->Name(), "r") == 0)
            {
                _circle.setRadius(stof(circleAttribute->Value()));
            }
            else if (strcmp(circleAttribute->Name(), "fill") == 0)
            {
                _circle.setColor(Color(circleAttribute->Value()));
                color = circleAttribute->Value();
            }
            else if (strcmp(circleAttribute->Name(), "id") == 0)
            {
                _circle.setId(stoi(circleAttribute->Value()));
            }

            circleAttribute = circleAttribute->Next();
        }

        if (color == string("blue"))
        {
            FlightArea flightArea(_circle);
            this->gameRuntime->getGame().setFlightArea(flightArea);

            GLfloat diameter = 2 * _circle.getRadius();
            windowInit(diameter, diameter);
        }
        else if (color == string("green"))
        {
            PlayerAirplane playerAirplane(_circle);
            this->gameRuntime->getGame().setPlayerAirplane(playerAirplane);
        }
        else if (color == string("red"))
        {
            FlightEnemy flightEnemy(_circle);
            this->gameRuntime->getGame().addFlightEnemy(flightEnemy);
        }
        else if (color == string("orange"))
        {
            TerrestrialEnemy terrestrialEnemy(_circle);
            this->gameRuntime->getGame().addTerrestrialEnemy(terrestrialEnemy);
        }
    }

    Color ParametersReading::readSVGRGBColor(string style)
    {
        string delimiter = ":";
        string rgb = style.substr(style.find(delimiter) + 5, 5);
        GLfloat r = stof(rgb.substr(0, 1)) / 255.0;
        GLfloat g = stof(rgb.substr(2, 1)) / 255.0;
        GLfloat b = stof(rgb.substr(4, 1)) / 255.0;

        return Color(r, g, b);
    }

    void ParametersReading::readLine(TiXmlElement *line)
    {
        TiXmlAttribute *lineAttribute = line->FirstAttribute();
        Line _line;

        while (lineAttribute)
        {
            if (strcmp(lineAttribute->Name(), "x1") == 0)
            {
                _line.setPoint1_x(stof(lineAttribute->Value()));
            }
            else if (strcmp(lineAttribute->Name(), "y1") == 0)
            {
                _line.setPoint1_y(stof(lineAttribute->Value()));
            }
            else if (strcmp(lineAttribute->Name(), "x2") == 0)
            {
                _line.setPoint2_x(stof(lineAttribute->Value()));
            }
            else if (strcmp(lineAttribute->Name(), "y2") == 0)
            {
                _line.setPoint2_y(stof(lineAttribute->Value()));
            }
            else if (strcmp(lineAttribute->Name(), "style") == 0)
            {
                _line.setColor(readSVGRGBColor(lineAttribute->Value()));
            }
            else if (strcmp(lineAttribute->Name(), "id") == 0)
            {
                _line.setId(stoi(lineAttribute->Value()));
            }

            lineAttribute = lineAttribute->Next();
        }

        AirportRunway airportRunway(_line);
        this->gameRuntime->getGame().setAirportRunway(airportRunway);
    }

    bool ParametersReading::readArenaFile()
    {
        TiXmlDocument doc(arenaFilename.c_str());
        bool loadOkay = doc.LoadFile();

        if (loadOkay)
        {
            TiXmlNode *arenaDescription = doc.FirstChildElement("svg");

            TiXmlElement *element = arenaDescription->FirstChildElement();

            for (element; element; element = element->NextSiblingElement())
            {
                if (element->ValueTStr() == "circle")
                {
                    readCircle(element);
                }
                else if (element->ValueTStr() == "line")
                {
                    readLine(element);
                }
            }

            this->gameRuntime->getGame().getPlayerAirplane().setAirplaneSpeedMultiplier(this->gameRuntime->getPlayerAirplaneSpeedMult());
            this->gameRuntime->getGame().getPlayerAirplane().setBulletSpeedMultiplier(this->gameRuntime->getBulletSpeedMult());

            return true;
        }
        else
        {
            cout << "Failed to load file" << endl;

            return false;
        }
    }