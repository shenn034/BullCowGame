//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by shen on 19/11/18.
//  Copyright © 2018 shen. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map // to make syntax Unreal friendly

FBullCowGame::FBullCowGame() {
    reset();
}


EGuessStatus FBullCowGame::checkGuessValidity(FString &guess) const{
    if (!IsIsogram(guess)){
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(guess)){
        return EGuessStatus::Not_Lowercase;
    }
    else if (guess.length() != getHiddenWordLength()){
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}


bool FBullCowGame::isGameWon() const{
    return bGameIsWon;
}


int32 FBullCowGame::getMaxTries() const{
    TMap<int32, int32> wordLengthToMaxTries {{3, 5}, {4, 5}, {5, 5}, {6, 5}};
    return wordLengthToMaxTries[(int32)myHiddenWord.length()];
}


void FBullCowGame::reset() {
    const FString HIDDEN_WORD = "planet";
    myCurrentTry = 1;
    myHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    return;
}

int32 FBullCowGame::getCurrentTry() const{
    return myCurrentTry;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString &guess) {
    myCurrentTry++;
    FBullCowCount bullCowCount;
    
    //loop through all letters in the hidden word
    for (int32 myHiddenWordChar = 0; myHiddenWordChar < myHiddenWord.length(); myHiddenWordChar++){
        for (int32 guessWordChar = 0; guessWordChar < myHiddenWord.length(); guessWordChar++)
            if (guess[guessWordChar] == myHiddenWord[myHiddenWordChar]){
                if (guessWordChar == myHiddenWordChar)
                    bullCowCount.Bulls++;
                else
                    bullCowCount.Cows++;
            }
    }
    
    if (bullCowCount.Bulls == myHiddenWord.length()){
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    
    return bullCowCount;
}

int32 FBullCowGame::getHiddenWordLength() const { 
    return (int32)myHiddenWord.length();
}

bool FBullCowGame::IsIsogram(FString &guess) const {
    if (guess.length() <= 1){return true;}
    
    TMap<char,bool> letterSeen;
    for (char letter : guess)
    {
        letter = tolower(letter);
        if (letterSeen[letter]) {return false;}
        else {letterSeen[letter] = true;}
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString &guess) const { 
    
    for (char letter : guess)
    {
        if (!islower(letter)) {return false;}
    }
    return true;
}







