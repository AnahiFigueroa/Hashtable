#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include "main.h"
#include "hashtable.h"
#include "hashtable2.h"
#include "Node.h"

using namespace std::chrono;

int main(int argc, const char** argv) {
    
    ifstream inFile;
    string dictFile(argv[1]);
    inFile.open(dictFile.c_str());
 //   cout << dictFile.c_str();
    
    ifstream inputFilestream;
    string inputFile(argv[2]);
    inputFilestream.open(inputFile.c_str());
   
    string dictionaryword = "";
    int wordcount = 0;
    inFile >> dictionaryword;
    while (inFile){
        wordcount++;
        inFile >> dictionaryword;
    }
    
   
    
    inFile.clear();
    inFile.seekg(0, ios::beg);
    
    hashtable table(wordcount);
    table.create(inFile);
    
    inFile.clear();
    inFile.seekg(0, ios::beg);
    
    hashtable2 table2(wordcount);
    table2.create(inFile);
   // table2.print();
   
    

       
    
    //table.print();
auto start_hashtable1 = high_resolution_clock::now();
    string word = "";
    int mispelledCount = 0;
    while (inputFilestream >> word){
        if(!table.find(word)){
         //   cout << "could not find " << word << endl;
            mispelledCount++;
        }
    }

    auto stop_hahshtable1 = high_resolution_clock::now();
    auto hashtable1_duration = duration_cast<nanoseconds>(stop_hahshtable1-start_hashtable1);
    
    cout << "Total number of mispelled words in hashtable1: "<< mispelledCount << endl;
    cout << "Hashtable1 duration time: " << hashtable1_duration.count();
    cout << endl;
    
   inputFilestream.clear();
   inputFilestream.seekg(0, ios::beg);

auto start_hashtable2 = high_resolution_clock::now();
    mispelledCount = 0;
    while (inputFilestream >> word){
        if(!table2.find(word)){
            //   cout << "could not find " << word << endl;
                mispelledCount++;
           }
       }
    
    auto stop_hahshtable2 = high_resolution_clock::now();
     auto hashtable2_duration = duration_cast<nanoseconds>(stop_hahshtable2-start_hashtable2);
    cout << endl; 
    cout << "Total number of mispelled words in hashtable2: "<< mispelledCount << endl;
    
    cout << "Hashtable2 duration time: " << hashtable2_duration.count();
       cout << endl;
       cout << endl;
    if (hashtable1_duration.count() < hashtable1_duration.count()){
        cout << "Hashtable1 was more time efficient" << endl;
    }
    else {
        cout << "Hashtable2 was more time efficient" << endl;
    }
    
    
    return 0;
}
