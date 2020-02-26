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
    string word;
    bool beginning;
    bool end;
    int totalNextWords;
    int oldRandomNumber = 0;
    unordered_map<string, int> wordCount;
    unordered_map<string, Word*> nextWord;

  public:
    // static int totalExistingWords;
    //constructor
    Word(string s, bool b, bool e);
    //destructor
    ~Word();
    //get the word
    string getWord();
    //get if the word is the beginning or end of sentence
    bool isBeginning();
    bool isEnd();
    //add the next word
    void add(Word* word);
    //get the next word
    Word* getNext();

};

#endif