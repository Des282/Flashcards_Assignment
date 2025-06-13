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
    int baseScore;

    Flashcard(string q = "", string a = "", int s = 1)
        : question(q), answer(a), baseScore(s) {}

    void display() const {
        cout << "Q: " << question << endl;
    }
};

class UserProgress {
    map<string, int> difficultyScore;
    map<string, int> flashcardScores;

public:
    void updateScore(const string& question, bool remembered, int baseScore) {
        if (!remembered) {
            difficultyScore[question]++;
            flashcardScores[question] = max(0, flashcardScores[question] - baseScore);
        } else {
            if (difficultyScore[question] > 0)
                difficultyScore[question]--;
            flashcardScores[question] += baseScore;
        }
    }

    int getDifficulty(const string& question) const {
        auto it = difficultyScore.find(question);
        return it != difficultyScore.end() ? it->second : 0;
    }

    int getFlashcardScore(const string& question) const {
        auto it = flashcardScores.find(question);
        return it != flashcardScores.end() ? it->second : 0;
    }
};

class FlashcardManager {
    vector<Flashcard> cards;
    UserProgress progress;

public:
    void addCard(const Flashcard& card) {
        cards.push_back(card);
    }

    void deleteCard() {
        if (cards.empty()) {
            cout << "No flashcards to delete.\n";
            return;
        }
        for (size_t i = 0; i < cards.size(); ++i) {
            cout << i + 1 << ". " << cards[i].question << " | " << cards[i].answer << endl;
        }
        int choice;
        cout << "Enter the number of the card to delete: ";
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= (int)cards.size()) {
            cards.erase(cards.begin() + choice - 1);
            cout << "Card deleted.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

    void reviewCards(const string& userName) {
        if (cards.empty()) {
            cout << "No cards to review.\n";
            return;
        }

        vector<Flashcard> sortedCards = cards;
        sort(sortedCards.begin(), sortedCards.end(), [this](const Flashcard& a, const Flashcard& b) {
            return progress.getDifficulty(a.question) > progress.getDifficulty(b.question);
        });

        int totalScore = 0;
        for (auto& card : sortedCards) {
            int reps = 1 + min(3, progress.getDifficulty(card.question));
            for (int i = 0; i < reps; ++i) {
                card.display();
                cout << "Do you remember the answer? (yes/no): ";
                string response;
                getline(cin, response);

                bool remembered = (response == "yes" || response == "Yes");
                if (!remembered) {
                    cout << "Answer: " << card.answer << endl;
                }

                progress.updateScore(card.question, remembered, card.baseScore);
                cout << "Score for this flashcard: " << progress.getFlashcardScore(card.question) << "\n";

                if (remembered)
                    totalScore += card.baseScore;
            }
        }
        cout << userName << "'s final score: " << totalScore << endl;
    }

    void saveToFile(const string& filename) {
        ofstream out(filename);
        if (!out) {
            cout << "Error opening file for saving.\n";
            return;
        }
        for (auto& card : cards) {
            out << card.question << "|" << card.answer << "|" << card.baseScore << "\n";
        }
        cout << "Flashcards saved to " << filename << ".\n";
    }

    void loadFromFile(const string& filename) {
        ifstream in(filename);
        if (!in) {
            cout << "Error opening file for loading.\n";
            return;
        }
        cards.clear();
        string line;
        while (getline(in, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.rfind('|');
            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) {
                cout << "Skipping malformed line: " << line << endl;
                continue;
            }
            string q = line.substr(0, pos1);
            string a = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int s = stoi(line.substr(pos2 + 1));
            cards.emplace_back(q, a, s);
        }
        cout << "Loaded " << cards.size() << " flashcard(s).\n";
    }
};

class App {
    FlashcardManager manager;

    void addCard() {
        string q, a;
        int s;
        cin.ignore();
        cout << "Enter question: ";
        getline(cin, q);
        cout << "Enter answer: ";
        getline(cin, a);
        cout << "Enter score (1-10): ";
        cin >> s;
        cin.ignore();
        manager.addCard(Flashcard(q, a, s));
        cout << "Flashcard added.\n";
    }

public:
    void run() {
        int choice;
        string name;
        cout << "Enter your name: ";
        getline(cin, name);

        do {
            cout << "\n==== Digital Flashcard Menu ====\n";
            cout << "1. Add Flashcard\n2. Review Cards\n3. Delete Flashcard\n4. Save Cards\n5. Load Cards\n6. Exit\nEnter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: addCard(); break;
                case 2: manager.reviewCards(name); break;
                case 3: manager.deleteCard(); break;
                case 4: manager.saveToFile("flashcards.txt"); break;
                case 5: manager.loadFromFile("flashcards.txt"); break;
                case 6: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice.\n"; break;
            }
        } while (choice != 6);
    }
};

int main() {
    App app;
    app.run();
    return 0;
}
