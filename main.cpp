#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <random>
using namespace std;

class Player{
    const int id;
    string name;
    static double noPlayerCreated;
    int timesPlayed;
    int* scores;
    float average;
    void copyScores(int timesPlayed, int* scores);
public:
    Player();
    Player(string,int,int*,float);
    ~Player();
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    friend std::ostream& operator<<(std::ostream& out, const Player& obj);
    friend std::istream& operator>>(std::istream& in, Player& obj);
    int getID() const;
    string getName() const;
    double getNoPlayersCreated() const;
    int getTimesPlayed() const;
    const int* getScores() const;
    float getAverage() const;
    void setName(string);
    void setAverage(float);
    void setScores(int*, int);
    float calcAverage(int*, int);
};
double Player::noPlayerCreated=1;

void Player::copyScores(int timesPlayed, int* scores) {
    this->timesPlayed = timesPlayed;
    if (timesPlayed > 0) {
        this->scores = new int[timesPlayed];
        for (int i = 0; i < timesPlayed; i++)
            this->scores[i] = scores[i];
    } else {
        this->scores = nullptr;
    }
}
Player::Player():id(noPlayerCreated++) {
    name="N/A";
    timesPlayed=0;
    scores=nullptr;
    average=0.0;
}
Player::Player(string name, int timesPlayed, int* scores, float average):id(noPlayerCreated++) {
    this->name=name;
    copyScores(timesPlayed, scores);
    this->average=average;
}
Player::Player(const Player& obj):id(noPlayerCreated++) {
    name=obj.name;
    copyScores(obj.timesPlayed, obj.scores);
    average=obj.average;
}
Player::~Player() {
    delete[] scores;
}
Player& Player::operator=(const Player& obj) {
    if (this==&obj) return *this;
    name=obj.name;
    average=obj.average;
    delete[] scores;
    copyScores(obj.timesPlayed, obj.scores);
    return *this;
};
string Player::getName()const {
    return name;
}
int Player::getTimesPlayed() const {
    return timesPlayed;
}
float Player::getAverage() const {
    return average;
}
const int* Player::getScores() const {
    return scores;
}
int Player::getID() const {
    return id;
}
double Player::getNoPlayersCreated() const {
    return noPlayerCreated;
}

void Player::setName(string name) {
    this->name=name;
}
void Player::setAverage(float average) {
    this->average=average;
}
void Player::setScores(int* scores, int timesPlayed) {
    delete[] this->scores;
    copyScores(timesPlayed, scores);
}
std::istream& operator>>(std::istream& in, Player& obj) {
    cout<<"Enter player name: "<<endl;
    string name;
    in>>name;
    obj.setName(name);
    return in;
}
std::ostream& operator<<(std::ostream& out, const Player& obj) {
    out<<"Player name: "<<obj.name<<endl;
    out<<"Player ID: "<<obj.id<<endl;
    if (obj.scores!=nullptr) {
        out << "Number of times played: " << obj.timesPlayed <<endl;
        out<<"Scores: ";
        for (int i = 0; i < obj.timesPlayed; i++)
            out << obj.scores[i] << " ";
        out << '\n';
    } else {
        out << "Never played\n";
    }
    return out;
}
float Player::calcAverage(int* scores, int timesPlayed) {
    float average=0;
    if (scores!=nullptr) {
        for (int i=0;i<timesPlayed;i++) {
            average=average+scores[i];
        }
        average= average/timesPlayed;
        return average;
    }
    return 0;
}
class Card {
    const int id;
    static double noCardsCreated;
    string symbol;
    string rank;
    char* color;
    bool isFaceUp;
    const vector<string> order;
public:
    Card();
    Card(string,string,char*, bool);
    ~Card();
    Card(const Card&);
    Card& operator=(const Card& obj);
    friend std::ostream& operator<<(std::ostream& out, const Card& obj);
    const char* getColor() const;
    bool getIsFaceUp() const;
    string getSymbol() const ;
    string getRank() const ;
    void setIsFaceUp(bool isFaceUp);
    int getIndexOrder() const;
};

