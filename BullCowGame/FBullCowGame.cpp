#include "FBullCowGame.h"  
#include<locale>
#include<map>

#define TMap std::map

void FBullCowGame::Reset()
{
	GenerateNewWord();
	CurrentAttempt = 1;
}

int32  FBullCowGame::GetMaxTries() const
{
	return MAX_ATTEMPT_LIMIT;
}

int32  FBullCowGame::GetCurrentTry() const
{
	return CurrentAttempt;
}

int32 FBullCowGame::GetGeneratedWordLength() const
{
	return GeneratedWord.length();
}

EWordStatus FBullCowGame::isGuessValid(FString value) const
{
	if (value.empty()) {
		std::cout << std::endl << "Please enter something. " << std::endl;
		return EWordStatus::Empty;
	}
	else if (value.length() != GetGeneratedWordLength()) {
		std::cout << std::endl << "Please enter word of length: " << GetGeneratedWordLength() << std::endl;
		return EWordStatus::InvalidLength;
	}
	else if (HasNumber(value)) {
		std::cout << std::endl << "Please enter only alphabets word. " << std::endl;
		return EWordStatus::HasNumericValue;
	}
	else if (IsIsogram(value)) {
		std::cout << std::endl << "Please enter only isogram word(word without repeating letter). " << std::endl;
		return EWordStatus::NotIsogramm;
	}
	else if (value.length() == GetGeneratedWordLength()){
		return EWordStatus::OK;
	}
	else {
		return EWordStatus::InvalidValue;
	}
}

bool FBullCowGame::isGuessRight(FString value) const
{
	ToLowerCase(value);
	return  value == GeneratedWord;
}

FString FBullCowGame::GetUserGuess()
{
	//Get user input for gussed word
	FString guessedWord = "";
	do{
		std::cout << std::endl << std::endl << "Please guess the " << GetGeneratedWordLength() 
			<< " letter isogram that I have generated :(" << CurrentAttempt << " of " << MAX_ATTEMPT_LIMIT << ")";
		getline(std::cin, guessedWord);
	} while (isGuessValid(guessedWord) != EWordStatus::OK);
	ToLowerCase(guessedWord);
	return guessedWord;
}

//TO DO generate a random word
void FBullCowGame::GenerateNewWord()
{
	GeneratedWord = "help";
}

bool FBullCowGame::HasNumber(FString value) const
{
	return std::any_of(value.begin(), value.end(), ::isdigit);
}

bool FBullCowGame::IsIsogram(FString value) const
{
	TMap<char, bool> map;
	for (auto tempC : value) {
		if (tempC > 'z') {
			tempC -= ('Z' - 'z');
		}
		if (map[tempC]) {
			return true;
		}
		map[tempC] = true;
	}
	return false;
}

void FBullCowGame::ToLowerCase(FString &value) const
{
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);
}

BullCowCount FBullCowGame::submitValidGuess(FString value)
{
	//Check bulls and cows count
	BullCowCount count;
	CurrentAttempt++;
	if (isGuessValid(value) != EWordStatus::OK) {
		return count;
	}
	for (int32 i = 0; i < GetGeneratedWordLength(); i++) {
		if (value[i] == GeneratedWord[i]) {
			count.Bulls++;
		}
		else if (GeneratedWord.find(value[i]) != FString::npos) {
			count.Cows++;
		}
	}
	return count;
}
