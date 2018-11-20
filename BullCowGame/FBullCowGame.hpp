// The game logic (no view code or direct user interaciton)
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by shen on 19/11/18.
//  Copyright © 2018 shen. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

#endif /* FBullCowGame_hpp */

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};


class FBullCowGame {
private:
    int32 myCurrentTry;
    FString myHiddenWord;
    bool bGameIsWon;
    
    
public:
    FBullCowGame();
    void reset();
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    bool isGameWon() const;
    EGuessStatus checkGuessValidity(FString &guess) const;
    FBullCowCount SubmitValidGuess(FString &guess);
    bool IsIsogram(FString &guess) const;
    bool IsLowerCase(FString &guess) const;
    
    
    
};
