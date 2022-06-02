/*
 * MillerRabinTest.cpp
 */
#include <iostream>
#include <cassert>
#include "MillerRabinTest.h"

using namespace std;

/*Integer gcd(Integer& a, Integer& b) {
    Integer  R("0");
    while ((a % b) > 0)  {
        R = a % b;
        a = b;
        b = R;
    }
    return b;
}*/

Integer MillerRabinTest::modularExponentation(const Integer& a,const Integer& b,const Integer& n){
    Integer d("1");
    Integer c("0");
    int i = b.BitCount();//Initialisierung von int i als Anzahl aller Bits von der Binärdarstellung von b
    while (i > -1 ) {//Algorithmus aus dem zahlentheorie Vorkurs
        c = 2 * c;
        d = (d * d) % n;

        if (b.GetBit(i) == 1) {//das Bit an Stelle i von b wird überprüft ob es eine 1 ist
            c = c + 1;
            d = (d * a) % n;
        }i--;}

    return d;
}

bool MillerRabinTest::witness(const Integer& a, const Integer& n) {
    Integer x("0");
    x = n - 1;
    Integer r("0");
    Integer b("0");
    Integer u("1");


    while (b != 1) {
        x=(x>>1);//halbierung durch bitshift um 1 bit nach rechts
        u = x;
        b = u % 2;//test ob zahl ungerade
        r++;
    }
    Integer test = u * Integer::Power2(r.ConvertToLong());

    cout << "A3 Testwerte" << endl
         << "r = "
         << r << endl
         << "r = "
         << r << endl
         << "r.ConvertToLong() = "
         << r.ConvertToLong() << endl
         << "u = "
         << u << endl
         << "n - 1 = u*(2^r) = "
         << test << endl
         << "n = "
         << n << endl;

    Integer d = modularExponentation(a, u, n);
    cout << "r = " << r << endl;

    Integer i("1");
    while (i != r) {
        x = d;
        d = (d * d) % n;

        if (d == 1 && x != 1 && x != n - 1) {

            return true;}
        i++;}
    if (d != 1) {
        return true;}


    return false;}


bool MillerRabinTest::isPrime(PRNG* rng, const Integer& n, unsigned int s) {

    unsigned int i = 1;
    Integer p("0");
    Integer x("11");//x durch rng ersetzen
    Integer  R("0");


    cout << "A4" << endl
         << "rng = " << rng << endl
         << "n = " << n << endl;

    while(i <s+1) {

        if(Integer::Gcd(x,n) != 1){
            return false;}

        p = modularExponentation(x , n -1 , n);

        if (p != 1) {
            return false;}
        i++;}
    return true;
}


Integer MillerRabinTest::exp(const Integer& b, const Integer& e) {
    Integer r("1");
// Berechnet b^e
// i   ... binäre Darstellung von e
// r ... Resultat der Berechnung
    int i = e.BitCount();
    while (i > -1 ) {
        r = (r*r);
        if (e.GetBit(i) == 1) {//das Bit an Stelle i von e wird überprüft ob es eine 1 ist
            r= b * r;
        }i--;
    }
    return r;
}

bool MillerRabinTest::searchSqrt(const Integer &n, Integer& r) {
    /*************************************************************************
    * @details Die Funktion berechnet in einer do-while schleife, ob der übergebene Parameter n eine Ganzzahlige Quadretwurzel besitzt.
     * \n
    *
    *
    * @param n ist const Integer, e ist eine unsigned int call-by-reference
    *
    * @return true, falls n eine Ganzahlige Quadratwurzel besitzt. false, falls nicht. In jedem Fall wird die errechnete Wurzel in die Variable r geschrieben.
    *************************************************************************/
    Integer l = n.BitCount() + 1;
    Integer y;
    y = exp(2, l);
    do{
        r = y;
        y = (r  + (n / r)) / 2;
    }while(y < r);
    if((r*r) == n)
        return true;
    return false;
}

bool MillerRabinTest::searchRoot(const Integer &n, unsigned int k, Integer &r)  {
    /*************************************************************************
    * @details Die Funktion ist eine erweiterung der searchSqrt Funktion. Sie berechnet, ob n eine k-te Wurzel besitzt.
     * \n
    *
    *
    * @param n ist const Integer, k ist eine unsigned int call-by-reference, r ist eine Integer call-by-reference
    *
    * @return true, falls n eine k-te Wurzel besitzt. false, falls nicht. In jedem Fall wird die errechnete Wurzel in die Variable r geschrieben und der exponent in die Variable k.
    *************************************************************************/
    Integer l = n.BitCount()/k + 1;
    Integer y = exp(2, l);;
    do{
        r = y;
        y = ((k - 1) * r + n / exp(r, k-1)) / k;
    }while(y < r);
    if(exp(r, k) == n)
        return true;
    return false;
}

bool MillerRabinTest::extendedEuklid(
 const Integer& a,
 const Integer& b,
 Integer& d,
 Integer& x,
 Integer& y
)
{
    return false;
}

bool MillerRabinTest::isIntegerPower(const Integer& n, Integer& b, unsigned int& e) {
    /*************************************************************************
    * @details Die Funktion ruft die Funktion searchRoot  in einer Schleife auf. Diese läuft n.bitCount lang und
     * wird abgebrochen, wenn das Ergebnis der Funktion true zurückgibt\n
    *
    *
    * @param n ist const Integer, b eine Integer call-by-reference, e ist eine unsigned int call-by-reference
    *
    * @return true, falls n eine Ganzahl-Potenz ist. false, falls nicht. In jedem Fall werden die Variablen e und k verändert.
   *************************************************************************/

    //b = Basis der GZ-Potenz (falls n eine GZ-Potenz ist)
    //e = exponent der GZ-Potenz
    bool x;
    while(e <= n.BitCount())
    {
        x = searchRoot(n, e, b);
        if(x)
        {
            return true;
        }
        else
        {
            e = e + 1;
        }
    }
  return false;
}