double Card::noCardsCreated=0;
Card::Card( string symbol,string rank,char* color, bool isFaceUp):id(++noCardsCreated),order({"A","2","3","4","5","6","7","8","9","10","J","Q","K"}){
    this->isFaceUp=isFaceUp;
    this->symbol=symbol;
    this->rank=rank;
    this->color=strcpy(new char[strlen(color)+1],color);
};
Card::Card():id(++noCardsCreated),order({"A","2","3","4","5","6","7","8","9","10","J","Q","K"}){
    isFaceUp=false;
    symbol="N/A";
    rank="N/A";
    color=strcpy(new char[4], "N/A");
}
Card::~Card() {
    delete [] color;
}
Card& Card::operator=(const Card& obj){
    if (this==&obj) return *this;
    delete[] color;

    isFaceUp=obj.isFaceUp;
    symbol=obj.symbol;
    rank=obj.rank;
    color=strcpy(new char[strlen(obj.color)+1],obj.color);
    return *this;
};
Card::Card(const Card& obj):id(++noCardsCreated){
    isFaceUp=obj.isFaceUp;
    symbol=obj.symbol;
    rank=obj.rank;
    color=strcpy(new char[strlen(obj.color)+1],obj.color);
}
std::ostream& operator<<(std::ostream& out, const Card& obj){
    if (obj.getRank()=="N/A") {
        out<<"[    ]";
    }
    else if (obj.getIsFaceUp()==false) {
        out<<"(----)";
    }
    else{
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleOutputCP(CP_UTF8);
        if (obj.getColor()[0]=='R') {
            SetConsoleTextAttribute(hConsole, 12);
            SetConsoleOutputCP(CP_UTF8);
            out<<"( "<<obj.getRank()<<obj.getSymbol()<<" )";
            SetConsoleTextAttribute(hConsole, 7);
        }
        else{
            out<<"( "<<obj.getRank()<<obj.getSymbol()<<" )";
        }
    }
    return out;
};
const char* Card::getColor() const {
    return color;
}
bool Card::getIsFaceUp() const {
    return isFaceUp;
}
string Card::getSymbol() const {
    return symbol;
}
string Card::getRank() const {
    return rank;
}
void Card::setIsFaceUp(bool isFaceUp) {
    this->isFaceUp=isFaceUp;
}
int Card::getIndexOrder() const {
    for (int i=0;i<13;i++) {
        if (order[i]==rank) return i;
    }
}
class Deck {
    int noCards;
    vector<Card> deck;
public:
    Deck();
    Deck(int noCards);
    Deck(const Deck& obj);
    Deck& operator=(const Deck& obj);
    ~Deck();
    friend std::ostream& operator<<(std::ostream& out, const Deck& obj);
    void shuffleDeck(Deck&);
    Card getCard(int) const;
    Card Draw();
    bool isEmpty(Deck&);

};
Deck::Deck() {
    noCards=0;
};
Deck::~Deck() {

}
Deck::Deck(int noCards){
    this->noCards= noCards;
    int startCard=(-noCards/4+13)+1;
    string symbol[]={"\u2660","\u2663","\u2665","\u2666"};
    for (int j=0;j<2;j++)
        for (int i=startCard;i<=13;i++) {
            if (i==startCard) {
                deck.push_back(Card(symbol[j],"A","B",false));
            }
            else if (i==11) {
                deck.push_back(Card(symbol[j],"J","B",false));
            }
            else if (i==12) {
                deck.push_back(Card(symbol[j],"Q","B",false));
            }
            else if (i==13) {
                deck.push_back(Card(symbol[j],"K","B",false));
            }
            else {
                deck.push_back(Card(symbol[j],to_string(i),"B",false));
            }
        }
    for (int j=2;j<4;j++)
        for (int i=startCard;i<=13;i++) {
            if (i==startCard) {
                deck.push_back(Card(symbol[j],"A","R",false));
            }
            else if (i==11) {
                deck.push_back(Card(symbol[j],"J","R",false));
            }
            else if (i==12) {
                deck.push_back(Card(symbol[j],"Q","R",false));
            }
            else if (i==13) {
                deck.push_back(Card(symbol[j],"K","R",false));
            }
            else {
                deck.push_back(Card(symbol[j],to_string(i),"R",false));
            }
        }

}
Deck::Deck(const Deck& obj) {
    noCards= obj.noCards;
    deck=obj.deck;
}
Deck& Deck::operator=(const Deck& obj) {
    if (this==&obj) return *this;
    noCards= obj.noCards;
    deck=obj.deck;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const Deck& obj) {
    out<<obj.noCards<<endl;
    for (int i=0;i<obj.deck.size();i++) {
        cout<<obj.deck[i]<<"  ";
    }
    return out;
}
void Deck:: shuffleDeck(Deck& obj) {
    random_device rnd;
    mt19937_64 gen(rnd());
    shuffle(obj.deck.begin(), obj.deck.end(), gen);
}
bool Deck:: isEmpty(Deck& obj) {
    if (obj.deck.size()==0) return 0;
    else return 1;
}
Card Deck::getCard(int i) const {
    return deck[i];
    }
