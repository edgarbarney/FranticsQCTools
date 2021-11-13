// 2021 FranticDreamer

#include "base.hpp"
#include "fileprocessor.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std; // I don't use this often but its convenient to use for this app.

FileProcessor fProcessor;

int main(int argc, char* argv[])
{
    //First argument is filename
    for (int i = 1; i < argc; i++)
    {
        //Add file path arguments to the list
        fProcessor.AddPaths(argv[i]); 
    }

    //If no file found, screw this app.
    if (fProcessor.GetFilePathsSize() < 1) 
    {
        std::cout << "No file found. Exiting." << std::endl;
        system("pause");
        return 0;
    }

    //Show file list. Start from 1 because everyone isn't a programmer.
    for (size_t  i = 0; i < fProcessor.GetFilePathsSize(); i++)
    {
        std::cout << "File " << i+1 << ": " << (fProcessor.GetPathFromFilePaths(i)) << std::endl;
    }

    std::cout << "This process is -kinda- irreversible. Are you sure you want to proceed? (Y/N)" << std::endl;

    int userAnswer = 2; // I dun get it for default

    //Make sure user wants this.
    do
    {
        userAnswer = FranUtils::checkForAnswer();
    } 
    while (userAnswer == 2);

    if (userAnswer == 0)
    {
        system("pause");
        return 0;
    }
    else if (userAnswer == 1) //No need for another if but, you never know.
    {
        float scalebuffer = 0;
        std::cout << "Please enter a scale MULTIPLIER (not scale itself):" << std::endl;
        cin >> scalebuffer;
        while (!scalebuffer || scalebuffer == 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            std::cout << "Please enter a VALID float or integer" << std::endl;
            cin >> scalebuffer;
        } 
        cout << flush << "Starting conversion process..." << std::endl;

        //for (size_t i = 0; i < fProcessor.GetFilePathsSize(); i++)
        //{
            //fProcessor.AddQCFiles(fProcessor.FillQCFile(fProcessor.GetPathFromFilePaths(i)));
        //}

        for (string str : fProcessor.filePaths)
        {
            fProcessor.ProcessQCFile(str, scalebuffer);

            cout << "File Porcessing Completed: " << std::endl;
        }
        
        cout << "Files are done." << std::endl;
        system("pause");
    }

}

