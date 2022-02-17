// continuous.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "continuous.h"
using namespace std;

ContinuousVariable::ContinuousVariable(){
  for(int i = 0; i < 2; i++){
      total[i] = 0;
  }
  distribution_type = "default";
}

ContinuousVariable::ContinuousVariable(string type){
  for(int i = 0; i < 2; i++){
      total[i] = 0;
  }
  distribution_type = type; 
}

ContinuousVariable::~ContinuousVariable(){
}

void ContinuousVariable::insert(float value, int label){
  if(label == 0){
    if(data[0].empty()){
      minimum[0] = value;
      maximum[0] = value;
    }
    data[0].push_back(value);
    total[0]++;
    minimum[0] = min(minimum[0], value);
    maximum[0] = max(maximum[0], value);
  }
  else{
    if(data[1].empty()){
      minimum[1] = value;
      maximum[1] = value;
    }
    data[1].push_back(value);
    total[1]++;
    minimum[1] = min(minimum[1], value);
    maximum[1] = max(maximum[1], value);
  }
}

void ContinuousVariable::discretize(){
  for(int i = 0; i < 2; i++){
    
    // uniform distribution
    // W = 3.49*s*N^(-1/3)
    bin_size[i] = 3.49 * std_dev[i] * (1/cbrt(total[i]));
    num_bins[i] = (maximum[i] - minimum[i]) / bin_size[i];
    /*
    cout << minimum[i] << " " << maximum[i] << endl;
    cout << bin_size[i] << " " << num_bins[i] << endl;
    cout << endl;
    */
    
    // quartile distribution
    /*
    num_bins[i] = ceil(cbrt(total[i]));
    sort(data[i].begin(), data[i].end());
    //iqr_ranges[i] = new float[num_bins[i]];
    //histogram[i] = new int[num_bins[i]];

    int index;
    cout << minimum[i] << " " << maximum[i] << endl;
    cout << num_bins[i] << endl << endl;
    for(int j = 1; j < num_bins[i]; j++){
      index = floor((j * total[i]) / num_bins[i]);
      cout << j << " " << data[i].at(index) << endl;
      *iqr_ranges[j] = data[i].at(index);
      iqr_ranges[i].push_back(data[i].at(index));
    }
    cout << endl;
    for(int j = 0; j < total[i]; j++){
      
    }
    */

    //sort(data[i].begin(), data[i].end());
    num_bins[i]++; // add one more for up to including max element
    for(int j = 0; j < num_bins[i]; j++){
      histogram[i].push_back(0);
    }
    //cout << histogram[i].size()  << endl;
    // value = bin_size*index + min
    // index 0 correlates to values greater than minimum
    // and less than minimum + bin_size
    // index = floor((value - min) / bin_size)
    // if index < 0, else
    // if index >= num_bins, else

    // insert into histogram
    int index;
    for(int j = 0; j < total[i]; j++){
      index = floor((data[i].at(j) - minimum[i]) / bin_size[i]);
      if(index < 0){
	cout << "less" << endl;
      }
      else if(index >= num_bins[i]){
	cout << "more" << endl;
      }
      else{
	histogram[i][index] = histogram[i][index] + 1;
      }
    }
    // convert histogram to probabilities
     for(int j = 0; j < num_bins[i]; j++){
       /*
       if(histogram[i][j] == 0)
	 histogram[i][j] = 1;
       histogram[i][j] = histogram[i][j] / total[i];
       */
    }
     
     //probabilityInterpolation(24.5, 1);
  }
}

void ContinuousVariable::normalizeData(){
}

void ContinuousVariable::prepare(){
  calculateMean();
  calculateStdDev();
}

float ContinuousVariable::probability(float value, int label){
  //return probabilityInterpolation(value, label);
  if(distribution_type == "guassian")
    return probabilityGuassian(value, label);
  else if(distribution_type == "interpolation")
    return probabilityInterpolation(value, label);
  else
    return probabilityGuassian(value, label);
}

float ContinuousVariable::probabilityGuassian(float value, int label){
  // assume guassian distribution for all continuous variables
  float term1;
  float term2;
  if(label == 0){
    term1 = 1 / (sqrt(2 * M_PI) * std_dev[0]);
      term2 = exp(-pow(value - mean[0],2)/(2*pow(std_dev[0],2)));
  }
    else{
      term1 = 1 / (sqrt(2 * M_PI) * std_dev[1]);
      term2 = exp(-pow(value - mean[1],2)/(2*pow(std_dev[1],2)));
    }
  return term1 * term2;
}

float ContinuousVariable::probabilityInterpolation(float value, int label){
  /*
  // print
  for(int i = 0; i < num_bins[1]; i++){
    cout << histogram[1].at(i) << " ";
  }
  cout << endl;
  */

  int raw_index = (value - minimum[label]) / bin_size[label];
  int index = floor(raw_index);
  //int index = floor((value - minimum[label]) / bin_size[label]);
  //cout << index << endl;

  // Interpolate
  if(index < 0){
    // interpolate from 1 / total to min
    //cout << "less" << endl;
    return 1 / static_cast<float>(total[label]);
  }
  else if(index >= num_bins[label] - 1){
    // interpolate from 1 / total to max
    //cout << "more" << endl;
    return 1 / static_cast<float>(total[label]);
  }
  else{
    // or straight up just return the probability for now
    //cout << histogram[label][index] << endl;
    return histogram[label][index];

    // interpolation
    //float slope = (histogram[label][index + 1] - histogram[label][index]) / bin_size[label];
    //return histogram[label][index] + (value - histogram[label][index]) * slope;
    return histogram[label][index] + (raw_index - index) * (histogram[label][index + 1] - histogram[label][index]) / (index + 1 - index);
  }
  
  //return 0.0;
}

/*
float ContinuousVariable::probabilityDiscrete(float value, int label){
  // returns probability for quantile discretized data
  
  int index;
  if(value < iqr_ranges[label][1])
    index = 0;
  else if(value > iqr_ranges[label][num_bins[label] - 1])
    index = num_bins[label] - 1;
  else{
    for(int i = 2; i < num_bins[label] - 1; i++){
      if(value < iqr_ranges[label][i]){
	index = i - 1;
	break;
      }
    }
  }
  cout << index << endl;
  return 0.0;
  
  // return histogram[label][i];
  return 0.0;
}
*/

void ContinuousVariable::out(){
  /*
    for(int i = 0; i < 8; i++){
    cout << data_0.at(i) << " ";
    }
    cout << endl;
    for(int i = 0; i < 8; i++){
    cout << data_1.at(i) << " ";
    }
    cout << endl;
  */
  //std_dev =
  //  cout << std_dev << endl;
  /*
    calculateMean();
    calculateStdDev();
    cout << mean_0 << endl;
    cout << std_dev_0 << endl;
    float temp = 3.49 * std_dev_0 * (1/cbrt(data_0.size()));
    cout << temp << endl;
  */
}

void ContinuousVariable::calculateMean(){
  for(int i = 0; i < 2; i++){
    mean[i] = 0;
    for(int j = 0; j < total[i]; j++){
      mean[i] += data[i].at(j);
    }
    mean[i] = mean[i] / total[i];
  }
}

void ContinuousVariable::calculateStdDev(){
  for(int i = 0; i < 2; i++){
    std_dev[i] = 0;
    for(int j = 0; j < total[i]; j++){
      std_dev[i] += pow(data[i].at(j) - mean[i], 2);
    }
    std_dev[i] = sqrt(std_dev[i] / total[i]);
  }
}
