DIPAL KRANTI
(dkranti@student.ysu.edu)
SANDESH RAI
(srai23@student.ysu.edu)


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iterator>
#include <map>
#include <utility>
using namespace std;

struct Card {
    string value;
    string suit;
};

string printCard(Card c) {
    return (c.value + c.suit);
}

struct Deck {
    int currentCard = 0;
    Card card[52];
};

Deck create_deck() {
    const int NUMCARDS = 52;
    const int CARDSIZE = 2;
    Deck deck;
    char suits[] = {'C', 'D', 'H', 'S'};
    char cardValues[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    int count = 0;
    Card current;
    for (int n = 0; n < 4; n++) {
        for (int m = 0; m < 13; m++) {
            current.suit = suits[n];
            current.value = cardValues[m];
            deck.card[count] = current;
            count++;
        }
    }
    if (count == 52) {
        cout << "Deck size OK..." << endl;
    } else {
        cout << "Deck size: " << count << ", ERROR...exiting." << endl;
        exit(-1);
    }
    return deck;
}

struct Hand {
    string owner;
    int numCards = 0;
    Card card[12];
};

Hand createHand(string owner) {
    Hand h;
    h.owner = owner;
    return h;
}

void printHand(Hand h) {
    string s;
    cout << "\n" << h.owner << "'s hand:";
    for (int i = 0; i < h.numCards; i++) {
        s += (" " + printCard(h.card[i]));
    }
    cout << s << endl;
}

void printDealerHand(Hand h, bool hideFirst = true) {
    string s = "\nDealer's hand:";
    if (hideFirst) {
        s += " ?? ";
        for (int i = 1; i < h.numCards; i++) {
            s += " " + printCard(h.card[i]);
        }
    } else {
        for (int i = 0; i < h.numCards; i++) {
            s += " " + printCard(h.card[i]);
        }
    }
    cout << s << endl;
}

Hand addCard(Hand h, Card c) {
    if (h.numCards < 12) {
        h.card[h.numCards] = c;
        h.numCards++;
    }
    return h;
}

Hand dealCard(Hand h, Deck &d) {
    if (d.currentCard < 52) {
        h = addCard(h, d.card[d.currentCard]);
        d.currentCard++; 
    } else {
        cout << "No more cards in the deck!" << endl;
    }
    return h;
}

Card suitReplace(Card c) {
    if (c.suit == "S") {
        c.suit = "♠";
    } else if (c.suit == "H") {
        c.suit = "♥";
    } else if (c.suit == "C") {
        c.suit = "♣";
    } else if (c.suit == "D") {
        c.suit = "♦";
    } else {
        cout << "ERROR: invalid suit value in card: " << c.value << c.suit << endl;
    }
    return c;
}

int eval(Hand h) {
    int score = 0;
    int numAces = 0;

    map<string, int> cardMap = {
        {"A", 11},
        {"K", 10},
        {"Q", 10},
        {"J", 10},
        {"T", 10},
        {"9", 9},
        {"8", 8},
        {"7", 7},
        {"6", 6},
        {"5", 5},
        {"4", 4},
        {"3", 3},
        {"2", 2}
    };
    for (int n = 0; n < h.numCards; n++) {
        if (h.card[n].value == "A") {
            numAces++;
        } else {
            auto search = cardMap.find(h.card[n].value);
            if (search != cardMap.end()) {
                score += search->second;
            }
        }
    }
    for (int i = 0; i < numAces; i++) {
        if (score + 11 <= 21) {
            score += 11;
        } else {
            score += 1;
        }
    }

    return score;
}

void printDeck(Deck d) {
    for (int i = 0; i < 52; i++) {
        cout << d.card[i].value << d.card[i].suit;
        if (i != 51) { cout << ','; }
    }
    cout << endl;
    return;
}

Deck shuffleDeck(Deck d) {
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = d.card[i];
        d.card[i] = d.card[j];
        d.card[j] = temp;
    }

    d.currentCard = 0;     return d;
}

bool hasBlackjack(Hand h) {
    return (h.numCards == 2 && eval(h) == 21);
}

