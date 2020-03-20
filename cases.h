#ifndef FIRST_CASES_H
#define FIRST_CASES_H

#include <malloc.h>
#include "tools.h"

void encoder(char to_code, char* result);
char decoder(char* buff);

//Функция кодирующая из потока ввода в поток вывода
void first_case_c() {
    int times = 1;                                          //Переменная, нужная для понимания конечного объёма массива
    int pos = 0;                                            //Итератор
    char* mas = (char*)malloc(times*(100*(sizeof(char))));  //Объявление динамического массива
    char take_ch='0', put_char;

    while (take_ch != EOF) {
        take_ch = getchar();                                //Принимаем символ из потока ввода
        mas[pos] = take_ch;                                 //Присваиваем эл-ту массива символ
        ++pos;                                              //Сдвигаем итератор на +1

        if (pos == (times*100)) {                           //Проверяем не выйдем ли мы за границы массива                                                   //на следующем шаге
            ++times;                                        //Увеличиваем на 1 *размер* массива
            mas = (char*)realloc(mas, (times)*(100*(sizeof(char))));//Увеличиваем массив
            if (mas == NULL) {                                //Проверяем на то, что у нас получилось выделить память под
                fprintf(stderr, "%s\n", "Out of memory");     //Массив, в противном случае выход с ошибкой
                exit(-1);
            }
        }
    }                                                       //Повторяем, пока есть что брать из потока ввода
    printf("\n");
    for (int i = 0; i < pos-1; ++i) {                       //pos-1 потому что в mas[pos] находится EOF
        char buff[] = "0000";                               //Создаём буффер для интерпритации символа в 4ой сис исч
        put_char = mas[i];                                  //Берём символ для интерпритации
        encoder(put_char, buff);                        //*Кодируем исходный символ
        printf("%s", buff);                             //Печатаем закодированный символ
    }
    printf("%c", mas[pos-1]);                               //Печатаем EOF ?
    free(mas);
}
//Функция кодирующая из файла в поток вывода
void second_case_c(char* argv[]) {
    FILE* readfile;                                         //Создаём указатель на файл
    char put_char;                                          //Переменная для вывода в поток вывода
    if((readfile = fopen(argv[2], "r")) != 0) {             //Пытаемся открыть файл для чтения
        while (1) {
            char buff[] = "0000";                           //Создаём буффер для интерпритации символа
            put_char = fgetc(readfile);                     //Берём исходный символ
            if (put_char == EOF){ break;}
            encoder(put_char, &buff[0]);                    //Кодируем исходный символ
            printf("%s", buff);                             //Пишем *закодированный символ
        }
        printf("%c", EOF);                                  //В конец дописываем EOF
        fclose(readfile);                                   //Закрываем файл
    }
    else {
        fprintf(stderr, "%s\n", "Can't open source FILE");            //В случае, если не смогли открыть файл для
    }                                                                 //чтения, пишем об ошибке

}
//Функция кодирующая из файла в файл
void third_case_c(char *argv[]) {
    FILE* readfile, *writefile;                             //Создаём указатели на файлы
    char get_char;                                          //Переменная для кодирования
    if((readfile = fopen(argv[2], "r")) != 0) {             //Пытаемся открыть файл для чтения
        if ((writefile = fopen(argv[3], "w")) != 0) {       //Пытаемся открыть файл для записи
            while (1) {
                char buff[] = "0000";
                get_char = fgetc(readfile);
                if(get_char == EOF){ break;}
                encoder(get_char, &buff[0]);
                fputs(buff, writefile);
            }
            fputc(EOF, writefile);
            fclose(writefile);
        }
        else {
            fprintf(stderr, "%s\n", "Can't open distanation FILE");
        }
        fclose(readfile);
    }
    else {
        fprintf(stderr, "%s\n", "Can't open source FILE");
    }
}
//Функция декодирующая из потока ввода в поток вывода
void first_case_d() {
    int times = 1;
    int pos = 0;
    char* mas = (char*)malloc(times*(100*(sizeof(char))));
    char take_ch='0';

    while (take_ch != EOF) {
        take_ch = getchar();
        if (take_ch == 10) {
            //do nothing
        }
        else {
            mas[pos] = take_ch;
            ++pos;
        }
        if (pos == (times*100)) {                           //Проверяем не выйдем ли мы за границы массива                                                   //на следующем шаге
            ++times;                                        //Если выходим, увеличиваем на 1 *размер* массива
            mas = (char*)realloc(mas, (times)*(100*(sizeof(char))));//Увеличиваем массив для копирования
            if (mas == NULL) {                              //Проверяем, выделилась ли под него память
                fprintf(stderr, "%s\n", "Out of memory");   //И в случае, если нет, выходим с ошибкой
                exit(-1);
            }
        }

        if (((take_ch < 48) || (take_ch > 51)) && (take_ch != EOF)) { //Проверяем, правильные ли
            if (take_ch != 10) {
                fprintf(stderr, "%s%d\n", "Wrong symbol, position - ", pos);//символы нам дали для декодирования
                exit(-1);                                       //И в случае, если они неверны, выходим с ошибкой
            }
        }
    }

    if ((pos-1)%4 != 0) {                                   //Проверяем правильность длины строки
        fprintf(stderr, "%s\n", "Wrong input string");
        exit(-1);
    }
    char* origin_mas = mas;
    printf("\n");
    for (int i = 0; i < pos - 1; i = i + 4) {               //В случае, если все хорошо, выводим раскодированные символы
        printf("%c", decoder(&mas[i]));
    }

    printf("%c", EOF);                                      //Печатаем EOF ?
    free(origin_mas);
}
//Функция декодирующая из файла в поток вывода
void second_case_d(char *argv[])    {
    FILE* readfile;
    if((readfile = fopen(argv[2], "r")) != 0) {
        int times = 1;
        int pos = 0;
        char* mas = (char*)malloc(times*(100*(sizeof(char))));
        char take_ch='0';

        while (take_ch != EOF) {
            take_ch = fgetc(readfile);
            if (take_ch == 10) {
                //do nothing
            }
            else {
                mas[pos] = take_ch;
                ++pos;
            }
            if (pos == (times*100)) {                           //Проверяем не выйдем ли мы за границы массива                                                   //на следующем шаге
                ++times;                                        //Увеличиваем на 1 *размер* массива
                mas = (char*)realloc(mas, (times)*(100*(sizeof(char))));//Увеличиваем массив
                if (mas == NULL) {                                //Проверяем на то, что у нас получилось выделить память под
                    fprintf(stderr, "%s\n", "Out of memory");     //Массив, в противном случае выход с ошибкой
                    exit(-1);
                }
            }

            if (((take_ch < 48) || (take_ch > 51)) && (take_ch != EOF)) { //Проверяем, правильные ли символы нам дали для
                if (take_ch != 10) {
                    fprintf(stderr, "%s%d\n", "Wrong symbol, position - ", pos);//декодирования
                    exit(-1);                                       //И в случае, если они неверны, выходим с ошибкой
                }
            }
        }

        if ((pos-1)%4 != 0) {                                   //Проверяем правильность длины строки
            fprintf(stderr, "%s\n", "Wrong input string");
            exit(-1);
        }
        char* origin_mas = mas;
        printf("\n");
        for (int i = 0; i < pos - 1; i = i + 4) {               //В случае, если все хорошо, выводим раскодированные символы
            printf("%c", decoder(&mas[i]));
        }

        printf("%c", EOF);                                      //Печатаем EOF ?
        fclose(readfile);
        free(origin_mas);
    }
    else {
        fprintf(stderr, "%s\n", "Can't open source FILE");
    }

}
//Функция декодирующая из файла в файл
void third_case_d(char* argv[]) {
    FILE* readfile, *writefile;
    if((readfile = fopen(argv[2], "r")) != 0)   {
        if ((writefile = fopen(argv[3], "w")) != 0) {

            int times = 1;
            int pos = 0;
            char* mas = (char*)malloc(times*(100*(sizeof(char))));
            char take_ch='0';

            while (take_ch != EOF)   {
                take_ch = fgetc(readfile);
                if (take_ch == 10) {
                    //do nothing
                }
                else {
                    mas[pos] = take_ch;
                    ++pos;
                }
                if (pos == (times*100)) {                           //Проверяем не выйдем ли мы за границы массива                                                   //на следующем шаге
                    ++times;                                        //Увеличиваем на 1 *размер* массива
                    mas = (char*)realloc(mas, (times)*(100*(sizeof(char))));//Увеличиваем массив
                    if (mas == NULL) {                                //Проверяем на то, что у нас получилось выделить память под
                        fprintf(stderr, "%s\n", "Out of memory");     //Массив, в противном случае выход с ошибкой
                        exit(-1);
                    }
                }

                if (((take_ch < 48) || (take_ch > 51)) && (take_ch != EOF)) { //Проверяем, правильные ли символы нам дали для
                    if (take_ch !=10) {
                        fprintf(stderr, "%s%d\n", "Wrong symbol, position - ", pos);//декодирования
                        exit(-1);                                       //И в случае, если они неверны, выходим с ошибкой
                    }
                }
            }

            if ((pos-1)%4 != 0) {                                   //Проверяем правильность длины строки
                fprintf(stderr, "%s\n", "Wrong input string");
                exit(-1);
            }
            char* origin_mas = mas;
            printf("\n");
            for (int i = 0; i < pos - 1; i = i + 4) {               //После всех проверок печатаем в файл раскодированные файлы
                putc(decoder(&mas[i]), writefile);
            }

            putc(EOF, writefile);                                   //И вгоняем EOF
            fclose(writefile);
            free(origin_mas);
        }
        else {
            fprintf(stderr, "%s\n", "Can't open distanation FILE");
        }
        fclose(readfile);
    }
    else {
        fprintf(stderr, "%s\n", "Can't open source FILE");
    }
}

void encoder(char to_code, char *result)    {
    char parse;
    to_code = to_code & 255;
    parse = (to_code&192)>>6;
    *result = parse + 48;                                           //В значение, на которое ссылаемся, записываем
    *result++;                                                      //Ссылаемся на *след область памяти

    parse= (to_code&48)>>4;
    *result = parse + 48;
    *result++;

    parse = (to_code&12)>>2;
    *result = parse + 48;
    *result++;

    parse = (to_code & 3);
    *result = parse + 48;

}
char decoder(char* buff)    {
    char parse = 0;
    parse = parse | (buff[0]-48);
    buff++;

    parse = parse<<2;
    parse = parse | (buff[0]-48);
    buff++;

    parse = parse<<2;
    parse = parse | (buff[0]-48);
    buff++;

    parse = parse<<2;
    parse = parse | (buff[0]-48);

    return parse;
}

#endif //FIRST_CASES_H