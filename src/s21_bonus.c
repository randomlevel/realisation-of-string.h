#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
    char *first_parametr = (char *)src;
    char *second_parametr = (char *)trim_chars;
    char *arr;
    int fl = 1;
    if (second_parametr == s21_NULL) {
        trim_chars = "\n\t\f\v";
        second_parametr = (char *)trim_chars;
    }
    if (first_parametr == s21_NULL) {
        fl = 0;
    }
    if (fl) {
        s21_size_t l1 = s21_strlen(src);
        s21_size_t l2 = s21_strlen(trim_chars);
        arr = (char *)malloc((l1 + 1) * sizeof(char));
        int arr_i = 0;
        int st_i = s21_start_i(first_parametr, second_parametr, l1, l2);
        int en_i = s21_end_i(first_parametr, second_parametr, l1, l2);
        for (int i = st_i; i < en_i; i++) {
            arr[arr_i] = src[i];
            arr_i++;
        }
        arr[arr_i] = '\0';
    }
    return fl == 0 ? s21_NULL : (char *)arr;
}
int s21_start_i(const char *first_parametr, const char *second_parametr,
                s21_size_t l1, s21_size_t l2) {
    int start_i = 0;
    for (s21_size_t i = 0; i < l1; i++) {
        int flag1 = 0;
        for (s21_size_t j = 0; j < l2; j++) {
            if (first_parametr[i] == second_parametr[j]) {
                flag1 = 1;
                break;
            }
        }
        if (flag1 == 1) {
            start_i++;
        } else {
            break;
        }
    }
    return start_i;
}
int s21_end_i(const char *first_parametr, const char *second_parametr,
              s21_size_t l1, s21_size_t l2) {
    int end_i = l1;
    for (int i = l1 - 1; i > -1; i--) {
        int flag2 = 0;
        for (s21_size_t j = 0; j < l2; j++) {
            if (first_parametr[i] == second_parametr[j]) {
                flag2 = 1;
                break;
            }
        }
        if (flag2 == 1) {
            end_i--;
        } else {
            break;
        }
    }
    return end_i;
}
void *s21_insert(const char *src, const char *str, size_t start_index) {
    int flag = 0;
    char *res = (malloc(s21_strlen(src) + s21_strlen(str) + 1));
    if (!res) flag = 1;
    char *r, *s;
    for (r = res, s = (char *)src; *s || *str; r++) {
        if (s == src + start_index && *str)
            *r = *(str++);
        else
            *r = *(s++);
    }
    *r = 0;
    if (flag == 1) res = s21_NULL;
    return res;
}
void *s21_to_upper(const char *str) {
    char *p = (char *)malloc(s21_strlen(str) + 1);
    for (int i = 0; *(str + i) != '\0'; i++) {
        if (*(str + i) >= 'a' && *(str + i) <= 'z') {
            p[i] = *(str + i) - 32;
        } else {
            p[i] = *(str + i);
        }
        if (i == (int)(s21_strlen(str)) - 1) p[i + 1] = '\0';
    }
    return p;
}
void *s21_to_lower(const char *str) {
    char *p = (char *)malloc(s21_strlen(str) + 1);
    for (int i = 0; *(str + i) != '\0'; i++) {
        if (*(str + i) >= 'A' && *(str + i) <= 'Z') {
            p[i] = *(str + i) + 32;
        } else {
            p[i] = *(str + i);
        }
        if (i == (int)(s21_strlen(str)) - 1) p[i + 1] = '\0';
    }
    return p;
}
