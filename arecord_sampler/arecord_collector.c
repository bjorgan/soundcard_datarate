#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>

/**
 * Calculate time difference between two struct timevals.
 */
double duration(struct timeval tv_start, struct timeval tv_end) {
    double ret_duration = tv_end.tv_sec - tv_start.tv_sec
                        + (tv_end.tv_usec - tv_start.tv_usec)*1.0e-06;
    return ret_duration;
}

int main(int argc, char *argv[])
{
    const int DATA_LENGTH = 1024;
    float data[DATA_LENGTH];

    int i = 0;

    long tot_num_elements = 0;
    struct timeval start_time, curr_time;
    gettimeofday(&start_time, NULL);

    while (true) {
        //read data from stdout
        int num_elements = fread(data, sizeof(float), DATA_LENGTH, stdin);
        tot_num_elements += num_elements;

        //time since start
        gettimeofday(&curr_time, NULL);
        double call_duration = duration(start_time, curr_time);

        //current effective sample rate
        printf("%f\n", tot_num_elements/call_duration);

        i++;
    }
}
