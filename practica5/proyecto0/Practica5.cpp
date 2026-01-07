/*

    ⠀        ⢀⣠⣤⣶⣶⣶⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
    ⠀⠀⠀⠀⠀⠀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡀⠀⠀⠀⠀⠀
    ⠀⠀⠀⣠⣴⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⣵⣄⠀⠀⠀
    ⠀⠀⢾⣻⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⡀⠀
    ⠀⠸⣽⣻⠃⣿⡿⠋⣉⠛⣿⣿⣿⣿⣿⣿⣿⣿⣏⡟⠉⡉⢻⣿⡌⣿⣳⡥⠀
    ⠀⢜⣳⡟⢸⣿⣷⣄⣠⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣤⣠⣼⣿⣇⢸⢧⢣⠀
    ⠀⠨⢳⠇⣸⣿⣿⢿⣿⣿⣿⣿⡿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⠀⡟⢆⠀
    ⠀⠀⠈⠀⣾⣿⣿⣼⣿⣿⣿⣿⡀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣽⣿⣿⠐⠈⠀⠀
    ⠀⢀⣀⣼⣷⣭⣛⣯⡝⠿⢿⣛⣋⣤⣤⣀⣉⣛⣻⡿⢟⣵⣟⣯⣶⣿⣄⡀⠀
    ⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣾⣶⣶⣴⣾⣿⣿⣿⣿⣿⣿⢿⣿⣿⣧
    ⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⣿⡿

*/


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
    int datos[3] = { 0,0,0 }, fin, color, opcion, numero, led;
    char pto, resp;
    miPto.Init(puerto);

    do {

        cout << "SWITCH CASE con comunicacion USB " << endl;
        
        cout << "Indique un ejercicio ";
        cin >> opcion;

        datos[0] = 3;       //Palabra de control para ESCRIBIR al puerto D

        switch (opcion) {

        case 1:

            int led;

            cout << "Indique la posicion del LED: ";
            cin >> numero;


            if (numero == 0)
                led = 1;

            if (numero == 1)
                led = 2;

            if (numero == 2)
                led = 4;

            if (numero == 3)
                led = 8;

            if (numero == 4)
                led = 16;

            if (numero == 5)
                led = 32;

            if (numero == 6)
                led = 64;

            if (numero == 7)
                led = 128;

            

            datos[1] = led;
            miPto.SendPacket(datos);        

            break;

        case 2:
            printf("Secuencia de LEDs\n");

            led = 0;
            
                while ( led < 128) {

  
                    led = 1;
                    Sleep(500);

                    
                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);

                    

                    led = 2;
                    Sleep(500);

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);


                    led = 4;
                    Sleep(500);

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);


                    led = 8;
                    Sleep(500);

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);


                    led = 16;
                    Sleep(500);               

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);


                    led = 32;
                    Sleep(500);         

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);


                    led = 64;
                    Sleep(500);

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);


                    led = 128;
                    Sleep(500);

                    datos[1] = led;
                    miPto.SendPacket(datos);
                    Sleep(500);
                 
                }

        break;
            
        default:
            printf("Opcion no valida\n");
        }

        cout << "\nOtra vuelta? (1 = si, 0 = no) ";
        cin >> fin;

    } while (fin);
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