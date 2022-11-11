#include <iostream>
#include <string>
#include <TestArray.hpp>
#include <BinarySearch.hpp>

using namespace std;

// "./FindArrayValueEqualIndex" uses a randomly generated array.
// "./FindArrayValueEqualIndex <n1> ..." uses numbers from stdin.
// "./FindArrayValueEqualIndex set <len> <startVal> <minStep> <maxStep>" uses
//     a randomly generated array with the given parameters.
int main(int argc, char *argv[]){
  TestArray *ta;

  // TODO: implement getopt interface.
  // TODO: check if inputs are correct.
  if(argc <= 1){
    cout<<"Testing with randomly generated array."<<endl;
    ta = new TestArray();
  }else{
    if(isdigit(argv[0][0])){
      cout<<"Testing with array from stdin."<<endl;
      ta = new TestArray(argc-1, &argv[1]);
    }else{
      cout<<"Testing with randomly generated array with given parameters"<<endl;
      ta = new TestArray(stoi(argv[2]), stoi(argv[3]),
                         stoi(argv[4]), stoi(argv[5]));
    }
  }

  ta->printArray();
}
