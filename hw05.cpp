/*
  hw04.cpp
  Evan Lee
  Simulate nobles hiring, firing, and battling with warriors
  2/23/2023
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Your Noble and Warrior classes should go here.

/**
 * @brief Warrior class. Used to represent a warrior
*/
class Warrior{
public:
    /**
     * @brief           onstructs a new warrior with given parameters
     * @param iName     the input name of the warrior
     * @param iStrength the input strength of the warrior
     * @param hired     a boolean to check whether the warrior is currently employed.
     *                  warriors are created unemployed
    */
    Warrior(const string& iName, double iStrength) : 
                                                    name(iName), 
                                                    strength(iStrength), 
                                                    hired(false){}

    /**
     * @brief   returns the name of the warrior
     * @return  the name of the warrior (as a string)
    */
    const string& getName() const{return name;}
    /**
     * @brief   returns the strength of the warrior
     * @return  the strength of the warrior (as a double)
    */
    double getStrength() const{return strength;}
    /**
     * @brief   returns whether the warrior is hired
     * @return  whether the warrior is hired (as a boolean)
    */
    bool isHired() const{return hired;}
    /**
     * @brief   sets the strength of the warrior
     * @param   amount the strength to set warrior's set to
    */
    void setStrength(double amount) { strength = amount;}
    /**
     * @brief   sets whether the warrior has been hired or not
     * @param   isHired the boolean to set
    */
    void setHired(bool isHired){ hired = isHired;}

    // declare friend operator for the warrior
    friend ostream& operator<<(ostream&os, const Warrior&);

private:
// private variables for the warrior
    string name;
    double strength;
    bool hired;
};

class Noble{
public:
    /**
     * @brief           constructs a new Noble with given parameters
     * @param iName     the input name of the noble
     * @param isAlive   a boolean to check whether the noble is alive
     *                  nobles are created alive
    */
    Noble(const string& iName) : name(iName), isAlive(true){}

    /**
     * @brief   returns the name of the noble
     * @return  the name of the noble (as a string)
    */
    const string& getName() const{ return name; }
    /**
     * @brief   hires a warrior
     *      * @param   warrior the warrior to hire
    */

