#ifndef MYSTG_H
#define MYSTG_H

using namespace std;

typedef long double LD;

enum class GameStatus
{
    STARTMENU, 
    GAME
    //and more.
};

enum class DirectionType
{
    NORMAL, 
    RIGHT, 
    UP, 
    LEFT, 
    DOWN
};


struct StraightMovement
{
    double direction;
    double speed;
    DirectionType directionType;
};

int SecondToFrame(double seconds);
double FrameToSecond(int frame);
double DegreeStandardize(double& degree);
double StandardizeDegree(double degree);

void InitGame(void);

class ImageSetting
{
    // more.
};

class Attack //（敌人）攻击
{
    public:
        virtual bool IfDefaultKill() = 0;
        virtual bool MissedJudge() = 0;
        virtual void Draw() = 0;
        virtual void Summon(void);
        virtual void Summon(int gameFrame);
    protected:
        ImageSetting imageSettings;
        int SummonFrame;
};

class Movable //可移动对象
{
    public:
        void SetSpeed(double speed);
        void VarySpeed(double acceleration);
        virtual void SetMoveDirection(double direction);
        virtual void SetMoveDirection(DirectionType direction);
        virtual void SpinMoveDirection(double degree);

        double GetX(void);
        double GetY(void);
        double GetSpeed(void);
        double GetMoveDirection(void);
        
        //移动
        virtual void UniformMove(double speed, double direction);
        virtual void UniformMove(double speed);
        virtual void UniformMove(double speed, DirectionType direction);
        virtual void StraightMove(double direction);
        virtual void StraightMove(void);
        virtual void StraightMove(DirectionType direction);
        virtual void ParallelMove(double distance, double direction);
        virtual void ParallelMove(double distance);
        virtual void ParallelMove(double distance, DirectionType direction);
        virtual void SetX(double x);
        virtual void SetY(double y);
        virtual void Teleport(double x, double y); 
    protected:
        double x;
        double y;
        StraightMovement straightMovement;
        void UpdateDirectionType(void);
        Movable(void);
};

class Bullet : public Attack, public Movable //子弹
{
    public:
        Bullet(void);
        Bullet(double size);
        Bullet(double x, double y, double size);

        virtual void SetMoveDirection(double direction);
        virtual void SetMoveDirection(double direction, bool turned);
        virtual void SetMoveDirection(DirectionType direction);
        virtual void SetMoveDirection(DirectionType direction, bool turned);
        virtual void SpinMoveDirection(double degree);
        virtual void SpinMoveDirection(double degree, bool turned);
        void SetInclineDegree(double degree);
        void SpinInclineDegree(double degree);

        double GetInclineDegree(void);
        double GetSize(void);

        bool IfDefaultKill(void);
        bool MissedJudge(void);
        void Draw(void);

    protected:
        double size = 5.0;
        double inclineDegree = 0.0;

};

class SmallBullet : public Bullet
{
    public:
        SmallBullet(void);
        SmallBullet(double x, double y);

        void Draw(void);
};

class Lazer : public Attack, public Movable
{
    public:
        Lazer(void);
        void SetSlope(double degree);
        void TurnSlope(double degree);
        void SetAngularVelocity(double angularVelocity);
        void VaryAngularVelocity(double angularVelocity);
        void Spin(void);

        double GetSlope(void);
        double GetAngularVelocity(void);
        bool Is_Active(void);

        //覆写移动方法
        virtual void UniformMove(double speed, double direction);
        virtual void UniformMove(double speed);
        virtual void UniformMove(double speed, DirectionType direction);
        virtual void StraightMove(double direction);
        virtual void StraightMove(void);
        virtual void StraightMove(DirectionType direction);
        virtual void ParallelMove(double distance, double direction);
        virtual void ParallelMove(double distance);
        virtual void ParallelMove(double distance, DirectionType direction);
        virtual void SetX(double x);
        virtual void SetY(double y);
        virtual void Teleport(double x, double y);

        virtual bool IfDefaultKill(void);
        virtual bool MissedJudge(void);
        virtual void Draw(void);

    protected:
        double slopeDegree;
        double angularVelocity;
        double intercept;
        double width;
        DirectionType slopeDirectionType;

        void UpdateIntercept(void);
        void UpdateSlopeDirectionType(void);
};

class Ray : public Lazer
{
    public:
        Ray();

        virtual bool MissedJudge(void);
        virtual void Draw(void);
};

class Flash : public Lazer
{
    public:
        Flash(void);

        virtual bool IfDefaultKill(void);
        virtual bool MissedJudge(void);
        virtual void Draw(void);
};

class Shot : public Flash
{
    public:
        Shot(void);
         
        virtual bool MissedJudge(void);
        virtual void Draw(void);
};

class Slash : public Flash
{
    public:
        Slash(void);

        virtual bool MissedJudge(void);
        virtual void Draw(void);
};

class Enemy : public Movable{
    // more.
};

#endif