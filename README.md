# Win32Serial
Opening a Serial COM port, writing on it, reading from it and closing it.

Microsoft documentation on serial communicaton: https://msdn.microsoft.com/en-us/library/ff802693.aspx

COM port is defined on the line 16: char ComPortName[] = "\\\\.\\COM4";

COM parametars are defined on lines 42-45:  dcbSerialParams.BaudRate = CBR_9600; // BaudRate = 9600
    dcbSerialParams.ByteSize = 8; // ByteSize = 8
    dcbSerialParams.StopBits = 1; // StopBits = 1
    dcbSerialParams.Parity = NOPARITY; // Parity = None 
    
String being sent is defined on line 58
char lpBuffer[4] = {
      'T',
      'E',
      'M',
      'P'
    }
