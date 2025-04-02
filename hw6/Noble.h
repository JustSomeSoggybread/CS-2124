/*
  Noble.h
  Evan Lee
  The noble header for WarriorCraft
  3/23/2023
*/

#include <string>
#include <vector>
#include <iostream>

#ifndef NOBLE_H
#define NOBLE_H
namespace WarriorCraft {
    class Warrior; 
    class Noble{
    public:
        /**
         * @brief           constructs a new Noble with given parameters
         * @param iName     the input name of the noble
         * @param isAlive   a boolean to check whether the noble is alive
         *                  nobles are created alive
        */
        Noble(const std::string&);
        /**
         * @brief   returns the name of the noble
         * @return  the name of the noble (as a string)
        */
        const std::string& getName() const;
        /**
         * @brief   hires a warrior
         * @param   warrior the warrior to hire
        */
        bool hire(Warrior&);
        /**
         * @brief   fires a warrior from the noble's army
         * @param   warrior the warrior to fire
         * @param   runaway if the warrior ran away
        */
        bool fire(Warrior&, bool ranaway = false);
        /**
         * @brief for when the noble dies (loses a battle)
         */
        void die();
        /**
         * @brief   returns the strength of the noble's army
         * @return  the strength of the noble's army (as a double)
        */
        double getStrength() const;
        /**
         * @brief               sets the strength of a warrior's army after a battle
         * @param armyStrength  the current strength of the warrior's army
         * @param enemyStrength the current strength of the enemy noble's army
        */
        void setArmyStrength(double, double);
        /**
         * @brief   simulates a battle between two armies
         * @param   enemy the enemy noble to fight
        */
        void battle(Noble&);
        
        // declare friend operator for the warrior
        friend std::ostream& operator<<(std::ostream&, const Noble&);
        
    private:
        // private variables for the noble class
        std::vector<Warrior*> armyList;
        std::string name;
        bool isAlive;
    };
}
#endif