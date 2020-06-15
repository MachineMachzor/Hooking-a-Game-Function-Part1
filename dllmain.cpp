// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

typedef int(*_sum)(int x, int y);


_sum sum;





DWORD WINAPI MainThread(LPVOID param)
{
    //AllocConsole();
    //FILE* f;
    //freopen_s(&f, "CONOUT$", "w", stdout);

    uintptr_t modBase = (uintptr_t)GetModuleHandle(L"hookThisWeirdSumFunction.exe"); //NULL parameter makes it return the base address loading this module
    sum = (_sum)(modBase + 0x00011096); //0x12630 makes the func print twice



    //uintptr_t sum = ((uintptr_t)GetModuleHandle(L"hookThisWeirdSumFunction.exe")) + 0x12630;



    //x1 = (_x1)(modBase + 0x00012668);



    while (true)
    {
        if (GetAsyncKeyState(VK_F1) & 1)
        {
            int five = sum(1, 4);
            std::cout << five << std::endl;
            
            
            //works += 1;

        }
    }

    //FreeConsole();
    //fclose(f);
    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )


{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

