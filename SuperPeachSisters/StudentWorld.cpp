#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
using namespace std;

void StudentWorld::setLevelStatus(int complete) {
    if (complete == 1)      //  if flag sent signal, alert level is finished
        levelComplete = true;
    if (complete == 2)      //  if mario sent signal, alert game is won
        hitMario = true;
}


GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_Peach = nullptr;
    levelComplete = false;
    hitMario = false;
}

int StudentWorld::init()
{
    Level lev(assetPath());

    ostringstream level;                //  get the current level create a string off that to read the proper text file
    level.setf(ios::fixed);
    level << "level0" << getLevel() << ".txt";
    string a = level.str();

    string level_file = a;
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find " << a <<  " data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << a << " is improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                ge = lev.getContentsOf(x, y);           // read the contents each (x, y) coordinate
                
                switch (ge) {
                    case Level::empty:
                        break;
                    case Level::peach: {                    // if peach, create a peach object
                        m_Peach = new Peach(x, y, this);
                        break;
                    }
                    case Level::koopa:
                    {
                        int direction = randInt(0, 1);      //  choose direction randomly
                        if (direction == 0)
                            Actors.push_back(new Koopa(x, y, 0, this)); //  create Koopa object
                        else
                            Actors.push_back(new Koopa(x, y, 180, this));
                        break;
                    }
                    case Level::goomba:
                    {
                        int direction = randInt(0, 1);      //  choose direction randomly
                        if (direction == 0)
                            Actors.push_back(new Goomba(x, y, 0, this));    //  create Goomba object
                        else
                            Actors.push_back(new Goomba(x, y, 180, this));
                        break;
                    }
                    case Level::piranha:            
                    {
                        int direction = randInt(0, 1);      //  choose direction randomly
                        if (direction == 0)
                            Actors.push_back(new Piranha(x, y, 0, this));   //  create Koopa object
                        else
                            Actors.push_back(new Piranha(x, y, 180, this));
                        break;
                    }
                    case Level::block:
                        Actors.push_back(new Block(IID_BLOCK, x, y, this)); //  create Block object
                        break;
                    case Level::star_goodie_block:
                        Actors.push_back(new Block(IID_BLOCK, x, y, this, "Star")); //  create Block object with Star
                        break;
                    case Level::mushroom_goodie_block:
                        Actors.push_back(new Block(IID_BLOCK, x, y, this, "Mushroom")); //  create Block object with Mushroom
                        break;
                    case Level::flower_goodie_block:
                        Actors.push_back(new Block(IID_BLOCK, x, y, this, "Flower"));   //  create Block object with Flower
                        break;
                    case Level::pipe:
                        Actors.push_back(new Pipe(x, y, this)); //  create Pipe object
                        break;
                    case Level::flag:
                        Actors.push_back(new Flag(x, y, this)); //  create Flag object
                        break;
                    case Level::mario:
                        Actors.push_back(new Mario(x, y, this));    //  create Mario object
                        break;
                    default:
                        break;
                }
                
            }
        }
        
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    
    std::vector<Actor*>::iterator temp;
    temp = Actors.begin();
    getPeach()->doSomething();
    while (temp != Actors.end()) {          //  iterate through the vector and make each Actor do something
        if ((*temp)->getStatus()) {
            (*temp)->doSomething();
            if (!m_Peach->getStatus())  { //   if peach died, decrease lives and continue game again
                decLives();
                playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
            }
            if (hitMario) {                 //   if hit mario, then the game is won
                playSound(SOUND_GAME_OVER);
                return GWSTATUS_PLAYER_WON;
            }
                
            if (levelComplete) {            //   if the level is complete, then move to the next level
                levelComplete = 0;
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
                
        }
        temp++;
    }
   
    // delete the dead characters in the list
    temp = Actors.begin();                  //  If there are any dead characters in the list, then remove them
    while (temp != Actors.end()) {
        if (!(*temp)->getStatus()) {
            Actor * killMe = * temp;
            Actors.erase(temp);
            delete killMe;
        }
        else
            temp++;
    }

    //   Update the text at the top of the game by creating a string to be displayed
    ostringstream text;
    text.setf(ios::fixed);
    text.fill('0');
    text << "Lives: " << setw(1) << getLives() << "  " << "Level: " << setw(2) << getLevel() << "  " << "Points: " << setw(6) << getScore();
    string s = text.str();
    if (getPeach()->getShoot()) {       // If player has shoot power, then display shoot power
        s+= " ShootPower!";
    }
    if (getPeach()->getJump()) {        //   If player has jump, then display jump
        s+= " JumpPower!";
    }
    if (getPeach()->getStar()) {       //   if player has star power, then dispay star power
        s+= " StarPower!";
    }
    setGameStatText(s);                 // display the text
    // Update the game status line
   
    // the player hasn’t completed the current level and hasn’t died, so // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //  delete all the actors in the list when cleaning up program
    delete m_Peach;
    std::vector<Actor*>::iterator temp;
    temp = Actors.begin();
    while (temp != Actors.end()) {
        Actor * killMe = *temp;
        delete killMe;
        temp = Actors.erase(temp);
    }
}

