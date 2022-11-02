#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <iostream>

class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor : public GraphObject {
public:
    Actor (int ID, int sx, int sy, int direction, int depth, double size, bool block, bool damageable, StudentWorld * temp)
    : GraphObject(ID, SPRITE_WIDTH*sx, SPRITE_HEIGHT*sy, direction, depth, size), m_block(block), m_damageable(damageable), m_temp(temp)
    {
        m_alive = true;     // set alive and undamaged
        m_damaged = false;
    }
    bool getStatus() { return m_alive; }
    bool getBlock() { return m_block; }
    bool getDamageable() { return m_damageable; }
    bool getDamage() { return m_damaged; }
    bool overlapPeach();
    void setDamage(bool ishit) { m_damaged = ishit; }
    StudentWorld * getWorld() { return m_temp; }
    void setStatus(bool alive) {m_alive = alive; }
    virtual void doSomething() = 0;
    virtual void bonk() = 0;
    void moveDown();
private:
    StudentWorld * m_temp;
    bool m_alive;
    bool m_block;
    bool m_damageable;
    bool m_damaged;
};

class Peach : public Actor {
public:
    Peach(int x, int y, StudentWorld * world)
    : Actor(IID_PEACH, x, y, 0, 0, 1, false, true, world) {
        invicibility = 0; m_temp_invincibility = 0;
        recharge = 0; m_ticks = 0; m_hp = 1;
        remaining_jump_distance = 0; m_temp_invinc_ticks = 0;
        time_to_recharge_before_next_fire = 0;
        m_star = m_jump = m_shoot = false;
    }
    virtual void doSomething();
    virtual void bonk();
    void setPower (std::string power);
    void decHP() { m_hp--; }
    bool getInvincibility() {return invicibility; }
    bool getStar() { return m_star; }
    bool getJump() {return m_jump; }
    bool getShoot() { return m_shoot; }
private:
    bool invicibility;
    bool m_temp_invincibility;
    bool recharge;
    bool m_star;
    bool m_jump;
    bool m_shoot;
    int m_ticks;
    int m_temp_invinc_ticks;
    int m_hp;
    int time_to_recharge_before_next_fire;
    int remaining_jump_distance;
};

//  Super Class for Goomba, Koopa, and Piranha
class Enemy : public Actor {
public:
    Enemy (int ID, int x, int y, int direction, StudentWorld * world) : Actor(ID, x, y, direction, 0, 1, false, true, world) {}
    virtual void doSomething();
    virtual void bonk();
protected:
    void move();
    
};

class Goomba : public Enemy {
public:
    Goomba (int x, int y, int direction, StudentWorld * world) : Enemy(IID_GOOMBA, x, y, direction, world) {}
    
};

class Koopa : public Enemy {
public:
    Koopa (int x, int y, int direction, StudentWorld * world) : Enemy(IID_KOOPA, x, y, direction, world) {}
    virtual void doSomething();
    virtual void bonk();
};

class Piranha : public Enemy {
public:
    Piranha (int x, int y, int direction, StudentWorld * world) : Enemy(IID_PIRANHA, x, y, direction, world) { m_delay = 0; }
    virtual void doSomething();
private:
    int m_delay;
};

// Superclass for Mushroom, Flower, and Star
class Goodie : public Actor {
public:
    Goodie (int ID, int x, int y, int score, std::string power, StudentWorld * world) : Actor(ID, x, y, 0, 1, 1, false, false, world), m_power(power), m_score(score) {}
    virtual void doSomething();
    virtual void bonk() { return; }
    
private:
    std::string m_power;
    int m_score;
};

class Star : public Goodie {
public:
    Star (int x, int y, StudentWorld * world) : Goodie(IID_STAR, x, y, 100, "Star Power", world) {}
        
};

class Mushroom : public Goodie {
public:
    Mushroom (int x, int y, StudentWorld * world) : Goodie(IID_MUSHROOM, x, y, 75, "Jump Power", world) {}
    
};

class Flower : public Goodie {
public:
    Flower (int x, int y, StudentWorld * world) : Goodie(IID_FLOWER, x, y, 50, "Shoot Power", world) {}
};

// Superclass for Peachfire, PiranhaFire, and Shell
class Projectile : public Actor {
public:
    Projectile (int ID, int x, int y, int direction, StudentWorld * world) : Actor(ID, x, y, direction, 1, 1, false, false, world) {}
    virtual void doSomething();
    virtual void bonk() { return; }
};

class PeachFire : public Projectile {
public:
    PeachFire (int x, int y, int direction, StudentWorld * world) : Projectile(IID_PEACH_FIRE, x, y, direction, world) {}
};

class Shell : public Projectile {
public:
    Shell (int x, int y, int direction, StudentWorld * world) : Projectile(IID_SHELL, x, y, direction, world) {}
};

class PiranhaFire : public Projectile {
public:
    PiranhaFire (int x, int y, int direction, StudentWorld * world) : Projectile(IID_PIRANHA_FIRE, x, y, direction, world) {}
    virtual void doSomething();
};

// Superclass for Pipe
class Block : public Actor {
public:
    Block(int ID, int x, int y, StudentWorld * world, std::string goodie = "") : Actor(ID, x, y, 0, 2, 1, true, false, world), m_goodie(goodie) { m_goodie_released = 0;}
    virtual void doSomething() { return; }
    void bonk();
private:
    bool m_goodie_released;
    std::string m_goodie;
};

class Pipe : public Block {
public:
    Pipe(int x, int y, StudentWorld * world) :Block(IID_PIPE, x, y, world, "") {}
    void bonk() { return; }
};


// Superclass for Mario and Flag Object
class EndItems : public Actor {
public:
    EndItems (int ID, int x, int y, int signal, StudentWorld * world) : Actor(ID, x, y, 0, 1, 1, false, false, world), m_signal(signal) {}
    virtual void doSomething();
    virtual void bonk() { return; }
private:
    int m_signal;
    
};

class Flag : public EndItems {
public:
    Flag (int x, int y, StudentWorld * world) : EndItems(IID_FLAG, x, y, 1, world) {}
    
};

class Mario : public EndItems {
public:
    Mario (int x, int y, StudentWorld * world) : EndItems(IID_MARIO, x, y, 2, world) {}
};


#endif // ACTOR_H_
