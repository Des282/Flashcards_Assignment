#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Flashcard {
    string question;
    string answer;
    int score;
public:
    Flashcard() {}
    Flashcard(string q, string a, int s) : question(q), answer(a), score(s) {}

    string getQuestion() {
        return question;
        }
    string getAnswer() {
        return answer;
        }
    int getScore() {
        return score;
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
        ofstream fileout(filename); // create or overwrite file
        if (fileout.is_open()) {
        for (int i = 0; i < num; i++) {
            fileout << card[i].getQuestion() << "|"
            << card[i].getAnswer() << "|"
            << card[i].getScore() << "\n";
            }
        }
        else{cout<<"Error creating file\n";}
        fileout.close();
        cout << "Flashcards successfully saved to " << filename << ".\n";
    }

    void loadFromFile(const string& filename1) {
        ifstream filein(filename1);
        string line;
        num = 0;  // Reset number of flashcards
        if(filein.is_open()){
            while (getline(filein, line)) {
                size_t pos1 = line.find('|');
                size_t pos2 = line.rfind('|');

                if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
                    cerr << "Skipping malformed line: " << line << endl;
                    continue;
                }

                string q = line.substr(0, pos1);
                string a = line.substr(pos1 + 1, pos2 - pos1 - 1);
                string scoreStr = line.substr(pos2 + 1);

            try {
                int s = stoi(scoreStr);
                card[num++] = Flashcard(q, a, s);
            } catch (exception& e) {
            cerr << "Invalid score in line: " << line << endl;
            }
        }
        }
        else{cout<<"Error opening load File."<<endl;}
        filein.close();
        cout << "Loaded " << num << " flashcard(s) from " << filename1 << ".\n";
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
            cout << "Invalid No.flashcard chosen\n";
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

