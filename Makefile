CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = abstractcpu.o basiccpu.o card.o client.o game.o main.o player.o table.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

