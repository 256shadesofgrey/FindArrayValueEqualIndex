#include <iostream>
#include <string>

#include <sys/select.h>

#include <TestArray.hpp>
#include <BinarySearch.hpp>

using namespace std;

// "./FindArrayValueEqualIndex" uses a randomly generated array.
// "echo <n1> ... | ./FindArrayValueEqualIndex" will use piped values for the array.
// "./FindArrayValueEqualIndex <n1> ..." uses numbers passed as parameters as
//     the array.
// "./FindArrayValueEqualIndex set <len> <startVal> <minStep> <maxStep>" uses
//     a randomly generated array with the given parameters.
int main(int argc, char *argv[]){
  TestArray *ta;

  // TODO: implement getopt interface.
  // TODO: check if inputs are correct.
  if(argc > 1){
    bool firstParamInteger = true;

    try{
      stoi(argv[1]);
    }catch(invalid_argument){
      firstParamInteger = false;
    }

    if(firstParamInteger){
      cout<<"Testing with array passed as parameters."<<endl;
      ta = new TestArray(argc-1, &argv[1]);
    }else{
      cout<<"Testing with randomly generated array with given parameters"<<endl;
      ta = new TestArray(stoi(argv[2]), stoi(argv[3]),
                         stoi(argv[4]), stoi(argv[5]));
    }
  }else{
    int32_t n;
    vector<int32_t> buffer;

    int fd_stdin = fileno(stdin);
    fd_set readfds;
    FD_SET(fd_stdin, &readfds);
    struct timeval tv = {0, 0};

    while(select(1, &readfds, NULL, NULL, &tv) && cin>>n){
      buffer.push_back(n);
    }

    if(buffer.size() > 0){
      cout<<"Testing with piped values."<<endl;
      ta = new TestArray(buffer);
    }else{
      cout<<"Testing with randomly generated array."<<endl;
      ta = new TestArray();
    }
  }

  ta->printArray();

  int32_t result = BinarySearch::search(ta->getArray(), ta->len());

  if(result >= 0){
    cout<<"Value and its index equal at: "<<result<<endl;
  }else{
    cout<<"There is no value that equals its index."<<endl;
  }

  return 0;
}
