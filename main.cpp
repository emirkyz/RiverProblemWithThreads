//
// Created by emir on 5/6/23.
//
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <random>
#define N 4


sem_t disla, kalkis;
int hackers = 0;
int microsoftlar = 0;
sem_t siradaki_hacker, siradaki_microsoft;
bool bot_kalkti = false;

int formasyon[2];
int bot_sayisi = 1;

int bot_hacker = 0;
int bot_microsoft = 0;
void *microsoft_thread(void *);
void *hacker_thread(void *);

std::random_device rd;     // Only used once to initialise (seed) engine
std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(1,6); // Guaranteed unbiased

int main(){

    sem_init(&kalkis, 0, 1);
    sem_init(&disla,0,1);
//    sem_init(&bilet,0,24);
    sem_init(&siradaki_microsoft, 0, 1);
    sem_init(&siradaki_hacker, 0, 1);
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
//    sem_destroy(&bilet);
    sem_destroy(&siradaki_microsoft);
    sem_destroy(&siradaki_hacker);
    sem_destroy(&kalkis);
}


void rowBoat(std::string grup){
    sem_wait(&kalkis);
    if (formasyon[0] == 0 and formasyon[1] == 0){
        return;
//        printf("Bot kalkamaz\n");
    }


    if (formasyon[0] == 4 and formasyon[1] == 0){
        printf("Microsoft grubu %d. bot ile kalkış gerçekleştirdi (%d,%d)\n",bot_sayisi,formasyon[0],formasyon[1]);
        bot_sayisi += 1;
        sem_post(&kalkis);

    }
    else if (formasyon[0] == 0 and formasyon[1] == 4){
        printf("Hacker gurubu %d. bot ile kalkış gerçekliştirdi(%d,%d)\n",bot_sayisi,formasyon[0],formasyon[1]);
        bot_sayisi += 1;
        sem_post(&kalkis);

    }
    else if (formasyon[0] == 2 and formasyon[1] == 2){
        printf("Hacker ve microsoft çalışanları birlikte %d. bot ile kalkış gerçekleştirdi (%d,%d)\n",bot_sayisi,formasyon[0],formasyon[1]);
        bot_sayisi += 1;
        sem_post(&kalkis);

    }
    else {
        printf("else içi");
    }

//    printf("%s grubu bot ile  kalkış gerçekleştirdi\n",grup.c_str());
//    printf("Formasyon = %d, %d\n",formasyon[0],formasyon[1]);

}

void board(std::string kisi){

    if (kisi == "Hacker"){
        bot_hacker +=1;
//        printf("%d. Hacker bota bindi \n",bot_hacker);
        printf("%d. bot için Bir Hacker sıraya girdi\n",bot_sayisi);
    }
    if (bot_hacker == 4){
        bot_hacker -= 4;
        rowBoat("Hacker");
//        bot_hacker = 0;
    }
    if (kisi == "Microsoft"){
        bot_microsoft +=1;
//        printf("%d. Microsoft bota bindi \n",bot_microsoft);
        printf("%d. bot için Bir Microsoft çalışanı sıraya girdi\n", bot_sayisi);
    }
    if (bot_microsoft == 4){
        bot_microsoft -= 4 ;
        rowBoat("Microsoft");
//        bot_microsoft = 0;
    }
    if (bot_microsoft == 2 and bot_hacker == 2){
        rowBoat("TEST");
    }
}







void *microsoft_thread(void *){
    while (true) {

        sem_wait(&disla);

        microsoftlar += 1;
        if (microsoftlar == 4) {
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_microsoft);

            formasyon[0] = 4;
            formasyon[1] = 0;

            microsoftlar -= 4;
            bot_kalkti = true;
        } else if (hackers == 2 and microsoftlar == 2) {
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_hacker);
            sem_post(&siradaki_hacker);

            formasyon[0] = 2;
            formasyon[1] = 2;

            microsoftlar -= 2;
            hackers -=2;
            bot_kalkti = true;
        } else {
            sem_post(&disla);
        }


        sem_wait(&siradaki_microsoft);

        board("Microsoft");


        if (bot_kalkti) {

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
            sem_post(&siradaki_hacker);
            sem_post(&siradaki_hacker);
            sem_post(&siradaki_hacker);
            sem_post(&siradaki_hacker);

            formasyon[0] = 0;
            formasyon[1] = 4;

            hackers -= 4;
            bot_kalkti = true;
        } else if (hackers == 2 and microsoftlar == 2) {
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_microsoft);
            sem_post(&siradaki_hacker);
            sem_post(&siradaki_hacker);

            formasyon[0] = 2;
            formasyon[1] = 2;

            hackers -= 2;
            microsoftlar -=2;
            bot_kalkti = true;
        } else {
            sem_post(&disla);
        }

        sem_wait(&siradaki_hacker);
        board("Hacker");

        if (bot_kalkti) {
            sem_post(&disla);
        }
        sleep(1);
    }

}
