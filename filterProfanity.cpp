#include "filterProfanity.h";

FilterProfanity::FilterProfanity(){
    string filename = "profanity.txt";
    ifstream input_file;
    input_file.open(filename);
    bool file_exists = true;

    if(!input_file.is_open()){
        cout << " Profanity file could not be opened" << endl;
        file_exists = false;
    }

    string profanityWord;
    while(file_exists && input_file >> profanityWord){
        profanityMap[profanityWord] = 1;
    }    
}

bool FilterProfanity::isProfanity(string word){
    if(profanityMap.count(word) > 0){
        return true;
    }
    return false;
}