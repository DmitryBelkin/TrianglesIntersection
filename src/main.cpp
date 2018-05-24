#include <iostream>
#include "BelkinD_triangle.h"

int main(int argc, const char * argv[])
{
    double t1[9] = {3,3,0, 7,7,0, 5,9,0};
    double t2[9] = {9,4,0, 9,9,0, 8,7,0};
//    double t1[9] = {2,2,0, 6,3,0, 3,6,0};
//    double t2[9] = {2,6,0, 5,2,0, 5,8,1};
    std::cout << BelkinD::AreTrianglesIntersect(t1, t2) << std::endl;
    return 0;
}
