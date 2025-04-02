/*
  Noble.cpp
  Evan Lee
  The Noble class for WarriorCraft
  3/23/2023
*/

#include <vector>
#include <string>
#include <iostream>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft{
    /**
     * @brief           constructs a new Noble with given parameters
     * @param iName     the input name of the noble
     * @param isAlive   a boolean to check whether the noble is alive
     *                  nobles are created alive
    */
    Noble::Noble(const string& iName) : name(iName), isAlive(true){}

    /**
     * @brief   returns the name of the noble
     * @return  the name of the noble (as a string)
    */
    const string& Noble::getName() const{return name;}
    /**
     * @brief   returns if the noble is alive
     * @return  a boolean on if the noble is alive
    */
    bool getAlive() const{
        return isAlive;
    }
    /**
     * @brief   hires a warrior
     * @param   warrior the warrior to hire
    */
    bool Noble::hire(Warrior& warrior){
        // checks if:
        // a) the warrior is not currently employed
        // b) the noble is alive
        if (warrior.isHired() == false && isAlive){
            // creates a pointer to the warrior reference
            Warrior* warriorP(&warrior);
            // adds the pointer to the noble's army
            armyList.push_back(warriorP);
            // the warrior is now employed
            warrior.setHired(true);
            // the warrior's employer is the noble
            warrior.setEmployer(this);
            // the hiring was a success
            return true;
        }
        else{
            // otherwise, the noble did not hire the warrior
            cout << 
            name << " failed to hire " << warrior.getName() 
            << endl;
            return false;
        }
    }

    /**
     * @brief   fires a warrior from the noble's army
     * @param   warrior the warrior to fire
     * @param   runaway if the warrior ran away
    */
    bool Noble::fire(Warrior& warrior, bool runaway){
        // initializes a warriorPosition 
        // to find the position of the warrior in the army
        size_t warriorPosition = armyList.size();
        // if the noble is alive
        if (isAlive){
            // iterates through the warrior list
            for (size_t i = 0; i < armyList.size(); i++){
                // if the warrior is found in the army
                // uses the reference and doesn't check name,
                // because different warriors can have the
                // same name
                if (armyList[i] == &warrior){
                    // saves the position of the warrior
                    warriorPosition = i;
                    // sets the warrior to no longer be unemployed
                    warrior.setHired(false);
                    // sets the warrior's employer to be a nullptr
                    warrior.setEmployer(nullptr);
                    // sends a message if the warrior was fired
                    // ie the warrior did not run away
                    if (runaway == false){
                        cout << 
                        warrior.getName() << 
                        " you don't work for me any more! -- " << name 
                        << endl;
                    }
                }
            }
            
            // if the warrior was found in the army
            if (warriorPosition != armyList.size()){
                // shift all elements in the army left, starting with the warrior
                for (size_t i = warriorPosition; i < armyList.size(); i++){
                    armyList[i] = armyList[i+1];
                }
                // remove the final warrior pointer in the army 
                // this is OK because this warrior pointer will be the same as
                // the second-to-last element in the army
                armyList.pop_back();
                // return that the firing was a success
                return true;
            }
        
            // if the warrior is not in the army,
            // the noble cannot fire the warrior
            cout << 
            name << " failed to fire " << warrior.getName() 
            << endl;
            return false;
        }
        
        else{
            // if the noble is dead,
            // the noble cannot fire the warrior
            cout << 
            name << " failed to fire " << warrior.getName() 
            << endl;
            return false;}
    }

    /**
     * @brief for when the noble dies (loses a battle)
     */
    void Noble::die(){
        // they are no longer alive
        isAlive = false;
        // set all the strengths of all the warriors in their army to 0
        for (size_t i = 0; i < armyList.size(); i++){
            armyList[i]->setStrength(0);
        }
    }

    /**
     * @brief   returns the strength of the noble's army
     * @return  the strength of the noble's army (as a double)
    */
    double Noble::getStrength() const{
        // default sets the noble's strength to 0
        double totalStrength = 0;
        // for each warrior in the noble's army,
        // add their strength to the total strength of the army
        for (size_t i = 0; i < armyList.size(); i++){
            totalStrength += armyList[i]->getStrength();
        }
        // return the final strength of the warriors in the noble's army
        return totalStrength;
    }
    /**
     * @brief               sets the strength of a warrior's army after a battle
     * @param armyStrength  the current strength of the warrior's army
     * @param enemyStrength the current strength of the enemy noble's army
    */
    void Noble::setArmyStrength(double armyStrength, double enemyStrength){
        // for each warrior in the army
        for (size_t i = 0; i < armyList.size(); i++){
            // subtracts a portion of their strength equal
            // to the ratio between the two armies' strengths
            armyList[i]->setStrength(
                armyList[i]->getStrength() * 
                (1 - (enemyStrength / armyStrength))
                );
            }

    }
    /**
     * @brief   simulates a battle between two armies
     * @param   enemy the enemy noble to fight
    */
    void Noble::battle(Noble& enemy){
        // Displays who is battling whome
        cout << name << " battles " << enemy.name << endl;
        // Checks if the noble is battling themselves.
        Noble* enemyP(&enemy);
        if (this == enemyP){
            cout << 
            "Silly " << name << ", you can't battle yourself!" 
            << endl;
        }
        
        // Checks if both nobles are dead
        if (isAlive == false && enemy.isAlive == false){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        // Checks if this noble is dead
        else if(isAlive == false){
            cout << "He's dead, " << enemy.name << endl;
        }
        // Checks if the enemy noble is dead
        else if(enemy.isAlive == false){
            cout << "He's dead, " << name << endl;
        }
        // Checks if the two nobles have the same strength
        // If they do, since neither of them are dead, they will then kill eachother
        else if (getStrength() == enemy.getStrength()){
            cout 
            << "Mutual Annihilation: " << 
            name << " and " << enemy.name << 
            " die at each other's hands" << endl;
            enemy.die();
            die();
        }
        // Checks if this noble is stronger than the enemy
        // This noble loses army strength equal to the other noble
        // Kills the other noble
        else if(getStrength() > enemy.getStrength()){
            cout << name << " defeats " << enemy.name << endl;
            setArmyStrength(getStrength(), enemy.getStrength());
            enemy.die();
        }
        // Checks if the other noble is stronger than this one
        // The other noble loses army strength equal to the other noble
        // This kills this noble
        else if(enemy.getStrength() > getStrength()){
            cout << name << " defeats " << enemy.name << endl;
            enemy.setArmyStrength(enemy.getStrength(), getStrength());
            die();
        }
    }

    /**
     * @brief           overloads << operator for the warrior class
     * @param os        specified output stream
     * @param noble     specified noble to print
     * @return          ostream& output stream with noble's name,
     *                  the size of their army, and the warriors in their army
    */
    ostream& operator<<(ostream&os, const Noble& noble){
        os << 
        noble.name << " has an army of " << noble.armyList.size();
        for (size_t i = 0; i < noble.armyList.size(); i++) {
            if (noble.armyList[i] != nullptr) {
                os << "\n \t" << *noble.armyList[i];
            }
        }
        return os;
    }

}