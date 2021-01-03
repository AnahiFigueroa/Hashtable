//  Created by Anahi Figueroa  on 3/26/20.
#ifndef hashtable_h
#define hashtable_h

#include "Node.h"
#include <fstream>

using namespace std;

class hashtable {
public:
    hashtable();
    hashtable(int words);
    void create(ifstream &dictFile);
    void insert(string word);
    unsigned long hash(string word);
    void print();
    bool find(string wordQuery);
    
    Node *table; //an array of nodes
    int collisions;
    int mispelledCount;
    int tableSize;
};

hashtable::hashtable(){
    collisions = 0;
    mispelledCount = 0;
    tableSize = 15;
    table = new Node[tableSize];
}


hashtable::hashtable(int words){
    collisions = 0;
    mispelledCount = 0;
    tableSize = words * 2;
    table = new Node[tableSize];
}

/*
 Loops through all the words in the file and calls insert in each one
 */
void hashtable::create(ifstream &dictFile){
    string word = "";
    while (dictFile >> word){
     //   cout << word;
      //  cout << endl;
     //   cout << "size: " << hash(word);
        insert(word);
        
    
    }
}

unsigned long hashtable::hash(string word){
    unsigned long hash = 0;
    unsigned long key = 0;
    
    for (int i = 0; i < word.size(); i++){
        hash = hash * 37 + word[i];
    }
    
    key = hash % tableSize;
    return key;
}

//dictionary file
void hashtable::insert(string word){
   unsigned long key;
   key = hash(word);
    if (table[key].word == ""){  //no word in the node at the position of the array
        table[key].word = word;
    }
    else{
       
        Node *addMe = new Node(word);
        Node *currentptr = &table[key]; //currentptr to the node at the position in the array which is also the head of the linkedlist
        while (currentptr->next != NULL){
            if (currentptr->word == word){
                return; 
            }
            currentptr = currentptr->next;
        }
            currentptr->next = addMe;    //assigning the last node's next ptr to the node we just created which holds the word we passed into                             insert
    }
}

bool hashtable::find(string wordQuery){
    for (int i = 0; i < wordQuery.size(); i++){
        if (wordQuery[i] <= 90 && wordQuery[i] >= 65){
            wordQuery[i] += 32;
        }
        if (wordQuery[i] == '-' && wordQuery[i+1] == '-'){
            return true;
        }
    }
     //access the character in wordQuery at that index
    if (wordQuery[wordQuery.size()-1] == '.' ||
        wordQuery[wordQuery.size()-1] == ',' ||
        wordQuery[wordQuery.size()-1] == ';' ||
        wordQuery[wordQuery.size()-1] == ':' ||
        wordQuery[wordQuery.size()-1] == '"' ||
        wordQuery[wordQuery.size()-1] == '?' ||
        wordQuery[wordQuery.size()-1] == '!'){
    
        wordQuery.erase(wordQuery.size()-1, 1); 
    }
    
    if (wordQuery[0] >= 48 && wordQuery[0] <= 57 ){
        return true; 
    }
    
    unsigned long key = hash(wordQuery);
    
    if (table[key].word == wordQuery){
        return true;
    }
    else {
        Node *currentptr = &table[key];
        while (currentptr != NULL){
            if (currentptr->word == wordQuery){
                return true;
            }
            else{
                currentptr = currentptr->next;
            }
        }
    }
    return false; 
}

void hashtable::print(){
    for (int i = 0; i < tableSize; i++){
        cout << i;
        Node* currentptr = &table[i];
//        cout << currentptr->word << " ";
        if (currentptr->word != ""){
                while(currentptr != NULL){
                    cout << currentptr->word<< " ";
                    currentptr = currentptr->next;
                    
                }
        }
           cout << endl;
  }
}









#endif /* hashtable_h */
