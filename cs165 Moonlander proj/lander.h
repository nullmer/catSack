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

#ifndef LANDER_H
#define LANDER_H

#include "velocity.h"
#include "uiDraw.h"

class Lander
{
  public:
  Lander() : width(12), fuel(1000), health(1000.0), mass(width * width), velocity(0, 0, 0, 0) {}
  
   //Getters
   int getFuel()           { return fuel;                }
   Point getPoint()        { return velocity.getPoint(); }
   float getX()            { return velocity.getX();     }
   float getY()            { return velocity.getY();     }
   Velocity getVelocity()  { return velocity;            }
   float getDx()           { return velocity.getDx();    }
   float getDy()           { return velocity.getDy();    }
   float getMag()          { return velocity.getMag();   }
   float getMass()         { return mass;                }
   float getHealth()         { return health;              }

   //Setters
   void setX(float x)       { velocity.setX(x);      }
   void setY(float y)       { velocity.setY(y);      }
   void setDx(float dx)     { velocity.setDx(dx);    }
   void setDy(float dy)     { velocity.setDy(dy);    }
   void setPoint(Point pt)  { velocity.setPoint(pt); }
   void addHealth(float h)    { health += h;           }
   void setHealth(float h)    { health  = h;           }

   void draw(bool a, bool b, bool c);
   void advance(bool a, bool b, bool c, const Velocity & w);
   bool isCloseTo(const Point & pt, int prox)
   {
       return( (getX() - (width / 2) < (pt.getX() + prox/2) && getX() + (width / 2) > (pt.getX() - prox/2)) &&
               (getY() - (width / 2) < (pt.getY() + prox/2) && getY() + (width / 2) > (pt.getY() - prox/2))   );
   }
   
  private:
   int fuel;
   float mass;
   float width;
   float health;
   Velocity velocity;
};

#endif // for lander-pander-wander-mcGander.eyyych
