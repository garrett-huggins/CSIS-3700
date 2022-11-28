#include <iostream>
#include <fstream>
#include "linearlist.h"
#include "queue.h"

Queue<int> queue;
      
struct WordNode {
  string word;
  int ptr;
  LinearList<int> linkedWords;
};

WordNode wordList[5757];

int search(string);
int hammingDistance(string, string);
void genAdjacency();
void genLadder(int, int);

int main() {
    std::fstream wordsFile; 

    wordsFile.open("sgb-words.txt", ios::in);

    if (wordsFile.is_open()) {
      string line;
      int i = 0;
      while ( getline (wordsFile,line) ) {
        wordList[i].word = line;
        wordList[i].ptr = -1;

        i++;
      }
      wordsFile.close();
    }

    genAdjacency();

    WordNode word1, word2;
    std::cin >> word1.word >> word2.word;

    word1.ptr = search(word1.word);
    word2.ptr = search(word2.word);

    if (word1.ptr == -1) {
      std::cout << "word 1 not found" << std::endl;
      return 0;
    }
    if ( word2.ptr == -1) {
      std::cout << "word 2 not found" << std::endl;
    }

    genLadder(word1.ptr, word2.ptr);
    
    return 0;
}

int search(string w) {
  for (int i = 0; i < 5757; i++) {
    if (wordList[i].word == w) {
      return i;
    }
  }
  return -1;
}

int hammingDistance(string w1, string w2) {
  int count = 0;
  for (int i = 0; i < 5; i++) {
    if (w1[i] != w2[i]) {
      count++;
    }
  }
  return count;
}

void genAdjacency() {
  for (int i = 0; i < 5757; i++) {
    for (int j = 0; j < 5757; j++) {
      if (hammingDistance(wordList[i].word, wordList[j].word) == 1) {
        wordList[i].linkedWords.insert(wordList[i].linkedWords.size(), j);
      }
    }
  }
}

void genLadder(int w1, int w2) {
  int w,v;

  queue.enqueue(w2);

  while (!queue.isEmpty()) {
    w = queue.dequeue();

    for (int i = 0; i < wordList[w].linkedWords.size(); i++) {
      v = wordList[w].linkedWords[i];

      if (wordList[v].ptr == -1 && v != w2) {
        wordList[v].ptr = w;

        queue.enqueue(v);
      }
    }
  }

  if (wordList[w1].ptr != -1) {
    std::cout << wordList[w].word << std::endl;
    w = wordList[w1].ptr;

    while (w != -1) {
      std::cout << wordList[w].word << std::endl;
      w = wordList[w].ptr;
    }
  } else {
    std::cout << "No ladder exists" << std::endl;
  }
}