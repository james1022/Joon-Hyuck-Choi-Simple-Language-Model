/*
 * Homework5, 600.120 Spring 2015
 * README.txt
 * Name: Joon Hyuck Choi
 * Date: Mar 29, 2015
 * Assignment 5
 * Phone: 667-239-0288
 * BB login: jchoi100
 * email: jchoi100@jhu.edu
 * Updated: 16:39 03/29/2015
 */
===========================================================================================
The .zip file includes:

     1) lang.h
     2) lang.cc
     3) hw5.cc
     4) testLang.cc
     5) Makefile
     6) README.txt

===========================================================================================

How to compile testLang:

       (Using Makefile): make testLang
       (On command line): g++ -std=c++11 -Wall -Wextra -pedantic -o testLang -O testLang.cc

===========================================================================================

How to run testLang:

       (Using Makefile): make test
       (On command line): ./testLang

===========================================================================================

How to compile hw5:

       (Using Makefile): make lang.o
       	      		 make hw5.o
			 make hw5 (or typing make hw5 from the beginning will work as well)
       (command ln): g++ -std=c11++ -Wall -Wextra -pedantic -o hw5 -O lang.h lang.cc hw5.cc

===========================================================================================

How to run hw5:

       (On command line): ./hw5

===========================================================================================

Comments:

   testLang.cc
	The tester file contains 7 tests:
	1: tests readText()
	2: tests first functionality of updateLM()
	3: tests second functionality of updateLM()
	4: tests third functionality of updateLM()
	5: tests fourth functionality of updateLM()
	6: tests the counting functionaliy of all parts of updateLM() once more
	7: tests randGenText()

===========================================================================================
