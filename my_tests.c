#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flights.h"
#include <stdbool.h>
#include "flight_structs.h"
#include "flights.c"
#include "timeHM.h"
#include "timeHM.c"

int main() {
    printf("\n");
    printf("RUNNING: my_tests.c \n \n");
    
    // tests
    printf("What airports are in the system? \n");
    flightSys_t* system = createSystem();
    addAirport(system, "SFO");
    addAirport(system, "SEA");
    addAirport(system, "DTW");
    addAirport(system, "LAX");
    airport_t* SEA = getAirport(system, "SEA");
    airport_t* SFO = getAirport(system, "SFO");
    airport_t* DTW = getAirport(system, "DTW");
    airport_t* LAX = getAirport(system, "LAX");
    printAirports(system);
    printf("\n");
    flight_t* f1 = createFlight(SFO, &(timeHM_t) {.hours = 12, .minutes = 0 }, &(timeHM_t) {.hours = 13, .minutes = 0 }, 200);
    flight_t* f2 = createFlight(SEA, &(timeHM_t) {.hours = 13, .minutes = 0 }, &(timeHM_t) {.hours = 14, .minutes = 0 }, 300);
    addFlight(SFO, SEA, &(timeHM_t) {.hours = 12, .minutes = 0 }, &(timeHM_t) {.hours = 13, .minutes = 0 }, 200);
    addFlight(SFO, DTW, &(timeHM_t) {.hours = 5, .minutes = 1}, &(timeHM_t) {.hours = 6, .minutes = 0 }, 300);
    addFlight(SFO, DTW, &(timeHM_t) {.hours = 3, .minutes = 0 }, &(timeHM_t) {.hours = 5, .minutes = 0 }, 900);
    addFlight(DTW, SFO, &(timeHM_t) {.hours = 7, .minutes = 0 }, &(timeHM_t) {.hours = 9, .minutes = 0 }, 1300);
    addFlight(SFO, SEA, &(timeHM_t) {.hours = 12, .minutes = 0 }, &(timeHM_t) {.hours = 13, .minutes = 0 }, 200);
    addFlight(SFO, LAX, &(timeHM_t) {.hours = 13, .minutes = 0 }, &(timeHM_t) {.hours = 14, .minutes = 0 }, 300);
    addFlight(SFO, DTW, &(timeHM_t) {.hours = 5, .minutes = 30 }, &(timeHM_t) {.hours = 6, .minutes = 0 }, 900);
    addFlight(SFO, DTW, &(timeHM_t) {.hours = 5, .minutes = 43}, &(timeHM_t) {.hours = 6, .minutes = 0 }, 1300);
    printSchedule(SFO);
    printf("\n");
    printSchedule(DTW);
    printf("\n");
    timeHM_t* depart = (timeHM_t*) malloc(sizeof(timeHM_t));
    timeHM_t* arrive = (timeHM_t*) malloc(sizeof(timeHM_t));
    int* cost = (int*) malloc(sizeof(timeHM_t));
    if (depart == NULL || arrive == NULL || cost == NULL) {
        allocation_failed();
    }
    printf("OUTPUT for getNextFlight: ");
    int result = getNextFlight(SFO, DTW, &(timeHM_t) {.hours = 5, .minutes = 0 }, depart, arrive, cost);
    printf("%i ", result);
    printf("\n");
    printTime(depart); 
    printf(", ");
    printTime(arrive);
    printf(", ");
    printf("%i \n", *cost);
    


    









    printf("\n");
    printf("DeleteALLFlights: SFO \n");
    deleteFlights(SFO);
    printf("\n Printing schedule: ");
    printSchedule(SFO);
    deleteFlight(f1);
    deleteFlight(f2);
    deleteSystem(system);


    return 0;
}




    


