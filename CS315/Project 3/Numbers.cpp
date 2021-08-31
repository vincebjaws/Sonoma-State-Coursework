#include "Numbers.hpp"

int Numbers::value(char romanDigit) {
        if (romanDigit == 'I') return 1;
        if (romanDigit == 'V') return 5;
        if (romanDigit == 'X') return 10;
        if (romanDigit == 'L') return 50;
        if (romanDigit == 'C') return 100;
        if (romanDigit == 'D') return 500;
        return 1000;
}

int Numbers::converterToDecimal(std::string &romanNum) {
    std::vector<char> validity;
    int conversion = 0;
    int numOfI = 0;
    int numOfV = 0;
    int numOfX = 0;
    int numOfL = 0;
    int numOfC = 0;
    int numOfD = 0;
    int numOfM = 0;
    int prev = 0;
    for (int i=0; i<romanNum.length(); i++) {
        char lastRomanNum = romanNum[i];
        if(lastRomanNum == 'I')
            numOfI = numOfI + 1;
        if(lastRomanNum == 'V')
            numOfV = numOfV + 1;
        if(lastRomanNum == 'X')
            numOfX = numOfX + 1;
        if(lastRomanNum == 'L')
            numOfL = numOfL + 1;
        if(lastRomanNum == 'C')
            numOfC = numOfC + 1;
        if(lastRomanNum == 'D')
            numOfD = numOfD + 1;
        if(lastRomanNum == 'M')
            numOfM = numOfM + 1;
        if(numOfI > 3 || numOfV > 3 || numOfX > 3 || numOfL > 3 ||
           numOfC > 3 || numOfD > 3 || numOfM > 3){
            std::cout << "Malformed Roman Number." ;
            exit(2);
        }
        int current = value(lastRomanNum);
        int next = value(romanNum[i+1]);
        if(current == prev) {
            validity.push_back(lastRomanNum);
            if(validity.size() == 2){
                if(next<current){
                    std::cout<< "Malformed Roman Number";
                    exit(2);
                }
            }
        }
        else
            while(validity.size()>0)
                validity.pop_back();
        if (i+1 < romanNum.length()) {
            next = value(romanNum[i+1]);
            if (current >= next)
                conversion = conversion + current;
            else {
                conversion = conversion + next - current;
                i++;
            }
        }
        else
            conversion = conversion + current;
        prev = current;
    }
    return conversion;
}

std::string Numbers::convertToRoman(int &decimal) {
    //thousands
    //
    std::string thousandsPlace[] = {"", "M", "MM", "MMM"};
    std::string mColumnEval = thousandsPlace[decimal/1000];
    //hundreds
    std::string hundredsPlace[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    std::string cColumnEval = hundredsPlace[(decimal%1000)/100];
    //tens
    std::string tensPlace[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    std::string xColumnEval =  tensPlace[(decimal%100)/10];
    //ones
    std::string onesPlace[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    std::string iColumnEval = onesPlace[decimal%10];
    std::string final = mColumnEval + cColumnEval + xColumnEval + iColumnEval;

        return final;
}


