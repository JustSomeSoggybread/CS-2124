#include <vector>
#include <string>
#include <iostream>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft{
    /**
     * @brief           constructs a new Noble with given parameters
     * @param iName     the input name of the noble
     * @param iStrength the input strength of the noble. Default set to 0.
     * @param isAlive   a boolean to check whether the noble is alive
     *                  nobles are created alive. Default set to true.
    */
    Noble::Noble(const string& iName, double iStrength = 0) : name(iName), strength(iStrength), isAlive(true){}
    /**
     * @brief   returns the name of the noble
     * @return  the name of the noble (as a string)
    */
    string Noble::getName() const{
        return name;
    }
    /**
     * @brief   returns the strength of the noble
     * @return  the strength of the noble (as a double)
    */
    double Noble::getStrength() const{
        return strength;
    }
    /**
     * @brief       simulates a battle between two armies
     * @param enemy the enemy noble to fight
    */
    void Noble::setStrength(double newStrength){
        strength = newStrength;
    }
    /**
     * @brief   returns if the noble is alive
     * @return  a boolean on if the noble is alive
    */
    bool Noble::getAlive() const{
        return isAlive;
    }
    /**
     * @brief   sets the lord's "alive" status to false, 
     *          sets their strength to 0
    */
    void Noble::die(){
        strength = 0;
        isAlive = false;
    }
    /**
     * @brief       simulates a battle between two armies
     * @param enemy the enemy noble to fight
    */
    void Noble::battle(Noble& enemy){
        cout  << name  << " battles " << enemy.name 
            << endl;
        
        if (isAlive){
            battlecry();
        }
        if (enemy.getAlive()){
            enemy.battlecry();
        }
        if (!isAlive && !enemy.getAlive()){
            cout  << "Oh, NO! They're both dead! YUCK!" 
                << endl;
        }
        else if (!(isAlive)){
            cout  << "He's dead, " << enemy.name 
                << endl;
        }
        else if (!(enemy.getAlive())){
            cout  << "He's dead, " << name 
                << endl;
        }
        else{
            double tempStrength = strength;
            double tempEStrength = enemy.strength;
            calcStrength(tempStrength, tempEStrength);
            enemy.calcStrength(tempEStrength, tempStrength);
            if (strength > enemy.strength){
                cout << name << " defeats " << enemy.name << endl;
            }
            else if (strength < enemy.strength) {
                cout << enemy.name << " defeats " << name << endl;
            }
            else{
                cout  << "Mutual Annihilation: " 
                    << name << " and " << enemy.name 
                    << " die at each other's hands" 
                    << endl;
            }
        }
    }
    /**
     * @brief               calculates the strength of a noble after a battle
     * @param thisStrength  the strength of this noble
     * @param enemyStrength the strength of the enemy noble
    */
    void Noble::calcStrength(double thisStrength, double otherStrength){
        double calcRatio = otherStrength/thisStrength;
        if (calcRatio < 1){
            strength = strength * (1-calcRatio);
        }
        else{
            strength = 0;
            isAlive = false;
        }
    }
    
    /**
     * @brief       constructs a new lord with the given parameter
     * @param iName the name of the lord
    */
    Lord::Lord(const string& iName) : Noble(iName){}
    /**
     * @brief finds the strength of the lord's standing army
    */
    double Lord::getArmyStrength() const{
        double retStrength = 0;
        for (size_t i = 0; i < armyList.size(); i++){
            retStrength += armyList[i]->getStrength();
        }
        return retStrength;
    }
    /**
     * @brief           hires a protector into the lord's army
     * @param toHire    the protector to hire
    */
    bool Lord::hires(Protector& toHire){ 
        if (getAlive() && toHire.getLord() == nullptr && toHire.getAlive() == true){
            armyList.push_back(&toHire);
            toHire.setLord(this);
            setStrength(getArmyStrength());
            return true;
        }
        return false;
    }
    /**
     * @brief           fires a protector from the lord's army
     * @param toFire    the protector to fire
    */
    bool Lord::fires(Protector& toFire){
        for (size_t i = 0; i < armyList.size(); i++){
            if (armyList[i] == &toFire){
                cout << toFire.getName() 
                << " you don't work for me anymore! -- " 
                << getName() 
                << endl;
                setStrength(getArmyStrength());
                toFire.setLord(nullptr);
                for (size_t i = 0; i < armyList.size(); i++){
                armyList[i] = armyList[i + 1];
                }
                armyList.pop_back();
                return true;
            }
        }
        cout  << "Did not find " << toFire.getName() 
            << " in " << getName() << "'s army." 
            << endl;
        return false;
    }
    /**
     * @brief       simulates a protector running away from the lord's army
     * @param toRun the protector to run away from the lord's army
    */
    bool Lord::runsAway(Protector& toRun){
        for (size_t i = 0; i < armyList.size(); i++){
            if (armyList[i] == &toRun){
                setStrength(getArmyStrength());
                toRun.setLord(nullptr);
                for (size_t i = 0; i < armyList.size(); i++){
                armyList[i] = armyList[i + 1];
                }
                armyList.pop_back();
                return true;
            }
        }
        return false;
    }
    /**
     * @brief   triggers the lord's battlecry
    */
    void Lord::battlecry() const{
        for (size_t i = 0; i < armyList.size(); i++){
            armyList[i]->battlecry();
        }
    }
    /**
     * @brief   calculates the strength of the lord's army after a battle
     * @param thisStrength  the strength of this noble
     * @param enemyStrength the strength of the enemy noble
    */
    void Lord::calcStrength(double thisStrength, double enemyStrength){
        double calcRatio = enemyStrength/thisStrength;
        for (size_t i = 0; i < armyList.size(); i++){
        if (calcRatio < 1){
            armyList[i]->setStrength(armyList[i]->getStrength() * (1-calcRatio));
        }
        else{
            armyList[i]->setStrength(0); 
        }
        }
        if (calcRatio >= 1){
        die();
        }
        else{
            setStrength(getArmyStrength());
        }
    }
    /**
     * @brief       displays a lord's army
     * @param os    the stream to display to
    */
    void Lord::display(ostream& os) const{
        os << getName() << " has an army of size: " << armyList.size();
        for (size_t i = 0; i < armyList.size(); ++i) {
            armyList[i]->display(os);
        }
    }

/**
     * @brief           constructs a new person with strength to fight with the given parameter
     * @param iName     the name of the person with strength to fight
     * @param iStrength the strength of the person
    */
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& iName, double iStrength) : Noble(iName, iStrength){}
    /**
     * @brief   triggers the person with strength to fight's battlecry
    */
    void PersonWithStrengthToFight::battlecry() const{
    cout << "Ugh!" << endl;
    }

    /**
     * @brief       displays a person's strength
     * @param os    the stream to output to
    */
    void PersonWithStrengthToFight::display(ostream& os) const{
        os << getName() << " has strength: " << getStrength();;
    }
    
    // output operator for noble (idk there doesn't seem to be requirement for it here)
    ostream& operator<<(ostream& os, const Noble& n){
        n.display(os);
        return os;
    }
}