/*
  Warrior.cpp
  Evan Lee
  The warrior class for WarriorCraft
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
     * @brief           constructs a new Warrior with given parameters
     * @param iName     the given name of the warrior
     * @param iStrength the given strength of the warrior
    */
    Warrior::Warrior(const string& iName, double iStrength) : 
                                                        name(iName), 
                                                        strength(iStrength), 
                                                        hired(false){}
    /**
     * @brief   returns the name of the warrior
     * @return  the name of the warrior (as a string)
    */
    const string& Warrior::getName() const{return name;}
    /**
     * @brief   returns the strength of the warrior
     * @return  the strength of the warrior (as a double)
    */
    double Warrior::getStrength() const{return strength;}
    /**
     * @brief   returns whether the warrior is hired
     * @return  whether the warrior is hired (as a boolean)
    */
    bool Warrior::isHired() const{return hired;}
    /**
     * @brief   sets the strength of the warrior
     * @param   amount the strength to set warrior's set to
    */
    void Warrior::setStrength(double amount) { strength = amount;}
    /**
     * @brief   sets whether the warrior has been hired or not
     * @param   isHired the boolean to set
    */
    void Warrior::setHired(bool isHired){ hired = isHired;}
    /**
     * @brief   sets the warrior's employer
     * @param   noble the noble hiring the warrior
    */
    void Warrior::setEmployer(Noble* noble){
        employer = noble;
    }
    /**
     * @brief simulates the warrior running away from a noble
    */
    bool Warrior::runaway(){
        if (employer != nullptr){
            cout << name << " flees in terror, abandoning his lord " <<
            employer->getName() << endl;
            employer->fire(*this, true);
            return true;
        }
        else{
            cout << name << " is already unemployed." << endl;
            return false;
        }
    }
    /**
     * @brief           overloads << operator for the warrior class
     * @param os        specified output stream
     * @param warrior   specified warrior to print
     * @return          ostream& output stream with warrior's name and strength
    */
    ostream& operator<<(ostream&os, const Warrior& warrior){
        os << warrior.name << ": " << warrior.strength;
        return os;
    }
}