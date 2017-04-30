
#include "MenuClass.hpp"
#include <iostream>

using namespace std;

void inputMenu(char &);
void menu();

int main()
{
    MenuClass cabin;
    char start = 's';
    
    cabin.menu();
    
    do
    {
        cabin.inputMenu(start);
    }
    while (start != 'Q');

}





