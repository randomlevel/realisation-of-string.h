#include "s21_string.h"

int s21_sscanf(char* str, const char* format, ...) {
    char* pFormat = (char*)format;
    int check = 0, ptr = 0, flag = 0;
    va_list ap;
    va_start(ap, format);
    while (*pFormat) {
        if (*pFormat == '%') {
            token tok = {{0, 0, 0, 0, 0}, -1, -1, '$', '$'};
            pFormat = initToken(pFormat, &tok, ap);
            if (tok.spec == '%') flag = 1;
            initVariable_s(str, tok, ap, &check, &ptr, &flag);
        } else if (*pFormat != ' ') {
            flag = 1;
            pFormat++;
        } else {
            pFormat++;
        }
    }
    va_end(ap);
    return check;
}
char* initToken(char* pFormat, token* tok, va_list ap) {
    pFormat++;
    while (s21_strspn(pFormat, "-+ #0") > 0) {
        if (*pFormat == '-') tok->flag[0] = 1;
        if (*pFormat == '+') tok->flag[1] = 1;
        if (*pFormat == ' ') tok->flag[2] = 1;
        if (*pFormat == '#') tok->flag[3] = 1;
        if (*pFormat == '0') tok->flag[4] = 1;
        pFormat++;
    }
    if (s21_strspn(pFormat, "1234567890") > 0) {
        int buf = *pFormat - '0';
        pFormat++;
        while (s21_strspn(pFormat, "1234567890") > 0) {
            buf = buf * 10 + (*pFormat - '0');
            pFormat++;
        }
        tok->width = buf;
    }
    if (*pFormat == '*') {
        tok->width = va_arg(ap, int);
        pFormat++;
    }
    if (*pFormat == '.') {
        tok->accuracy = 0;
        pFormat++;
        if (s21_strspn(pFormat, "1234567890") > 0) {
            int buf = *pFormat - '0';
            pFormat++;
            while (s21_strspn(pFormat, "1234567890") > 0) {
                buf = buf * 10 + (*pFormat - '0');
                pFormat++;
            }
            tok->accuracy = buf;
        } else if (*pFormat == '*') {
            tok->accuracy = va_arg(ap, int);
            pFormat++;
        }
    }
    if (s21_strspn(pFormat, "hlL") > 0) tok->length = *pFormat++;
    if (s21_strspn(pFormat, "seEdigGxXfoc%npu") > 0) tok->spec = *pFormat++;
    return pFormat;
}
void initVariable_s(char* str, token tok, va_list ap, int* check, int* ptr,
                    int* flag) {
    char DATA[999] = {0};
    char* buf = DATA;
    if (tok.spec == 'c') work_c_s(str, tok, ap, check, ptr, flag);
    if (tok.spec == 's') work_s_s(str, buf, tok, ap, check, ptr, flag);
    if (tok.spec == 'd') work_d_s(str, tok, ap, check, ptr, flag);
    if (tok.spec == 'i') work_i_s(str, buf, tok, ap, check, ptr, flag);
    if (tok.spec == 'x' || tok.spec == 'X' || tok.spec == 'p')
        work_xX_s(str, buf, tok, ap, check, ptr, flag);
    if (tok.spec == 'o') work_o_s(str, tok, ap, check, ptr, flag);
    if (tok.spec == 'u') work_d_s(str, tok, ap, check, ptr, flag);
    if (tok.spec == 'n') work_n_s(ap, ptr, flag);
    if (tok.spec == 'f' || tok.spec == 'e' || tok.spec == 'E' ||
        tok.spec == 'g' || tok.spec == 'G')
        work_f_s(str, buf, tok, ap, check, ptr, flag);
}
void work_c_s(const char* str, token tok, va_list ap, int* check,
              int* ptr, int* flag) {
    if (*flag == 0) {
        if (str[0] != '\0') {
            if (tok.width == -1) tok.width = 1;
            *va_arg(ap, char*) = str[*ptr];
            *ptr += tok.width;
            *check += 1;
        } else {
            *flag = 1;
            *check = -1;
        }
    }
}
void work_s_s(char* str, char* buf, token tok, va_list ap, int* check, int* ptr,
              int* flag) {
    if (*flag == 0) {
        if (tok.width == -1) tok.width = (int)s21_strlen(str);
        while (str[*ptr] == ' ') *ptr += 1;
        buf = va_arg(ap, char*);
        int i = 0;
        while (str[*ptr] != ' ' && i < tok.width && str[*ptr] != '\0') {
            buf[i++] = str[*ptr];
            *ptr += 1;
        }
        buf[i]='\0';
        *check += 1;
        if (str[*ptr] == '\0') *flag = 1;
    }
}
void work_d_s(char* str, token tok, va_list ap, int* check, int* ptr,
              int* flag) {
    if (*flag == 0) {
        if (tok.width == -1) tok.width = (int)s21_strlen(str) - *ptr;
        int counter = 0, b = 1, a = 0, che = 0;
        long al = 0;
        while (str[*ptr] == ' ') *ptr += 1;
        if (str[*ptr] == '-' || str[*ptr] == '+') {
            if (str[*ptr] == '-') b = -1;
            *ptr += 1;
            counter++;
        }
        if (str[*ptr] == 0 && str[*ptr + 1] == 0 && tok.width > counter) {
            *ptr += 1;
            counter++;
        }
        while (s21_strspn(&str[*ptr], "1234567890") > 0 &&
               tok.width > counter) {
            if (tok.length == '$') a = a * 10 + (str[*ptr] - '0');
            if (tok.length == 'l') al = al * 10 + (str[*ptr] - '0');
            che++;
            *ptr += 1;
            counter++;
        }
        if (che > 0) {
            a *= b;
            al *= b;
            if (tok.length == '$') *va_arg(ap, int*) = a;
            if (tok.length == 'l') *va_arg(ap, long*) = al;
            *check += 1;
        } else {
            *flag = 1;
        }
    }
}
void work_i_s(char* str, char* buf, token tok, va_list ap, int* check, int* ptr,
              int* flag) {
    if (*flag == 0) {
        if (tok.width == -1) tok.width = (int)s21_strlen(str) - *ptr;
        int che = 0, counter = 0, be = 1, chp = 0;
        while (str[*ptr] == ' ') *ptr += 1;
        chp = *ptr;
        if (str[*ptr] == '-' || str[*ptr] == '+') {
            if (str[*ptr] == '-') be = -1;
            *ptr += 1;
            counter++;
        }
        xX(str, buf, ptr, tok, ap, &counter, &che, &be, check, flag);
        while (str[*ptr] == '0' && str[*ptr + 1] == '0') {
            *ptr += 1;
            counter++;
        }
        o(str, ptr, tok, ap, &counter, &che, &be, check, flag, &chp);
    }
}
void work_o_s(char* str, token tok, va_list ap, int* check, int* ptr,
              int* flag) {
    if (*flag == 0) {
        if (tok.width == -1) tok.width = (int)s21_strlen(str) - *ptr;
        int counter = 0, be = 1;
        while (str[*ptr] == ' ') *ptr += 1;
        if (str[*ptr] == '-' || str[*ptr] == '+') {
            if (str[*ptr] == '-') be = -1;
            *ptr += 1;
            counter++;
        }
        while (str[*ptr] == '0' && str[*ptr + 1] == '0') {
            *ptr += 1;
            counter++;
        }
        if (s21_strspn(&str[*ptr], "1234567890") > 0 && tok.width > counter) {
            int che = 0;
            long b = str[*ptr] - '0';
            *ptr += 1;
            che++;
            counter++;
            while (s21_strspn(&str[*ptr], "1234567890") > 0 &&
                   tok.width > counter) {
                b = b * 10 + (str[*ptr] - '0');
                counter++;
                *ptr += 1;
                che++;
            }
            b = s21_eight_sys_rev(b) * be;
            if (che > 0) {
                *va_arg(ap, int*) = b;
                *check += 1;
            } else {
                *flag = 1;
            }
        } else {
            *flag = 1;
        }
    }
}
void work_xX_s(char* str, char* buf, token tok, va_list ap, int* check,
               int* ptr, int* flag) {
    if (*flag == 0) {
        if (tok.width == -1) tok.width = (int)s21_strlen(str) - *ptr;
        int counter = 0, b = 1;
        while (str[*ptr] == ' ') *ptr += 1;
        if (str[*ptr] == '-' || str[*ptr] == '+') {
            if (str[*ptr] == '-') b = -1;
            *ptr += 1;
            counter++;
        }
        if (str[*ptr] == '0' &&
            (str[*ptr + 1] == 'x' || str[*ptr + 1] == 'X') &&
            tok.width > counter) {
            int che = 0;
            *ptr += 2;
            counter += 2;
            long z = 0;
            int i = 0;
            while (str[*ptr] != ' ' && tok.width > counter) {
                buf[i] = str[*ptr];
                *ptr += 1;
                counter++;
                i++;
                che++;
            }
            buf[i] = '\0';
            z = s21_hex_system_rev(buf) * b;
            if (che > 0) {
                *va_arg(ap, int*) = z;
                *check += 1;
            } else {
                *flag = 1;
            }
        } else if (s21_strspn(&str[*ptr], "1234567890") > 0) {
            work_d_s(str, tok, ap, check, ptr, flag);
        }
    }
}
void work_n_s(va_list ap, const int* ptr, const int* flag) {
    if (*flag == 0) {
        int* temp = va_arg(ap, int*);
        *temp = *ptr;
    }
}
void work_f_s(char* str, char* buf, token tok, va_list ap, int* check, int* ptr,
              int* flag) {
    if (*flag == 0) {
        if (tok.width == -1) tok.width = (int)s21_strlen(str);
        while (str[*ptr] == ' ') *ptr += 1;
        int i = 0;
        while (str[*ptr] != ' ' && i < tok.width && str[*ptr] != '\0') {
            buf[i++] = str[*ptr];
            *ptr += 1;
        }
        *check += 1;
        if (str[*ptr] == '\0') *flag = 1;
        if (tok.length == '$') *va_arg(ap, float*) = atof(buf);
        if (tok.length == 'l') *va_arg(ap, double*) = atof(buf);
        if (tok.length == 'L') *va_arg(ap, long double*) = atof(buf);
    }
}
long s21_eight_sys_rev(long b) {
    long res = 0, c = 1;
    while (b) {
        res += b % 10 * c;
        c *= 8;
        b /= 10;
    }
    return res;
}
long s21_hex_system_rev(char* buf) {
    long res = 0, c = 1;
    for (int i = (int)s21_strlen(buf) - 1; i >= 0; i--) {
        if (s21_strspn(&buf[i], "abcdefABCDEF") > 0) {
            if (buf[i] == 'a' || buf[i] == 'A') res += 10 * c;
            if (buf[i] == 'b' || buf[i] == 'B') res += 11 * c;
            if (buf[i] == 'c' || buf[i] == 'C') res += 12 * c;
            if (buf[i] == 'd' || buf[i] == 'D') res += 13 * c;
            if (buf[i] == 'e' || buf[i] == 'E') res += 14 * c;
            if (buf[i] == 'f' || buf[i] == 'F') res += 15 * c;
            c *= 16;
        } else {
            res += (int)(buf[i] - '0') % 10 * c;
            c *= 16;
        }
    }
    return res;
}
void xX(const char* str, char* buf, int* ptr, token tok, va_list ap,
        int* counter, int* che, const int* be, int* check, int* flag) {
    if (str[*ptr] == '0' && (str[*ptr + 1] == 'x' || str[*ptr + 1] == 'X') &&
        tok.width > *counter) {
        *ptr += 2;
        *counter += 2;
        long z = 0;
        int i = 0;
        while (str[*ptr] != ' ' && tok.width > *counter) {
            buf[i] = str[*ptr];
            *ptr += 1;
            *counter += 1;
            i++;
            *che += 1;
        }
        buf[i] = '\0';
        z = s21_hex_system_rev(buf) * (*be);
        if (che > 0) {
            if (tok.length == '$') *va_arg(ap, int*) = z;
            if (tok.length == 'l') *va_arg(ap, long*) = z;
            *check += 1;
        } else {
            *flag = 1;
        }
    }
}
void o(char* str, int* ptr, token tok, va_list ap, int* counter,
       int* che, const int* be, int* check, int* flag, const int* chp) {
    if (str[*ptr] == '0' && s21_strspn(&str[*ptr + 1], "1234567890") > 0 &&
        tok.width > *counter) {
        long b = str[*ptr] - '0';
        *ptr += 1;
        *counter += 1;
        *che += 1;
        while (s21_strspn(&str[*ptr], "1234567890") > 0 &&
               tok.width > *counter) {
            b = b * 10 + (str[*ptr] - '0');
            *counter += 1;
            *ptr += 1;
            *che += 1;
        }
        b = s21_eight_sys_rev(b) * (*be);
        if (*che > 0) {
            *va_arg(ap, int*) = b;
            *check += 1;
        } else {
            *flag = 1;
        }
    } else if (s21_strspn(&str[*ptr], "1234567890") > 0) {
        *ptr = *chp;
        work_d_s(str, tok, ap, check, ptr, flag);
    }
}
