CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++14
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DEPS = CelestialBody.h Universe.h 

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

all: Universe.o CelestialBody.o NBody.o NBody

NBody: NBody.o CelestialBody.o Universe.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm $(wildcard *.o) NBody
