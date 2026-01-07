// PortCOM.h: interface for the PortCOM class. Modificada*
//331%
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// File written by DIego Losada 
// PEARL Project
// Archivo modificado
// 20 - 06 - 2016
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_PORTCOM_H__3C8B4324_571D_11D4_BC3E_0050DA386E22__INCLUDED_)
#define AFX_PORTCOM_H__3C8B4324_571D_11D4_BC3E_0050DA386E22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "stdafx.h"
#include<stdio.h>
#include<windows.h>
#include <atlstr.h>		//<- necesario para poder usar la clase CString!!!

//CONFIGURATION PARAMETERS
#define PORT_COMMS_INTERVAL_TIMEOUT			53	//millisecs
#define PORT_COMMS_TOTAL_TIMEOUT_MULTIPLIER 53	//millisecs
#define PORT_COMMS_TOTAL_TIMEOUT_CONSTANT	0   //millisecs

//BAUDS
#define PORT_COMMS_BAUDS_115200		1
#define PORT_COMMS_BAUDS_38400		2
#define PORT_COMMS_BAUDS_921600		3	//Mio	


//ERROR CODES
#define PORT_OK						 0
#define PORT_ERROR_CREATEFILE		-101
#define PORT_ERROR_SETDCB			-102
#define PORT_ERROR_WRITEFILE		-103 
#define PORT_ERROR_WRITENUM			-104 
#define PORT_ERROR_READFILE			-105
#define PORT_ERROR_READNUM			-106
#define PORT_ERROR_CLOSE_HANDLE		-107
#define PORT_ERROR_BAD_PARAMETER	-108
#define PORT_ERROR_TIMEOUT			-109



class CPortCOM
{
public:
	bool IsPortValid();
	int Receive(unsigned long num,PVOID pmessage);
	int ReceivePacket(int *pmensaje);		//Nueva método de recepción de datos
	int Send(unsigned long num, PVOID pmessage);
	int SendPacket(int *pmensaje);			//Nuevo método de envío de datos
	int Close();
	int Init(CString port);
	int SetBaud(int baud);
	BYTE SerIn(void);
	void SerOut(BYTE sbuf);
	void SetupCommPort(CString);
	CPortCOM();
	virtual ~CPortCOM();
private:
	DCB dcb;
	HANDLE  idCom;
	HANDLE  hCom;
	COMMTIMEOUTS timeouts;

};

#endif
