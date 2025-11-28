#include <iostream>
#include "CPortCOM.h"

using namespace std;
void reiniciadatos(int*);
#define PAQUETE 5

int escribirusb[PAQUETE] = { 0 }, leerusb[PAQUETE] = { 0 };
unsigned long a = PAQUETE;


int main() {

    CPortCOM miPto;
    CString puerto = "COM6";    //<-checar el COM en el administrador de dispositivos, si fueran 2 dígitos: "\\\\.\\COM17"
    int datos[3] = { 0,0,0 }, datofin, fin, datofinb, resultado;
    char pto, resp;
    miPto.Init(puerto);

    do {


        //Leer el dato del puerto analogico (puerto A0)
        reiniciadatos(datos);
        cout << "\nSe leera el valor del puerto d" << endl;
        system("pause");
        datos[0] = 5;           //Palabra de control para LEER loss puertos d
        miPto.SendPacket(datos);
        Sleep(10);
        miPto.ReceivePacket(datos);
        printf("Datos recibidos: %d\t%d\t%d\n", datos[0], datos[1], datos[2]);
        datofin = datos[0];
        

        //Leer el dato del puerto analogico (puerto A0)
        reiniciadatos(datos);
        cout << "\nSe leera el valor del puerto b" << endl;
        system("pause");
        datos[0] = 4;           //Palabra de control para LEER loss puertos d
        miPto.SendPacket(datos);
        Sleep(10);
        miPto.ReceivePacket(datos);
        printf("Datos recibidos:  %d\t%d\t%d\n", datos[0], datos[1], datos[2]);
        datofinb = datos[0];
        std::cout << std::endl;

        std::cout << "----------------------------------" << std::endl;
        std::cout << std::endl;

        // Operaciones a nivel de bit
        resultado = datofin or_eq datofinb;
        cout << "La operacion OR entre ambos numeros en decimal es: " << resultado << endl;
        std::cout << std::endl;

        resultado = datofin & datofinb;
        cout << "La operacion AND entre ambos numeros en decimal es: " << resultado << endl;
        std::cout << std::endl;

        resultado = datofin << 1;
        cout << "El corrimiento de un bit a la izquierda de puerto B es: " << resultado << endl;
        std::cout << std::endl;

        resultado = datofin >> 1;
        cout << "El corrimiento de un bit a la derecha de puerto B es: " << resultado << endl;
        std::cout << std::endl;

        std::cout << "----------------------------------" << std::endl;
        std::cout << std::endl;

        cout << "El valor en el puerto B es: " << oct << datofin << " en sistema octal" << endl;
        std::cout << std::endl;

        cout << "El valor en el puerto D es: " << oct << datofinb << " en sistema octal" << endl;
        std::cout << std::endl;

        cout << "El valor en el puerto B es: " << hex << datofin << " en sistema hexadecimal" << endl;
        std::cout << std::endl;

        cout << "El valor en el puerto D es: " << hex << datofinb << " en sistema hexadecimal" << endl;
        std::cout << std::endl;

        

       
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

