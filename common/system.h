#ifndef LSOFT_SYS_SYSTEM_H
#define LSOFT_SYS_SYSTEM_H

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define LSOFT_POSIX
#elif defined(_WIN32) || defined(_WIN64)
#define LSOFT_WINDOWS
#endif

#endif // LSOFT_SYS_SYSTEM_H
