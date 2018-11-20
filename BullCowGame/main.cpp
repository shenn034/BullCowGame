//
//  main.cpp
//  BullCowGame
//
//  Created by shen on 19/11/18.
//  Copyright © 2018 shen. All rights reserved.
//

#include <iostream>
#include "FBullCowGame.hpp"

// to make the syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void printGameSummary();

FBullCowGame BCGame; // instantiate a new game, where we re-use accross plays

// the entry of the game
int main() {
    bool bPlayAgain {false};
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while(bPlayAgain);
    
    return 0;
}




void PrintIntro()
{
    // introduce the game
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << std::endl;
    std::cout <<"          }   {                ___ " << std::endl;
    std::cout <<"          (o o)               (o o) " << std::endl;
    std::cout <<"   /-------\\ /                 \\ /-------\\" << std::endl;
    std::cout <<"  / | BUll |o                   o| COW  | \\ " << std::endl;
    std::cout <<" *  |-,--- |                     |------|  * " << std::endl;
    std::cout <<"    ^      ^                     ^      ^ " << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    std::cout << std::endl;
    return;
}


FText GetValidGuess()
{
    FText Guess {};
    EGuessStatus status  = EGuessStatus::Invalid_Status;
    do {
        int32 currentTry = BCGame.getCurrentTry();
        
        // get a guess from the player
        
        
        std::cout << "Try " << currentTry << " of " << BCGame.getMaxTries()<< ". Enter your guess: ";
        std::getline(std::cin,Guess);
        
        status = BCGame.checkGuessValidity(Guess);
        switch (status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n";
                break;
                
                
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a lowercase letter.\n";
                break;
                
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n";
                break;
                
            default:
                break;
        }
        std::cout << std::endl;
    } while (status != EGuessStatus::OK);
    return Guess;
}

// plays a gingle game to completion
void PlayGame()
{
    BCGame.reset();
    int32 maxTries = BCGame.getMaxTries();
    
    
    // loop for the number of turns asking for guesses
    while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries){
        FText Guess {GetValidGuess()};
        
        FBullCowCount bullCowCount = BCGame.SubmitValidGuess(Guess);
        std::cout << "Bulls = " << bullCowCount.Bulls;
        std::cout << ". Cows = " << bullCowCount.Cows << "\n\n";
    }
    
    printGameSummary();
    
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? (y/n)";
    FText response {};
    getline(std::cin, response);
    return (response[0] == 'y' || response[0] == 'Y');
}

void printGameSummary(){
    // TODO summarize game
    if (BCGame.isGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n" << std::endl;
    }
    
    else
    {
        std::cout << "Better lucks next time!\n" << std::endl;
    }
}
