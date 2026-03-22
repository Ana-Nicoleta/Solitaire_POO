#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <random>
#include <cstring>
using namespace std;

class Player{
    const int id;
    string name;
    static long noPlayerCreated;
    int timesPlayed;
    long score;
    int* scores;
    float average;
    void copyScores(int timesPlayed, int* scores);
public:
    Player();
    Player(string,int,int*,long,float);
    ~Player();
    Player(const Player& obj);
    Player& operator=(const Player& obj);
    friend std::ostream& operator<<(std::ostream& out, const Player& obj);
    friend std::istream& operator>>(std::istream& in, Player& obj);
    int getID() const;
    string getName() const;
    long getNoPlayersCreated() const;
    long getScore()const;
    int getTimesPlayed() const;
    const int* getScores() const;
    float getAverage() const;
    void setName(string);
    void setAverage(float);
    void setScores(int*, int);
    void setNewScore(long score);
    void setScore(long score);
    float calcAverage(const int*, int);
};
long Player::noPlayerCreated=1;

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
    score=0;
}
Player::Player(string name, int timesPlayed, int* scores,long score, float average):id(noPlayerCreated++) {
    this->name=name;
    copyScores(timesPlayed, scores);
    this->average=average;
    this->score=score;
}
Player::Player(const Player& obj):id(noPlayerCreated++) {
    name=obj.name;
    copyScores(obj.timesPlayed, obj.scores);
    average=obj.average;
    score=obj.score;
}
Player::~Player() {
    delete[] scores;
}
Player& Player::operator=(const Player& obj) {
    if (this==&obj) return *this;
    name=obj.name;
    average=obj.average;
    score=obj.score;
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
long Player::getNoPlayersCreated() const {
    return noPlayerCreated;
}
long Player::getScore()const {
    return score;
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
void Player::setNewScore(long score) {
    this->scores[++this->timesPlayed]=score;
}

void Player::setScore(long score) {
    this->score=score;
}
std::istream& operator>>(std::istream& in, Player& obj) {
    cout<<"First write your name: ";
    string name;
    in>>name;
    obj.setName(name);
    cout<<"How many times have you played: ";
    int timesPlayed;
    cin>>timesPlayed;
    cout<<"Your previous scores: ";
    int* scores=new int[timesPlayed];
    for (int i=0;i<timesPlayed;i++) {
        cin>>scores[i];
    }
    obj.setScores(scores,timesPlayed);
    delete[] scores;
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
float Player::calcAverage(const int* scores, int timesPlayed) {
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
    static long noCardsCreated;
    string symbol;
    string rank;
    char* color;
    bool isFaceUp;
    static vector<string> order;
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

long Card::noCardsCreated=0;
vector<string> Card::order={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
Card::Card( string symbol,string rank,char* color, bool isFaceUp):id(++noCardsCreated){
    this->isFaceUp=isFaceUp;
    this->symbol=symbol;
    this->rank=rank;
    this->color=strcpy(new char[strlen(color)+1],color);
};
Card::Card():id(++noCardsCreated){
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
        if (strcmp(obj.getColor(),"R")==0 ){
            SetConsoleTextAttribute(hConsole, 12);
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
    return -1;
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
    Player player;

public:
    Game();
    ~Game();
    friend std::ostream& operator<<(std::ostream&, const Game&);
    bool moveWasteToFoundation(int);
    bool moveCardToFoundation(int, int);
    bool extractCard();
    void reversePiles();
    bool moveColumnToColumn(int , int ) ;
    bool moveMoreCards(int, int, int);
    bool moveWasteToColumn(int );
    bool moveFoundationToColumn(int ,int );
    void setPlayer(Player) ;
    void setScorePlayer(long score);
    float getAverageGame() const;
    Player getPlayer() const;
    bool finish();
    void reset() ;

};
Game::Game() {
    Card a;
    Deck deck(52);
    deck.shuffleDeck(deck);
    columnSize=new int[8];
    foundationSize=new int[5];
    for (int i = 1; i <= 7; i++) {
        tableau[i]=new Card[52];
        tableau[i][0]=a;
        for (int j = 1; j <= i; j++) {
            tableau[i][j]=deck.Draw();

            if (j == i) tableau[i][j].setIsFaceUp(true);
        }
        columnSize[i]=i;
    }
    pile.push_back(a);
    while (deck.isEmpty(deck)!=0) {
        pile.push_back(deck.Draw());
    }
    waste.push_back(a);
    for(int i=1;i<=4;i++) {
        foundationSize[i]=0;
        foundation[i]=new Card[14];
        foundation[i][0]=a;
    }
    player.setScore(0);
};

std::ostream& operator<<(std::ostream& out, const Game& obj) {
    out<<"Player: "<<obj.player.getName()<<"\t\t"<<"Score: "<<obj.player.getScore()<<endl;
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
    for (int i=1;i<=4;i++) {
        delete[] foundation[i];
    }
    delete[] foundation;
    for (int i=1;i<=7;i++) {
        delete[] tableau[i];
    }
    delete[] tableau;
    delete[] columnSize;
    delete[] foundationSize;
}
void Game::setPlayer(Player p) {
    this->player=p;
}

bool Game::moveWasteToFoundation(int f) {
    if (f<1 || f>4) return false;
    if (waste.size()==1) return false;
    if ((foundationSize[f]>0 && waste.back().getSymbol()==foundation[f][foundationSize[f]].getSymbol() &&
        waste.back().getIndexOrder()==1+foundation[f][foundationSize[f]].getIndexOrder()) || (foundationSize[f]==0 && waste.back().getRank()=="A")) {
        foundationSize[f]++;
        foundation[f][foundationSize[f]]=waste.back();
        waste.pop_back();
        player.setScore(player.getScore()+100);
        return true;
    }
    return false;
}



bool Game::moveCardToFoundation(int c, int f) {
    if (c<1 || c>7 || f<1 || f>4) return false;
    if ((foundationSize[f]==0 && tableau[c][columnSize[c]].getRank()=="A")||
        (tableau[c][columnSize[c]].getSymbol()==foundation[f][foundationSize[f]].getSymbol() &&
            tableau[c][columnSize[c]].getIndexOrder()==1+foundation[f][foundationSize[f]].getIndexOrder())) {
        foundationSize[f]++;
        foundation[f][foundationSize[f]]=tableau[c][columnSize[c]];
        columnSize[c]--;
        if (columnSize[c] > 0) {
            tableau[c][columnSize[c]].setIsFaceUp(true);
        }
        player.setScore(player.getScore()+150);
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
        while (waste.size() > 1) {
            Card topWaste = waste.back();
            topWaste.setIsFaceUp(false);
            pile.push_back(topWaste);
            waste.pop_back();
        }
    }
}
bool Game::moveColumnToColumn(int c1, int c2) {
    if (c1<1 || c1>7 || c2<1 || c2>7) return false;
    if (columnSize[c2]==0 && tableau[c1][columnSize[c1]].getRank()=="K"){
        columnSize[c2]++;
        tableau[c2][columnSize[c2]]=tableau[c1][columnSize[c1]];
        columnSize[c1]--;
        if (tableau[c1][columnSize[c1]].getIsFaceUp()==false && columnSize[c1] > 0) {
            tableau[c1][columnSize[c1]].setIsFaceUp(true);
        }
        player.setScore(player.getScore()+50);
        return true;
    }
    if (strcmp(tableau[c1][columnSize[c1]].getColor(),tableau[c2][columnSize[c2]].getColor())!=0 &&
        1+tableau[c1][columnSize[c1]].getIndexOrder() ==tableau[c2][columnSize[c2]].getIndexOrder()) {
        columnSize[c2]++;
        tableau[c2][columnSize[c2]]=tableau[c1][columnSize[c1]];
        columnSize[c1]--;
        if (tableau[c1][columnSize[c1]].getIsFaceUp()==false && columnSize[c1] > 0) {
            tableau[c1][columnSize[c1]].setIsFaceUp(true);
        }
        player.setScore(player.getScore()+50);
        return true;
    }
    return false;
}
bool Game::moveMoreCards(int c1, int index, int c2) {
     int multi=columnSize[c1]-index+1;
    if (c1<1 || c1>7 || c2<1 || c2>7) return false;
    if (index <= 0 || index > columnSize[c1]) return false;
    if (tableau[c1][index].getIsFaceUp()==false) return false;
    if ((columnSize[c2]==0 && tableau[c1][index].getRank()=="K")||(strcmp(tableau[c1][index].getColor(),tableau[c2][columnSize[c2]].getColor())!=0 &&
        tableau[c1][index].getIndexOrder()+1==tableau[c2][columnSize[c2]].getIndexOrder() )) {
        for (int i=index;i<=columnSize[c1];i++) {
            columnSize[c2]++;
            tableau[c2][columnSize[c2]]=tableau[c1][i];
        }
        columnSize[c1]=columnSize[c1]-(columnSize[c1]-index+1);
        if (tableau[c1][columnSize[c1]].getIsFaceUp()==false && columnSize[c1] > 0) {
            tableau[c1][columnSize[c1]].setIsFaceUp(true);
        }
        player.setScore(player.getScore()+multi*90);
        return true;
    }
    return false;
}
bool Game::moveWasteToColumn(int c) {
    if (c<1 || c>7) return false;
    if (waste.size()==1) return false;
    if (columnSize[c]==0 && waste.back().getRank()=="K") {
        columnSize[c]++;
        tableau[c][columnSize[c]]=waste.back();
        waste.pop_back();
        player.setScore(player.getScore()+80);
        return true;
    };
    if (strcmp(waste.back().getColor(),tableau[c][columnSize[c]].getColor())!=0 &&
        waste.back().getIndexOrder()+1==tableau[c][columnSize[c]].getIndexOrder()) {
        columnSize[c]++;
        tableau[c][columnSize[c]]=waste.back();
        waste.pop_back();
        player.setScore(player.getScore()+80);
        return true;
    }
    return false;
}
bool Game::moveFoundationToColumn(int f,int c) {
    if (c<1 || c>7 || f<1 || f>4) return false;
    if (foundationSize[f]==0) return false;
    if (columnSize[c]==0 && foundation[f][foundationSize[f]].getRank()!="K") return false;
    if (strcmp(foundation[f][foundationSize[f]].getColor(),tableau[c][columnSize[c]].getColor())!=0 &&
        foundation[f][foundationSize[f]].getIndexOrder()+1==tableau[c][columnSize[c]].getIndexOrder() ) {
        columnSize[c]++;
        tableau[c][columnSize[c]]=foundation[f][foundationSize[f]];
        foundationSize[f]--;
        player.setScore(player.getScore()+120);
        return true;
    }
    return false;
}
bool Game::finish() {
    int cnt=0;
    for (int i=1;i<=4;i++) {
        cnt+=foundationSize[i];
    }
    if (cnt==52)return true;
    return false;
}
void Game::reset() {
    Card a;
    for(int i=1;i<=4;i++) {
        foundationSize[i]=0;
        foundation[i][0]=a;
    }
    waste.clear();
    waste.push_back(a);
    pile.clear();
    pile.push_back(a);

    Deck deck(52);
    deck.shuffleDeck(deck);
    for (int i = 1; i <= 7; i++) {
        columnSize[i] = i;
        tableau[i][0] = a;
        for (int j = 1; j <= i; j++) {
            tableau[i][j] = deck.Draw();
            if (j == i) tableau[i][j].setIsFaceUp(true);
            else tableau[i][j].setIsFaceUp(false);
        }
    }

    while (deck.isEmpty(deck)!=0) {
        pile.push_back(deck.Draw());
    }
    player.setScore(0);

}
void Game::setScorePlayer(long score) {
    this->player.setNewScore(score);
    this->player.setAverage(this->player.calcAverage(this->player.getScores(),this->player.getTimesPlayed()));
}

float Game::getAverageGame() const {
    return player.getAverage();
}
Player Game::getPlayer()const {
    return player;
}

class Menu {
    Game solitaire;
    Player player;
public:
    Menu()=default;
    void run();
    void gameMenu();
};
void Menu::run() {
    while (true) {
        SetConsoleOutputCP(CP_UTF8);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"\u2660 \u2663 \u2665 \u2666 SOLITAIRE \u2660 \u2663 \u2665 \u2666"<<endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout<<"1 - rules\n";
        cout<<"2 - start the game\n";
        cout<<"0 - exit\n";
        cout<<"Option: ";

        int option;
        cin>>option;
        cin.ignore();

        switch (option) {
            case 0:
                cout<<"byeee! \u2663 \n";
                return;
            case 1:
                cout<<"Here are the rules for solitaire:\nClassic Solitaire (Klondike) involves arranging a 52-card deck into four foundation piles by suit (Ace to King) using a seven-column tableau. Build tableau columns down by alternating colors (e.g., red 6 on black 7), move Aces to foundations immediately, and fill empty spaces only with Kings.\n In this Solitaire, in console, you will have 6 options of moving the cards:\n- from waste to column\n- from waste to foundation\n- from foundation to column\n- from column to foundation\n- from column to column\n- multiple from one column to another.\nThis will be possible by writing , for example, when moving column to column, <1 2>, which will move the last card from the first column to the end of the second, if the card fits.\n\n"<<endl;
                break;
            case 2: {
                solitaire.reset();
                Player gamer;
                cin>>gamer;
                solitaire.setPlayer(gamer);
                cout<<"ready?"<<endl;
                cout<<"START"<<"\n\n";
                gameMenu();
                break;
            }
            default:
                cout<<"Invalid option"<<endl;
        }
    }
}
void Menu::gameMenu() {
    while (true) {
        cout<<solitaire<<"\n";
        cout<<"1 - Extract card from stock\n";
        cout<<"2 - Move from column to column\n";
        cout<<"3 - Move a card from waste to a column\n";
        cout<<"4 - Move a card from waste to a foundation\n";
        cout<<"5 - Move a card from a foundation to a column\n";
        cout<<"6 - Move a card from a column to a foundation\n";
        cout<<"7 - Move multiple cards from a column to another\n";
        cout<<"8 - Switch waste pile with stock pile (when stock is empty)\n";
        cout<<"0 - Exit\n";
        cout<<"Option: ";
        int option;
        cin>>option;
        cin.ignore();
        switch (option) {
            case 0:
                return;
            case 1: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 12);
                if (solitaire.extractCard()==false) cout<<"NO MORE CARDS IN THE STOCK PILE, TRY SWITCHING IT WITH THE WASTE PILE\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 2: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"Write <x y>, x and y from 1 to 7, where x is which column to take the card from, and y is in which column do you want to put it\n";
                cout<<"Move: ";
                int a,c;
                cin>>a>>c;
                SetConsoleTextAttribute(hConsole, 12);
                if (solitaire.moveColumnToColumn(a,c)==false) cout<<"THIS IS NOT A PROPER CARD\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 3: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"Write <x>, from 1 to 7, where x is which column ,from left to right, where you want the card to go\n";
                cout<<"Move: ";
                int c;
                cin>>c;
                SetConsoleTextAttribute(hConsole, 12);
                if (solitaire.moveWasteToColumn(c)==false) cout<<"THIS IS NOT A PROPER CARD\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 4: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"Write <x>, from 1 to 4, where x is which foundation, from left to right, where you want the card to go\n";
                cout<<"Move: ";
                int f;
                cin>>f;
                SetConsoleTextAttribute(hConsole, 12);
                if(solitaire.moveWasteToFoundation(f)==false) cout<<"THIS IS NOT A PROPER CARD\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 5: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"write <x y>, x from 1 to 4, y from 1 to 7, where x is which foundation to take the card from, and y is in which column do you want to put it\n";
                cout<<"Move: ";
                int f,c;
                cin>>f>>c;
                SetConsoleTextAttribute(hConsole, 12);
                if (solitaire.moveFoundationToColumn(f,c)==false) cout<<"THIS IS NOT A PROPER CARD\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 6: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"Write <x y>, x from 1 to 7, y from 1 to 4, where x is which column to take the card from, and y is in which foundation do you want to put it\n";
                cout<<"Move: ";
                int c,f;
                cin>>c>>f;
                SetConsoleTextAttribute(hConsole, 12);
                if (solitaire.moveCardToFoundation(c,f)==false) cout<<"THIS IS NOT A PROPER CARD\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 7: {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 14);
                cout<<"write <x y z>, x and z from 1 to 7, where x is the column you want to take the cards from, y is what index the first card is on (counting from top to bottom, starting with 1), and z the column in which to put them\n";
                cout<<"Move: ";
                int a,i,c;
                cin>>a>>i>>c;
                SetConsoleTextAttribute(hConsole, 12);
                if (solitaire.moveMoreCards(a,i,c)==false) cout<<"THIS IS NOT A PROPER CARD\n";
                SetConsoleTextAttribute(hConsole, 7);
                cout<<"\n";
                break;
            }
            case 8: {
                solitaire.reversePiles();
                break;
            }
            default:
                cout<<"invalid option\n";
        }
        if (solitaire.finish()==true) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleTextAttribute(hConsole, 13);
            cout<<"\u2666\u2666 YOU WON CONGRATULATIONS!! \u2666\u2666"<<"\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Your score is: "<<solitaire.getPlayer().getScore()<<endl;
            solitaire.setScorePlayer(solitaire.getPlayer().getScore());
            cout<<"Your average is:"<<solitaire.getAverageGame()<<endl;
            cout<<"\n\n";

            break;
        }
    }
}
int main() {
    Menu one;
    one.run();
};
