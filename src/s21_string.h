#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdarg.h>
#include <stdlib.h>

#define s21_NULL (void *)0

typedef unsigned long s21_size_t;

struct Token_S {
    int flag[5];
    int width;
    int accuracy;
    char length;
    char spec;
} typedef token;

char *initToken(char *pFormat, token *tok, va_list ap);
char *initVariable(char *str, token tok, va_list ap, int *check);
void initVariable_s(char *str, token tok, va_list ap, int *check, int *ptr,
                    int *flag);
void work_c(char *str, char *buf, token tok, va_list ap, int *check);
void work_s(char *str, char *buf, token tok, va_list ap, int *check);
void work_di_int(char *str, char *buf, token tok, va_list ap, int *check);
void work_di_long(char *str, char *buf, token tok, va_list ap, int *check);
void work_o(char *str, char *buf, token tok, va_list ap, int *check);
void work_xX(char *str, char *buf, token tok, va_list ap, int *check);
void work_u(char *str, char *buf, token tok, va_list ap, int *check);
void work_p(char *str, char *buf, token tok, va_list ap, int *check);
void work_n(va_list ap, const int *check);
void work_f(char *str, char *buf, token tok, va_list ap, int *check);
void work_e(char *str, char *buf, token tok, va_list ap, int *check);
void work_g(char *str, char *buf, token tok, va_list ap, int *check);
void work_c_s(const char *str, token tok, va_list ap, int *check,
              int *ptr, int *flag);
void work_s_s(char *str, char *buf, token tok, va_list ap, int *check, int *ptr,
              int *flag);
void work_d_s(char *str, token tok, va_list ap, int *check, int *ptr,
              int *flag);
void work_i_s(char *str, char *buf, token tok, va_list ap, int *check, int *ptr,
              int *flag);
void work_xX_s(char *str, char *buf, token tok, va_list ap, int *check,
               int *ptr, int *flag);
void work_o_s(char *str, token tok, va_list ap, int *check, int *ptr,
              int *flag);
void work_n_s(va_list ap, const int *ptr, const int *flag);
void work_f_s(char *str, char *buf, token tok, va_list ap, int *check, int *ptr,
              int *flag);
void s21_znak_int(char *buf, char *past, token tok, const int *prev,
                  const int *znak, const int *num);
void s21_znak_long(char *buf, char *past, token tok, const int *prev,
                   const int *znak, const long *num);
void s21_flag0_0(char *buf, char *past, token *tok, const int *prev,
                 const int *znak, char *ch);
void s21_flag0_1(char *buf, char *past, token *tok, const int *znak,
                 const char *ch);
void s21_zero_int(char *bPast, token tok, int *num);
void s21_zero_long(char *bPast, token tok, long *num);
void s21_accuracy(token tok, char *bPast, char *past);
void s21_accuracy_float(token tok, char *ptr, int *znak, int *dec, char *past,
                        char *bPast, double *num);
long s21_eight_sys(long a);
long s21_eight_sys_rev(long a);
void s21_hex_system(long number, char *buf, token tok);
long s21_hex_system_rev(char *buf);
void xX(const char *str, char *buf, int *ptr, token tok, va_list ap,
        int *counter, int *che, const int *be, int *check, int *flag);
void o(char *str, int *ptr, token tok, va_list ap, int *counter,
       int *che, const int *be, int *check, int *flag, const int *chp);
int work_sign(long double *number);
void work_e_degree(char *buf, int test_temp, const long double *number, int dec, token tok);
void znak_float(token tok, char *p, char *past, const int *znak, const char *ch,
                long double *number);

int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(char *str, const char *format, ...);

const void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void s21_itoa(int errnum, char *ptr);
void s21_itoa_un_int(int errnum, char *ptr, token tok);
void s21_itoa_un_long(long errnum, char *ptr, token tok);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, size_t start_index);

void *s21_trim(const char *src, const char *trim_chars);
int s21_start_i(const char *first_parametr, const char *second_parametr, s21_size_t l1, s21_size_t l2);
int s21_end_i(const char *first_parametr, const char *second_parametr, s21_size_t l1, s21_size_t l2);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);

