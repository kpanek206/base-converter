#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
//base_from - baza wejściowa
//base_to - baza wyjściowa
//prec - precyzja
vector<int> convert_fraction(vector<int> input_number, float base_from, float base_to, int prec){

    vector < int > output_number;
    float position = 0;
    float rest = 1;
    float inp, intPosition; 

    // zamiana wejściowej części ułamkowej na system dziesiętny
    for(int i = 0;i<input_number.size(); i++){
        asm(
                "fld %3;"
                "fld %2;"
                "fdivp;"         //rest /= base_from;
                "fstp %0;" 
                "fld %4;"
                "fld %2;"
                "fmulp;"         //position += inp*rest
                "fld %5;"
                "faddp;"
                "fstp %1;" 
            : "=m" (rest) , "=m" (position) 
            : "m" (rest), "m" (base_from), "m" (inp = input_number[i]), "m" (position)); 
    }

    // zamiana uzyskanej liczby na system wyjściowy
    // pętla kończy się wraz z uzyskaniem podanej precyzji
     for(int i = 0; i < prec; i++){
        asm ( "fld %1;"
              "fld %2;"
              "fmulp;"       //position *= base_to;
              "fstp %0;" : "=m" (position) : "m" (position), "m" (base_to) ) ;
        output_number.push_back(position);
        asm ( "fld %2;"
              "fld %1;"
              "fsubp;"       //position -= (int)(position);
              "fstp %0;" : "=m" (position) : "m" (position), "m" (intPosition = (int)(position)) ) ;
      }
    return output_number;
}