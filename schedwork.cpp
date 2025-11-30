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
bool scheduleHelper(
    size_t day,
    size_t slot,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsUsed
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
    const size_t n = avail.size();
    const size_t k = avail[0].size();
   for(size_t i = 0; i < n; i++) {
        std::vector<Worker_T> row(dailyNeed, INVALID_ID);
        sched.push_back(row);
    }
   
     std::vector<size_t> shiftsUsed(k, 0);
    return scheduleHelper(0, 0, avail, dailyNeed, maxShifts, sched, shiftsUsed);

    

}
bool scheduleHelper(
    size_t day,
    size_t slot,
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsUsed
)
{
    const size_t n = avail.size();
    const size_t k = avail[0].size();
    if(day == n){
        return true;
    }

    if(slot == dailyNeed){
        return scheduleHelper(day + 1, 0, avail, dailyNeed, maxShifts, sched, shiftsUsed);
    }

    for(size_t w = 0; w < k; ++w){
    
        if(!avail[day][w]){
            continue;
        }
        if(shiftsUsed[w] >= maxShifts){
            continue;
        }
        if(std::find(sched[day].begin(),
                     sched[day].begin() + slot,
                     (Worker_T)w) != sched[day].begin() + slot){
            continue;
        }
        sched[day][slot] = (Worker_T)w;
        shiftsUsed[w]++;
        if(scheduleHelper(day, slot + 1, avail, dailyNeed, maxShifts, sched, shiftsUsed)){
            return true;
        }
        shiftsUsed[w]--;
        sched[day][slot] = INVALID_ID;
    }

    
    return false;
}

