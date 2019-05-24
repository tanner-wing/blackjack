/// @author Tanner Wing
/// @file blackjack.cpp
/// @version 2019-05-09
/// @brief This is a Blackjack card game.
/// @note So far, this program took me 8 hours to develop & debug.


#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

typedef unsigned int uint;

const uint DECK_SIZE = 52,
           AMOUNT_VALUES = 13,
           AMOUNT_SUITS = 4;

struct PlayingCard;
class  Deck;

struct PlayingCard
{
    string value = "";
    char   suit = '\0';
    uint   intValue = 0;
};

class Deck      // Class definition.
{               // Place variables and function prototypes with access levels here.
public:
    Deck();
    void            Shuffle();
    PlayingCard     GetNextCard();
//  int             CardCount();

private:
    PlayingCard     cards[DECK_SIZE];
    int             currentCard = 0;
    void            SwapCards(int, int);
};

// Out-of-line class member function definitions
Deck::Deck()
{
    currentCard = 0;

    uint index = 0;

    for (int suit = 0; suit < AMOUNT_SUITS; suit++)     // AMOUNT_SUITS = 4
    {
        for (int value = 0; value < AMOUNT_VALUES; value++)     // AMOUNT_VALUES = 13
        {
            switch (suit)
            {
                case 0: cards[index].suit = 'S';   break;
                case 1: cards[index].suit = 'C';   break;
                case 2: cards[index].suit = 'D';   break;
                case 3: cards[index].suit = 'H';   break;
                default:    break;
            }
            switch (value)
            {
                case 0: cards[index].value = "2";
                        cards[index].intValue = 2;  break;
                case 1: cards[index].value = "3";
                        cards[index].intValue = 3;  break;
                case 2: cards[index].value = "4";
                        cards[index].intValue = 4;  break;
                case 3: cards[index].value = "5";
                        cards[index].intValue = 5;  break;
                case 4: cards[index].value = "6";
                        cards[index].intValue = 6;  break;
                case 5: cards[index].value = "7";
                        cards[index].intValue = 7;  break;
                case 6: cards[index].value = "8";
                        cards[index].intValue = 8;  break;
                case 7: cards[index].value = "9";
                        cards[index].intValue = 9;  break;
                case 8: cards[index].value = "10";
                        cards[index].intValue = 10; break;
                case 9: cards[index].value = "J";
                        cards[index].intValue = 10; break;
                case 10: cards[index].value = "Q";
                         cards[index].intValue = 10; break;
                case 11: cards[index].value = "K";
                         cards[index].intValue = 10; break;
                case 12: cards[index].value = "A";
                         cards[index].intValue = 11; break;
                default:    break;
            }
            index++;
        }
    }
}

void Deck::Shuffle()
{
    currentCard = 0;

    for (int i = 0; i < DECK_SIZE; i++)
    {
        SwapCards(i, rand() % 52);
    }
}

PlayingCard Deck::GetNextCard()
{
    PlayingCard nextCard;

    if (currentCard < DECK_SIZE)
    {
        nextCard.value = cards[currentCard].value;
        nextCard.suit = cards[currentCard].suit;
        nextCard.intValue = cards[currentCard].intValue;
    }
    else
    {
        nextCard.value = "";
        nextCard.suit = '\0';
        nextCard.intValue = 0;
    }

    currentCard++;

    return nextCard;
}

/*
int Deck::CardCount()
{
    short int count = DECK_SIZE - currentCard;

    return count;
}
*/

void Deck::SwapCards(int a, int b)
{
    PlayingCard temp;

    temp = cards[a];
    cards[a] = cards[b];
    cards[b] = temp;
}

// Function Prototype(s)
void printHeader();
//void printDeck( Deck& deck );
//void nextFiveCards( Deck& deck);

