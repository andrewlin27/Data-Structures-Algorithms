#include <string>
#include <sstream>
#include "Card.h"

int rand221(void) {
    return rand();
}

// You may want to write the following three functions, but they are not required

std::istream& operator>>(std::istream& in, Suit& suit) {
    std::string input;
    in >> input;
    if (input == "spades") {
        suit = Suit::SPADES;
    }
    else if (input == "diamonds") {
        suit = Suit::DIAMONDS;
    }
    else if (input == "clubs") {
        suit = Suit::CLUBS;
    }
    else if (input == "hearts") {
        suit = Suit::HEARTS;
    }
    return in;
}

Rank to_rank(const std::string& string) {
    Rank num;
    if (string.length() <= 2) {
        num = stoi(string);
    }
    else if (string == "ace") {
        num = 1;
    }
    else if (string == "jack") {
        num = 11;
    }
    else if (string == "queen") {
        num = 12;
    }
    else if (string == "king") {
        num = 13;
    }
    return num;
}

std::istream& operator>>(std::istream& in, Card& card) {
    std::string rankStr;
    in >> card.suit >> rankStr;
    card.rank = to_rank(rankStr);
    return in;
}

List<Card> buildDeck(std::istream& file) {
    List<Card> deck;
    std::string lineStr;
    while (getline(file, lineStr)) {
        std::istringstream lineIn(lineStr);
        Card currCard;
        lineIn >> currCard;
        deck.push_back(currCard);
    }
    return deck;
}

List<Card> shuffle(const List<Card>& deck) {
    List<Card> newDeck;
    for (Card x : deck) {
        if (rand221() % 2 == 0) {
            newDeck.push_front(x);
        }
        else {
            newDeck.push_back(x);
        }
    }
    return newDeck;
}