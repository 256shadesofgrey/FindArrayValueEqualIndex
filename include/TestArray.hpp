#ifndef TEST_ARRAY_HPP
#define TEST_ARRAY_HPP

#include <cstdint>
#include <random>

enum DebugLevel{
  silent = 0,
  verbose = 1,
  debug = 2
};

class TestArray{
private:
  DebugLevel debugLevel_ = silent;

  int32_t *array_ = nullptr;
  int32_t startValue_;
  int32_t minStep_;
  int32_t maxStep_;
  uint32_t len_;

  std::random_device rd_;
  std::mt19937 rng_;

  void generateArray();
  void convertCharArrayToIntArray(uint32_t len, char *charArray[], int32_t *intArray);
  void printParams();

public:
  TestArray();
  TestArray(uint32_t len, int32_t startValue, int32_t minStep, int32_t maxStep);
  TestArray(uint32_t len, char *array[]);

  ~TestArray();

  void setDebugLevel(DebugLevel debugLevel);

  void setSeed();
  void setNewParams(uint32_t len, int32_t startValue,
                    int32_t minStep, int32_t maxStep);
  void setRandomParams();

  const int32_t *getArray();
  int32_t len() {return len_;};

  void printArray();
};

#endif // TEST_ARRAY_HPP
