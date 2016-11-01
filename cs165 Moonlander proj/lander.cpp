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
#include "lander.h"

void Lander::draw(bool isLeft, bool isRight, bool isDown)
{
   Point pt = velocity.getPoint();
   drawLander( pt );

   if (fuel)
   {
      drawLanderFlames( pt,
                        isDown,
                        isLeft,
                        isRight );
   }
}

void Lander::advance(bool isLeft, bool isRight, bool isDown, const Velocity & windHitGrav)
{
   //Velocity grav(0,0,0,-0.06);
   //velocity += grav;
   velocity += windHitGrav;
   
   if(fuel)
   {
      float dx = 0;
      float dy = 0;      
      if(isLeft)
      { dx +=  0.25; fuel--; }
      if(isRight)
      { dx -=  0.25; fuel--; }
      if(isDown)
      { dy +=  0.25; fuel--; }
      Velocity boost(0,0,dx,dy);
      velocity += boost;
   }

   velocity++;
}
