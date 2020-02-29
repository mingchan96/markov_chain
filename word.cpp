#include "word.h"
// #include <iostream>
// #include <string>
// #include <unordered_map>
// #include <random>
// #include <time.h>

// using namespace std;

Word::Word(string s){
    word = s;
    // Word::totalExistingWords++;
}

Word::~Word(){
    // Word::totalExistingWords--;
    // cout << "Erasing: " << word << endl;
    // cout << "Remaining Words: " << Word::totalExistingWords << "\n" << endl;
}

string Word::getWord(){
    return word;
}

bool Word::isBeginning(){
    return beginning;
}

bool Word::isEnd(){
    return end;
}

void Word::setBeginning(bool b){
    beginning = b;
}
void Word::setEnd(bool e){
    end = e;
}

void Word::add(Word* w){
    //if the word doesn't exists, then insert it into the hash table
    if(wordCount.find(w->getWord()) == wordCount.end()){
        wordCount.insert(make_pair(w->getWord(),1));
        nextWord.insert(make_pair(w->getWord(), w));
    }
    //if it does exist, then increment the counter for the word
    else{
        wordCount[w->getWord()]++;
    }
    totalNextWords++;
}

Word* Word::getNext(){
    Word* nextWordPtr = NULL;
    //if the hashtable doesn't have any next words
    if(wordCount.size() == 0){
      return nextWordPtr;
    }
    
    int min = 0;
    int max = totalNextWords;
    // mt19937 rng(time(0));
    mt19937_64 rng(time(0));
    uniform_int_distribution<int> gen(min, max);
    int randomNumber = gen(rng);

    //reduce repeatively choosing the same random number
    int iterations = 10;
    while(randomNumber==oldRandomNumber && iterations > 0){
      randomNumber = gen(rng);
      iterations--;
    }
    
    oldRandomNumber = randomNumber;

    //iterate through the hash table to find the next word
    int x = 0;
    string nextWordKey = "";
    unordered_map<string, int>:: iterator itr;
    for(itr = wordCount.begin(); itr != wordCount.end(); itr++){
        nextWordKey = itr->first;
        nextWordPtr = nextWord[nextWordKey];
        int y = x + itr->second;
        //if the random number is between x and y, then choice this word
        if(randomNumber <= y){
            break;
        }
        else{
            x = y;
        }
    }
    return nextWordPtr;
}

void Word::printNextWords(){
  cout << "Printing next words for \""<< word <<"\""<< endl;
  unordered_map<string, int>:: iterator itr;
    for(itr = wordCount.begin(); itr != wordCount.end(); itr++){
      cout << itr->first << ", " << itr->second << endl;
    }
}