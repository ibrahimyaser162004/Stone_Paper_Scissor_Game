#include <iostream>
#include <vector>
using namespace std;

int roundsNumber(){
    int roundNumber;
    do {
        cout << "How many rounds you want?";
        cin >> roundNumber;
    } while (roundNumber <= 0);
    return roundNumber;
}



enum whoWins {player = 1, computer = -1, draw = 0};
enum choices {stone = 1, paper = 2, scissor = 3 };

struct roundInfo {
    int roundNumber;
    choices playerChoice;
    choices computerChoice;
    whoWins winner;
    string winnerName;
};

struct resultsInfo {
    int gameRounds;
    int playerWonTimes = 0;
    int computerWonTimes = 0;
    int drawTimes = 0;
    whoWins finalGameWinner;
    string finalWinnerName;
};

whoWins whoWinsfunc (int playerChoice, int computerChoice){
    if (playerChoice == computerChoice) return whoWins::draw;
    if (playerChoice == choices::stone) {
        return computerChoice == choices::paper? whoWins::computer : whoWins::player;
    }
    else if (playerChoice == choices::paper) {
        return computerChoice == choices::scissor? whoWins::computer : whoWins::player;
    }
    else {
        return computerChoice == choices::stone? whoWins::computer : whoWins::player;
    }
}

string choiceString(choices choice) {
    switch (choice) {
        case choices::paper: return "Paper";
        case choices::scissor: return "Scissor";
        case choices::stone: return "Stone";
        default: return NULL;
    }
}

string winnerString(whoWins winner) {
    switch(winner) {
        case whoWins::player : return "\033[42m  Player  \033[0m";
        case whoWins::computer : return "\033[41m  Computer  \033[0m";
        case whoWins::draw : return "\033[43m  No Winner \033[0m";
    }
}

whoWins roundWinner(int playerChoice, int computerChoice){
    if (whoWinsfunc(playerChoice, computerChoice) == whoWins::computer) return whoWins::computer;
    else if (whoWinsfunc(playerChoice, computerChoice) == whoWins::player) return whoWins::player;
    else return whoWins::draw;
}

void roundPrint(roundInfo roundDetails) {
    cout << "\n\n__________Round["  << roundDetails.roundNumber << "]__________\n\n";
    cout << "Player Choice: " << choiceString(roundDetails.playerChoice) << endl;
    cout << "Computer Choice: " << choiceString(roundDetails.computerChoice) << endl;
    cout << "Round Winner: " << roundDetails.winnerName << endl;
    cout << "____________________________\n\n";
}

whoWins finalWinner(int player, int computer) {
    if (player > computer) return whoWins::player;
    else if (player < computer) return whoWins::computer;
    else return whoWins::draw;
}

char lower(char ch){
    if (ch <= 'Z' && ch >= 'A') return ch + ('a'-'A');
    return ch;
}

void gameOver(resultsInfo resultDetails) {
    cout << "\n\n\t\t\t________________________________\n";
    cout << "\n\n\t\t\t\t+++ Game Over +++\n";
    cout << "\n\n\t\t\t________________________________\n";
    cout << "\n\n\t\t\t___________[Game Results]_______\n\n";
    cout << "\t\t\tGame Rounds       : \t " << resultDetails.gameRounds << endl;
    cout << "\t\t\tPlayer won times  : \t " << resultDetails.playerWonTimes << endl;
    cout << "\t\t\tComuter won times : \t " << resultDetails.computerWonTimes << endl;
    cout << "\t\t\tDraw times        : \t " << resultDetails.drawTimes << endl;
    cout << "\t\t\tFinal winner      : " << resultDetails.finalWinnerName << endl;
    cout << "\t\t\t________________________________\n\n";
}

choices randComputerChoice(){
    return choices(rand()%3+1); //rand()%(To-from)+from
}

choices getPlayerChoice(){
    int playerChoice;
    do {
        cout << "Your choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
        cin >> playerChoice;
    } while (!(playerChoice >= 1 && playerChoice <= 3));
    return choices(playerChoice);
}

void roundsRun(int numberOfRounds){
    roundInfo roundDetails;
    resultsInfo finalGameResultsDetails;
    for (int i = 0; i < numberOfRounds; i++){
        cout << "Round [" << i+1 << "] begins: \n";
        roundDetails.roundNumber = i+1;
        roundDetails.playerChoice = getPlayerChoice();
        roundDetails.computerChoice = randComputerChoice();
        roundDetails.winner = roundWinner(roundDetails.playerChoice, roundDetails.computerChoice);
        roundDetails.winnerName = winnerString(roundDetails.winner);
        roundPrint(roundDetails);
        if (roundWinner(roundDetails.playerChoice, roundDetails.computerChoice) == whoWins::player) finalGameResultsDetails.playerWonTimes++;
        else if (roundWinner(roundDetails.playerChoice, roundDetails.computerChoice) == whoWins::computer) finalGameResultsDetails.computerWonTimes++;
        else finalGameResultsDetails.drawTimes++;
    }
    finalGameResultsDetails.gameRounds = numberOfRounds;
    finalGameResultsDetails.finalGameWinner = finalWinner(finalGameResultsDetails.playerWonTimes, finalGameResultsDetails.computerWonTimes);
    finalGameResultsDetails.finalWinnerName = winnerString(finalGameResultsDetails.finalGameWinner);
    gameOver(finalGameResultsDetails);
}


void playMore(){
    char playAgain;
    do {
        cout << "Do you want to play again (y/n)?" ;
        cin >> playAgain;
        playAgain = lower(playAgain);
        if (playAgain == 'y') {
        int roundNum =  roundsNumber();
        roundsRun(roundNum);
    }} while (playAgain == 'y');
}

int main(){
    srand(unsigned(time(NULL)));
    int roundNum = roundsNumber();
    roundsRun(roundNum);
    playMore();
}