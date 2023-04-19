#include<bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

#define IS_TRUE(x) { if (!(x)) std::cerr << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }



// Forward declaration  
class rock_paper_scissor;



// Class symbol_rps
class Symbol_rps {
  private:
    char symbol;
    map<char,int> mp;
  public:
    Symbol_rps(char symbol_): symbol(symbol_) {
        mp['R']=0;
        mp['P']=1;
        mp['S']=2;
    };

    char get_symbol() {
        return this -> symbol;
    }

    void set_symbol(char s) {
        this -> symbol = s;
    }

    bool is_valid() {
        if (this -> symbol == 'R' || this -> symbol == 'P' || this -> symbol == 'S') {
            return true;
        }
        cerr << "INVALID SYMBOL\n";
        return false;
    }

    bool operator > (const Symbol_rps & ref) {
        return (mp[this->symbol]+2)%3 == mp[ref.symbol];
    }

    bool operator == (const Symbol_rps & ref) {
        return this -> symbol == ref.symbol;
    }
};


// Defining Player
class Player {
  private:
    int score;
    string name;
    void increment_score() {
        score++;
    };

  public:

    Player(string name_): name(name_),
    score(0) {}

    string set_name(string name_) {
        name = name_;
    }
    string get_name() {
        return name;
    }

    int get_score() {
        return score;
    }

    virtual Symbol_rps * move() = 0;

    friend rock_paper_scissor;

};

// rock_paper_scissor declaration

class rock_paper_scissor {
  private: 
    int num_rounds;
    Player * p1;
    Player * p2;

    void update_score_using_moves(Symbol_rps * p1_move, Symbol_rps * p2_move) {

        if ( * p1_move > * p2_move) {
            p1 -> increment_score();
        } else if ( * p1_move == * p2_move) {
            p1 -> increment_score();
            p2 -> increment_score();
        } else {
            p2 -> increment_score();
        }

    };
  public:
    rock_paper_scissor(Player * p1_, Player * p2_): p1(p1_),p2(p2_) {}

    void show_round_result() {
        cout << p1 -> get_name() << " : " << p1 -> get_score() <<
        " " << p2 -> get_name() << " : " <<
        p2 -> get_score() << "\n";
    }

    void display_result() {

        Player * winner = NULL;

        if (p1 -> get_score() > p2 -> get_score())
        winner = p1;
        else if (p1 -> get_score() < p2 -> get_score())
        winner = p2;
        if (winner)
        cout << winner -> get_name() << " WON\n";
        else
        cout << "Its a tie!!\n";

    }

    void play() {
        cout << "Enter number of rounds to play: ";
        cin >> num_rounds;
        while (num_rounds--) {

            Symbol_rps * p1_move = p1 -> move();
            Symbol_rps * p2_move = p2 -> move();

            update_score_using_moves(p1_move, p2_move);
            delete p1_move;
            delete p2_move;
            show_round_result();
        }
    }
    // Function to test score board 
    friend void test_update_score();
};

// Defining Human_rps

class Human_rps: public Player {
  public:
    static void display_instructions() {
        cout << "Enter only 'R' -> Rock\n"
             << "           'P'-> Paper\n"
             << "           'S'-> Scissor\n";
    }
    // virtual ~Human_rps () {}
    Human_rps(string name = "Human"): Player(name) {}

    Symbol_rps * move() {

        Symbol_rps * human_move = new Symbol_rps('x');
        do {
            char x;
            cout << this -> get_name() << " MOVE : ";
            cin >> x;
            human_move -> set_symbol(x);
        } while (!human_move -> is_valid());

        return human_move;
    }

};

// Defining Bot_rps

class Bot_rps: public Player {
  public:
    // virtual ~Bot_rps () {}
    Bot_rps(): Player("Computer") {}

    Symbol_rps * move() {

        Symbol_rps * bot_move = new Symbol_rps('x');

        int x = rng() % 3;
        if (x == 0) bot_move -> set_symbol('R');
        if (x == 1) bot_move -> set_symbol('P');
        if (x == 2) bot_move -> set_symbol('S');

        cout << this -> get_name() << " MOVE : " << bot_move -> get_symbol() << "\n";

        return bot_move;
    }
};


class test_player: public Player{
    public:
        test_player(): Player("TestPlayer") {}
        Symbol_rps *move() {

        }
};


void check_bot(int t = 100) {
    std::cout.setstate(std::ios_base::failbit);
    // check if generated output is either of 'R' 'P' 'S'
    Bot_rps bot = Bot_rps();
    while(t--){
        Symbol_rps* move = bot.move();
        IS_TRUE(move->is_valid());
    }
    cout.clear();
}

void test_update_score() {
    std::cout.setstate(std::ios_base::failbit);\
    Bot_rps bot1 = Bot_rps();
    Bot_rps bot2 = Bot_rps();
    rock_paper_scissor rps(&bot1,&bot2);

    vector<pair<Symbol_rps,Symbol_rps>> moves;
    moves.push_back({Symbol_rps('R') , Symbol_rps('P')});
    moves.push_back({Symbol_rps('R') , Symbol_rps('S')});
    moves.push_back({Symbol_rps('R') , Symbol_rps('R')});
    moves.push_back({Symbol_rps('P') , Symbol_rps('S')});
    moves.push_back({Symbol_rps('S') , Symbol_rps('S')});
    moves.push_back({Symbol_rps('P') , Symbol_rps('P')});
    moves.push_back({Symbol_rps('P') , Symbol_rps('S')});

    for(auto &x : moves){
        Symbol_rps * p1_move = &x.first;
        Symbol_rps * p2_move = &x.second;
        rps.update_score_using_moves(p1_move, p2_move);
    }
    IS_TRUE(bot1.get_score() == 4 && bot2.get_score() == 6)
    cout.clear();
}







int main() {
    // Unit Testing 
    test_update_score();
    check_bot();
    // Create a game object for rock-paper-scissor
    Human_rps p1 = Human_rps();
    Bot_rps p2 = Bot_rps();
    rock_paper_scissor rpc( & p1, & p2);
    Human_rps::display_instructions();
    rpc.play();
    rpc.display_result();
}