#include <iostream>
#include <string>

using namespace std;

// COLORS
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";

// TO UPPER
char myToUpper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

// RANDOM
class SimpleRandom {
private:
    unsigned int seed;

public:
    SimpleRandom() {
        seed = 123456789;
    }

    int getRandom(int min, int max) {
        seed = seed * 1103515245 + 12345;
        unsigned int r = (seed / 65536) % 32768;
        return min + (r % (max - min + 1));
    }
};

// PLAYER
class Player {
protected:
    string name;
    int score;

public:
    Player(string n) : name(n), score(0) {}

    virtual char makeChoice() = 0;

    string getName() { return name; }
    int getScore() { return score; }

    void inc() { score++; }
    void reset() { score = 0; }
};

// HUMAN
class Human : public Player {
public:
    Human() : Player("You") {}

    char makeChoice() override {
        string in;
        char c;

        while (true) {
            cout << BLUE << "Your move (R/P/S): " << RESET;
            cin >> in;

            if (in.size() == 1) {
                c = myToUpper(in[0]);
                if (c == 'R' || c == 'P' || c == 'S')
                    return c;
            }

            cout << RED << "Invalid input!" << RESET<<endl;
        }
    }
};

// COMPUTER
class Computer : public Player {
public:
    SimpleRandom rnd;
    int level;

    Computer(int l) : Player("Computer"), level(l) {}

    char makeChoice() override {

        int r = rnd.getRandom(0, 2);

        if (level == 1) return 'R'; // EASY
        if (level == 2) {
            if (r == 0) return 'R';
            if (r == 1) return 'P';
            return 'S';
        }
        if (level == 3) {
            if (r == 0) return 'P';
            if (r == 1) return 'S';
            return 'R';
        }

        return 'R';
    }
};

// GAME
class Game {
private:
    Human human;
    Computer* comp;
    int streak;

    int win(char h, char c) {
        if (h == c) return 0;

        if ((h == 'R' && c == 'S') ||
            (h == 'P' && c == 'R') ||
            (h == 'S' && c == 'P'))
            return 1;

        return -1;
    }

public:
    Game() : comp(nullptr), streak(0) {}

    void setLevel(int l) {
        if (comp) delete comp;
        comp = new Computer(l);
    }

    void play() {

        human.reset();
        comp->reset();
        streak = 0;

        cout << "GAME STARTED!" << endl;

        while (true) {

            char h = human.makeChoice();
            char c = comp->makeChoice();
            cout << endl;
            cout << "You: " << h 
                << " | Computer: " << c << endl;

            int r = win(h, c);

            if (r == 0) {
                cout << GREEN << "Tie → counted as WIN!" << RESET << endl;
                r = 1;
            }

            if (r == 1) {

                human.inc();
                streak++;

                cout << GREEN << "You win this round!" << RESET<<endl;

                //BONUS
                if (streak % 2 == 0) {
                    human.inc();
                    cout << YELLOW
                        << "BONUS +1 (Streak = "
                        << streak << ")\n"
                        << RESET;
                }

                if (human.getScore() >= 5) {
                    cout << GREEN
                        << "YOU WON THE GAME!"
                        << RESET<<endl;
                    break;
                }
            }
            else {

                comp->inc();
                streak = 0;

                cout << RED << "Computer wins round" << RESET<<endl;

                if (comp->getScore() >= 5) {
                    cout << RED
                        << "COMPUTER WON THE GAME!"
                        << RESET<<endl;
                    break;
                }
            }

            cout << BLUE
                << "Score → You: " << human.getScore()
                << " | Computer: " << comp->getScore()
                << RESET<<endl;
        }
    }
};


int main() {

    Game g;
    string input;

    while (true) {

        cout << "====================="<<endl;
        cout << "1. EASY" << endl;
        cout << "2. MEDIUM" << endl;
        cout << "3.HARD" << endl;
        cout<<"4.EXIT"<<endl;
        cout << "Choose level: "<<endl;
        cin >> input;

        if (input == "4") {
            cout << "Goodbye!"<<endl;
            break;
        }

        int level = input[0] - '0';

        g.setLevel(level);

        g.play();

        cout << endl;
        cout << "Do you want to play again? (Y/N): "<<endl;
        char again;
        cin >> again;

        again = myToUpper(again);

        if (again != 'Y') {
            cout << "Thanks for playing!"<<endl;
            break;
        }
    }

    return 0;
}