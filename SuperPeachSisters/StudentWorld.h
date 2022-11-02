#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void addActor(Actor * newActor);
    bool isOverlap(int ax, int ay, int bx, int by);
    bool blocks(int x, int y);
    void bonk(int x, int y);
    Actor * isBlockingAt(int x, int y);
    Peach * getPeach() { return m_Peach; }
    Actor * FireOverlap(int x, int y);
    void setLevelStatus(int complete);
private:
    std::vector<Actor*> Actors;
    Peach * m_Peach;
    bool levelComplete;
    bool hitMario;
};

#endif // STUDENTWORLD_H_
