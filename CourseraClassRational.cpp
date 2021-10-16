#include <iostream>
#include <cmath>
using namespace std;

int evclidFast(int a, int b){
  while(b != 0){
    int t = a % b;
    a = b;
    b = t;
  }
  return a;
}

class Rational {
public:
    Rational() {
        field_numerator = 0;
        filed_denominator = 1;
    }

    Rational(int numerator, int denominator) {
      if(numerator < 0 && denominator < 0){
        numerator *= -1;
        denominator *= -1;
      } 
      if(numerator == 0 && denominator != 0){
        field_numerator = 0;
        filed_denominator = 1;
      } else if(numerator % denominator != 0){
        int nod = evclidFast(numerator, denominator);
        field_numerator = numerator / nod;
        filed_denominator = denominator / nod;
      } else {
        field_numerator = numerator;
        filed_denominator = denominator;
      }
      if(field_numerator > 0 && filed_denominator < 0){
        field_numerator *= -1;
        filed_denominator *= -1;
      }
    }

    int Numerator() const {
        return field_numerator;
    }

    int Denominator() const {
        return filed_denominator;
    }

private:
    int field_numerator;
    int filed_denominator;
};

    Rational& operator + (const Rational& first_number, const Rational& second_number){
      return Rational(first_number.Numerator() * second_number.Denominator() + second_number.Numerator() * first_number.Denominator(), first_number.Denominator() * second_number.Denominator());
    }

    Rational& operator - (const Rational& first_number, const Rational& second_number){
      return Rational(first_number.Numerator() * second_number.Denominator() - second_number.Numerator() * first_number.Denominator(), first_number.Denominator() * second_number.Denominator());
    }

    bool operator == (const Rational& first_number, const Rational& second_number){
      return ((first_number.Numerator() == second_number.Numerator()) && (first_number.Denominator() == second_number.Denominator()));
    }    


int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    {
        const Rational r(-1, 15);
        if (r.Numerator() != -1 || r.Denominator() != 15) {
            cout << "Rational(-1, 15) != -1/15" << endl;
            return 6;
        }
    }

    {
        const Rational r(1, -15);
        if (r.Numerator() != -1 || r.Denominator() != 15) {
            cout << "Rational(1, -15) != -1/15" << endl;
            return 7;
        }
    }

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}