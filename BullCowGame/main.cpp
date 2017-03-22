#pragma once
#include <iostream>
#include <string>	
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());

	return 0; 
}

 
// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE! - You Win\n";
	}
	else
	{
		std::cout << "Better luck next time.\n";
	}
}


FText GetValidGuess()
{
	EWordStatus Status = EWordStatus::Invalid;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << "/" << BCGame.GetMaxTries() << " Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;

		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;

		case EWordStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word.\n";
			break;

		default:
			break;
		}
		
	}while (Status != EWordStatus::Ok);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
