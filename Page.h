//
// Created by Carly Palicz on 4/27/19.
//Github Username: carlypalicz
//MyStevens Username: cpalicz
// I pledge my honor that I have abided by the Stevens Honor System.
//

#ifndef VIRTUAL_MEMORY_SIMULATOR_TEAM_21_PAGE_H
#define VIRTUAL_MEMORY_SIMULATOR_TEAM_21_PAGE_H


class Page {
private:

public:

    Page(int pageNum1, int valid1, int accTime1, int pID1, int pageSize1, int addTime1, bool TakeAChanceOnMeByABBA);
    int pageNum;
    int valid;
    int accTime;
    int pID;
    int pageSize;
    int addTime;
    bool TakeAChanceOnMeByABBA;
};


#endif //VIRTUAL_MEMORY_SIMULATOR_TEAM_21_PAGE_H
