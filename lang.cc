/*
 * Homework5, 600.120 Spring 2015
 * lang.cc
 * Name: Joon Hyuck Choi
 * Date: Mar 29, 2015
 * Assignment 5
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:09 03/29/2015
 */

#include "lang.h"

/**
 * Takes in each piece of the input text and
 * stores it in the vector of strings.
 */
void readText(string token, vector<string>& vec) {
  vec.push_back(token);
}

/**
 * Updates the LanguageModel's components.
 * Each specific functionality is explained below in
 * each block of code.
 */
void updateLM(LanguageModel& m, vector<string> inputText) {

  //number of words in the original input text.
  int vecSize = (int) inputText.size();

  //fill a list with the original input text.
  //saves the info in LanguageModel's wordList.
  for (int i = 0; i < vecSize; i++) {
    m.wordList.push_back(inputText.at(i));
  }

  //counts how many different pairs there are.
  //saves the info in LanguageModel's pairCounter.
  for (int i = 0; i < vecSize - 1; i++) {
    string temp = inputText.at(i);
    temp += " ";
    temp += inputText.at(i + 1);
    m.pairCounter[temp]++;
  }

  //counts the occurrences of a single word.
  //saves the info in LanguageModel's counter.
  for (int i = 0; i < vecSize; i++) {
    string temp = inputText.at(i);
    m.counter[temp]++;
  }

  //makes a map of a particular word and the 
  //list of words that follow the word in the input text.
  //saves the info in LanguageModel's uOM.
  for (int i = 0; i < vecSize - 1; i++) {
    string temp = inputText.at(i);
    m.uOM[temp].push_back(inputText.at(i + 1));
  }

}

/**
 * Recursive function that generates a randomly generated text
 * based on the LanguageModel's map of strings to lists of strings.
 * The recursion ends when the code detects that the string is about to
 * add <END> to the last trail of the vector.
 */
void randGenText(map<string, list<string>> m, vector<string>& newText, string first) {
  typedef list<string>::iterator litr;
  litr beginL = m[first].begin();
  if (first == "<START>") {
    newText.push_back(*beginL);
    randGenText(m, newText, *beginL);
  } else { 
    int secondSize = m[first].size();
    int randomPosition = rand() % secondSize;
    int count = 0;
    litr secondBegin = m[first].begin();
    litr secondEnd = m[first].end();
    for (litr ptr = secondBegin; ptr != secondEnd; ptr++) {
      if (count == randomPosition) {
	if (*ptr == "<END>") {
	  return;
	} else {
	  newText.push_back(*ptr);
	  randGenText(m, newText, *ptr);
	}
	count++;
      } else {
	count++;
      }
    }
  }
}

/**
 * Prints a given vector of strings.
 */
void printText(vector<string> vec) {
  int lSize = (int) vec.size();
  for (int i = 0; i < lSize; i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}
