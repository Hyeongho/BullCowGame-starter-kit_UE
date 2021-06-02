// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

	SetupGame();

	PrintLine(TEXT("The number of possible words is %d"), Words.Num());

	PrintLine(TEXT("The HiddenWord is: %s. \nIt is %i characters iong"), *HiddenWord, HiddenWord.Len());

	//PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord));

	//HiddenWord = TEXT("cake");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();

		SetupGame();
	}

	else
	{
		ProcessGuess(Input);
	}
	
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = TEXT("cakes");
	Lives = 4;

	bGameOver = false;

	PrintLine(TEXT("Guess the %i Letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %d lives"), Lives);
	PrintLine(TEXT("Type in your guess and \npress enter to continue"));

	/*const TCHAR HW[] = TEXT("plums");
	PrintLine(TEXT("Charcter 1 of the hidden word is: %c"), HiddenWord[0]);
	PrintLine(TEXT("The 4th character of HW is: %c"), HW[3]);*/

}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;

	ClearScreen();

	
	PrintLine(TEXT("\nPress enter to play agian"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have Won!"));
		EndGame();

		return;
	}

	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again"));

		return;
	}

	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %d letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \n you have %d lives remaining"), Lives);

		return;
	}

	PrintLine(TEXT("Lost a life!"));
	PrintLine(TEXT("%d"), --Lives);

	if (Lives <= 0)
	{
		ClearScreen();

		PrintLine(TEXT("You hove no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

		EndGame();

		return;
	}

	PrintLine(TEXT("Guess again, you hove %d lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
	/*int i = 0;
	int Comparison = i + 1;*/

	for (int i = 0; i < Word.Len(); i++)
	{
		for (int Comparison = i + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[i] == Word[Comparison])
			{
				return false;
			}
		}
	}

	return true;
}