    bool hire(Warrior& warrior){
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
    */
    bool fire(Warrior& warrior){
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
                    // sends a message
                    cout << 
                    warrior.getName() << 
                    " you don't work for me any more! -- " << name 
                    << endl;
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
    void die(){
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
    // 
    double getStrength() const{
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
    void setArmyStrength(double armyStrength, double enemyStrength){
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
    void battle(Noble& enemy){
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
    
    // declare friend operator for the warrior
    friend ostream& operator<<(ostream&, const Noble&);

private:
    // private variables for the noble class
    vector<Warrior*> armyList;
    string name;
    bool isAlive;
};

ostream& operator<<(ostream&, const Warrior&);
ostream& operator<<(ostream&, const Noble&);
Warrior* getWarrior(const vector<Warrior*>&, const string&);
Noble* getNoble(const vector<Noble*>&, const string&);

/**
 * @brief   models nobles hiring, firing, and battling with warriors
 * @return  0 on success (as an int)
*/
int main() {
    // Initializes a vector of warrior pointers and a vector of noble pointers
	vector<Warrior*> warriorList;
    vector<Noble*> nobleList;
    // Initializes an input stream
    ifstream inputStream;
    // Input stream opens "warriors.txt"
    inputStream.open("nobleWarriors.txt");
    
    // Exits if specified file does not exist
    if (!inputStream){
        cerr << "File not at location." << endl;
        exit(1);
    }

    // Initializes a string to save the type of 
    // command to be called
    string commandType;

    while(inputStream >> commandType){

        // Checks if command is creating a new warrior
        if (commandType == "Warrior"){
            // If a new warrior is being created, assumes the
            // next string and int denote the warrior's 
            // name and strength
            string warriorName;
            int warriorStrength;

            inputStream >> warriorName >> warriorStrength;
            
            if (getWarrior(warriorList, warriorName) != nullptr){
                cout << warriorName << " already exists!" << endl;
            }
            else{
            // Adds a new warrior pointer with the
            // specified name and strength to the warrior pointer vector
            warriorList.push_back(new Warrior(warriorName, warriorStrength));
            }
        }
        else if (commandType == "Noble"){
            // If a new noble is being created, assumes the
            // next string denotes the noble's name
            string nobleName;

            inputStream >> nobleName;

            if (getNoble(nobleList, nobleName) != nullptr){
                cout << nobleName << " already exists!" << endl;
            }
            else{
            // Calls a function to add a new noble pointer with the
            // specified name and strength to the noble pointer vector
            nobleList.push_back(new Noble(nobleName));
            }
        }
            
        else if (commandType == "Hire"){
            // If a noble is hiring a warrior,
            // assumes the next two strings denotes
            // the noble's name and the warrior's name
            string nobleName;
            string warriorName;
            inputStream >> nobleName >> warriorName;

            // sets two pointers, one to the noble and one to the warrior
            Noble* noble = getNoble(nobleList, nobleName);
            Warrior* warrior = getWarrior(warriorList, warriorName);

            // Returns an error if either the noble or warrior
            // are not found in their respective lists
            if (noble == nullptr || warrior == nullptr){
                // Returns an error if the noble does not exist
                if (noble == nullptr) {
                    cout << "Attempting to hire using unknown noble: "
                    << nobleName << endl;
                }
                // Returns an error if the warrior does not exist
                if (warrior == nullptr) {
                    cout << "Attempting to hire using unknown warrior: "
                    << warriorName << endl;
                }
            }
            else{
                // Otherwise, the noble hires the warrior
                noble -> hire(*warrior);
            }
            
        }

        else if (commandType == "Fire"){
            // If a noble is firing a warrior,
            // assumes the next two strings are the
            // noble and warrior's names
            string nobleName;
            string warriorName;
            inputStream >> nobleName >> warriorName;

            // Sets two pointers, one to the noble and one to the warrior
            Noble* noble = getNoble(nobleList, nobleName);
            Warrior* warrior = getWarrior(warriorList, warriorName);

            // Returns an error if either the noble or warrior
            // are not found within their respective lists
            if (noble == nullptr || warrior == nullptr){
                // Returns an error if the noble is not found
                if (noble == nullptr) {
                    cout << "Attempting to fire using unknown noble: "
                    << nobleName << endl;
                }
                // Returns an error if the warrior is not found
                if (warrior == nullptr) {
                    cout << "Attempting to fire using unknown warrior: "
                    << warriorName << endl;
                }
            }
            else{
                // Otherwise, tells the noble to fire the warrior
                noble -> fire(*warrior);
            }
                
        }
        // Else, checks if the command was to have a battle.
        else if (commandType == "Battle"){
            // If a battle is being held, assumes the next two
            // strings name the two nobles fighting.
            string noble1Name;
            string noble2Name;
            inputStream >> noble1Name >> noble2Name;   

            // Sets two pointers, one to each noble
            Noble* noble1 = getNoble(nobleList, noble1Name);
            Noble* noble2 = getNoble(nobleList, noble2Name);

            // Returns an error if either noble is not found
            // on the noble list
            if (noble1 == nullptr || noble2 == nullptr){
                // Retuns an error if the first noble is not found
                if (noble1 == nullptr){
                    cout << noble1Name << " does not exist!" << endl;
                }
                // Returns an error if the second noble is not found
                if (noble2 == nullptr){
                    cout << noble2Name << " does not exist!" << endl;
                }
            }
            else{
                // Calls a function to hold a battle between the two
                // nobles with the specified names
                noble1->battle(*noble2);
            }
        }

        // Else, checks if command was to print status of warriors
        else if (commandType == "Status"){
            cout << "Status \n======" << endl;
            // Prints out the nobles (and their respective warriors)
            cout << "Nobles: " << endl;
            // If there are no nobles on the noblelist, print out "NONE"
            if (nobleList.size() == 0){
                cout << "NONE" << endl;
            }
            // otherwise, iterate through the noble list and 
            // print out each noble on the list
            else{
                for (size_t i = 0; i < nobleList.size(); i++){
                    cout << *nobleList[i] << endl;
                }
            }

            // A marker to count the number of unemployed warriors
            int unemployedWarriors = 0;
            cout << "\nUnemployed Warriors:" << endl;
            // Iterates through the warrior list 
            for (size_t i = 0; i < warriorList.size(); i++){
                // If a warrior is not employed,
                if (warriorList[i]->isHired() != true){
                    // print them out
                    cout << *warriorList[i] << endl;
                    // increment the marker to count the
                    // number of unemployed warriors
                    unemployedWarriors++;
                }
            }
            // If there were no unemployed warriors
            // print out "NONE"
            if (unemployedWarriors == 0){
                cout << "NONE" << endl;
            }
        }
        
        // Else, checks if the command is to clear the lists
        else if (commandType == "Clear") {
                // Iterates through the noble pointer list, and deletes
                // what each pointer is pointing to
                for (size_t i = 0; i < nobleList.size(); i++) {
                    delete nobleList[i];
                }
                // Clears the noble list of pointers
                nobleList.clear();
                // Iterates through the warrior pointer list, and deletes
                // what each pointer is pointing to
                for (size_t i = 0; i < warriorList.size(); ++i) {
                    delete warriorList[i];
                }
                // Clears the warrior list of pointers
                warriorList.clear();
        }

        // Otherwise, the command is not recognized
        else {
            // Print out an error
            cout << commandType << " is not a command!" << endl;
        }

    }

    inputStream.close();
}

/**
 * @brief           finds a Noble within the nobleList given the noble's name
 * @param nobleList the list of noble pointers to check
 * @param name      the name of the requested noble
 * @return          the pointer to the requested noble. Returns nullptr if the noble is not found
*/
Noble* getNoble(const vector<Noble*>& nobleList, const string& name){
    // Iterates through the noble list
    for (size_t i = 0; i < nobleList.size(); i++) {
        // If the noble's name is equal to the request name, return a pointer to the noble
        if (nobleList[i]->getName() == name){ return nobleList[i];}
    }
    // If a noble was not found in the list with the requested name, return nullptr
    return nullptr;
}

/**
 * @brief           finds a warrior within the warriorList given the warrior's name
 * @param nobleList the list of warrior pointers to check
 * @param name      the name of the requested warrior
 * @return          the pointer to the requested warrior. Returns nullptr if the warrior is not found
*/
Warrior* getWarrior(const vector<Warrior*>& warriorList, const string& name){
    // Iterates through the warrior list
    for (size_t i = 0; i < warriorList.size(); i++) {
        // If the warrior's name is equal to the request name, return a pointer to the warrior
        if (warriorList[i]->getName() == name){ return warriorList[i];}
    }
    // If a warrior was not found in the list with the requested name, return nullptr
    return nullptr;
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