#include "s21_string.h"

const void *s21_memchr(const void *str, int c, s21_size_t n) {
    int i;
    char *pstr = s21_NULL;
    for (i = 0; i < (int)n; i++)
        if (*((char *)str + i) == c) pstr = (char *)str + i;
    return pstr;
}
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    while (--n && *(char *)str1 == *(char *)str2) {
        str1 = (char *)str1 + 1;
        str2 = (char *)str2 + 1;
    }
    return (*((unsigned char *)str1) - *((unsigned char *)str2));
}
void *s21_memcpy(void *dest, const void *src, s21_size_t count) {
    char *tmp = dest;
    const char *s = src;
    while (count--) *tmp++ = *s++;
    return dest;
}
void *s21_memmove(void *dst, const void *src, s21_size_t n) {
    const char *s;
    char *d;
    d = dst;
    s = src;
    if ((int)s21_strlen(d) <= (int)s21_strlen(s)) {
        while (n--) *d++ = *s++;
    } else {
        char *lastd;
        const char *lasts;
        lasts = s + (n - 1);
        lastd = d + (n - 1);
        while (n--) *lastd-- = *lasts--;
    }
    return (dst);
}
void *s21_memset(void *str, int c, s21_size_t n) {
    int flag = 1;
    char *str_char = (char *)str;
    if (str == s21_NULL) flag--;
    while (*str_char && n > 0 && flag == 1) {
        *str_char = c;
        str_char++;
        n--;
    }
    return str;
}
char *s21_strcat(char *dest, const char *src) {
    char *cat = dest;
    while (*cat != '\0') {
        cat++;
    }
    while (*src != '\0') {
        *cat = *src;
        cat++;
        src++;
    }
    *cat = '\0';
    return dest;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *ret = dest;
    int flag = 0;
    while (*dest) dest++;
    while (n-- && flag == 0)
        if (dest++ ==s21_NULL || src++== s21_NULL) flag++;
    *dest = 0;
    return ret;
}
char *s21_strchr(const char *str, int c) {
    int flag = 0;
    char *ptr;
    while (*str != (char)c && flag == 0)
        if (!*str++) flag = 1;
    ptr = (char *)str;
    if (flag == 1) ptr = NULL;
    return ptr;
}
int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) str1++, str2++;
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int l = 0;
    while (n--)
        if (*str1++ != *str2++)
            l = *(unsigned char *)(str1 - 1) - *(unsigned char *)(str2 - 1);
    return l;
}
char *s21_strcpy(char *dst, const char *src) {
    char *new_str = dst;
    for (; *src != '\0'; src++, dst++) {
        *dst = *src;
    }
    *dst = '\0';
    return new_str;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char *ret = dest;
    int flag = 0;
    do {
        if (!n--) flag = 1;
    } while (flag == 0 && (*dest++ = *src++));
    while (flag == 0 && n--) *dest++ = 0;
    return ret;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    int len1 = s21_strlen(str1);
    int len2 = s21_strlen(str2);
    int i, b = 0;
    for (i = 0; i < len1 && b == 0; i++)
        for (int j = 0; j < len2; j++)
            if (str1[i] == str2[j]) b = 1;
    return i - 1;
}
char *s21_strerror(int errnum) {
    char *flag = s21_NULL;
    if ((0 < errnum) && (errnum < MAXERR)) {
        static const char *errdata[MAXERR] = ERRDATA;
        flag = (char*)errdata[errnum];
    } else {
        static char buf[30]={0};
        s21_sprintf(buf, "Unknown error: %d", errnum);
        flag = buf;
    }
    return flag;
}
s21_size_t s21_strlen(const char *str) {
    const char *c = str;
    int length = 0;
    while (*c != '\0') {
        length++;
        c++;
    }
    return length;
}
char *s21_strpbrk(const char *str1, const char *str2) {
    int len1 = s21_strlen(str1);
    int len2 = s21_strlen(str2);
    char *ptr = s21_NULL;
    int flag = 0;
    for (int i = 0; i < len1 && flag == 0; i++) {
        for (int j = 0; j < len2 && flag == 0; j++) {
            if (str1[i] == str2[j]) {
                ptr = (char *)&str1[i];
                flag = 1;
            }
        }
    }
    return ptr;
}
char *s21_strrchr(const char *s, int c) {
    char *ret = 0;
    do {
        if (*s == (char)c) ret = (char *)s;
    } while (*s++);
    return ret;
}
s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t ret = 0;
    while (*str1 && s21_strchr(str2, *str1++)) ret++;
    return ret;
}
char *s21_strstr(const char *haystack, const char *needle) {
    char *result = s21_NULL;
    char *temp_str1 = s21_NULL;
    char *temp_str2 = s21_NULL;
    int flag;
    int fflag = 0;
    while (*haystack && fflag == 0) {
        if (*haystack == *needle) {
            flag = 1;
            temp_str1 = (char *)haystack;
            temp_str2 = (char *)needle;
            while (*temp_str1 && *temp_str2) {
                flag &= flag && (*temp_str1 == *temp_str2);
                temp_str1++;
                temp_str2++;
            }
            if (flag) {
                result = (char *)haystack;
                fflag++;
            }
        }
        ++haystack;
    }
    return result;
}
char *s21_strtok(char *str, const char *delim) {
    char *final_ptr = s21_NULL;
    static char *temp_ptr = s21_NULL;
    int flagg = 0;
    unsigned int i, j;
    if (str != s21_NULL) {
        temp_ptr = str;
    }
    final_ptr = temp_ptr;
    for (i = 0; i <= s21_strlen(temp_ptr) && flagg == 0; i++) {
        for (j = 0; j < s21_strlen(delim) && flagg == 0; j++) {
            if (temp_ptr[i] == '\0') {
                flagg = 1;
            }
            if (temp_ptr[i] == delim[j]) {
                temp_ptr[i] = '\0';
                temp_ptr += i + 1;
                flagg = 1;
            }
        }
    }
    return final_ptr;
}
