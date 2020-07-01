/*
 * CS61C Summer 2019
 * Name:
 * Login:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "flight_structs.h"
#include "timeHM.h"


/*
 *  This should be called if memory allocation failed.
 */
static void allocation_failed(void) {
   fprintf(stderr, "Out of memory.\n");
   exit(EXIT_FAILURE);
}


/*
 *  Creates and initializes a flight system, which stores the flight schedules of several airports.
 *  Returns a pointer to the system created.
 *  
 *  I set this up as a linked list of airports. 
 * 
 */
flightSys_t* createSystem(void) {
   // Replace this line with your code

   // initialize system 
   flightSys_t* system = (flightSys_t*) malloc(sizeof(flightSys_t));
   if (system == NULL) {
      allocation_failed();
   }

   // allocate memory for its members 
   system->first_airport = (airport_t*) malloc(sizeof(airport_t));
   if (system->first_airport == NULL) {
      allocation_failed();
   }
   system->first_airport->airport_name = NULL;
   system->first_airport->first_flight = NULL;
   system->first_airport->next_airport = NULL;

   return system;
}


/*
 *  Adds an airport with the given name to the system. You must copy the string and store it.
 *  Do not store `name` (the pointer) as the contents it point to may change.
 *
 */
void addAirport(flightSys_t* system, char* name) {
   // Replace this line with your code

   // check for null inputs 
   if ((system == NULL) || (name == NULL)) {
      return;
   }

   // no need to add airport if it already exists 
   airport_t* airport_exists = getAirport(system, name); 
   if (airport_exists) {
      return;
   }

   // get a ptr to the memory allocated for the next airport in the system linked list 
   airport_t* new_airport = system->first_airport;
   while (new_airport->next_airport) {
      new_airport = new_airport->next_airport;
   }

   // initialize airport name 
   int str_size = strlen(name) + 1;
   new_airport->airport_name = (char*) malloc(str_size * sizeof(char));
   if (new_airport->airport_name == NULL) {
      allocation_failed();
   }
   strcpy(new_airport->airport_name, name);  // must COPY string 

   // allocate memory for first_flight in the flights linked list
   new_airport->first_flight = (flight_t*) malloc(sizeof(flight_t));
   if (new_airport->first_flight == NULL) {
      allocation_failed();
   }
   new_airport->first_flight->departure = NULL;
   new_airport->first_flight->arrival = NULL;
   new_airport->first_flight->cost = NULL;
   new_airport->first_flight->destination = NULL;
   new_airport->first_flight->next_flight = NULL;

   // allocate memory for next airport in the system linked list 
   new_airport->next_airport = (airport_t*) malloc(sizeof(airport_t));
   if (new_airport->next_airport == NULL) {
      allocation_failed();
   }
   new_airport->next_airport->airport_name = NULL;
   new_airport->next_airport->first_flight = NULL;
   new_airport->next_airport->next_airport = NULL;
}


/*
 *  Returns a pointer to the airport with the given name.
 *  If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* system, char* name) {
   // Replace this line with your code

   if ((system == NULL) || (name == NULL)) {
      return NULL;
   }

   airport_t* current_airport = system->first_airport;
   while(current_airport->next_airport) {
      int diff = strcmp(current_airport->airport_name, name);
      if (diff == 0) {
         return current_airport;
      }
      current_airport = current_airport->next_airport;
   }
    return NULL;
}


/*
 *  Print each airport name in the order they were added through addAirport, one on each line.
 *  Make sure to end with a new line. You should compare your output with the correct output
 *  in `flights.out` to make sure your formatting is correct.
 */
void printAirports(flightSys_t* system) {
   // Replace this line with your code
   
   if (system == NULL || system->first_airport == NULL) {
      return;
   }

   airport_t* airport = system->first_airport;
   while (airport->next_airport) {
      printf("%s \n", airport->airport_name);
      airport = airport->next_airport;
   }
}


/*
 *   Given a destination airport, departure and arrival times, and a cost, return a pointer to new flight_t.
 *
 *   Note that this pointer must be available to use even after this function returns.
 *   (What does this mean in terms of how this pointer should be instantiated?)
 *   Additionally you CANNOT assume that the `departure` and `arrival` pointers will persist after this function completes.
 *   (What does this mean about copying dep and arr?)
 */
