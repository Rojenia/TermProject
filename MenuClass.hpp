//
//  Nebula.hpp
//  TermProject
//
//  Created by Jenna Garcia on 4/5/17.
//  Copyright © 2017 Jenna Garcia. All rights reserved.
//

#include <string>
#include <vector>
#include <fstream>


using namespace std;

class MenuClass{
private:
    string name;
    long size;
    vector<string> content;
    long currentLine;
    vector<string> temp;
    
    bool lineBool(string, string);
    void contentFile(fstream &);
    void outOfBounds(long &);
    void help();
    
public:
    
    MenuClass();
    bool openFile(fstream &, string, char);
    string getFilename();
    void menu();
    void inputMenu(char &);
    void sub(string);
    void copy(long);
    void locate(string);
    void remove(long);
    void move(long);
    void type(long);
    void paste();
    void insert(long);
    void replace(long);
    void file(char, string);
    void save();
    void ClearScreen();
    
};
