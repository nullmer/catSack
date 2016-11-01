/***********************************************************************
* Program:
*    Project 02, Moon Lander
*    Brother Comeau, CS165
* Author:
*    Nathan Ulmer
* Summary: 
*    This is a header for an important file in MOOn LANDER
*
*
************************************************************************/
/***********************************************************************
 * Header File:
 *    GROUND : A class representing the lunar landscape
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything you needed to know about the ground but were afraid to ask
 ************************************************************************/

#ifndef GROUND_H
#define GROUND_H

#include "uiDraw.h"

#define BUMPY       0.5    // how bumpy is the ground
#define PLATFORM    31     // the width of the platform

/********************************************
 * GROUND
 * Terra-firma, except made of cheese
 ********************************************/
class Ground
{
public:
   // create the terrain
   Ground();
   
   // destroy the (moon) like a great scroll
   ~Ground()
   {
      delete [] ground;
   }
      
   // display the ground on the screen
   void draw() const;
   
   // did we leave the screen or enter the ground?
   bool crashed(const Point & point) const;
   
   // what is our elevation?
   Point getGround(const Point & pt) const;
      
   // generate a new terrain 
   void generateGround();
   
   // get the platform point
   Point getPlatformPosition() const { return platform; }

   // what is the width of the platform?
   int getPlatformWidth() const { return PLATFORM; }
   
private:

   Point platform;   // position of the platform
   int xSize;      // horizontal size of the world
   float * ground; // the array of the groud positions
};


#endif
