#include "asteroids.h"

// Alex Young
// R00219993
// Greedy Approach 

struct ship_action move_ship(int field[][FIELD_WIDTH], void *ship_state){
    
    // Initialize 'i' and 'j' variables for our loops
    int i, j;
    
    // Distance from our ship to the nearest asteroid 
    int distance = 5;
    
    // Row where the nearest asteroid is located, set to -1 initially 
    int asteroid_row = -1;
    
    // Variable used as our row with no asteroids updated from our loop, set to -1 initially 
    int free_row = -1;

    // If ship state is null, initialize to middle row
    if (ship_state == NULL){
        ship_state = malloc(sizeof(int));
        *(int *)ship_state = FIELD_HEIGHT / 2;
    }
    
    // Get the current row of the ship from the ship state
    int ship_row = *(int *)ship_state;
    
    // Find the nearest asteroid in the same row
    for (i = 0; i < FIELD_HEIGHT; i++){
        
        // If there is a ship in this row, skip it
        if (field[i][SHIP_WIDTH] != 0)
            continue;
        
        for (j = 0; j < FIELD_WIDTH; j++){
            
            // If there is an asteroid in this cell, calculate the distance to the ship
            if (field[i][j] == ASTEROID_VAL){
                // Update the distance and row of the nearest asteroid
                // We use the abs (absolute value) method as the distance between the ship and asteroid may be negative
                if (abs(i - ship_row) < distance){
                    distance = abs(i - ship_row);
                    asteroid_row = i;
                }
                
                // Break out of the inner loop as soon as we find an asteroid in this row
                break;
            }
        }
        
        // If there are no asteroids in this row and free_row has not been set, this is the next free row
        if (free_row == -1 && j == FIELD_WIDTH)
            free_row = i;
    }
    
    // Move towards the nearest asteroid
    if (asteroid_row != -1)
    {
        // If asteroid is above the ship, move up 
        if (asteroid_row < ship_row)
            ship_row--;
        // Otherwise move down 
        else if (asteroid_row > ship_row)
            ship_row++;
  
    // Otherwise move to the next free row if there are no asteroids in the same row
    } else if (free_row != -1) {
        // If the free row is above the ship, move up
        if (free_row < ship_row)
            // Move towards the next free row 
            ship_row--;
        
        // Otherwise, move down
         else if (free_row > ship_row)
            ship_row++;
        
    }
    
    // Create the next ship action based on the new ship row
    struct ship_action next_action = {MOVE_NO, ship_state};
    
    // If the new row is above the current row, move up
    if (ship_row < *(int *)ship_state)
        next_action.move = MOVE_UP;
        
    // If the new row is below the current row, move down
    else if (ship_row > *(int *)ship_state)
        next_action.move = MOVE_DOWN;
    
    // Update the ship state to the new row
    *(int *)ship_state = ship_row;
    
    // And finally return our next action for the next action
    return next_action;
}
