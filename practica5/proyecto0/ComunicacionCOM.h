//Biblioteca de comunicación versión final. 27-07-2016
//
//#include"USB.h" //Clase USB sin modificar, != a CUSB.h
//#include"usb2550.h"
#include <iostream>
using namespace std;
#include "CPortCOM.h"
#define PAQUETE 5
#define SYS_OFF 0	
#define LED_ON	1
#define PORTB_OUTPUT 2
#define PORTD_OUTPUT 3
#define PORTB_INPUT 4
#define PORTD_INPUT 5
#define ADC_ON 6
#define PWM1_ON 7
#define PWM2_ON 8
#define PWM1M_ON 9
#define PWM2M_ON 10
#define PWM1F_ON 11
#define PWM2F_ON 12
#define PWM_OFF 13
#define PB_ON 14
#define MATRIZ_LEDS 15
#define RS 32
#define EN 16
#define EN2 1
#define RS2 2
#define MIUVA 1010
#define ATANQH 2020

int escribirusb[PAQUETE] = { 0 }, leerusb[PAQUETE] = { 0 };
unsigned long a = PAQUETE;
//USB myusb;
CPortCOM miPto;
CString puerto = "COM6";    //<-checar el COM en el administrador de dispositivos, si fueran 2 dígitos: "\\\\.\\COM17"
//CString puerto; //= "\\\\.\\COM10";
/*void mandarpaquete(int control)
{
	escribirusb[0] = control;
	myusb.SendPacket(escribirusb, 5);
}*/
/////////////////////Funciones para mandar datos al PIC////////////////////////////////////
void reiniciadatos(int* arre)
{
	for (int i = 0; i < 3; i++)
		arre[i] = 0;
}
void inicia(int pto)
{
	if (pto > 0 && pto < 10)
		puerto.Format(_T("COM%d"), pto);
	else if (pto >= 10)
		puerto.Format(_T("\\\\.\\COM%d"), pto);
	//cout << pto << " texto: " << puerto << endl;
	//printf_s("%s\n", puerto);
	//puts(puerto);
	reiniciadatos(escribirusb);
	reiniciadatos(leerusb);
	miPto.Init(puerto);
}
void termina()
{
	miPto.Close();
}
void mandarpaquete(int control, int *apdato)
{
	reiniciadatos(escribirusb);
	escribirusb[0] = control;
	escribirusb[1] = *apdato;
	miPto.SendPacket(escribirusb);
}

void mandarpaquete(int control, char *apdato)
{
	reiniciadatos(escribirusb);
	escribirusb[0] = control;
	escribirusb[1] = *apdato;
	miPto.SendPacket(escribirusb);
}

