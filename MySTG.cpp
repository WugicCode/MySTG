#include<cmath>
#include<ctime>
#include<list>

#include"MySTG.h"

using namespace std;

//常量
const int FPS = 60;
const LD SPF = 1.0 / (double)FPS;
const int DefaultPreFrame = 30;

//全局变量
int frameCnt = 0;
bool gamePause = false;
int gameFrameCnt = 0;
int lifeLeft;
GameStatus gameStatus; 
list<Attack*> attackCache;

int SecondToFrame(double seconds)
{
    return seconds * FPS;
}

double FrameToSecond(int frame)
{
    return frame * SPF;
}

double DegreeStandardize(double& degree)
{
    while(degree >= 360.0)degree -= 360.0;
    while(degree < 0.0)degree += 360.0;
    return degree;
}

double StandardizeDegree(double degree)
{
    while(degree >= 360.0)degree -= 360.0;
    while(degree < 0.0)degree += 360.0;
    return degree;
}

void InitGame(void)
{
    //and more.
}

void Attack::Summon(void)
{
    SummonFrame = gameFrameCnt;
    return;
}

void Attack::Summon(int gameFrame)
{
    SummonFrame = gameFrame;
    return;
}


Movable::Movable(void) {}

void Movable::SetX(double x)
{
    this->x = x;
    return;
}

void Movable::SetY(double y)
{
    this->y = y;
    return;
}

void Movable::SetSpeed(double speed)
{
    straightMovement.speed = speed;
    return;
}

void Movable::VarySpeed(double acceleration)
{
    straightMovement.speed += acceleration * SPF;
    return;
}

void Movable::SetMoveDirection(double direction)
{
    DegreeStandardize(direction);
    straightMovement.direction = direction;
    UpdateDirectionType();
    return;
}

void Movable::SetMoveDirection(DirectionType direction)
{
    if(direction == DirectionType::NORMAL) return;
    straightMovement.directionType = direction;
    switch (direction)
    {
        case DirectionType::RIGHT :
            straightMovement.direction = 0.0;
            break;
        case DirectionType::UP :
            straightMovement.direction = 90.0;
            break;
        case DirectionType::LEFT :
            straightMovement.direction = 180.0;
            break;
        case DirectionType::DOWN :
            straightMovement.direction = 270.0;
            break;
    }
    return;
}

void Movable::SpinMoveDirection(double degree)
{
    straightMovement.direction += degree;
    UpdateDirectionType();
    return;
}

double Movable::GetX(void)
{
    return this->x;
}

double Movable::GetY(void)
{
    return this->y;
}

double Movable::GetSpeed(void)
{
    return this->straightMovement.speed;
}

double Movable::GetMoveDirection(void)
{
    return this->straightMovement.direction;
}

void Movable::UniformMove(double speed, double direction)
{
    DegreeStandardize(direction);
    x += speed * cos(direction) * SPF;
    y += speed * sin(direction) * SPF;
    return;
}

void Movable::UniformMove(double speed){
    UniformMove(speed, straightMovement.direction);
    return;
}

void Movable::UniformMove(double speed, DirectionType direction)
{
    switch (direction)
    {
        case DirectionType::NORMAL :
            UniformMove(speed);
            break;
        case DirectionType::RIGHT :
            UniformMove(speed, 0.0);
            break;
        case DirectionType::UP :
            UniformMove(speed, 90.0);
            break;
        case DirectionType::LEFT :
            UniformMove(speed, 180.0);
            break;
        case DirectionType::DOWN :
            UniformMove(speed, 270.0);
            break;
    }
    return;
}

void Movable::StraightMove(double direction)
{
    UniformMove(straightMovement.speed, direction);
    return;
}

void Movable::StraightMove(void)
{
    UniformMove(straightMovement.speed);
    return;
}

void Movable::StraightMove(DirectionType direction)
{
    UniformMove(straightMovement.speed, direction);
    return;
}

void Movable::ParallelMove(double distance, double direction)
{
    DegreeStandardize(direction);
    x += distance * cos(direction);
    y += distance * sin(direction);
    return;
}

void Movable::ParallelMove(double distance)
{
    ParallelMove(distance, straightMovement.direction);
    return;
}

