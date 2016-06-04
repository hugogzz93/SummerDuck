#include <iostream>
#include <unordered_map>
#include "SemanticCube.h"

  typedef std::unordered_map<int,int> dimThree;
  typedef std::unordered_map<int, dimThree> dimTwo;
  typedef std::unordered_map<int, dimTwo> dimOne;

using namespace std;

dimOne SemanticCube::getMatrix() {
	return matrix;
}

int SemanticCube::getResult(int op, int lOp, int rOp) {
	return matrix[lOp][rOp][op];
}
