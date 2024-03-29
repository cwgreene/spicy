#include <ngspice/sharedspice.h>
#include <stdio.h>
#include <unistd.h>

#include <latch>

#include <math.h>

struct CallbackData {
    std::latch latch{1};
};

int sendchar(char *c, int whichspice, void* data) {
    printf("%s\t%d\t%s\n", c, whichspice, (char *) data);
    return 0;
}

int bgthreadrunning(NG_BOOL isNotRunning, int, void *data) {
    CallbackData *d = (CallbackData *) data;
    if (isNotRunning) {
        printf("All done!\n");
        d->latch.count_down();
    } else {
        printf("Still running!\n");
    }
    return 0;
}

int vsrcdata(double *voltage, double time, char *node, int whichSpice, void *data) {
    *voltage = sin(time*2714);
    //printf("data: %s %lf\n", node, time);
    return 0;
}

int main() {
    const char *hello = "hello";
    CallbackData data;
    int result = ngSpice_Init(
        sendchar, /* SendChar: int (SendChar)(char *, int, void*)*/
        NULL, /* SendStat: int (SendStat)(char *, int *, void *)*/
        NULL, /* ControlledExit */
        NULL, /* SendData: int (SendData)(pvecvaluesall, int, int, void *)*/
        NULL, /* SendInitData: int (SendInitData)(pvecinfoall, int, void *)*/
        bgthreadrunning, /* BGThreadRunning */
        &data);
    printf("All done with init\n");
    ngSpice_Init_Sync(vsrcdata, /*GetVSRCData*/
        NULL, /*GetISRCData*/
        NULL, /*GetSyncData */
        NULL, /*int id*/
        NULL  /*data*/);

    ngSpice_Command ((char*) "source test.spice");
    printf("Loaded spice\n");
    ngSpice_Command((char*) "bg_run");
    data.latch.wait();
    return 0;    
}
