#ifndef ASSIGNMENT8_H
#define ASSIGNMENT8_H

//******************************************************************//
//   PROGRAM:    CSCI 340 Assignment 8                              //
//   PROGRAMMER: Margaret Higginbotham                              //
//   LOGON ID:   z1793581                                           //
//   DUE DATE:   April 18, 2018                                     //
//                                                                  //
//   FUNCTION:   Creates, searches, prints, and manages             //
//               an item inventory                                  //
//******************************************************************//

#include <vector>
#include <string>

struct Entry{
  std::string key;
  std::string description;

  Entry() { key = "---"; }
};

class HT {
  private:
    std::vector<Entry>* hTable;
    int table_size;
    int item_count;
    int hashing(const std::string&);

  public:
    HT(int size);
    ~HT();
    bool insert(const Entry&);
    int search(const std::string&);
    bool remove(const std::string&);
    void print();
};

#endif
