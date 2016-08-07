#ifndef __TOOLS_H_
#define __TOOLS_H_

#pragma once
#include <xtl.h>
#include <stdio.h>
#include <xkelib.h>

#ifdef DEVKIT
#include <xbdm.h>
#endif

typedef HRESULT (*pDmSetMemory)(LPVOID lpbAddr, DWORD cb, LPCVOID lpbBuf, LPDWORD pcbRet);


class MemoryBuffer
{
public:

MemoryBuffer( DWORD dwSize = 512 )
{
m_pBuffer = NULL;
m_dwDataLength = 0;
m_dwBufferSize = 0;

if( ( dwSize < UINT_MAX ) && ( dwSize != 0 ) )
{
m_pBuffer = ( BYTE* )malloc( dwSize + 1 );    // one more char, in case when using string funcions
if( m_pBuffer )
{
m_dwBufferSize = dwSize;
m_pBuffer[0] = 0;
}
}
};

~MemoryBuffer()
{
if( m_pBuffer )
free( m_pBuffer );

m_pBuffer = NULL;
m_dwDataLength = 0;
m_dwBufferSize = 0;
};

    // Add chunk of memory to buffer
    BOOL    Add( const void* p, DWORD dwSize )
    {
        if( CheckSize( dwSize ) )
        {
            memcpy( m_pBuffer + m_dwDataLength, p, dwSize );
            m_dwDataLength += dwSize;
            *( m_pBuffer + m_dwDataLength ) = 0;    // fill end zero
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    };

    // Get the data in buffer
    BYTE* GetData() const
    {
        return m_pBuffer;
    };

    // Get the length of data in buffer
    DWORD   GetDataLength() const
    {
        return m_dwDataLength;
    };

    // Rewind the data pointer to the begining
    void    Rewind()
    {
        m_dwDataLength = 0; m_pBuffer[ 0 ] = 0;
    };

    // Automatically adjust increase buffer size if necessary
    BOOL    CheckSize( DWORD dwSize )
    {
        if( m_dwBufferSize >= ( m_dwDataLength + dwSize ) )
        {
            return TRUE;    // Enough space
        }
        else
        {
            // Try to double it
            DWORD dwNewSize = max( m_dwDataLength + dwSize, m_dwBufferSize * 2 );
            BYTE* pNewBuffer = ( UCHAR* )realloc( m_pBuffer, dwNewSize + 1 );        // one more char
            if( pNewBuffer )
            {
                m_pBuffer = pNewBuffer;
                m_dwBufferSize = dwNewSize;
                return TRUE;
            }
            else
            {
                // Failed
                return FALSE;
            }
        }
    }

private:

BYTE* m_pBuffer;

    DWORD m_dwDataLength;

    DWORD m_dwBufferSize;
};






VOID XNotifyUI(PWCHAR pwszStringParam);
BOOL DumpFile(CHAR *szFileName, BYTE *pbData, DWORD dwSize);
BYTE *GetFile(CHAR *szPath, PDWORD pdwOutSize);
HRESULT SetMemory(VOID* Destination, VOID* Source, DWORD Length);
DWORD ResolveFunction(PCHAR modname, DWORD ord);
VOID PatchInJump(PDWORD addr, DWORD dest, BOOL linked);
HRESULT MountPath(const char* szDrive, const char* szDevice, BOOL both);
DWORD PatchModuleImport(CHAR* Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
DWORD PatchModuleImport(PLDR_DATA_TABLE_ENTRY Module, CHAR* ImportedModuleName, DWORD Ordinal, DWORD PatchAddress);
BOOL XeKeysPkcs1Verify(const BYTE* pbHash, const BYTE* pbSig, XECRYPT_RSA* pRsa);
BOOL CReadFile(const CHAR * FileName, MemoryBuffer &pBuffer);
BOOL CWriteFile(const CHAR* FilePath, const VOID* Data, DWORD Size);
BOOL FileExists(LPCSTR lpFileName);
HRESULT CreateSymbolicLink(CHAR* szDrive, CHAR* szDeviceName, BOOL System);
HRESULT DeleteSymbolicLink(CHAR* szDrive, BOOL System);
VOID PatchInBranch(DWORD* Address, DWORD Destination, BOOL Linked);

#ifdef DEVKIT
VOID PatchInJumpDev(DWORD addr, DWORD dest, BOOL linked);
#endif

VOID hookFunctionStartEx(...);//(Address, SaveStubAddress, Destination)

#endif
