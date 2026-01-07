// CPortCOM.cpp: implementation of the CPortCOM class.Modificada*
//Es necesario utilizar juego de caracteres Unicode y MFC con un dll compartido
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// File written by %331
// 14 - Junio -2016
// 
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "CPortCOM.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPortCOM::CPortCOM()
{
	idCom = NULL;
}

CPortCOM::~CPortCOM()
{

}

int CPortCOM::Init(CString port)
{
	idCom = CreateFile(port,
		GENERIC_READ | GENERIC_WRITE,
		0,	//Acceso exclusivo
		NULL,	//sin atributos de seguridad
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (idCom == INVALID_HANDLE_VALUE)
	{
		idCom = NULL;
		return(PORT_ERROR_CREATEFILE);
	}
	else
	{

		GetCommState(idCom, &dcb);
		dcb.BaudRate = CBR_9600;
		dcb.ByteSize = 8;
		dcb.Parity = NOPARITY;
		dcb.StopBits = ONESTOPBIT;

		dcb.fBinary = 1;
		dcb.fOutxCtsFlow = 0;
		dcb.fOutxDsrFlow = 0;
		dcb.fDtrControl = DTR_CONTROL_DISABLE;
		dcb.fDsrSensitivity = 0;
		dcb.fTXContinueOnXoff = 1;
		dcb.fOutX = 0;
		dcb.fInX = 0;
		dcb.fErrorChar = 0;
		dcb.fNull = 0;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		dcb.fAbortOnError = 1;
		dcb.XonLim = 2048;
		dcb.XoffLim = 512;
		dcb.XonChar = 17;
		dcb.XoffChar = 19;
		dcb.ErrorChar = 0;
		dcb.EofChar = 0;
		dcb.EvtChar = 0;

		dcb.DCBlength = sizeof(dcb);
		int ret = SetCommState(idCom, &dcb);
		if (ret == 0)
		{
			int err = GetLastError();
			CloseHandle(idCom);
			idCom = NULL;
			return(PORT_ERROR_SETDCB);
		}
		timeouts.ReadIntervalTimeout = 1;   /*PORT_COMMS_INTERVAL_TIMEOUT*/
		timeouts.ReadTotalTimeoutMultiplier = 1;  /*PORT_COMMS_TOTAL_TIMEOUT_MULTIPLIER*/
		timeouts.ReadTotalTimeoutConstant = PORT_COMMS_TOTAL_TIMEOUT_CONSTANT;
		timeouts.WriteTotalTimeoutMultiplier = 0;
		timeouts.WriteTotalTimeoutConstant = 0;
		SetCommTimeouts(idCom, &timeouts);
		return(PORT_OK);
	}
}

int CPortCOM::Close()
{
	if (CloseHandle(idCom) != 0)return(PORT_OK);
	else return(PORT_ERROR_CLOSE_HANDLE);
	idCom = NULL;
}

int CPortCOM::Send(unsigned long num,PVOID pmessage)
{
	unsigned long written = 0;
	if (WriteFile(idCom, pmessage, num, &written, NULL) == 0) 	return(PORT_ERROR_WRITEFILE);
	if (written != num) return(PORT_ERROR_WRITENUM);
	//flush(idCom);
	return(PORT_OK);
}

int CPortCOM::Receive(unsigned long num, /*unsigned char **/PVOID pmessage) //Es necesario utilizar caracteres Unicode
{

	unsigned long read = 0;
	unsigned long EnviadoOk = 0;

	EnviadoOk = ReadFile(idCom, pmessage, num, &read, NULL);
	if (EnviadoOk == 0) return PORT_ERROR_READFILE;
	//ReadFile -> If the function fails, the return value is zero
	return(EnviadoOk);
}

bool CPortCOM::IsPortValid()
{
	if (idCom != NULL)return(true);
	else return(false);
}

int CPortCOM::SetBaud(int baud)
{
	if (baud<1 || baud>3)return PORT_ERROR_BAD_PARAMETER;
	if (baud == PORT_COMMS_BAUDS_115200)dcb.BaudRate = CBR_115200;
	if (baud == PORT_COMMS_BAUDS_38400)dcb.BaudRate = CBR_38400;
	if (SetCommState(idCom, &dcb) == 0)
		return(PORT_ERROR_SETDCB);
	return(PORT_OK);
}

void CPortCOM::SetupCommPort(CString port)
{
	DCB dcb;
	hCom = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	GetCommState(hCom, &dcb);
	dcb.BaudRate = CBR_19200;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	SetCommState(hCom, &dcb);
}

void CPortCOM::SerOut(BYTE sbuf)
{
	DWORD n;
	WriteFile(hCom, &sbuf, 1, &n, NULL);
}

BYTE CPortCOM::SerIn(void)
{
	BYTE sbuf;
	DWORD n;
	ReadFile(hCom, &sbuf, 1, &n, NULL);
	return sbuf;
}
/////////////////////////Nuevos métodos

int CPortCOM::SendPacket(int* pmensaje)
{
	int*  datoenviar;
	datoenviar = pmensaje;
	Send(1, datoenviar);
	datoenviar = pmensaje+1;
	Send(1, datoenviar);
	datoenviar = pmensaje + 2;
	Send(1, datoenviar);
	return 0;
}

int CPortCOM::ReceivePacket(int *pmensaje)
{
	Sleep(300);
	*pmensaje = 0;
	Receive(2, pmensaje);
	return 0;
}