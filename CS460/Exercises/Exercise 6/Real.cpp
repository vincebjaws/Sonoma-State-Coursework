#include <iostream>
#include <string>
#include <algorithm>
#include "Real.h"

using namespace std;

Real::Real(){ //done
    value = "0.0";
    whole = "0";
    decimal = "0";
    negative_number = false;
}

Real::Real(const Real & R){ //done

    if((R.whole == "0" && R.value != "0.0")
    || (R.decimal == "0" && R.value != "0.0")
    || (R.value[0] == '-')) {
        Real temp = Real(R.value);
        value = temp.value;
        negative_number = temp.negative_number;
        decimal = temp.decimal;
        whole = temp.whole;
    } else {
        value = R.value;
        negative_number = R.negative_number;
        decimal = R.decimal;
        whole = R.whole;
    }
}

Real::Real(const string & S){ //done
    negative_number = false;
    value = S;
    string leadingZeros;
    bool wholeNum =false;
    bool dec = false;
    for(char i : value){//for(int i = 0; i < value.length(); i++) {
        if(i == '-') // if(value[i] == '-')
            negative_number = true;
        else if(i == '.') //else if(value[i] == '.')
            dec = true;
        else {
            if (!dec)
                if(i != '0') { // if (value[i] != '0'){
                    whole.push_back(i);
                    wholeNum = true;
                }
                else if(wholeNum)
                    whole.push_back(i);
                else{
                    continue;
                }
            else {
                if(i == '0') //if(value[i] == '0')
                    leadingZeros.append("0");
                else {
                    decimal.append(leadingZeros);
                    leadingZeros = "";
                    decimal.push_back(i);
                }}}
    }
    if(decimal.empty())
        decimal = "0";

    if(whole.empty())
        whole = "0";

    if (negative_number){
        value = value.substr(1);
    }
    if (!dec) {
        value.append(".0");
        if(decimal != "0")
            decimal.append("0");
    }
    if(value[0] == '.'){
        string temp = "0";
        temp.append(value);
        value = temp;
        whole.append("0");
    }
    value = whole + '.' + decimal;
}
Real::Real(long long W, long long D){ // done
    //two string "" . ""
    string long1 = to_string(W);
    whole = long1;

    string long2 = to_string(D);
    decimal = long2;

    value = long1 + "." + long2;

    if(W < 0){
        negative_number = true;
    }
}

Real::Real(double D){ //done
    negative_number = D < 0;
    string temp = to_string(D);
    string temp2;
    bool dec = false;
    for(int i = 0; i < temp.length(); i++){
        if(temp[i] == '.'){
            dec = true;
        }
        else if(dec){
            if(temp[i] == '0')
                temp2.push_back('0');
            else {
                decimal.append(temp2);
                decimal.push_back(temp[i]);
                temp2 = "";
            }
        }
        else {
            whole.push_back(temp[i]);
        }

    }
    value = whole + '.' + decimal;
    if (!dec) {
        value.append("0");
        decimal.append("0");
    }
    if(value[0] == '.'){
        string leadingZero = "0";
        leadingZero.append(value);
        value = leadingZero;
        whole.append("0");
    }
    if(value.back() == '.'){
        decimal = "0";
        value.append("0");
    }
}

Real::~Real(){

}

Real & Real::operator = (const Real & R){ // done

    if(this->value.empty())
        this->value = "0.0";
    else
        this->value = R.value;

    if(this->whole.empty())
        this->whole = "0";
    else
        this->whole = R.whole;

    if(this->decimal.empty())
        this->decimal = "0";
    else
        this->decimal = R.decimal;

    this->negative_number = R.negative_number;
    return *this;
}

ostream & operator << (ostream & outs, const Real & R){ // done
    if(R.negative_number)
        outs << "-";
    outs << R.value;
    return outs;
}


istream &operator>>(istream &ins, Real &R) {
    ins >> R.value;
    return ins;
}


bool Real::operator == (const Real & R) const { // done
    return this->negative_number == R.negative_number && this->value == R.value ;
}

bool Real::operator != (const Real & R) const { // done
    return !(this->negative_number == R.negative_number && this->value == R.value);
}

