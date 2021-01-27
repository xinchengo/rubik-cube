#include <iostream>
#include "rubik.h"
using namespace std;
int main()
{
    rubik cube1;
    int cnt = 0;
    do
    {
        cube1.rotate(FACE_UP, 3);
        cube1.rotate(FACE_RIGHT);
        cnt++;
    } while (!cube1.solved());
    cout << cnt << endl;
    return 0;
}