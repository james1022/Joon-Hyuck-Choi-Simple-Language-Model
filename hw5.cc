/*
 * Homework5, 600.120 Spring 2015
 * hw5.cc
 * Name: Joon Hyuck Choi
 * Date: Mar 29, 2015
 * Assignment 5
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:05 03/29/2015
 */

#include "lang.h"

int main() {

  //seed the random number generator with the current time
  srand(time(NULL));

  //vector to store the original input text
  vector<string> line;
  line.reserve(3000);
  //token to store each piece of the input string
  string token;

  //take stdin and pass each token into function readText
  cout << "Please enter a text: ";
  readText("<START>", line); //put <START> at beginning
  while (cin >> token) {
    readText(token, line);
  } //jumps out when user presses ctrl+d
  readText("<END>", line); //put <END> at end

  LanguageModel m1;
  updateLM(m1, line);

  //vector to store the randomly generated string
  vector<string> randomSentence;
  randGenText(m1.uOM, randomSentence, "<START>");

  //print the randomly generated string
  printText(randomSentence);

  return 0;
} //end main()
