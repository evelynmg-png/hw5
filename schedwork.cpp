#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_help (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day, 
    size_t slots
);

bool schedule_worker(
    Worker_T worker,
    const DailySchedule& sched,
    size_t maxShift, 
    size_t currDay
);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t n = avail.size();
    sched.resize(n);

    return schedule_help(avail, dailyNeed, maxShifts, sched, 0, 0);

}

bool schedule_help (
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day, 
    size_t slots
)
{

  // number of workers 
  // and number of employess 
  size_t n = avail.size();
  size_t k = avail[0].size(); 


  if (day == n){
    return true;
  }

  // if the day is full, do a recurisve  call
  if (slots == dailyNeed){
    return schedule_help(avail, dailyNeed, maxShifts, sched, day +1, 0);
  }

  //  going through every worker to see which  will work
  for (Worker_T worker = 0; worker < k; worker++){
    // chekc to see if the worker is aviable, hsa reached the max amount of maxShifts
    // also will check if they were alreayd schedlued for the day we are searchign for
    if (avail[day][worker] && schedule_worker(worker, sched, maxShifts, day) && find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()){
      
      sched[day].push_back(worker);

      // rescurive call
      if(schedule_help(avail, dailyNeed, maxShifts, sched, day, slots +1)){
        return true;
      }

      sched[day].pop_back();
    }

  }

  return false;
}


bool schedule_worker(
    Worker_T worker,
    const DailySchedule& sched,
    size_t maxShift, 
    size_t currDay
)
{
  size_t count =0;

  //checks to see how mnay shift they have
  for (size_t day =0; day < currDay; day++){
    if (find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()){
      count++;
    }
  }

  return count < maxShift;
}

