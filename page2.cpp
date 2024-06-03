#include <iostream>
#include <cstdlib>
#include "demo.cpp"
using namespace std;

const string file = "page1.exe";
const string file1 = "page3.exe";

class GameChooser
{
public:
    void chooseGame(int choice)
    {
        if (choice == 1)
        {
            cout << "Congratulations, you have chosen the game 1.\n";
            system("cls");
            system(file.c_str());
        }
        else if (choice == 2)
        {
            cout << "Congratulations, you have chosen the game 2.\n";
            system("cls");
            system(file1.c_str());
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }
};

int main()
{
    GameChooser game;
    int choice;
    cout << GREEN << "CHOOSE GAME OR SOMETHING BRAINY " << RESET << endl;
    cout << "Enter 1 for Game  "
         << BLUE << "or  " << RESET << "Enter 2 to look into Advance data strcutures";
    cin >>
        choice;

    game.chooseGame(choice);

    return 0;
}
