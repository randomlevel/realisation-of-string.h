#include "s21_string.h"

int s21_sprintf(char* str, const char* format, ...) {
    char* pFormat = (char*)format;
    int check = 0;
    va_list ap;
    va_start(ap, format);
    while (*pFormat) {
        if (*pFormat == '%') {
            token tok = {{0, 0, 0, 0, 0}, -1, -1, '$', '$'};
            char* pTrash = pFormat + 1;
            pFormat = initToken(pFormat, &tok, ap);
            if (tok.spec == '%') {
                str[check++] = '%';
            } else if (tok.spec == '$') {
                pFormat = pTrash;
                str[check++] = *pFormat++;
            } else {
                str = initVariable(str, tok, ap, &check);
            }
        } else {
            str[check++] = *pFormat++;
        }
    }
    va_end(ap);
    return check;
}
char* initVariable(char* str, token tok, va_list ap, int* check) {
    char DATA[999] = {0};
    char* buf = DATA;
    if (tok.spec == 'c') work_c(str, buf, tok, ap, check);
    if (tok.spec == 's') work_s(str, buf, tok, ap, check);
    if (tok.spec == 'd' || tok.spec == 'i') {
        if (tok.length != 'l')
            work_di_int(str, buf, tok, ap, check);
        else
            work_di_long(str, buf, tok, ap, check);
    }
    if (tok.spec == 'o') work_o(str, buf, tok, ap, check);
    if (tok.spec == 'x' || tok.spec == 'X') work_xX(str, buf, tok, ap, check);
    if (tok.spec == 'u') work_u(str, buf, tok, ap, check);
    if (tok.spec == 'p') work_p(str, buf, tok, ap, check);
    if (tok.spec == 'n') work_n(ap, check);
    if (tok.spec == 'f') work_f(str, buf, tok, ap, check);
    if (tok.spec == 'e' || tok.spec == 'E') work_e(str, buf, tok, ap, check);
    if (tok.spec == 'g' || tok.spec == 'G') {
        if (tok.flag[3] == 0)
            work_g(str, buf, tok, ap, check);
        else
            work_f(str, buf, tok, ap, check);
    }
    return str;
}
void work_c(char* str, char* buf, token tok, va_list ap, int* check) {
    if (tok.width == -1) tok.width = 1;
    if (tok.flag[0] == 1) {
        for (int i = tok.width - 1; i > 0; i--) *(buf + i) = ' ';
        buf[0] = va_arg(ap, int);
    } else {
        for (int i = 0; i < tok.width; i++) *(buf + i) = ' ';
        buf[tok.width - 1] = va_arg(ap, int);
    }
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_s(char* str, char* buf, token tok, va_list ap, int* check) {
    if (tok.width == -1) tok.width = 1;
    char past[999] = {0};
    s21_strcpy(past, va_arg(ap, char*));
    if (tok.accuracy > tok.width) tok.width = tok.accuracy;
    if (tok.accuracy < 0 && (int)s21_strlen(past) > tok.width)
        tok.width = (int)s21_strlen(past);
    if (tok.accuracy >= 0) past[tok.accuracy] = '\0';
    if (tok.flag[0] == 1) {
        for (int i = tok.width - 1; i >= 0; i--) {
            buf[i] = ' ';
            buf[tok.width] = '\0';
        }
        for (int k = 0; k < (int)s21_strlen(past); k++)
            *(buf + k) = *(past + k);
    } else {
        int z = 0;
        for (int i = 0; i < tok.width; i++) {
            buf[i] = ' ';
            buf[tok.width] = '\0';
        }
        for (int n = (int)s21_strlen(past); n > 0; n--) {
            buf[tok.width - n] = past[z];
            z++;
        }
        if ((int)s21_strlen(past) == 0 && tok.width == 1) buf[0] = '\0';
    }
    if (tok.accuracy == 0) {
        int i = 0;
        while (buf[i] != '\0') {
            buf[i] = ' ';
            i++;
        }
    }
    s21_strcat(str, buf);
    *check += s21_strlen(buf);
}
void work_di_int(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0;
    int prev = 0;
    if (tok.accuracy != -1) prev++;
    char ch = ' ';
    int num = va_arg(ap, int);
    if (num < 0 || tok.flag[1] == 1 || tok.flag[2] == 1) znak++;
    s21_zero_int(bPast, tok, &num);
    s21_accuracy(tok, bPast, past);
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    s21_znak_int(buf, past, tok, &prev, &znak, &num);
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_di_long(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0;
    int prev = 0;
    if (tok.accuracy != -1) prev++;
    char ch = ' ';
    long num = va_arg(ap, long);
    if (num < 0 || tok.flag[1] == 1 || tok.flag[2] == 1) znak++;
    s21_zero_long(bPast, tok, &num);
    s21_accuracy(tok, bPast, past);
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    s21_znak_long(buf, past, tok, &prev, &znak, &num);
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_o(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0;
    int prev = 0;
    if (tok.accuracy != -1) prev++;
    char ch = ' ';
    long num = s21_eight_sys(va_arg(ap, long));
    s21_zero_long(bPast, tok, &num);
    s21_accuracy(tok, bPast, past);
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    s21_znak_long(buf, past, tok, &prev, &znak, &num);
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_xX(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0;
    int prev = 0;
    if (tok.accuracy != -1) prev++;
    char ch = ' ';
    long num = va_arg(ap, long);
    s21_hex_system(num, bPast, tok);
    s21_zero_long(bPast, tok, &num);
    s21_accuracy(tok, bPast, past);
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    s21_znak_long(buf, past, tok, &prev, &znak, &num);
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_u(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0;
    int prev = 0;
    if (tok.accuracy != -1) prev++;
    char ch = ' ';
    long num = va_arg(ap, long);
    s21_zero_long(bPast, tok, &num);
    s21_accuracy(tok, bPast, past);
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    s21_znak_long(buf, past, tok, &prev, &znak, &num);
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_p(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0;
    int prev = 0;
    if (tok.accuracy != -1) prev++;
    char ch = ' ';
    long num = va_arg(ap, long);
    s21_hex_system(num, bPast, tok);
    s21_zero_long(bPast, tok, &num);
    s21_accuracy(tok, bPast, past);
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    s21_znak_long(buf, past, tok, &prev, &znak, &num);
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_n(va_list ap, const int* check) {
    int* temp = va_arg(ap, int*);
    *temp = *check;
}
void work_f(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0}, bPast[999] = {0};
    int znak = 0, dec = 0, prev = 0;
    char* ptr = NULL;
    char ch = ' ';
    double num = va_arg(ap, double);
    if (tok.accuracy == -1) tok.accuracy = 6;
    if (tok.spec == 'g' && tok.flag[3] == 1) tok.accuracy -= 2;
    s21_accuracy_float(tok, ptr, &znak, &dec, past, bPast, &num);
    if (tok.flag[1] == 1 || tok.flag[2] == 1) znak = 1;
    if (tok.flag[4] == 1) ch = '0';
    char zn[1];
    gcvt(num, 1, zn);
    if (zn[0] == '-') znak = 1;
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    if (znak == 1) {
        if (tok.flag[0] == 1 || tok.flag[4] == 1) {
            if (zn[0] == '-') buf[0] = '-';
            if (tok.flag[1] == 1 && zn[0] != '-') buf[0] = '+';
            if (tok.flag[2] == 1 && zn[0] != '-') buf[0] = ' ';
        } else {
            if (zn[0] == '-')
                buf[tok.width - (int)s21_strlen(past) - znak] = '-';
            if (tok.flag[1] == 1 && zn[0] != '-') {
                buf[tok.width - (int)s21_strlen(past) - znak] = '+';
            }
        }
    }
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void work_e(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0};
    if (tok.accuracy == -1) tok.accuracy = 6;
    int znak = 0;
    char* p = buf;
    char ch = ' ';
    if (tok.flag[4] == 1 && tok.flag[0] == 0) ch = '0';
    long double number = va_arg(ap, double);
    int test = tok.accuracy;
    int test_temp = test;
    if (work_sign(&number) && tok.flag[4] != 1) {
        *buf++ = '-';
        number = -number;
    }
    if (work_sign(&number) == 1 || tok.flag[1] == 1 || tok.flag[2] == 1)
        znak = 1;
    int dec, sign;
    char* c = ecvt(number, test + 1, &dec, &sign);
    test = 1;
    while (*c) {
        *buf++ = *c++;
        if ((test == 1 && test_temp != 0) || tok.flag[3] == 1) {
            *buf++ = '.';
            tok.flag[3] = 0;
        }
        test++;
    }
    work_e_degree(buf, test_temp, &number, dec, tok);
    znak_float(tok, p, past, &znak, &ch, &number);
    s21_strcat(str, past);
    *check += (int)s21_strlen(past);
}
void work_g(char* str, char* buf, token tok, va_list ap, int* check) {
    char past[999] = {0};
    int znak = 0, prev = 0;
    char ch = ' ';
    double numun;
    double num = va_arg(ap, double);
    if (tok.accuracy == -1) tok.accuracy = 6;
    if (tok.flag[3] == 1) tok.accuracy = 5;
    numun = num;
    if (num < 0) numun *= -1;
    gcvt(numun, tok.accuracy, past);
    if (tok.flag[1] == 1 || tok.flag[2] == 1) znak = 1;
    if (tok.flag[4] == 1) ch = '0';
    char zn[1];
    gcvt(num, 1, zn);
    if (zn[0] == '-') znak = 1;
    s21_flag0_0(buf, past, &tok, &prev, &znak, &ch);
    s21_flag0_1(buf, past, &tok, &znak, &ch);
    if (znak == 1) {
        if (tok.flag[0] == 1 || tok.flag[4] == 1) {
            if (zn[0] == '-') buf[0] = '-';
            if (tok.flag[1] == 1 && zn[0] != '-') buf[0] = '+';
            if (tok.flag[2] == 1 && zn[0] != '-') buf[0] = ' ';
        } else {
            if (zn[0] == '-')
                buf[tok.width - (int)s21_strlen(past) - znak] = '-';
            if (tok.flag[1] == 1 && zn[0] != '-') {
                buf[tok.width - (int)s21_strlen(past) - znak] = '+';
            }
        }
    }
    s21_strcat(str, buf);
    *check += (int)s21_strlen(buf);
}
void s21_accuracy(token tok, char* bPast, char* past) {
    if (tok.accuracy <= (int)s21_strlen(bPast)) {
        tok.accuracy = (int)s21_strlen(bPast);
        s21_strcpy(past, bPast);
    }
    if (tok.accuracy > (int)s21_strlen(bPast)) {
        for (int i = 0; i < tok.accuracy - (int)s21_strlen(bPast); i++)
            past[i] = '0';
        past[tok.accuracy - (int)s21_strlen(bPast)] = '\0';
        s21_strcat(past, bPast);
    }
}
void s21_accuracy_float(token tok, char* ptr, int* znak, int* dec, char* past,
                        char* bPast, double* num) {
    if (tok.accuracy != 0) {
        ptr = fcvt(*num, tok.accuracy, dec, znak);
        if (*znak != 0) *znak = 1;
        if (*dec > 0) {
            for (int i = 0; i < *dec; i++) {
                past[i] = ptr[i];
                past[i + 1] = '.';
                past[i + 2] = '\0';
            }
            for (int i = 0; i < tok.accuracy; i++) {
                bPast[i] = ptr[i + *dec];
                bPast[i + 1] = '\0';
            }
            s21_strcat(past, bPast);
        }
        if (*dec <= 0) {
            past[0] = '0';
            past[1] = '.';
            past[2] = '\0';
            int a = 0;
            while (a < (-*dec) && a < tok.accuracy) bPast[a++] = '0';
            while (a < tok.accuracy) bPast[a++] = *ptr++;
            s21_strcat(past, bPast);
        }
    }
    if (tok.accuracy == 0) {
        fcvt(*num, tok.accuracy + 1, dec, znak);
        if (*znak != 0) *znak = 1;
        double temp = *num - (int)*num;
        if ((int)*num % 2 != 0) {
            if (temp >= 0.5) *num += 1;
            if (temp <= (-0.5)) *num -= 1;
        }
        s21_itoa_un_long((long)*num, past, tok);
        if (tok.flag[3] == 1) {
            char znd[2] = ".";
            s21_strcat(past, znd);
        }
    }
}
void s21_zero_int(char* bPast, token tok, int* num) {
    s21_itoa_un_int(*num, bPast, tok);
    if (tok.flag[3] == 1) {
        char rev[999] = {0};
        rev[0] = '0';
        rev[1] = '\0';
        s21_strcat(rev, bPast);
        s21_strcpy(bPast, rev);
    }
}
void s21_zero_long(char* bPast, token tok, long* num) {
    if (*bPast == 0) s21_itoa_un_long(*num, bPast, tok);
    if (tok.flag[3] == 1 && tok.spec == 'o') {
        char rev[999] = {0};
        rev[0] = '0';
        rev[1] = '\0';
        s21_strcat(rev, bPast);
        s21_strcpy(bPast, rev);
    }
}
void s21_znak_int(char* buf, char* past, token tok, const int* prev,
                  const int* znak, const int* num) {
    if (*znak == 1) {
        if (*num < 0) {
            if ((tok.flag[4] == 1 && *prev == 0) || tok.flag[0] == 1)
                buf[0] = '-';
            if ((tok.flag[4] == 0 || *prev == 1) && tok.flag[0] == 0)
                buf[tok.width - (int)s21_strlen(past) - *znak] = '-';
        }
        if (*num >= 0) {
            if ((tok.flag[4] == 1 && *prev == 0) || tok.flag[0] == 1) {
                if (tok.flag[1] == 1) buf[0] = '+';
                if (tok.flag[2] == 1) buf[0] = ' ';
            } else {
                if (tok.flag[1] == 1)
                    buf[tok.width - (int)s21_strlen(past) - *znak] = '+';
                if (tok.flag[2] == 1)
                    buf[tok.width - (int)s21_strlen(past) - *znak] = ' ';
            }
        }
    }
}
void s21_znak_long(char* buf, char* past, token tok, const int* prev,
                   const int* znak, const long* num) {
    if (*znak == 1) {
        if (*num < 0) {
            if ((tok.flag[4] == 1 && *prev == 0) || tok.flag[0] == 1)
                buf[0] = '-';
            if ((tok.flag[4] == 0 || *prev == 1) && tok.flag[0] == 0)
                buf[tok.width - (int)s21_strlen(past) - *znak] = '-';
        }
        if (*num >= 0) {
            if ((tok.flag[4] == 1 && *prev == 0) || tok.flag[0] == 1) {
                if (tok.flag[1] == 1) buf[0] = '+';
                if (tok.flag[2] == 1) buf[0] = ' ';
            } else {
                if (tok.flag[1] == 1)
                    buf[tok.width - (int)s21_strlen(past) - *znak] = '+';
                if (tok.flag[2] == 1)
                    buf[tok.width - (int)s21_strlen(past) - *znak] = ' ';
            }
        }
    }
    if (tok.spec == 'x' || tok.spec == 'X' || tok.spec == 'p') {
        if (tok.flag[3] == 1 || tok.spec == 'p') {
            if (tok.flag[0] == 0 && tok.flag[4] == 0) {
                int kol = 2;
                buf[tok.width - (int)s21_strlen(past) - kol] = '0';
                kol--;
                if (tok.spec == 'x' || tok.spec == 'p')
                    buf[tok.width - (int)s21_strlen(past) - kol] = 'x';
                if (tok.spec == 'X')
                    buf[tok.width - (int)s21_strlen(past) - kol] = 'X';
            } else {
                buf[0] = '0';
                if (tok.spec == 'x' || tok.spec == 'p') buf[1] = 'x';
                if (tok.spec == 'X') buf[1] = 'X';
            }
        }
    }
}
void s21_flag0_1(char* buf, char* past, token* tok, const int* znak,
                 const char* ch) {
    if (tok->flag[0] == 1) {
        int kol = 0;
        if (tok->spec == 'x' || tok->spec == 'X' || tok->spec == 'p') kol += 2;
        if (tok->width == -1) tok->width = (int)s21_strlen(past) + *znak + kol;
        if (tok->width <= tok->accuracy)
            tok->width = tok->accuracy + *znak + kol;
        for (int i = 0; i < tok->width; i++) buf[i] = *ch;
        buf[tok->width] = '\0';
        for (int i = 0 + *znak + kol; i < (int)s21_strlen(past) + *znak + kol;
             i++)
            buf[i] = past[i - *znak - kol];
    }
}
void s21_flag0_0(char* buf, char* past, token* tok, const int* prev,
                 const int* znak, char* ch) {
    int kol = 0;
    if (tok->spec == 'x' || tok->spec == 'X' || tok->spec == 'p') kol += 2;
    if (tok->flag[0] == 0) {
        if (tok->flag[4] == 1) *ch = '0';
        if (tok->width >= tok->accuracy) {
            if (tok->width == -1 ||
                tok->width < (int)s21_strlen(past) + *znak + kol)
                tok->width = (int)s21_strlen(past) + *znak + kol;
            if (*prev == 1) *ch = ' ';
            if (tok->width == tok->accuracy && *znak == 1) tok->width++;
            for (int i = 0; i < tok->width - (int)s21_strlen(past); i++)
                buf[i] = *ch;
            buf[tok->width - (int)s21_strlen(past)] = '\0';
            s21_strcat(buf, past);
        }
        if (tok->width < tok->accuracy) {
            tok->width = (int)s21_strlen(past) + *znak + kol;
            if (*znak == 1) {
                buf[0] = *ch;
                buf[1] = '\0';
                s21_strcat(buf, past);
            } else if (kol == 2) {
                buf[0] = *ch;
                buf[1] = *ch;
                buf[2] = '\0';
                s21_strcat(buf, past);
            } else {
                s21_strcpy(buf, past);
            }
        }
    }
}
void s21_itoa_un_int(int errnum, char* ptr, token tok) {
    if (errnum != 0) {
        int temp;
        if (errnum < 0) {
            errnum *= (-1);
        }
        for (temp = errnum; temp > 0; temp /= 10, ptr++) *ptr = '\0';
        for (temp = errnum; temp > 0; temp /= 10) *--ptr = temp % 10 + '0';
    } else if (tok.accuracy != 0) {
        ptr[0] = '0';
        ptr[1] = '\0';
    } else {
        ptr[0] = '\0';
    }
}
void s21_itoa_un_long(long errnum, char* ptr, token tok) {
    if (errnum != 0) {
        long temp;
        if (errnum < 0) {
            errnum *= (-1);
        }
        for (temp = errnum; temp > 0; temp /= 10, ptr++) *ptr = '\0';
        for (temp = errnum; temp > 0; temp /= 10) *--ptr = temp % 10 + '0';
    } else if (tok.accuracy != 0 || tok.spec == 'f') {
        ptr[0] = '0';
        ptr[1] = '\0';
    } else {
        ptr[0] = '\0';
    }
}
long s21_eight_sys(long a) {
    long b = 0, c = 1;
    while (a) {
        b = b + (a % 8) * c;
        a /= 8;
        c *= 10;
    }
    return b;
}
void s21_hex_system(long number, char* buf, token tok) {
    long counter, i;
    char hex[32];
    counter = 0;
    while (number) {
        switch (number % 16) {
            case 10:
                if (tok.spec == 'x' || tok.spec == 'p') hex[counter] = 'a';
                if (tok.spec == 'X') hex[counter] = 'A';
                break;
            case 11:
                if (tok.spec == 'x' || tok.spec == 'p') hex[counter] = 'b';
                if (tok.spec == 'X') hex[counter] = 'B';
                break;
            case 12:
                if (tok.spec == 'x' || tok.spec == 'p') hex[counter] = 'c';
                if (tok.spec == 'X') hex[counter] = 'C';
                break;
            case 13:
                if (tok.spec == 'x' || tok.spec == 'p') hex[counter] = 'd';
                if (tok.spec == 'X') hex[counter] = 'D';

                break;
            case 14:
                if (tok.spec == 'x' || tok.spec == 'p') hex[counter] = 'e';
                if (tok.spec == 'X') hex[counter] = 'E';
                break;
            case 15:
                if (tok.spec == 'x' || tok.spec == 'p') hex[counter] = 'f';
                if (tok.spec == 'X') hex[counter] = 'F';
                break;
            default:
                hex[counter] = (number % 16) + 0x30;
        }
        number = number / 16;
        counter++;
    }
    int j = 0;
    for (i = (counter - 1); i >= 0; i--) {
        buf[j] = hex[i];
        j++;
    }
}
void work_e_degree(char* buf, int test_temp, const long double* number, int dec,
                   token tok) {
    if (tok.spec == 'e' || tok.spec == 'g')
        *buf++ = 'e';
    else
        *buf++ = 'E';
    int counter = 0;
    long double clone = *number;
    if (clone < 0.0) clone = -(clone);
    if ((int)clone == 0 && (int)(clone * 10) > 5 && test_temp < 3) {
        *buf++ = '+';
        counter = dec - 1;
    } else {
        if (clone < 1 && clone > 0) {
            *buf++ = '-';
            dec = -dec;
            counter = dec + 1;
        } else if (clone > 0) {
            *buf++ = '+';
            counter = dec - 1;
        } else {
            *buf++ = '+';
            counter = 0;
        }
    }
    if (counter > 9) {
        int temp_counter = counter;
        int i = 0;
        while (temp_counter) {
            i++;
            temp_counter /= 10;
            buf++;
        }
        for (int j = i; j > 0; j--) {
            *--buf = counter % 10 + '0';
            counter /= 10;
        }
    } else {
        *buf++ = '0';
        *buf++ = counter % 10 + '0';
    }
}
int work_sign(long double* number) {
    int minus_plus = 0;
    if ((int)*number <= 0) {
        char q[999999] = {0};
        gcvt(*number, 1, q);
        if (q[0] == '-') {
            minus_plus = 1;
        }
    }
    return minus_plus;
}
void znak_float(token tok, char* p, char* past, const int* znak, const char* ch,
                long double* number) {
    if (tok.width < (int)s21_strlen(p) + *znak)
        tok.width = (int)s21_strlen(p) + *znak;
    if (tok.width >= (int)s21_strlen(p) + *znak) {
        if (tok.flag[0] == 0) {
            for (int i = 0; i < tok.width - (int)s21_strlen(p); i++)
                past[i] = *ch;
            past[tok.width - (int)s21_strlen(p)] = '\0';
            s21_strcat(past, p);
            if (tok.flag[4] == 0) {
                if (work_sign(number))
                    past[tok.width - (int)s21_strlen(p) - 1] = '-';
                if (work_sign(number) == 0 && tok.flag[1] == 1)
                    past[tok.width - (int)s21_strlen(p) - 1] = '+';
                if (work_sign(number) == 0 && tok.flag[2] == 1)
                    past[tok.width - (int)s21_strlen(p) - 1] = ' ';
            }
            if (tok.flag[4] == 1) {
                if (work_sign(number)) past[0] = '-';
                if (work_sign(number) == 0 && tok.flag[1] == 1) past[0] = '+';
                if (work_sign(number) == 0 && tok.flag[2] == 1) past[0] = ' ';
            }
        } else {
            for (int i = 0 + *znak; i < tok.width; i++) past[i] = p[i];
            past[tok.width] = '\0';
            if (work_sign(number)) past[0] = '-';
            if (work_sign(number) == 0 && tok.flag[1] == 1) past[0] = '+';
            if (work_sign(number) == 0 && tok.flag[2] == 1) past[0] = ' ';
        }
    }
}
