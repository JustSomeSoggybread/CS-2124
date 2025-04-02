// hw03.cpp
// Evan Lee
// 02/12/2023
// Model a game of medieval times of a world filled with warriors, 
// storing data for warriors and their weapons via classes

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief   used to represent a warrior
*/
class Warrior{

private:
    /**
     * @brief   used to represent a warrior's weapon
    */
    class Weapon{
    public:

        /**
         * @brief   constructs a weapon if no input parameters
        */
        Weapon(): weaponName("None"), weaponStrength(0){}

        /**
         * @brief   constructs a weapon if input parameters
         * @param   iWeaponName input weapon name
         * @param   iStrength input weapon strength
        */
        Weapon(const string& iWeaponName, int iStrength):
            weaponName(iWeaponName), weaponStrength(iStrength){}

        /**
         * @brief   returns the strength of the weapon
         * @return  strength of the weapon (as an int)
        */
        int getStrength() const{
            return weaponStrength;
        }

        /**
         * @brief   sets the strength of the weapon
         * @param   amount thespecified strength to set the weapon to
        */
        void setStrength(int amount) {
            weaponStrength = amount;
        };

        // declare operator<< as friend
        friend ostream& operator<<(ostream&os, const Weapon& weapon);

    // private weaponName and weaponStrength variables
    // for Weapon class, storing the weapon's strength
    // and name.
    private:
        string weaponName;
        int weaponStrength;
    };

    //private variables for the warrior
    string warriorName;
    // an empty weapon object is created, and then
    // warriorWeapon is reassigned to given inputs
    Weapon warriorWeapon = Weapon("", 0);

public:
    /**
     * @brief   constructs a new warrior with given parameters
     * @param   iName the input name of the warrior
     * @param   iWeaponname the input name of the warrior's weapon
     * @param   iStrength the input name of the weapon's strength
    */
    Warrior(const string& iName, const string& iWeaponName, int iStrength){
        warriorName = iName;
        // constructs a new Weapon object
        // and sets the warrior's weapon to 
        // the given name and strength
        warriorWeapon = Weapon(iWeaponName, iStrength);
    };

    /**
     * @brief   returns the strength of the warrior
     * @return  the strength of the warrior's weapon (as an int)
    */
    int getStrength() const{
        return warriorWeapon.getStrength();
    }

    /** 
     * @brief   returns the name of the warrior
     * @return  the name of the warrior (as a string)
    */
    string getName() const{
        return warriorName;
    }

    /**
     * @brief           sets the strength of the warrior's weapon
     * @param amount    the strength to set the weapon to
    */
    void setStrength(int amount) {
        warriorWeapon.setStrength(amount);
    }

    // declare friend operator<< for the warrior and their weapon
    friend ostream& operator<<(ostream&os, const Warrior&);
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);

};

//prototyping
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
ostream& operator<<(ostream& os, const Warrior& warrior);
void addWarrior(vector<Warrior>&, const string&, const string&, int);
void battleWarriors(vector<Warrior>&, const string&, const string&);
void battleResult(Warrior&, Warrior&);
void readStatus(const vector<Warrior>&);
size_t findWarrior(const vector<Warrior>&, const string&);

