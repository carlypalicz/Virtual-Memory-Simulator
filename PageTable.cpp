//
// Created by Carly Palicz on 4/27/19.
//Github Username: carlypalicz
//MyStevens Username: cpalicz
// I pledge my honor that I have abided by the Stevens Honor System.
//

#include "PageTable.h"
#include "Page.h"
#include <vector>
#include <iostream>

using namespace std;

PageTable::PageTable(int pID1, int progSize1, int pageSize1, string algType1, string flag1, int NumOfProgs1,
                     int counter1) {
    pID = pID1;
    progSize = progSize1;
    pageSize = pageSize1;
    algType = algType1;
    flag = flag1;
    NumOfProgs = NumOfProgs1;
    counter = counter1;
    pageCount = progSize / pageSize;

    for (int i = 0; i <= (pageCount); i++) {
        pagetable.push_back(new Page(i, 0, 0, pID, pageSize, 0, false));
        //cout << "page added from pID " + to_string(pID) +  "\n";
    }

    MainMem(counter);
}

int PageTable::isValid(int pgnum) {
    return pagetable[pgnum]->valid;
}

void PageTable::notValid(int pgnum) { //for clock, set valid bit in mainmem to 0 before removing
    mainmem[pgnum]->valid = 0;
}

void PageTable::nullify(int pgnum){
    mainmem[pgnum] = NULL;
}

void PageTable::MainMem(int counter) {
    int split = (512 / pageSize) / NumOfProgs; // how many pages each prog gets
    for (int i = 0; i < split; i++) {
        //load pages from the pagetable into main mem
        if (i < pagetable.size()) {
            mainmem.push_back(pagetable[i]); //add page to mainmem
            counter++;
            pagetable[i]->valid = 1; //update page on pagetable to show its in mainmem
            pagetable[i]->accTime = counter; // update time bc it was just accessed
            pagetable[i]->addTime = counter; //update time bc it was just added
            //cout << "page added " + to_string(counter) + "\n";
        }
        //else{
        //   mainmem.push_back(NULL); //add a "blank" page
        //cout << "blank page added\n";
        //   counter++;
        // }
    }
    //cout << "actual counter is " + to_string(counter) + "\n";
}

int PageTable::FindFIFO(int c) {
    int temp = c;
    //cout << "counter in findFIFO is " + to_string(c)+ "\n";
    int first;
    //find oldest page in mainmem
    for (int i = 0; i < mainmem.size(); i++) {
        if (mainmem[i]->pID == pID) {
            if (mainmem[i]->addTime < temp) {
                temp = mainmem[i]->addTime;
                first = i;
            }
        }
    }
    return first; //returns the index of the oldest page in mainmem
}

int PageTable::FindLRU(int c) {
    int temp = c;
    int first;
    //find page used longest ago in mainmem
    for (int i = 0; i < mainmem.size(); i++) {
        if (mainmem[i]->pID == pID) {
            if (mainmem[i]->accTime < temp) {
                temp = mainmem[i]->accTime;
                first = i;
            }
        }
    }
    return first; //returns the index of page used longest ago in mainmem
}


int PageTable::FindClock(int c, int hand) {
    int index;
    while (1) {
        if (mainmem[hand] != NULL){
            if (mainmem[hand]->TakeAChanceOnMeByABBA) {
                mainmem[hand]->TakeAChanceOnMeByABBA = false;
                hand += 1;
                hand = hand % (mainmem.size());
                //cout << "hand iss " + to_string(hand) + "\n";
                //cout << "mainmem length is" + to_string(mainmem.size()) + "\n";
            } else {
                return hand;
            }
        }
        cout << "reached a NULL boi\n";
        hand += 1;
        hand = hand % (mainmem.size());
    }
}

void PageTable::swap(int pgnum, int swp, int count) {
    if (mainmem[swp] != NULL) {
        int oldPN = mainmem[swp]->pageNum; //old page number to update page table
        pagetable[oldPN]->valid = 0; //its not in mainmem anymore
    }
    mainmem[swp] = pagetable[pgnum]; //switches the pages in mainmem
    pagetable[pgnum]->addTime = count; //added to mainmem
    pagetable[pgnum]->accTime = count; //added to mainmem
    pagetable[pgnum]->valid = 1; //added to mainmem
    mainmem[swp]->TakeAChanceOnMeByABBA = false;

    //cout << "valid 1: " + to_string(pagetable[pgnum]->valid) + "\n";
    //cout << "valid 0: " + to_string(pagetable[swp]->valid) + "\n";
    //cout << "count is " + to_string(count) + "\n";
}


