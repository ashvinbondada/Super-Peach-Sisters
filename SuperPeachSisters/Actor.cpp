#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
using namespace std;

void Peach::setPower (std::string power) {
    if (power == "Star Power") {            //  if star power, then make peach invincible for 150 ticks
        m_star = 1; m_ticks += 150; invicibility = 1; }
    if (power == "Shoot Power") {           //  if shoot power, give peach shoot power and make hit points 2
        m_shoot = 1; m_hp = 2; }
    if (power == "Jump Power") {            //  //  if Jump power, give peach jump power and make hit points 2
        m_jump = 1; m_hp = 2; }
    
}

//  When called, determine if the Actor calling this function overlaps with Peach
bool Actor::overlapPeach() {
    if (getWorld()->isOverlap(getX(), getY(), getWorld()->getPeach()->getX(), getWorld()->getPeach()->getY()))
        return true;
    return false;
}

//  If Flower, Mushroom, or Star overlaps with peach, play POWERUP SOUND
//      set Peach's power to power of the goodie and kill the Goodie
void Goodie::doSomething() {
    if (overlapPeach()) {
        getWorld()->increaseScore(m_score);
        getWorld()->getPeach()->setPower(m_power);
        setStatus(0);       // kills object
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    moveDown();
}

void Actor::moveDown() {
    if (!getWorld()->blocks(getX(), getY() - 2))        //  if there is no block below the actor
        moveTo(getX(), getY() - 2);                     //      move down two pixels
    
    if (getDirection() == 0) {                          //  if facing right and there is an object blocking movement
        if (getWorld()->blocks(getX() + 2, getY())) {   //      change direction to left
            setDirection(180);
            return;
        }
    }
    if (getDirection() == 180) {                        //  if facing left and there is an object blocking movement
        if (getWorld()->blocks(getX() - 2, getY())) {   //      change direction to right
            setDirection(0);
            return;
        }
    }
    if (getDirection() == 180) moveTo(getX() - 2, getY());  //  If facing left, then move 2 pixels left
    if (getDirection() == 0) moveTo(getX() + 2, getY());    //  If facing right, then move 2 pixels right
}

void Enemy::move() {
    if (getDirection() == 180) {                                //  If facing left and there is an object blocking movement
        if (getWorld()->blocks(getX() - 1, getY()))             //   change direction to right
            setDirection(0);
    }
    if (getDirection() == 0) {                                  //  If facing right and there is an object blocking movement
        if (getWorld()->blocks(getX() + 1, getY()))             //      change direction to left
            setDirection(180);
    }
    if (getDirection() == 180) {                                                //  if facing left and about to fall off edge
        if (!getWorld()->blocks(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT)) //      change direction to right
            setDirection(0);
    }
    if (getDirection() == 0) {
        if (!getWorld()->blocks(getX() + 7, getY() - SPRITE_HEIGHT))            //  if facing right and about to fall of edge
            setDirection(180);                                                  //      change direction to left
    }
    if (getDirection() == 180) {                                                //  If facing left and there is an object blocking movement
        if (getWorld()->blocks(getX() - 1, getY()))                             //      dont move
            return;
    }
    if (getDirection() == 0) {                                                  //  If facing left and there is an object blocking movement
        if (getWorld()->blocks(getX() + 1, getY()))                             //      dont move
            return;
    }
    if (getDirection() == 180)                      //   If facing left, move 1 pixel left
        moveTo(getX() - 1, getY());
    if (getDirection() == 0)                        //   If facing right, move 1 pixel right
        moveTo(getX() + 1, getY());
}


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Peach::doSomething() {
    if (getDamage()) {      //  if Peach is damaged, react with bonk, and reset Peach to be damaged again
        bonk();
        setDamage(0);
    }
    if (!getStatus())   //  if dead, then stop, program will end
        return;
    if (m_star) {       //  If have star power, decrease time with power until no power at all
        m_ticks--;
        if (m_ticks == 0) {
            m_star = 0;
            invicibility = 0;
        }
            
    }
    if (m_temp_invincibility) {     //  If have temp invic, decrease time with temp invic, until no temp invic at all
        m_temp_invinc_ticks --;
        if (m_temp_invinc_ticks == 0)
            m_temp_invincibility = 0;
    }
    if (recharge) {                 //  if in recharge mode, decrease time in recharge mode until out of recharge mode
        if (time_to_recharge_before_next_fire > 0) { time_to_recharge_before_next_fire--;
        }
        if (time_to_recharge_before_next_fire == 0)
            recharge = 0;
    }
    
    Actor * a = getWorld()->isBlockingAt(getX(), getY());   //  If overlapping with another object, bonk that object
    if (a != nullptr)
        a->bonk();
    
    if (remaining_jump_distance > 0) {                      //  If still in the air, If an object blocks peach from jumping higher, stop jump
        if (getWorld()->blocks(getX(), getY() + 4)) {
            getWorld()->bonk(getX(), getY() + 4);
            remaining_jump_distance = 0;
        }
        else {                                              //  otherwise keep moving up while still in motion
            moveTo(getX(), getY() + 4);
            remaining_jump_distance--;
        }
    }
    
    else {                                                  //  When done jumping, if there is nothing below Peach, fall 4 pixels
        if (!getWorld()->blocks(getX(), getY() - 3)) {
            moveTo(getX(), getY() - 4);
        }
    }
    
    // moving left and right
    int ch;
    //cout << getWorld()->blocks(getX(),getY() - 1);
    if (getWorld()->getKey(ch)) {
    // user hit a key during this tick!
    switch (ch)
    {
        case KEY_PRESS_LEFT: {                          //   if press left, switch direction to left
            setDirection(180);                          //      and try to move if no object blocks movement
            if (getWorld()->blocks(getX() - 4, getY()))
                return;
            else
                moveTo(getX() - 4, getY());
            break;
        }
        case KEY_PRESS_RIGHT: {                         //   if press left, switch direction to left
            setDirection(0);                            //      and try to move if no object blocks movement
            if (getWorld()->blocks(getX() + 4, getY()))
                return;
            else
                moveTo(getX() + 4, getY());
            break;
            }
        case KEY_PRESS_UP: {                                //   if press up, determine jump distance if Peach has Jump Power or not
            if (getWorld()->blocks(getX(), getY() - 1)){    //      and move up 4 pixels on the next tick
                if (m_jump)
                    remaining_jump_distance = 12;
                else
                    remaining_jump_distance = 8;
            }
            getWorld()->playSound(SOUND_PLAYER_JUMP);
            break;
        }
        case KEY_PRESS_SPACE: {                                     //  if press space, check if peach has Shoot Power
            if (!m_shoot || time_to_recharge_before_next_fire > 0)  //      and create new fireballs 4 pixels away from Peach
                return;
            if (m_shoot) {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                int X = getX() / SPRITE_WIDTH;
                int Y = getY() / SPRITE_HEIGHT;
                getWorld()->addActor(new PeachFire(X + 0.5, Y, getDirection(), getWorld()));
                time_to_recharge_before_next_fire = 8;
                recharge = 1;
            }
            break;
        }
        }
    } 
}


void Enemy::doSomething() {
    if (getDamage()) {                  //  If an enemy is damaged, increase peach score and set its own status to not alive
        getWorld()->increaseScore(100);
        setStatus(0);
    }
    if (!getStatus())
        return;
    if (overlapPeach()) {               //  if overlapping with peach, then bonk peach
        getWorld()->getPeach()->bonk();
        return;
    }
    move();                             //  else just keep moving
}

void Koopa::doSomething() {
    if (getDamage()) {                  //  If  damaged, increase peach score, CREATE SHELL, and set its own status to not alive
        getWorld()->increaseScore(100);
        setStatus(0);
        int X = getX() / SPRITE_WIDTH;      //  Creating Shell here
        int Y = getY() / SPRITE_HEIGHT;
        getWorld()->addActor(new Shell(X, Y, getDirection(), getWorld()));
    }
    if (!getStatus())
        return;
    if (overlapPeach()) {               //  if overlapping with peach, then bonk peach
        getWorld()->getPeach()->bonk();
        return;
    }
    move();                                 //  else just keep moving
}

void Piranha::doSomething() {
    if (getDamage()) {                  //  If  damaged, increase peach score, CREATE SHELL, and set its own status to not alive
        getWorld()->increaseScore(100);
        setStatus(0);
    }
    if (!getStatus())
        return;
    increaseAnimationNumber();          // change animations
    if (overlapPeach()) {               //  if overlapping with peach, then bonk peach
        getWorld()->getPeach()->bonk();
        return;
    }
    
    //  Check if Peach is in proximity to Piranha to act
    if (!(abs(getY() - getWorld()->getPeach()->getY()) < 1.5*SPRITE_HEIGHT)) {
        return;
    }
    if (getX() - getWorld()->getPeach()->getX() > 0)    //  If peach is to right of Piranha, face left
        setDirection(180);
    if (getX() - getWorld()->getPeach()->getX() < 0)    //  If peach is to left of Piranha, face right
        setDirection(0);
    if (m_delay > 0) {                                  //  If firing delay, then decrease it by 1, dont act yet
        m_delay --; return;
    }
    if (m_delay == 0) {                                                         //  if no firing delay and Peach is close, fire
        if ((abs(getX() - getWorld()->getPeach()->getX()) < 8*SPRITE_WIDTH)) {
            int X = getX() / SPRITE_WIDTH;                                      //  creating a new Piranha fire object here
            int Y = getY() / SPRITE_HEIGHT;
            getWorld()->addActor(new PiranhaFire(X, Y, getDirection(), getWorld()));
            m_delay = 40;
        }
    }
}

void EndItems::doSomething() {              //  If dead, dont act
    if (!getStatus())
        return;
    if (overlapPeach()) {                   //  if overlapping with Peach, signal the game is over
        getWorld()->increaseScore(1000);
        setStatus(0);
        getWorld()->setLevelStatus(m_signal);
    }
}


void Projectile::doSomething() {
    Actor * killMe = getWorld()->FireOverlap(getX(), getY());
    if (killMe != nullptr)              //  if Projectile overlaps with a damageable object thats not Peach or a Block
    {                                   //      damage the object and then remove Projectile from the game
        killMe->setDamage(1);
        setStatus(0);
        return;
    }
    moveDown();                         //  otherwise just keep moving left/right/down
//
}

void PiranhaFire::doSomething() {
    if (overlapPeach()) {               //  If overlapping with peach, damage peach, and remove fireball from game
        getWorld()->getPeach()->setDamage(1);
        setStatus(0);
        return;
    }
    if (getDirection() == 0) {                          //  if facing right and object blocks movement, then remove fireball from game
        if (getWorld()->blocks(getX() + 1, getY())) {
            setStatus(0);
            return;
        }
    }
    if (getDirection() == 180) {                        //  if facing left and object blocks movement, then remove fireball from game
        if (getWorld()->blocks(getX() - 1, getY())) {
            setStatus(0);
            return;
        }
    }
    moveDown();                                     //  otherwise keep moving
}


void Block::bonk() {
    if (m_goodie_released) {                        //  if goodie already released, do nothing
        getWorld()->playSound(SOUND_PLAYER_BONK);
        return;
    }
    else if (m_goodie.length() > 0){                    //  if block has a goodie, create a goodie above the block
        getWorld()->playSound(SOUND_POWERUP_APPEARS);   //      depending on what the goodie is
        int X = getX() / SPRITE_WIDTH;
        int Y = getY() / SPRITE_HEIGHT;
        //  Creating a star
        if (m_goodie == "Star") {
            getWorld()->addActor(new Star(X, Y + 1, getWorld()));
            m_goodie_released = 1;
        }
        //  Creating a mushroom
        if (m_goodie == "Mushroom") {
            getWorld()->addActor(new Mushroom(X, Y + 1, getWorld()));
            m_goodie_released = 1;
        }
        //  Creating a Flower
        if (m_goodie == "Flower") {
            getWorld()->addActor(new Flower(X, Y + 1, getWorld()));
            m_goodie_released = 1;
        }
    }
}
    
void Enemy::bonk() {
    if (!overlapPeach()) {              //  if not overlapping with Peach, do nothing,
        return;
    }
    if (getWorld()->getPeach()->getInvincibility()) {       //  if bonks peach with Star power, remove enemy from the game
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getWorld()->increaseScore(100);
        setStatus(0);
    }
}

void Koopa::bonk() {
    if (!overlapPeach()) {              //  if not overlapping with Peach, do nothing,
        return;
    }
    if (getWorld()->getPeach()->getInvincibility()) {   //  if bonks peach with Star power, remove enemy from the game
        getWorld()->playSound(SOUND_PLAYER_KICK);      //       and create a Shell in its place
        getWorld()->increaseScore(100);
        setStatus(0);
        int X = getX() / SPRITE_WIDTH;                  //  creating a shell here
        int Y = getY() / SPRITE_HEIGHT;
        getWorld()->addActor(new Shell(X, Y, getDirection(), getWorld()));
    }
}


void Peach::bonk() {
    if (invicibility || m_temp_invincibility)           //  if an Enemy bonks peach while invincible, do nothing
        return;
    if (!getWorld()->blocks(getX(), getY() + 4)) {     //   if Peach is not bonking a block, and ONLY enemies,
        decHP();                                        //      switch off powers and decrease a hit point
        m_temp_invincibility = true;
        m_temp_invinc_ticks = 10;
        if (m_shoot) {
            m_shoot = false;
        }
        if (m_jump) {
            m_jump = false;
        }
        if (m_hp >= 1)                              //  if still alive after hit, play hurt, or else just end Peach
            getWorld()->playSound(SOUND_PLAYER_HURT);
        if (m_hp <= 0)
            setStatus(0);
    }
}
