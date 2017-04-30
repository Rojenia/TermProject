//  MenuClass.cpp
//  TermProject
//
//  Created by Jenna Garcia on 4/5/17.
//  Copyright © 2017 Jenna Garcia. All rights reserved.

#include "MenuClass.hpp"
#include <iostream>

using namespace std;

MenuClass::MenuClass()
{
    name = " ";
    size = 0;
    content.push_back("yes");
    currentLine = 0;
    temp.push_back("Temporary Storage");
}


/*************************
       CLEARSCREEN
 ************************/
void MenuClass::ClearScreen()
{
    cout << string( 100, '\n' );
}


/*************************
        OPEN FILE
 ************************/
bool MenuClass::openFile (fstream &file, string fileName, char start)
{
    
    if(start == 'N')
    {
        file.open(fileName, ios:: out);
    }
    else
    {
        file.open(fileName, ios:: in);
    }
    
    if(file.fail())
        return false;
    else
        return true;
    
}

/*************************
      CONTENTFILE
 ************************/
void MenuClass::contentFile(fstream &file)
{
    string line;
    getline(file,line);
    
    while(!file.eof())
    {
        content.push_back(line);
        getline(file,line);
    }
    size = content.size();
}

/*************************
      OUT OF BOUNDS
 ************************/
void MenuClass::outOfBounds(long &num)
{
    long range = currentLine + num;
    if (range <= 0){
        cout << "You are at the beginning of the document \n\n";
        
        if(range == 0)
            num = num;
        else
            num = -currentLine;
    }
    else if(range >= size)
    {
        cout << "You are at the end of the document \n\n";
        
        if(range == size)
            num = num - 1;
        else if(currentLine == 0)
            num = size - 1;
        else
            num = (size - 1) - currentLine;
    }
}


/*************************
       LINE BOOLEAN
 ************************/
bool MenuClass::lineBool(string a, string b)
{
    long aLength = a.length();
    long bLength = b.length();
    int length = 0;
    
    if(aLength == bLength)
    {
        for(int i = 0; i < aLength; i++)
        {
            if(a[i] != b[i])
            {
                length++;
            }
        }
    }
    else
        return false;
    
    if(length > 0)
        return false;
    else
        return true;
}

string MenuClass::getFilename()
{
    return name;
}

/*************************
        INPUTMENU
 ************************/
void MenuClass::inputMenu(char &action)
{
    string input;
    long nom = 0;
    
    cout << endl << "Type H for (H)elp" << endl;
    
    cin >> input;
    
    if(isalpha(input[0]))
        action = toupper(input[0]);
    
    if(action == 'C' || action == 'M' || action == 'T' || action == 'R' || action == 'D' || action == 'I')
        cin >> nom;
    
    ClearScreen();
    
    cout <<"----------" << name << "----------" << endl;
    
    switch(action)
    {
        case 'N':
        case 'O':
            file(action);
            break;
            
        case 'S':
            sub();
            break;
            
        case 'C':
            copy(nom);
            break;
            
        case 'L':
            locate();
            break;
            
        case 'D':
            remove(nom);
            break;
            
        case 'M':
            move(nom);
            break;
            
        case 'T':
            type(nom);
            break;
            
        case 'P':
            paste();
            break;
            
        case 'I':
            insert(nom);
            break;
            
        case 'R':
            replace(nom);
            break;
            
        case 'H':
            menu();
            break;
            
        case 'Q':
            save();
            exit(0);
            
        default:
            cout << "Invalid option. Please try again." << endl;
    }
    
}

/*************************
          MENU
 ************************/
void MenuClass::menu()
{
    string menu[14] = {"1. Open File (O)",
        "2. Create New File (N)",
        "3. Substitute (S)",
        "4. Copy (C)",
        "5. Locate (L)",
        "6. Delete (D)",
        "7. Move (M)",
        "8. Type (T)",
        "9. Paste (P)",
        "10. Insert (I)",
        "11. Replace (R)",
        "12. Save (S)",
        "13. Help (H)",
        "14. Quit (Q)"};
    
    for(int i = 0; i < 14; i++)
    {
        cout << menu[i] << endl;
    }
    
    cout << "Enter the first letter of the operation you want to perform. If the operation requires you to use lines." << endl;
    cout << "Type the first letter and the number of lines right afterwards" << endl;
    cout << "Example: Move 2 lines: M 2" << endl;
    
}

/*************************
        SUBSTITUTE
 ************************/
void MenuClass::sub() {
    string oldString;
    string newString;
    string word1;
    string line = content.at(currentLine);
    vector<char> newline (line.begin(), line.end());
    
    int j = 0;
    int index = 0;
    
    cout << "Old word:" << endl;;
    cin >> oldString;
    cout << "New word:" << endl;
    cin >> newString;
    
    
    char *oldWord = new char[oldString.length() + 1];
    char *newWord = new char[newString.length() + 1];
    
    strcpy(oldWord, oldString.c_str());
    strcpy(newWord, newString.c_str());
    
    for(int i = 0; i < newline.size(); i++)
    {
        if(isalpha(newline.at(i)))
        {
            if(oldWord[j] == newline.at(i))
            {
                for(int k = 0; k < oldString.length(); k++)
                {
                    if((i+k) < newline.size())
                        word1 += newline.at(i+k);
                    index = i+k+1;
                }
            }
            j++;
        }
        else
            j = 0;
        
        
        if(word1 == oldString)
        {
            newline.erase(newline.begin()+i, newline.begin()+index);
            newline.insert(newline.begin()+i, newWord, newWord+(sizeof(newWord)));
        }
        word1.clear();
        
    }
    
    string sentence(newline.begin(), newline.end());
    
    ClearScreen();
    
    if(!(lineBool(sentence, line)))
    {
        content[currentLine] = sentence;
        cout << currentLine + 1 << " - " << sentence << endl;
    }
    else
    {
        cout << "The word: " << oldString << endl;
        cout <<"Does not appear in the current line." << endl;
        cout << currentLine + 1 << " - " << line << endl;
    }
}