bool Real::operator > (const Real & R) const{ // clean up but done
    if(!this->negative_number && R.negative_number)
        return true;

    else if(this->negative_number && !R.negative_number)
        return false;

    int longerThis = 0; // 0 equal // 1 this is more // 2 R is more

    if(R.whole.length() < this->whole.length()) {
        return !R.negative_number;
    }
    else if(R.whole.length() > this->whole.length()) {
        return R.negative_number;
    }
    int iter = 0;
    if(R.decimal.length() < this->decimal.length()) {
        longerThis = 1;
        iter = R.decimal.length();
    }
    else {
        iter = this->decimal.length();
        longerThis = 2;
    }
    iter = iter + whole.length() + 1; //+1 for decimal
    for(int i = 0; i < iter; i++){
        if(this->value[i] > R.value[i]) {
            return !R.negative_number;
        }
        else if(this->value[i] < R.value[i]){
            return R.negative_number;
        }

    }
    if(longerThis == 1){
        if(!R.negative_number)
            return true;
    }
    else if(longerThis == 2){
        if(R.negative_number)
            return true;
        }

    return false;
}

bool Real::operator >= (const  Real & R) const {
    if(!this->negative_number && R.negative_number)
        return true;

    else if(this->negative_number && !R.negative_number)
        return false;
    int longerThis = 0; // 0 equal // 1 this is more // 2 R is more

    if(R.whole.length() < this->whole.length()) {
        return !R.negative_number;
    }
    else if(R.whole.length() > this->whole.length()) {
        return R.negative_number;
    }
    int iter = 0;
    if(R.decimal.length() < this->decimal.length()) {
        longerThis = 1;
        iter = R.decimal.length();
    }
    else {
        iter = this->decimal.length();
        longerThis = 2;
    }
    iter = iter + whole.length() + 1; //+1 for decimal
    for(int i = 0; i < iter; i++){
        if(this->value[i] > R.value[i]) {
            return !R.negative_number;
        }
        else if(this->value[i] < R.value[i]){
            return R.negative_number;
        }

    }
    if(longerThis == 1){
        if(!R.negative_number)
            return true;
    }
    else if(longerThis == 2){
        if(R.negative_number)
            return true;
    }

    return true;
}

bool Real::operator < (const Real & R) const{ // clean up but done
    if(!this->negative_number && R.negative_number)
        return false; //t

    else if(this->negative_number && !R.negative_number)
        return true; //f
    int longerThis = 0; // 0 equal // 1 this is more // 2 R is more

    if(R.whole.length() < this->whole.length()) {
        return R.negative_number; //f
    }
    else if(R.whole.length() > this->whole.length()) {
        return !R.negative_number; //t
    }
    int iter = 0;
    if(R.decimal.length() < this->decimal.length()) {
        longerThis = 1;
        iter = R.decimal.length();
    }
    else {
        iter = this->decimal.length();
        longerThis = 2;
    }
    iter = iter + whole.length() + 1; //+1 for decimal
    for(int i = 0; i < iter; i++){
        if(this->value[i] > R.value[i]) {
            return R.negative_number; //f
        }
        else if(this->value[i] < R.value[i]){
            return !R.negative_number; //f
        }

    }
    if(longerThis == 1){
        if(!R.negative_number)
            return false; //t
    }
    else if(longerThis == 2){
        if(R.negative_number)
            return false; //t
    }

    return false;
}

bool Real::operator <= (const Real & R) const {
    if (!this->negative_number && R.negative_number)
        return false; //t

    else if (this->negative_number && !R.negative_number)
        return true; //f

    int longerThis = 0; // 0 equal // 1 this is more // 2 R is more

    if (R.whole.length() < this->whole.length()) {
        return R.negative_number; //f
    } else if (R.whole.length() > this->whole.length()) {
        return !R.negative_number; //t
    }
    int iter = 0;
    if (R.decimal.length() < this->decimal.length()) {
        longerThis = 1;
        iter = R.decimal.length();
    } else {
        iter = this->decimal.length();
        longerThis = 2;
    }
    iter = iter + whole.length() + 1; //+1 for decimal
    for (int i = 0; i < iter; i++) {
        if (this->value[i] > R.value[i]) {
            if (!R.negative_number)
                return false; //t
            else
                return true; //f
        } else if (this->value[i] < R.value[i]) {
            if (R.negative_number)
                return false; //t
            else
                return true; //f
        }

    }
    if (longerThis == 1) {
        if (!R.negative_number)
            return false; //t
    } else if (longerThis == 2) {
        if (R.negative_number)
            return false; //t
    }

    return true;
}

