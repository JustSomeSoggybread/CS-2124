#include <vector>
#include <string>
#include <iostream>
#include "Noble.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft{
    /**
     * @brief           constructs a new Protector with given parameters
     * @param iName     the name of the protector
     * @param iStrength the strength of the protector
    */
    Protector::Protector(const string& iName, double iStrength) : name(iName), strength(iStrength), lord(nullptr), isAlive(true) {}
    /**
     * @brief   returns the name of the protector
    */
    string Protector::getName() const{
        return name;
    }
    /**
     * @brief   returns the strength of the protector
    */
    double Protector::getStrength() const{
        return strength;
    }
    /**
     * @brief   returns if the protector is alive
    */
    bool Protector::getAlive() const{
        return isAlive;
    }
    /**
     * @brief   returns the protector's lord
    */
    Lord* Protector::getLord() const{
        return lord;
    }
    /**
     * @brief           designates a new lord
     * @param setLord   the new lord to set to
    */
    void Protector::setLord(Lord* setLord){
        lord = setLord;
    }
    /**
     * @brief           sets the protector's strength to a specified amount
     * @param newStr    the new strength to set to
    */
    void Protector::setStrength(double newStrength){
        strength = newStrength;
        if (strength == 0){
            isAlive = false;
        }
    }
    /**
     * @brief   simulates the protector running away
    */
    bool Protector::runaway(){
        if (isAlive){
            if (lord != nullptr){
                cout  << name << " flees in terror, abandoning his lord, " 
                        << lord->getName() << endl;
                lord->runsAway(*this);
                return true;
            }
            else{
                cout << name << " doesn't have a lord to run away from!" << endl;
                return false;
            }
        }
        else{
            cout << name << " can't run away, they're dead!" << endl;
            return false;
        }
    }
    /**
     * @brief       displays the Protector's strength
     * @param os    the stream to output to
     */
    void Protector::display(ostream& os) const{
        os << "\n\t" << name << " has strength " << strength;
    }

    // friend outstream operator
    ostream& operator<<(ostream& os, const Protector& prot){
        prot.display(os);
        return os;
    } 
    /**
     * @brief           creates a wizard protector
     * @param iName     the name of the wizard
     * @param iStrength the strength of the wizard
    */
    Wizard::Wizard(const string& iName, double iStrength) : Protector(iName, iStrength) {}
    /**
     * @brief   triggers the wizard's battlecry
    */
    void Wizard::battlecry() const{
        if (getAlive()){
            cout << "POOF!" << endl;
        }
    }
    /**
     * @brief           creates a warrior protector
     * @param iName     the name of the warrior
     * @param iStrength the strength of the warrior
    */
    Warrior::Warrior(const string& iName, double iStrength) : Protector(iName, iStrength) {}
    /**
     * @brief   triggers the warrior's battlecry
    */
    void Warrior::battlecry() const{
        cout << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
    }
    /**
     * @brief           creates an archer warrior
     * @param iName     the name of the archer
     * @param iStrength the strength of the archer
    */
    Archer::Archer(const string& iName, double iStrength) : Warrior(iName, iStrength) {}
    /**
     * @brief   triggers the archer's battlecry
    */
    void Archer::battlecry() const{
        if (getAlive()){
            cout << "TWANG!\t";
            Warrior::battlecry();
        }
    }
    /**
     * @brief           creates a swordsman protector
     * @param iName     the name of the swordsman
     * @param iStrength the strength of the swordsman
    */
    Swordsman::Swordsman(const string& iName, double iStrength) : Warrior(iName, iStrength) {}
    /**
     * @brief   triggers the swordsman's battlecry
    */
    void Swordsman::battlecry() const {
        if (getAlive()){
            cout << "CLANG!\t";
            Warrior::battlecry();
        }
    }
}