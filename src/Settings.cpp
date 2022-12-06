#include <Settings.h>
#include <iostream>

Settings::Settings(){
    shortest_path = "Valor do Menor Caminho: ";
    current_value = "Valor Atual: ";
    try_number = "Tentativa: "; 
    best_try = "Melhor Resultado: ";
    victory = "PARABENS!";

    if(!font.loadFromFile("assets/Fruit_Days.ttf")) exit(1);

    width = 800;
    height = 480;
}

Settings::~Settings(){

}