/**
 * @brief   model a medieval game
 * @return  0 on success (as an int)
*/
int main(){
    // Creates a vector of warriors
    vector<Warrior> warriorList;
    // Initializes an input stream
    ifstream inputStream;
    // Input stream opens "warriors.txt"
    inputStream.open("warriors.txt");

    // Exits if specified file does not exist
    if (!inputStream){
        cerr << "File not found at location" << endl;
        exit(1);
    }

    // Initializes a string to save the type of
    // command to be called
    string commandType;

    //Reads the command words and reads the following words
    // as according to the expected input
    // Warrior <string> <string> <int> to create a new warrior
    // Battle <string> <string> to have two warriors battle
    // Status to print out the status of all warriors  
    while(inputStream >> commandType){
        
        // Checks if the command is creating a new warrior
        if (commandType == "Warrior"){
            // If a new warrior is being created, assumes the
            // next two strings and int denote the warrior's 
            // name, the name of the warrior's weapon, and 
            // the strength of the weapon.
            string warriorName;
            string weaponName;
            int strength;

            inputStream >> warriorName >> weaponName >> strength;

            // Calls a function to add a new warrior with the 
            // specified name, weapon name, and strength
            addWarrior(warriorList, warriorName, weaponName, strength);
        }

        // Else, checks if the command was to have a battle.
        else if (commandType == "Battle"){
            // If a battle is being held, assumes the next two
            // strings name the two warriors fighting.
            string Warrior1;
            string Warrior2;
            inputStream >> Warrior1 >> Warrior2;

            // Calls a function to hold a battle between the two
            // warriors with the specified names
            battleWarriors(warriorList, Warrior1, Warrior2);
        }
        // Else, checks if command was to print status of warriors
        else if(commandType == "Status"){
            // Tells user if there is no warrior in the list
            if (warriorList.size() == 0){
                cout << "No warriors on list" << endl;
            }
            else{
                // Calls a function to read the status of the warriors
                // stored in the warriorList vector

                readStatus(warriorList);
            }
        }

    }
}

/**
 * @brief           overloads << operator for the warrior class
 * @param os        specified output stream
 * @param warrior   specified warrior to print
 * @return          ostream& output stream with warrior's name, warrior's weapon's name, and weapon strength
*/
ostream& operator<<(ostream&os, const Warrior& warrior){
    os << "Warrior: " << warrior.warriorName << ", weapon: " << warrior.warriorWeapon;
    return os;
}

/**
 * @brief           overloads << operator for the weapon class
 * @param os        specified output stream
 * @param weapon    specified weapon to print
 * @return          ostream& output stream with weapon's name and strength
*/
ostream& operator<<(ostream&os, const Warrior::Weapon& weapon){
        os << weapon.weaponName << ", " << weapon.weaponStrength;
        return os;
}

/**
 * @brief                   Given the parameters of a warrior, add the warrior to a list of warriors
 * @param warriorList       the list of warriors, stored as a vector
 * @param warriorName       the name of the warrior to be added
 * @param weaponName        the name of the warrior's weapon
 * @param warriorStrength   the strength of the warrior to be added
*/
void addWarrior(vector<Warrior>& warriorList, 
                const string& warriorName, 
                const string& weaponName,
                int strength){
    // If the warrior's name is already on the list, return an error
    if (findWarrior(warriorList, warriorName) != -1){
        cout << "Error: " << warriorName << " already exists" << endl;
    }

    // Otherwise, put a new Warrior object at the back of the warriorList
    // with the specified parameters
    else{warriorList.emplace_back(warriorName, weaponName, strength);}
}

/**
 * @brief               battles two warriors
 * @param warriorList     the list of warriors
 * @param warrior1Name  the name of the first warrior to battle
 * @param warrior2Name  the name of the second warrior to battle
*/
void battleWarriors(vector<Warrior>& warriorList, const string& warrior1Name, const string& warrior2Name){
    // Checks if the same warrior was called to fight themselves.
    // Returns an error if the same name is called twice.    
    if (warrior1Name == warrior2Name){
        cout << "Silly " << warrior1Name << ", you can't fight yourself!" << endl;
    }

    // Checks if either battling warrior is not on the list.
    // Return an error if they are not found on the list.
    // Returns two errors if both warriors are not found on the list.
    else if (findWarrior(warriorList, warrior1Name) == -1 || findWarrior(warriorList, warrior2Name) == -1){
        if (findWarrior(warriorList, warrior1Name) == -1){
            cout << "Error: " << warrior1Name << " does not exist."<< endl;
        }
        if (findWarrior(warriorList, warrior2Name) == -1){
           cout << "Error: " << warrior2Name << " does not exist"<< endl;
        }
    }

    // Otherwise, assumes both warriors are eligible
    // for battle
    else{
        // Creates two warrior references to the warriors
        Warrior& warrior1 = warriorList[findWarrior(warriorList, warrior1Name)];
        Warrior& warrior2 = warriorList[findWarrior(warriorList, warrior2Name)];
        
        // Calls a function to determine the winner
        battleResult(warrior1, warrior2);
    }
}

