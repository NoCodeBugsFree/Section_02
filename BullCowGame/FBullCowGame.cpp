#pragma once
#include "FBullCowGame.h"
#include <map>

#define TMap std::map 

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries { { 3, 5}, { 4, 5 }, { 5, 5 }, { 6, 5 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isogram
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case

		if (LetterSeen[Letter])
		{
			return false; // we do not have an isogram
		}
		else // else add the letter to the map as seen
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLoweCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		} 
	}
	return true;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // must be isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess is not an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLoweCase(Guess)) // if the guess is not all lowercase
	{
		return EGuessStatus::NOT_LOWERCASE; 
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH; // if guess length is wrong
	}
	else
	{
		return EGuessStatus::OK; // otherwise return OK
	}
}

// receives a VALID guess, increments turn, and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assume same length as guess

	for (int32 MyHiddenWordCharacter = 0; MyHiddenWordCharacter < WordLength; MyHiddenWordCharacter++)
	{
		// compare letters against the guess
		for (int32 GuessCharacter = 0; GuessCharacter < WordLength; GuessCharacter++)
		{
			// if they match then
			if (Guess[GuessCharacter] == MyHiddenWord[MyHiddenWordCharacter])
			{
				if (MyHiddenWordCharacter == GuessCharacter)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}	
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	
	return BullCowCount;
}

