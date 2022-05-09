#include <iostream>
#include "BEVector2.h"
#include "BEMatrix3.h"

int main()
{
	BEVector2 myVector = BEVector2(1,2);

	int a = 0;

	BEMatrix3 myMat = BEMatrix3(2,3,-1,1,2,0,4,2,1);

	float myTest;
	myTest = myMat.GetMatrixDeterminant();

	std::cout << myMat.ToString() << std::endl;
	std::cout << myTest << std::endl;

	return 0;

}