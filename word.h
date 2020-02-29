#ifndef  WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <time.h>

using namespace std;

class Word
{
  private:
    string word = "";
    bool beginning = false;
    bool end = false;
    int totalNextWords = 0;
    int oldRandomNumber = 0;
    unordered_map<string, int> wordCount;

  public:
    unordered_map<string, Word*> nextWord;
    // static int totalExistingWords;
    //constructor
    Word(string s);
    //destructor
    ~Word();
    //get the word
    string getWord();
    //get if the word is the beginning or end of sentence
    bool isBeginning();
    bool isEnd();
    //set the beginning and ending
    void setBeginning(bool b);
    void setEnd(bool e);
    //add the next word
    void add(Word* word);
    //get the next word
    Word* getNext();
    //print the next words 
    void printNextWords();
};

#endif