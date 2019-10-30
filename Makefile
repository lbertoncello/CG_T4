all:
	g++ -std="c++11" tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp main.cpp draw.cpp point.cpp circle.cpp line.cpp color.cpp game.cpp flightArea.cpp enemy.cpp flightEnemy.cpp terrestrialEnemy.cpp playerAirplane.cpp airportRunway.cpp gameRuntime.cpp gameSetup.cpp parametersReading.cpp bullet.cpp bomb.cpp calc.cpp -lGL -lGLU -lglut -o trabalhocg

clean:
	rm trabalhocg