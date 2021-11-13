#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace FranUtils 
{
    //Basic ask for an answer
    inline int checkForAnswer()
    {
        using namespace std;
        string buffer;
        cin >> buffer;
        if (buffer == "Y" || buffer == "y")
        {
            return 1;
        }
        else if (buffer == "N" || buffer == "n")
        {
            cout << "OK. Waiting for you when you've made your mind." << endl;
            return 0;
        }
        else
        {
            cout << "I dun get it." << endl;
            return 2;
        }
    }
}