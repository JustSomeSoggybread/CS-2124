#include <string>
#include <vector>
#include <iostream>

#ifndef PROTECTOR_H
#define PROTECTOR_H

namespace WarriorCraft{
    class Lord;

    class Protector{
    public:
        /**
         * @brief           constructs a new Protector with given parameters
         * @param iName     the name of the protector
         * @param iStrength the strength of the protector
        */
        Protector(const std::string& iName, double iStrength);
        /**
         * @brief       displays the Protector's strength
         * @param os    the stream to output to
        */
        void display(std::ostream& os) const;
        /**
         * @brief   returns the name of the protector
        */
        std::string getName() const;
        /**
         * @brief   returns the strength of the protector
        */
        double getStrength() const;
        /**
         * @brief   returns if the protector is alive
        */
        bool getAlive() const;
        /**
         * @brief   returns the protector's lord
        */
        Lord* getLord() const;
        /**
         * @brief           designates a new lord
         * @param setLord   the new lord to set to
        */
        void setLord(Lord* setLord);
        /**
         * @brief           sets the protector's strength to a specified amount
         * @param newStr    the new strength to set to
        */
        void setStrength(double newStr);
        /**
         * @brief   triggers the protector's battlecry
        */
        virtual void battlecry() const = 0;
        /**
         * @brief   simulates the protector running away
        */
        bool runaway();

        // friend output operator
        friend std::ostream& operator<<(std::ostream& os, const Protector& prot);

    // private variables of the Protector
    private:
        std::string name;
        double strength;
        Lord* lord;
        bool isAlive;
    };
    class Wizard : public Protector{
    public:
        /**
         * @brief           creates a wizard protector
         * @param iName     the name of the wizard
         * @param iStrength the strength of the wizard
        */
        Wizard(const std::string& iName, double iStrength);
        /**
         * @brief   triggers the wizard's battlecry
        */
        void battlecry() const;
    private:
    };

    class Warrior : public Protector{
        public:
        /**
         * @brief           creates a warrior protector
         * @param iName     the name of the warrior
         * @param iStrength the strength of the warrior
        */
        Warrior(const std::string& iName, double iStrength);
        /**
         * @brief   triggers the warrior's battlecry
        */
        void battlecry() const;

    private:
    };

    class Archer : public Warrior{
        public:
        /**
         * @brief           creates an archer warrior
         * @param iName     the name of the archer
         * @param iStrength the strength of the archer
        */
        Archer(const std::string& iName, double iStrength);
        /**
         * @brief   triggers the archer's battlecry
        */
        void battlecry() const;

    private:
    };

    class Swordsman : public Warrior{
        public:
        /**
         * @brief           creates a swordsman protector
         * @param iName     the name of the swordsman
         * @param iStrength the strength of the swordsman
        */
        Swordsman(const std::string& iName, double iStrength);
        /**
         * @brief   triggers the swordsman's battlecry
        */
        void battlecry() const;

    private:
    };
}
#endif