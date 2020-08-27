#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/poll.h>
#include <sys/time.h>

#define TRIMz(x) ((tz = (unsigned long long)(x)) < 0 ? 0 : tz)

void stat(int arg)
{

    FILE *fp_stat;
    char buff[128 + 1];
    static unsigned long long u, u_sav, u_frme, s, s_sav, s_frme,
        n, n_sav, n_frme, i, i_sav, i_frme,
        w, w_sav, w_frme, x, x_sav, x_frme,
        y, y_sav, y_frme, z, z_sav, z_frme,
        tot_frme, tz;
    float scale;
    fp_stat = fopen("/proc/stat", "r");
    while (fgets(buff, 128, fp_stat))
    {
        if (strstr(buff, "cpu"))
        {
            sscanf(buff, "cpu %Lu %Lu %Lu %Lu %Lu %Lu %Lu %Lu",
                   &u, &n, &s, &i, &w, &x, &y, &z);
            break;
        }
    }
    fclose(fp_stat);
    u_frme = u - u_sav;
    s_frme = s - s_sav;
    n_frme = n - n_sav;
    i_frme = TRIMz(i - i_sav);
    w_frme = w - w_sav;
    x_frme = x - x_sav;
    y_frme = y - y_sav;
    z_frme = z - z_sav;
    tot_frme = u_frme + s_frme + n_frme + i_frme + w_frme + x_frme + y_frme + z_frme;
    if (tot_frme < 1)
        tot_frme = 1;
    scale = 100.0 / (float)tot_frme;
    printf("%5.1f%%us,%5.1f%%sy,%5.1f%%ni,%5.1f%%id,%5.1f%%wa,%5.1f%%hi,%5.1f%%si,%5.1f%%st\n",
           u_frme * scale, s_frme * scale, n_frme * scale,
           i_frme * scale, w_frme * scale, x_frme * scale, y_frme * scale, z_frme * scale);
    float cpu_usage = (tot_frme -i_frme)/(float)tot_frme;
    printf("cpu_usage:%5.3f\n",cpu_usage);
    u_sav = u;
    s_sav = s;
    n_sav = n;
    i_sav = i;
    w_sav = w;
    x_sav = x;
    y_sav = y;
    z_sav = z;
}

int main()
{
    int i, j;
    struct itimerval tick;
    int res;

    /**
    *
    * Timer interrupt handler
    *
    */
    signal(SIGALRM, stat); /* SIGALRM handeler */
    /* setting first time interval */
    tick.it_value.tv_sec = 0;       // sec
    tick.it_value.tv_usec = 500000; // usec
    /* setting next time interval */
    tick.it_interval.tv_sec = 0;       // sec
    tick.it_interval.tv_usec = 500000; // usec
    res = setitimer(ITIMER_REAL, &tick, NULL);
    if (res)
        fprintf(stderr, "Error: timer setting faul.\n");
    else
        printf("Timer start...\n");
    /*
    * END
    */

    getchar();

    return 0;
}