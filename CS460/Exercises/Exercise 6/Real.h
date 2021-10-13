//
// Created by Vince Lawrence Bjazevic on 11/19/20.
//

#ifndef EX6_REAL_H
#define EX6_REAL_H

#pragma once
#include <iostream>


using namespace std;

class Real {
public:
    Real(); //done
    Real(const Real & R); //done
    Real(const string & S); //done
    Real (long long W, long long D); //done
    Real (double D); // done
    ~Real();
    Real & operator = (const Real & R); //done
    friend ostream & operator << (ostream & outs, const Real & R); //done
    friend istream & operator >> (istream & ins, Real & R); //?
    bool operator == (const Real & R) const; //done
    bool operator != (const Real & R) const; //done
    bool operator > (const Real & R) const; //done
    bool operator >= (const Real & R) const; //done
    bool operator < (const Real & R) const; //done
    bool operator <= (const Real & R) const; //done
    Real operator + (const Real & R) const; //done
    Real operator += (const Real & R); // just adjust
    Real operator ++ (); // just adjust
    Real operator ++ (int); // just adjust
    Real operator - (const Real & R) const; // done
    Real operator -= (const Real & R); // just adjust
    Real operator -- (); // just adjust
    Real operator -- (int); // just adjust
    Real operator * (const Real & R) const; // done
    Real operator *= (const Real & R); // need to adjust
    Real operator / (const Real & R) const; // Extra Credit
    Real operator /= (const Real & R); // Extra Credit


private:
    string value;
    bool negative_number;
    string whole;
    string decimal;
    string addHelper(const Real R1, const Real & R2) const;
    string subHelper(const Real& R1, const Real & R2) const;


};
#endif //EX6_REAL_H
