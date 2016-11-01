###############################################################
# Program:
#     Project 02, Moon Lander
#     Brother Comeau, CS165
# Author:
#     Nathan Ulmer     
# Summary:
#     Regular Moon Lander WITH elevation-based wind, dust particles for show,
#     and floating debris that can push/kill you. Also a dashboard displaying
#     fuel, speed, and health, all of which are color-coded for urgency.
#
###############################################################

LFLAGS = -lglut -lGLU

###############################################################
# Programs:
#    a.out:         The moon lander game
###############################################################
#a.out: ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o debris.o
	#g++ -o a.out ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o $(LFLAGS)
  #tar -j -cf moonLander.tar makefile *.h *.cpp 

a.out: ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o debris.o
	g++ -o a.out ground.o game.o uiInteract.o uiDraw.o point.o velocity.o lander.o $(LFLAGS)
	tar -j -cf project2.tar makefile *.h *.cpp
###############################################################
# Individual files
#    ground.o      Displays the ground and platform
#    game.o        The moon game
#    uiInteract.o  Handles input events
#    uiDraw.o      Drawing functions
#    point.o       Point class
#    debris.o      Debris class
#    lander.o      Lander class
#    velocity.o    Velocity class
###############################################################
game.o: game.cpp uiDraw.h uiInteract.h point.h ground.h lander.h velocity.h debris.h
	g++ -c game.cpp

ground.o: ground.cpp ground.h
	g++ -c ground.cpp

uiInteract.o: uiInteract.cpp uiInteract.h
	g++ -c uiInteract.cpp

lander.o: lander.cpp lander.h
	g++ -c lander.cpp
 
debris.o: debris.cpp debris.h
	g++ -c debris.cpp

velocity.o: velocity.cpp velocity.h
	g++ -c velocity.cpp

uiDraw.o: uiDraw.cpp uiDraw.h
	g++ -c uiDraw.cpp

point.o: point.cpp point.h
	g++ -c point.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.tar *.o *~

all:
	a.out
