#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <sstream>
// #include <bits/stdc++.h>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <time.h>
#include "word.h"
#include "filterProfanity.h"

using namespace std;

//iterate through the hash table to delete the pointers
int deleteHashTable(unordered_map<string, Word*> wordHash){
  unordered_map<string, Word*>:: iterator itr;
  for(itr = wordHash.begin(); itr != wordHash.end(); itr++){
    delete itr->second;
  }
  return 0;
}

template<typename T>
//check to see if word exists in hash table
bool wordExist(unordered_map<string, T> wordHash, string word){
  if (wordHash.find(word) == wordHash.end()){
    return false;
  }
  return true;
}

bool isEndOfSentence(string word){
  char lastChar = word.back();
  // unordered_set<char> punctuations {'.','!','?'};
  // return punctuations.find(lastChar) != punctuations.end();
  return (lastChar == '#');
}

int generateRandomNumber(int totalWords, int oldNumber){
  int min = 1;
  int max = totalWords;
  // mt19937 rng(time(0));
  mt19937_64 rng(time(0));
  uniform_int_distribution<int> gen(min, max);

  int randomNumber = gen(rng);
  while(randomNumber == oldNumber){
    randomNumber = gen(rng);
  }
  // cout << "Random Number: " << randomNumber << endl;
  return randomNumber;
}

//generate the starting word
string generateStartWord(unordered_map<string,int> beginningHash, int randomNumber){
  
  //iterate through the hash table to find the next word
  int x = 1;
  string key = "";
  unordered_map<string, int>:: iterator itr;
  for(itr = beginningHash.begin(); itr != beginningHash.end(); itr++){
      int y = x + itr->second;
      key = itr->first;
      //if the random number is between x and y, then choice this word
      if(x <= randomNumber && randomNumber <= y){
          cout << "Starting word: " << key << endl;
          return key;
      }
      else{
          x = y;
      }
  }
  return key;
}

//generate the sentences
string markovIteration(string startWord, unordered_map<string, Word*> wordHash, int iterations){
  string output = startWord;
  Word* currentWord = wordHash[startWord]->getNext();

  while(iterations != 0 && currentWord != NULL){
    output += " " + currentWord->getWord();
    //check if the word is a word at the end of a sentence
    if(currentWord->isEnd()){
      return output;
    }

    currentWord = currentWord->getNext();
    iterations--;
  }

  return output;
}

//first argument filename, second number of quotes
//third argument determines if only non-profanity words allowed
//int main(int argc, char** argv){
int main(int argc, char *argv[]) {

  string filename = argv[1];
  int numQuotes = stoi(argv[2]);
  int safeWords = stoi(argv[3]);

  // string filename = "Ron_Burgundy.txt";
  // string filename = "Christmas_Carol.txt";
  // int numQuotes = 3;
  // int safeWords = 0;

  ifstream input_file;
  input_file.open(filename);

  if(!input_file.is_open()){
    cout << "File could not be opened" << endl;
    return 0;
  }

  FilterProfanity* filterProfanity;
  if(safeWords == 1){
    filterProfanity = new FilterProfanity();
    cout << "***Safe words is turned on***\n" << endl;
  }
  else if(safeWords == 0){
    cout << "***Safe words is turned off***\n" << endl;
  }
  else{
    cout << "Invalid safeWords argument" << endl;
    return 0;
  }
  

  vector <string> beginning;
  unordered_map <string, Word*> wordHash;
  unordered_map <string, int> beginningHash;

  int iterations = 100;
  int sentenceWordPosition = 1;
  int totalBeginning = 0;
  // string word = "";
  // string previousWord = "";
  // while(input_file >> word && iterations != 0){
  //   while(input_file >> word){
  //     // cout << word;
  //     bool profanityWord = false;
  //     bool beginning = false;
  //     bool ending = false;

  //     if (safeWords == 1){
  //       profanityWord = filterProfanity->isProfanity(word);
  //     }

  //     //the start of a sentence
  //     if(sentenceWordPosition == 1){
  //       // cout << " (beginning of sentence)";
  //       beginning = true;
  //       if(!profanityWord){
  //         totalBeginning++;
  //         if(wordExist(beginningHash, word)){
  //           beginningHash[word]++;
  //         }
  //         else{
  //           beginningHash[word] = 1;
  //         }
  //       }
  //     }
      
  //     //the end of a sentence
  //     if(isEndOfSentence(word)){
  //       // cout << " (end of sentence)";
  //       sentenceWordPosition = 0;
  //       ending = true;
  //     }

  //     if(!profanityWord){
  //       //check if the word is in the hash
  //       if(!wordExist(wordHash, word)){
  //         wordHash[word] = new Word(word, beginning, ending);
  //       }

  //       //add the current word to the previous word
  //       if(previousWord != ""){
  //         Word* currentWord = wordHash[word];
  //         wordHash[previousWord]->add(currentWord);
  //       }
  //       previousWord = word;
  //     }

  //   iterations--;
  //   sentenceWordPosition++;
    
  //   // cout << endl;
  // }

  string tweet = "";
  Word* wordPtr = NULL;
  Word* previousWordPtr = NULL;

  while(getline(input_file, tweet)){
    istringstream ss(tweet);
    bool beginningTweet = true;

    do{
      bool profanityWord = false;
      string word = "";
      ss >> word;
      
      //if safe word is turned on and word is a profanity word then skip processing
      if (safeWords == 1 && filterProfanity->isProfanity(word)){
        continue;
      }

      //check if the word is in the hash
      //create it if doesn't exist and fetch it if it does exist
      if(!wordExist(wordHash, word)){
        wordPtr = new Word(word);
        wordHash[word] = wordPtr;
      }
      else{
        wordPtr = wordHash[word];
      }

      if(previousWordPtr != NULL){
        previousWordPtr->add(wordPtr);
      }
      previousWordPtr = wordPtr;

      if (beginningTweet){
        totalBeginning++;
        if(wordExist(beginningHash, word)){
          beginningHash[word]++;
        }
        else{
          beginningHash[word] = 1;
          wordPtr->setBeginning(true);
        }
        beginningTweet = false;
      }

    }while(ss);

    //last word to be processed will be set to end
    if(wordPtr != NULL){
      wordPtr->setEnd(true);
    }
  }

  input_file.close();

  int randomNumber = 0;
  for (int i = numQuotes; i > 0; i--){
    randomNumber = generateRandomNumber(totalBeginning, randomNumber);
    string startingWord = generateStartWord(beginningHash, randomNumber);
    // string startingWord = "Dear";
    string outputString = markovIteration(startingWord, wordHash, 100);
    cout << outputString << "\n" << endl;
  }
  
  //delete the objects in the system
  deleteHashTable(wordHash);
  if(safeWords==1) delete filterProfanity;
  cout << "Executed: line 203" << endl;

  return 0;
}