Hand playerTurn(Hand playerHand, Deck &deck) {
    char choice;
    while (eval(playerHand) < 21) {
        cout << "\n" << playerHand.owner << ", your score is " << eval(playerHand);
        cout << "\nWould you like to (H)it or (S)tand? ";
        cin >> choice;

        choice = toupper(choice); 

        if (choice == 'H') {
            playerHand = dealCard(playerHand, deck);
            printHand(playerHand);
        } else if (choice == 'S') {
            break;
        } else {
            cout << "Invalid input. Please enter 'H' to hit or 'S' to stand." << endl;
        }
    }
    return playerHand;
}

Hand dealerTurn(Hand dealerHand, Deck &deck) {
    cout << "\nDealer's turn:" << endl;
    printDealerHand(dealerHand, false);  

    while (eval(dealerHand) <= 16) {
        dealerHand = dealCard(dealerHand, deck);
        cout << "\nDealer hits:" << endl;
        printDealerHand(dealerHand, false);
    }

    return dealerHand;
}

void determineWinner(Hand playerHand, Hand dealerHand, int &playerWins, int &dealerWins, int &ties) {
    int playerScore = eval(playerHand);
    int dealerScore = eval(dealerHand);

    cout << "\nFinal scores:" << endl;
    cout << playerHand.owner << ": " << playerScore << endl;
    cout << "Dealer: " << dealerScore << endl;

    if (playerScore > 21) {
        cout << playerHand.owner << " busts! Dealer wins!" << endl;
        dealerWins++;
    } else if (dealerScore > 21) {
        cout << "Dealer busts! " << playerHand.owner << " wins!" << endl;
        playerWins++;
    } else if (playerScore > dealerScore) {
        cout << playerHand.owner << " wins!" << endl;
        playerWins++;
    } else if (dealerScore > playerScore) {
        cout << "Dealer wins!" << endl;
        dealerWins++;
    } else {
        cout << "It's a tie!" << endl;
        ties++;
    }
}

int main() {
    int playerWins = 0, dealerWins = 0, ties = 0;
    char playAgain;

    do {
        Deck deck = create_deck();
        for (int i = 0; i < 52; i++) {
            deck.card[i] = suitReplace(deck.card[i]);
        }
        deck = shuffleDeck(deck);

        Hand dealerHand = createHand("Dealer");
        Hand playerHand = createHand("Player 1");
        playerHand = dealCard(playerHand, deck);
        dealerHand = dealCard(dealerHand, deck);
        playerHand = dealCard(playerHand, deck);
        dealerHand = dealCard(dealerHand, deck);

        printHand(playerHand);
        printDealerHand(dealerHand);
        bool playerBlackjack = hasBlackjack(playerHand);
        bool dealerBlackjack = hasBlackjack(dealerHand);

        if (playerBlackjack || dealerBlackjack) {
            cout << "\nBlackjack!" << endl;
            printDealerHand(dealerHand, false);  

            if (playerBlackjack && dealerBlackjack) {
                cout << "Both have Blackjack! Push!" << endl;
                ties++;
            } else if (dealerBlackjack) {
                cout << "Dealer has Blackjack! Dealer wins!" << endl;
                dealerWins++;
            } else {
                cout << playerHand.owner << " has Blackjack! " << playerHand.owner << " wins!" << endl;
                playerWins++;
            }
        } else {
            playerHand = playerTurn(playerHand, deck);
            dealerHand = dealerTurn(dealerHand, deck);
            determineWinner(playerHand, dealerHand, playerWins, dealerWins, ties);
        }

        cout << "\nScoreboard: " << endl;
        cout << "Player Wins: " << playerWins << endl;
        cout << "Dealer Wins: " << dealerWins << endl;
        cout << "Ties: " << ties << endl;

        cout << "\nWould you like to play again? (Y/N): ";
        cin >> playAgain;
        playAgain = toupper(playAgain); 
    } while (playAgain == 'Y');

    cout << "Thanks for playing!" << endl;

    return 0;
}