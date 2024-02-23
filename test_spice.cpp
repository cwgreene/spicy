#include <ngspice/sharedspice.h>
#include <stdio.h>

int sendchar(char *c, int whichspice, void* data) {
    printf("%s\t%d\t%s\n", c, whichspice, (char *) data);
    return 0;
}

int main() {
    const char *hello = "hello";
    int result = ngSpice_Init(
        sendchar, /* SendChar: int (SendChar)(char *, int, void*)*/
        NULL, /* SendStat: int (SendStat)(char *, int *, void *)*/
        NULL, /* ControlledExit */
        NULL, /* SendData: int (SendData)(pvecvaluesall, int, int, void *)*/
        NULL, /* SendInitData: int (SendInitData)(pvecinfoall, int, void *)*/
        NULL, /* BGThreadRunning */
        (void *)hello);
    printf("All done with init\n");
    return 0;    
}