/** 
    @brief              deduces the outcome of a battle between each warrior
    @param warrior1     the first warrior to fight
    @param warrior2     the second warrior to fight
*/
void battleResult(Warrior& warrior1, Warrior& warrior2){
    // Displays who is battling whom.
    cout << warrior1.getName() << " battles " << warrior2.getName() << endl;
    
    // If both warriors are matched in power:
    if (warrior1.getStrength() == warrior2.getStrength()){
        // Check if warrior 1 is dead.
        // If warrior 1 is dead and the warriors are matched in power,
        // both warriors are dead.
        if (warrior1.getStrength() == 0){
            cout << "Oh, no! They're both dead! Yuck!" << endl;
        }
        // Otherwise, both warriors will kill eachother, regardless of
        // how much power they each have.
        else{
            cout << "Mutual Annihilation: " << 
            warrior1.getName() << " and " << warrior2.getName() << 
            " die at each other's hands" << endl;

            warrior1.setStrength(0);
            warrior2.setStrength(0);
        }
    }

    // Checks if only warrior 1 is dead. 
    // We do not need to account for both warriors being dead
    // because the previous if statement will have caught that.
    else if (warrior1.getStrength() == 0){
        cout << "He's dead, " << warrior2.getName() << endl;
    }

    // Checks if only warrior 2 is dead.
    // Similarly, do not need to account for both warriors being dead.
    else if (warrior2.getStrength() == 0){
        cout << "He's dead, " << warrior1.getName() << endl;
    }

    // Otherwise, checks if warrior 1 is stronger.
    else if (warrior1.getStrength() > warrior2.getStrength()){
        // If they are, warrior 2 is defeated (strength = 0) and
        // warrior 1 loses strength equal to warrior 2's strength
        warrior1.setStrength(warrior1.getStrength()-warrior2.getStrength());
        warrior2.setStrength(0);
    }
    // Otherwise, check if warrior 2 is stronger (which they should be 
    // given it is the only remaining possible case)
    else if (warrior2.getStrength() > warrior1.getStrength()){
        // If they are, warrior 1 is defeated (strength = 0) and 
        // warrior 2 loses strength equal to warrior 1's strength
        warrior2.setStrength(warrior2.getStrength()-warrior1.getStrength());
        warrior1.setStrength(0);
    }
}

/**
 * @brief               returns the status of the warrior in the warrior list
 * @param warruirList   the list of warriors
*/
void readStatus(const vector<Warrior>& warriorList){
    // Displays the number of warriors that have been put on the list
    // Note: This includes dead warriors, since they are not removed from the list
    // when they die
    cout << "There are: " << warriorList.size() << " warriors" << endl;
    
    // Iterates through the warrior list, displays each warrior's respective
    // name and strength
    for (const Warrior& warrior : warriorList){
        cout << warrior << endl;
    }
}

/**
 * @brief                   find the location of a warrior within the warrior list based off their name
 * @param warriorList     the list of warriors
 * @param targetName      the name of the warrior to find
*/

size_t findWarrior(const vector<Warrior>& warriorList, const string& targetName){
    // Iterates through the warrior list, returns the index of the warrior if there
    // is a warrior with the specified name
    for (size_t i = 0; i < warriorList.size(); i++){
        if (warriorList[i].getName() == targetName){
            return i;
        }
    }

    // If the warrior's name was not found in the list, return -1
    // Since no warrior will be at index -1, this can be used as 
    // a signifier that the warrior is not in the list
    return -1;
}
