//
// Created by Carly Palicz on 4/27/19.
//Github Username: carlypalicz
//MyStevens Username: cpalicz
// I pledge my honor that I have abided by the Stevens Honor System.
//

#ifndef VIRTUAL_MEMORY_SIMULATOR_TEAM_21_PAGETABLE_H
#define VIRTUAL_MEMORY_SIMULATOR_TEAM_21_PAGETABLE_H

#include <string>
#include "Page.h"
#include <vector>
using namespace std;

class PageTable {
private:

public:
    PageTable(int pID, int progSize, int pageSize, string algType, string flag, int NumOfProgs1, int counter1);
    void MainMem(int counter);
    int isValid(int pgnum);
    void notValid(int pgnum);
    void nullify(int pgnum);
    bool isChanceWorthy(int pgnum);
    int FindFIFO(int c);
    int FindLRU(int c);
    int FindClock(int c, int hand);
    void swap(int pgnum, int swp, int count);
//    int LRUpre();
//    int LRUdemand();
//    int ClockPre();
//    int ClockDemand();
    int pID;
    int progSize;
    int pageSize;
    int NumOfProgs;
    string algType;
    string flag;
    int accTime;
    int addTime;
    vector<Page*> pagetable;
    vector<Page*> mainmem;
    ulong counter;
    int pageCount;

};



#endif //VIRTUAL_MEMORY_SIMULATOR_TEAM_21_PAGETABLE_H
