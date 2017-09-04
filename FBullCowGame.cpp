//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Dean Paget on 01/09/2017.
//  Copyright © 2017 Dean Paget. All rights reserved.
//


#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using int32 = int;
using Fstring = std::string;

FBullCowGame::FBullCowGame()
{
    Reset("dog");
}


void FBullCowGame::Reset(FString HiddenWord)
{
    MyCurrentTry = 1;
    MyHiddenWord = HiddenWord;
    bGameIsWon = false;
}

FString FBullCowGame::GetWantedLength(int32 DesiredLength) const
{
    TMap <int32, FString> HIDDEN_WORD {{3, "dog"},{4, "port"},{5, "table"},{6, "planet"},{7, "destroy"}};
    return HIDDEN_WORD[DesiredLength];
}


int32 FBullCowGame::GetMaxTries() const
{
    TMap <int32, int32> WordLengthToMaxTries {{3,4}, {4,7}, {5,10}, {6,15}, {7,25}};
    
    return WordLengthToMaxTries[MyHiddenWord.length()];
}


int32 FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}


int32 FBullCowGame::GetHiddenWordLength() const
{
    return MyHiddenWord.length();
}


bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if(Word.length() <= 1)
    {
        return true;
    }
    
    
    TMap <char, bool> LetterSeen; // setting up map
    for (auto Letter : Word) // for all letters of the word
    {
        Letter = tolower(Letter);
        if(LetterSeen[Letter]) //if letter is in the map
        {
            return false;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    if(Word.length() <= 1)
    {
        return true;
    }

    for(auto Letter : Word)
    {
        if(!islower(Letter)){
            return false;
        }
    }
    return true;
}


EGuessStatus FBullCowGame::CheckGuessValidity(Fstring Guess) const
{
    if(!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if(!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
    
}

FBullCowCount FBullCowGame::SubmitValidGuess(Fstring Guess)
{
    MyCurrentTry++;

    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();
    
    // loop through all letters in the guess
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        // compare letters against the hidden word
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            // if they match then
            if(Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++; // increment bulls if theyre in the same place
                }
                // increment cows when not
                else
                {
                    BullCowCount.Cows++;
                }
               
            }
        }
    }
    if(BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    
    return BullCowCount;
}




