#include "Player.h"
//Collision detection function
bool isCollision( Rectangle A, Rectangle B )
{
     if ( A.x < B.x + B.w &&
     A.x + A.w > B.x &&
     A.y < B.y + B.h &&
     A.y + A.h > B.y )
     {
          return true;
     }
     return false;
}
