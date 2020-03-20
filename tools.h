#ifndef FIRST_TOOLS_H
#define FIRST_TOOLS_H

#include "cases.h"

int check_more_options(int argc, char* argv[]) {                    //Функция проверки наличия использования больше чем
    int rez = getopt(argc, argv, "cd");                             //одного ключа
    if (rez != -1) {
        fprintf(stderr, "%s\n", "Operation Error - multiple or wrong using of options");
        return 1;
    }
    return 0;
}

void choose_case_c(int argc, char* argv[]) {                        //Функция определения поведения программы
    switch (argc) {                                                 //А так же проверки количества аргументов
        case 2:first_case_c(); break;
        case 3:second_case_c(argv);break;
        case 4:third_case_c(argv); break;
    }
    if (argc > 4)
        fprintf(stderr, "%s\n", "There are more then 2 arguments, Error");
}

void choose_case_d(int argc, char* argv[]) {                        //Функция определения поведения программы
    switch (argc) {                                                 // А так же проверки количества аргументов
        case 2:first_case_d(); break;
        case 3:second_case_d(argv);break;
        case 4:third_case_d(argv); break;
    }
    if (argc>4)
        fprintf(stderr, "%s\n", "There are more then 2 arguments, Error");
}



#endif //FIRST_TOOLS_H
