#ifndef __LOGGING_H
#define __LOGGING_H


#define DEBUG

#ifdef DEBUG
#define PINFO(fmt, ...) printf("[+] " fmt, ##__VA_ARGS__)
#else
#define pinfo(fmt, ...)  // does nothing
#endif

#define PWARN(fmt, ...) printf("[!] " fmt, ##__VA_ARGS__)

#endif
