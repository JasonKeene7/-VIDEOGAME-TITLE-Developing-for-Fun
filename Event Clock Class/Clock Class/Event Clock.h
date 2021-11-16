#include <ctime>
#include <cstdint>

#ifndef EVENTCLOCK_H
#define EVENTCLOCK_H

class eventClock
{
	float cycle = 0;					//Cycles in seconds
	int *p_eventTime;					//Pointer to multidimensional array. Event trigger in seconds
	int* p_firstEvent;					//Pointer to first event so p_eventTime always has a starting reference
	const int* p_lastEvent;				//Pointer to last item in event array
	void (*p_eventHandler)(uint8_t);	//Pointer to custom event handler Fx
	
public:
	//Sets up class members
	eventClock(float, int*, const int*, int, void (*)(uint8_t));
	
	/*Checks if cycle time has passed an event trigger or has reached the
	* cycle limit. Returns true if end of cycle wasnt reached yet and false
	* if it was
	*/
	bool eventCheck(clock_t);
};

#endif