CXX = g++
CXXFLAGS = -std=c++11 -O2
LDFLAGS = -lglut -lGLU -lGL
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: ForestLuxuryWorld

ForestLuxuryWorld: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	rm -f src/*.o ForestLuxuryWorld
