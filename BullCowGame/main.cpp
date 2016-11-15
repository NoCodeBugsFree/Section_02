/** 
* Project Description 
* this is View in MVC pattern
* for game logic see the FBullCowGame class
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Unreal syntax
using FText = std::string;
using int32 = int;

// functions definitions - prototype
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, we re-use across plays

// entry point
int main()
{
	bool bPlayAgain = false;
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0;
}

// introduce the game
void PrintIntro()
{	
	std::cout << "Welcome to Bulls ans Cows,  a fun word game!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

// loop continually until he user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::INVALID;

	do
	{
		int CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess : ";
		
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::NOT_ISOGRAM:
		{
			std::cout << "Please enter a word without repeating letters" << std::endl;
		}
		break;
		case EGuessStatus::NOT_LOWERCASE:
		{
			std::cout << "Please enter all lowercase letters" << std::endl;
		}
		break;
		case EGuessStatus::WRONG_LENGTH:
		{
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letters isogram!" << std::endl;
		}
		break;
		default:
			// assume the guess is valid
			break;
		}
	}
	while (Status != EGuessStatus::OK); // keep looping until we get no error

	return Guess;
}

//
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is not won
	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries )
	{
		FText Guess = GetValidGuess();
		// Submit valid guess to the game 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		std::cout << std::endl;
	}

	
	PrintGameSummary();

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again ? (y/n)" << std::endl;
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Win\n" << std::endl;
	} 
	else
	{
		std::cout << "Lose\n" << std::endl;
	}
}




