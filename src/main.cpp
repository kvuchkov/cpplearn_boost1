#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include "CalcPI.h"
#include "CalcConstSlow.h"

using namespace std;

void * calc(void *data)
{
    CalcNode *node = reinterpret_cast<CalcNode*>(data);
    (*node)();
    // cout << " [" << result << "]" << endl;
    return NULL;
}

int main()
{   
    vector<CalcNode*> calcs;
    
    calcs.push_back(new CalcPI());
    calcs.push_back(new CalcConstSlow());
    calcs.push_back(new CalcPI());
    calcs.push_back(new CalcConstSlow());
    
    vector<boost::thread*> threads;
    int n = 1;
    BOOST_FOREACH(CalcNode* c, calcs)
    {
        threads.push_back(new boost::thread(boost::ref(*c)));
        cout << "Thread #" << n++ << " started." << endl; 
    }
    
    BOOST_FOREACH(boost::thread* t, threads)
    {
        t->join();
    }
    
    double result=1;
    BOOST_FOREACH(CalcNode* c, calcs)
    {
        result *= c->result();
    }
    cout << result << endl;

	return 0;
}
