#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo 
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults 
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To) 
{
    return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) 
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return Draw;
    switch (RoundInfo.PlayerChoice) {
    case Stone:
        return (RoundInfo.ComputerChoice == Paper) ? Computer : Player;
    case Paper:
        return (RoundInfo.ComputerChoice == Scissors) ? Computer : Player;
    case Scissors:
        return (RoundInfo.ComputerChoice == Stone) ? Computer : Player;
    }
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes) return Player;
    else if (ComputerWinTimes > PlayerWinTimes) return Computer;
    else return Draw;
}

string ChoiceName(enGameChoice Choice) 
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner) 
{
    string arrWinnerName[3] = { "Player", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayerChoice()
{
    short Choice;

    do {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player Choice: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;

    // Text-based simulation of green/red screen
    if (RoundInfo.Winner == Player) {
        system("Color 2F");
        cout << "(Player wins)\n";
    }
    else if (RoundInfo.Winner == Computer) {
        system("Color 4F");
        cout << '\a';
        cout << "(Computer wins)\n";
    }
    else
        system("Color 6F");
}

stGameResults PlayGame(short HowManyRounds) 
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return { HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(PlayerWinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(PlayerWinTimes, ComputerWinTimes)) };
}

void StartGame()
{
    char PlayAgain = 'Y';

       
    do {
        system("cls"); // Clear the screen for a new game
        short HowManyRounds;
        cout << "How many rounds do you want to play? ";
        cin >> HowManyRounds;
        while (HowManyRounds < 1) {
            cout << "Please enter a positive number of rounds: ";
            cin >> HowManyRounds;
        }


        stGameResults GameResults = PlayGame(HowManyRounds);
        cout << "\nWinner: " << GameResults.WinnerName << endl;

        this_thread::sleep_for(chrono::seconds(1));

        if (GameResults.GameWinner == Player)
        {
            system("Color 2F");
        }
        else if(GameResults.GameWinner == Computer)
        {
            system("Color 4F");
        }
        else
        {
            system("Color 6F");
        }
   
        cout << "Game Results: Player wins " << GameResults.PlayerWinTimes << " times, Computer wins " << GameResults.ComputerWinTimes << " times, Draws " << GameResults.DrawTimes << " times.\n";

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() 
{

    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}