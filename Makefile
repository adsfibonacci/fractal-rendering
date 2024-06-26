CXX = g++
CXXFLAGS = -Wall -pedantic -g -std=c++17 -O3
LDFLAGS = -lGLEW -lglfw -lGL -lX11 -lpthread -ldl

SOURCE = compute.cpp render.cpp varray.cpp ibuffer.cpp vbuffer.cpp shader.cpp camera.cpp syshead.cpp shapes/circle.cpp shapes/bandwith.cpp shapes/shape.cpp
OBJECTS = $(SOURCE:.cpp=.o)
TARGET = proj.out

all: clean $(TARGET) clean

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.cpp~ *.hpp~ *~ shapes/*.o shapes/*.cpp~ shapes/*.hpp~ shapes/*~ shaders/*~
