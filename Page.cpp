//
// Created by Carly Palicz on 4/27/19.
//Github Username: carlypalicz
//MyStevens Username: cpalicz
// I pledge my honor that I have abided by the Stevens Honor System.
//

#include "Page.h"
#include <iostream>
using namespace std;

Page::Page(int pageNum1, int valid1, int accTime1, int pID1, int pageSize1, int addTime1, bool chnce){
    pageNum = pageNum1;
    valid = valid1;
    accTime = accTime1;
    pID = pID1;
    pageSize = pageSize1;
    addTime = addTime1;
    TakeAChanceOnMeByABBA = chnce;


//    cout << "pageNum: " + to_string(pageNum);
//    cout << " valid: " + to_string(valid);
//    cout << " accTime: " + to_string(accTime);
//    cout << " pID: " + to_string(pID);
//    cout << " pageSize: " + to_string(pageSize);
//    cout << " addTime: " + to_string(addTime) + "\n";


}
