/*
 * Homework5, 600.120 Spring 2015
 * lang.h
 * Name: Joon Hyuck Choi
 * Date: Mar 29, 2015
 * Assignment 5
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:10 03/29/2015
 */

#include <unordered_map>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::string;
using std::list;
using std::unordered_map;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::vector;

typedef struct {
  list<string> wordList;
  map<string, list<string>> uOM;
  unordered_map<string, int> counter;
  map<string, int> pairCounter;
} LanguageModel;

/* Each function's functionality is explained in lang.cc*/

void readText(string, vector<string>&);

void updateLM(LanguageModel&, vector<string>);

void randGenText(map<string, list<string>>, vector<string>&, string);

void printText(vector<string>);
