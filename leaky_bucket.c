#include <stdio.h>

struct packet {
    int time, size;
};

int main() {
    int n, i, k = 0, bucket_size, current_bucket = 0, output_rate;
    printf("Enter the number of packets: ");
    scanf("%d", &n);

    struct packet p[n];
    for (i = 0; i < n; i++) {
        printf("Enter the time and size of packet %d: ", i + 1);
        scanf("%d %d", &p[i].time, &p[i].size);
    }

    printf("Enter the bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter the output rate: ");
    scanf("%d", &output_rate);

    int max_time = p[n - 1].time;

    for (i = 0; i <= max_time || current_bucket != 0; i++) {
        printf("\nAt time %d", i);

        if (k < n && p[k].time == i) {
            if (bucket_size >= current_bucket + p[k].size) {
                current_bucket += p[k].size;
                printf("\n%d byte packet is inserted", p[k].size);
            } else {
                printf("\n%d byte packet is discarded", p[k].size);
            }
            k++;
        }

        if (current_bucket == 0) {
            printf("\nNo packets to transmit");
        } else {
            int transfer = (current_bucket >= output_rate) ? output_rate : current_bucket;
            printf("\n%d bytes transferred", transfer);
            current_bucket -= transfer;
        }
        printf("\nPackets in the bucket: %d byte(s)", current_bucket);
    }

    return 0;
}
