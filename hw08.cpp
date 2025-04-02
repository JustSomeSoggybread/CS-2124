// rec13.cpp
// Evan Lee
// 

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

class Polynomial{
private:
    struct Node{
        Node(int iD, Node* iNext = nullptr): data(iD), next(iNext){}
        Node(): next(nullptr), data(0){}
        Node* next;
        int data;
    };
    Node* head;
    size_t degree;

    void dropLeadingZeros(){
        Node* curr = head;
        Node* prev = nullptr;
        while (curr->data == 0){
            prev = curr;
            curr = curr->next;
            delete prev;
            prev= nullptr;
            degree--;
        }
        head = curr;
    }

public:
    Polynomial(){
        head = new Node;
        head->data = 0;
        degree = 0;
    }

    Polynomial(const vector<int>& inVec){
        head = new Node;
        Node* curr = head;
        curr->data = inVec[0];
        for (size_t i = 1; i < inVec.size(); i++){
            Node* temp = new Node;
            temp->data = inVec[i];
            curr->next = temp;
            curr = temp;
        }
        degree = inVec.size()-1;
        dropLeadingZeros();
    }

    Polynomial& operator+=(const Polynomial& rhs){
        Node* otherCurr = rhs.head;
        Node* thisCurr = head;
        if (rhs.degree > degree){
            Node* temp = new Node;
            temp->data = head->data;
            head->data = otherCurr->data;
            temp->next = head->next;
            head->next = temp;
            Node* iter = head;
            otherCurr = otherCurr->next;
            
            for (size_t i = 0; i < (rhs.degree - degree) - 1; i++){
                Node* iterTemp = new Node(otherCurr->data);
                iterTemp->next = iter->next;
                iter->next = iterTemp;
                iter = iter->next;
                otherCurr = otherCurr->next;
            }
            
            thisCurr = temp;
            degree = rhs.degree;
        }

        else if(degree > rhs.degree){
            for (size_t i = 0; i < (degree - rhs.degree); i++){thisCurr = thisCurr->next;}
        }

        while (thisCurr != nullptr && otherCurr != nullptr){
            thisCurr->data += otherCurr->data;
            thisCurr = thisCurr->next;
            otherCurr = otherCurr->next;
        }
        dropLeadingZeros();
        return *this;
    }

    double evaluate(double x) const {
        double retThis = 0;
        Node* curr = head;
        while (curr != nullptr) {
            retThis = retThis * x + curr->data;
            curr = curr->next;
        }
        return retThis;
    }



    Polynomial(const Polynomial& other) : degree(other.degree) {
            Node* temp = new Node{};
            head = temp;
            Node* otherTemp = other.head;
            while(otherTemp != nullptr) {
                temp->data = otherTemp->data;
                temp->next = new Node{};
                temp = temp->next;
                otherTemp = otherTemp->next;
            }
            temp->next = nullptr;
        }

        ~Polynomial() {
            Node* temp = head;
            while (temp != nullptr) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
            head = nullptr;
        }

        Polynomial& operator=(const Polynomial& other) {
            if (this != &other) {
                degree = other.degree;
                Node* temp = head;
                while (temp != nullptr) {
                Node* next = temp->next;
                    delete temp;
                    temp = next;
                }
                temp = nullptr;
                Node* otherTemp = other.head;
                while (otherTemp != nullptr) {
                    temp = new Node{otherTemp->data, temp};
                    otherTemp = otherTemp->next;
                }
                head = temp;
        // reverse the order of the nodes so largest exponent is first
                Node* prev = nullptr;
                Node* curr = head;
                while (curr != nullptr) {
                    Node* next = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = next;
                }
                head = prev;
            }
            dropLeadingZeros();
            return *this;
        }

    friend ostream& operator<<(ostream&, const Polynomial&);
    friend Polynomial operator+(const Polynomial&, const Polynomial&);
    friend bool operator==(const Polynomial&, const Polynomial&);
    friend bool operator!=(const Polynomial&, const Polynomial&);

};


void doNothing(Polynomial temp) {}

int main(){

     //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    Polynomial temp(p4);
    cout << "temp: " << temp << endl;
        
    //    cerr << "displaying polynomials\n";
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;

    //Polynomial temp;
    temp = p2 + p3;
    cout << "temp: " << temp << endl;
    
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;

    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
        
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}

ostream& operator<<(ostream& os, const Polynomial& poly){
    Polynomial::Node* curr = poly.head;
        for (size_t i = poly.degree; i > 0; i--){
            if (curr->data != 0){
                if (curr->data != 1 && curr->data != -1){os << curr->data;}
                if (curr->data == -1){
                    os <<"-";
                }
                if (i != 1) {os << "x^" << i;}
                else{os << "x";}
            }
            if (curr->next->data != 0){os << "+";}
            curr = curr->next;
        }
        os << curr->data;
    return os;

}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial retThis = lhs;
    retThis += rhs;
    return retThis;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if (lhs.degree != rhs.degree){
        return false;
    }
    Polynomial::Node* lhs_curr = lhs.head;
    Polynomial::Node* rhs_curr = rhs.head;
    while (lhs_curr != nullptr && rhs_curr != nullptr){
        if (lhs_curr->data != rhs_curr->data ){
            return false;
        }
        lhs_curr = lhs_curr->next;
        rhs_curr = rhs_curr->next;
    }
    return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}