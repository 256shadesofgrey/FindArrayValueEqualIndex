#include "BinarySearch.hpp"

int32_t BinarySearch::search(const int32_t *array, uint32_t len)
{
  // Slope of value graph fv is mv>=1, while the slope of the index graph fi is mi=1.
  // That means if fv starts above 0 or ends below len-1, there cannot possibly
  // be an intersection that we're looking for, so we can skip the search.
  if(array[0] > 0){
    return -1;
  }

  // Subtracting 1 from len now to save one subtraction operation in the if stetement.
  --len;

  if(array[len] < len){
    return -1;
  }

  // Adding 1 to len again because we need the original value for the actual
  // search. This means that when the if statement above evaluates to false,
  // we will not have saved any operations by doing it this way, but in cases
  // when it evaluates to true, we will have saved one, so it's an average case
  // improvement.
  // We could have used an additional variable to avoid this operation, but
  // doing so would have used more memory and would still have resulted in an
  // allocation operation, so this is still better.
  ++len;

  uint32_t start = 0;

  // Declaring variable outside of the scope of the loop, even though it is
  // not needed outside, to make sure that the memory for it is only allocated
  // once, which depending on compiler optimizations might save a few cycles.
  // Not assigning a value to mid, because we will do it in the loop before it
  // will be used the first time. This saves us one operation.
  uint32_t mid;

  // Doing the search iteratively to save memory on the stack.
  while(start != len){
    // We have to divide an integer by 2, which in binary gives the same result
    // as shifting by 1 to the right. Depending on compiler optimizations and the
    // CPUs this code will run on, this operation might be faster than division.
    mid = (start + len) >> 1;
    if(array[mid] == mid){
      return mid;
    }else if(array[mid] > mid){ // Intersection to the left of mid.
      len = mid;
    }else{ // Intersection to the right of mid.
      start = mid+1;
    }
  }

  return -1;
}