Real Real::operator + (const Real & R) const{
    Real tempThis(this->value);
    tempThis.negative_number = false;
    Real tempR(R.value);
    tempR.negative_number = false;

    bool mSign = false;
    string sumValue;

    if(this->negative_number && !R.negative_number){
        if(tempThis > tempR){
            mSign = true;
            sumValue = subHelper(tempThis, tempR);
        }
        else if(tempThis < tempR){
            sumValue = subHelper(tempThis, tempR);
        }
        else{
            sumValue = "0";
        }
    }
    else if(!this->negative_number && R.negative_number){
        if(tempThis > tempR){
            mSign = true;
            sumValue = subHelper(tempR, tempThis);
        }
        else if(tempThis < tempR){
            sumValue = subHelper(tempThis, tempR);
        }
        else{
            sumValue = "0";
        }
    }

    else if(this->negative_number && R.negative_number){
        mSign = true;
        sumValue = addHelper(tempThis, tempR);
    }
    else{
        sumValue = addHelper(tempThis, tempR);
    }

    Real summation = Real(sumValue);
    if(mSign)
        summation.negative_number = true;
    return summation;
}

Real Real::operator += (const Real & R) {
    Real plusEquals = *this + R;
    return plusEquals;
}

Real Real::operator ++ (){
    Real iterate = Real("1");
    iterate = iterate + *this;

    this->negative_number = iterate.negative_number;
    this->value = iterate.value;
    this->decimal = iterate.decimal;
    this->whole = iterate.whole;

    return iterate;
}

Real Real::operator ++(int){
    Real postIterate = Real("1");
    Real current = *this;
    postIterate =  postIterate + *this;

    this->negative_number = postIterate.negative_number;
    this->value = postIterate.value;
    this->whole = postIterate.whole;
    this->decimal = postIterate.decimal;

    return current;
}

Real Real::operator - (const Real & R) const{
    Real tempThis(this->value);
    tempThis.negative_number = false;
    Real tempR(R.value);
    tempR.negative_number = false;
    bool mSign = false;
    string subValue;

    if(this->negative_number && !R.negative_number){
        mSign = true;
        subValue = addHelper(tempThis, tempR);
    }
    else if(!this->negative_number && R.negative_number){
        subValue = addHelper(tempThis, tempR);
    }
    else if(this->negative_number && R.negative_number){
        if(tempThis > tempR){
            mSign = true;
            subValue = subHelper(tempThis, tempR);
        }
        else if(tempThis < tempR)
            subValue = subHelper(tempR, tempThis);
        else{
            subValue = "0.0";
        }
    }
    else if(!this->negative_number && !R.negative_number){
        if(tempThis < tempR){
            mSign = true;
            subValue = subHelper(tempR, tempThis);
        }
        else if(tempThis > tempR){
            subValue = subHelper(tempThis, tempR);
        }
        else{
            subValue = "0";
        }
    }
    Real subtraction = Real(subValue);
    if(mSign)
        subtraction.negative_number = true;
    return subtraction;
}

Real Real::operator -= (const Real & R){
    Real minusEquals = *this + R;
    return minusEquals;
}

Real Real::operator -- (){
    Real iterate = Real("1");
    iterate = *this - iterate;

    this->negative_number = iterate.negative_number;
    this->value = iterate.value;
    this->decimal = iterate.decimal;
    this->whole = iterate.whole;

    return iterate;
}

Real Real::operator -- (int){
    Real postIterate = Real("1");
    Real current = *this;
    postIterate =   *this - postIterate;

    this->negative_number = postIterate.negative_number;
    this->value = postIterate.value;
    this->whole = postIterate.whole;
    this->decimal = postIterate.decimal;

    return current;
}

Real Real::operator * (const Real & R) const{
    bool mSign = false;
    mSign = (this->negative_number && !R.negative_number) ||
            (!this->negative_number && R.negative_number);

    string numThis = this->whole + this->decimal;
    string numR = R.whole + R.decimal;
    int decPos = this->decimal.length() + R.decimal.length();

    string total;
    int product = 0;
    double totalnum = 0;
    int multPos = 1;
    int iter = 1;

    for(int i = numR.length()-1; i>=0; i--){
        for(int j = numThis.length()-1; j>=0; j--){
            product = 0;
            int multR = ((int)(numR[i]-48));
            int multThis = ((int)(numThis[j]-48));
            product = multR * multThis;
            int offset = multPos;
            product = product * offset;
            totalnum += product;
            multPos*=10;
        }
        iter = iter * 10;
        multPos= 1 * iter;
    }
    int x = 10;
    int y = decPos;
    int offset = 1;
    for(int i = 0; i < y; ++i)
    {
        offset *= x;
    }

    totalnum = totalnum/offset;
    total = to_string(totalnum);
    Real finalProduct = Real(total);
    if(mSign)
        finalProduct.negative_number = true;
    return finalProduct;
}

Real Real::operator *= (const Real & R){
    *this = *this * R;
    return *this;
}


