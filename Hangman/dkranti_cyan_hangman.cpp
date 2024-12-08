Dipal Kranti(dkranti@student.ysu.edu)
Sandesh rai(srai02@student.ysu.edu)
#include <iostream> 
#include <iomanip> 
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <fstream> 
#include <string>
#include <vector>
using namespace std;

void displayGallows(int incorrectGuesses) {
  cout << endl;
  switch (incorrectGuesses) {
    case 0:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 1:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 2:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |       |" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 3:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |      /|" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 4:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |      /|\\" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 5:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |      /|\\" << endl;
      cout << "     |       |" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 6:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |      /|\\" << endl;
      cout << "     |       |" << endl;
      cout << "     |      /" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    case 7:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |      /|\\" << endl;
      cout << "     |       |" << endl;
      cout << "     |      / \\" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
    default:
      cout << "     ---------" << endl;
      cout << "     |       |" << endl;
      cout << "     |       O" << endl;
      cout << "     |      /|\\" << endl;
      cout << "     |       |" << endl;
      cout << "     |      / \\" << endl;
      cout << "     |       " << endl;
      cout << "     |       " << endl;
      cout << "    -" << endl;
      cout << endl;
      break;
  }
}

void displayBlanks(const string& hiddenWord) {
  for (char c : hiddenWord) {
    if (c != ' ') {
      cout << "_ ";
    } else {
      cout << "  ";
    }
  }
  cout << endl;
}

int main() {
  srand(time(0));
  string word;
  string hint;
  string guessedCharacters = "";
  int incorrectGuesses = 0;
  bool gameWon = false;
  bool playAgain = true;
  vector<string> words;
  vector<string> hints;

  ifstream dataFile("data.csv");
  if (dataFile.is_open()) {
    while (getline(dataFile, word, ',') && getline(dataFile, hint)) {
      words.push_back(word);
      hints.push_back(hint);
    }
    dataFile.close();
  } else {
    cout << "Error: Unable to open data file." << endl;
    return 1;
  }

  while (playAgain) {
    int randomIndex = rand() % words.size();
    word = words[randomIndex];
    hint = hints[randomIndex];
    string hiddenWord(word.length(), '_');

    guessedCharacters = "";
    incorrectGuesses = 0;
    gameWon = false;

    while (!gameWon && incorrectGuesses < 7) {
      displayGallows(incorrectGuesses);
      cout << "Hint: " << hint << endl;
      displayBlanks(hiddenWord);
      cout << "Guessed Characters: " << guessedCharacters << endl;

      char guess;
      cout << "Enter a letter: ";
      cin >> guess;
      guess = toupper(guess);

      if (guessedCharacters.find(guess) != string::npos) {
        cout << "You already guessed that letter. Try again." << endl;
        continue;
      }

      guessedCharacters += guess;
      bool correctGuess = false;

      for (size_t i = 0; i < word.length(); i++) {
        if (toupper(word[i]) == guess) {
          hiddenWord[i] = word[i];
          correctGuess = true;
        }
      }

      if (!correctGuess) {
        incorrectGuesses++;
      }

      if (hiddenWord == word) {
        gameWon = true;
      }
    }

    displayGallows(incorrectGuesses);
    if (gameWon) {
      cout << "Congratulations! You guessed the word: " << word << endl;
    } else {
      cout << "You lose! The word was: " << word << endl;
    }

    char playAgainResponse;
    cout << "Play again? (y/n): ";
    cin >> playAgainResponse;
    playAgain = (tolower(playAgainResponse) == 'y');
  }

  return 0;
}