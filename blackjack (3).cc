#include <iostream>
#include <string>
#include <vector>

bool IsAce(const std::string& card_name) { 
    return card_name == "A"; 
}

bool IsFaceCard(const std::string& card_name) {
    return (card_name == "Q") || (card_name == "J") || (card_name == "K");
}

bool IsNumberCard(const std::string& card_name) {
    int value = 0;
    bool num_card = true;
    try {
        value = stoi(card_name);
        if ((value > 1) && (value < 11)) {
            num_card = true;
        } else if ((value < 2) || (value > 10)) {
            num_card = false;
        }
    } catch (std::exception const& e) {
        num_card = false;
    }
    return num_card;
}

bool IsCardName(const std::string& str) {
    return (IsAce(str) || IsFaceCard(str) || IsNumberCard(str));
}

bool AllArgumentsValid(const std::vector<std::string>& arguments) {
    for (int i = 1; i < arguments.size(); i++) {
        if (!IsCardName(arguments.at(i))) {
            std::cout << "error: unknown card '" << arguments.at(i) << "' \n";
            return false;
        }
    }
    return true;
}

int CardPoints(const std::string& card_name) {
    int points = 0;
    if (IsAce(card_name)) {
        points = 1;
    } else if (IsFaceCard(card_name)) {
        points = 10;
    } else {
        points = std::stoi(card_name);
    }
    return points;
}

bool HandContainsAce(const std::vector<std::string>& arguments) {
    for (int index = 1; index < arguments.size(); index++) {
        if (IsAce(arguments.at(index))) {
            return true;
        }
    }
    return false;
}

bool IsBust(int score) { 
    return (score > 21); 
}

int HandScore(const std::vector<std::string>& arguments) {
    int sum_cards = 0;
    int new_value = 0;
    for (int index = 1; index < arguments.size(); index++) {
        new_value = sum_cards + (CardPoints(arguments.at(index)));
        sum_cards = new_value;
    }
    if ((HandContainsAce(arguments)) && !(IsBust(sum_cards + 10))) {
        sum_cards = sum_cards + 10;
    }

    return sum_cards;
}

void PrintScore(int score) {
    if (!(IsBust(score))) {
        std::cout << "Score is " << score << "\n";
    } else {
        std::cout << "Score is " << score << ", BUST"
                  << "\n";
    }
}

void TestBlackjack() {
    std::vector<std::vector<std::string>> testCases = {
        {"Test", "A", "K"},
        {"Test", "A", "10"},
        {"Test", "8", "5", "3"},
        {"Test", "8", "5", "3", "A"},
        {"Test", "K", "3", "Q"},
        {"Test", "K", "3", "Q", "A"},
        {"Test", "Z"} 
    };

    for(const auto& testCase : testCases) {
        if (AllArgumentsValid(testCase)) {
            PrintScore(HandScore(testCase));
        } else {
            std::cout << "error: invalid card " << std::endl;
        }
    }
}

int main() {
    TestBlackjack();
    return 0;
}
