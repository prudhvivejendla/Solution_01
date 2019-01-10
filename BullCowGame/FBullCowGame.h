#pragma once
#include <string>
#include <iostream>
#include <algorithm>

using FString = std::string;
using int32 = int;

struct BullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	OK,
	NotIsogramm,
	Empty,
	InvalidLength,
	HasNumericValue,
	InvalidValue
};

class FBullCowGame {
public:
	void Reset();
	int32  GetMaxTries() const;
	int32  GetCurrentTry() const;
	int32  GetGeneratedWordLength() const;
	EWordStatus isGuessValid(FString) const;
	bool isGuessRight(FString) const;
	FString GetUserGuess();
	BullCowCount submitValidGuess(FString);
private:
	int32  CurrentAttempt;
	int32  MAX_ATTEMPT_LIMIT = 5;
	FString GeneratedWord;
	void GenerateNewWord();
	void ToLowerCase(FString &) const;
	bool HasNumber(FString) const;
	bool IsIsogram(FString) const;
};