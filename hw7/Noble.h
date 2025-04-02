
#include <string>
#include <vector>
#include <iostream>

#ifndef NOBLE_H
#define NOBLE_H
namespace WarriorCraft{
    class Protector;

    class Noble{
    public:
        /**
         * @brief           constructs a new Noble with given parameters
         * @param iName     the input name of the noble
         * @param iStrength the input strength of the noble. Default set to 0.
         * @param isAlive   a boolean to check whether the noble is alive
         *                  nobles are created alive. Default set to true.
        */
        Noble(const std::string& iName, double iStrength);
        /**
         * @brief   returns the name of the noble
         * @return  the name of the noble (as a string)
        */
        std::string getName() const;
        /**
         * @brief   returns the strength of the noble
         * @return  the strength of the noble (as a double)
        */
        double getStrength() const;
        /**
         * @brief           sets the strength of the lord
         * @param newStr    the new strength to set the lord's strength to
        */
        void setStrength(double newStr);
        /**
         * @brief   returns if the noble is alive
         * @return  a boolean on if the noble is alive
        */
        bool getAlive() const;
        /**
         * @brief   sets the lord's "alive" status to false, 
         *          sets their strength to 0
        */
        void die();
        /**
         * @brief   triggers the noble's battlecry
        */
        virtual void battlecry() const = 0;
        /**
         * @brief       simulates a battle between two armies
         * @param enemy the enemy noble to fight
        */
        void battle(Noble& enemy);
        /**
         * @brief               calculates the strength of a noble after a battle
         * @param thisStrength  the strength of this noble
         * @param enemyStrength the strength of the enemy noble
        */
        virtual void calcStrength(double thisStrength, double enemyStrength);

        /**
         * @brief       displays the Noble's strength
         * @param os    the outstream to display to
        */
        virtual void display(std::ostream& os) const = 0;
        //declare friend output operator for the noble
        friend std::ostream& operator<<(std::ostream&, const Noble&);

    //protected variables for the noble class
    //  note: Lord and PersonWithStrengthToFight
    //  also use these, so it's easier to use protected vs private
    private:
        std::string name;
        double strength;
        bool isAlive;
    };

    // Class for "Those Who Are Lords of the Land"
    class Lord : public Noble{
    public:
        /**
         * @brief       constructs a new lord with the given parameter
         * @param iName the name of the lord
        */
        Lord(const std::string& iName);
        /**
         * @brief finds the strength of the lord's standing army
        */
        double getArmyStrength() const;
        /**
         * @brief           hires a protector into the lord's army
         * @param toHire    the protector to hire
        */
        bool hires(Protector& toHire);
        /**
         * @brief           fires a protector from the lord's army
         * @param toFire    the protector to fire
        */
        bool fires(Protector& toFire);
        /**
         * @brief       simulates a protector running away from the lord's army
         * @param toRun the protector to run away from the lord's army
        */
        bool runsAway(Protector&);
        /**
         * @brief   triggers the lord's battlecry
        */
        void battlecry() const;
        /**
         * @brief   calculates the strength of the lord's army after a battle
         * @param thisStrength  the strength of this noble
         * @param enemyStrength the strength of the enemy noble
        */
        void calcStrength(double thisStrength, double enemyStrength);

        /**
         * @brief       displays a lord's army
         * @param os    the stream to output to
        */
        void display(std::ostream& os) const;

    private:
        std::vector<Protector*> armyList;
    };

    class PersonWithStrengthToFight : public Noble{
    public:
        /**
         * @brief           constructs a new person with strength to fight with the given parameter
         * @param iName     the name of the person with strength to fight
         * @param iStrength the strength of the person
        */
        PersonWithStrengthToFight(const std::string&, double);
        /**
         * @brief   triggers the person with strength to fight's battlecry
        */
        void battlecry() const;
        /**
         * @brief       displays a person's strength
         * @param os    the stream to output to
        */
       void display(std::ostream& os) const;    
    private:
    };
}
#endif