#include <cstdio>
#include <ctime>
#include <cstdint>
#include "Event Clock.h"
using namespace std;


eventClock::eventClock(float _cycle, int* _eventTime, const int* _lastEvent,
	int _eventNum, void (*ev_fx)(uint8_t)) :
	cycle(_cycle), p_eventTime(_eventTime), p_firstEvent(_eventTime), 
	p_lastEvent(_lastEvent), p_eventHandler(ev_fx)
{
	//printf("Cycle = %f seconds\n", _cycle);		//Used to troubleshoot class
}

bool eventClock::eventCheck(clock_t s_time)
{
	//If the clock exceds cycle limit, return pointer to first element
	if (difftime(clock(), s_time) > CLOCKS_PER_SEC * cycle)
	{
		p_eventTime = p_firstEvent;		//Return array pointer to first element
		//printf("pointer returned to: %.3f\n", float(*p_eventTime)/1000);		//Used to troubleshoot class
		return false;
	}
	/*If the clock reaches or passes the event time, take event code and pass to event
	* caller Fx
	*/
	else if (difftime(clock(), s_time) >= CLOCKS_PER_SEC * float(*p_eventTime)/1000 && p_eventTime <= p_lastEvent)
	{
		//printf("Event at: %.3f sec\n", float(*p_eventTime)/1000);		//Used to troubleshoot class
		p_eventHandler(*(p_eventTime+1));
		++++p_eventTime;
	}
	return true;		//If the cycle limit isn't exceeded, return true
}