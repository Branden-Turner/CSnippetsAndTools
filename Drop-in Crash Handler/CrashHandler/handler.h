#ifndef HANDLER_H
#define HANDLER_H

#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")

struct CrashInfo
{
  EXCEPTION_POINTERS* pExcept;
  DWORD parentId;
};

class CrashHandler
{
  public:
    CrashHandler();
    ~CrashHandler(); 
    static LONG WINAPI LogException( EXCEPTION_POINTERS* pException );
    static CrashInfo* info;
    static DWORD handleShell;
    static HANDLE handle;
};

void WriteDump();

#endif HANDLER_H
