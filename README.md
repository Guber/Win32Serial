# Win32Serial
Opening a Serial COM port, writing on it, reading from it and closing it.

Microsoft documentation on serial communicaton: https://msdn.microsoft.com/en-us/library/ff802693.aspx

You can change COM parametars and string to be sent, and well everything else. This table will get you started quickly. :)

| Parametar     | Line          | Code  |
| ------------- |:-------------:| -----:|
| COM port      | 16            |```c char ComPortName[] = "\\\\.\\COM4";``` |
| COM parametars| 42-45         |```c  cbSerialParams.BaudRate = CBR_9600;``` |
| String to send| 58            |```c   char lpBuffer[4] = {}``` |


