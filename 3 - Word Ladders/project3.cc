#include <iostream>
#include <fstream>
#include "linearlist.h"
#include "queue.h"

// word struct    
struct WordNode {
  std::string word;
  int ptr;
  LinearList<int> adjacentWords;
};

// word queue handler
Queue<int> queue;

// list of words from file
WordNode wordList[5757];

// function prototypes
int search(std::string);
int hammingDistance(std::string, std::string);
void genLadder(int, int);

int main() {
  // sgb-words.txt file
  std::fstream wordsFile; 

  wordsFile.open("sgb-words.txt", ios::in);

  if (wordsFile.is_open()) {
    std::string line;
    int i = 0;

    // insert each word node into word list
    // initialize ptr to words to -1 (NULL)
    while ( getline (wordsFile,line) ) {
      wordList[i].word = line;
      wordList[i].ptr = -1; // does not point to any words yet

      i++;
    }
    wordsFile.close();
  }

  // find adjacent words
  // create a list of words with only 1 letter in difference (hamming distance == 1)
  for (int i = 0; i < 5757; i++) {
    for (int j = 0; j < 5757; j++) {
      if (hammingDistance(wordList[i].word, wordList[j].word) == 1) {
        wordList[i].adjacentWords.insert(wordList[i].adjacentWords.size(), j);
      }
    }
  }

  WordNode word1, word2;

  // get input
  std::cin >> word1.word >> word2.word;

  word1.ptr = search(word1.word);
  word2.ptr = search(word2.word);

  // check words are in list
  if (word1.ptr == -1) {
    std::cout << "first word not found" << std::endl;
    return 0;
  }
  if ( word2.ptr == -1) {
    std::cout << "second word not found" << std::endl;
    return 0;
  }

  // generate ladder
  genLadder(word1.ptr, word2.ptr);
  
  return 0;
}

// sequential search
int search(std::string w) {
  for (int i = 0; i < 5757; i++) {
    if (wordList[i].word == w) {
      return i;
    }
  }
  return -1;
}

// returns the number of different letters between 2 words
int hammingDistance(std::string w1, std::string w2) {
  int count = 0;
  for (int i = 0; i < 5; i++) {
    if (w1[i] != w2[i]) {
      count++;
    }
  }
  return count;
}

void genLadder(int w1, int w2) {
  // w1 and w2 are ptr's
  // must reference wordList at ptr to access word node

  int w,v;

  queue.enqueue(w2);

  while (!queue.isEmpty()) {
    w = queue.dequeue();

    // check each word in ladder list
    for (int i = 0; i < wordList[w].adjacentWords.size(); i++) {
      v = wordList[w].adjacentWords[i];

      if (wordList[v].ptr == -1 && v != w2) {
        wordList[v].ptr = w;

        queue.enqueue(v);
      }
    }
  }

  if (wordList[w1].ptr != -1) {
    std::cout << wordList[w1].word << std::endl;
    w = wordList[w1].ptr;

    while (w != -1) {
      std::cout << wordList[w].word << std::endl;
      w = wordList[w].ptr;
    }
  } else {
    std::cout << "no ladder exists" << std::endl;
  }
}