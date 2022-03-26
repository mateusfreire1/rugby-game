// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  static int turn_count = 0; //Variable to keep track of turn count.
  position_t x = attacker_position;
  srand(time(NULL));

  if (get_spy_number_uses(defender_spy) < 1 && turn_count == 3){
    x = get_spy_position(defender_spy); //Perform spying.
  }
  
  if (turn_count < 3){            //For the first three turns, move upwards.
    turn_count++;
    return (direction_t) DIR_UP;
  }
  else{                           
    if (x.j > attacker_position.j && (abs(x.j)-abs(x.j)) >= 2){       //If defender is below and far away, move right.
      turn_count++;
      return (direction_t) DIR_RIGHT;
    }
    else if (x.j > attacker_position.j && (abs(x.j)-abs(x.j)) < 2){   //If defender is below but not far, move up again.
      turn_count++;
      return (direction_t) DIR_UP;
    }
    else if (x.j < attacker_position.j && (abs(x.j)-abs(x.j)) < 2){   //If defender is above, move down.
      turn_count++;
      return (direction_t) DIR_DOWN;
    }
    else{     //Main movement logic, where the attacker always tends to move right, however with a chance to deviate paths.
      turn_count++;
      int fate = rand() % 100 + 1;
      if (fate > 90)
        return (direction_t) DIR_UP;
      else if (fate > 50 && fate <= 90)
        return (direction_t) DIR_RIGHT;
      else if (fate > 30 && fate <= 50)
        return (direction_t) DIR_UP_RIGHT;  
      else if (fate > 10 && fate <= 30)
        return (direction_t) DIR_DOWN_RIGHT;
      else
        return (direction_t) DIR_DOWN;
    }
  }
  

  
}

/*----------------------------------------------------------------------------*/
