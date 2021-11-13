#include "fileprocessor.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std; // I don't use this often but its convenient to use for this app.

void FileProcessor::AddPaths(string str)
{
    filePaths.push_back(str);
}

void FileProcessor::ProcessQCFile(std::string fileName, float scaleMult)
{
    fstream fsMainStream;
    fstream fsWriteStream;

    fsMainStream.open(fileName, ios::in);
    fsWriteStream.open(fileName + "_scaled", ios::out);
    if (fsMainStream.is_open() && fsWriteStream.is_open())
    {
        string buffer;
        // Read line, put in into buffer.
        while (getline(fsMainStream, buffer)) 
        {
            //Lets iterate through our parameters, shall we?
            //Comments are kinda supported
            if (buffer.find("$hbox") != string::npos)
            {
                float maxesAndMins[6];          //Maximum and Mininmum XYZ values
                int hboxType = 0;               //Hitbox type. Used by Traceattack
                string hboxName;                //Hitbox bone name.
                int quoteIndices[2] = {0, 0};   //Which words include a double quotation mark?

                string finalString = "$hbox ";  //"Initialize" with parameter

                vector<string> words = split(buffer, ' '); //Split by space
                
                //Search for double quotes
                for (size_t i = 0; i < words.size(); i++)
                {
                    if (words[i].find("\"") != string::npos && quoteIndices[0] == 0)
                    {
                        quoteIndices[0] = (int)i;
                    }
                    else if (words[i].find("\"") != string::npos)
                    {
                        quoteIndices[1] = (int)i;
                    }
                }

                for (size_t i = quoteIndices[0]; i < quoteIndices[1]+1; i++)
                {
                    hboxName += words[i];
                    if (i < quoteIndices[1])
                        hboxName += " ";
                }

                //Set Hbox Type
                hboxType = stoi(words[1]);

                //Put Maxes and Mins to their individual places into the array
                maxesAndMins[0] = stof(words[quoteIndices[1] + 1]) * scaleMult;
                maxesAndMins[1] = stof(words[quoteIndices[1] + 2]) * scaleMult;
                maxesAndMins[2] = stof(words[quoteIndices[1] + 3]) * scaleMult;
                maxesAndMins[3] = stof(words[quoteIndices[1] + 4]) * scaleMult;
                maxesAndMins[4] = stof(words[quoteIndices[1] + 5]) * scaleMult;
                maxesAndMins[5] = stof(words[quoteIndices[1] + 6]) * scaleMult;

                //Make string structure.
                finalString +=
                    to_string(hboxType)
                    + " "
                    + hboxName
                    + " "
                    + to_string(maxesAndMins[0])
                    + " "
                    + to_string(maxesAndMins[1])
                    + " "
                    + to_string(maxesAndMins[2])
                    + " "
                    + to_string(maxesAndMins[3])
                    + " "
                    + to_string(maxesAndMins[4])
                    + " "
                    + to_string(maxesAndMins[5]);

                int iter = 0;
                for (string word : words)
                {
                    //Ignore the parameters and add other words 
                    //if there are any (comments etc.)
                    if (iter > quoteIndices[1] + 6)
                        finalString += " " + word;
                    iter++;
                }

                fsWriteStream << finalString << endl;
            }
            else if (buffer.find("$attachment") != string::npos)
            {
                float maxesAndMins[3];          //XYZ values
                int attIndex = 0;               //Attachment index.
                string attName;                 //Attachment bone name.
                int quoteIndices[2] = { 0, 0 };   //Which words include a double quotation mark?

                string finalString = "$attachment ";  //"Initialize" with parameter

                vector<string> words = split(buffer, ' '); //Split by space

                //Search for double quotes
                for (size_t i = 0; i < words.size(); i++)
                {
                    if (words[i].find("\"") != string::npos && quoteIndices[0] == 0)
                    {
                        quoteIndices[0] = (int)i;
                    }
                    else if (words[i].find("\"") != string::npos)
                    {
                        quoteIndices[1] = (int)i;
                    }
                }

                for (size_t i = quoteIndices[0]; i < quoteIndices[1] + 1; i++)
                {
                    attName += words[i];
                    if (i < quoteIndices[1])
                        attName += " ";
                }

                //Set Hbox Type
                attIndex = stoi(words[1]);

                //Put Maxes and Mins to their individual places into the array
                maxesAndMins[0] = stof(words[quoteIndices[1] + 1]) * scaleMult;
                maxesAndMins[1] = stof(words[quoteIndices[1] + 2]) * scaleMult;
                maxesAndMins[2] = stof(words[quoteIndices[1] + 3]) * scaleMult;

                //Make string structure.
                finalString +=
                    to_string(attIndex)
                    + " "
                    + attName
                    + " "
                    + to_string(maxesAndMins[0])
                    + " "
                    + to_string(maxesAndMins[1])
                    + " "
                    + to_string(maxesAndMins[2]);

                int iter = 0;
                for (string word : words)
                {
                    //Ignore the parameters and add other words 
                    //if there are any (comments etc.)
                    if (iter > quoteIndices[1] + 3)
                        finalString += " " + word;
                    iter++;
                }

                fsWriteStream << finalString << endl;
            }
            else if (buffer.find("$eyeposition") != string::npos)
            {
                float maxesAndMins[3];  //Eye position XYZ values

                string finalString = "$eyeposition "; //"Initialize" with parameter

                vector<string> words = split(buffer, ' '); //Split by space

                //Put eye position values to their individual places into the array
                maxesAndMins[0] = stof(words[1]) * scaleMult;
                maxesAndMins[1] = stof(words[2]) * scaleMult;
                maxesAndMins[2] = stof(words[3]) * scaleMult;

                finalString += 
                    to_string(maxesAndMins[0]) 
                    + " " 
                    + to_string(maxesAndMins[1]) 
                    + " " 
                    + to_string(maxesAndMins[2]);

                int iter = 0;
                for (string word : words)
                {
                    //Ignore the parameters and add other words 
                    //if there are any (comments etc.)
                    if (iter > 3) 
                        finalString = finalString + " " + word;
                    iter++;
                }
                fsWriteStream << finalString << endl;
            }
            else if (buffer.find("$scale") != string::npos)
            {
                float scaleFloat;   //Scale Value

                string finalString = "$scale "; //"Initialize" with parameter
                
                vector<string> words = split(buffer, ' '); //Split by space

                scaleFloat = stof(words[1]) * scaleMult;
                finalString = finalString + to_string(scaleFloat);

                int iter = 0;
                for (string word : words)
                {
                    //Ignore the parameters and add other words 
                    //if there are any (comments etc.)
                    if (iter > 1)
                        finalString = finalString + " " + word;
                    iter++;
                }
                fsWriteStream << finalString << endl;
            }
            else 
            {
                // We didnt find any parameters. Write the line just like it is
                fsWriteStream << buffer << endl;
            }
        }
        
        // We've done reading and writing files.
        fsMainStream.close();
        fsWriteStream.close();

        if (rename(fileName.c_str(), (fileName + "_backup").c_str()) != 0)
        {
            cout << "Error renaming file: " << fileName << endl;
            cout << "You can manually use newly created file FILENAME.qc_scaled" << endl;
            system("pause");
            return;
        }
        else if (rename((fileName + "_scaled").c_str(), (fileName).c_str()) != 0)
        {
            cout << "Error renaming file: " << fileName << "_scaled" << endl;
            cout << "You can manually use newly created file FILENAME.qc_scaled" << endl;
            system("pause");
            return;
        }
        else
        {
            return;
        }
    }
}

