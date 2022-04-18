#include <iostream>
#include <string_view>
#include <string>
#include<stdlib.h>
#include<fstream>
#include<time.h>
#include<vector>
#include<cstring>
using namespace std;

string guessMe = "";
int numberOfLetters = 0;
string guesses = "";
string currentProgress = "";
const int deadCount = 10;
int wrongCount = 0;
bool isWordGuessed = false;
int lettersRight = 0;


void getWord()
{
    string line;
    vector<string> lines;

    srand(time(0));

    //input file stream
    ifstream file("hangmanWords.txt");

    //count number of total lines in the file and store the lines in the string vector
    int total_lines = 0;
    while (getline(file, line))
    {
        total_lines++;
        lines.push_back(line);
    }

    //generate a random number between 0 and count of total lines
    int random_number = rand() % total_lines;



    //fetch the line where line index (starting from 0) matches with the random number

    guessMe = lines[random_number];
    numberOfLetters = guessMe.length();

    
}
string guessLetter() {
    string resp;
    cout << "Guess a letter!";
    cin >> resp;
    resp = tolower(resp[0]);
    return resp;
}
void initializeProgress() {
    currentProgress = "";
    int places = guessMe.length();
        for (int n = 0; n < places;n++) {
            currentProgress.push_back('_');
        }
}
void resetGuesses() {
    guesses = "";
}
void setupScoring() {
    wrongCount = 0;
    lettersRight = 0;
}
void initializeGame() {
    getWord();
    initializeProgress();
    resetGuesses();
    setupScoring();
    isWordGuessed = false;

}
void update() {
    system("cls");
    cout << wrongCount << " out of " << deadCount << " attempts\n";
    cout << "You've guessed " << lettersRight << " out of " << numberOfLetters << " letters right!\n";
    cout << "Letters guessed: " << guesses << "\n";
    cout << currentProgress << "\n";
}
void checkGuess(string guess) {
    int places = guessMe.length();
    guesses.push_back(guess[0]);
        bool isGuessed = false;
        for (int i = 0; i < places; i++) {
            if (guess[0] == guessMe[i]) {
                currentProgress[i] = guess[0];
                isGuessed = true;
                lettersRight++;
            }
        }
        if (!(isGuessed)) {
            wrongCount++;
            cout << "Uh oh! " << guess << " isn't in the word!\n";
            update();
        }
        if ((isGuessed) && (lettersRight == numberOfLetters)) {
            isWordGuessed = true;
            cout << "Congratulations! You solved it! The word was " << guessMe <<"\n";
            
        }
        if ((isGuessed) && !(lettersRight == numberOfLetters)) {
            cout << "You're right!! " << guess << " is in the word!\n";
            update();
        }
}
int main()
{
    while (true)
    {
        string resp;
        cout << "Welcome to Hangman! Would you like to start a new game? (Y)es or (N)o?: ";
        cin >> resp;
        resp = tolower(resp[0]);
        if (resp == "n") 
        {
            break;
        }
        
        else if (resp == "y") 
        {
            initializeGame();
            update();
                while (true){
                    if ((wrongCount < deadCount) && !(isWordGuessed)) {
              
                        string guess = guessLetter();
                        checkGuess(guess);
                    }
                    else if (wrongCount == deadCount) {
                        string pass;
                        cout << "Oops, you lose!\n";
                        cout << "press any key to return to main menu";
                        system("pause");
                        system("cls");
                        main();
                    }
                    else if (isWordGuessed) {
                        string pass;
                        cout << "Congratulations you win!\n";
                        cout << "press any key to return to main menu";
                        system("pause");
                        system("cls");
                        main();
                    }
                }
        }
    }

    
}