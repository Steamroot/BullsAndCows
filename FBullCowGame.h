#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus{
    InvalidStatus,
    OK,
    NotIsogram,
    WrongLength,
    NotAllLower
};

class FBullCowGame
{
public:
    FBullCowGame(); //Constructor

    int32 GetHiddenWordLength() const;
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;

    void Reset();
    //Counts the bulls and cows, and that increases the "try" #, assuming valid guess
    FBullCowCount SubmitValidGuess(FString);


private:
    //See constructor for initialitation
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;

    bool IsIsogram(FString) const;
    
    bool IsLowercase(FString) const;
};