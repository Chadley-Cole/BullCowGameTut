// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    GetValidWords(Words);
    SetupGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is: %i."), GetValidWords(Words).Num());
    // :: is know as a Scope Resolution operator
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); //Debug line

    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // If game is over then do ClearScreen() and then SetupGame()
    // else Checking PlayerGuess
    
    //Checking PlayerGuess
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else //Checking PlayerGuess
    {
        ProcessGuess(Input);  
    }   
}
void UBullCowCartridge::SetupGame()
{
    //Welcome the Player
    PrintLine(TEXT("Welcome to the BullCow Game!"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Your lives are: %i."), Lives);
    PrintLine(TEXT("Type in your guess and\npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }
    
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }

    //Check if Isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    //Remove Life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    //Check if lives > 0
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no more lives!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    //Show the player Bulls and Cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
            return false;
            }
        }
    }
    return true;
    // For each letter.
    // Start at element [0].
    // Compare against the next letter.
    // Until we reach [Word.Len() -1].
    // If any return the same return false.
}
TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word)) 
        {
            ValidWords.Emplace(Word);
        }
    }
     return ValidWords;
}