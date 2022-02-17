// continuous.h

#include <string>
#include <vector>
#include <cmath>

class ContinuousVariable
{
 public:
  ContinuousVariable();
  ContinuousVariable(std::string type);
  ~ContinuousVariable();  
  void insert(float value, int label);
  void discretize();
  void normalizeData();
  //void calculateDistribution();
  void prepare();
  float probability(float value, int label);
  void out();
 private:
  // general purpose variables and functions
  std::vector<float> data[2];
  int total[2];
  float probabilityGuassian(float value, int label);
  //float probabilityDiscrete(float value, int label);
  float probabilityInterpolation(float value, int label);
  std::string distribution_type;
  // for use with guassian distribution
  float mean[2];
  float std_dev[2];
  void calculateMean(); 
  void calculateStdDev();
  // for use with iqr discretization
  // for use with histogram interpolation
  float minimum[2];
  float maximum[2];
  float bin_size[2];
  int num_bins[2];
  //float *iqr_ranges[2];
  //int *histogram[2];
  //std::vector<float> iqr_ranges[2];
  //std::vector<int> histogram[2];
  //void insertHistogram();
  std::vector<float> histogram[2];
};

