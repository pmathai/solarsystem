#////////////////////////////////////////////////////////////
#//
#// File:  Makefile
#// Authors: RIT 
#// Contributors:
#// Last modified: 2/2/11
#//
#// Description:  Makefile, targets:
#//               Solaris Build:
#//                 - make
#//                 - make all
#//                 - make tessellation
#//               OS X Build:
#//                 - make mac
#//               Cleanup:
#//                 - make clean
#//                 - make realclean
#//
#////////////////////////////////////////////////////////////

LDLIBS = -lglut -lGLU -lGL -lXext -LX11 -lm -lSOIL
MACLDLIBS = -framework GLUT -framework OpenGL -framework Cocoa

SOURCE_C = render.cpp solarsystem.cpp
SOURCE_H = render.h
OBJ_FILES = solarsystem.o render.o
BINARY = solarsystem

CC =       gcc
CXX =      g++

CXXFLAGS = -g

all:   solarsystem 


solarsystem: $(OBJ_FILES)
	$(CXX)  -o $(BINARY) $(OBJ_FILES) -g $(LDLIBS)

clean:
	-/bin/rm $(OBJ_FILES) $(BINARY) 

realclean:       clean