#define EPERM 1
#define ENOENT 2
#define ESRCH 3
#define EINTR 4
#define EIO 5
#define ENXIO 6
#define E2BIG 7
#define ENOEXEC 8
#define EBADF 9
#define ECHILD 10
#define EAGAIN 11
#define ENOMEM 12
#define EACCES 13
#define EFAULT 14
#define ENOTBLK 15
#define EBUSY 16
#define EEXIST 17
#define EXDEV 18
#define ENODEV 19
#define ENOTDIR 20
#define EISDIR 21
#define EINVAL 22
#define ENFILE 23
#define EMFILE 24
#define ENOTTY 25
#define ETXTBSY 26
#define EFBIG 27
#define ENOSPC 28
#define ESPIPE 29
#define EROFS 30
#define EMLINK 31
#define EPIPE 32
#define EDOM 33
#define ERANGE 34
#define EDEADLK 35
#define ENAMETOOLONG 36
#define ENOLCK 37
#define ENOSYS 38
#define ENOTEMPTY 39
#define ELOOP 40
#define EWOULDBLOCK EAGAIN
#define ENOMSG 42
#define EIDRM 43
#define ECHRNG 44
#define EL2NSYNC 45
#define EL3HLT 46
#define EL3RST 47
#define ELNRNG 48
#define EUNATCH 49
#define ENOCSI 50
#define EL2HLT 51
#define EBADE 52
#define EBADR 53
#define EXFULL 54
#define ENOANO 55
#define EBADRQC 56
#define EBADSLT 57
#define EDEADLOCK EDEADLK
#define EBFONT 59
#define ENOSTR 60
#define ENODATA 61
#define ETIME 62
#define ENOSR 63
#define ENONET 64
#define ENOPKG 65
#define EREMOTE 66
#define ENOLINK 67
#define EADV 68
#define ESRMNT 69
#define ECOMM 70
#define EPROTO 71
#define EMULTIHOP 72
#define EDOTDOT 73
#define EBADMSG 74
#define EOVERFLOW 75
#define ENOTUNIQ 76
#define EBADFD 77
#define EREMCHG 78
#define ELIBACC 79
#define ELIBBAD 80
#define ELIBSCN 81
#define ELIBMAX 82
#define ELIBEXEC 83
#define EILSEQ 84
#define ERESTART 85
#define ESTRPIPE 86
#define EUSERS 87
#define ENOTSOCK 88
#define EDESTADDRREQ 89
#define EMSGSIZE 90
#define EPROTOTYPE 91
#define ENOPROTOOPT 92
#define EPROTONOSUPPORT 93
#define ESOCKTNOSUPPORT 94
#define EOPNOTSUPP 95
#define EPFNOSUPPORT 96
#define EAFNOSUPPORT 97
#define EADDRINUSE 98
#define EADDRNOTAVAIL 99
#define ENETDOWN 100
#define ENETUNREACH 101
#define ENETRESET 102
#define ECONNABORTED 103
#define ECONNRESET 104
#define ENOBUFS 105
#define EISCONN 106
#define ENOTCONN 107
#define ESHUTDOWN 108
#define ETOOMANYREFS 109
#define ETIMEDOUT 110
#define ECONNREFUSED 111
#define EHOSTDOWN 112
#define EHOSTUNREACH 113
#define EALREADY 114
#define EINPROGRESS115
#define ESTALE 116
#define EUCLEAN 117
#define ENOTNAM 118
#define ENAVAIL 119
#define EISNAM 120
#define EREMOTEIO 121
#define EDQUOT 122
#define ENOMEDIUM 123
#define EMEDIUMTYPE 124
#define ECANCELED 125
#define ENOKEY 126
#define EKEYEXPIRED 127
#define EKEYREVOKED 128
#define EKEYREJECTED 129
#define EOWNERDEAD 130
#define ENOTRECOVERABLE 131
#define ERFKILL 132
#define EHWPOISON 133

