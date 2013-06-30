#include "handler.h"

CrashInfo* CrashHandler::info = 0;
DWORD CrashHandler::handleShell = 0;
HANDLE CrashHandler::handle = 0;

void WriteDump()
{
  HANDLE process = GetCurrentProcess();

  DWORD processID = CrashHandler::info->parentId;

  //Create the file we're going to write to.
  HANDLE file = CreateFile( L"dump.dmp", GENERIC_READ | GENERIC_WRITE, 
                            0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

  MINIDUMP_TYPE dumpType = MiniDumpWithPrivateReadWriteMemory;

  MINIDUMP_EXCEPTION_INFORMATION information;

  ZeroMemory(&information, sizeof(information));

  information.ThreadId = GetCurrentThreadId();

  information.ExceptionPointers = CrashHandler::info->pExcept;

  information.ClientPointers = FALSE;

  MiniDumpWriteDump(process, processID, file, dumpType, &information, NULL, NULL);

  CloseHandle(file);
}

DWORD WINAPI HandlerShell( void* )
{
  WriteDump();
  return 0;
}

CrashHandler::CrashHandler()
{
  CrashHandler::info = new CrashInfo();
  CrashHandler::handle = CreateThread(NULL, 0, HandlerShell, 0, CREATE_SUSPENDED, &CrashHandler::handleShell);
  SetUnhandledExceptionFilter(LogException);
}

CrashHandler::~CrashHandler()
{
  delete CrashHandler::info;
}


LONG WINAPI CrashHandler::LogException( EXCEPTION_POINTERS* pException )
{
  CrashHandler::info->parentId = GetCurrentProcessId();
  CrashHandler::info->pExcept = pException;
  ResumeThread(CrashHandler::handle);
  WaitForSingleObject(CrashHandler::handle, INFINITE);
  return EXCEPTION_CONTINUE_SEARCH;
}
