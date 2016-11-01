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

 #ifndef DEBRIS_H
 #define DEBRIS_H
 
 #include "velocity.h"
 #include "uiDraw.h"
 //#include <cmath>

class Debris
{
  private:
   float width;
   float height;
   float mass;
   float force;
   int rotation;
   Velocity velocity;
   
   void setMass() {mass = width * height;}
   void setForce() {force = fabs(mass * velocity.getMag());}

  public:
  Debris() : width(1), height(1), rotation(1), velocity() 
  {
    setMass();
    setForce();
  }
   
   //Getters
   float getWidth()        { return width;               }
   float getHeight()       { return height;              }
   int getRotation()       { return rotation;            }
   float getForce()        { return force;               }
   float getMass()         { return mass;                }
   Point getPoint()        { return velocity.getPoint(); }
   float getX()            { return velocity.getX();     }
   float getY()            { return velocity.getY();     }
   Velocity getVelocity()  { return velocity;            }
   float getDx()           { return velocity.getDx();    }
   float getDy()           { return velocity.getDy();    }
   float getMag()          { return velocity.getMag();   }

   //Setters
   void setX(float x)       { velocity.setX(x);      }
   void setY(float y)       { velocity.setY(y);      }
   void setDx(float dx)     { velocity.setDx(dx); setMass(); setForce();   }
   void setDy(float dy)     { velocity.setDy(dy); setMass(); setForce();   }
   void setPoint(Point pt)  { velocity.setPoint(pt); }
   void setWidth(float w)   { width = w; setMass(); setForce();            }
   void setHeight(float h)  { height = h; setMass(); setForce();           }
   void setRotation(int r)  { rotation = r;          }
   
   void draw()
   {
     Point pt = velocity.getPoint();
     drawRect(pt, width, height, rotation);
   }

   void advance(const Velocity & hit)
   {
     (rotation > 0)? rotation++ : rotation-- ;
     velocity += hit;
     velocity++;
   }
   
};

#endif // for debris.h