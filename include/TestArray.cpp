#include <cstdlib>
#include <string>
#include <iostream>
#include "TestArray.hpp"

using namespace std;

void TestArray::setDebugLevel(DebugLevel debugLevel)
{
  debugLevel_ = debugLevel;
}

void TestArray::printParams()
{
  cout<<"len: "<<len_<<endl;
  cout<<"startValue: "<<startValue_<<endl;
  cout<<"minStep: "<<minStep_<<endl;
  cout<<"maxStep: "<<maxStep_<<endl;
}


TestArray::TestArray()
{
  rng_.seed(rd_());
  setRandomParams();
}

TestArray::TestArray(uint32_t len, int32_t startValue, int32_t minStep, int32_t maxStep)
{
  array_ = new int32_t[len];
  rng_.seed(rd_());
  setNewParams(len, startValue, minStep, maxStep);
}

TestArray::TestArray(uint32_t len, char *array[])
  :startValue_{0}, minStep_{0}, maxStep_{0}, len_{len}
{
  array_ = new int32_t[len];
  rng_.seed(rd_());
  convertCharArrayToIntArray(len_, array, array_);
}

TestArray::~TestArray()
{
  if(array_){
    free(array_);
  }
}

void TestArray::generateArray()
{
  int32_t nextValue = startValue_;

  uniform_int_distribution<int32_t> intDist(minStep_, maxStep_);

  for(int i = 0; i < len_; i++){
    array_[i] = nextValue;
    nextValue += intDist(rng_);
  }
}

void TestArray::setNewParams(uint32_t len, int32_t startValue,
                             int32_t minStep, int32_t maxStep)
{
  len_ = len;
  startValue_ = startValue;
  minStep_ = minStep;
  maxStep_ = maxStep;

  if(array_){
    free(array_);
  }

  if(debugLevel_ >= verbose){
    printParams();
  }

  array_ = new int32_t[len_];
  generateArray();
}

void TestArray::setRandomParams()
{
  // Theoretically the limit is (0, UINT32_MAX), but we'd probably run out of RAM.
  uniform_int_distribution<uint32_t> uintDistLen(1, 10000);
  len_ = uintDistLen(rng_);
  // Starting point must allow for at least as many distinct entries
  // as there are indices. Theoreticall max is (INT32_MIN, INT32_MAX-len_).
  uniform_int_distribution<int32_t> intDistStart(-5000, 2000);
  startValue_ = intDistStart(rng_);
  //int32_t maxStepLimit = (INT32_MAX - startValue_) / len_;
  //uniform_int_distribution<uint32_t> uintDistMinStep(1, maxStepLimit);
  //minStep_ = uintDistMinStep(rng_);
  minStep_ = 1;
  // Theoreticall limit (minStep_, maxStepLimit);
  uniform_int_distribution<uint32_t> uintDistMaxStep(minStep_, 100);
  maxStep_ = uintDistMaxStep(rng_);

  if(array_){
    free(array_);
  }

  if(debugLevel_ >= verbose){
    printParams();
  }

  array_ = new int32_t[len_];
  generateArray();
}

void TestArray::convertCharArrayToIntArray(uint32_t len, char *charArray[],
                                           int32_t *intArray)
{
  for(uint32_t i = 0; i < len; i++){
    intArray[i] = stoi(charArray[i]);
  }
}

const int32_t *TestArray::getArray()
{
  return array_;
}

void TestArray::printArray()
{
  for(uint32_t i = 0; i < len_; i++){
    cout<<array_[i]<<" ";
  }
  cout<<endl;
}
