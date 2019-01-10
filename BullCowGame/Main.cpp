#include "FBullCowGame.h"

constexpr int MAX_WORD_LENGTH = 5;
constexpr int MAX_ATTEMPT_LIMIT = 5;

using FText = FString;
using int32 = int;

FText playerName;
FText generatedWord;int32 currentAttempt;

void printIntro();
void playGame();
bool playAgain();
FBullCowGame BCGame;
int main() {
	do {
		printIntro();
		playGame();
	} while (playAgain());
	std::cout << std::endl;
	return 0;
}

void playGame()
{
	FText guessedWord;
	BCGame.Reset();
	//Loop through and get user guess until he get the right answer or user exceeds max attempts
	while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		guessedWord = BCGame.GetUserGuess();
		std::cout << std::endl << "Your guessed word (" << guessedWord <<")";
		if(BCGame.isGuessRight(guessedWord)){
			std::cout << std::endl;
			if (currentAttempt == 1) {
				std::cout << "Congratulations it's a bulls eye, you have gussed random generated word ('" << guessedWord << "') in 1st attempt.";
			}
			else {
				std::cout << "Congratulations you have successfully gussed the random generated word ('" << guessedWord << "') in " << (BCGame.GetCurrentTry()) << " attempts.";
			}
			break;
		} else {
			BullCowCount count = BCGame.submitValidGuess(guessedWord);
			std::cout << " has " << count.Bulls << " bulls and " << count.Cows << " cows.";
			if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) {
				std::cout << std::endl << "Sorry you are out of chances.";
			}
		}
		std::cout << std::endl;
	}
}

bool playAgain() {
	// Chech if player want to replay
	char userInput;
	std::cout << std::endl << "would you like to try again: (Y/N)";
	std::cin >> userInput;
	userInput = tolower(userInput);
	if (userInput != 'y' && userInput != 'n') {
		std::cout << std::endl << "Please enter either 'Y' or 'N'.";
		return playAgain();
	}
	std::cin.ignore(INT_MAX,'\n');
	return userInput == 'y';
}

void printIntro() {
	// Print the intro screen
	std::cout << "Hello there welcome to Bulls and Cows fun word game." << std::endl;
}