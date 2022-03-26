// Standard headers
#include <stdio.h>

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

bool will_move_hit_wall(direction_t dir, position_t attacker_position, size_t field_height);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameter, remove this line later
  UNUSED(defender_spy);

  // Function state
  static position_t initial_attacker_position = INVALID_POSITION;
  static size_t field_height = 0;

  if (equal_positions(initial_attacker_position, (position_t) INVALID_POSITION)) {
    initial_attacker_position = attacker_position;
    field_height = initial_attacker_position.i*2;
  }

  direction_t next_move = (direction_t) DIR_UP_RIGHT;
  if (will_move_hit_wall(next_move, attacker_position, field_height)) {
    next_move = (direction_t) DIR_RIGHT;
  }
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

bool will_move_hit_wall(direction_t dir, position_t attacker_position, size_t field_height) {
  // Check if move will hit upper or lower walls
  size_t new_i = attacker_position.i + dir.i;
  if (new_i >= field_height || new_i <= 0) return true;
  return false;
}

/*----------------------------------------------------------------------------*/
