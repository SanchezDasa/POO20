//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include <algorithm>
#include "../Utils.h"

      

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, true) {
    experience = 0;
    level = 1;
    depression = 0;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    if (health <= 0) {
        cout << "\t Muerto " << endl;
        cout << "\n";
        cin.get();
        exit(-1);
    }
    else {
        cout << "\t Recibiste "  << damage << " de daamage"  << endl;
        cout << "\n";
        Depression(5);
        cin.get();
    }
}
         

   


void Player::flee(vector<Enemy*> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy* fastestEnemy = enemies[0];
    bool fleed = false;
    if(this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed =  true;
    }
    else {
        srand(time(NULL));
        int chance = rand() % 100;
        cout<< "chance de ser gojo : " << chance << endl;
        cout << "\n";
        if (fleed = chance > 90) {
            fleed = true;
        }
        else {
            cout << "\t moriste gojo" << endl;
            cout << "\n\n";
        }
    }

    this->fleed = fleed;
}

void Player::emote() {
    cout<<"sukuna se ríe" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);

    cout << "\t>Subiste de nivel:" << level << endl;
    cout << "\n\n";
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}

Character* Player::getTarget(vector<Enemy*> enemies) {
    int targetIndex = 0;
    while (true) {
        cout << "Selecciona victima" << endl;
        for (int i = 0; i < enemies.size(); i++) {
            cout << i  << ". " << enemies[i]->getName() << endl;
        } 
        cout << "> ";
        cin >> targetIndex;
        cout << "\n";
        if (targetIndex  >= enemies.size() || targetIndex < 0) {
            cout <<"\tOpcion invalida" << endl;
            cout << "\n";
        }
        else break;
    }   
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int option = 0;
    bool oks = false;
    Character* target = nullptr;
    bool fleed = false;
    Action myAction;
    
    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    while (oks == false){
        cout << "Selecciona una accion" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Flee" << endl;
        cout << "> ";
        cin >> option;
        cout << "\n";
        switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            myAction.action = [this, target]() {
                doAttack(target);
                gainExperience(33);
            };
            oks = true;
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            oks = true;
            break;
        default:
            cout << "\t Opcion invalida" << endl;
            cout << "\n";
            break;
        }
    }
    return myAction;
}
void Player::Depression(int depre){
    depression = depression + depre;
    if ((depression > 50) && (rand() % 100 > 90)) {
        if (rand() % 100 > 50) {
            Suicide();
        }
    }
}
void Player::Suicide() {
        setHealth(getHealth() == 0);
        cout << "\n"; 
        cout << "\t Has seleccionado la suicidación" << endl;
        cout << "\n";
        cin.get();
        exit(-1);
   

}