#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "demo.cpp"
using namespace std;

const string filename = "users.txt";
const string file = "page2.exe";

class login
{
private:
    string username;
    string password;

public:
    login(){};
    void registerUser(const string &username, const string &password)
    {
        ofstream file(filename, ios::app);
        if (file.is_open())
        {
            file << username << " " << password << endl;
            file.close();
            cout << "Registration successful!\n";
        }
        else
        {
            cout << "Error: Unable to open file for registration.\n";
        }
    }
    bool loginUser(const string &username, const string &password)
    {
        ifstream file(filename);
        if (file.is_open())
        {
            string storedUsername, storedPassword;
            while (file >> storedUsername >> storedPassword)
            {
                if (storedUsername == username && storedPassword == password)
                {
                    file.close();
                    return true;
                }
            }
            file.close();
        }
        else
        {
            cout << "Error: Unable to open file for login.\n";
        }
        return false;
    }
};

int main()
{
    login userManager;

    int choice;
    bool flag = true;
    string username, password;
    cout << GREEN << "LOGIN AND REGISTERATION PAGE " << RESET << endl;
    do
    {
        cout << "1. Register\n2. Login\n3. Exit\n";
        cout << endl
             << "Enter your choice :";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << BLUE << "REGISTER" << RESET << endl;
            cout << "Enter your username: ";
            cin >> username;
            cout << "Enter your password: ";
            cin >> password;
            userManager.registerUser(username, password);
            break;
        case 2:
            cout << BLUE << "LOGIN" << RESET << endl;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (userManager.loginUser(username, password))
            {
                cout << "Login successfully\n";
                flag = false;
                system("cls");
                system(file.c_str());
            }
            else
            {
                cout << "Login failed. Incorrect username or password.\n";
            }
            break;
        case 3:
            cout << "Press any key to continue...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3 && flag);

    return 0;
}