flight_t* createFlight(airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
// Replace this line with your code

  // isAfter() returns arg1 > arg2
  if ((destination == NULL) || (departure == NULL) || (arrival == NULL)) {
    return NULL;
  }
  if (isAfter(departure, arrival) || (cost < 0)) {
    return NULL;
  }

   // initialize a temporty flight 
   flight_t* tmp_flight = (flight_t*) malloc(sizeof(flight_t));
   if (tmp_flight == NULL) {
      allocation_failed();
   }

   // create space for destination and store destination
    tmp_flight->destination = (airport_t*) malloc(sizeof(airport_t));
    if ((tmp_flight->destination) == NULL) {
        allocation_failed();
    }
    *(tmp_flight->destination) = *destination;
    
    // create space for departure and store departure
    tmp_flight->departure = (timeHM_t*) malloc(sizeof(timeHM_t));
    if ((tmp_flight->departure) == NULL) {
        allocation_failed();
    }
    *(tmp_flight->departure) = *departure;

    // create space for arrival and store arrival
    tmp_flight->arrival = (timeHM_t*) malloc(sizeof(timeHM_t));
    if ((tmp_flight->arrival) == NULL) {
        allocation_failed();
    }
    *(tmp_flight->arrival) = *arrival;
    
    // create space for cost and store cost
    tmp_flight->cost = (int*) malloc(sizeof(int));
    if ((tmp_flight->cost) == NULL) {
        allocation_failed();
    }
    *(tmp_flight->cost) = cost;

    // no memory allocated for the nest flight
    tmp_flight->next_flight = NULL;

   return tmp_flight;
}


/*
 *  Frees all memory allocated for a single flight. You may or may not decide
 *  to use this in delete system but you must implement it.
 */
void deleteFlight(flight_t* flight) {
   // Replace this line with your code
   if (flight == NULL) {
      return;
   }

   free(flight->departure);
   flight->departure = NULL;
   free(flight->arrival);
   flight->arrival = NULL;
   free(flight->cost);
   flight->cost = NULL;
   free(flight->destination);
   flight->destination = NULL;
   free(flight->next_flight);
   flight->next_flight = NULL;
   free(flight);
   flight = NULL;
}


/*
 *  Adds a flight to source's schedule, stating a flight will leave to destination at departure time and arrive at arrival time.
 *  This function works for airport outside of the system as well as inside of the system.  
 */
void addFlight(airport_t* source, airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
   // Replace this line with your code

   // check for bad inputs 
   if ((source == NULL) || (destination == NULL) || (cost < 0) || (departure == NULL) || (arrival == NULL)) {
    return;
   }

   // check for bad inputs
   if (isAfter(departure, arrival) || (cost < 0)) {
      return;
   }

   flight_t* new_flight = source->first_flight;
   while (new_flight->next_flight) {
      new_flight = new_flight->next_flight;
   }

   // create space for departure and store departure
    new_flight->departure = (timeHM_t*) malloc(sizeof(timeHM_t));
    if (new_flight->departure == NULL) {
        allocation_failed();
    }
    *(new_flight->departure) = *departure;

    // create space for arrival and store arrival
    new_flight->arrival = (timeHM_t*) malloc(sizeof(timeHM_t));
    if (new_flight->arrival == NULL) {
        allocation_failed();
    }
    *(new_flight->arrival) = *arrival;

    // create space for cost and store cost
    new_flight->cost = (int*) malloc(sizeof(int));
    if (new_flight->cost == NULL) {
        allocation_failed();
    }
    *(new_flight->cost) = cost;

   // create space for destination and store destination
   new_flight->destination = (airport_t*) malloc(sizeof(airport_t));
   if (new_flight->destination == NULL) {
      allocation_failed();
   }
   *(new_flight->destination) = *destination;
    
    // set up for the next flight
   new_flight->next_flight = (flight_t*) malloc(sizeof(flight_t));
   if (new_flight->next_flight == NULL) {
      allocation_failed();
   }
   new_flight->next_flight->departure = NULL;
   new_flight->next_flight->arrival = NULL;
   new_flight->next_flight->cost= NULL;
   new_flight->next_flight->destination = NULL;
   new_flight->next_flight->next_flight = NULL;
}


