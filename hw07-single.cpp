/*
  CS2124 hw07-test.cpp
  -jbs
 */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class Protector;

class Noble{
public:
    Noble(const string&, double);
    friend ostream& operator<<(ostream& os, const Noble& noble);
    string getName() const;
    double getStrength() const;
    void setStrength(double);
    bool getAlive() const;
    void die();
    virtual void battlecry() const = 0;
    void battle(Noble&);
    virtual void display(ostream& os) const = 0;
    virtual void calcStrength(double, double);
    
private:
    string name;
    double strength;
    bool isAlive;
};

class Lord : public Noble{
public:

    Lord(const string&);
    double getArmyStrength() const;
    bool hires(Protector&);
    bool fires(Protector&);
    bool runsAway(Protector&);
    void battlecry() const;
    void calcStrength(double, double);
    void display(ostream& os) const;
  
private:
    vector<Protector*> armyList;
};

class PersonWithStrengthToFight : public Noble{
public:

    PersonWithStrengthToFight(const string&, double);
    void battlecry() const;
    void display(ostream& os) const;
};

class Protector{
public:
    /*/
    Protector(const string& iName, double iStrength) : name(iName), strength(iStrength), lord(nullptr), isAlive(true) {}
    friend ostream& operator<< (ostream& os, const Protector* protector);
    string getName() const{
        return name;
    }
    double getStrength() const{
        return strength;
    }
    bool getAlive() const{
      return isAlive;
    }
    Lord* getLord() const{
        return lord;
    }

    void setLord(Lord& setLord){
        lord = &setLord;
    }

    void setStrength(double newStrength){
        strength = newStrength;
    }
    virtual void battlecry() const = 0;

    bool runaway(){
        if (lord != nullptr){
          if (lord->runsAway(*this)){
              cout  << name << " flees in terror, abandoning his lord, " 
                    << lord->getName() << endl;
              lord = nullptr;
              return true;
          }
          return false;
        }
        else{
            cout << name << " doesn't have a lord to run away from!" << endl;
            return false;
        }
    }

    void display(ostream& os) {
        os << name << " has strength " << strength << endl;
    }
    */
  Protector(const string&, double);
  //friend ostream& operator<< (ostream& os, const Protector& protector);
  void display(ostream& os) const;
  string getName() const;
  double getStrength() const;
  bool getAlive() const;
  Lord* getLord() const;
  void setLord(Lord* setLord);
  void setStrength(double);
  virtual void battlecry() const = 0;
  bool runaway();

private:
    string name;
    double strength;
    Lord* lord;
    bool isAlive;
};


class Wizard : public Protector{
public:
    Wizard(const string&, double);
    void battlecry() const;
private:
};

class Warrior : public Protector{
public:
    Warrior(const string&, double);
    void battlecry() const;

private:
};

class Archer : public Warrior{
public:
    Archer(const string&, double);
    void battlecry() const;
private:
};

class Swordsman : public Warrior{
public: 
    Swordsman(const string&, double);
    void battlecry() const;
private:
};

//
// Test Code
//
int main() {
    cout << "Version 5" << endl;
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";
} // main

Noble::Noble(const string& iName, double iStrength = 0) : name(iName), strength(iStrength), isAlive(true){}
string Noble::getName() const{
  return name;
}
double Noble::getStrength() const{
  return strength;
}

void Noble::setStrength(double newStrength){
    strength = newStrength;
}
bool Noble::getAlive() const{
    return isAlive;
}

void Noble::die(){
    strength = 0;
    isAlive = false;
}

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

ostream& operator<<(ostream& os, const Noble& n){
    n.display(os);
    return os;
}

Lord::Lord(const string& iName) : Noble(iName){}
  
double Lord::getArmyStrength() const{
    double retStrength = 0;
    for (size_t i = 0; i < armyList.size(); i++){
        retStrength += armyList[i]->getStrength();
    }
    return retStrength;
}

bool Lord::hires(Protector& toHire){ 
    if (getAlive() && toHire.getLord() == nullptr){
        armyList.push_back(&toHire);
        toHire.setLord(this);
        setStrength(getArmyStrength());
        return true;
    }
    return false;
}

void Lord::display(ostream& os) const{
    os << getName() << " has an army of size: " << armyList.size();
    for (size_t i = 0; i < armyList.size(); ++i) {
        armyList[i]->display(os);
    }
}
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
void Lord::battlecry() const{
    for (size_t i = 0; i < armyList.size(); i++){
        armyList[i]->battlecry();
    }
}

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

PersonWithStrengthToFight::PersonWithStrengthToFight(const string& iName, double iStrength) : Noble(iName, iStrength){}

void PersonWithStrengthToFight::battlecry() const{
  cout << "Ugh!" << endl;
}

void PersonWithStrengthToFight::display(ostream& os) const{
    os << getName() << " has strength: " << getStrength();;
}
Protector::Protector(const string& iName, double iStrength) : name(iName), strength(iStrength), lord(nullptr), isAlive(true) {}
string Protector::getName() const{
    return name;
}
double Protector::getStrength() const{
    return strength;
}
bool Protector::getAlive() const{
  return isAlive;
}
Lord* Protector::getLord() const{
    return lord;
}

void Protector::setLord(Lord* setLord){
    lord = setLord;
}

void Protector::setStrength(double newStrength){
    strength = newStrength;
    if (strength == 0){
        isAlive = false;
    }
}

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

void Protector::display(ostream& os) const{
    os << "\n\t" << name << " has strength " << strength;
}
ostream& operator<<(ostream& os, const Protector& prot){
    prot.display(os);
    return os;
} 

Wizard::Wizard(const string& iName, double iStrength) : Protector(iName, iStrength) {}

void Wizard::battlecry() const{
    if (getAlive()){
        cout << "POOF!" << endl;
    }
}

Warrior::Warrior(const string& iName, double iStrength) : Protector(iName, iStrength) {}
void Warrior::battlecry() const{
    cout << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
}

Archer::Archer(const string& iName, double iStrength) : Warrior(iName, iStrength) {}
void Archer::battlecry() const{
    if (getAlive()){
        cout << "TWANG!\t";
        Warrior::battlecry();
    }
}
Swordsman::Swordsman(const string& iName, double iStrength) : Warrior(iName, iStrength) {}
void Swordsman::battlecry() const {
    if (getAlive()){
        cout << "CLANG!\t";
        Warrior::battlecry();
    }
}