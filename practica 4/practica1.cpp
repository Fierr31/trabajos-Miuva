#include <iostream>
#include "CPortCOM.h"

using namespace std;
void reiniciadatos(int*);
#define PAQUETE 5

int escribirusb[PAQUETE] = { 0 }, leerusb[PAQUETE] = { 0 };
unsigned long a = PAQUETE;


int main() {

    CPortCOM miPto;
    CString puerto = "COM4";    //<-checar el COM en el administrador de dispositivos, si fueran 2 dígitos: "\\\\.\\COM17"
    int datos[3] = { 0,0,0 }, datofin, fin, datofinb, resultado, dato, color, estado;
    char pto, resp;
    miPto.Init(puerto);

    do {

        int dato;

        cout << "Ciclo WHILE con comunicacion usb" << endl;

        cout << "" << endl;

        cout << "Presione el boton para apagar el led" << endl;

        //Leer el dato del puerto analogico (puerto A0)
        reiniciadatos(datos);
        cout << "\nSe leera el valor del puerto analogico (y del convertidor ADC)" << endl;
        system("pause");
        datos[0] = 14;           //Palabra de control para LEER el dato del ADC, puerto A0
        miPto.SendPacket(datos);
        Sleep(10);
        miPto.ReceivePacket(datos);
        printf("Datos recibidos: %d\t%d\t%d\n", datos[0], datos[1], datos[2]);
        estado = datos[0];
        cout << "Dato leido: " << estado << endl;
      
        std::cout << std::endl;


        while (estado == 0) {

            datos[0] = 3;       //Palabra de control para ESCRIBIR al puerto D

            color = '1';

            datos[1] = color;
            miPto.SendPacket(datos);
            Sleep(1000);

            datos[1] = '0';
            miPto.SendPacket(datos);
            Sleep(1000);

            reiniciadatos(datos);
            
            datos[0] = 14;           //Palabra de control para LEER el dato del ADC, puerto A0
            Sleep(1000);
            miPto.SendPacket(datos);
            Sleep(10);
            miPto.ReceivePacket(datos);
            printf("Datos recibidos: %d\t%d\t%d\n", datos[0], datos[1], datos[2]);
            estado = datos[0];
            cout << "Dato leido: " << estado << endl;

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

