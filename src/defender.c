// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {

  static int turn_count = 0;  //Variable to keep track of turn count.
  static int tendency = 0;    //Variable to keep track of the attacker's approximate direction.
  position_t x = defender_position;
  srand(time(NULL));

  if (get_spy_number_uses(attacker_spy) < 1 && turn_count == 2){
    x = get_spy_position(attacker_spy);    //Perform spying.
    if (x.j > defender_position.j){        //If attacker is below defender, move down and restart turn cycle.
      turn_count = 4;
      tendency = 1;
      return (direction_t) DIR_DOWN;
    }
    else if (x.j < defender_position.j){   //If attacker is above defender, move up and restart turn cycle.
      turn_count = 4;
      tendency = -1;
      return (direction_t) DIR_UP;
    }
    else {                                //If attacker is at the same height as defender, stay and restart turn cycle.
      turn_count = 4;
      tendency = 0;
      return (direction_t) DIR_STAY;
    }
  }

  //Create a cycle of moves that repeats periodically, with a chance to deviate based on the position recieved on the spy.
  int turn_cycle = turn_count % 4;
  int fate = rand() % 100 + 1;
  if (fate > 90){
    switch (tendency){
    case -1:
        turn_count++;
        return (direction_t) DIR_UP;
    case 0:
        turn_count++;
        return (direction_t) DIR_STAY;
    case 1:
        turn_count++;
        return (direction_t) DIR_DOWN;
    }
  }
  else{
    switch(turn_cycle){
      case 0:
          turn_count++;
          return (direction_t) DIR_UP_LEFT;
      case 1:
          turn_count++;
          return (direction_t) DIR_DOWN_RIGHT;
      case 2:
          turn_count++;
          return (direction_t) DIR_DOWN_LEFT;
      case 3:
          turn_count++;
          return (direction_t) DIR_UP_RIGHT;
    }

  }
  
  
  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
