// hw02.cpp
// Evan Lee
// 02/05/2023
// Model a game of medieval times of a world filled with warriors.

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Warrior structure - each warrior has a name and a respective strength.
struct Warrior{
    string name;
    int strength;
};

// Prototyping
void addWarrior(vector<Warrior>& inputList, 
                const string& inpName, 
                int inpStrength);
void battleWarriors(vector<Warrior>& inputList, 
                    const string& warrior1Name, 
                    const string& warrior2Name);
void readStatus(const vector<Warrior>& inputList);
size_t findWarrior(const vector<Warrior>& inputList, const string& findName);
void battleResult(Warrior& warrior1, Warrior& warrior2);


/**
 * @brief       model a medieval game
 * @return      int 0 on success
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
        cerr << "File not at location." << endl;
        exit(1);
    }

    // Initializes a string to save the type of 
    // command to be called
    string commandType;

    // Reads the command word and reads following words
    // according to expected input 
    // Warrior <string> <int> to create a new warrior
    // Battle <string> <string> to have two warriors battle
    // Status to print out the status of all warriors
    while(inputStream >> commandType){

        // Checks if command is creating a new warrior
        if (commandType == "Warrior"){
            // If a new warrior is being created, assumes the
            // next string and int denote the warrior's 
            // name and strength
            string warriorName;
            int warriorStrength;

            inputStream >> warriorName >> warriorStrength;

            // Calls a function to add a new warrior with the
            // specified name and strength to the warrior vector
            addWarrior(warriorList, warriorName, warriorStrength);
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
        else if (commandType == "Status"){
            // Calls a function to read the status of the warriors
            // stored in the warriorList vector
            readStatus(warriorList);
        }
    }
}

/**
 * @brief               Given the parameters of a warrior, add the warrior to a list of warriors
 * @param inputList     the list of warriors, stored as a vector
 * @param inpName       the name of the warrior to be added
 * @param inpStrength   the strength of the warrior to be added
*/
void addWarrior(vector<Warrior>& inputList, const string& inpName, int inpStrength){
    // If the warrior's name is already on the list, return an error.
    if (findWarrior(inputList, inpName) != inputList.size()){
        cout << "Error: " << inpName << " already exists."<< endl;
    }
    
    else{
        // Create a new warrior instance with the specified name and strength
        Warrior newWarrior;
        newWarrior.name = inpName;
        newWarrior.strength = inpStrength;
        // Pushes this new warrior to the list of warriors
        inputList.push_back(newWarrior);
    }
}

/**
 * @brief               battles two warriors
 * @param inputList     the list of warriors
 * @param warrior1Name  the name of the first warrior to battle
 * @param warrior2Name  the name of the second warrior to battle
*/
void battleWarriors(vector<Warrior>& inputList, const string& warrior1Name, const string& warrior2Name){
    // Checks if the same warrior was called to fight themselves.
    // Returns an error if the same name is called twice.    
    if (warrior1Name == warrior2Name){
        cout << "Silly " << warrior1Name << ", you can't fight yourself!" << endl;
    }

    // Checks if either battling warrior is not on the list.
    // Return an error if they are not found on the list.
    // Returns two errors if both warriors are not found on the list.
    else if (findWarrior(inputList, warrior1Name) == inputList.size() || findWarrior(inputList, warrior2Name) == inputList.size()){
        if (findWarrior(inputList, warrior1Name) == inputList.size()){
            cout << "Error: " << warrior1Name << " does not exist."<< endl;
        }
        if (findWarrior(inputList, warrior2Name) == inputList.size()){
           cout << "Error: " << warrior2Name << " does not exist."<< endl;
        }
    }
    

    else{
        // Creates two warrior references to the warriors on the list
        Warrior& warrior1 = inputList[findWarrior(inputList, warrior1Name)];
        Warrior& warrior2 = inputList[findWarrior(inputList, warrior2Name)];

        // calls a function to determine who the winner is in the battle
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
        cout << warrior1.name << " battles " << warrior2.name << endl;
    // If both warriors are matched in power
        if(warrior1.strength == warrior2.strength){
            // Check if warrior 1 is dead.
            // If warrior 1 is dead and the warriors are matched in power,
            // both warriors are dead.
            if (warrior1.strength == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            // Otherwise, both warriors will kill eachother, regardless of
            // how much power they each have.
            else{
                warrior1.strength = 0;
                warrior2.strength = 0;

                // I apologize for kind of butchering this cout
                cout << "Mutual Annihilation: " << 
                warrior1.name << " and " << warrior2.name << 
                " die at each other's hands" << endl;
            }
        }

        // Checks if only warrior 1 is dead. 
        // We do not need to account for both warriors being dead
        // because the previous if statement will have caught that.
        else if (warrior1.strength == 0){
            cout << "He's dead, " << warrior2.name << endl;
        }

        // Checks if only warrior 2 is dead.
        // Similarly, do not need to account for both warriors being dead.
        else if (warrior2.strength == 0){
            cout << "He's dead, " << warrior1.name << endl;
        }

        // Otherwise, checks if warrior 1 is stronger.
        else if (warrior1.strength > warrior2.strength){
            // If they are, warrior 2 is defeated (strength = 0) and
            // warrior 1 loses strength equal to warrior 2's strength
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
            cout << warrior1.name << " defeats " << warrior2.name << endl;
        }

        // Otherwise, check if warrior 2 is stronger (which they should be 
        // given it is the only remaining possible case)
        else if (warrior2.strength > warrior1.strength){
            // If they are, warrior 1 is defeated (strength = 0) and 
            // warrior 2 loses strength equal to warrior 1's strength
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
            cout << warrior2.name << " defeats " << warrior1.name << endl;
        }
}

/**
 * @brief           returns the status of the warrior in the warrior list
 * @param inputList the list of warriors
*/
void readStatus(const vector<Warrior>& inputList){
    // Displays the number of warriors that have been put on the list
    // Note: This includes dead warriors, since they are not removed from the list
    // when they die
    cout << "There are: " << inputList.size() << " warriors" << endl;
    // Iterates through the warrior list, displays each warrior's respective
    // name and strength
    for (size_t i = 0; i < inputList.size(); i++){
        cout << "Warrior: " << inputList[i].name << ", strength: " << inputList[i].strength << endl;
    }
}

/**
 * @brief               find the location of a warrior within the warrior list based off their name
 * @param inputList     the list of warriors
 * @param findName      the name of the warrior to find
*/
size_t findWarrior(const vector<Warrior>& inputList, const string& findName){
    // Iterates through the warrior list, returns the index of the warrior if there
    // is a warrior with the specified name
    for (size_t i = 0; i < inputList.size(); i++){
        if (inputList[i].name == findName){
            return i;
        }
    }
    // If the warrior's name was not found in the list, return the size of the list
    return inputList.size();
    
}