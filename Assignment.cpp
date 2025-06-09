#include <iostream>
#include <fstream>
#include <stdlib.h> // For system("cls")
#include <string>

using namespace std;
int num=0;
class Flashcard
{
public:
    string q;
    string a;
    int s;

    Flashcard(string question, string answer, int score){
        q = question;
        a = answer;
        s = score;
    }   //define each question and answer

    void showquestion(){
        cout<<question<<endl;
    }
    void showanswer(){
        cout<<answer<<endl;
    }
};

class SystemProcess //manage the whole system process
{
public:
    Flashcard* f_array = new Flashcards; // Fixed maximum array instead of vector
    int num;                  // Number of flashcards currently stored

    void UpdateScore(){}

    void

};

class SystemManager{  //to run the function which displaying on menu
private:
    SystemProgress progress;

public:
    SystemManager();
    void addcard(){
        string ques;
        string ans;
        int s;
        cout<<"Question: "<<endl;
        cin>>ques;
        cout<<"\nAnswer: "<<endl;
        cin>>ans;
        cout<<"\nScore: "<<endl;
        cin>>s;
        f_array[num] = Flashcard(ques, ans, s);
    }

    void deletecard(){
        for (int j=0;j<num;j++){
            cout<<j+1<<". "<<endl;
            cout<<"Question: "<<f_array[j].showquestion()<<endl;
            cout<<"\nAnswer: "<<f_array[j].showanswer()<<endl;
        }
        cout<<"\nDelete which no.flashcard: "<<endl;
        int d;
        cin<<d;
        for (j=0;j<num;j++){
            if(j+1 == d){
                delete f_array[j];
                cout<<"\nDelete successfully"<<endl;
                break;
            }
        }
    }

    void reviewcard(){
        for(int i=0;i<num;i++){

        }
    }

    void


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