StudentWorld::~StudentWorld() {
    cleanUp(); }

// ********************************************* //
// ********************************************* //
// ********************************************* //

// Determine if two Sprites are overlapping and return true if overlapping and false otherwise
bool StudentWorld::isOverlap(int ax, int ay, int bx, int by) {
    if (ax + SPRITE_WIDTH > bx && ax < bx + SPRITE_WIDTH) {
        if (ay + SPRITE_HEIGHT > by && ay < by + SPRITE_HEIGHT)
            return true;
    }
    return false;
}

Actor * StudentWorld::isBlockingAt(int x, int y) {
    std::vector<Actor*>::iterator temp;                 //  if an Actor overlaps with another object
    temp = Actors.begin();                              //      in the vector, then return the object
    while (temp != Actors.end()) {                      //      else return nullptr
        if (isOverlap(x, y, (*temp)->getX(), (*temp)->getY())) {
                return *temp;
        }
        temp++;
    }
    return nullptr;
}



bool StudentWorld::blocks(int x, int y) {           //  if an Actor overlaps with another object that blocks movement
    std::vector<Actor*>::iterator temp;             //      in the vector, then return the object thats blocking movement
    temp = Actors.begin();                          //      else return nullptr
    while (temp != Actors.end()) {
        if (isOverlap(x, y, (*temp)->getX(), (*temp)->getY()) && (*temp)->getBlock()) {
            return true;
        }
        temp++;
    }
    return false;
}

Actor * StudentWorld::FireOverlap(int x, int y) {   // If an Actor overlaps with an object thats 1)Alive, 2) Damageable
    std::vector<Actor*>::iterator temp;             //      3) not Peach, then return the object
    temp = Actors.begin();
    while (temp != Actors.end()) {
        if (isOverlap(x, y, (*temp)->getX(), (*temp)->getY()) && (*temp)->getStatus()) {
            if ((*temp)->getDamageable()){
                if (!isOverlap(x, y, getPeach()->getX(), getPeach()->getY()))
                    return *temp;
            }
            if (blocks((*temp)->getX() + 1, (*temp)->getY())) {     //  if Actor overlaps with a Block, return the block's ptr
                return *temp;
            }
            if (blocks((*temp)->getX() - 1, (*temp)->getY())) {     //  if Actor overlaps with a Block, return the block's ptr
                return *temp;
            }
        }
    temp++;
    }
    return nullptr;
}

void StudentWorld::addActor(Actor * newActor) {     //   Add a new actor to the vector when created
    Actors.push_back(newActor);
}

void StudentWorld::bonk(int x, int y) {             //   if Actor overlaps with another Actor, then bonk the Actor
    vector<Actor*>::iterator it;
    it = Actors.begin();
    while (it != Actors.end()) {                // iterating through the vector
        if (isOverlap(x, y, (*it)->getX(), (*it)->getY())) {
            (*it)->bonk();
            
        }
        it++;
    }
}
