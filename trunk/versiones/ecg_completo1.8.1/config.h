#include "config.cfg"

#if SYSTEM==GNULINUX
#define MAINFUNC main
#endif
#if SYSTEM==SIHIVE
#define MAINFUNC hrt_main
#endif
#if SYSTEM==AVR
#define MAINFUNC hrt_main
#endif
