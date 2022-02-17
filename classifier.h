// classifier.h

#include <vector>
#include "continuous.h"
#include "discrete.h"

class Classifier
{
public:
  Classifier();
  ~Classifier();
  void insert(std::vector<std::string> data);
  void train();
  int predict(std::vector<std::string> data);
private:
  int total;
  int total_yes;
  ContinuousVariable age;
  DiscreteVariable gender;
  ContinuousVariable height_cm;
  ContinuousVariable weight_kg;
  ContinuousVariable body_fat;
  ContinuousVariable diastolic;
  ContinuousVariable systolic;
  ContinuousVariable grip_force;
  ContinuousVariable sit_and_bend_forward_cm;
  ContinuousVariable sit_up_count;
  ContinuousVariable broad_jump_cm;
  float likelihood(std::vector<std::string> data, int label);
};
