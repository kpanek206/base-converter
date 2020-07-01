#include "conversion_int.cpp"
#include "conversion_fr.cpp"
#include "main.h"

#include <stdio.h>

//Podstawa z ktorej konwersja jest wykonywana
int base_from = 10;
//Podstawa do ktorej konwersja jest wykonywana
int base_to = 16;
//Precyzja (maksymalna ilosc miejsc po przecinku przy konwersji)
int precision = 4;

char to_char(int a){
    if(a > 9)
        return a + 55; 
    else
        return a + 48;
}

int to_int(char a){
    if(a > 64)
        return a - 55;
    else
        return a - 48;
}

//Zmiana jednego z parametrow
void change_parameter(){
    cout << "Wprowadz 1 aby edytowac podstawe z ktorej liczba jest konwertowana" << endl;
    cout << "Wprowadz 2 aby edytowac podstawe do ktorej liczba jest konwertowana" << endl;
    cout << "Wprowadz 3 aby edytowac precyzje wprowadzanej liczby" << endl;

    int a = 0;

    while(a < 1 || a > 3){
        cin >> a;
    }

    cout << "Wprowadz nowa wartosc: " << endl;
    int input; 
    cin >> input;
    switch(a){
        case 1:
            base_from = input;
            cout << "Podstawa #1 zostala zmieniona na " << input << endl;
            break;
        case 2:
            base_to = input;
            cout << "Podstawa #2 zostala zmieniona na " << input << endl;
            break;
        case 3:
            precision = input;
            cout << "Precyzja zostala zmieniona na " << input << endl;
            break;
    }
}
//Konwersja wprowadzonego stringa na liczbe
pair<vector<int>, vector<int>> read_number(string input){
    pair<vector<int>, vector<int>> output;
    int i=0;
    char current_pos = input[0];

    while(current_pos != ',' && current_pos !='.' && i<input.length()){
        int value = to_int(current_pos);
        if(value >= base_from){       
            cout << "Wprowadzono wartosc spoza podstawy - wprowadz dowolna liczbe aby powrocic do menu glownego" << endl;
            cin >> input;
            cout << endl;
            main();
        }
        output.first.push_back(value);
        i++;
        current_pos = input[i];
    }
    if(current_pos == ',' || current_pos =='.'){
        while(i+1<input.length()){
            i++;
            output.second.push_back(to_int(input[i]));
        }
    }

    return output;
}

//Konwersja liczby miedzy systemami
pair<vector<int>, vector<int>> conversion(pair<vector<int>, vector<int>> number){
    pair<vector<int>, vector<int>> output;

    if(number.first.size() == 0)
        output.first = vector<int>(0);
    else
        output.first = convert_base_int(number.first, base_from, base_to);

    if(number.second.size() == 0)
        output.second = vector<int>(0);
    else
        output.second = convert_fraction(number.second, base_from, base_to, precision);  

    return output;
}

//Interpretacja wprowadzonych przez uzytkownika danych
void handle_input(string input){

    if(input == "zmien"){
        change_parameter();
    }

    else{
        pair<vector<int>, vector<int>> number = read_number(input);
        cout << "Przed konwersja" << endl;
        cout << "Czesc calkowita: ";
        if(number.first.size() == 0)
            cout << 0;
        else
            for(int i=0; i<number.first.size(); i++){
                cout  << to_char(number.first[i]);
            }
        cout << endl << "Czesc ulamkowa: ";
        if(number.second.size() == 0)
            cout << "BRAK";
        else
            cout << ".";
            for(int i=0; i<number.second.size(); i++){
                cout  << to_char(number.second[i]);
            }
        cout << endl;

        pair<vector<int>, vector<int>> converted_number = conversion(number);
        cout << endl << "Po konwersji" << endl;
        for(int i=0; i<converted_number.first.size(); i++)
            cout << to_char(converted_number.first[i]);
        cout << ".";
        for(int i=0; i<converted_number.second.size(); i++)
            cout << to_char(converted_number.second[i]);
        cout << endl;
    }
}


int main(){
    system("clear");
    cout << "Aktualna konwersja z podstawy " << base_from << " na podstawe " << base_to << endl;
    cout << "Ilosc miejsc po przecinku konwertowanej liczby: " << precision << endl;
    cout << "Aby edytowac jedna z podstaw lub precyzje wpisz \"zmien\"" << endl;
    cout << "Aby dokonac konwersji wprowadz liczbe" << endl; 
    string input;
    cin >> input;
    cout << endl;
    handle_input(input);
    cout << endl;
    cout << "Wprowadz dowolna wartosc aby kontynuowac" << endl;
    cin >> input;
    main();
}