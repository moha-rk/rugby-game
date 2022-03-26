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
/*                          PRIVATE FUNCTIONS HEADERS                         */
/*----------------------------------------------------------------------------*/

position_t get_defender_position_hack(Spy defender_spy);
direction_t get_next_attacker_move(
  position_t attacker_position, 
  position_t last_position, 
  direction_t last_move, 
  size_t field_height);
direction_t draw_next_move();

bool will_move_hit_wall(direction_t dir, position_t attacker_position, size_t field_height);
bool equal_directions_a(direction_t d1, direction_t d2);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameter, remove this line later
  UNUSED(defender_spy);

  // Function state
  static size_t field_height = 0;
  static direction_t last_move = DIR_STAY;
  static position_t last_position = INVALID_POSITION;

  if (equal_positions(last_position, (position_t) INVALID_POSITION)) {
    last_position = attacker_position;
    field_height = attacker_position.i*2;
  }

  direction_t next_move = 
    get_next_attacker_move(attacker_position, last_position, last_move, field_height);
  last_move = next_move;
  last_position = attacker_position;
  return next_move;
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

position_t get_defender_position_hack(Spy defender_spy) {
  if (defender_spy == NULL) return (position_t) { 0, 0 };
  
  Item defender_item = (Item) (*(long int*)defender_spy);
  return get_item_position(defender_item);
}

direction_t get_next_attacker_move(
    position_t attacker_position, 
    position_t last_position, 
    direction_t last_move, 
    size_t field_height) {
  direction_t next_move = draw_next_move();
  if (will_move_hit_wall(next_move, attacker_position, field_height)) {
    next_move = (direction_t) DIR_RIGHT;
  }
  if (equal_positions(attacker_position, last_position)
      && equal_directions_a(last_move, next_move)) {
    if (next_move.i == (direction_t) DIR_RIGHT.i) {
      next_move.i = (direction_t) DIR_UP_RIGHT.i;
      if (will_move_hit_wall(next_move, attacker_position, field_height)) {
        next_move.i = (direction_t) DIR_DOWN_RIGHT.i;
      }
    }
    else {
      next_move = (direction_t) DIR_RIGHT;
    }
  }
  return next_move;
}

direction_t draw_next_move() {
  time_t t;
  direction_t move;
  srand((unsigned) time(&t));
  int random_number = rand();
  switch (random_number%3)
  {
  case 0:
    move = (direction_t) DIR_DOWN_RIGHT;
    break;

  case 1:
    move = (direction_t) DIR_UP_RIGHT;
    break;

  default:
    move = (direction_t) DIR_RIGHT;
    break;
  }
  return move;
}

bool will_move_hit_wall(direction_t dir, position_t attacker_position, size_t field_height) {
  // Check if move will hit upper or lower walls
  size_t new_i = attacker_position.i + dir.i;
  if (new_i >= field_height || new_i <= 0) return true;
  return false;
}

bool equal_directions_a(direction_t d1, direction_t d2) {
  return (d1.i == d2.i && d1.j == d2.j);
}

/*----------------------------------------------------------------------------*/
