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

#include "velocity.h"

// overload <<, ==, and !=
std::ostream & operator << (std::ostream & out, Velocity & rhs)
{
   // no setf() type stuff here then?
   out << "(" << rhs.getX() << ", " << rhs.getY() << ") ["
       << rhs.getDx() << ", " << rhs.getDy() << "]";
   return out;
}

bool operator == (Velocity & lhs, Velocity & rhs)
{
   if ( int(lhs.getDx() * 1000.0) == int(rhs.getDx() * 1000.0) )
      if ( int(lhs.getDy() * 1000.0) == int(rhs.getDy() * 1000.0) )
         if ( int(lhs.getX() * 1000.0) == int(rhs.getX() * 1000.0) )
            if ( int(lhs.getY() * 1000.0) == int(rhs.getY() * 1000.0) )
               return true;
   return false;
}

bool operator != (Velocity & lhs, Velocity & rhs)
{
   return !(lhs == rhs);
}

// Overloaded Friend Operators
// Velocity > float
bool operator  > (Velocity & v1, float mag)
{
   return v1.magnitude > mag;
}

//     ''   <   ''
bool operator  < (Velocity & v1, float mag)
{
   return v1.magnitude < mag;   
}

//     ''   >=  ''
bool operator >= (Velocity & v1, float mag)
{
   return v1.magnitude >= mag;   
}

//     ''   <=  ''
bool operator <= (Velocity & v1, float mag)
{
   return v1.magnitude <= mag;   
}

// Velocity  -  Velocity ... idk what/why we're doing this like this...
float operator - (Velocity & v1, Velocity & v2)
{
   float slicePercent =
      1/( fmax(
               fmax(fabs(v1.dx), fabs(v1.dy))
             , fmax(fabs(v2.dx), fabs(v2.dy)) ) );
   float distSqd = 0;
   float minDistSqd =
      pow(((v1.getX() + v1.dx)-(v2.getX() + v2.dx)), 2)+
      pow(((v1.getY() + v1.dy)-(v2.getY() + v2.dy)), 2);

   for (float p = 0; p <= 1; p += slicePercent)
   {
      distSqd = ( pow(
                      ( (v1.getX() + v1.dx * p) - (v2.getX() + v2.dx * p) ), 2)
                 + pow(
                      ( (v1.getY() + v1.dy * p) - (v2.getY() + v2.dy * p) ), 2) );
      minDistSqd = fmin(distSqd, minDistSqd);
   }

   return sqrt(minDistSqd);

}
