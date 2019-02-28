#include <stdio.h>
#include <stdarg.h>

void _serverAssert(const char *estr, const char *file, int line) {
    fprintf(stderr, "=== ASSERTION FAILED ===");
    fprintf(stderr, "==> %s:%d '%s' is not true\n",file,line,estr);
    *((char*)-1) = 'x';
}

void _serverPanic(const char *file, int line, const char *msg, ...) {
    va_list ap;
    va_start(ap,msg);
    char fmtmsg[256];
    vsnprintf(fmtmsg,sizeof(fmtmsg),msg,ap);
    va_end(ap);
    fprintf(stderr, "=== PANIC ===");
    fprintf(stderr, "==> %s:%d '%s' break\n",file,line,fmtmsg);
    *((char*)-1) = 'x';
}
