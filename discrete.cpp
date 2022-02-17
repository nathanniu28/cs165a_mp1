// discrete.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "discrete.h"
using namespace std;

DiscreteVariable::DiscreteVariable(){
  total = 0;
  male_total = 0;
  female_total = 0;
  male_yes = 0;
  female_yes = 0;
}

DiscreteVariable::~DiscreteVariable(){
}

void DiscreteVariable::insert(string value, int label){
  total++;
  if(label == 0){
    if(value == "M"){
      male_total++;
    }
    if(value == "F"){
      female_total++;
    }
  }
  else{
    if(value == "M"){
      male_total++;
      male_yes++;
    }
    if(value == "F"){
      female_total++;
      female_yes++;
    }
  }
}

float DiscreteVariable::probability(string value, int label){
    if(label == 0){
      // proability of male given no
      if(value == "M")
	return (male_total - male_yes) / (male_total - male_yes + female_total - female_yes);
      // probability of female given no
      if(value == "F")
	return (female_total - female_yes) / (male_total - male_yes + female_total - female_yes);;
    }
    else{
      // probability of male given yes
      if(value == "M")
	return male_yes / (male_yes + female_yes);
      // probability of female given yes
      if(value == "F")
	return female_yes / (male_yes + female_yes);
    }
    return 0.0;
}

void DiscreteVariable::out(){
  /*
    cout << total << endl;
    cout << male_total << " " << male_yes << endl;
    cout << female_total << " " << female_yes << endl;
    cout << probability("M", 0) << endl;
    cout << probability("M", 1) << endl;
    cout << probability("F", 0) << endl;
    cout << probability("F", 1) << endl << endl;
  */
}
