/*
 * Homework5, 600.120 Spring 2015
 * testLang.cc
 * Name: Joon Hyuck Choi
 * Date: Mar 29, 2015
 * Assignment 5
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:26 03/29/2015
 */

#include "lang.h"
#include <cassert>
#include <cstdio>

using std::fprintf;
using std::fclose;
using std::fopen;

/**
 * Copied over from HW2 sample file.
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match.
 */
bool fileeq(char lhsName[], char rhsName[]) {
    FILE* lhs = fopen(lhsName, "r");
    FILE* rhs = fopen(rhsName, "r");

    // don't compare if we can't open the files
    if (!lhs || !rhs) return false;

    bool match = true;
    // read until both of the files are done or there is a mismatch
    while (!feof(lhs) || !feof(rhs)) {
        if (feof(lhs) ||                  // lhs done first
            feof(rhs) ||                  // rhs done first
            (fgetc(lhs) != fgetc(rhs))) { // chars don't match
            match = false;
            break;
        }
    }
    fclose(lhs);
    fclose(rhs);
    return match;
} //end fileeq()

/**
 * Tests the function readText().
 * The function takes in a string token, vector reference
 * and saves the tokens in a single vector.
 */
void test_readText() {
  LanguageModel m1;
  vector<string> line;
  readText("<START>", line);
  readText("I", line);
  readText("am", line);
  readText("writing", line);
  readText("this", line);
  readText("test", line);
  readText("to", line);
  readText("see", line);
  readText("the", line);
  readText("result", line);
  readText("<END>", line);

  assert(line.size() == 11);
  assert(line.at(0) == "<START>");
  assert(line.at(1) == "I");
  assert(line.at(2) == "am");
  assert(line.at(3) == "writing");
  assert(line.at(4) == "this");
  assert(line.at(5) == "test");
  assert(line.at(6) == "to");
  assert(line.at(7) == "see");
  assert(line.at(8) == "the");
  assert(line.at(9) == "result");
  assert(line.at(10) == "<END>");
}

/**
 * Tests the first part of updateLM().
 * The first part of updateLM() merely fills in 
 * the original input text string token by token
 * in a list of strings.
 */
void test_updateLM_1() {
  LanguageModel m1;
  vector<string> line;
  readText("<START>", line);
  readText("I", line);
  readText("am", line);
  readText("writing", line);
  readText("this", line);
  readText("test", line);
  readText("to", line);
  readText("see", line);
  readText("the", line);
  readText("result", line);
  readText("<END>", line);

  updateLM(m1, line);

  char e1[14] = "expected1.txt";
  FILE* expected1 = fopen(e1, "w");
  fprintf(expected1, "<START>\n");
  fprintf(expected1, "I\n");
  fprintf(expected1, "am\n");
  fprintf(expected1, "writing\n");
  fprintf(expected1, "this\n");
  fprintf(expected1, "test\n");
  fprintf(expected1, "to\n");
  fprintf(expected1, "see\n");
  fprintf(expected1, "the\n");
  fprintf(expected1, "result\n");
  fprintf(expected1, "<END>\n");
  fclose(expected1);

  char a1[12] = "actual1.txt";
  FILE* actual1 = fopen(a1, "w");
  typedef list<string>::iterator litr;
  litr end = m1.wordList.end();
  for (litr ptr = m1.wordList.begin(); ptr != end; ptr++) {
    fprintf(actual1, "%s\n", (*ptr).c_str());
  }
  fclose(actual1);

  assert(fileeq(e1, a1));
}

/**
 * Tests the second part of updateLM().
 * The second part of updateLM() counts how many 
 * different pairs there are.
 */
