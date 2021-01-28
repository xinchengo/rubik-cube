#ifndef __RUBIK_CUBE_H_XINCHENGO__
#define __RUBIK_CUBE_H_XINCHENGO__
#define FACE_UNSET 0
#define FACE_UP 1
#define FACE_DOWN 2
#define FACE_FRONT 3
#define FACE_BACK 4
#define FACE_LEFT 5
#define FACE_RIGHT 6
#define MODE_UP 0
#define MODE_DOWN 1
#define MODE_LEFT 2
#define MODE_RIGHT 3
#define MODE_ALL 4
const int copy_mode_x[4][3] = {{0, 0, 0}, {2, 2, 2}, {2, 1, 0}, {0, 1, 2}};
const int copy_mode_y[4][3] = {{0, 1, 2}, {2, 1, 0}, {0, 0, 0}, {2, 2, 2}};
class __rubik_face
{
public:
    __rubik_face();
    void settype(int);
    int face[3][3];
    void rotate(int);
    void update();
    friend int copy(__rubik_face &, __rubik_face &, int, int);

private:
    void __rotate1();
    void __rotate2();
    void __rotate3();
    int __face[3][3];
};
__rubik_face::__rubik_face()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            __face[i][j] = face[i][j] = FACE_UNSET;
}
void __rubik_face::settype(int _default = 0)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            face[i][j] = _default;
}
void __rubik_face::__rotate1()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            __face[i][j] = face[2 - j][i];
}
void __rubik_face::__rotate2()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            __face[i][j] = face[2 - i][2 - j];
}
void __rubik_face::__rotate3()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            __face[i][j] = face[j][2 - i];
}
void __rubik_face::rotate(int times = 1)
{
    int mode = times % 4;
    switch (mode)
    {
    case 0:
        break;
    case 1:
        __rotate1();
        break;
    case 2:
        __rotate2();
        break;
    case 3:
        __rotate3();
        break;
    }
}
void __rubik_face::update()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            face[i][j] = (__face[i][j] == FACE_UNSET) ? face[i][j] : __face[i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            __face[i][j] == FACE_UNSET;
}
int copy(__rubik_face &source, __rubik_face &target, int smode, int tmode)
{
    if (smode == 4 && tmode == 4)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                target.__face[i][j] = source.face[i][j];
    else if (smode < 4 && tmode < 4 && smode >= 0 && tmode >= 0)
        for (int i = 0; i < 3; i++)
            target.__face[copy_mode_x[tmode][i]][copy_mode_y[tmode][i]] = source.face[copy_mode_x[smode][i]][copy_mode_y[smode][i]];
    else
        return 1;
    return 0;
}
class rubik
{
public:
    __rubik_face up;    //       +-----+
    __rubik_face down;  //       | UP  |
    __rubik_face front; // +-----+-----+-----+-----+
    __rubik_face back;  // |LEFT |FRONT|RIGHT|BACK |
    __rubik_face left;  // +-----+-----+-----+-----+
    __rubik_face right; //       |DOWN |
    rubik();            //       +-----+
    void update();
    bool solved();
    void rotate(int, int);

private:
    void __rotate(int);
};
rubik::rubik()
{
    up.settype(FACE_UP);
    down.settype(FACE_DOWN);
    front.settype(FACE_FRONT);
    back.settype(FACE_BACK);
    left.settype(FACE_LEFT);
    right.settype(FACE_RIGHT);
}
void rubik::update()
{
    up.update();
    down.update();
    front.update();
    back.update();
    left.update();
    right.update();
}
void rubik::__rotate(int face)
{
    switch (face)
    {
    case FACE_UP:
        up.rotate();
        copy(front, left, MODE_UP, MODE_UP);
        copy(left, back, MODE_UP, MODE_UP);
        copy(back, right, MODE_UP, MODE_UP);
        copy(right, front, MODE_UP, MODE_UP);
        break;
    case FACE_DOWN:
        down.rotate();
        copy(front, right, MODE_DOWN, MODE_DOWN);
        copy(right, back, MODE_DOWN, MODE_DOWN);
        copy(back, left, MODE_DOWN, MODE_DOWN);
        copy(left, front, MODE_DOWN, MODE_DOWN);
        break;
    case FACE_FRONT:
        front.rotate();
        copy(up, right, MODE_DOWN, MODE_LEFT);
        copy(right, down, MODE_LEFT, MODE_UP);
        copy(down, left, MODE_UP, MODE_RIGHT);
        copy(left, up, MODE_RIGHT, MODE_DOWN);
        break;
    case FACE_BACK:
        back.rotate();
        copy(up, left, MODE_UP, MODE_LEFT);
        copy(left, down, MODE_LEFT, MODE_DOWN);
        copy(down, right, MODE_DOWN, MODE_RIGHT);
        copy(right, up, MODE_RIGHT, MODE_UP);
        break;
    case FACE_LEFT:
        left.rotate();
        copy(front, down, MODE_LEFT, MODE_LEFT);
        copy(down, back, MODE_LEFT, MODE_RIGHT);
        copy(back, up, MODE_RIGHT, MODE_LEFT);
        copy(up, front, MODE_LEFT, MODE_LEFT);
        break;
    case FACE_RIGHT:
        right.rotate();
        copy(front, up, MODE_RIGHT, MODE_RIGHT);
        copy(up, back, MODE_RIGHT, MODE_LEFT);
        copy(back, down, MODE_LEFT, MODE_RIGHT);
        copy(down, front, MODE_RIGHT, MODE_RIGHT);
        break;
    }
    update();
}
void rubik::rotate(int face, int times = 1)
{
    times %= 4;
    if (times == 0)
    {
        return;
    }
    while (times--)
    {
        __rotate(face);
    }
}
bool rubik::solved()
{
    bool flag = true;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            flag = flag && (up.face[i][j] == FACE_UP);
            flag = flag && (down.face[i][j] == FACE_DOWN);
            flag = flag && (front.face[i][j] == FACE_FRONT);
            flag = flag && (back.face[i][j] == FACE_BACK);
            flag = flag && (left.face[i][j] == FACE_LEFT);
            flag = flag && (right.face[i][j] == FACE_RIGHT);
        }
    return flag;
}
#endif