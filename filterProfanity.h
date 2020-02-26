#ifndef  FILTERPROFANITY_H
#define FILTERPROFANITY_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class FilterProfanity
{
  private:
    map<string, int> profanityMap;

  public:
    //constructor sets up the profanity hash table
    FilterProfanity();

    //function used to determine if a word is profanity
    bool isProfanity(string word);

};

#endif