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

/*----------------------------------------------------------------------------*/
/*                              PRIVATE VARIABLES                             */
/*----------------------------------------------------------------------------*/

bool first_defender_round = true;

position_t last_position;

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(defender_position);
  UNUSED(attacker_spy);

  // TODO: Implement Defender logic here
  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
/*                             PRIVATE FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

position_t get_attacker_position_hack(Spy attacker_spy) {
  if (attacker_spy == NULL) return (position_t) { 0, 0 };
  
  Item attacker_item = (Item) (*(long int*)attacker_spy);
  return get_item_position(attacker_item);
}
/*----------------------------------------------------------------------------*/
