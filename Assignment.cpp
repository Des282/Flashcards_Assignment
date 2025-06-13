#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

class Flashcard {
public:
    string question;
    string answer;

    Flashcard(string q = "", string a = "") : question(q), answer(a) {}

    void display() const {
        cout << "Q: " << question << endl;
    }
};

class UserProgress {
public:
    map<string, int> difficultyScore; // higher = more difficult
    int totalScore = 0;

    void updateScore(const string& question, bool remembered) {
        if (!remembered) {
            difficultyScore[question]++;
            totalScore -= 1;
        }
        else {
            if (difficultyScore[question] > 0)
                difficultyScore[question]--;
            totalScore += 1;
        }
    }

    int getScore(const string& question) const {
        auto it = difficultyScore.find(question);
        return it != difficultyScore.end() ? it->second : 0;
    }

    int getTotalScore() const {
        return totalScore;
    }
};

class FlashcardManager {
private:
    vector<Flashcard> cards;
    UserProgress progress;

public:
    void addCard(const Flashcard& card) {
        cards.push_back(card);
    }

    void reviewCards() {
        if (cards.empty()) {
            cout << "No cards to review.\n";
            return;
        }

        // Sort by difficulty descending
        sort(cards.begin(), cards.end(), [this](const Flashcard& a, const Flashcard& b) {
            return progress.getScore(a.question) > progress.getScore(b.question);
        });

        for (auto& card : cards) {
            card.display();
            cout << "Do you remember the answer? (yes/no): ";
            string response;
            getline(cin, response);

            bool remembered = (response == "yes" || response == "Yes");
            if (!remembered) cout << "Answer: " << card.answer << endl;

            progress.updateScore(card.question, remembered);
            cout << "Current Score: " << progress.getTotalScore() << "\n";
        }
    }

    void saveToFile(const string& filename) {
        ofstream out(filename);
        for (auto& card : cards)
            out << card.question << "|" << card.answer << endl;
        out.close();
        cout << "Cards saved.\n";
    }

    void loadFromFile(const string& filename) {
        cards.clear();
        ifstream in(filename);
        string line;
        while (getline(in, line)) {
            size_t sep = line.find('|');
            if (sep != string::npos) {
                string q = line.substr(0, sep);
                string a = line.substr(sep + 1);
                cards.emplace_back(q, a);
            }
        }
        in.close();
        cout << "Cards loaded.\n";
    }
};

class App {
    FlashcardManager manager;

public:
    void run() {
        int choice;
        do {
            cout << "\n==== Digital Flashcard Menu ====" << endl;
            cout << "1. Add Flashcard\n2. Review Cards\n3. Save Cards\n4. Load Cards\n5. Exit\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: addCard(); break;
                case 2: manager.reviewCards(); break;
                case 3: manager.saveToFile("flashcards.txt"); break;
                case 4: manager.loadFromFile("flashcards.txt"); break;
                case 5: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice.\n"; break;
            }
        } while (choice != 5);
    }

    void addCard() {
        string q, a;
        cout << "Enter question: ";
        getline(cin, q);
        cout << "Enter answer: ";
        getline(cin, a);
        manager.addCard(Flashcard(q, a));
        cout << "Flashcard added.\n";
    }
};

int main() {
    App app;
    app.run();
    return 0;
}
