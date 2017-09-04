/*
    main.cpp
    BullCowGame

    Created by Dean Paget on 31/08/2017.
    Copyright © 2017 Dean Paget. All rights reserved.
*/


#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void WordChoice();



FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main()
{
    do {
    PrintIntro();
    PlayGame();
    } while(AskToPlayAgain() == true);
    return 0; // exit the application
}


// Introduce the game
void PrintIntro()
{
    std::cout << "\nWelcome to the Bulls and Cows Game." << std::endl;
    std::cout << "                                               " << std::endl;
    std::cout << "              ^}---}^                           " << std::endl;
    std::cout << "             / o\\ /o \\          ^---^               " << std::endl;
    std::cout << "             |       |        / o  o  \\                  " << std::endl;
    std::cout << "      _______\\  ----/        |        |               " << std::endl;
    std::cout << "     / BULL     ___/         \\  O     /_____              " << std::endl;
    std::cout << "   /|  ____   /               \\___     COW  \\           " << std::endl;
    std::cout << "  / | |    | |                     \\   ___  |\\           " << std::endl;
    std::cout << " *  |_|    |_|                      | |   | | \\             " << std::endl;
    std::cout << "                                    |_|   |_|  *            " << std::endl;
    std::cout << std::endl;
    std::cout << "Your task is to guess the isogram in a limited amount of tries.\n";
    std::cout << "An isogram is a word where none of its letter repeat for example 'toilet'\n\n";

}


void PlayGame()
{
    
    WordChoice();
    
    int32 MaxTries = BCGame.GetMaxTries();
   
    // loop for the number of attempts
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
    FText Guess = GetValidGuess();
    
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
        std::cout << std::endl;
        
    }
    PrintGameSummary();
}


FText GetValidGuess()
{
    FText Guess = "";
    
    EGuessStatus Status = EGuessStatus::Invalid;
    do
    {
        // Get a guess from a player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " out of " << BCGame.GetMaxTries()
        <<": Enter your guess: ";
        
        getline(std::cin,Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
    
        switch(Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength()
                << " letter word. \n\n";
                break;
            
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter your guess in lowercase. \n\n";
                break;
            
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter an isogram. \n\n";
                break;
            
            default:
                break;
        }
    } while(Status != EGuessStatus::OK);
    return Guess;
}


bool AskToPlayAgain()
{
    std::cout << "Do you want to play again? (Y/N): ";
    FText Response = "";
    getline (std::cin,Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}


void PrintGameSummary()
{
    if(BCGame.IsGameWon())
    {
        std::cout << "WELL DONE, you answered correctly! \n";
    }
    else
    {
        std::cout << "Better luck next time. \n";
    }
    
}

void WordChoice()
{
    int32 DesiredLength = 3;
    do
    {
        std::cout << "Please Enter the length you would like the isogram to be (between 3 and 7): ";
        std::cin >> DesiredLength;
        std::cout << std::endl;
        
        if(DesiredLength < 3 || DesiredLength > 7)
        {
            std::cout << "Isogram must be between 3 and 7 characters long \n";
        }
    } while (DesiredLength < 3 || DesiredLength > 7);
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    FString HiddenWord = BCGame.GetWantedLength(DesiredLength);
    
    BCGame.Reset(HiddenWord);
    
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?" << std::endl << std::endl;
    
    
}