#if defined(__APPLE__)
#define MAXERR 107
#define ERRDATA                                         \
    {"Undefined error: 0",                              \
     "Operation not permitted",                         \
     "No such file or directory",                       \
     "No such process",                                 \
     "Interrupted system call",                         \
     "I/O error",                                       \
     "No such device or address",                       \
     "Argument list too long",                          \
     "Exec format error",                               \
     "Bad file number",                                 \
     "No child processes",                              \
     "Try again",                                       \
     "Out of memory",                                   \
     "Permission denied",                               \
     "Bad address",                                     \
     "Block device required",                           \
     "Device or resource busy",                         \
     "File exists",                                     \
     "Cross-device link",                               \
     "No such device",                                  \
     "Not a directory",                                 \
     "Is a directory",                                  \
     "Invalid argument",                                \
     "File table overflow",                             \
     "Too many open files",                             \
     "Not a typewriter",                                \
     "Text file busy",                                  \
     "File too large",                                  \
     "No space left on device",                         \
     "Illegal seek",                                    \
     "Read-only file system",                           \
     "Too many links",                                  \
     "Broken pipe",                                     \
     "Numerical argument out of domain",                \
     "Result too large",                                \
     "Resource temporarily unavailable",                \
     "Operation now in progress",                       \
     "Operation already in progress",                   \
     "Socket operation on non-socket",                  \
     "Destination address required",                    \
     "Message too long",                                \
     "Protocol wrong type for socket",                  \
     "Protocol not available",                          \
     "Protocol not supported",                          \
     "Socket type not supported",                       \
     "Operation not supported",                         \
     "Protocol family not supported",                   \
     "Address family not supported by protocol family", \
     "Address already in use",                          \
     "Can't assign requested address",                  \
     "Network is down",                                 \
     "Network is unreachable",                          \
     "Network dropped connection on reset",             \
     "Software caused connection abort",                \
     "Connection reset by peer",                        \
     "No buffer space available",                       \
     "Socket is already connected",                     \
     "Socket is not connected",                         \
     "Can't send after socket shutdown",                \
     "Too many references: can't splice",               \
     "Operation timed out",                             \
     "Connection refused",                              \
     "Too many levels of symbolic links",               \
     "File name too long",                              \
     "Host is down",                                    \
     "No route to host",                                \
     "Directory not empty",                             \
     "Too many processes",                              \
     "Too many users",                                  \
     "Disc quota exceeded",                             \
     "Stale NFS file handle",                           \
     "Too many levels of remote in path",               \
     "RPC struct is bad",                               \
     "RPC version wrong",                               \
     "RPC prog. not avail",                             \
     "Program version wrong",                           \
     "Bad procedure for program",                       \
     "No locks available",                              \
     "Function not implemented",                        \
     "Inappropriate file type or format",               \
     "Authentication error",                            \
     "Need authenticator",                              \
     "Device power is off",                             \
     "Device error",                                    \
     "Value too large to be stored in data type",       \
     "Bad executable (or shared library)",              \
     "Bad CPU type in executable",                      \
     "Shared library version mismatch",                 \
     "Malformed Mach-o file",                           \
     "Operation canceled",                              \
     "Identifier removed",                              \
     "No message of desired type",                      \
     "Illegal byte sequence",                           \
     "Attribute not found",                             \
     "Bad message",                                     \
     "EMULTIHOP (Reserved)",                            \
     "No message available on STREAM",                  \
     "ENOLINK (Reserved)",                              \
     "No STREAM resources",                             \
     "Not a STREAM",                                    \
     "Protocol error",                                  \
     "STREAM ioctl timeout",                            \
     "Operation not supported on socket",               \
     "Policy not found",                                \
     "State not recoverable",                           \
     "Previous owner died",                             \
     "Interface output queue is full"};

