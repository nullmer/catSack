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
************************************************************************
 * IT'S ALLLLIIIIIIIIIVVVE!
 * so much help from: Br. Comeau (thanks!!!)
 ****************************************/

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "ground.h"
#include "lander.h"
#include "debris.h"
#include <cmath>
#include <cstdlib>
#include <string>


#define MAX_LANDMAG  200     // any magnitude > this / 1000 is too fast to land
#define X_SIZE       600     // window width (MULTIPLES OF 100 PLEASE)
#define GRAVITY      -0.06   // arbitrary!

// set the bounds of the drawing rectangle
float Point::xMin = -(X_SIZE / 2.0);
float Point::xMax =  (X_SIZE / 2.0);
float Point::yMin = -(X_SIZE / 2.0);
float Point::yMax =  (X_SIZE / 2.0);

/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
   // create the game
   Game() : dead(false), landed(false), isLeft(false), isRight(false), 
            isDown(false), statusMsg(""), gravity(), lander(), dash(), storm(), wind(0)
   {
      gravity.setDy(GRAVITY);
      
      lander.setX(lander.getPoint().getXMax() - 30);
      lander.setY(lander.getPoint().getYMax());
      lander.setDx(-2.0);
      lander.setDy(-0.012);
      
      dash.setX(dash.getXMin() + 15);
      dash.setY(dash.getYMax() - 15);
      
      wind = float( (rand() % 30 + 10)  / 1000.0 ) ;
      storm.setDx(wind);
      
      setDust();
      setDebris();
   }
   // Destructor
   ~Game()
   {
     delete [] dust;
     delete [] debris;
   }
            
   // handle user input
   void input(const Interface & ui);

   // advance the game
   void advance();
         
   // draw stuff
   void draw();
   
private:
   bool justLanded();
   void drawDash();
   void updateWind(const Point & pt);
   void setDust();
   void setDebris();
   
   std::string statusMsg;
   bool dead;
   bool landed;
   Velocity gravity;
   Ground ground;
   Lander lander;
   bool isLeft;
   bool isRight;
   bool isDown;

   //extra credit stuff
   Point dash;
   float wind;
   Velocity storm;
   Velocity dust[X_SIZE];
   Debris debris[X_SIZE / 50];

};

//SET DEBRIS*********************************
void Game::setDebris()
{
  int j = -(X_SIZE/2);
  float d;
  for (int i = 0; i < (X_SIZE / 50); i++)
  {
    (i % 2 == 0) ? d = -1.0 : d = 1.0;
    if ( j <= (X_SIZE/2)) 
    {
    int sq = (rand() % 30 + 15);
      debris[i].setX(j + (rand() % 60 + 20));
      debris[i].setY(X_SIZE/4 + ((rand() % (X_SIZE/5) + 1) * d));
      debris[i].setDx((rand() % 20 + 1) * 0.1 * -d);
      debris[i].setDy((rand() % 15 + 10) * -0.01);
      debris[i].setWidth(sq);
      debris[i].setHeight(sq);
      debris[i].setRotation((rand() % 15 + 1) * d);
      j+=50;
    }
  }
  
}

//SET DUST***********************************
void Game::setDust()
{ 
  //float skew = 4.0;
  for (int i = 0; i < X_SIZE; i+=(X_SIZE / 10))
  {
    int k = i / (X_SIZE / 100);
    for (int j = 0; j < (X_SIZE / 1); j+=(X_SIZE / 20)) //
    {
      //skew = -(skew - (rand() % 30 + 15));
      // +x +y quadrant
      dust[k + (j / (X_SIZE / 20))].setX( (X_SIZE / 2) - i + (rand() % 60 + 15));
      dust[k + (j / (X_SIZE / 20))].setY( (X_SIZE / 2) - j + (rand() % 60 + 15));
 
      // -x +y quadrant
      dust[k + (j / (X_SIZE / 20)) + (X_SIZE*1/4)].setX( -(X_SIZE / 2) + i + (rand() % 60 + 15));
      dust[k + (j / (X_SIZE / 20)) + (X_SIZE*1/4)].setY(  (X_SIZE / 2) - j + (rand() % 60 + 15));

      // -x -y quadrant
      dust[k + (j / (X_SIZE / 20)) + (X_SIZE*2/4)].setX( -(X_SIZE / 2) + i + (rand() % 60 + 15));
      dust[k + (j / (X_SIZE / 20)) + (X_SIZE*2/4)].setY( -(X_SIZE / 2) + j + (rand() % 60 + 15));

      // +x -y quadrant
      dust[k + (j / (X_SIZE / 20)) + (X_SIZE*3/4)].setX(  (X_SIZE / 2) - i + (rand() % 60 + 15));
      dust[k + (j / (X_SIZE / 20)) + (X_SIZE*3/4)].setY( -(X_SIZE / 2) + j + (rand() % 60 + 15));

    }
  }
}
/******************************************
 * GAME :: LANDED
 * Did we land successfully?
 ******************************************/