Card Deck::Draw() {
        Card topCard = deck.back();
        deck.pop_back();
        return topCard;
}

class Game {
    vector<Card> pile;
    vector<Card> waste;
    Card** foundation=new Card*[5];
    Card** tableau=new Card*[8];
    int* columnSize;
    int* foundationSize;
    //Player player;
    Deck initDeck;
    int noCardsFaceUp;
public:
    Game();
    ~Game();
    friend std::ostream& operator<<(std::ostream&, const Game&);
    void goToFoundation();
    bool moveCardToFoundation(int, int);
    bool extractCard();
    void reversePiles();
    bool moveColumnToColumn(int , int ) ;
    bool moveMoreCards(int, int, int);
    bool moveWasteToColumn(int );
    bool moveFoundationToColumn(int f,int c);

};
Game::Game() {
    Card a;
    Deck deck(52);
    initDeck=deck;
    initDeck.shuffleDeck(initDeck);
    columnSize=new int[8];
    foundationSize=new int[5];
    for (int i = 1; i <= 7; i++) {
        tableau[i]=new Card[52];
        tableau[i][0]=a;
        for (int j = 1; j <= i; j++) {
            tableau[i][j]=initDeck.Draw();

            if (j == i) tableau[i][j].setIsFaceUp(true);
        }
        columnSize[i]=i;
    }
    while (initDeck.isEmpty(initDeck)!=0) {
        pile.push_back(initDeck.Draw());
    }
    waste.push_back(a);
    for(int i=1;i<=4;i++) {
        foundationSize[i]=0;
        foundation[i]=new Card[13];
        foundation[i][0]=a;
    }
    noCardsFaceUp=7;
};