void test_updateLM_2() {
  LanguageModel m1;
  vector<string> line;
  readText("<START>", line);
  readText("I", line);
  readText("am", line);
  readText("writing", line);
  readText("this", line);
  readText("test", line);
  readText("to", line);
  readText("see", line);
  readText("the", line);
  readText("result", line);
  readText("<END>", line);

  updateLM(m1, line);

  char e2[14] = "expected2.txt";
  FILE* expected2 = fopen(e2, "w");
  fprintf(expected2, "<START> I (1)\n");
  fprintf(expected2, "I am (1)\n");
  fprintf(expected2, "am writing (1)\n");
  fprintf(expected2, "result <END> (1)\n");
  fprintf(expected2, "see the (1)\n");
  fprintf(expected2, "test to (1)\n");
  fprintf(expected2, "the result (1)\n");
  fprintf(expected2, "this test (1)\n");
  fprintf(expected2, "to see (1)\n");
  fprintf(expected2, "writing this (1)\n");
  fclose(expected2);

  char a2[12] = "actual2.txt";
  FILE* actual2 = fopen(a2, "w");
  typedef map<string, int>::iterator mitr;
  mitr end = m1.pairCounter.end();
  for (mitr ptr = m1.pairCounter.begin(); ptr != end; ptr++) {
    fprintf(actual2, "%s ", (ptr->first).c_str());
    fprintf(actual2, "(%d)\n", (ptr->second));
  }
  fclose(actual2);

  assert(fileeq(e2, a2));
}

/**
 * Tests the third part of updateLM().
 * The third part of updateLM() takes each token of
 * string in the input text and maps the token
 * with its number of occurrences in the original text.
 */
void test_updateLM_3() {
  LanguageModel m1;
  vector<string> line;
  readText("<START>", line);
  readText("I", line);
  readText("am", line);
  readText("writing", line);
  readText("this", line);
  readText("test", line);
  readText("to", line);
  readText("see", line);
  readText("the", line);
  readText("result", line);
  readText("<END>", line);

  updateLM(m1, line);

  char e3[14] = "expected3.txt";
  FILE* expected3 = fopen(e3, "w");
  fprintf(expected3, "<START> occurs 1 time(s).\n");
  fprintf(expected3, "I occurs 1 time(s).\n");
  fprintf(expected3, "writing occurs 1 time(s).\n");
  fprintf(expected3, "am occurs 1 time(s).\n");
  fprintf(expected3, "this occurs 1 time(s).\n");
  fprintf(expected3, "the occurs 1 time(s).\n");
  fprintf(expected3, "to occurs 1 time(s).\n");
  fprintf(expected3, "<END> occurs 1 time(s).\n");
  fprintf(expected3, "test occurs 1 time(s).\n");
  fprintf(expected3, "result occurs 1 time(s).\n");
  fprintf(expected3, "see occurs 1 time(s).\n");
  fclose(expected3);

  char a3[12] = "actual3.txt";
  FILE* actual3 = fopen(a3, "w");
  typedef unordered_map<string, int>::iterator umitr;
  umitr end = m1.counter.end();
  for (umitr ptr = m1.counter.begin(); ptr != end; ptr++) {
    fprintf(actual3, "%s occurs %d time(s).\n", (ptr->first).c_str(), (ptr->second));
  }
  fclose(actual3);

  assert(fileeq(e3, a3));
}

/**
 * Tests the fourth part of updateLM().
 * The fourth part of updateLM() takes the input text
 * token by token and creates a list of strings that
 * follow a particular token for each token.
 */
void test_updateLM_4() {
  LanguageModel m1;
  vector<string> line;
  readText("<START>", line);
  readText("I", line);
  readText("am", line);
  readText("writing", line);
  readText("this", line);
  readText("test", line);
  readText("to", line);
  readText("see", line);
  readText("the", line);
  readText("result", line);
  readText("<END>", line);

  updateLM(m1, line);

  char e4[14] = "expected4.txt";
  FILE* expected4 = fopen(e4, "w");
  fprintf(expected4, "<START> is followed by I\n");
  fprintf(expected4, "I is followed by am\n");
  fprintf(expected4, "am is followed by writing\n");
  fprintf(expected4, "result is followed by <END>\n");
  fprintf(expected4, "see is followed by the\n");
  fprintf(expected4, "test is followed by to\n");
  fprintf(expected4, "the is followed by result\n");
  fprintf(expected4, "this is followed by test\n");
  fprintf(expected4, "to is followed by see\n");
  fprintf(expected4, "writing is followed by this\n");
  fclose(expected4);

  char a4[12] = "actual4.txt";
  FILE* actual4 = fopen(a4, "w");
  typedef map<string, list<string>>::iterator mitr;
  mitr end = m1.uOM.end();
  for (mitr ptr = m1.uOM.begin(); ptr != end; ptr++) {
    fprintf(actual4, "%s is followed by ", (ptr->first).c_str());
    for (list<string>::iterator j = ptr->second.begin(); 
	 j != (ptr->second).end(); j++) {
      fprintf(actual4, "%s\n", (*j).c_str());
    }
  }
  fclose(actual4);

  assert(fileeq(e4, a4));
}

