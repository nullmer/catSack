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

#ifndef VELOCITY_H
#define VELOCITY_H

#include "point.h"
#include <iostream> // for "<<" operator
#include <cmath>

class Velocity
{
  private:
   float dx;
   float dy;
   float magnitude;
   Point point;

  public:
  Velocity() : dx(0), dy(0), point() { setMag(); }
  Velocity(float x, float y, float dx, float dy)
     : dx(dx), dy(dy)
   {
      point.setX(x);
      point.setY(y);
      setMag();
   }
   // ~Velocity();

   friend bool operator  > (Velocity & v1, float mag);
   friend bool operator  < (Velocity & v1, float mag);
   friend bool operator >= (Velocity & v1, float mag);
   friend bool operator <= (Velocity & v1, float mag);
   friend float operator - (Velocity & v1, Velocity & v2);

   // = operator
   void operator = (const Velocity &rhs)
   {
      this->setX(rhs.getX());
      this->setY(rhs.getY());
      this->dx = (rhs.getDx());
      this->dy = (rhs.getDy());
      setMag();
   }
   // += operator
   void operator += (const Velocity &rhs)
   {
      this->dx += rhs.getDx();
      this->dy += rhs.getDy();
      setMag();
   }
   // ++_ operator Prefix
   void operator ++()
   {
      this->setX(this->getX() + dx);
      this->setY(this->getY() + dy);      
   }
   // _++ operator Postfix
   void operator ++ (int dummy)
   {
      this->setX(this->getX() + dx);
      this->setY(this->getY() + dy);            
   }
   // + operator
    Velocity  operator + (const Velocity &rhs)
   {
      Velocity newVel;

      newVel.setX(this->getX());
      newVel.setY(this->getY());
      newVel.dx += (this->dx + rhs.getDx());
      newVel.dy += (this->dy + rhs.getDy());
      setMag();
      return newVel;
   }

   
   // Accessors
   float getX()     const { return point.getX(); }
   float getY()     const { return point.getY(); }
   float getDx()    const { return dx;           }
   float getDy()    const { return dy;           }
   float getMag()   const { return magnitude;    }
   Point getPoint()       { return point;        }

   // Mutators
   void setX(float x)   { point.setX(x); }
   void setY(float y)   { point.setY(y); }
   void setDx(float dx) { this->dx = dx; setMag(); }
   void setDy(float dy) { this->dy = dy; setMag(); }
   void setPoint(const Point & pt) { point = pt; setMag(); }

  private:
   void setMag() { magnitude = sqrt(pow(dx, 2) +  pow(dy, 2)); }
   
};

// overload <<, ==, and !=
std::ostream & operator << (std::ostream & out, Velocity & rhs);
bool operator == (Velocity & lhs, Velocity & rhs);
bool operator != (Velocity & lhs, Velocity & rhs);

#endif // for velocity.h