void Movable::ParallelMove(double distance, DirectionType direction)
{
    switch (direction)
    {
        case DirectionType::NORMAL :
            ParallelMove(distance);
            break;
        case DirectionType::RIGHT :
            ParallelMove(distance, 0.0);
            break;
        case DirectionType::UP :
            ParallelMove(distance, 90.0);
            break;
        case DirectionType::LEFT :
            ParallelMove(distance, 180.0);
            break;
        case DirectionType::DOWN :
            ParallelMove(distance, 270.0);
            break;
    }
    return;
}

void Movable::Teleport(double x, double y)
{
    this->x = x;
    this->y = y;
    return;
}

void Movable::UpdateDirectionType(void)
{
    DegreeStandardize(straightMovement.direction);
    if(straightMovement.direction == 0.0)straightMovement.directionType = DirectionType::RIGHT;
    if(straightMovement.direction == 90.0)straightMovement.directionType = DirectionType::UP;
    if(straightMovement.direction == 180.0)straightMovement.directionType = DirectionType::LEFT;
    if(straightMovement.direction == 270.0)straightMovement.directionType = DirectionType::DOWN;
    return;
}


Bullet::Bullet(void) {}

Bullet::Bullet(double size)
{
    this->size = size;
}

Bullet::Bullet(double x, double y, double size)
{
    this->x = x;
    this->y = y;
    this->size = size;
}

void Bullet::SetMoveDirection(double direction)
{
    DegreeStandardize(direction);
    SetInclineDegree(direction);
    straightMovement.direction = direction;
    UpdateDirectionType();
    return;
}

void Bullet::SetMoveDirection(double direction, bool turned)
{
    DegreeStandardize(direction);
    if(turned == true) SetInclineDegree(direction);
    straightMovement.direction = direction;
    UpdateDirectionType();
    return;
}

void Bullet::SetMoveDirection(DirectionType direction)
{
    if(direction == DirectionType::NORMAL) return;
    straightMovement.directionType = direction;
    switch (direction)
    {
        case DirectionType::RIGHT :
            straightMovement.direction = 0.0;
            SetInclineDegree(0.0);
            break;
        case DirectionType::UP :
            straightMovement.direction = 90.0;
            SetInclineDegree(90.0);
            break;
        case DirectionType::LEFT :
            straightMovement.direction = 180.0;
            SetInclineDegree(180.0);
            break;
        case DirectionType::DOWN :
            straightMovement.direction = 270.0;
            SetInclineDegree(270.0);
            break;
    }
    return;
}

void Bullet::SetMoveDirection(DirectionType direction, bool turned)
{
    if(direction == DirectionType::NORMAL) return;
    straightMovement.directionType = direction;
    switch (direction)
    {
        case DirectionType::RIGHT :
            straightMovement.direction = 0.0;
            if(turned == true) SetInclineDegree(0.0);
            break;
        case DirectionType::UP :
            straightMovement.direction = 90.0;
            if(turned == true) SetInclineDegree(90.0);
            break;
        case DirectionType::LEFT :
            straightMovement.direction = 180.0;
            if(turned == true) SetInclineDegree(180.0);
            break;
        case DirectionType::DOWN :
            straightMovement.direction = 270.0;
            if(turned == true) SetInclineDegree(270.0);
            break;
    }
    return;
}

void Bullet::SpinMoveDirection(double degree)
{
    straightMovement.direction += degree;
    SpinInclineDegree(degree);
    UpdateDirectionType();
    return;
}

void Bullet::SpinMoveDirection(double degree, bool turned)
{
    straightMovement.direction += degree;
    if(turned == true) SpinInclineDegree(degree);
    UpdateDirectionType();
    return;
}

void Bullet::SetInclineDegree(double degree)
{
    DegreeStandardize(degree);
    inclineDegree = degree;
    return;
}

void Bullet::SpinInclineDegree(double degree)
{
    DegreeStandardize(degree);
    inclineDegree += degree;
    return;
}

double Bullet::GetInclineDegree(void)
{
    return inclineDegree;
}

double Bullet::GetSize(void)
{
    return size;
}


SmallBullet::SmallBullet(void)
{
    size = 5.0;
}

SmallBullet::SmallBullet(double x, double y){
    size = 5.0;
    this->x = x;
    this->y = y;
}


//前方施工

bool Bullet::IfDefaultKill() 
{
    
}

bool Bullet::MissedJudge() 
{

}

void Bullet::Draw()
{

}

void SmallBullet::Draw()
{

}