#elif defined(__linux__)
#define MAXERR 134
#define ERRDATA                                           \
    {"Success",                                           \
     "Operation not permitted",                           \
     "No such file or directory",                         \
     "No such process",                                   \
     "Interrupted system call",                           \
     "Input/output error",                                \
     "No such device or address",                         \
     "Argument list too long",                            \
     "Exec format error",                                 \
     "Bad file descriptor",                               \
     "No child processes",                                \
     "Resource temporarily unavailable",                  \
     "Cannot allocate memory",                            \
     "Permission denied",                                 \
     "Bad address",                                       \
     "Block device required",                             \
     "Device or resource busy",                           \
     "File exists",                                       \
     "Invalid cross-device link",                         \
     "No such device",                                    \
     "Not a directory",                                   \
     "Is a directory",                                    \
     "Invalid argument",                                  \
     "Too many open files in system",                     \
     "Too many open files",                               \
     "Inappropriate ioctl for device",                    \
     "Text file busy",                                    \
     "File too large",                                    \
     "No space left on device",                           \
     "Illegal seek",                                      \
     "Read-only file system",                             \
     "Too many links",                                    \
     "Broken pipe",                                       \
     "Numerical argument out of domain",                  \
     "Numerical result out of range",                     \
     "Resource deadlock avoided",                         \
     "File name too long",                                \
     "No locks available",                                \
     "Function not implemented",                          \
     "Directory not empty",                               \
     "Too many levels of symbolic links",                 \
     "Unknown error 41",                                  \
     "No message of desired type",                        \
     "Identifier removed",                                \
     "Channel number out of range",                       \
     "Level 2 not synchronized",                          \
     "Level 3 halted",                                    \
     "Level 3 reset",                                     \
     "Link number out of range",                          \
     "Protocol driver not attached",                      \
     "No CSI structure available",                        \
     "Level 2 halted",                                    \
     "Invalid exchange",                                  \
     "Invalid request descriptor",                        \
     "Exchange full",                                     \
     "No anode",                                          \
     "Invalid request code",                              \
     "Invalid slot",                                      \
     "Unknown error 58",                                  \
     "Bad font file format",                              \
     "Device not a stream",                               \
     "No data available",                                 \
     "Timer expired",                                     \
     "Out of streams resources",                          \
     "Machine is not on the network",                     \
     "Package not installed",                             \
     "Object is remote",                                  \
     "Link has been severed",                             \
     "Advertise error",                                   \
     "Srmount error",                                     \
     "Communication error on send",                       \
     "Protocol error",                                    \
     "Multihop attempted",                                \
     "RFS specific error",                                \
     "Bad message",                                       \
     "Value too large for defined data type",             \
     "Name not unique on network",                        \
     "File descriptor in bad state",                      \
     "Remote address changed",                            \
     "Can not access a needed shared library",            \
     "Accessing a corrupted shared library",              \
     ".lib section in a.out corrupted",                   \
     "Attempting to link in too many shared libraries",   \
     "Cannot exec a shared library directly",             \
     "Invalid or incomplete multibyte or wide character", \
     "Interrupted system call should be restarted",       \
     "Streams pipe error",                                \
     "Too many users",                                    \
     "Socket operation on non-socket",                    \
     "Destination address required",                      \
     "Message too long",                                  \
     "Protocol wrong type for socket",                    \
     "Protocol not available",                            \
     "Protocol not supported",                            \
     "Socket type not supported",                         \
     "Operation not supported",                           \
     "Protocol family not supported",                     \
     "Address family not supported by protocol",          \
     "Address already in use",                            \
     "Cannot assign requested address",                   \
     "Network is down",                                   \
     "Network is unreachable",                            \
     "Network dropped connection on reset",               \
     "Software caused connection abort",                  \
     "Connection reset by peer",                          \
     "No buffer space available",                         \
     "Transport endpoint is already connected",           \
     "Transport endpoint is not connected",               \
     "Cannot send after transport endpoint shutdown",     \
     "Too many references: cannot splice",                \
     "Connection timed out",                              \
     "Connection refused",                                \
     "Host is down",                                      \
     "No route to host",                                  \
     "Operation already in progress",                     \
     "Operation now in progress",                         \
     "Stale file handle",                                 \
     "Structure needs cleaning",                          \
     "Not a XENIX named type file",                       \
     "No XENIX semaphores available",                     \
     "Is a named type file",                              \
     "Remote I/O error",                                  \
     "Disk quota exceeded",                               \
     "No medium found",                                   \
     "Wrong medium type",                                 \
     "Operation canceled",                                \
     "Required key not available",                        \
     "Key has expired",                                   \
     "Key has been revoked",                              \
     "Key was rejected by service",                       \
     "Owner died",                                        \
     "State not recoverable",                             \
     "Operation not possible due to RF-kill",             \
     "Memory page has hardware error"};
#endif

#endif  //  SRC_S21_STRING_H_
