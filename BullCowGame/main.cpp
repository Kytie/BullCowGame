#include <iostream>
#include <locale>
#include "main.h"
#include "FBullCowGame.h"

FBullCowGame BCGame;

int main()
{
	PrintIntro();
	do
	{
		PlayGame();
	} 
	while (IsPlayAgain());
	return 0;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxRetries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		std::cout << std::endl;
		int32 TriesLeft = BCGame.GetMaxRetries() - BCGame.GetCurrentTry();
		FString Guess = GetValidGuess();
		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BCCount.bulls;
		std::cout << ". Cows = " << BCCount.cows << std::endl;
		std::cout << "Guesses Left: " << TriesLeft << std::endl;
	}
	PrintGameSummary(BCGame.IsGameWon());
	return;
}

void PrintGameSummary(bool IsGameWon)
{
	std::cout << std::endl;
	if (IsGameWon)
	{
		std::cout << "Congratulations you won!" << std::endl;
	}
	else
	{
		std::cout << "You lost, better luck Next time!" << std::endl;
	}
}

FString GetValidGuess()
{
	EGuessStatus GuessStatus = EGuessStatus::INVALID;
	FString Guess = "";
	do
	{
		std::cout << "Please enter your guess: ";
		std::getline(std::cin, Guess);
		GuessStatus = BCGame.CheckGuessValidity(Guess);
		switch (GuessStatus)
		{
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Your guess is not an isogram." << std::endl;
			break;
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter in a " << BCGame.GetHiddenWordLength() << " Length word." << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter your guess in all lowercase." << std::endl;
		default:
			break;
		}
	} while (GuessStatus != EGuessStatus::OK);
	return Guess;
}

bool IsPlayAgain()
{
	std::cout << std::endl;
	std::cout << "Would you like to play again? (y/n): ";
	std::locale loc;
	FString response = "";
	std::getline(std::cin, response);
	FString temp = response;
	for (FString::size_type i = 0; i < response.length(); ++i)
	{
		temp = tolower(response[i], loc);
	}
	return (temp[0] == 'y');
}
