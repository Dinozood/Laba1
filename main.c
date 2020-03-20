#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char* argv[])
{
    opterr = 0;
    int rez = getopt(argc, argv, "cd");             //Принимаем ключи

    switch (rez) {
        case 'c':
            if(check_more_options(argc, argv))      //Проверяем ключи
                exit(-1);                   //В случае, если происходит ошибка, завершаем программу -1
            choose_case_c(argc, argv);              //При успешной проверке, определяем дальнейште действия
            break;
        case 'd':
            if (check_more_options(argc, argv))
                exit(-1);
            choose_case_d(argc, argv);
            break;
        case -1:                                    //Если изначально нет ключей, говорим что нет ключей
            fprintf(stderr, "%s\n", "There is no key, Error");
            exit(-1);
        case '?':                                   //Если ключ не известен, говорим, что ошибка
            fprintf(stderr, "%s\n", "There is wrong key, Error");
            exit(-1);
    }
    return 0;
}