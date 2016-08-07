#ifndef __HVEXPANSION_HPP
#define __HVEXPANSION_HPP

#include <xtl.h>
#include <stdio.h>
#include <stdlib.h>
#include <xkelib.h>

UINT64 HvxExpansionCall(DWORD magic, DWORD mode, ...);
VOID writeHVPriv( BYTE* src, UINT64 dest, DWORD size);
VOID readHVPriv( UINT64 src, BYTE* dest, DWORD size);
DWORD HvxInstallExpansion(INT64 addr, DWORD size);
BOOL installExpansion();



#endif