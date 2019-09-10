#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() {Reset();} //Default constructor


int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const {return bGameIsWon;}   

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthMaxTries {3, 5};
    return WordLengthMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(){
    MyCurrentTry = 1;
    bGameIsWon = false;
    const FString HiddenWord = "caro";
    MyHiddenWord = HiddenWord;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
    //If guess is not an isogram
    if (!IsIsogram(Guess)){
        return EGuessStatus::NotIsogram;
    }
    //If guess isn't all lower case
    else if(!IsLowercase(Guess)){
        return EGuessStatus::NotAllLower;
    }
    //If guess length is wrong
    else if(Guess.length() != GetHiddenWordLength()){
        return EGuessStatus::WrongLength;
    }
    //Otherwise
    else{
        return EGuessStatus::OK;
    }
        //return OK
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
    
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();
    
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
        for (int32 GChar = 0; GChar < WordLength; GChar++){

           if (Guess[GChar] == MyHiddenWord[MHWChar]){
                if (MHWChar == GChar){
                    BullCowCount.Bulls++;

                }else{
                    BullCowCount.Cows++;
                }
            } 

        }
    }
    if (BullCowCount.Bulls == WordLength){
        bGameIsWon = true;
    }else{
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const{
    //treat 0 and 1 letter words as isograms 
    if (Word.length() <= 1){return true;}
    
    TMap<char, bool> LetterSeen;   //setup our map
    for (auto Letter : Word){
        Letter = tolower(Letter);//Loop through alll the letters in the word
        if (LetterSeen[Letter]){
            return false;
        }else{
            LetterSeen[Letter] = true;
        }
    }
    return true;//in cases where \0 is entered
}

bool FBullCowGame::IsLowercase(FString Guess) const{
    for (auto Letter : Guess){
        if (!islower(Letter)){
            return false; 
        }else{
            return true;
        }
    }
    return true;
}