#include <iostream>
#include "CPortCOM.h"
#include <stdio.h>

using namespace std;
void reiniciadatos(int*);
#define PAQUETE 5

int escribirusb[PAQUETE] = { 0 }, leerusb[PAQUETE] = { 0 };
unsigned long a = PAQUETE;


int main() {

    CPortCOM miPto;
    CString puerto = "COM6";    //<-checar el COM en el administrador de dispositivos, si fueran 2 dígitos: "\\\\.\\COM17"
    int datos[3] = { 0,0,0 }, datofin, color;
    char pto, resp;
    miPto.Init(puerto);

    do {


        //Escribir en el puerto D o B una palabra de 8 bits
        reiniciadatos(datos);
        cout << "En que puerto desea escribir, B o D? ";
        cin >> pto;
        datos[0] = 20;          //Se va al default (en el pic) para apagar ambos puertos, B y D
        miPto.SendPacket(datos);


        if (pto == 'd' || pto == 'D')
            datos[0] = 3;       //Palabra de control para ESCRIBIR al puerto D


        else if (pto == 'b' || pto == 'B')
            datos[0] = 2;       //Palabra de control para ESCRIBIR al puerto B

        cout << "Presione v para encender el LED verde, a para encender el LED amarillo y r para encender el LED rojo: ";
        cin >> resp;

        if (resp == 'v' || resp == 'A')
            color = '4' ;

        else if (resp == 'a' || resp == 'A')
            color = '2';

        else if (resp == 'r' || resp == 'R')
            color = '1';

        datos[1] = color;
        miPto.SendPacket(datos);


       
        cout << "\nOtra vuelta? (1 = si, 0 = no) ";
        cin >> datofin;

    } while (datofin);
    std::cout << "\nPrueba terminada!\n";

    miPto.Close();      //<--- IMPORTANTE CERRAR EL PUERTO
    system("pause");
    return 0;

    
}
void reiniciadatos(int* arre)
{
    for (int i = 0; i < 3; i++)
        arre[i] = 0;
}

