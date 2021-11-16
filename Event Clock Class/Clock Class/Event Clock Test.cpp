#include <cstdio>
#include <ctime>
#include <cstdint> 
#include "Event Clock.h"
using namespace std;

void eventCaller(uint8_t);

int main()
{
	float c0_time = 2.0;		//Total cycle time in seconds

	/*Cycle event multidimensional array that contains the event time
	* Time is in milliseconds
	* and the function number.
	* EVENTS CANT BE BIGGER THAN CYCLE TIME AND MUST BE IN ORDER
	*/
	int c0_ev[3][2] = { { 500, 0}, {1000, 3}, {1500, 2} };
	
	printf("Hello World!\n");
	eventClock clock0(c0_time, &c0_ev[0][0], &c0_ev[2][1], 
		sizeof(c0_ev)/sizeof(c0_ev[0][0]),
		&eventCaller);

	/*Determining where the clock reset will go may have to be figured out for
	* each program using this class. One program I may want to have a clock for
	* each event object, or just run with one for all.
	*/
	clock_t cycle_0 = clock();		//Called before the while loop to get a reference time
	while (clock0.eventCheck(cycle_0));		//Call eventCheck() constantly until it returns false
	printf("\nCycle 1 complete!\n\n");

	/*Block below demonstrates multiple event classes running at once each running
	* only one cycle. while loop does not exit until all cycle classes are done.
	*/
	bool ev1 = true, ev2 = true, ev3 = true;
	float c1_time = 1.0;
	clock_t cycle_1 = clock();
	int c1_ev[2][2] = { { 250, 0}, {900, 0}};
	eventClock clock1(c1_time, &c1_ev[0][0], &c1_ev[1][1], 
		sizeof(c1_ev)/sizeof(c1_ev[0][0]),
		&eventCaller);
	
	float c2_time = 3.0;
	clock_t cycle_2 = clock();
	int c2_ev[4][2] = { { 200, 1}, {400, 1}, {1400, 1} , {2600, 1} };
	eventClock clock2(c2_time, &c2_ev[0][0], &c2_ev[3][1], 
		sizeof(c2_ev) / sizeof(c2_ev[0][0]),
		&eventCaller);

	float c3_time = 0.5;
	clock_t cycle_3 = clock();
	int c3_ev[3][2] = { { 150, 2}, {350, 2}, {450, 2} };
	eventClock clock3(c3_time, &c3_ev[0][0], &c3_ev[2][1], 
		sizeof(c3_ev) / sizeof(c3_ev[0][0]),
		&eventCaller);

	while (ev1 || ev2 || ev3)
	{
		ev1 ? ev1 = clock1.eventCheck(cycle_1) : ev1 = false;
		ev2 ? ev2 = clock2.eventCheck(cycle_2) : ev2 = false;
		ev3 ? ev3 = clock3.eventCheck(cycle_3) : ev3 = false;
	}
	return 0;
}

/*Forcing the programmer to create their own event handler Fx was the
* most flexible way I could implement event catching
*/
void eventCaller(uint8_t evNum)
{
	//a switch case event block for all events
	//printf("Event #: %d\n", evNum);		//Used to troubleshoot class
	switch (evNum)
	{
	case 0: printf("Event 0\n"); break;
	case 1: printf("Event 1\n"); break;
	case 2: printf("Event 2\n"); break;
	case 3:	printf("Event 3\n"); break;
	default: break;
	}
}