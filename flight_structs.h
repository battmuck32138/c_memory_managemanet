/*
 * CS61C Summer 2019
 * Name: 
 * Login: 
 */

#ifndef FLIGHT_STRUCTS_H
#define FLIGHT_STRUCTS_H
#include "timeHM.h"

typedef struct flightSys flightSys_t;
typedef struct airport airport_t;
typedef struct flight flight_t;


// I set these up as linked lists.  
struct flightSys {
  // Place the members you think are necessary for the flightSys struct here.
  struct airport* first_airport;  // pointer to the first airport in the system 
} flightSys;


struct airport {
    // Place the members you think are necessary for the airport struct here.
   char* airport_name;
   struct flight* first_flight;  // this is the schedule
   struct airport* next_airport;
} airport;


struct flight {
    // Place the members you think are necessary for the flight struct here.
  timeHM_t* departure;
  timeHM_t* arrival;
  int* cost;
  struct airport* destination;
  struct flight* next_flight;
} flight;


#endif

