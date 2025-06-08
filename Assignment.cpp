#include <iostream>
#include <fstream>
#include <stdlib.h> // For system("cls")
#include <string>

using namespace std;

class Flashcard
{
public:
    string question;
    string answer;
    int score;

    Flashcard(string question, string answer, int score){}   //define each question and answer


};

class SystemProcess //manage the whole system process
{
public:
    Flashcard flashcards[max_flashcards]; // Fixed array instead of vector
    int count;                      // Number of flashcards currently stored

    SyetemManager() : count(0) {}

};

class SystemManager{  //to run the function which displaying on menu
};


class App  //display the menu
{
private:


public:

};

int main()
{

    return 0;
}
