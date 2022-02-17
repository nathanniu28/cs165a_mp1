// classifier.cpp

#include <iostream>
#include "classifier.h"
using namespace std;

Classifier::Classifier(){
  // initializes the "Classifier" class
  total = 0;
  total_yes = 0;
}

Classifier::~Classifier(){
}

void Classifier::insert(vector<string> data){
  // organizes information in "data" and inserts the stored values into their appropriate data structures
  int label = stoi(data[11]);
  total++;
  if(label == 1)
    total_yes++;
  
  age.insert                       (stof(data[0]), label);
  gender.insert                    (data[1], label);
  height_cm.insert                 (stof(data[2]), label);
  weight_kg.insert                 (stof(data[3]), label);
  body_fat.insert                  (stof(data[4]), label);
  diastolic.insert                 (stof(data[5]), label);
  systolic.insert                  (stof(data[6]), label);
  grip_force.insert                (stof(data[7]), label);
  sit_and_bend_forward_cm.insert   (stof(data[8]), label);
  sit_up_count.insert              (stof(data[9]), label);
  broad_jump_cm.insert             (stof(data[10]), label);
}

void Classifier::train(){
  // prepares probability distributions
  //age.discretize();
  age.prepare();
  gender.out();
  height_cm.prepare();
  weight_kg.prepare();
  body_fat.prepare();
  diastolic.prepare();
  systolic.prepare();
  grip_force.prepare();
  sit_and_bend_forward_cm.prepare();
  sit_up_count.prepare();
  broad_jump_cm.prepare();

  //age.discretize()
  //sit_and_bend_forward_cm.discretize();

  age.discretize();
  //gender.out();
  height_cm.discretize();
  weight_kg.discretize();
  body_fat.discretize();
  diastolic.discretize();
  systolic.discretize();
  grip_force.discretize();
  sit_and_bend_forward_cm.discretize();
  sit_up_count.discretize();
  broad_jump_cm.discretize();
}

int Classifier::predict(vector<string> data){
  // compares probability of a "1" label to the probability of a "0" label, given the data; outputs the more likely outcome given the dataset 
  return likelihood(data, 1) > likelihood(data, 0);
}

float Classifier::likelihood(vector<string> data, int label){
  // computes conditional probability of outcome "label" given the information in "data"
  float probability =
    age.probability                       (stof(data[0]), label) *
    gender.probability                    (data[1], label)       *
    height_cm.probability                 (stof(data[2]), label) *
    weight_kg.probability                 (stof(data[3]), label) *
    body_fat.probability                  (stof(data[4]), label) *
    diastolic.probability                 (stof(data[5]), label) *
    systolic.probability                  (stof(data[6]), label) *
    grip_force.probability                (stof(data[7]), label) *
    sit_and_bend_forward_cm.probability   (stof(data[8]), label) *
    sit_up_count.probability              (stof(data[9]), label) *
    broad_jump_cm.probability             (stof(data[10]), label);
  
  if(label == 0)
    probability *= static_cast<float>(total - total_yes) / total;
  else
    probability *= static_cast<float>(total_yes) / total;

  //cout << probability << endl;
  return probability;
}