/*
 *  Prints the schedule of flights of the given airport.
 *
 *  Prints the airport name on the first line, then prints a schedule entry on each
 *  line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".
 *
 *  You should use `printTime()` (look in `timeHM.h`) to print times, and the order should be the same as
 *  the order they were added in through addFlight. Make sure to end with a new line.
 *  You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
void printSchedule(airport_t* airport) {
   // Replace this line with your code

   if (airport == NULL || airport->first_flight == NULL) {
    return;
   }
   printf("%s\n", airport->airport_name);

   // ptr to first_flight in schedule 
   flight_t* flight = airport->first_flight;
    while (flight->next_flight) {

      if (flight->destination->airport_name) {
        printf("%s ", flight->destination->airport_name);
      }

      if (flight->departure) {
        printTime(flight->departure);
      }

      if (flight->arrival) {
        printf("%s", " ");
        printTime(flight->arrival);
      }

      if (flight->cost) {
        printf(" $%d\n", *(flight->cost));
      }

      flight = flight->next_flight;
    }
}


/*
   Frees all memory assosiated with airport flights. 
 */
void deleteFlights(airport_t* airport) {
   if ((airport == NULL) || (airport->first_flight == NULL)) {
      return;
   }

    flight_t* flight = airport->first_flight;
    flight_t* tmp = NULL;

    while(flight->next_flight) {
        tmp = flight;
        free(tmp->destination);
        tmp->destination = NULL;
        free(tmp->cost);
        tmp->cost = NULL;
        free(tmp->departure);
        tmp->departure = NULL;
        free(tmp->arrival);
        tmp->arrival = NULL;
        flight = flight->next_flight;
        free(tmp);
        tmp = NULL;
    }

    if (flight) {
      free(flight->destination);
      flight->destination = NULL;
      free(flight->departure);
      flight->departure = NULL;
      free(flight->arrival);
      flight->arrival = NULL;
      free(flight->cost);
      flight->cost = NULL;
      free(flight);
      flight = NULL;
    }
    airport->first_flight = NULL;
}


/*
 *  Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* system) {
   //flightSys_t* system = s;
    if (system == NULL) {
        return;
    }

    if (system->first_airport) {
      airport_t* airport = system->first_airport;
      airport_t* tmp = NULL;

      while(airport) {
         free(airport->airport_name);
         airport->airport_name = NULL;
         deleteFlights(airport);
         tmp = airport;
         airport = airport->next_airport;
         free(tmp);
         tmp = NULL;
      }
   }

    free(system);
    system = NULL;
}


/*
 *   Given a source and destination airport, and the time now, finds the next flight to take based on the following rules:
 *   1) Finds the earliest arriving flight from source to destination that departs after now.
 *   2) If there are multiple earliest flights, take the one that costs the least.
 *
 *   If a flight is found, you should store the flight's departure time, arrival time, and cost in the `departure`, `arrival`,
 *   and `cost` params and return true. Otherwise, return false.
 *
 *   Please use the functions `isAfter()` and `isEqual()` from `timeHM.h` when comparing two timeHM_t objects and compare
 *   the airport names to compare airports, not the pointers.
 */
