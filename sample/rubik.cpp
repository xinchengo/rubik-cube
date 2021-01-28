#include <iostream>
#include "../include/rubik.h"
using namespace std;
int main()
{
    rubik cube1;
    int cnt = 0;
    do
    {
        cube1.rotate(FACE_RIGHT);
        cube1.rotate(FACE_UP);
        cube1.rotate(FACE_LEFT);
        cube1.rotate(FACE_DOWN);
        cnt++;
    } while (!cube1.solved());
    cout << cnt << endl;
    return 0;
}