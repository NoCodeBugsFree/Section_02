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
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE,
	INVALID
};

/** Game logic  */

class FBullCowGame
{

public:

	FBullCowGame(); // ctor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;
	void Reset(); 
	
	// counts bulls and cows, and increasing turn number
	// assuming valid Guess
	FBullCowCount SubmitValidGuess(FString Guess);
	
protected:
	
	
	
private:

	int32 MyCurrentTry = 1;
	FString MyHiddenWord;
	bool IsIsogram(FString Word) const;
	bool IsLoweCase(FString Word) const;
	bool bGameIsWon;
};
