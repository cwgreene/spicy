#include <ngspice/sharedspice.h>
#include <stdio.h>

int main() {
    int result = ngSpice_Init(
        NULL, /* SendChar */
        NULL, /* SendStat */
        NULL, /* ControlledExit */
        NULL, /* SendData */
        NULL, /* SendInitData */
        NULL, /* BGThreadRunning */
        NULL /* void * */);
}
