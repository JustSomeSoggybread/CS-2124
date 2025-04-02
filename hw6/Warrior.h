/*
  Warrior.h
  Evan Lee
  The warrior header for WarriorCraft
  3/23/2023
*/

#include <string>
#include <iostream>

#ifndef WARRIOR_H
#define WARRIOR_H

namespace WarriorCraft {
    class Noble; 
    class Warrior{
    public:
        /**
         * @brief   returns the name of the warrior
         * @return  the name of the warrior (as a string)
        */
        Warrior(const std::string&, double);
        /**
         * @brief   returns the name of the warrior
         * @return  the name of the warrior (as a string)
        */
        const std::string& getName() const;
        /**
         * @brief   returns the strength of the warrior
         * @return  the strength of the warrior (as a double)
        */
        double getStrength() const;
        /**
         * @brief   returns whether the warrior is hired
         * @return  whether the warrior is hired (as a boolean)
        */
        bool isHired() const;
        /**
         * @brief   sets the strength of the warrior
         * @param   amount the strength to set warrior's set to
        */
        void setStrength(double);
        /**
         * @brief   sets whether the warrior has been hired or not
         * @param   isHired the boolean to set
        */
        void setHired(bool);
        /**
         * @brief   sets the warrior's employer
         * @param   noble the noble hiring the warrior
        */
        void setEmployer(Noble*);
        /**
         * @brief simulates the warrior running away from a noble
        */
        bool runaway();
        
        // friend operator
        friend std::ostream& operator<<(std::ostream&, const Warrior&);
    private:
    // private variables for the warrior
        std::string name;
        double strength;
        bool hired;
        Noble* employer;
    };
    
}
#endif