bool Game :: justLanded()
{
   return (
   //Lander's Y is at least 5 pixels above || below Platform's Y
      ( lander.getY() <=
        (ground.getPlatformPosition().getY() + 5) &&
        lander.getY() >=
        (ground.getPlatformPosition().getY() - 5) )
      &&
   //Landers X is within the range of Platform's width
      ( lander.getX() <=
        (ground.getPlatformPosition().getX() +
         (ground.getPlatformWidth() / 2.0))    &&
        lander.getX() >=
        (ground.getPlatformPosition().getX() -
         (ground.getPlatformWidth() / 2.0))    )
      &&
   //Landers Magnitude isn't too high
      ( int(lander.getMag() * 100) < MAX_LANDMAG )
      &&
   //Lander's Dy is negative. No landing from the side/beneath weirdo...
      ( int(lander.getDy() * 1000) < 0) );
}

//UPDATE WIND ******************************
void Game::updateWind(const Point & pt)
{
   float tempWind = wind;

   if (pt.getY() < (X_SIZE * -.25) ) 
      tempWind = (wind * .33);
   else if (pt.getY() < 0 ) 
      tempWind = (wind * .55); 
   else if (pt.getY() < (X_SIZE * .25) ) 
      tempWind = (wind * .77); 

   storm.setDx(tempWind);
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game :: advance()
{
   // These are used for managing collisions
   Velocity collisionD;
   Velocity collisionL;
   float dx = 0;
   float dy = 0;
   float damage = 0;
   float massReductionPercent = 0.0001;
   float fpsReductionPercent = float( 1.0/60.0 );
   
   // advance Dust particles
   for (int i = X_SIZE; i > -1; i--)
   {
      updateWind(dust[i].getPoint());
      dust[i].setDx(storm.getDx() * 300); // lets make the wind look faster...
      dust[i]++;
      // handle wrapping
      if (dust[i].getX() > X_SIZE/2)
        dust[i].setX(-(X_SIZE/2) + (dust[i].getX() - X_SIZE/2));
      if (dust[i].getX() < -(X_SIZE/2))
        dust[i].setX((X_SIZE/2) + (dust[i].getX() + X_SIZE/2));
   }
   
   
   // advance debris and check for collisions
   for (int i = 0; i < X_SIZE/50; i++)
   {
      // handle wrapping
      if (debris[i].getX() > X_SIZE/2)
        debris[i].setX(-(X_SIZE/2) + (debris[i].getX() - X_SIZE/2));
      if (debris[i].getX() < -(X_SIZE/2))
        debris[i].setX((X_SIZE/2) + (debris[i].getX() + X_SIZE/2));
      if (debris[i].getY() > X_SIZE/2)
        debris[i].setY(-(X_SIZE/2) + (debris[i].getY() - X_SIZE/2));
      if (debris[i].getY() < -(X_SIZE/2))
        debris[i].setY((X_SIZE/2) + (debris[i].getY() + X_SIZE/2));
      
      // if lander and debris collide, handle that change in velocity for both DEBRIS and LANDER
      if (lander.isCloseTo(debris[i].getPoint(), debris[i].getHeight() ) )
      {   
          Lander fake; //drawLander(fake.getPoint());
          // ((dx / mag) x mass) + (((dy / mag) x %mass) + equal-and-opposite push, all x some fraction of a second
          collisionD.setDx(((lander.getDx() / lander.getMag() * lander.getMass()) 
          - (debris[i].getDx() / debris[i].getMag() * debris[i].getMass())
          )* massReductionPercent / fpsReductionPercent);
          
          collisionD.setDy(((lander.getDy() / lander.getMag() * lander.getMass()) 
          - (debris[i].getDy() / debris[i].getMag() * debris[i].getMass())
          )* massReductionPercent / fpsReductionPercent);
          
          collisionL.setDx(((debris[i].getDx() / debris[i].getMag() * debris[i].getMass()) 
          - (lander.getDx() / lander.getMag() * lander.getMass()) 
          )* massReductionPercent / fpsReductionPercent);
          
          collisionL.setDy(((debris[i].getDy() / debris[i].getMag() * debris[i].getMass()) 
          - (lander.getDy() / lander.getMag() * lander.getMass())
          )* massReductionPercent / fpsReductionPercent);
          
          damage -= debris[i].getForce() * 0.01 ;
      }
      else
      {
          collisionD.setDx(0);
          collisionD.setDy(0);
          collisionL.setDx(0);
          collisionL.setDy(0);
      }

      debris[i].advance(collisionD); // advance the debris
   }
   
   // check for landing
   if (justLanded())
   {
       statusMsg = "[ LANDED ]";
       landed = true;
   }

   // check for crash
   else if ( lander.getPoint().getY() <=
             ground.getGround(lander.getPoint()).getY() 
             )
   {
      lander.setHealth(0);
      dead = true;
      statusMsg = "[ CRASHED ]";
   }
   // check for out of bounds
   // - 20-pix safe zone outside of window
   // - no Y upper limit
   else if( fabs(lander.getX()) > (X_SIZE / 2.0 + 20.0) 
            )
   {
      lander.setHealth(0);
      dead = true;
      statusMsg = "[ CRASHED ]";
   }
   // move lander
   else
   {
      updateWind(lander.getPoint());
      lander.advance( isLeft, isRight, isDown, storm + collisionL + gravity);
      lander.addHealth(damage);
      if (int(lander.getHealth()) < 0)
      {
        lander.setHealth(0.0);
        dead = true;
        statusMsg = "[ CRASHED ]";
      }
   }

   
}

/***************************************
 * GAME :: input
 * accept input from the user
 ***************************************/
void Game :: input(const Interface &ui)
{
   isLeft  = ui.isLeft();
   isRight = ui.isRight();
   isDown  = ui.isDown();   
}

// DRAWDASH()******************************
void Game::drawDash()
{
   int color = 0;

   // draw the fuel
   Point pt = dash;
   drawText(pt, "fuel:");
   pt.setY(pt.getY() - 7);
   int fuel = lander.getFuel();
   color = 0;
   if      (fuel > 400) color = GREEN;
   else if (fuel < 200) color = RED;
   else                 color = YELLOW;   
   drawNumber( pt, fuel, color);

   // draw the lander's speed
   pt.setY(pt.getY() - 25);
   drawText(pt, "speed:");
   pt.setY(pt.getY() - 7);
   int mag = int(lander.getMag() * 100.0);
   color = 0;
   if      (mag < 201) color = GREEN;
   else if (mag > 399) color = RED;
   else                color = YELLOW;
   drawNumber( pt, mag, color );
   
   // draw the lander's health
   pt.setY(pt.getY() - 25);
   drawText(pt, "health:");
   pt.setY(pt.getY() - 7);
   int health = int(lander.getHealth());
   color = 0;
   if      (health > 699) color = GREEN;
   else if (health < 400) color = RED;
   else                   color = YELLOW;
   drawNumber( pt, health, color );
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game :: draw()
{
   Point msgPt(-30, 160);
   if (dead)
      drawText(msgPt, statusMsg.c_str());
   else if (landed)
      drawText(msgPt, statusMsg.c_str());
   else
      lander.draw(isLeft, isRight, isDown);
   
   //draw the dashboard display   
   drawDash();
   
   // draw ground
   ground.draw();
   
   // draw debris field
   for (int i = 0; i < X_SIZE/50; i++)
   {
     debris[i].draw();
   }

   // draw Dust particles
   for (int i = 0; i < X_SIZE; i++)
   {
       drawDot(dust[i].getPoint());
   }
}

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface *pUI, void *p)
{
   Game *pGame = (Game *)p;

   pGame->input(*pUI);   
   
   pGame->advance();
   
   pGame->draw();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * the game and call the display engine.
 * That is all!
 *********************************/
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Moon Lander");
   Game game;
   ui.run(callBack, &game);
   
   return 0;
}
