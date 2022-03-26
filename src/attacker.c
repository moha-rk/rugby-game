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

void set_initial_attacker_position(position_t attacker_position);
void set_field_height();

bool will_move_hit_wall(direction_t dir, position_t attacker_position);

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

position_t initial_attacker_position = {0, 0};
size_t field_height = 0;

bool first_round = true;

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {
  // TODO: unused parameter, remove this line later
  UNUSED(defender_spy);
  if (first_round) {
    set_initial_attacker_position(attacker_position);
    set_field_height();
    first_round = false
  }

  // TODO: Implement Attacker logic here
  return (direction_t) DIR_RIGHT;
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

void set_initial_attacker_position(position_t attacker_position) {
  initial_attacker_position.i = attacker_position.i;
  initial_attacker_position.j = attacker_position.j;
}

void set_field_height() {
  field_height = initial_attacker_position.i*2;
}

bool will_move_hit_wall(direction_t dir, position_t attacker_position) {
  // Check if move will hit upper or lower walls
  size_t new_i = attacker_position.i + dir.i;
  if (new_i >= field_height || new_i <= 0) return true;
  return false;
}

/*----------------------------------------------------------------------------*/
