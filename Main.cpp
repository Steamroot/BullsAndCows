/*This is the console executable, that makes use of the BullCowGame class 
This acts as the view in an MVC pattern, and its responsable for all user Int32eraction
for game logic, see the FBullCowGame class*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include "FBullCowGame.h"

using FText = std::string;
using Int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //Start new game

int main(){ 

    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while(bPlayAgain);
    return 0; //Exit app 

}


void PrintIntro(){

    std::cout << "\nWelcome to Bulls and Cows!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram?";
    return;

}


void PlayGame(){

    BCGame.Reset();
    Int32 MaxTries = BCGame.GetMaxTries();

    //Loop for the number of tries 
    //TODO Change from FOR to WHILE
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetValidGuess(); //TODO Make loop that checks for valid guesses

        //Submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        //PrInt32 the number of bulls and cows 
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << "\nCows = " << BullCowCount.Cows;
    }
    PrintGameSummary();
    return;
}


FText GetValidGuess(){
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::InvalidStatus;
    do{
        //Get guess from player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "\n\nTry  " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";

        std::getline(std::cin, Guess);

        //Check status and give feedback
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status){
            case EGuessStatus::WrongLength:
                std::cout << "\nPlease enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::NotIsogram:
                std::cout << "\nPlease enter a word without repeating letters.\n";
                break;
            case EGuessStatus::NotAllLower:
                std::cout << "\nPlease enter all lower case.\n";
                break;
            default:
            break;
        }
    } while (Status != EGuessStatus::OK);   
    return Guess;
}

bool AskToPlayAgain(){
    std::cout << "\nDo you want to play again with the same hidden word? (y/n)\n";
    FText Response = "";
    std::getline(std::cin, Response);
    return (std::tolower(Response[0]) == 'y');
}

void PrintGameSummary(){
    if(BCGame.IsGameWon()){
        std::cout << "\n\nCongratulations, you have won the game!\n";
    }else{
        std::cout << "\n\nSorry, you lost!\n";
    }
}