std::ostream& operator<<(std::ostream& out, const Game& obj) {
    out<<"Stock\tWaste\tFound.1\tFound.2\tFound.3\tFound.4"<<endl;
    out<<obj.pile.back()<<"\t"<<obj.waste.back()<<"\t";
    for (int i = 1; i <= 4; i++) {
        out<<obj.foundation[i][obj.foundationSize[i]]<<"\t";
    }
    out<<endl;
    out << "\n\nCol 1\tCol 2\tCol 3\tCol 4\tCol 5\tCol 6\tCol 7\n";
    out << "-------------------------------------------------------\n";
    int maxSize = 0;
    for (int i = 1; i <= 7; i++) {
        if (obj.columnSize[i] > maxSize) maxSize = obj.columnSize[i];
    }
    for (int j=1;j<=maxSize;j++) {
        for (int i=1;i<=7;i++) {
            if (j<=obj.columnSize[i]) {
                out<<obj.tableau[i][j];
            }
            out<<"\t";
        }
        out<<endl;
    }
    return out;
}
Game::~Game() {
    delete[] foundation;
    delete[] tableau;
    delete[] columnSize;
    delete[] foundationSize;
}
void Game::goToFoundation() {
    if (waste.size()>1) {
        for (int i=1;i<=4;i++) {
            if (foundationSize[i]>0) {
                if (waste.back().getSymbol()==foundation[i][foundationSize[i]].getSymbol() &&
                    waste.back().getIndexOrder()==1+foundation[i][foundationSize[i]].getIndexOrder()) {
                    foundationSize[i]++;
                    waste.back().setIsFaceUp(true);
                    foundation[i][foundationSize[i]]=waste.back();
                    waste.pop_back();
                    noCardsFaceUp++;
                }
            }
            else {
                if (waste.back().getRank()=="A") {
                    foundationSize[i]++;
                    waste.back().setIsFaceUp(true);
                    foundation[i][foundationSize[i]]=waste.back();
                    waste.pop_back();
                    noCardsFaceUp++;
                }
            }
        }
    }
}
bool Game::moveCardToFoundation(int column, int found) {
    if ((foundationSize[found]==0 && tableau[column][columnSize[column]].getRank()=="A")||
        (tableau[column][columnSize[column]].getSymbol()==foundation[found][foundationSize[found]].getSymbol() &&
            tableau[column][columnSize[column]].getIndexOrder()==1+foundation[found][foundationSize[found]].getIndexOrder())) {
        foundationSize[found]++;
        foundation[found][foundationSize[found]]=tableau[column][columnSize[column]];
        columnSize[column]--;
        tableau[column][columnSize[column]].setIsFaceUp(true);
        noCardsFaceUp++;
        return true;
    }
    else return false;
}
bool Game::extractCard() {
    if (pile.size()>1) {
        waste.push_back(pile.back());
        waste.back().setIsFaceUp(true);
        pile.pop_back();
        return true;
    }
    return false;
}
void Game::reversePiles() {
    if (pile.size()==1) {
        for (int i=1;i<waste.size();i++) {
            waste[i].setIsFaceUp(false);
            pile.push_back(waste[i]);
            waste.pop_back();
        }
    }
}
bool Game::moveColumnToColumn(int c1, int c2) {
    if (columnSize[c2]==0 && tableau[c1][columnSize[c1]].getRank()!="K") return false;
    if (tableau[c1][columnSize[c1]].getColor()!=tableau[c2][columnSize[c2]].getColor() &&
        1+tableau[c1][columnSize[c1]].getIndexOrder() ==tableau[c2][columnSize[c2]].getIndexOrder()) {
        columnSize[c2]++;
        tableau[c2][columnSize[c2]]=tableau[c1][columnSize[c1]];
        columnSize[c1]--;
        if (tableau[c1][columnSize[c1]].getIsFaceUp()==false) {
            tableau[c1][columnSize[c1]].setIsFaceUp(true);
            noCardsFaceUp++;
        }
        return true;
    }
    return false;
}
bool Game::moveMoreCards(int c1, int index, int c2) {
    if (index>columnSize[c1]) return false;
    if (tableau[c1][index].getColor()!=tableau[c2][columnSize[c2]].getColor() &&
        tableau[c1][index].getIndexOrder()+1==tableau[c2][columnSize[c2]].getIndexOrder() ) {
        for (int i=index;i<=columnSize[c1];i++) {
            columnSize[c2]++;
            tableau[c2][columnSize[c2]]=tableau[c1][i];
        }
        columnSize[c1]=columnSize[c1]-(columnSize[c1]-index+1);
        if (tableau[c1][columnSize[c1]].getIsFaceUp()==false) {
            tableau[c1][columnSize[c1]].setIsFaceUp(true);
            noCardsFaceUp++;
        }
        return true;
    }
    return false;
}
bool Game::moveWasteToColumn(int c) {
    if (waste.size()==1) return false;
    if (columnSize[c]==0 && waste.back().getRank()!="K") return false;
    if (waste.back().getColor()!=tableau[c][columnSize[c]].getColor() &&
        waste.back().getIndexOrder()+1==tableau[c][columnSize[c]].getIndexOrder()) {
        columnSize[c]++;
        tableau[c][columnSize[c]]=waste.back();
        waste.pop_back();
        noCardsFaceUp++;
        return true;
    }
    return false;
}
bool Game::moveFoundationToColumn(int f,int c) {
    if (foundationSize[f]==0) return false;
    if (columnSize[c]==0 && foundation[f][foundationSize[f]].getRank()!="K") return false;
    if (foundation[f][foundationSize[f]].getColor()!=tableau[c][columnSize[c]].getColor() &&
        foundation[f][foundationSize[f]].getIndexOrder()+1==tableau[c][columnSize[c]].getIndexOrder() ) {
        columnSize[c]++;
        tableau[c][columnSize[c]]=foundation[f][foundationSize[f]];
        foundationSize[f]--;
        return true;
    }
    return false;
}

class Menu {
    Game solitair;
    Player player;
};
int main() {
    Card a("\u2665","K","R",true),b("\u2660","Q","B",true);
    Card c=b;
    Deck d(36),f(52);
    d.shuffleDeck(d);
    //cout<<d;
    Game g;
    cout<<g;
    Player one;
    cin>>one;
};
