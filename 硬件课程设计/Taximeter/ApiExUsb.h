
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the APIEXDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// APIEXDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef APIEXDLL_EXPORTS
#define APIEXDLL_API __declspec(dllexport)
#else
#define APIEXDLL_API __declspec(dllimport)
#endif

/*
// This class is exported from the ApiExDLL.dll
class APIEXDLL_API CApiExDLL {
public:
	CApiExDLL(void);
	// TODO: add your methods here.
};

extern APIEXDLL_API int nApiExDLL;

APIEXDLL_API int fnApiExDLL(void);
*/
#ifndef __APIEX_H__
#define __APIEX_H__

//#define APIEXDLL_API

#include <windows.h>
//#include "stdafx.h"

/*
 *	Interface Routines
*/
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ISR_ROUTINE)();
typedef void (*BOARD_FAILURE_ROUTINE)();
typedef void (*DMA_FINISH_ROUTINE)();
APIEXDLL_API bool Startup();
APIEXDLL_API void Cleanup();

APIEXDLL_API bool PortReadByte(WORD address, BYTE *pdata);
APIEXDLL_API bool PortWriteByte(WORD address, BYTE data);

APIEXDLL_API bool MemReadByte(WORD address, BYTE *pdata);
APIEXDLL_API bool MemWriteByte(WORD address, BYTE data);

APIEXDLL_API bool EnableIntr();
APIEXDLL_API bool DisableIntr();
APIEXDLL_API bool RegisterLocalISR(ISR_ROUTINE, ...);
APIEXDLL_API bool RegisterLocalISREx(ISR_ROUTINE, WORD);

APIEXDLL_API bool RegisterBoardFailureRoutine(BOARD_FAILURE_ROUTINE);

APIEXDLL_API bool RegisterDmaFinishNotifyRoutine(DMA_FINISH_ROUTINE);

APIEXDLL_API bool ProgMemReadByte(WORD address, BYTE* pdata);
APIEXDLL_API bool ProgMemWriteByte(WORD address, BYTE data);

APIEXDLL_API bool PramWrite(WORD address, BYTE data[], int len, bool bWrite);
APIEXDLL_API int DmaRead(BYTE buffer[], DWORD nBytesToRead);
APIEXDLL_API int DmaWrite(BYTE buffer[], DWORD nBytesToWrite);
//APIEXDLL_API int BulkRead(BYTE buffer[], DWORD nBytesToWrite);
//APIEXDLL_API int BulkWrite(BYTE buffer[], DWORD nBytesToWrite);
APIEXDLL_API bool Read8237(WORD address, BYTE* pdata);
APIEXDLL_API bool Write8237(WORD address, BYTE data);
APIEXDLL_API int DmaTransferHostToLocal(BYTE data[], WORD wBytes);

// +++++++++++++++++++++++++++++++++ //
APIEXDLL_API bool PortWriteEx(WORD address, BYTE data[], BYTE nBytesToWrite, BYTE nDelay);
APIEXDLL_API bool PortReadEx(WORD address, BYTE buffer[], BYTE nBytesToRead, BYTE nDelay);
APIEXDLL_API bool Read0809(WORD address, BYTE buffer[], BYTE nBytesToRead, BYTE nDelay);
// +++++++++++++++++++++++++++++++++ //

#ifdef __cplusplus
}
#endif
#endif
