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

class SystemProcess {
public:
    int counter = 0;

    void updateScore(Flashcard a_card) {
        counter = counter + a_card.getScore();
    }

    int getScore() {
        return counter;
    }
};

class SystemManager {
public:
    Flashcard* card = new Flashcard[100];
    int num = 0;
    SystemProcess process;

    Flashcard addCard() {
        string q, a;
        int s;
        cin.ignore();
        cout << "Enter question: ";
        getline(cin, q);
        cout << "Enter answer: ";
        getline(cin, a);
        cout << "Enter score: ";
        cin >> s;
        return Flashcard(q, a, s);
    }

    void reviewCards(string a_name) {
        string response;
        process.counter = 0;

        for (int j = 0; j < num; j++) {
            cout << "Q" << j + 1 << ". " << card[j].getQuestion() << endl;
            cout << "Do you know the answer? (yes/no): ";
            cin >> response;

            if (response == "yes") {
                process.updateScore(card[j]);
                cout << a_name << "'s current score: " << process.getScore() << endl;
            } else if (response == "no") {
                cout << "You lose " << card[j].getScore() << " mark(s)." << endl;
            } else {
                cout << "Invalid response.\n";
            }
        }
        cout << "Final Score: " << process.getScore() << endl;
    }

    void SaveToFile(const string& filename) {
        ofstream out(filename); // create or overwrite file
        if (!out) {
        cerr << "Error creating file.\n";
        return;
        }
        for (int i = 0; i < num; i++) {
            out << card[i].getQuestion() << "|"
            << card[i].getAnswer() << "|"
            << card[i].getScore() << "\n";
        }
        out.close();
        cout << "Flashcards successfully saved to " << filename << ".\n";
}


    void loadFromFile(const string& filename) {
        ifstream filein(filename);
        string q, a;
        int s;
        string line;
        num = 0;

        while (getline(filein, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.rfind("|");
            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                q = line.substr(0, pos1);
                a = line.substr(pos1 + 1, pos2 - pos1 - 1);
                s = stoi(line.substr(pos2 + 1));
                card[num++] = Flashcard(q, a, s);
            }
        }
        filein.close();
        cout << "Cards done loaded.\n";
    }

    void DeleteCard() {
        for (int i = 0; i < num; i++) {
            cout << i + 1 << ". " << card[i].getQuestion() << " | " << card[i].getAnswer() << endl;
        }

        int chosen;
        cout << "Enter No.flashcard that want to delete: ";
        cin >> chosen;

        if (chosen >= 1 && chosen <= num) {
            for (int i = chosen - 1; i < num - 1; i++) {
                card[i] = card[i + 1];
            }
            num = num - 1;
            cout << "Card deleted.\n";
        } else {
            cout << "Invalid No.falshcard chosen.\n";
        }
    }

    void addCardToList() {
        num = num + 1;
        card[num] = addCard();
    }
};

class App {
public:
    SystemManager manager;

    void run() {
        int choice;
        string name;
        cout << "Enter your name: ";
        cin >> name;

        do {
            cout << "\n=== Digital Flashcard Menu ===" << endl;
            cout << "1. Add Flashcard\n2. Review Cards\n3. Delete Cards\n4. Save Cards\n5. Load Cards\n6. Exit\nChoice: ";
            cin >> choice;
            switch (choice) {
                case 1:{
                    manager.addCardToList();
                    break;
                }
                case 2:{
                    manager.reviewCards(name);
                    break;
                }
                case 3:{
                    manager.DeleteCard();
                    break;
                }
                case 4:{
                    manager.SaveToFile("Savedflashcards.txt");
                    break;
                }
                case 5:{
                    manager.loadFromFile("Loadflashcards.txt");
                    break;
                }
                case 6:{
                    cout << "Exiting program.\n";
                    break;
                }
                default:{
                    cout << "Invalid choice.\n";
                }
            }
        } while (choice != 6);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}
