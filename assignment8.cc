#include "assignment8.h"

//******************************************************************//
//   PROGRAM:    CSCI 340 Assignment 8                              //
//   PROGRAMMER: Margaret Higginbotham                              //
//   LOGON ID:   z1793581                                           //
//   DUE DATE:   April 18, 2018                                     //
//                                                                  //
//   FUNCTION:   Creates, searches, prints, and manages             //
//               an item inventory                                  //
//******************************************************************//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
   return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
}

////////////////////////////////////////////////////////////////
//                        CONSTRUCTOR                         //
////////////////////////////////////////////////////////////////
/***************************************************************
HT::HT(int s = 11)
Use: Constructor
Parameters: 1. int s = 11- size s default 11
Returns: Nothing
***************************************************************/
HT::HT(int s = 11){
  table_size = s;
  item_count = 0;
  hTable = new vector <Entry>(s);
}

////////////////////////////////////////////////////////////////
//                        DESTRUCTOR                          //
////////////////////////////////////////////////////////////////
/***************************************************************
HT::~HT()
Use: Destructor
Parameters: None
Returns: Nothing
***************************************************************/
HT::~HT(){
  delete hTable;
}

////////////////////////////////////////////////////////////////
//                    MEMBER FUNCTIONS                        //
////////////////////////////////////////////////////////////////
/***************************************************************
bool HT::insert(const Entry& e)
Use: Inserts item e in the hash table
Parameters: 1. const Entry& e- item being inserted
Returns: bool
***************************************************************/
bool HT::insert(const Entry& e){
  if(item_count < table_size){
    item_count++;
    int hash = hashing(e.key);

    for(int i = 0; i < table_size; i++){
      if(hTable -> at((i + hash) % table_size).key == "---"){
        hTable ->at((i + hash) % table_size) = e;
        break;
      }

    }

  }

  return false;
}

/***************************************************************
int HT::search(const string& key2)
Use: Searches the hash table for a record with a given key
Parameters: 1. const string& key2- key2 is being searched for
Returns: int
***************************************************************/
int HT::search(const string& key2){
  int current = -1;
  int hash = hashing(key2);

  for(int i = 0; i <table_size; i++){
    if(hTable -> at((i + hash) % table_size).key == key2){
      current = (i + hash) % table_size;
      break;
    }

  }

  return current;
}

/***************************************************************
bool HT::remove(const string& s)
Use: Removes an item with a key s
Parameters: 1. const
Returns: bool
***************************************************************/
bool HT::remove(const string& s){
  int current = search(s);

  if(current < 0)
    return false;

  else{
    Entry* ent = new Entry();
    hTable -> at(current) = *ent;
    return true;
  }

}

/***************************************************************
void HT::print()
Use: Prints the hashtable
Parameters: None
Returns: Nothing
***************************************************************/
void HT::print(){
  cout << "\n----Hash Table-----\n";

  for(vector<Entry>::iterator i = hTable -> begin(); i != hTable -> end(); i++){
    if(i -> key != "---")
      cout << setw(2) << right << i - hTable -> begin() << ": " << i -> key << " " << i -> description << "\n";
  }

  cout << "-------------------\n\n";
}

////////////////////////////////////////////////////////////////
//                     GLOBAL FUNCTIONS                       //
////////////////////////////////////////////////////////////////
/***************************************************************
Entry* get_entry (const string& line)
Use: Takes a line of input and parses it to create a new Entry
Parameters: 1. const string& line- string that is going to be parsed
Returns: Entry
***************************************************************/
Entry* get_entry (const string& line){
  Entry* ent = new Entry();
  ent -> key = line.substr(line.find(':') + 1, 3);
  ent -> description = line.substr(line.find(':') + 5);

  return ent;
}

/***************************************************************
string get_key (const string& line)
Use: Takes a line of input and parses it to return the item key
Parameters: 1. const string& line- string that is going to be parsed
Returns: string
***************************************************************/
string get_key (const string& line){
  return line.substr(line.find(':') + 1);
}

////////////////////////////////////////////////////////////////
//                          MAIN                              //
////////////////////////////////////////////////////////////////
int main(int argc, char** argv){
  if(argc < 2){
    cerr << "argument: file-name\n";
    return 1;
  }

  HT ht;
  ifstream infile(argv[1], ios::in);
  string line;
  infile >> line;
  while(!infile.eof()){
    if(line[0] == 'A'){
      Entry* e = get_entry(line);
      ht.insert(*e);
      delete e;
    }

    else{
      string key = get_key(line);
      if(line[0] == 'D'){
        cout << "Removing " << key << "...\n";
        bool removed = ht.remove(key);
        if(removed)
          cout << key << " is removed successfully...\n\n";
        else
          cout << key << " does not exist, no key is removed...\n\n";
      }

      else if(line[0] == 'S'){
        int found = ht.search(key);
        if(found < 0)
          cout << key << " does not exit in the hash table ..." << endl << endl;
        else
          cout << key << " is found at table position " << found << endl << endl;
      }

      else if(line[0] == 'P'){
        cout << "\nDisplaying the table: " << endl;
        ht.print();
      }

      else
        cerr << "wrong input: " << line << endl;
    }

    infile >> line;
  }

  infile.close();
  return 0;
}
