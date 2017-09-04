//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Dean Paget on 01/09/2017.
//  Copyright © 2017 Dean Paget. All rights reserved.
//
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
    
};


class FBullCowGame {
public:
    FBullCowGame();
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    FString GetWantedLength(int32) const;
    
    bool IsGameWon() const;
    
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset(FString);
    FBullCowCount SubmitValidGuess(FString);
    
    
    
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    int32 WantedLength;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

