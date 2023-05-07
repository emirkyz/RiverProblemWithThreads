//
// Created by emir on 5/6/23.
//
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#define N 4

sem_t bilet,disla, test;
int hackers = 0;
int microsoftlar = 0;
sem_t hacker_queue, microsoft_queue;
bool is_captain = false;

int formasyon[2];
int bot_sayisi = 1;

int bot_hacker = 0;
int bot_microsoft = 0;
void *microsoft_thread(void *);
void *hacker_thread(void *);


int main(){
    sem_init(&test,0,0);
    sem_init(&disla,0,1);
    sem_init(&bilet,0,24);
    sem_init(&microsoft_queue,0,1);
    sem_init(&hacker_queue,0,1);
    pthread_t Microsoft[N], Hacker[N];

    for (int i = 0; i< N ; i++) {
        pthread_create(&Microsoft[i], nullptr, microsoft_thread, nullptr);
    }
    for (int i = 0; i< N ; i++) {
        pthread_create(&Hacker[i], nullptr, hacker_thread, nullptr);
    }


    for (int i = 0; i< N ; i++) {
        pthread_join(Microsoft[i], nullptr);
    }
    for (int i = 0; i< N ; i++) {
        pthread_join(Hacker[i], nullptr);
    }

    sem_destroy(&disla);
    sem_destroy(&bilet);
    sem_destroy(&microsoft_queue);
    sem_destroy(&hacker_queue);
    sem_destroy(&test);
}


void rowBoat(std::string grup){
    if (formasyon[0] == 0 and formasyon[1] == 0){
        printf("Bot kalkamaz");
    }
    if (formasyon[0] == 4 and formasyon[1] == 0){
        printf("Microsoft grubu %d. bot ile kalkış gerçekleştirdi (%d,%d)\n",bot_sayisi,formasyon[0],formasyon[1]);
        bot_sayisi += 1;
        return;
    }
    if (formasyon[0] == 0 and formasyon[1] == 4){
        printf("Hacker gurubu %d. bot ile kalkış gerçekliştirdi(%d,%d)\n",bot_sayisi,formasyon[0],formasyon[1]);
        bot_sayisi += 1;
        return;
    }
    if (formasyon[0] == 2 and formasyon[1] == 2){
        printf("Hacker ve microsoft çalışanları birlikte %d. bot ile kalkış gerçekleştirdi (%d,%d)\n",bot_sayisi,formasyon[0],formasyon[1]);
        bot_sayisi += 1;
        return;
    }

//    printf("%s grubu bot ile  kalkış gerçekleştirdi\n",grup.c_str());
    printf("Formasyon = %d, %d\n",formasyon[0],formasyon[1]);
    formasyon[0] = 0;
    formasyon[1] = 0;

}

void board(std::string kisi){

    if (kisi == "Hacker"){
        bot_hacker +=1;
//        printf("%d. Hacker bota bindi \n",bot_hacker);
        printf("Bir Hacker sıraya girdi\n");
    }
    if (bot_hacker == 4){
        rowBoat("Hacker");
        bot_hacker = 0;
    }
    if (kisi == "Microsoft"){
        bot_microsoft +=1;
//        printf("%d. Microsoft bota bindi \n",bot_microsoft);
        printf("Bir Microsoft çalışanı sıraya girdi\n");
    }
    if (bot_microsoft == 4){
        rowBoat("Microsoft");
        bot_microsoft = 0;
    }

}







void *microsoft_thread(void *){
    while (true) {
        sem_wait(&disla);

        microsoftlar += 1;
        if (microsoftlar == 4) {
            sem_post(&microsoft_queue);
            sem_post(&microsoft_queue);
            sem_post(&microsoft_queue);
            sem_post(&microsoft_queue);

            formasyon[0] = 4;
            formasyon[1] = 0;

            microsoftlar = 0;
            is_captain = true;
        } else if (hackers == 2 and microsoftlar == 2) {
            sem_post(&microsoft_queue);
            sem_post(&microsoft_queue);
            sem_post(&hacker_queue);
            sem_post(&hacker_queue);

            formasyon[0] = 2;
            formasyon[1] = 2;

            microsoftlar -= 2;
            hackers = 0;
            is_captain = true;
        } else {
            sem_post(&disla);
        }


        sem_wait(&microsoft_queue);
        board("Microsoft");
        sem_wait(&bilet);

        if (is_captain) {

            sem_post(&disla);
        }
        sleep(1);
    }

}

void *hacker_thread(void *){
    while (true) {
        sem_wait(&disla);

        hackers += 1;
        if (hackers == 4) {
            sem_post(&hacker_queue);
            sem_post(&hacker_queue);
            sem_post(&hacker_queue);
            sem_post(&hacker_queue);

            formasyon[0] = 0;
            formasyon[1] = 4;

            hackers = 0;
            is_captain = true;
        } else if (hackers == 2 and microsoftlar == 2) {
            sem_post(&microsoft_queue);
            sem_post(&microsoft_queue);
            sem_post(&hacker_queue);
            sem_post(&hacker_queue);

            formasyon[0] = 2;
            formasyon[1] = 2;

            hackers -= 2;
            microsoftlar = 0;
            is_captain = true;
        } else {
            sem_post(&disla);
        }

        sem_wait(&hacker_queue);
        board("Hacker");
        sem_wait(&bilet);
        if (is_captain) {
            sem_post(&disla);
        }
        sleep(1);
    }
}
