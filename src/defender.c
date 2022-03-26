// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

position_t get_attacker_position_hack(Spy attacker_spy);
direction_t get_next_defender_move(
  position_t attacker_position, 
  position_t defender_position,
  position_t last_position,
  direction_t last_move);

bool position_equals(position_t p1, position_t p2);
bool direction_equals(direction_t d1, direction_t d2);
bool tried_to_move(direction_t move);
size_t difference_between_positions(size_t s1, size_t s2);

/*----------------------------------------------------------------------------*/
/*                              PRIVATE VARIABLES                             */
/*----------------------------------------------------------------------------*/

bool first_defender_round = true;

direction_t last_move = DIR_STAY;
position_t last_position;

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  if (first_defender_round) {
    last_position = defender_position;
    first_defender_round = false;
  }
  position_t hack_attacker_position = get_attacker_position_hack(attacker_spy);
  direction_t next_move = 
    get_next_defender_move(hack_attacker_position, defender_position, last_position, last_move);
  last_move = next_move;
  return next_move;
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

position_t get_attacker_position_hack(Spy attacker_spy) {
  if (attacker_spy == NULL) return (position_t) { 0, 0 };
  
  Item attacker_item = (Item) (*(long int*)attacker_spy);
  return get_item_position(attacker_item);
}

direction_t get_next_defender_move(
    position_t attacker_position, 
    position_t defender_position,
    position_t last_position,
    direction_t last_move) {
  int i_move, j_move;
  if (defender_position.i > attacker_position.i) {
    i_move = -1;
  }
  else if (defender_position.i < attacker_position.i) {
    i_move = +1;
  }
  else {
    i_move = 0;
  }
  if (defender_position.j > attacker_position.j) {
    j_move = -1;
  }
  else if (defender_position.j < attacker_position.j) {
    j_move = +1;
  }
  else {
    j_move = 0;
  }

  direction_t current_move = (direction_t) {i_move, j_move};

  //If the defender stayed in the same position and is trying to make the same move,
  //we have to make a different one
  if (position_equals(defender_position, last_position) && tried_to_move(last_move)
      && direction_equals(last_move, current_move)) {
    if (current_move.i == 0) {
      current_move.j = 0;
    }
    else if (current_move.j == 0) {
      current_move.i = 0;
    }
    else {
      if (difference_between_positions(attacker_position.i, defender_position.i) > 
          difference_between_positions(attacker_position.j, defender_position.j)) {
        current_move.j = 0;
      }
      else {
        current_move.i = 0;
      }
    }
  }
  return current_move;
}

size_t difference_between_positions(size_t s1, size_t s2) {
  if (s1 > s2)
    return s1 - s2;
  return s2 - s1;
}

bool position_equals(position_t p1, position_t p2) {
  return (p1.i == p2.i && p1.j == p2.j);
}

bool direction_equals(direction_t d1, direction_t d2) {
  return (d1.i == d2.i && d1.j == d2.j);
}

bool tried_to_move(direction_t move) {
  return (move.i != (direction_t) DIR_STAY.i || move.j != (direction_t) DIR_STAY.j);
}

/*----------------------------------------------------------------------------*/