bool getNextFlight(airport_t* source, airport_t* destination, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival, int* cost) {
   // Replace this line with your code

   if ((source == NULL) || (destination == NULL) || (now == NULL) || (departure == NULL) || (arrival == NULL) || (cost == NULL)) {
    return 0;
   }

   int size = 0;
   int i = 0;
   int diff = 0;
   int num_valid_flights = 0;
   stringToTime("24:23", arrival);  // store the latest time possible to arrival (no overnight flights allowed)
   int min_cost = 2147483647;  // max int value in C 

   // get number of flights from source airport 
   flight_t* flight = source->first_flight;
   while (flight->next_flight) {
      flight = flight->next_flight;
      size += 1;
   }

   // load flights into an array for easy handling 
   flight_t* source_arr[size];
   flight = source->first_flight;
   while (flight->next_flight) {
      source_arr[i] = flight;
      flight = flight->next_flight;
      i += 1;
   }

   // find the best flight 
   for (i=0; i < size; i++) {
      flight = source_arr[i];

      // filter out flights with the wrong destination 
      diff = strcmp(destination->airport_name, flight->destination->airport_name);
      if (diff != 0) {
         source_arr[i] = NULL;
      }

      // filter out flights that left prior to now
      if (isAfter(now, flight->departure)) {
         source_arr[i] = NULL;
      }
   }

   // find flights with min arrival times
   for (i=0; i < size; i++) {
      if (source_arr[i]) {
         flight = source_arr[i];
         if (isAfter(arrival, flight->arrival) || isEqual(arrival, flight->arrival)) {
            memcpy(departure, flight->departure, sizeof(timeHM_t));
            memcpy(arrival, flight->arrival, sizeof(timeHM_t));
            memcpy(cost, flight->cost, sizeof(int));
            num_valid_flights += 1;
         } 
         else {
            source_arr[i] = NULL;
         }
      }
   }

   // case of a tie, find min cost flight 
   if (num_valid_flights) {
      for (i = 0; i < size; i++) {
         if (source_arr[i]) {
            flight = source_arr[i];
            if (*(flight->cost) < min_cost) {
               min_cost = *flight->cost; 
               memcpy(departure, flight->departure, sizeof(timeHM_t));
               memcpy(arrival, flight->arrival, sizeof(timeHM_t));
               memcpy(cost, flight->cost, sizeof(int));
            }
            
         }
      }
      return true;

   } 
   return false;
}



/*
 *  Given a list of flight_t pointers (`flight_list`) and a list of destination airport names (`airport_name_list`),
 *  first confirm that it is indeed possible to take these sequences of flights, (i.e. be sure that the i+1th flight departs
 *  after or at the same time as the ith flight arrives) (HINT: use the `isAfter()` and `isEqual()` functions).
 *  Then confirm that the list of destination airport names match the actual destination airport names of the provided flight_t structs.
 *
 *  `size` tells you the number of flights and destination airport names to consider. Be sure to extensively test for errors.
 *  As one example, if you encounter NULL's for any values that you might expect to be non-NULL return -1, but test for other possible errors too.
 *
 *  Return from this function the total cost of taking these sequence of flights.
 *  If it is impossible to take these sequence of flights,
 *  if the list of destination airport names doesn't match the actual destination airport names provided in the flight_t struct's,
 *  or if you run into any errors mentioned previously or any other errors, return -1.
 */
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int size) {
   if (flight_list == NULL || airport_name_list == NULL || size < 1 || *flight_list == NULL || *airport_name_list == NULL) {
    return -1;
  }

  int tot_cost = 0; 
  int diff = 0;
  int i = 0;
  timeHM_t* arrive = NULL;
  timeHM_t* depart = NULL;

   /*
  //see whats going on
  for (i= 0; i < size; i++) {
      printf("\n %s ", flight_list[i]->destination->airport_name);
      printf("  ");
      printTime(flight_list[i]->departure);
      printf("  ");
      printTime(flight_list[i]->arrival);
      printf("  ");
      printf(" %i ", *(flight_list[i]->cost));
      printf("%s  ", airport_name_list[i]);
   }
   */

  if (flight_list[0]) {
      arrive = flight_list[0]->arrival;  // first flights arrival time 
      tot_cost = *(flight_list[0]->cost);
  }

  // check for bad inputs 
  for (i= 1; i < size; i++) {
      if (flight_list[i] == NULL || airport_name_list[i] == NULL) {
      return -1;
      }  
      
      depart = flight_list[i]->departure;
      if (isAfter(arrive, depart)) {
         return -1;
      }
      arrive = flight_list[i]->arrival;
      tot_cost += *(flight_list[i]->cost);
   }

   // check for matching names 
  for (i = 0; i < size; i++) {
      diff = strcmp(flight_list[i]->destination->airport_name, airport_name_list[i]);
       if (diff != 0) {
         return -1;
      }
   }

  //printf("%i \n", tot_cost);
  return tot_cost;
}