string Real::addHelper(const Real R1, const Real & R2) const {

    Real tempThis = R1;
    Real tempR = R2;
    string summation;
    string tempAddTool;


    if (tempThis.whole.length() > tempR.whole.length()) {
        int diff = tempThis.whole.length() - tempR.whole.length();
        for (int i = 0; i < diff; i++) {
            tempAddTool.push_back('0');
        }
        tempR.whole = tempAddTool + tempR.whole;
    } else {
        int diff = tempR.whole.length() - tempThis.whole.length();
        for (int i = 0; i < diff; i++) {
            tempAddTool.push_back('0');
        }
        tempThis.whole = tempAddTool + tempThis.whole;
    }
    tempAddTool = "";
    if (tempThis.decimal.length() > tempR.decimal.length()) {
        int diff = tempThis.decimal.length() - tempR.decimal.length();
        for (int i = 0; i < diff; i++) {
            tempAddTool.push_back('0');
        }
        tempR.decimal = tempR.decimal + tempAddTool;
    } else {
        int diff = tempR.decimal.length() - tempThis.decimal.length();
        for (int i = 0; i < diff; i++) {
            tempAddTool.push_back('0');
        }
        tempThis.decimal = tempThis.decimal + tempAddTool;
    }
    tempThis.value = tempThis.whole + "." + tempThis.decimal;
    tempR.value = tempR.whole + "." + tempR.decimal;
    reverse(tempThis.value.begin(), tempThis.value.end());
    reverse(tempR.value.begin(), tempR.value.end());
    int carry = 0;
    for (int i = 0; i < tempThis.value.length(); i++) {
        if (tempThis.value[i] == '.' && tempR.value[i] == '.') {
            summation.push_back('.');
        } else {
            int t = 0;
            t = tempThis.value[i] + tempR.value[i] + carry;
            if (t != 48) {
                t = t - 48;
            }
            if (t > 57) {
                carry = 1;
                t = t - 10;
                summation.push_back((char) t);
            } else {
                carry = 0;
                summation.push_back((char) t);
            }
        }
    }
    if (carry > 0) {
        int t = carry;
        summation = summation + to_string(t);
    }
    reverse(summation.begin(), summation.end());
    return summation;
}


string Real::subHelper(const Real& R1, const Real &R2) const {

    Real tempThis = R1;
    Real tempR = R2;
    string subtraction;
    string tempZeros;


    if(tempThis.whole.length() > tempR.whole.length()){
        int diff = tempThis.whole.length() - tempR.whole.length();
        for(int i = 0; i < diff; i++){
            tempZeros.push_back('0');
        }
        tempR.whole = tempZeros + tempR.whole;
    }
    else{
        int diff = tempR.whole.length() - tempThis.whole.length();
        for(int i = 0; i < diff; i++){
            tempZeros.push_back('0');
        }
        tempThis.whole = tempZeros + tempThis.whole;
    }
    tempZeros = "";
    if(tempThis.decimal.length() > tempR.decimal.length()){
        int diff = tempThis.decimal.length() - tempR.decimal.length();
        for(int i = 0; i < diff; i++){
            tempZeros.push_back('0');
        }
        tempR.decimal = tempR.decimal + tempZeros;
    }
    else{
        int diff = tempR.decimal.length() - tempThis.decimal.length();
        for(int i = 0; i < diff; i++){
            tempZeros.push_back('0');
        }
        tempThis.decimal = tempThis.decimal + tempZeros;
    }
    tempThis.value = tempThis.whole + "." + tempThis.decimal;
    tempR.value = tempR.whole + "." + tempR.decimal;
    reverse(tempThis.value.begin(), tempThis.value.end());
    reverse(tempR.value.begin(), tempR.value.end());
    int i = 0;
    while(i < tempThis.value.length()){
        if(tempThis.value[i] == '.'  && tempR.value[i] == '.'){
            subtraction.push_back('.');
            i++;
        }
        else if(tempThis.value[i] < tempR.value[i]){
            // need to borrow
            int j = i+1;
            while(tempThis.value[j] == 48 || tempThis.value[j] == '.'){
                j++;
            }
            while(j != i){
                if(tempThis.value[j] != 46){
                    tempThis.value[j] = tempThis.value[j]-1;
                    j--;
                    if(tempThis.value[j] == '.'){
                        tempThis.value[j-1] = tempThis.value[j-1] + 10;
                    }
                    else{
                        tempThis.value[j] = tempThis.value[j] + 10;
                    }}
                else{
                    j--;
                }}
            int t = (tempThis.value[i] - tempR.value[i]);
            t = t+48;
            subtraction.push_back((char) t);
            i++;
        }
        else{
            int t = (tempThis.value[i] - tempR.value[i]);
            t = t + 48;
            subtraction.push_back((char) t);
            i++;
        }}

    reverse(subtraction.begin(), subtraction.end());
    return subtraction;
}
