//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>

using namespace std;

//TODO: Check the circular dependency
int maxHealth = 0;

int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false) {
    maxHealth = health;
}

int Enemy::getMaxHealth (){
    return maxHealth;
}

void Enemy::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Enemy::takeDamage(int damage) {
    bool wow = false;
    if (getAttack() > 15) {
        wow = true;
    }
    setHealth(getHealth() - damage);

    if(getHealth() <= 0) {
        if (wow = false) {
            cout << "\t" << getName() << " has died" << endl;
            cout << "\n\n";
            cin.get();
        }
        if (wow = true) {
            cout << "\t" << getName() << " has died" << endl;
            cout << "\n\n";
            cin.get();
        }
    }
    else {
        if (wow = false) {
            cout <<"\t" << getName() << " has taken " << damage << " damage" << endl;
            cout << "\n\n";
            cin.get();
        }
        if (wow = true) {
            cout << "\t " << getName() << " has taken " << damage << " damage" << endl;
            cout << "\n\n";
            cin.get();
        }
    }
}

Character* Enemy::getTarget(vector<Player *> teamMembers) {
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for (int i = 0; i < teamMembers.size(); i++) {
        ;
        if(teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

Action Enemy::takeAction(vector<Player*> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    myAction.target = target;
    if ((this->getMaxHealth() * 0.50 >= this->getHealth()) && rand() % 100 < 50) {
        myAction.action = [this, target]() {
            this->fleed = true;
        };
    }
    else {
        myAction.action = [this, target]() {
            doAttack(target);
        };
    }

    return myAction;
}