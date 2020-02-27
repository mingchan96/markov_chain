#include "word.h"
// #include <iostream>
// #include <string>
// #include <unordered_map>
// #include <random>
// #include <time.h>

// using namespace std;

Word::Word(string s, bool b, bool e){
    word = s;
    beginning = b;
    end = e;
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

void Word::add(Word* word){
    //if the word doesn't exists, then insert it into the hash table
    if(wordCount.find(word->getWord()) == wordCount.end()){
        wordCount.insert(make_pair(word->getWord(),1));
        nextWord.insert(make_pair(word->getWord(), word));
    }
    //if it does exist, then increment the counter for the word
    else{
        wordCount[word->getWord()]++;
    }
    totalNextWords++;
}

Word* Word::getNext(){
    //if the hashtable doesn't have any next words
    if(wordCount.size() == 0){
      return NULL;
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
        int y = x + itr->second;
        //if the random number is between x and y, then choice this word
        if(x <= randomNumber && randomNumber <= y){
            break;
        }
        else{
            x = y;
        }
    }
    return nextWord[nextWordKey];
}

void Word::printNextWords(){
  cout << "Printing next words for \""<< word <<"\""<< endl;
  unordered_map<string, Word*>:: iterator itr;
    for(itr = nextWord.begin(); itr != nextWord.end(); itr++){
      cout << itr->second->getWord() << ", ";
    }
    cout << endl;
}