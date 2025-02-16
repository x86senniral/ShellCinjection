# ShellCinjection
Simple shellcode injector

- Replace shellcode (generate one using msfvenom for example.)

- Compile
```
g++ -o poc poc.cpp
```

- Usage:
```
poc.exe <PID OF THE PROCESS>
```

# r13Encrypted.cpp
This one is encoded using rot13. The shellcode provided is a simple popup box that is already encoded in rot13 and then later on decrypted when allocating the memory.
```cpp
void rot13_encrypt(unsigned char* data, size_t length) {
    for (int i = 0; i < length; ++i) {
        data[i] = data[i] + 13;
    }
}
```
