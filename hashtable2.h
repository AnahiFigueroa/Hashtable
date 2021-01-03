//hashtable implentation using quadratic probing

#include "Node.h"

#ifndef hashtable2_h
#define hashtable2_h

class hashtable2{
    public:
    hashtable2();
    hashtable2(int words);
    void create(ifstream &dictFile);
    void insert(string word);
    int hash(string word);
    void print();
    bool isPrime(int n);
    int nextPrime(int N);
    bool find(string wordQuery);
    
    
    Node *table; //an array of nodes
    int collisions;
    int mispelledCount;
    int tableSize;
};

hashtable2::hashtable2(){
    collisions = 0;
    mispelledCount = 0;
    tableSize = 959659;
    table = new Node[tableSize];
}


hashtable2::hashtable2(int words){
    collisions = 0;
    mispelledCount = 0;
    int doublewords = 2 * words;
   // cout << "word count times 2: " << doublewords << endl;
    tableSize = nextPrime(doublewords);
  //  cout << "table size: " << tableSize << endl;
  
    //I have to set table size to 2x words and then find the next prime number
    table = new Node[tableSize];
    
}

bool hashtable2::isPrime(int n){
    if (n <= 1){
        return false;
    }
    if (n <= 3){
        return true;
    }
    
  
    if (n%2 == 0 || n%3 == 0){
        return false;
    }
    
    for (int i=5; i*i<=n; i=i+6){
        if (n%i == 0 || n%(i+2) == 0){
           return false;
        }
    }
    return true;
}

int hashtable2::nextPrime(int n1){
    if (n1 <= 1){
        return 2;
    }
       int primenumber = n1;
       bool found = false;
     

       while (!found) {
           primenumber++;
     
           if (isPrime(primenumber)){
               found = true;
           }
       }
     
       return primenumber;
}


/*
 Loops through all the words in the file and calls insert in each one
 */
void hashtable2::create(ifstream &dictFile){
 //   cout << "here in create" << endl;
    string word = "";
    while (dictFile >> word){
     //   cout << word; 
        insert(word);
    }
}

int hashtable2::hash(string word){
    unsigned long hash = 0;
    int key = 0;
    
    for (int i = 0; i < word.size(); i++){
        hash = hash * 37 + word[i];
    }
    
    key = hash % tableSize;
    return key;
}

//dictionary file
void hashtable2::insert(string word){
   // cout << "here in insert" << endl;
   int key;
   key = hash(word);
 //   cout << word << endl; 
   int h = 1;

      while( table[key].word != ""){
           key = (key + (h * h)) % tableSize;
           h++;
      }

      table[key].word = word;
     // cout << word;
   }



bool hashtable2::find(string wordQuery){
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
       
       //cout << "After pre-processing: " << wordQuery << endl;
    int key = hash(wordQuery);
    int h = 1;
    while (table[key].word != wordQuery && h < 50){
        key = (key + (h * h)) % tableSize;
        h++;
    }
    if (h == 50){
        return false;
    }
    else {
        return true; 
}
}

void hashtable2::print(){
    for (int i = 0; i < tableSize; i++){
           cout << i;
           Node* currentptr = &table[i];
           if (currentptr->word != ""){
                   while(currentptr != NULL){
                       cout << currentptr->word<< " ";
                       currentptr = currentptr->next;
                       
                   }
           }
              cout << endl;
     }
}

















#endif /* hashtable2_h */