/*************************
          COPY
 ************************/
void MenuClass::copy(long num) {
    
    outOfBounds(num);
    
    num += 1;
    
    temp.clear();
    
    for(int i = 0; i < num; i++)
    {
        temp.push_back(content.at(currentLine + i));
    }
    
    for(int i = 0; i < num; i++)
    {
        cout << temp.at(i) << endl;
    }
    
}

/*************************
          LOCATE
 ************************/
void MenuClass::locate() {
    
    string wordSearch;
    string word1;
    long indexLine = 0;
    long cur = currentLine;
    int indexWord = 0;
    
    cout << "Find: ";
    cin.ignore();
    getline(cin, wordSearch);
    
    
    do
    {
        indexLine++;
        cur++;
        
        string line = content.at(cur);
        vector<char> newline (line.begin(), line.end());
    
        char *oldWord = new char[wordSearch.length() + 1];
    
        strcpy(oldWord, wordSearch.c_str());
        
        for(int i = 0; i < newline.size(); i++)
        {
            indexWord = 0;
            word1.clear();
            if(isalpha(newline.at(i)))
            {
                if(oldWord[indexWord] == newline.at(i))
                {
                    for(int k = 0; k < wordSearch.length(); k++)
                    {
                        if((i+k) < newline.size())
                        {
                            word1 += newline.at(i+k);
                        }
                    }
                    if(word1 == wordSearch){
                        currentLine += indexLine;
                        break;
                    }
                }
                indexWord++;
            }
            
        }
        if(indexLine >= size)
        {
            indexLine--;
        }

        
    } while(word1 != wordSearch && indexLine != (size-1));
    
    ClearScreen();
    
    cout << currentLine + 1 << " - " << content.at(currentLine) << endl;;

}

/*************************
          REMOVE
 ************************/
void MenuClass::remove(long num) {
    long last = currentLine + num;
    
    content.erase(content.begin()+currentLine, content.begin()+last);
    size = content.size();
    cout << content.at(currentLine) << endl;
}

/*************************
          MOVE
 ************************/
void MenuClass::move(long num) {
    
    outOfBounds(num);
    currentLine += num;
    
    cout << currentLine + 1 << " - " << content.at(currentLine) << endl;
}

/*************************
          TYPE
 ************************/
void MenuClass::type(long num) {
    outOfBounds(num);
    
    long endIndex = num + currentLine;
    
    for(long i = currentLine; i <= endIndex; i++)
    {
        cout << i + 1 << " - "<< content.at(i) << endl;
    }
    currentLine = endIndex;
}


/*************************
         PASTE
 ************************/
void MenuClass::paste() {
    
    for(int i = 0; i < temp.size(); i++)
    {
        cout << temp.at(i) << endl << endl;
    }
    
    content.insert(content.begin()+(currentLine+1), temp.begin(), temp.end());
    
    size = content.size();
    
    currentLine += temp.size();
    
    temp.clear();
}


/*************************
         INSERT
 ************************/
void MenuClass::insert(long num) {
    string sentence;
    
    cin.ignore();
    for(int i = 0; i < num; i++)
    {
        currentLine += 1;
        cout << currentLine + 1 << " - ";
        getline(cin, sentence);
        content.insert(content.begin()+currentLine, 1, sentence);
    }
    
    ClearScreen();
    
    size = content.size();
    cout << currentLine + 1 << " - " << content.at(currentLine);
    
}

/*************************
         REPLACE
 ************************/
void MenuClass::replace(long num) {
    string line;
    num += currentLine;
    for(long i = currentLine; i < num; i++)
    {
        cout << currentLine+ 1 << " - ";
        cin >> ws;
        getline(cin,line);
        
        content[currentLine] = line;
        
        if(currentLine != num - 1)
            currentLine++;
    }
    
}


/*************************
          FILE
 ************************/
void MenuClass::file(char ch)
{
    fstream newFile;
    string fileName, line;
    
    cout << "File name: ";
    cin >> ws;
    getline(cin, fileName);
    
    fileName = fileName + ".txt";
    
    name = fileName;
    
    if(content.size() > 0)
    {
        content.clear();
    }
    
    if(openFile(newFile, fileName, ch))
    {
        if(ch == 'N')
        {
            int a = 0;
            
            cout << "--------------" << fileName << "-----------------" << endl;
            cout << "How many lines would you like to insert? ";
            cin >> a;
            for(int i = 0; i < a; i++)
            {
                cout << i + 1 << " - ";
                cin >> ws;
                getline(cin, line);
                if(i == (a - 1))
                {
                    newFile << line;
                }
                else
                {
                    newFile << line << endl;
                }
                
                content.push_back(line);
            }
            size = content.size();
            newFile.close();
        }
        else if (ch == 'O')
        {
            cout << "--------------" << fileName << "-----------------" << endl;
            contentFile(newFile);
            newFile.close();
        }
    }
    
    
    else
        cout << "Error. File cannot be opened" << endl;
}

/*************************
          SAVE
 ************************/
void MenuClass::save()
{
    if(::remove(name.c_str()) != 0)
        cout << "File could not be saved." << endl;
    else
        cout << "Your file has been saved." << endl;
    
    ofstream outFile;
    
    outFile.open(name);
    
    if(outFile.is_open())
    {
        vector<string>::iterator it;
        
        for(it = content.begin(); it < content.end(); it++)
        {
            outFile << *it << endl;
        }
    }
    else
        cout << "Cannot create file" << endl;
    outFile.close();
}


