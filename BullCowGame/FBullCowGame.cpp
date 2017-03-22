#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const{return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{return bIsGameWon;}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxtries{ {3,4}, {4,5}, {5,6}, {6,7} };
	return WordLengthToMaxtries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bIsGameWon = false;
	return;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght())
	{
		return EWordStatus::Wrong_Lenght;
	}
	else
	{
		return EWordStatus::Ok;
	}
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LettersSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LettersSeen[Letter])
		{
			return false;
		}
		else 
		{
			LettersSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (MyHiddenWord[i] == Guess[j])
			{
				if (i == j)
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
	
	if(BullCowCount.Bulls == HiddenWordLength)
		bIsGameWon = true;

	return BullCowCount;
}
