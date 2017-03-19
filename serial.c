#include <windows.h> 
#include <stdio.h>

  // Opening a Serial COM port, writing on it, reading from it and closing it :)
  // Written by Emanuel Guberovic and the allmighty help of online threads and Microsoft documentation

  int main() {

    /*
	/* Microsoft documentation on serial communicaton:
	/* https://msdn.microsoft.com/en-us/library/ff802693.aspx
	*/

    /*------------------------- Creating a HANDLE for the Serial connection ----------------------------------*/
    HANDLE hComm;
    char ComPortName[] = "\\\\.\\COM4";

    //port name, Read/Write, No Sharing, No Security, Open existing port only, Non Overlapped I/O, Null for Com Devices
    hComm = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hComm == INVALID_HANDLE_VALUE) {
      fprintf(stderr, "Error whilst opening serial port %s\r\n", ComPortName);
    } else {
      printf("Opening serial port %s successfull\r\n", ComPortName);
    }

    /*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

    // Initializing DCB structure	
    DCB dcbSerialParams = {
      0
    };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    //retreive current settings
    int Status = GetCommState(hComm, & dcbSerialParams);

    if (Status == FALSE) {
      fprintf(stderr, "Error whilst getting current COM state .r\n");
    }

    dcbSerialParams.BaudRate = CBR_9600; // BaudRate = 9600
    dcbSerialParams.ByteSize = 8; // ByteSize = 8
    dcbSerialParams.StopBits = 1; // StopBits = 1
    dcbSerialParams.Parity = NOPARITY; // Parity = None 

    Status = SetCommState(hComm, & dcbSerialParams); //Configuring the port according to settings in DCB 

    if (Status == FALSE) {
      fprintf(stderr, "Error whilst setting DCB Structure .r\n");
    } else {
      printf("\n\n    Setting DCB Structure Successfull\n");
    }

    /*---------------------------------------- Writing on TX -------------------------------------------------*/

    //Char array that repreents a string which is to be sent on TX
    char lpBuffer[4] = {
      'T',
      'E',
      'M',
      'P'
    };
    DWORD dNoOFBytestoWrite = sizeof(lpBuffer);
    DWORD dNoOfBytesWritten = 0;

    // Handle to the Serial port, Data to be written to the port, No of bytes to write, Bytes written
    Status = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite, & dNoOfBytesWritten, NULL);

    if (Status == FALSE) {
      fprintf(stderr, "Error whilst sending message %s to TX on %sr\n", lpBuffer, ComPortName);
    } else {
      printf("Succsfully sent message %s to TX on %sr\n", lpBuffer, ComPortName);
    }

    /*------------------------------------ Setting Receive Mask ----------------------------------------------*/

    Status = SetCommMask(hComm, EV_RXCHAR); //Set the communication device to monitor for character reception

    if (Status == FALSE) {
      fprintf(stderr, "Error whilst setting COM Mask for monitoring on charcter reception event.r\n");
    } else {
      printf("Setting COM Mask for monitoring on character reception event successfull.r\n");
    }

    /*--------------------------------------- Wait Event  ----------------------------------------------------*/

    DWORD dwEventMask;
    Status = WaitCommEvent(hComm, & dwEventMask, NULL);
    if (Status == FALSE) {
      fprintf(stderr, "Error whilst configuring COM for waiting on event .r\n");
    } else {
      printf("COM configured to wait on event succssefull.r\n");
    }

    /*--------------------------------- Setting COM Timeouts -------------------------------------------------*/

    COMMTIMEOUTS timeouts = {
      0
    };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, & timeouts) == FALSE)
      fprintf(stderr, "Error whilst setting COM timeouts .r\n");
    else
      printf("Setting Serial Port timeouts Successfull\r\n");

    /*--------------------------------- Receiving data -------------------------------------------------*/

    //temporary char, buffer and counter for redaing from RX
    char TempChar;
    char SerialBuffer[256];
    DWORD NoBytesRead;
    int i = 0, j = 0;

    // Loop whilst there is something being read or  until we havent read anything :)
    do {
      //Handle of the Serial port, Temporary character, Size of TempChar, /Number of bytes read	 
      ReadFile(hComm, & TempChar, sizeof(TempChar), & NoBytesRead, NULL);
      SerialBuffer[i++] = TempChar; // Store Tempchar into buffer
    } while ((NoBytesRead > 0) || (i == 0));

    printf("Succsfully read message %s on RX on %sr\n", SerialBuffer, ComPortName);

    /*--------------------------------- Closing the Handle --------------------------------------------*/
    CloseHandle(hComm); //Closing the Serial Port

    return 0;
  }
