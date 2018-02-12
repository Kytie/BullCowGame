#pragma once
using FString = std::string;

void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool IsPlayAgain();
void PrintGameSummary(bool IsGameWon);