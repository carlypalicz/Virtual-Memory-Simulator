//
// Created by Carly Palicz on 4/20/19.
//Github Username: carlypalicz
//MyStevens Username: cpalicz
// I pledge my honor that I have abided by the Stevens Honor System.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <cstring>
#include "PageTable.h"
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 6) { //wrong number of arguments
        cout << "usage: " << argv[0] << " <filename>\n";
        exit(1);
    }

    int progSize;
    int pageSize = stoi(argv[3]);
    string algType = argv[4];
    string flag = argv[5];
    int NumOfProgs = 0;
    vector<PageTable*> tables;
    ulong counter = 1;

    //read plist to get number of programs
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "Could not open file\n";
        exit(1);
    } else {
        string line1;
        while (getline(file, line1)) { //read file line by line
            int spc1 = line1.find(' '); //read each "word"
            if (spc1 != -1) {
                NumOfProgs++; //gets total number of programs
            }
        }

    }

    //read plist to get pID and progSize
    ifstream the_file(argv[1]);
    if (!the_file.is_open()) {
        cout << "Could not open file\n";
        exit(1);
    } else {
        int pID;
        string line;
        while (getline(the_file, line)) {
            int spc = line.find(' ');
            if (spc != -1) {
                pID = stoi(line.substr(0, spc)); //gets the pID as int
                progSize = stoi(line.substr(spc + 1)); //gets the program size as int
                //creates a page table for each program and stores them in a vector
                tables.push_back(new PageTable(pID, progSize, pageSize, algType, flag, NumOfProgs, counter));

                counter += (512 / pageSize) / NumOfProgs;
                //cout << "counter is " + to_string(counter) + "\n";
            }
        }
    }

    //read ptrace
    ifstream file_2(argv[2]);
    if (!file_2.is_open()) {
        cout << "Could not open file\n";
        exit(1);
    }
    counter++;
    //cout << "counter starting at " + to_string(counter) + "\n";
    int pID;
    int memLoc;
    string line;
    int swpCount = 0;
    int contCount = 0;
    int hand = 0;

    while (getline(file_2, line)) { //read line by line
        int spc = line.find(' ');
        if (spc != -1) {
            pID = stoi(line.substr(0, spc)); //get pID as int
            memLoc = stoi(line.substr(spc + 1)); //get memory location as int

            for (int i = 0; i < tables.size(); i++) { //loop thru page tables
                if (tables[i]->pID == pID) { //the page table u want to look thru
                    //go to the correct page
                    int pgnum = memLoc / pageSize;
                    if (tables[i]->isValid(pgnum) == 0) {
                        //then it is not loaded into memory
                        //cout << "an alg would happen here\n";
                        counter++;
                        if (algType.compare("FIFO") == 0) {
                            if (flag.compare("+") == 0) {
                                //FIFO with pre paging
                                int swp = tables[i]->FindFIFO(counter);
                                swpCount++;
                                tables[i]->swap(pgnum, swp, counter);
                                counter++;

                                swp = tables[i]->FindFIFO(counter);
                                int x = ((pgnum+1)%(tables[i]->pageCount));
                                tables[i]->swap(x, swp, counter);
                                //cout << "pre loading page " + to_string(x) + "\n";
                                //cout << "page count is " +to_string(tables[i]->pageCount) + "\n";
                            } else {
                                //FIFO with demand paging
                                int swp = tables[i]->FindFIFO(counter);
                                swpCount++;
                                //cout << "swpcount is " + to_string(swpCount) << endl;
                                tables[i]->swap(pgnum, swp, counter);
                            }
                        } else if (algType.compare("LRU") == 0) {
                            if (flag.compare("+") == 0) {
                                //LRU with pre paging
                                int swp = tables[i]->FindLRU(counter);
                                swpCount++;
                                tables[i]->swap(pgnum, swp, counter);
                                counter++;

                                swp = tables[i]->FindLRU(counter);
                                int x = ((pgnum+1)%(tables[i]->pageCount));
                                tables[i]->swap(x, swp, counter);

                            } else {
                                //LRU with demand paging
                                int swp = tables[i]->FindLRU(counter);
                                swpCount++;
                                tables[i]->swap(pgnum, swp, counter);

                            }
                        } else {
                            //cout << "swap counter starting at "+ to_string(swpCount) + "\n";

                            if (flag.compare("+") == 0) {
                                //clock with pre paging

                                int mainmemsz = 512 / pageSize / NumOfProgs;

                                int swp = tables[i]->FindClock(counter, hand);

                                // dif stuff
                                tables[i]->notValid(swp); //set valid bit to 0
                                tables[i]->nullify(swp);
                                //

                                hand += swp;
                                hand = (hand % mainmemsz) + 1;
                                counter++;

                                int swp2 = tables[i]->FindClock(counter, hand);
                                hand += swp2;
                                hand = (hand % mainmemsz) + 1;

                                tables[i]->swap(pgnum, swp, counter);
                                int x = ((pgnum+1)%(tables[i]->pageCount));
                                tables[i]->swap(x, swp2, counter);
                                swpCount++;


                            } else {
                                //clock with demand paging
                                int mainmemsz = 512 / pageSize / NumOfProgs;

                                int swp = tables[i]->FindClock(counter, hand);
                                swpCount++;
                                hand += swp;
                                hand = (hand % mainmemsz) + 1;
                                tables[i]->swap(pgnum, swp, counter);
                            }
                        }

                    } else {
                        contCount++;
                        tables[i]->pagetable[pgnum]->accTime = counter;
                        counter++;
                        tables[i]->pagetable[pgnum]->TakeAChanceOnMeByABBA = true;
                        //cout << "already in memory" + to_string(counter) + "\n";

                    }
                }
            }
        }

    }
//file closed

    cout << "swaps made: " + to_string(swpCount) + "\n";
    cout << "already in mem: " + to_string(contCount) + "\n";
    return 0;

}