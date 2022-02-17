// bayes.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include "classifier.h"
using namespace std;

  // ------------------ //
  //  Helper functions  //
  // ------------------ //

vector<string> parse(string input){
  vector<string> output;
  stringstream s(input);
  string word;
  while(getline(s, word, ',')){
    output.push_back(word);
  }
  return output;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argv, char** argc){
  
  // --------------------------------- //
  //  Proccess command line arguments  //
  // --------------------------------- //
  
  if(argv != 3){
    cout << "Please provide 2 file names" << endl;
    exit(1);
  }

  ifstream fileTraining(argc[1]);
  if(fileTraining.fail()){
    cout << "Could not open file " << argc[1]  << endl;
    exit(1);
  }

  ifstream fileTesting(argc[2]);
  if(fileTesting.fail()){
    cout << "Could not open file " << argc[2]  << endl;
    exit(1);
  }
  
  // ------------------------------ //
  //  Read training data from file  //
  // ------------------------------ //

  vector<string> data;
  Classifier naive_bayes;
  string line;
  while (getline(fileTraining, line) && (line.length() > 0)){
    data = parse(line);
    naive_bayes.insert(data);
  }
  
  fileTraining.close();

  // --------------------------- //
  //  Train algorithm with data  //
  // --------------------------- //

  naive_bayes.train();
  
  // -------------------------------- //
  //  Apply algorithm to testing set  //
  // -------------------------------- //
  
  int label;
  float accuracy = 0.0;
  int total = 0;
  
  while (getline(fileTesting, line) && (line.length() > 0)){
    data = parse(line);
    label = naive_bayes.predict(data);
    if(stoi(data[11]) == label){
      accuracy++;
    }
    total++;
    cout << label << endl;
  }
  
  //cout << accuracy/total << endl;
    
  fileTesting.close();
  
  return 0;
}