/**
 * Performs another set of tests to check that the
 * functions count correctly.
 * There are three blocks of assert statements below:
 * the first for testing LanguageModel's counter,
 * the second for testing its pairCounter, and
 * the third for testing its uOM.
 */
void overallCountTest() {
  //Idea borrowed from course website.
  LanguageModel m2;
  vector<string> line2 = {"he", "liked", "that", "he", "ate", "the", "sandwich", "he", "liked"};

  updateLM(m2, line2);

  assert(m2.counter["he"] == 3);
  assert(m2.counter["liked"] == 2);
  assert(m2.counter["that"] == 1);
  assert(m2.counter["ate"] == 1);
  assert(m2.counter["the"] == 1);
  assert(m2.counter["sandwich"] == 1);

  assert(m2.pairCounter["he liked"] == 2);
  assert(m2.pairCounter["liked that"] == 1);
  assert(m2.pairCounter["that he"] == 1);
  assert(m2.pairCounter["he ate"] == 1);
  assert(m2.pairCounter["ate the"] == 1);
  assert(m2.pairCounter["the sandwich"] == 1);
  assert(m2.pairCounter["sandwich he"] == 1);

  assert(m2.uOM["he"].size() == 3);
  assert(m2.uOM["liked"].size() == 1);
  assert(m2.uOM["that"].size() == 1);
  assert(m2.uOM["ate"].size() == 1);
  assert(m2.uOM["the"].size() == 1);
  assert(m2.uOM["sandwich"].size() == 1);
}

/**
 * Tests randGenText().
 * Since it is hard to actually compare an
 * expected random text and the actual random text,
 * the best we can do is test the common properties
 * of the randomly generated text.
 * Namely, the randomly generated text's length
 * must be greater than 1, its first and last strings
 * are predetermined by the input text, and it must 
 * not be an empty string.
 */
void test_randGenText() {
  LanguageModel m1;
  vector<string> line;
  readText("<START>", line);
  readText("I", line);
  readText("am", line);
  readText("writing", line);
  readText("this", line);
  readText("test", line);
  readText("to", line);
  readText("see", line);
  readText("the", line);
  readText("result", line);
  readText("<END>", line);

  updateLM(m1, line);

  vector<string> randomSentence;
  randGenText(m1.uOM, randomSentence, "<START>");

  assert(randomSentence.size() >= 1);
  assert(randomSentence.front() == "I");
  assert(randomSentence.back() == "result");
  assert(!randomSentence.empty());
}

/**
 * Driver main method for the tester.
 */
int main() {

  cout << "Running tests...." << endl << endl;

  cout << "   * Running test_readText()..." <<endl;
       test_readText();
  cout << "     Passed test_readText()" << endl << endl;;

  cout << "   * Running test_updateLM_1()..." <<endl;
       test_updateLM_1();
  cout << "     Passed test_updateLM_1()" << endl << endl;

  cout << "   * Running test_updateLM_2()..." <<endl;
       test_updateLM_2();
  cout << "     Passed test_updateLM_2()" << endl << endl;
  
  cout << "   * Running test_updateLM_3()..." <<endl;
       test_updateLM_3();
  cout << "     Passed test_updateLM_3()" << endl << endl;
  
  cout << "   * Running test_updateLM_4()..." <<endl;
       test_updateLM_4();
  cout << "     Passed test_updateLM_4()" << endl << endl;
  
  cout << "   * Running test_randGenText()..." <<endl;
       test_randGenText();
  cout << "     Passed test_randGenText()" << endl << endl;

  cout << "   * Running overallCountTest()..." <<endl;
       overallCountTest();
  cout << "     Passed overallCountTest()" << endl << endl;

  cout << "All tests passed!" << endl;

  return 0;
} //end main()