int main()
{
    Deck newDeck;
    PlayingCard dealerCard1, dealerCard2, playerCard1, playerCard2;
    bool exitFlag, retry, stay, bust;
    char play, decision;
    uint dealerTotal = 0, playerTotal = 0, bet = 0, playerWins = 0, dealerWins = 0;
    int playerMoney = 0;

    // Seed the RNG
    srand(static_cast<uint>(time(nullptr)));

    // Print the header
    printHeader();

    retry = true;
    while (retry)
    {
        cout << "Minimum buy in is $10, what is your buy in? ";
        cin >> playerMoney;
        cout << endl;

        if (playerMoney < 10)
        {
            cout << "Not enough money, try again!" << endl << endl;
            retry = true;
        }
        else
        {
            retry = false;
            cout << endl;
        }
    }

    do
    {
        exitFlag = false;
        retry = true;
        while (retry)
        {
            cout << "----------------------------------------------------------" << endl;
            cout << "Minimum bet is $5, how much do you want to bet? ";
            cin >> bet;
            playerMoney -= bet;

            if (bet < 5)
            {
                cout << "Invalid bet, try again!" << endl << endl;
                retry = true;
            }
            else
            {
                retry = false;
                cout << endl;
            }
        }

        newDeck.Shuffle();

        dealerCard1 = newDeck.GetNextCard();
        dealerCard2 = newDeck.GetNextCard();
        dealerTotal = dealerCard1.intValue + dealerCard2.intValue;

        cout << "Dealer:  " << setw(4) << left << dealerCard1.value +
                dealerCard1.suit << setw(4) << left << "??"
             << "(" << dealerCard1.intValue << ")" << endl;

        playerCard1 = newDeck.GetNextCard();
        playerCard2 = newDeck.GetNextCard();
        playerTotal = playerCard1.intValue + playerCard2.intValue;

        cout << "Player:  " << setw(4) << left << playerCard1.value +
                playerCard1.suit << setw(4) << left << playerCard2.value +
                playerCard2.suit << "(" << playerTotal << ")"<< endl << endl;

        // PLAYER DECISIONS
        stay = false;
        bust = false;
        while (!stay && !bust)
        {
            // Do you want to stay or hit?
            cout << "Do you want to stay or hit? (S/H): ";
            cin >> decision;
            //cout << endl;

            if (decision == 'H' || decision == 'h')
            {
                PlayingCard newCard = newDeck.GetNextCard();
                playerTotal += newCard.intValue;

                cout << "You drew " << newCard.value << newCard.suit
                     << "  (" << playerTotal << ")" << endl << endl;

                if (playerTotal > 21)
                {
                    bust = true;
                }

            }
            else if (decision == 'S' || decision == 's')
            {
                cout << endl;
                stay = true;
            }
        }

        // DEALER MOVES
        if (!bust)
        {
            cout << "Dealer:  " << dealerCard1.value << dealerCard1.suit
                 << " " << dealerCard2.value << dealerCard2.suit;
            cout << "  (" << dealerTotal << ")" << endl;

            if (dealerTotal <= playerTotal)
            {
                while ((dealerTotal < 21) && (dealerTotal <= playerTotal))
                {
                    PlayingCard newCard = newDeck.GetNextCard();
                    dealerTotal += newCard.intValue;

                    cout << "Dealer drew " << newCard.value << newCard.suit
                         << "  (" << dealerTotal << ")" << endl;
                }
                cout << endl;
            }
        }

        if (((playerTotal <= 21) && (playerTotal > dealerTotal)) || dealerTotal > 21)
        {
            playerWins++;
            playerMoney += bet * 2;
            cout << "PLAYER WINS!!!" << endl << "Player's " << playerTotal
                 << " beats dealer's " << dealerTotal << "." << endl << endl;
        }
        else if (((dealerTotal <= 21) && (dealerTotal > playerTotal)) || playerTotal > 21)
        {
            dealerWins++;
            if (bust)
            {
                cout << "BUST!!! ";
            }
            cout << "\nDEALER WINS!!!" << endl << "Dealer's " << dealerTotal
                 << " beats your " << playerTotal << "." << endl << endl;
        }
        else if (playerTotal == dealerTotal)
        {
            cout << "PUSH!!!" << endl << endl;
            playerMoney += bet;
        }

        cout << "Money left: " << playerMoney << endl
             << "Player wins: " << playerWins << endl
             << "Dealer wins: " << dealerWins << endl << endl;

        if (playerMoney >= 5)
        {
            cout << "Would you like to play again? (Y/N): ";
            cin >> play;
            cout << endl;

            if (play == 'Y' || play == 'y')
            {
                cout << "\n\n\n";
                exitFlag = false;
            }
            else if (play == 'N' || play == 'n')
                exitFlag = true;
        }
        else
        {
            cout << "Not enough money!" << endl
                 << "GAME OVER" << endl;
            exitFlag = true;
        }
    }
    while (!exitFlag);

    cout << "\nThanks for playing!" << endl;

    return 0;
}


void printHeader()
{
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl
         << "+   ____                  ____                  +" << endl
         << "+   |   \\ |  __   __  | /   |  __   __  | /     +" << endl
         << "+   | o / | /  | /  \\ |/    | /  | /  \\ |/      +" << endl
         << "+   | o \\ | |  | |    |\\    | |  | |    |\\      +" << endl
         << "+   |___/ | \\__| \\__/ | \\ \\_/ \\__| \\__/ | \\     +" << endl
         << "+                                               +" << endl
         << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl
         << "                by Tanner Wing" << endl << endl;
}

/*
void printDeck( Deck& deck )
{
    PlayingCard card;

    for (int counter = 0; counter < DECK_SIZE; counter++)
    {
        card = deck.GetNextCard();
        cout << card.value << card.suit << " ";
    }
}

void nextFiveCards( Deck& deck)
{
    PlayingCard card;

    while (deck.CardCount() > 0)
    {
        cout << "Next 5 cards: ";

        for (int i = 0; i < 5; i++)
        {
            card = deck.GetNextCard();

            if (card.suit != '\0')
                cout << card.value << card.suit << " ";
            else
            {
                i = 4;
                cout << "...out of cards! ";
            }
        }
        if (deck.CardCount() > 0)
            cout << "(" << deck.CardCount() << " cards left)" << endl;
        else
            cout << "(" << "0 " << "cards left)" << endl;
    }
}
*/