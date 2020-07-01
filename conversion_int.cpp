#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

vector<int> convert_base_int(vector<int> input_number, int base_from, int base_to){
    
    int processed_number = 0;
    int current_position_value = 0;
    int biggest_index = input_number.size() - 1;
    //konwersja z podanego wektora liczb na liczbę

    for(int i=0; i<input_number.size(); i++){
       asm(

            //%eax - aktualnie obliczana pozycja
            //%ebx - iterator
            //%ecx - podstawa, z której jest wykonywana konwersja
            //%esi - waga aktualnej pozycji

            //waga aktualnej pozycji (ilość pozycji - 1 - indeks aktualnej pozycji (wartość iteratora))
            "subl %%ebx, %%esi;"

            "movl $0, %%ebx;"                   //iterator po potęgach podstawy
            
            "cmpl %%esi, %%ebx;"                //jeśli waga = 0, to wartość * waga pozycji = wartość pozycji
            "je end;"

            //pętla potęgowania podstawy, aby obliczyć wartość danej pozycji
            "power_loop:"
                "mull %%ecx;"
                "incl %%ebx;"                   //inkrementacja iteratora
                "cmpl %%esi, %%ebx;"            //porównanie iteratora potęgowania z aktualną wagą
                "jl power_loop;"                //jeśli mniejszy, powtórzenie mnożenia wartości przez podstawę
            "end:"
            //koniec pętli

        : "=a" (current_position_value)
        : "a" (input_number[i]), "b" (i), "c" (base_from),  "S" (biggest_index)
        );
        processed_number += current_position_value;
    }
    // Algorytm wyznaczania reprezentacji części całkowitej
    //
    // A - oryginalna liczba
    // B - podstawa do której konwertujemy
    //
    // 0. X(0) = A, i = 0
    // 1. X(i + 1) = int(X(i) / B)
    // 2. xi = X(i) - B * X(i + 1)
    // 3. i++
    // 4. if(X(i + 1)) != X(i)) -> 1.
    
    vector<int> output_number;
    int xi;
    //Krok 0
    int currentX =  processed_number;
    int nextX = currentX;
    do
    {
        currentX = nextX;
        //Krok 1 i 2 - wyliczenie X(i + 1) i xi
        asm(
            "movl $0x0, %%edx;"
            "divl %%ebx;"
            : "=a" (nextX), "=d" (xi)
            : "a" (currentX), "b" (base_to)
        );

        output_number.insert(output_number.begin(), xi);

    } while (nextX != currentX);    //krok 4 - sprawdzenie
    
    return output_number;
}