void mandarpaquete(int control, int *apdato1, int *apdato2)
{
	reiniciadatos(escribirusb);
	escribirusb[0] = control;
	escribirusb[1] = *apdato1;
	escribirusb[2] = *apdato2;
	miPto.SendPacket(escribirusb);
}
//////////////////////Funciones para recibir datos del PIC////////////////
void recibirpaquete(int control, int *apdato)
{
	reiniciadatos(escribirusb);
	reiniciadatos(leerusb);
	escribirusb[0] = control;
	miPto.SendPacket(escribirusb);
	Sleep(100);
	miPto.ReceivePacket(leerusb);
	*apdato = leerusb[0];
}
void recibirpaquete(int control, int* apdato1, int* apdato2)
{
	escribirusb[0] = control;
	miPto.SendPacket(escribirusb);
	Sleep(100);
	//Sleep(10);
	miPto.ReceivePacket(leerusb);
	*apdato1 = leerusb[0];
	*apdato2 = leerusb[1];
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////Funciones para controlar LCD///////////////////////////////
/* Mandar datos al LCD en modo manual
printf("Mandar paquete a puerto D \n");
scanf("%d", &dato);
mandarpaquete(PORTD_OUTPUT, &dato);
*/
void ResetLCD(int tarjeta)
{
	if (tarjeta == MIUVA)
	{
		escribirusb[0] = PORTD_OUTPUT;
		miPto.SendPacket(escribirusb);
		escribirusb[1] = 3;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 19;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 3;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		//Limpiar LCD
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 17;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
	}
	else if (tarjeta == ATANQH)
	{
		escribirusb[0] = PORTD_OUTPUT;
		miPto.SendPacket(escribirusb);
		escribirusb[1] = 48;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 49;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 48;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		//Limpiar LCD
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 17;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(20);
	}
}
void BorrarLCD(int tarjeta)		//Limpia el LCD dejandolo en blanco
{
	if (tarjeta == ATANQH)
	{
		escribirusb[0] = PORTD_OUTPUT;
		miPto.SendPacket(escribirusb);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 17;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
	}
	else if (tarjeta == MIUVA)
	{
		escribirusb[0] = PORTD_OUTPUT;
		miPto.SendPacket(escribirusb);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 17;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
	}
}

void iniciarlcd(int tarjeta)		//Inicializa en LCD a 4 bits.
{
	if (tarjeta == MIUVA)
	{
		ResetLCD(MIUVA);
		BorrarLCD(MIUVA);
		escribirusb[0] = PORTD_OUTPUT;
		miPto.SendPacket(escribirusb);
		escribirusb[1] = 2;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 18;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 2;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 18;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 2;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 10;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 26;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 10;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 14;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 30;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 14;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 6;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 22;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 6;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 16;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 17;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(10);
		BorrarLCD(MIUVA);
	}
	else if (tarjeta == ATANQH)
	{
		ResetLCD(ATANQH);
		BorrarLCD(ATANQH);
		escribirusb[0] = PORTD_OUTPUT;
		miPto.SendPacket(escribirusb);
		escribirusb[1] = 32;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 33;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 32;				//Configurando el LCD a 4 bits
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 33;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 32;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 128;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 129;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 128;				//Configura LCD a 2 lineas
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 224;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 225;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 224;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;				//Funciones de cursor
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 1;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 0;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 48;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 49;
		miPto.SendPacket(escribirusb);
		Sleep(20);
		escribirusb[1] = 48;
		miPto.SendPacket(escribirusb);
		// Entra en modo SET
		BorrarLCD(ATANQH);
	}
}

void LCDlinea2(int tarjeta)		//Mueve el cursor a la segunda linea del LCD.
	{
		if (tarjeta == 1010)
		{
			escribirusb[0] = PORTD_OUTPUT;
			miPto.SendPacket(escribirusb);
			escribirusb[1] = 12;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 28;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 12;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 0;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 16;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 0;
			miPto.SendPacket(escribirusb);
			Sleep(100);
		}
		else if (tarjeta == 2020)
		{
			escribirusb[0] = PORTD_OUTPUT;
			miPto.SendPacket(escribirusb);
			escribirusb[1] = 192;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 193;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 192;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 0;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 1;
			miPto.SendPacket(escribirusb);
			Sleep(100);
			escribirusb[1] = 0;
			miPto.SendPacket(escribirusb);
		}

	}

void mandarcaracterLCD(int tarjeta, char letra)//Manda caracter por caracter
{

	char resultado, datolcd, dato;
	char mask2 = 240, mask1 = 15;
	dato = letra;
	if (tarjeta == 2020)
	{
		resultado = dato & mask2;				//Primer Nible mas significativo
		datolcd = resultado + RS2;	//Enable 0 RS 1
		//printf("Nible mas sig %d \n", datolcd);
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = resultado + EN2 + RS2; //Enable 1 RS 1
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = resultado + RS2; //Sólo genera el flanco de bajada sin alterar los datos
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		resultado = dato & mask1;			//Segundo Nible menos significativo
		datolcd = (resultado << 4) + RS2; //Enable 0 RS 1
		//printf("Nible menos sig %d \n", datolcd);
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = (resultado << 4) + EN2 + RS2; //Enable 1 RS 1
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = (resultado << 4) + RS2; //Sólo genera el flanco de bajada sin alterar los datos
		mandarpaquete(PORTD_OUTPUT, &datolcd);
	}
	else if (tarjeta == 1010)
	{
		resultado = dato & mask2;				//Primer Nible mas significativo
		datolcd = (resultado >> 4) + RS;	//Enable 0 RS 1
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = (resultado >> 4) + RS + EN; //Enable 1 RS 1
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		datolcd = (resultado >> 4) + RS; //Sólo genera el flanco de bajada sin alterar los datos
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		resultado = dato & mask1;			//Segundo Nible menos significativo
		datolcd = (resultado)+RS; //Enable 0 RS 1
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = (resultado)+RS + EN; //Enable 1 RS 1
		mandarpaquete(PORTD_OUTPUT, &datolcd);
		Sleep(10);
		datolcd = (resultado)+RS; //Sólo genera el flanco de bajada sin alterar los datos
		mandarpaquete(PORTD_OUTPUT, &datolcd);
	}
}


/////////////////
