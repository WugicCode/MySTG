#include<cstdio>

#include"MySTG.h"


int main()
{   
    SmallBullet a;
    Bullet b;
    b.SetMoveDirection(370.0);
    printf("%lf\n%f",b.GetMoveDirection(),a.GetSize());
    return 0;
}