// discrete.h

#include <string>
#include <vector>
#include <cmath>

/*
class DiscreteVariable
{
public:
  DiscreteVariable(){
    total = 0;
    data[0] = 0;
    data[1] = 0;
  }
  void insert(int value, int label){
    total++;
    if(label == 1){
      if(value == 0)
	data[0]++;
      else
	data[1]++;
    }
  }
  
  float getConditionalProbability(string value, int label){
    float probability;
    if(label == 0){
      // proability of male given no
      if(value == 0)
	probability = (tot);
      // probability of female given no
      else
	probability = ;
    }
    else{
      // probability of male given yes
      if(value == 0)
	probability = ;
      // probability of female given yes
      else
	probability = ;
    }
    return probability;
  }
  
  void out(){
    cout << total << " " << data[0] << " " << data[1] << endl;
  }
private:
    int total;
    int data[2];
};
*/

class DiscreteVariable
{
public:
  DiscreteVariable();
  ~DiscreteVariable();
  void insert(std::string value, int label);
  float probability(std::string value, int label);
  
  void out();
  
private:
  int total;
  float male_total;
  float female_total;
  float male_yes;
  float female_yes;
};
