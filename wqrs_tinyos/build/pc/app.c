# 24 "/usr/include/sys/types.h"
typedef short int __int16_t;
typedef unsigned short int __uint16_t;





typedef int __int32_t;
typedef unsigned int __uint32_t;






__extension__ 
#line 39
typedef long long __int64_t;
__extension__ 
#line 40
typedef unsigned long long __uint64_t;
# 12 "/usr/include/sys/_types.h"
typedef long _off_t;
__extension__ 
#line 13
typedef long long _off64_t;


typedef int _ssize_t;
# 323 "/usr/lib/gcc-lib/i686-pc-cygwin/3.2/include/stddef.h" 3
typedef unsigned int wint_t;
# 25 "/usr/include/sys/_types.h"
typedef struct __nesc_unnamed4242 {

  int __count;
  union __nesc_unnamed4243 {

    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;

typedef int _flock_t;
# 149 "/usr/lib/gcc-lib/i686-pc-cygwin/3.2/include/stddef.h" 3
typedef int ptrdiff_t;
#line 203
typedef unsigned int size_t;
#line 296
typedef short unsigned int wchar_t;
# 36 "/usr/include/machine/types.h" 3
typedef long int __off_t;
typedef int __pid_t;

__extension__ 
#line 39
typedef long long int __loff_t;
# 78 "/usr/include/sys/types.h"
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;



typedef unsigned short ushort;
typedef unsigned int uint;



typedef unsigned long clock_t;




typedef long time_t;




struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};


typedef long daddr_t;
typedef char *caddr_t;
# 166 "/usr/include/sys/types.h" 3
typedef int pid_t;
typedef long key_t;
typedef _ssize_t ssize_t;
#line 187
typedef unsigned short nlink_t;
#line 209
typedef long fd_mask;







typedef struct _types_fd_set {
  fd_mask fds_bits[(64 + (sizeof(fd_mask ) * 8 - 1)) / (sizeof(fd_mask ) * 8)];
} _types_fd_set;
#line 245
typedef unsigned long clockid_t;




typedef unsigned long timer_t;




typedef long useconds_t;
# 24 "/usr/include/cygwin/types.h"
typedef struct timespec timespec_t;




typedef struct timespec timestruc_t;




typedef long __off32_t;
typedef long long __off64_t;



typedef __off32_t off_t;





typedef short __dev16_t;
typedef unsigned long __dev32_t;



typedef __dev16_t dev_t;





typedef long blksize_t;




typedef long __blkcnt32_t;
typedef long long __blkcnt64_t;



typedef __blkcnt32_t blkcnt_t;





typedef unsigned short __uid16_t;
typedef unsigned long __uid32_t;



typedef __uid16_t uid_t;





typedef unsigned short __gid16_t;
typedef unsigned long __gid32_t;



typedef __gid16_t gid_t;








typedef unsigned long ino_t;








typedef unsigned long vm_offset_t;




typedef unsigned long vm_size_t;




typedef char int8_t;



typedef __int16_t int16_t;



typedef __int32_t int32_t;



typedef __int64_t int64_t;




typedef unsigned char uint8_t;



typedef __uint16_t uint16_t;



typedef __uint32_t uint32_t;



typedef __uint64_t uint64_t;




typedef unsigned char u_int8_t;



typedef __uint16_t u_int16_t;



typedef __uint32_t u_int32_t;



typedef __uint64_t u_int64_t;




typedef unsigned long uintptr_t;




typedef long intptr_t;




typedef __int32_t register_t;




typedef char *addr_t;




typedef unsigned mode_t;





typedef struct __pthread_t {
#line 193
  char __dummy;
} *
#line 193
pthread_t;
typedef struct __pthread_mutex_t {
#line 194
  char __dummy;
} *
#line 194
pthread_mutex_t;

typedef struct __pthread_key_t {
#line 196
  char __dummy;
} *
#line 196
pthread_key_t;
typedef struct __pthread_attr_t {
#line 197
  char __dummy;
} *
#line 197
pthread_attr_t;
typedef struct __pthread_mutexattr_t {
#line 198
  char __dummy;
} *
#line 198
pthread_mutexattr_t;
typedef struct __pthread_condattr_t {
#line 199
  char __dummy;
} *
#line 199
pthread_condattr_t;
typedef struct __pthread_cond_t {
#line 200
  char __dummy;
} *
#line 200
pthread_cond_t;


typedef struct __nesc_unnamed4244 {

  pthread_mutex_t mutex;
  int state;
} 
pthread_once_t;
typedef struct __pthread_rwlock_t {
#line 209
  char __dummy;
} *
#line 209
pthread_rwlock_t;
typedef struct __pthread_rwlockattr_t {
#line 210
  char __dummy;
} *
#line 210
pthread_rwlockattr_t;
# 27 "/usr/include/sys/unistd.h"
int __attribute((__cdecl__)) close(int __fildes);
#line 80
off_t __attribute((__cdecl__)) lseek(int __fildes, off_t __offset, int __whence);








_ssize_t __attribute((__cdecl__)) read(int __fd, void *__buf, size_t __nbyte);
#line 118
unsigned __attribute((__cdecl__)) sleep(unsigned int __seconds);





int __attribute((__cdecl__)) unlink(const char *__path);

_ssize_t __attribute((__cdecl__)) write(int __fd, const void *__buf, size_t __nbyte);
# 163 "/usr/include/sys/unistd.h" 3
unsigned __attribute((__cdecl__)) usleep(unsigned int __useconds);
# 44 "/usr/lib/gcc-lib/i686-pc-cygwin/3.2/include/stdarg.h" 3
typedef __builtin_va_list __gnuc_va_list;
# 19 "/usr/include/sys/reent.h"
typedef unsigned long __ULong;
# 40 "/usr/include/sys/reent.h" 3
struct _Bigint {

  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm {

  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};








struct _atexit {
  struct _atexit *_next;
  int _ind;
  void (*_fns[32])(void );
  void *_fnargs[32];
  __ULong _fntypes;
};
#line 91
struct __sbuf {
  unsigned char *_base;
  int _size;
};






typedef long _fpos_t;



typedef _off64_t _fpos64_t;
#line 156
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void *_cookie;

  _ssize_t __attribute((__cdecl__)) (*_read)(void *_cookie, char *_buf, int _n);
  _ssize_t __attribute((__cdecl__)) (*_write)(void *_cookie, const char *_buf, int _n);

  _fpos_t __attribute((__cdecl__)) (*_seek)(void *_cookie, _fpos_t _offset, int _whence);
  int __attribute((__cdecl__)) (*_close)(void *_cookie);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _offset;


  struct _reent *_data;



  _flock_t _lock;
};



struct __sFILE64 {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;

  struct _reent *_data;


  void *_cookie;

  _ssize_t __attribute((__cdecl__)) (*_read)(void *_cookie, char *_buf, int _n);
  _ssize_t __attribute((__cdecl__)) (*_write)(void *_cookie, const char *_buf, int _n);

  _fpos_t __attribute((__cdecl__)) (*_seek)(void *_cookie, _fpos_t _offset, int _whence);
  int __attribute((__cdecl__)) (*_close)(void *_cookie);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _flags2;

  _off64_t _offset;
  _fpos64_t __attribute((__cdecl__)) (*_seek64)(void *_cookie, _fpos64_t _offset, int _whence);


  _flock_t _lock;
};

typedef struct __sFILE64 __FILE;




struct _glue {

  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
#line 280
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;
};
#line 530
struct _reent {

  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];

  int _current_category;
  const char *_current_locale;

  int __sdidinit;

  void __attribute((__cdecl__)) (*__cleanup)(struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union __nesc_unnamed4245 {

    struct __nesc_unnamed4246 {

      unsigned int _unused_rand;
      char *_strtok_last;
      char _asctime_buf[26];
      struct __tm _localtime_buf;
      int _gamma_signgam;
      __extension__ unsigned long long _rand_next;
      struct _rand48 _r48;
      _mbstate_t _mblen_state;
      _mbstate_t _mbtowc_state;
      _mbstate_t _wctomb_state;
      char _l64a_buf[8];
      char _signal_buf[24];
      int _getdate_err;
      _mbstate_t _mbrlen_state;
      _mbstate_t _mbrtowc_state;
      _mbstate_t _mbsrtowcs_state;
      _mbstate_t _wcrtomb_state;
      _mbstate_t _wcsrtombs_state;
    } _reent;



    struct __nesc_unnamed4247 {


      unsigned char *_nextf[30];
      unsigned int _nmalloc[30];
    } _unused;
  } _new;


  struct _atexit *_atexit;
  struct _atexit _atexit0;


  void (**_sig_func)(int );




  struct _glue __sglue;
  __FILE __sf[3];
};
#line 726
extern struct _reent *_impure_ptr;
# 50 "/usr/include/stdio.h"
typedef __FILE FILE;





typedef _fpos_t fpos_t;
# 172 "/usr/include/stdio.h" 3
int __attribute((__cdecl__)) fclose(FILE *);




int __attribute((__cdecl__)) fprintf(FILE *, const char *, ...);
int __attribute((__cdecl__)) fscanf(FILE *, const char *, ...);
int __attribute((__cdecl__)) printf(const char *, ...);


int __attribute((__cdecl__)) vfprintf(FILE *, const char *, __gnuc_va_list );






int __attribute((__cdecl__)) getc(FILE *);
#line 208
FILE *__attribute((__cdecl__)) fopen(const char *_name, const char *_type);
#line 223
int __attribute((__cdecl__)) vsnprintf(char *, size_t , const char *, __gnuc_va_list );





int __attribute((__cdecl__)) snprintf(char *, size_t , const char *, ...);









FILE *__attribute((__cdecl__)) fdopen(int , const char *);
# 24 "/usr/include/string.h"
void *__attribute((__cdecl__)) memcpy(void *, const void *, size_t );

void *__attribute((__cdecl__)) memset(void *, int , size_t );


int __attribute((__cdecl__)) strcmp(const char *, const char *);



char *__attribute((__cdecl__)) strerror(int );


int __attribute((__cdecl__)) strncmp(const char *, const char *, size_t );
char *__attribute((__cdecl__)) strncpy(char *, const char *, size_t );






char *__attribute((__cdecl__)) strtok(char *, const char *);









void __attribute((__cdecl__)) bzero(void *, size_t );
# 24 "/usr/include/stdlib.h"
typedef struct __nesc_unnamed4248 {

  int quot;
  int rem;
} div_t;

typedef struct __nesc_unnamed4249 {

  long quot;
  long rem;
} ldiv_t;
#line 52
double __attribute((__cdecl__)) atof(const char *__nptr);



int __attribute((__cdecl__)) atoi(const char *__nptr);






void *__attribute((__cdecl__)) calloc(size_t __nmemb, size_t __size);

void __attribute((__cdecl__)) __attribute((noreturn)) exit(int __status);
void __attribute((__cdecl__)) free(void *);
char *__attribute((__cdecl__)) getenv(const char *__string);





void *__attribute((__cdecl__)) malloc(size_t __size);
#line 91
int __attribute((__cdecl__)) rand(void );

void __attribute((__cdecl__)) srand(unsigned __seed);
# 17 "/usr/include/math.h"
union __dmath {

  __ULong i[2];
  double d;
};




union __dmath;
#line 72
typedef float float_t;
typedef double double_t;
#line 290
struct exception {


  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};
#line 345
enum __fdlibm_version {

  __fdlibm_ieee = -1, 
  __fdlibm_svid, 
  __fdlibm_xopen, 
  __fdlibm_posix
};




enum __fdlibm_version;
# 91 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/tos.h"
typedef unsigned char bool;






enum __nesc_unnamed4250 {
  FALSE = 0, 
  TRUE = 1
};

uint16_t TOS_LOCAL_ADDRESS = 1;

enum __nesc_unnamed4251 {
  FAIL = 0, 
  SUCCESS = 1
};
static inline 

uint8_t rcombine(uint8_t r1, uint8_t r2);
typedef uint8_t  result_t;
static inline 






result_t rcombine(result_t r1, result_t r2);
static inline 






result_t rcombine3(result_t r1, result_t r2, result_t r3);
static inline 



result_t rcombine4(result_t r1, result_t r2, result_t r3, 
result_t r4);





enum __nesc_unnamed4252 {
  NULL = 0x0
};
# 19 "/usr/include/sys/signal.h"
typedef unsigned long sigset_t;
# 109 "/usr/include/sys/signal.h" 3
typedef void (*_sig_func_ptr)(int );

struct sigaction {

  _sig_func_ptr sa_handler;
  sigset_t sa_mask;
  int sa_flags;
};
#line 155
int __attribute((__cdecl__)) sigaction(int , const struct sigaction *, struct sigaction *);




int __attribute((__cdecl__)) sigemptyset(sigset_t *);
# 9 "/usr/include/signal.h"
typedef int sig_atomic_t;





struct _reent;





_sig_func_ptr __attribute((__cdecl__)) signal(int , _sig_func_ptr );
# 62 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/nido.h"
enum __nesc_unnamed4253 {
  TOSNODES = 1000, 
  DEFAULT_EEPROM_SIZE = 512 * 1024
};

enum __nesc_unnamed4254 {
  TOSSIM_RADIO_MODEL_SIMPLE = 0, 
  TOSSIM_RADIO_MODEL_LOSSY = 1, 
  TOSSIM_RADIO_MODEL_PACKET = 2
};
# 51 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.h"
typedef struct __nesc_unnamed4255 {
  int size;
  void *data;
  int private_size;
} heap_t;
static inline 
void init_heap(heap_t *heap);
static inline 
int heap_is_empty(heap_t *heap);
static inline 
long long heap_get_min_key(heap_t *heap);
static 
void *heap_pop_min_data(heap_t *heap, long long *key);
static inline void heap_insert(heap_t *heap, void *data, long long key);
# 33 "/usr/include/time.h"
struct tm {

  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};








struct tm;
struct tm;





struct tm;
struct tm;
# 24 "/usr/include/sched.h"
struct sched_param {

  int sched_priority;
};
# 104 "/usr/include/pthread.h" 3
typedef void (*__cleanup_routine_type)(void *);
typedef struct _pthread_cleanup_handler {

  __cleanup_routine_type function;
  void *arg;
  struct _pthread_cleanup_handler *next;
} __pthread_cleanup_handler;










int pthread_cond_broadcast(pthread_cond_t *);

int pthread_cond_init(pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_signal(pthread_cond_t *);


int pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);





int pthread_create(pthread_t *, const pthread_attr_t *, 
void *(*)(void *), void *);
#line 147
int pthread_mutex_init(pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_lock(pthread_mutex_t *);


int pthread_mutex_unlock(pthread_mutex_t *);
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/event_queue.h"
struct TOS_state;

typedef struct event_queue {
  int pause;
  heap_t heap;
  pthread_mutex_t lock;
} event_queue_t;

typedef struct event {
  long long time;
  int mote;
  int pause;
  int force;

  void *data;

  void (*handle)(struct event *, struct TOS_state *);
  void (*cleanup)(struct event *);
} event_t;
static inline 

void queue_init(event_queue_t *queue, int fpause);
static void queue_insert_event(event_queue_t *queue, event_t *event);
static inline event_t *queue_pop_event(event_queue_t *queue);
static inline void queue_handle_next_event(event_queue_t *queue);
static inline int queue_is_empty(event_queue_t *queue);
static inline long long queue_peek_event_time(event_queue_t *queue);
# 62 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adjacency_list.h"
enum __nesc_unnamed4256 {
  NUM_NODES_ALLOC = 200
};


typedef struct link {
  int mote;
  double data;
  char bit;
  struct link *next_link;
} link_t;


link_t *free_list;
int num_free_links;
static 
link_t *allocate_link(int mote);
static 
int adjacency_list_init(void);
# 62 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/rfm_model.h"
typedef struct __nesc_unnamed4257 {
  void (*init)(void);
  void (*transmit)(int , char );
  void (*stop_transmit)(int );
  char (*hears)(int );
  bool (*connected)(int , int );
  link_t *(*neighbors)(int );
} rfm_model;
static inline 

rfm_model *create_simple_model(void);
static inline 




rfm_model *create_lossy_model(char *file);
static 
void static_one_cell_init(void);
static inline 


void set_link_prob_value(uint16_t moteID1, uint16_t moteID2, double prob);



extern link_t *radio_connectivity[TOSNODES];
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adc_model.h"
typedef struct __nesc_unnamed4258 {
  void (*init)(void);

  uint16_t (*read)(int , uint8_t , long long );
} adc_model;
static inline 
adc_model *create_random_adc_model(void);
static inline adc_model *create_generic_adc_model(void);
static inline void set_adc_value(int moteID, uint8_t port, uint16_t value);
# 58 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/spatial_model.h"
typedef struct __nesc_unnamed4259 {
  double xCoordinate;
  double yCoordinate;
  double zCoordinate;
} point3D;

typedef struct __nesc_unnamed4260 {
  void (*init)(void);
  void (*get_position)(int , long long , point3D *);
} 

spatial_model;
static inline 


spatial_model *create_simple_spatial_model(void);
static inline 
# 64 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/nido_eeprom.h"
int anonymousEEPROM(int numMotes, int eepromSize);
static inline int namedEEPROM(char *name, int numMotes, int eepromSize);
# 55 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/events.h"
typedef struct __nesc_unnamed4261 {
  int interval;
  int mote;
  int valid;
  int disabled;
} clock_tick_data_t;

typedef struct __nesc_unnamed4262 {
  int valid;
  char port;
} adc_tick_data_t;

typedef struct __nesc_unnamed4263 {
  int interval;
  int mote;
  int valid;
} radio_tick_data_t;

typedef struct __nesc_unnamed4264 {
  int interval;
  int mote;
  int valid;
} channel_mon_data_t;

typedef struct __nesc_unnamed4265 {
  int interval;
  int mote;
  int valid;
  int count;
  int ending;
} spi_byte_data_t;

typedef struct __nesc_unnamed4266 {
  int interval;
  int mote;
  int valid;
} radio_timing_data_t;
static inline 




void event_default_cleanup(event_t *event);
static 
void event_total_cleanup(event_t *event);
static 
void event_clocktick_create(event_t *event, 
int mote, 
long long eventTime, 
int interval);
static inline 
void event_clocktick_handle(event_t *event, 
struct TOS_state *state);
static inline 
void event_clocktick_invalidate(event_t *event);
#line 128
void event_channel_mon_create(event_t *event, int mote, long long ftime, int interval);

void event_channel_mon_invalidate(event_t *event);

void event_spi_byte_handle(event_t *event, struct TOS_state *state);

void event_spi_byte_create(event_t *event, int mote, long long ftime, int interval, int count);

void event_spi_byte_invalidate(event_t *event);

void event_spi_byte_end(event_t *fevent);



void event_radio_timing_create(event_t *fevent, int mote, long long ftime, int interval);

void event_radio_timing_invalidate(event_t *fevent);
static inline 
void event_cleanup(event_t *fevent);
# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/types/AM.h"
enum __nesc_unnamed4267 {
  TOS_BCAST_ADDR = 0xffff, 
  TOS_UART_ADDR = 0x007e
};





enum __nesc_unnamed4268 {
  TOS_DEFAULT_AM_GROUP = 0x7d
};

uint8_t TOS_AM_GROUP = TOS_DEFAULT_AM_GROUP;
#line 84
typedef struct TOS_Msg {


  uint16_t addr;
  uint8_t type;
  uint8_t group;
  uint8_t length;
  int8_t data[29];
  uint16_t crc;







  uint16_t strength;
  uint8_t ack;
  uint16_t time;
  uint8_t sendSecurityMode;
  uint8_t receiveSecurityMode;
} TOS_Msg;

typedef struct TOS_Msg_TinySecCompat {


  uint16_t addr;
  uint8_t type;

  uint8_t length;
  uint8_t group;
  int8_t data[29];
  uint16_t crc;







  uint16_t strength;
  uint8_t ack;
  uint16_t time;
  uint8_t sendSecurityMode;
  uint8_t receiveSecurityMode;
} TOS_Msg_TinySecCompat;

typedef struct TinySec_Msg {

  uint16_t addr;
  uint8_t type;
  uint8_t length;

  uint8_t iv[4];

  uint8_t enc[29];

  uint8_t mac[4];


  uint8_t calc_mac[4];
  uint8_t ack_byte;
  bool cryptoDone;
  bool receiveDone;

  bool MACcomputed;
} __attribute((packed))  TinySec_Msg;



enum __nesc_unnamed4269 {
  MSG_DATA_SIZE = (size_t )& ((struct TOS_Msg *)0)->crc + sizeof(uint16_t ), 
  TINYSEC_MSG_DATA_SIZE = (size_t )& ((struct TinySec_Msg *)0)->mac + 4, 
  DATA_LENGTH = 29, 
  LENGTH_BYTE_NUMBER = (size_t )& ((struct TOS_Msg *)0)->length + 1, 
  TINYSEC_NODE_ID_SIZE = sizeof(uint16_t )
};

enum __nesc_unnamed4270 {
  TINYSEC_AUTH_ONLY = 1, 
  TINYSEC_ENCRYPT_AND_AUTH = 2, 
  TINYSEC_DISABLED = 3, 
  TINYSEC_RECEIVE_AUTHENTICATED = 4, 
  TINYSEC_RECEIVE_CRC = 5, 
  TINYSEC_RECEIVE_ANY = 6, 
  TINYSEC_ENABLED_BIT = 128, 
  TINYSEC_ENCRYPT_ENABLED_BIT = 64
} __attribute((packed)) ;


typedef TOS_Msg *TOS_MsgPtr;
static inline 
# 57 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/packet_sim.h"
void packet_sim_init(void);

void   packet_sim_transmit_done(TOS_MsgPtr msg);
void   packet_sim_receive_msg(TOS_MsgPtr msg);
# 16 "/usr/include/sys/time.h"
struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};
# 28 "/usr/include/sys/select.h"
int select(int __n, _types_fd_set *__readfds, _types_fd_set *__writefds, _types_fd_set *__exceptfds, struct timeval *__timeout);
# 36 "/usr/include/sys/time.h"
struct itimerval {
  struct timeval it_interval;
  struct timeval it_value;
};
# 73 "/usr/include/sys/time.h" 3
int __attribute((__cdecl__)) gettimeofday(struct timeval *__p, struct timezone *__z);
# 84 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/nido.h"
typedef struct TOS_node_state {
  long long time;
  int pot_setting;
} TOS_node_state_t;

typedef struct TOS_state {
  long long tos_time;
  int radio_kb_rate;
  short num_nodes;
  short current_node;
  TOS_node_state_t node_state[TOSNODES];
  event_queue_t queue;
  uint8_t radioModel;
  rfm_model *rfm;
  adc_model *adc;
  spatial_model *space;
  bool moteOn[TOSNODES];
  bool cancelBoot[TOSNODES];


  bool paused;
  pthread_mutex_t pause_lock;
  pthread_cond_t pause_cond;
  pthread_cond_t pause_ack_cond;
} TOS_state_t;






extern TOS_state_t tos_state;




void set_sim_rate(uint32_t );
uint32_t get_sim_rate(void);
static void __nesc_nido_initialise(int mote);
# 54 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/types/dbg_modes.h"
typedef long long TOS_dbg_mode;



enum __nesc_unnamed4271 {
  DBG_ALL = ~0ULL, 


  DBG_BOOT = 1ULL << 0, 
  DBG_CLOCK = 1ULL << 1, 
  DBG_TASK = 1ULL << 2, 
  DBG_SCHED = 1ULL << 3, 
  DBG_SENSOR = 1ULL << 4, 
  DBG_LED = 1ULL << 5, 
  DBG_CRYPTO = 1ULL << 6, 


  DBG_ROUTE = 1ULL << 7, 
  DBG_AM = 1ULL << 8, 
  DBG_CRC = 1ULL << 9, 
  DBG_PACKET = 1ULL << 10, 
  DBG_ENCODE = 1ULL << 11, 
  DBG_RADIO = 1ULL << 12, 


  DBG_LOG = 1ULL << 13, 
  DBG_ADC = 1ULL << 14, 
  DBG_I2C = 1ULL << 15, 
  DBG_UART = 1ULL << 16, 
  DBG_PROG = 1ULL << 17, 
  DBG_SOUNDER = 1ULL << 18, 
  DBG_TIME = 1ULL << 19, 
  DBG_POWER = 1ULL << 20, 



  DBG_SIM = 1ULL << 21, 
  DBG_QUEUE = 1ULL << 22, 
  DBG_SIMRADIO = 1ULL << 23, 
  DBG_HARD = 1ULL << 24, 
  DBG_MEM = 1ULL << 25, 



  DBG_USR1 = 1ULL << 27, 
  DBG_USR2 = 1ULL << 28, 
  DBG_USR3 = 1ULL << 29, 
  DBG_TEMP = 1ULL << 30, 

  DBG_ERROR = 1ULL << 31, 
  DBG_NONE = 0, 

  DBG_DEFAULT = DBG_ALL
};
static inline 
# 127 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/nido.h"
void tos_state_model_init(void );
static inline 
# 48 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.nido.h"
void init_hardware(void);
static 
short set_io_bit(char port, char bit);
static inline short clear_io_bit(char port, char bit);
#line 219
enum __nesc_unnamed4272 {
  TOSH_period16 = 0x00, 
  TOSH_period32 = 0x01, 
  TOSH_period64 = 0x02, 
  TOSH_period128 = 0x03, 
  TOSH_period256 = 0x04, 
  TOSH_period512 = 0x05, 
  TOSH_period1024 = 0x06, 
  TOSH_period2048 = 0x07
};



enum __nesc_unnamed4273 {

  TOSH_ACTUAL_CC_RSSI_PORT = 0, 
  TOSH_ACTUAL_VOLTAGE_PORT = 7, 
  TOSH_ACTUAL_BANDGAP_PORT = 30, 
  TOSH_ACTUAL_GND_PORT = 31
};

enum __nesc_unnamed4274 {

  TOS_ADC_CC_RSSI_PORT = 0, 
  TOS_ADC_VOLTAGE_PORT = 7, 
  TOS_ADC_BANDGAP_PORT = 10, 
  TOS_ADC_GND_PORT = 11
};
#line 270
static __inline void TOSH_CLR_RFM_TXD_PIN(void);
#line 270
static __inline void TOSH_MAKE_RFM_TXD_INPUT(void);
static __inline void TOSH_SET_RFM_CTL0_PIN(void);
#line 271
static __inline void TOSH_CLR_RFM_CTL0_PIN(void);
static __inline void TOSH_SET_RFM_CTL1_PIN(void);
# 46 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/pcConst.h"
typedef enum __nesc_unnamed4275 {
#line 46
  RX_TABLE_FULL = 0, 
  RX_NOT_EXPIRED_DUPLICATE = 1, 
  RX_EXPIRED_NOT_DUPLICATE = 2, 
  RX_SEQNO_NOTFOUND = 3, 
  RX_ENTRY_AVAILABLE = 4
} RX_PKT_PROCESSING_OUTCOME;

typedef enum __nesc_unnamed4276 {
#line 53
  TX_TABLE_FULL = 0, 
  TX_ENTRY_AVAILABLE = 1, 
  TX_EXPIRED_ENTRY = 2, 
  TX_VALID_ENTRY = 3
} TX_PKT_PROCESSING_OUTCOME;
# 18 "/usr/include/cygwin/socket.h"
struct sockaddr {
  unsigned short sa_family;
  char sa_data[14];
};
# 37 "/usr/include/cygwin/if.h"
struct ifreq {



  union __nesc_unnamed4277 {

    char ifrn_name[16];
  } ifr_ifrn;

  union __nesc_unnamed4278 {
    struct sockaddr ifru_addr;
    struct sockaddr ifru_broadaddr;
    struct sockaddr ifru_netmask;
    struct sockaddr ifru_hwaddr;
    short ifru_flags;
    int ifru_metric;
    int ifru_mtu;
  } ifr_ifru;
};
#line 74
struct ifconf {

  int ifc_len;
  union __nesc_unnamed4279 {

    caddr_t ifcu_buf;
    struct ifreq *ifcu_req;
  } ifc_ifcu;
};
# 28 "/usr/include/cygwin/socket.h"
struct linger {
  unsigned short l_onoff;
  unsigned short l_linger;
};

struct msghdr {

  void *msg_name;
  int msg_namelen;
  struct iovec *msg_iov;
  int msg_iovlen;
  void *msg_accrights;
  int msg_accrightslen;
};
# 29 "/usr/include/sys/socket.h"
int accept(int , struct sockaddr *__peer, int *);
int bind(int , const struct sockaddr *__my_addr, int __addrlen);



int listen(int , int __n);




int send(int , const void *__buff, int __len, int __flags);



int setsockopt(int __s, int __level, int __optname, const void *optval, int __optlen);


int socket(int __family, int __type, int __protocol);


struct servent;
# 24 "/usr/include/cygwin/in.h"
enum __nesc_unnamed4280 {

  IPPROTO_IP = 0, 
  IPPROTO_ICMP = 1, 
  IPPROTO_IGMP = 2, 
  IPPROTO_IPIP = 4, 
  IPPROTO_TCP = 6, 
  IPPROTO_EGP = 8, 
  IPPROTO_PUP = 12, 
  IPPROTO_UDP = 17, 
  IPPROTO_IDP = 22, 

  IPPROTO_RAW = 255, 
  IPPROTO_MAX
};

typedef uint16_t in_port_t;

enum __nesc_unnamed4281 {

  IPPORT_ECHO = 7, 
  IPPORT_DISCARD = 9, 
  IPPORT_SYSTAT = 11, 
  IPPORT_DAYTIME = 13, 
  IPPORT_NETSTAT = 15, 
  IPPORT_FTP = 21, 
  IPPORT_TELNET = 23, 
  IPPORT_SMTP = 25, 
  IPPORT_TIMESERVER = 37, 
  IPPORT_NAMESERVER = 42, 
  IPPORT_WHOIS = 43, 
  IPPORT_MTP = 57, 

  IPPORT_TFTP = 69, 
  IPPORT_RJE = 77, 
  IPPORT_FINGER = 79, 
  IPPORT_TTYLINK = 87, 
  IPPORT_SUPDUP = 95, 


  IPPORT_EXECSERVER = 512, 
  IPPORT_LOGINSERVER = 513, 
  IPPORT_CMDSERVER = 514, 
  IPPORT_EFSSERVER = 520, 


  IPPORT_BIFFUDP = 512, 
  IPPORT_WHOSERVER = 513, 
  IPPORT_ROUTESERVER = 520, 


  IPPORT_RESERVED = 1024, 


  IPPORT_USERRESERVED = 5000
};

typedef uint32_t in_addr_t;

struct in_addr {

  unsigned int s_addr;
};



struct ip_mreq {

  struct in_addr imr_multiaddr;
  struct in_addr imr_interface;
};




struct sockaddr_in {

  short int sin_family;
  unsigned short int sin_port;
  struct in_addr sin_addr;


  unsigned char __pad
  [
#line 106
  16 - sizeof(short int )
   - sizeof(unsigned short int ) - sizeof(struct in_addr )];
};
# 35 "/usr/include/asm/byteorder.h" 3
extern unsigned short int ntohs(unsigned short int );
extern unsigned long int htonl(unsigned long int );
extern unsigned short int htons(unsigned short int );
# 175 "/usr/include/cygwin/in.h"
struct in6_addr {

  unsigned char s6_addr[16];
};

struct sockaddr_in6 {

  unsigned short sin6_family;
  unsigned short sin6_port;
  unsigned long sin6_flowinfo;
  struct in6_addr sin6_addr;
};
# 4 "/usr/include/errno.h"
typedef int error_t;
# 15 "/usr/include/sys/errno.h"
extern int *__errno(void );
 
# 46 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.h"
static int socketsInitialized = 0;
static inline void initializeSockets(void);
static inline int readTossimCommand(int clifd, int clidx);
static void buildTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data, 
unsigned char **msgp, int *lenp);
static void sendTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data);
static int writeTossimEvent(void *data, int datalen, int clifd);
static inline 



char *currentTime(void);
static inline int printTime(char *buf, int len);
static int printOtherTime(char *buf, int len, long long int ftime);
# 111 "/usr/lib/gcc-lib/i686-pc-cygwin/3.2/include/stdarg.h" 3
typedef __gnuc_va_list va_list;
# 58 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/GuiMsg.h"
enum __nesc_unnamed4282 {

  AM_DEBUGMSGEVENT = 1, 
  AM_RADIOMSGSENTEVENT = 1 << 1, 
  AM_UARTMSGSENTEVENT = 1 << 2, 
  AM_ADCDATAREADYEVENT = 1 << 3, 
  AM_TOSSIMINITEVENT = 1 << 4, 
  AM_INTERRUPTEVENT = 1 << 5, 
  AM_LEDEVENT = 1 << 6, 






  AM_TURNONMOTECOMMAND = 1 << 12, 
  AM_TURNOFFMOTECOMMAND, 
  AM_RADIOMSGSENDCOMMAND, 
  AM_UARTMSGSENDCOMMAND, 
  AM_SETLINKPROBCOMMAND, 
  AM_SETADCPORTVALUECOMMAND, 
  AM_INTERRUPTCOMMAND, 
  AM_SETRATECOMMAND, 
  AM_SETDBGCOMMAND, 
  AM_VARIABLERESOLVECOMMAND, 
  AM_VARIABLERESOLVERESPONSE, 
  AM_VARIABLEREQUESTCOMMAND, 
  AM_VARIABLEREQUESTRESPONSE, 
  AM_GETMOTECOUNTCOMMAND, 
  AM_GETMOTECOUNTRESPONSE, 
  AM_SETEVENTMASKCOMMAND, 
  AM_BEGINBATCHCOMMAND, 
  AM_ENDBATCHCOMMAND
};







typedef struct GuiMsg {
  uint16_t msgType;
  uint16_t moteID;
  long long time;
  uint16_t payLoadLen;
} GuiMsg;






typedef struct DebugMsgEvent {
  char debugMessage[512];
} DebugMsgEvent;


typedef struct RadioMsgSentEvent {
  TOS_Msg message;
} RadioMsgSentEvent;


typedef struct UARTMsgSentEvent {
  TOS_Msg message;
} UARTMsgSentEvent;


typedef struct ADCDataReadyEvent {
  uint8_t port;
  uint16_t data;
} ADCDataReadyEvent;


typedef struct VariableResolveResponse {
  uint32_t addr;
  uint32_t length;
} VariableResolveResponse;


typedef struct VariableRequestResponse {
  uint32_t length;
  char value[256];
} VariableRequestResponse;


typedef struct TossimInitEvent {
  int numMotes;
  uint8_t radioModel;
  uint32_t rate;
} __attribute((packed))  TossimInitEvent;


typedef struct InterruptEvent {
  uint32_t id;
} InterruptEvent;


typedef struct TurnOnMoteCommand {
} TurnOnMoteCommand;


typedef struct TurnOffMoteCommand {
} TurnOffMoteCommand;


typedef struct RadioMsgSendCommand {
  TOS_Msg message;
} RadioMsgSendCommand;


typedef struct UARTMsgSendCommand {
  TOS_Msg message;
} UARTMsgSendCommand;


typedef struct SetLinkProbCommand {
  uint16_t moteReceiver;
  uint32_t scaledProb;
} SetLinkProbCommand;


typedef struct SetADCPortValueCommand {
  uint8_t port;
  uint16_t value;
} SetADCPortValueCommand;


typedef struct VariableResolveCommand {
  char name[256];
} VariableResolveCommand;


typedef struct VariableRequestCommand {
  uint32_t addr;
  uint8_t length;
} VariableRequestCommand;

typedef struct InterruptCommand {
  uint32_t id;
} InterruptCommand;

typedef struct SetRateCommand {
  uint32_t rate;
} SetRateCommand;

typedef struct LedEvent {
  uint8_t red : 1;
  uint8_t green : 1;
  uint8_t yellow : 1;
} LedEvent;

typedef struct SetDBGCommand {
  long long dbg;
} SetDBGCommand;

typedef struct GetMoteCountCommand {
  uint8_t placeholder;
} GetMoteCountCommand;

typedef struct GetMoteCountResponse {
  uint16_t totalMotes;
  uint8_t bitmask[(TOSNODES + 7) / 8];
} GetMoteCountResponse;

typedef struct SetEventMaskCommand {
  uint16_t mask;
} SetEventMaskCommand;

typedef struct BeginBatchCommand {
} BeginBatchCommand;

typedef struct EndBatchCommand {
} EndBatchCommand;
# 72 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/types/dbg.h"
typedef struct dbg_mode {
  char *d_name;
  unsigned long long d_mode;
} TOS_dbg_mode_names;

TOS_dbg_mode dbg_modes = 0;
 bool dbg_suppress_stdout = 0;

static bool dbg_active(TOS_dbg_mode mode);




static void dbg_add_mode(const char *mode);
static void dbg_add_modes(const char *modes);
static void dbg_init(void );
static void dbg_help(void );

static void dbg_set(TOS_dbg_mode );

static void dbg(TOS_dbg_mode mode, const char *format, ...);
#line 112
static void dbg_clear(TOS_dbg_mode mode, const char *format, ...);
# 68 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.h"
extern  TOS_dbg_mode dbg_modes;
 
TOS_state_t tos_state;
#line 87
typedef uint8_t __nesc_atomic_t;

__inline __nesc_atomic_t  __nesc_atomic_start(void );




__inline void  __nesc_atomic_end(__nesc_atomic_t oldSreg);







enum __nesc_unnamed4283 {
  TOSH_ADC_PORTMAPSIZE = 255
};
# 48 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
const int STARTING_SIZE = 511;



typedef struct node {
  void *data;
  long long key;
} node_t;
static 
void down_heap(heap_t *heap, int findex);
static void up_heap(heap_t *heap, int findex);
static void swap(node_t *first, node_t *second);
static inline 







void init_heap(heap_t *heap);
static inline 








int is_empty(heap_t *heap);
static inline 


int heap_is_empty(heap_t *heap);
static inline 


long long heap_get_min_key(heap_t *heap);
static 
#line 104
void *heap_pop_min_data(heap_t *heap, long long *key);
static inline 
#line 120
void expand_heap(heap_t *heap);
static inline 
#line 134
void heap_insert(heap_t *heap, void *data, long long key);
static 
#line 148
void swap(node_t *first, node_t *second);
static 
#line 161
void down_heap(heap_t *heap, int findex);
static 
#line 187
void up_heap(heap_t *heap, int findex);
 
# 41 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.c"
struct __nesc_unnamed4284 {
  char status_register;
  char register_A;
  char register_B;
  char register_C;
  char register_D;
  char register_E;
  char register_default;
} TOSH_pc_hardware;
static inline 
void init_hardware(void);
static 






short set_io_bit(char port, char bit);
static inline 
#line 98
short clear_io_bit(char port, char bit);
# 47 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/event_queue.c"
struct timespec;
static inline 


void queue_init(event_queue_t *queue, int fpause);
static 




void queue_insert_event(event_queue_t *queue, event_t *event);
static inline 




event_t *queue_pop_event(event_queue_t *queue);
static inline 
#line 86
int queue_is_empty(event_queue_t *queue);
static inline 






long long queue_peek_event_time(event_queue_t *queue);
static inline 
#line 109
void queue_handle_next_event(event_queue_t *queue);
static inline 
# 43 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/events.c"
void event_default_cleanup(event_t *event);
static 



void event_total_cleanup(event_t *event);
static inline 






void event_cleanup(event_t *fevent);
 
# 11 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/powermod.h"
double *cycles;
 int power_init;
 int prof_on;
 int cpu_prof_on;





const float em_VOLTAGE = 2.4;
const float em_CPU_FREQ = 4000000.0;

const float em_RADIO_RX = 18.0;
float em_RADIO_TX[256];
#line 41
const float em_CPU_IDLE = 1.0;
const float em_CPU_ADC_NOISE_REDUCTION = 1.0;
const float em_CPU_POWER_DOWN = 0.001;
const float em_CPU_POWER_SAVE = 0.001;
const float em_CPU_RESERVED = 0.001;
const float em_CPU_STANDBY = 0.001;
const float em_CPU_EXTENDED_STANDBY = 0.001;

float em_CPUCrt[8];
#line 78
const float em_RADIO_DEFAULT_POWER = 14.00;




float batteryEnergy[TOSNODES];
float scavengerCrt;






struct __nesc_unnamed4285 {

  bool on;
  bool tx;
  float txpower;
} 
radioState[TOSNODES];

float radioCrt[TOSNODES];

float CPUCrt[TOSNODES];
int CPUState[TOSNODES];

int PrevCPUCycles[TOSNODES];

float totalCPUEng[TOSNODES];
float totalRadioEng[TOSNODES];

long startSimTime = -1;

FILE *finScavenger;
# 39 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hpl.c"
static int clockScales[8] = { -1, 122, 976, 3906, 7812, 15625, 31250, 125000 };
 
static event_t *clockEvents[TOSNODES];
 static uint8_t intervals[TOSNODES];
 static uint8_t scales[TOSNODES];
 static long long setTime[TOSNODES];
 static uint8_t interruptPending[TOSNODES];
static inline 
void  SIG_OUTPUT_COMPARE2_interrupt(void );
static 





void TOSH_clock_set_interval(uint8_t interval);
static 
#line 86
void TOSH_clock_set_rate(char interval, char scale);
static inline 
#line 115
uint8_t TOSH_get_clock_interval(void);
static 







uint8_t TOSH_get_clock0_counter(void);
#line 154
struct timeval;
static inline 
void event_clocktick_handle(event_t *event, 
struct TOS_state *state);
static 
#line 191
void event_clocktick_create(event_t *event, int mote, long long eventTime, int interval);
static inline 
#line 211
void event_clocktick_invalidate(event_t *event);










enum __nesc_unnamed4286 {
  ADC_LATENCY = 200
};
#line 342
uint8_t radioWaitingState[TOSNODES];
char TOSH_MHSR_start[12] = { 0xf0, 0xf0, 0xf0, 0xff, 0x00, 0xff, 0x0f, 0x00, 0xff, 0x0f, 0x0f, 0x0f };

enum __nesc_unnamed4287 {
  NOT_WAITING = 0, 
  WAITING_FOR_ONE_TO_PASS = 1, 
  WAITING_FOR_ONE_TO_CAPTURE = 2
};
static 
#line 389
uint8_t TOSH_rfm_rx_bit(void );
static inline 







void TOSH_rfm_tx_bit(uint8_t data);
#line 470
void   event_spi_byte_create(event_t *fevent, int mote, long long ftime, int interval, int count);

event_t *spiByteEvents[TOSNODES];

int RADIO_TICKS_PER_EVENT = 100;
# 46 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/dbg.c"
static TOS_dbg_mode_names dbg_nametab[34] = { 
{ "all", DBG_ALL }, { "boot", DBG_BOOT | DBG_ERROR }, { "clock", DBG_CLOCK | DBG_ERROR }, { "task", DBG_TASK | DBG_ERROR }, { "sched", DBG_SCHED | DBG_ERROR }, { "sensor", DBG_SENSOR | DBG_ERROR }, { "led", DBG_LED | DBG_ERROR }, { "crypto", DBG_CRYPTO | DBG_ERROR }, { "route", DBG_ROUTE | DBG_ERROR }, { "am", DBG_AM | DBG_ERROR }, { "crc", DBG_CRC | DBG_ERROR }, { "packet", DBG_PACKET | DBG_ERROR }, { "encode", DBG_ENCODE | DBG_ERROR }, { "radio", DBG_RADIO | DBG_ERROR }, { "logger", DBG_LOG | DBG_ERROR }, { "adc", DBG_ADC | DBG_ERROR }, { "i2c", DBG_I2C | DBG_ERROR }, { "uart", DBG_UART | DBG_ERROR }, { "prog", DBG_PROG | DBG_ERROR }, { "sounder", DBG_SOUNDER | DBG_ERROR }, { "time", DBG_TIME | DBG_ERROR }, { "power", DBG_POWER | DBG_ERROR }, { "sim", DBG_SIM | DBG_ERROR }, { "queue", DBG_QUEUE | DBG_ERROR }, { "simradio", DBG_SIMRADIO | DBG_ERROR }, { "hardware", DBG_HARD | DBG_ERROR }, { "simmem", DBG_MEM | DBG_ERROR }, { "usr1", DBG_USR1 | DBG_ERROR }, { "usr2", DBG_USR2 | DBG_ERROR }, { "usr3", DBG_USR3 | DBG_ERROR }, { "temp", DBG_TEMP | DBG_ERROR }, { "error", DBG_ERROR }, { "none", DBG_NONE }, { (void *)0, DBG_ERROR } };






void dbg_set(TOS_dbg_mode modes);



void dbg_add_mode(const char *name);
#line 84
void dbg_add_modes(const char *modes);








void dbg_init(void );
#line 107
void dbg_help(void );
static 
# 36 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
int64_t bswap_64(int64_t n);
#line 83
int commandServerSocket = -1;
int eventServerSocket = -1;
int commandClients[4];
uint8_t batchState[4];
 int eventClients[4];
 uint16_t eventMask;

pthread_t eventAcceptThread;
pthread_t commandReadThread;
pthread_mutex_t eventClientsLock;
pthread_cond_t eventClientsCond;


TOS_Msg external_comm_msgs_[TOSNODES];
TOS_MsgPtr external_comm_buffers_[TOSNODES];
 static int GUI_enabled;
static 
int createServerSocket(short port);
static inline void *eventAcceptThreadFunc(void *arg);
static inline void *commandReadThreadFunc(void *arg);



static int __nesc_nido_resolve(int __nesc_mote, 
char *varname, 
uintptr_t *addr, size_t *size);
static inline 
#line 125
void initializeSockets(void);
static 
#line 152
int acceptConnection(int servfd);
static 
#line 168
int createServerSocket(short port);
static inline 
#line 225
void waitForGuiConnection(void);
static 
#line 245
int printOtherTime(char *buf, int len, long long int ftime);
static inline 
#line 262
int printTime(char *buf, int len);
static inline 


char *currentTime(void);
static 




void addClient(int *clientSockets, int clifd);
static inline 
#line 286
void sendInitEvent(int clifd);
static inline 
#line 305
void *eventAcceptThreadFunc(void *arg);
#line 339
typedef struct __nesc_unnamed4288 {
  GuiMsg *msg;
  char *payLoad;
} incoming_command_data_t;



void nido_start_mote(uint16_t moteID);
void nido_stop_mote(uint16_t moteID);
TOS_MsgPtr NIDO_received_radio(TOS_MsgPtr packet);
TOS_MsgPtr NIDO_received_uart(TOS_MsgPtr packet);
static inline void set_link_prob_value(uint16_t moteID1, uint16_t moteID2, double prob);
static inline 
void event_command_cleanup(event_t *event);
static inline 




void event_command_in_handle(event_t *event, 
struct TOS_state *state);
static inline void event_command_in_create(event_t *event, 
GuiMsg *msg, 
char *payLoad);
static inline 
#line 382
int processCommand(int clifd, int clidx, GuiMsg *msg, char *payLoad, 
unsigned char **replyMsg, int *replyLen);
static inline 
#line 512
void event_command_in_handle(event_t *event, 
struct TOS_state *state);
static inline 
#line 583
int readTossimCommand(int clifd, int clidx);
static inline 
#line 679
void *commandReadThreadFunc(void *arg);
static 
#line 754
int writeTossimEvent(void *data, int datalen, int clifd);
static 
#line 785
void buildTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data, 
unsigned char **msgp, int *lenp);
static 
#line 845
void sendTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data);
# 32 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/tos.c"
int signaled = 0;

long long rate_checkpoint_time;
double rate_value;

struct timeval startTime;
struct timeval thisTime;
static inline 
void handle_signal(int sig);
static inline 
#line 52
void init_signals(void );
static inline 
#line 72
double get_rate_value(void);
static inline 


void set_rate_value(double rate);
static inline 


void rate_checkpoint(void);
static inline 




void rate_based_wait(void);
static inline 
# 48 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adc_model.c"
void random_adc_init(void);
static inline 
uint16_t random_adc_read(int moteID, uint8_t port, long long ftime);
static inline 


adc_model *create_random_adc_model(void);










enum __nesc_unnamed4289 {
  ADC_NUM_PORTS_PER_NODE = 256
};

uint16_t adcValues[TOSNODES][ADC_NUM_PORTS_PER_NODE];
pthread_mutex_t adcValuesLock;
static inline 
void generic_adc_init(void);
static inline 









uint16_t generic_adc_read(int moteID, uint8_t port, long long ftime);
static inline 
#line 99
adc_model *create_generic_adc_model(void);
static inline 





void set_adc_value(int moteID, uint8_t port, uint16_t value);
# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/spatial_model.c"
point3D *points;
static inline 
void simple_spatial_init(void);
static inline 
#line 63
void simple_spatial_get_position(int moteID, long long ftime, point3D *point);
static inline 





spatial_model *create_simple_spatial_model(void);
# 62 "/usr/include/cygwin/stat.h" 3
struct stat {

  dev_t st_dev;
  ino_t st_ino;
  mode_t st_mode;
  nlink_t st_nlink;
  uid_t st_uid;
  gid_t st_gid;
  dev_t st_rdev;
  off_t st_size;
  timestruc_t st_atim;
  timestruc_t st_mtim;
  timestruc_t st_ctim;
  blksize_t st_blksize;
  blkcnt_t st_blocks;
  long st_spare4[2];
};
# 139 "/usr/include/sys/fcntl.h"
struct flock {
  short l_type;
  short l_whence;
  long l_start;
  long l_len;
  short l_pid;
  short l_xxx;
};



struct eflock {
  short l_type;
  short l_whence;
  long l_start;
  long l_len;
  short l_pid;
  short l_xxx;
  long l_rpid;
  long l_rsys;
};






extern int open(const char *, int , ...);
# 52 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/eeprom.c"
static char *local_filename;
static int numMotes = 0;
static int moteSize = 0;
static int initialized = 0;
static int local_fd = -1;
static 
int createEEPROM(char *file, int motes, int eempromBytes);
static inline 
#line 91
int anonymousEEPROM(int fnumMotes, int eepromSize);
static inline 
#line 104
int namedEEPROM(char *name, int fnumMotes, int eepromSize);
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/sched.c"
typedef struct __nesc_unnamed4290 {
  void (*tp)(void);
} TOSH_sched_entry_T;

enum __nesc_unnamed4291 {






  TOSH_MAX_TASKS = 8, 

  TOSH_TASK_BITMASK = TOSH_MAX_TASKS - 1
};

volatile TOSH_sched_entry_T TOSH_queue[TOSH_MAX_TASKS];
uint8_t TOSH_sched_full;
volatile uint8_t TOSH_sched_free;
#line 92
bool TOS_post(void (*tp)(void));
#line 106
bool  TOS_post(void (*tp)(void));
static 
#line 140
bool TOSH_run_next_task(void);
static 
# 149 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/tos.h"
void *nmemcpy(void *to, const void *from, size_t n);
# 28 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/Ident.h"
enum __nesc_unnamed4292 {

  IDENT_MAX_PROGRAM_NAME_LENGTH = 16
};

typedef struct __nesc_unnamed4293 {

  uint32_t unix_time;
  uint32_t user_hash;
  char program_name[IDENT_MAX_PROGRAM_NAME_LENGTH];
} Ident_t;
# 22 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/lib/NetworkGenericComm/NetworkGenericComm.h"
enum __nesc_unnamed4294 {

  AM_BEACON = 5, 
  AM_DATA = 6
};

enum NODE_ID {
  NODE_SLAVE = 38, 
  NODE_MASTER = 40
};

enum __nesc_unnamed4295 {
  AM_SLAVE = 42, 
  AM_SLAVE2 = 44, 
  AM_SLAVE3 = 46, 
  AM_MASTER = 900, 
  AM_MASTER2 = 1000
};


typedef struct BeaMsg {
  uint8_t comman;
  uint16_t dest;
  uint8_t val;
} BeaMsg;
#line 58
typedef struct AMdata {
  uint8_t data[29];
} AMdata;
typedef AMdata *AMdataPtr;

typedef struct SMPdata {
  uint8_t data;
} SMPdata;
typedef SMPdata *SMPdataPtr;

typedef struct Stacky {
  AMdata top;
  AMdata bottom;
} Stacky;
# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PCRadio.h"
typedef struct __nesc_unnamed4296 {
  TOS_MsgPtr msg;
  int success;
} uart_send_done_data_t;

enum __nesc_unnamed4297 {
  UART_SEND_DELAY = 1600
};



void NIDO_uart_send_done(TOS_MsgPtr fmsg, result_t fsuccess);
static 
# 47 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adjacency_list.c"
link_t *allocate_link(int mote);
static 
#line 78
int adjacency_list_init(void);
# 61 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/rfm_model.c"
char transmitting[TOSNODES];
int radio_active[TOSNODES];
link_t *radio_connectivity[TOSNODES];
pthread_mutex_t radioConnectivityLock;





short radio_heard[TOSNODES];

bool radio_idle_state[TOSNODES];
double noise_prob = 0;

short IDLE_STATE_MASK = 0xffff;
char *lossyFileName = "lossy.nss";
static inline 
bool simple_connected(int moteID1, int moteID2);
static inline 


void simple_init(void);
static inline 








void simple_transmit(int moteID, char bit);
static inline 







void simple_stops_transmit(int moteID);
static inline 









char simple_hears(int moteID);
static inline 
#line 124
link_t *simple_neighbors(int moteID);
static inline 






rfm_model *create_simple_model(void);
static 
#line 194
void static_one_cell_init(void);
static inline 
#line 313
bool lossy_connected(int moteID1, int moteID2);
static inline 
#line 336
void lossy_transmit(int moteID, char bit);
static inline 
#line 357
void lossy_stop_transmit(int moteID);
static inline 
#line 371
char lossy_hears(int moteID);
static inline 
#line 392
int read_lossy_entry(FILE *file, int *mote_one, int *mote_two, double *loss);
static inline 
#line 471
void lossy_init(void);
static inline 
#line 512
link_t *lossy_neighbors(int moteID);
static inline 






rfm_model *create_lossy_model(char *file);
static inline 
#line 550
void set_link_prob_value(uint16_t moteID1, uint16_t moteID2, double prob);
# 57 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/packet_sim.c"
int byteTransmitTime = 8 * 104 * 2;


int backoffLow = 10 * (8 * 104);
int backoffHigh = 20 * (8 * 104);
int txChangeLatency = 30 * (8 * 104);
int preambleLength = 20;
int headerLength = 7;


struct IncomingMsg;

typedef struct IncomingMsg {
  TOS_Msg msg;
  struct IncomingMsg *next;
} IncomingMsg;

TOS_MsgPtr packet_transmitting[TOSNODES];
IncomingMsg *incoming[TOSNODES];
link_t *cc1000_connectivity[TOSNODES];
static 

void event_backoff_create(event_t *event, int node, long long eventTime);
void   event_backoff_handle(event_t *event, struct TOS_state *state);

void   event_start_transmit_handle(event_t *event, struct TOS_state *state);
static inline void event_start_transmit_create(event_t *event, int node, long long eventTime);

void   event_receive_packet_create(event_t *event, int node, long long eventTime, IncomingMsg *msg);
void   event_receive_packet_handle(event_t *event, struct TOS_state *state);

void   event_send_packet_done_create(event_t *event, int node, long long eventTime);
void   event_send_packet_done_handle(event_t *event, struct TOS_state *state);
static inline 
void packet_sim_init(void);
static 
#line 130
void event_backoff_create(event_t *event, int node, long long eventTime);










void   event_backoff_handle(event_t *event, struct TOS_state *state);
static inline 
#line 155
void event_start_transmit_create(event_t *event, int node, long long eventTime);
static 








void corruptPacket(IncomingMsg *msg, int src, int dest);








void   event_start_transmit_handle(event_t *event, struct TOS_state *state);
#line 228
void   event_receive_packet_create(event_t *event, int node, long long eventTime, IncomingMsg *msg);










void   event_receive_packet_handle(event_t *event, struct TOS_state *state);
#line 266
void   event_send_packet_done_create(event_t *event, int node, long long eventTime);










void   event_send_packet_done_handle(event_t *event, struct TOS_state *state);
# 45 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/sensorboards/micasb/sensorboard.h"
enum __nesc_unnamed4298 {
  TOSH_ACTUAL_PHOTO_PORT = 1, 
  TOSH_ACTUAL_TEMP_PORT = 1, 
  TOSH_ACTUAL_MIC_PORT = 2, 
  TOSH_ACTUAL_ACCEL_X_PORT = 3, 
  TOSH_ACTUAL_ACCEL_Y_PORT = 4, 
  TOSH_ACTUAL_MAG_X_PORT = 6, 
  TOSH_ACTUAL_MAG_Y_PORT = 5
};

enum __nesc_unnamed4299 {
  TOS_ADC_PHOTO_PORT = 1, 
  TOS_ADC_TEMP_PORT = 2, 
  TOS_ADC_MIC_PORT = 3, 
  TOS_ADC_ACCEL_X_PORT = 4, 
  TOS_ADC_ACCEL_Y_PORT = 5, 
  TOS_ADC_MAG_X_PORT = 6, 

  TOS_ADC_MAG_Y_PORT = 8
};

enum __nesc_unnamed4300 {
  TOS_MAG_POT_ADDR = 0, 
  TOS_MIC_POT_ADDR = 1
};
# 46 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/lib/Counters/IntMsg.h"
typedef struct IntMsg {
  uint16_t val;
  uint16_t src;
} IntMsg;

enum __nesc_unnamed4301 {
  AM_INTMSG = 4
};
# 39 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.h"
enum __nesc_unnamed4302 {
  TIMER_REPEAT = 0, 
  TIMER_ONE_SHOT = 1, 
  NUM_TIMERS = 2
};
# 34 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.h"
enum __nesc_unnamed4303 {
  TOS_I1024PS = 0, TOS_S1024PS = 3, 
  TOS_I512PS = 1, TOS_S512PS = 3, 
  TOS_I256PS = 3, TOS_S256PS = 3, 
  TOS_I128PS = 7, TOS_S128PS = 3, 
  TOS_I64PS = 15, TOS_S64PS = 3, 
  TOS_I32PS = 31, TOS_S32PS = 3, 
  TOS_I16PS = 63, TOS_S16PS = 3, 
  TOS_I8PS = 127, TOS_S8PS = 3, 
  TOS_I4PS = 255, TOS_S4PS = 3, 
  TOS_I2PS = 15, TOS_S2PS = 7, 
  TOS_I1PS = 31, TOS_S1PS = 7, 
  TOS_I0PS = 0, TOS_S0PS = 0
};
enum __nesc_unnamed4304 {
  DEFAULT_SCALE = 3, DEFAULT_INTERVAL = 255
};
static  result_t Nido$RadioSendMsg$default$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08);
static   void PowerStateM$PowerState$radioStop(void);
static   void PowerStateM$PowerState$radioStart(void);
static   void PowerStateM$PowerState$CPUCycleCheckpoint(void);
static   result_t PowerStateM$PowerState$init(int arg_0xe0ab58, int arg_0xe0aca0);
static   void PowerStateM$PowerState$radioRxMode(void);
static   void PowerStateM$PowerState$radioTxMode(void);
static   result_t PowerStateM$PowerState$stop(void);
static   double PowerStateM$PowerState$get_mote_cycles(int arg_0xe0a748);
static  result_t TOSwqrsM$SendData$sendDone(TOS_MsgPtr arg_0xf10d30, result_t arg_0xf10e80);
static  TOS_MsgPtr TOSwqrsM$ReceiveDataMsg$receive(TOS_MsgPtr arg_0xe14160);
static  result_t TOSwqrsM$StdControl$init(void);
static  result_t TOSwqrsM$StdControl$start(void);
static  result_t TOSwqrsM$StdControl$stop(void);
static  result_t TOSwqrsM$Timer$fired(void);
static   result_t LedsM$Leds$init(void);
static   result_t TimerM$Clock$fire(void);
static  result_t TimerM$StdControl$init(void);
static  result_t TimerM$StdControl$start(void);
static  result_t TimerM$StdControl$stop(void);
static  result_t TimerM$Timer$default$fired(uint8_t arg_0xfa7090);
static  result_t TimerM$Timer$start(uint8_t arg_0xfa7090, char arg_0xf3e578, uint32_t arg_0xf3e6d0);
static  result_t TimerM$Timer$stop(uint8_t arg_0xfa7090);
static   void HPLClock$Clock$setInterval(uint8_t arg_0xfc3648);
static   uint8_t HPLClock$Clock$readCounter(void);
static   result_t HPLClock$Clock$setRate(char arg_0xfc2b48, char arg_0xfc2c88);
static   uint8_t HPLClock$Clock$getInterval(void);
static   uint8_t HPLPowerManagementM$PowerManagement$adjustPower(void);
static  TOS_MsgPtr AMStandard$ReceiveMsg$default$receive(uint8_t arg_0xfe6730, TOS_MsgPtr arg_0xe14160);
static  result_t AMStandard$ActivityTimer$fired(void);
static  result_t AMStandard$UARTSend$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08);
static  TOS_MsgPtr AMStandard$RadioReceive$receive(TOS_MsgPtr arg_0xe14160);
static  result_t AMStandard$Control$init(void);
static  result_t AMStandard$Control$start(void);
static  result_t AMStandard$Control$stop(void);
static  result_t AMStandard$default$sendDone(void);
static  result_t AMStandard$RadioSend$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08);
static  result_t AMStandard$SendMsg$default$sendDone(uint8_t arg_0xfe6178, TOS_MsgPtr arg_0xf10d30, result_t arg_0xf10e80);
static  TOS_MsgPtr AMStandard$UARTReceive$receive(TOS_MsgPtr arg_0xe14160);
static  result_t MicaHighSpeedRadioM$Code$decodeDone(char arg_0x101a2e8, char arg_0x101a428);
static  result_t MicaHighSpeedRadioM$Code$encodeDone(char arg_0x101a830);
static   void MicaHighSpeedRadioM$RadioReceiveCoordinator$default$byte(TOS_MsgPtr arg_0xffba50, uint8_t arg_0xffbba0);
static   void MicaHighSpeedRadioM$RadioReceiveCoordinator$default$startSymbol(uint8_t arg_0xffb340, uint8_t arg_0xffb488, TOS_MsgPtr arg_0xffb5d8);
static  result_t MicaHighSpeedRadioM$SpiByteFifo$dataReady(uint8_t arg_0x1044618);
static  result_t MicaHighSpeedRadioM$Control$init(void);
static  result_t MicaHighSpeedRadioM$Control$start(void);
static  result_t MicaHighSpeedRadioM$Control$stop(void);
static   void MicaHighSpeedRadioM$RadioSendCoordinator$default$byte(TOS_MsgPtr arg_0xffba50, uint8_t arg_0xffbba0);
static   void MicaHighSpeedRadioM$RadioSendCoordinator$default$startSymbol(uint8_t arg_0xffb340, uint8_t arg_0xffb488, TOS_MsgPtr arg_0xffb5d8);
static  result_t MicaHighSpeedRadioM$ChannelMon$idleDetect(void);
static  result_t MicaHighSpeedRadioM$ChannelMon$startSymDetect(void);
static  result_t SecDedEncoding$Code$encode_flush(void);
static  result_t SecDedEncoding$Code$decode(char arg_0x101fe50);
static  result_t SecDedEncoding$Code$encode(char arg_0x101fa58);
static   uint16_t RandomLFSR$Random$rand(void);
static   result_t RandomLFSR$Random$init(void);
static  result_t ChannelMonC$ChannelMon$startSymbolSearch(void);
static  result_t ChannelMonC$ChannelMon$init(void);
static  result_t ChannelMonC$ChannelMon$stopMonitorChannel(void);
static   uint16_t RadioTimingC$RadioTiming$currentTime(void);
static   uint16_t RadioTimingC$RadioTiming$getTiming(void);
static  result_t SpiByteFifoC$SpiByteFifo$send(uint8_t arg_0x1049300);
static  result_t SpiByteFifoC$SpiByteFifo$phaseShift(void);
static  result_t SpiByteFifoC$SpiByteFifo$startReadBytes(uint16_t arg_0x10499c0);
static  result_t SpiByteFifoC$SpiByteFifo$idle(void);
static  result_t SpiByteFifoC$SpiByteFifo$txMode(void);
static  result_t SpiByteFifoC$SpiByteFifo$rxMode(void);
static  TOS_MsgPtr CrcFilter$LowerReceive$receive(TOS_MsgPtr arg_0xe14160);
static  result_t UARTNoCRCPacketM$Control$init(void);
static  result_t UARTNoCRCPacketM$Control$start(void);
static  result_t UARTNoCRCPacketM$Control$stop(void);
static  
# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr Nido$UARTReceiveMsg$receive(TOS_MsgPtr arg_0xe14160);
static   
# 22 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
void Nido$PowerState$CPUCycleCheckpoint(void);
static   
#line 14
result_t Nido$PowerState$init(int arg_0xe0ab58, int arg_0xe0aca0);
static   


result_t Nido$PowerState$stop(void);
static  
# 67 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
result_t Nido$RadioSendMsg$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08);
static  
# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr Nido$RadioReceiveMsg$receive(TOS_MsgPtr arg_0xe14160);
static  
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
result_t Nido$StdControl$init(void);
static  





result_t Nido$StdControl$start(void);
static  






result_t Nido$StdControl$stop(void);
static inline 
# 74 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void Nido$usage(char *progname);
static 



void Nido$help(char *progname);
#line 107
void   event_boot_handle(event_t *fevent, 
struct TOS_state *fstate);
static inline 
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState_Alex_include.h"
void Nido$ReadScavengerProfile(void);
# 124 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
int   main(int argc, char **argv);
#line 406
void   nido_start_mote(uint16_t moteID);
#line 453
void   nido_stop_mote(uint16_t moteID);
#line 468
TOS_MsgPtr   NIDO_received_radio(TOS_MsgPtr packet);









TOS_MsgPtr   NIDO_received_uart(TOS_MsgPtr packet);
static inline   
#line 494
result_t Nido$RadioSendMsg$default$sendDone(TOS_MsgPtr msg, result_t success);



void   packet_sim_transmit_done(TOS_MsgPtr msg);




void   packet_sim_receive_msg(TOS_MsgPtr msg);



void   set_sim_rate(uint32_t rate);







uint32_t   get_sim_rate(void);
static 
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState_Alex_include.h"
void PowerStateM$ReadScavengerProfile(void);
static inline 
# 24 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
int PowerStateM$num_bbs(void);
static inline void PowerStateM$dump_power_details(void);
static inline   
result_t PowerStateM$PowerState$init(int prof, int cpu_prof);
static inline   
#line 63
result_t PowerStateM$PowerState$stop(void);
static   
#line 179
void PowerStateM$PowerState$radioTxMode(void);
static   
#line 195
void PowerStateM$PowerState$radioRxMode(void);
static inline   
#line 225
void PowerStateM$PowerState$radioStart(void);
static inline   
#line 243
void PowerStateM$PowerState$radioStop(void);
static inline 
#line 378
int PowerStateM$num_bbs(void);
static inline 




int PowerStateM$bb_exec_count(int mote, int bb);
static   



double PowerStateM$PowerState$get_mote_cycles(int mote);
static inline 
#line 406
void PowerStateM$print_power_info(void);
static inline 
#line 428
void PowerStateM$dump_power_details(void);
static inline   
#line 456
void PowerStateM$PowerState$CPUCycleCheckpoint(void);
static  
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
result_t TOSwqrsM$CommControl$init(void);
static  





result_t TOSwqrsM$CommControl$start(void);
static  






result_t TOSwqrsM$CommControl$stop(void);
static   
# 56 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Leds.nc"
result_t TOSwqrsM$Leds$init(void);
static  
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
result_t TOSwqrsM$Timer$start(char arg_0xf3e578, uint32_t arg_0xf3e6d0);
static  







result_t TOSwqrsM$Timer$stop(void);
# 86 "types.h"
typedef char TOSwqrsM$eint8;
typedef signed char TOSwqrsM$esint8;
typedef unsigned char TOSwqrsM$euint8;
typedef short TOSwqrsM$eint16;
typedef signed short TOSwqrsM$esint16;
typedef unsigned short TOSwqrsM$euint16;
typedef long TOSwqrsM$eint32;
typedef signed long TOSwqrsM$esint32;
typedef unsigned long TOSwqrsM$euint32;
#line 128
typedef TOSwqrsM$esint16 TOSwqrsM$sample_t;
typedef TOSwqrsM$esint16 TOSwqrsM$stdvar_t;
typedef TOSwqrsM$euint16 TOSwqrsM$stdvaru_t;
# 2 "wqrs.h"
typedef int16_t TOSwqrsM$WFDB_Sample;
typedef int32_t TOSwqrsM$WFDB_Time;
typedef double TOSwqrsM$WFDB_Gain;
typedef double TOSwqrsM$WFDB_Frequency;
# 1 "input.h"
int TOSwqrsM$testinput[1000][163];
# 28 "TOSwqrsM.nc"
static TOSwqrsM$sample_t TOSwqrsM$get_sample_from_core(void);


TOS_Msg TOSwqrsM$datapck[1000];
static inline  
result_t TOSwqrsM$StdControl$init(void);
static inline  





result_t TOSwqrsM$StdControl$start(void);
static inline  








result_t TOSwqrsM$StdControl$stop(void);
static inline  






result_t TOSwqrsM$Timer$fired(void);
static inline  
#line 80
result_t TOSwqrsM$SendData$sendDone(TOS_MsgPtr pMsg, result_t success);
static inline  


TOS_MsgPtr TOSwqrsM$ReceiveDataMsg$receive(TOS_MsgPtr m);
#line 105
static TOSwqrsM$sample_t TOSwqrsM$get_sample_from_core(void);


static unsigned int TOSwqrsM$get_sample_from_core$counter[1000];
# 51 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/LedsM.nc"
uint8_t LedsM$ledsOn[1000];

enum LedsM$__nesc_unnamed4305 {
  LedsM$RED_BIT = 1, 
  LedsM$GREEN_BIT = 2, 
  LedsM$YELLOW_BIT = 4
};
static inline 
void LedsM$updateLeds(void);
static inline   







result_t LedsM$Leds$init(void);
static   
# 41 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
uint8_t TimerM$PowerManagement$adjustPower(void);
static   
# 105 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
void TimerM$Clock$setInterval(uint8_t arg_0xfc3648);
static   
#line 153
uint8_t TimerM$Clock$readCounter(void);
static   
#line 96
result_t TimerM$Clock$setRate(char arg_0xfc2b48, char arg_0xfc2c88);
static   
#line 121
uint8_t TimerM$Clock$getInterval(void);
static  
# 73 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
result_t TimerM$Timer$fired(
# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
uint8_t arg_0xfa7090);









uint32_t TimerM$mState[1000];
uint8_t TimerM$setIntervalFlag[1000];
uint8_t TimerM$mScale[1000];
#line 61
uint8_t TimerM$mInterval[1000];
int8_t TimerM$queue_head[1000];
int8_t TimerM$queue_tail[1000];
uint8_t TimerM$queue_size[1000];
uint8_t TimerM$queue[1000][NUM_TIMERS];
volatile uint16_t TimerM$interval_outstanding[1000];

struct TimerM$timer_s {
  uint8_t type;
  int32_t ticks;
  int32_t ticksLeft;
} TimerM$mTimerList[1000][NUM_TIMERS];

enum TimerM$__nesc_unnamed4306 {
  TimerM$maxTimerInterval = 230
};
static  result_t TimerM$StdControl$init(void);
static inline  








result_t TimerM$StdControl$start(void);
static inline  


result_t TimerM$StdControl$stop(void);
static  





result_t TimerM$Timer$start(uint8_t id, char type, 
uint32_t interval);
#line 129
static void TimerM$adjustInterval(void);
static  
#line 168
result_t TimerM$Timer$stop(uint8_t id);
static inline   
#line 182
result_t TimerM$Timer$default$fired(uint8_t id);
static inline 


void TimerM$enqueue(uint8_t value);
static inline 






uint8_t TimerM$dequeue(void);
static inline  








void TimerM$signalOneTimer(void);
static inline  




void TimerM$HandleFire(void);
static inline   
#line 253
result_t TimerM$Clock$fire(void);
static   
# 180 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
result_t HPLClock$Clock$fire(void);
# 60 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLClock.nc"
char HPLClock$set_flag[1000];
 unsigned char HPLClock$mscale[1000];
 
#line 61
unsigned char HPLClock$nextScale[1000];
 
#line 61
unsigned char HPLClock$minterval[1000];
static inline   
#line 82
void HPLClock$Clock$setInterval(uint8_t value);
static inline   







uint8_t HPLClock$Clock$getInterval(void);
static inline   
#line 113
uint8_t HPLClock$Clock$readCounter(void);
static inline   
#line 128
result_t HPLClock$Clock$setRate(char interval, char scale);
static inline 






void  SIG_OUTPUT_COMPARE2_interrupt(void);
# 50 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLPowerManagementM.nc"
enum HPLPowerManagementM$__nesc_unnamed4307 {
  HPLPowerManagementM$IDLE = 0
};
static inline   
uint8_t HPLPowerManagementM$PowerManagement$adjustPower(void);
static  
# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr AMStandard$ReceiveMsg$receive(
# 56 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xfe6730, 
# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr arg_0xe14160);
static  
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
result_t AMStandard$ActivityTimer$start(char arg_0xf3e578, uint32_t arg_0xf3e6d0);
static  







result_t AMStandard$ActivityTimer$stop(void);
static   
# 41 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
uint8_t AMStandard$PowerManagement$adjustPower(void);
static  
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
result_t AMStandard$RadioControl$init(void);
static  





result_t AMStandard$RadioControl$start(void);
static  






result_t AMStandard$RadioControl$stop(void);
static  
#line 63
result_t AMStandard$TimerControl$init(void);
static  





result_t AMStandard$TimerControl$start(void);
static  
#line 63
result_t AMStandard$UARTControl$init(void);
static  





result_t AMStandard$UARTControl$start(void);
static  






result_t AMStandard$UARTControl$stop(void);
static  
# 65 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$sendDone(void);
static  
# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
result_t AMStandard$SendMsg$sendDone(
# 55 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xfe6178, 
# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
TOS_MsgPtr arg_0xf10d30, result_t arg_0xf10e80);
# 81 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
bool AMStandard$state[1000];

uint16_t AMStandard$lastCount[1000];
uint16_t AMStandard$counter[1000];
static inline  

bool AMStandard$Control$init(void);
static inline  
#line 103
bool AMStandard$Control$start(void);
static inline  
#line 119
bool AMStandard$Control$stop(void);
static inline 
#line 132
void AMStandard$dbgPacket(TOS_MsgPtr data);
static 









result_t AMStandard$reportSendDone(TOS_MsgPtr msg, result_t success);
static inline  






result_t AMStandard$ActivityTimer$fired(void);
static inline   




result_t AMStandard$SendMsg$default$sendDone(uint8_t id, TOS_MsgPtr msg, result_t success);
static inline   

result_t AMStandard$default$sendDone(void);
static inline  
#line 207
result_t AMStandard$UARTSend$sendDone(TOS_MsgPtr msg, result_t success);
static inline  

result_t AMStandard$RadioSend$sendDone(TOS_MsgPtr msg, result_t success);




TOS_MsgPtr   received(TOS_MsgPtr packet);
static inline   
#line 242
TOS_MsgPtr AMStandard$ReceiveMsg$default$receive(uint8_t id, TOS_MsgPtr msg);
static inline  


TOS_MsgPtr AMStandard$UARTReceive$receive(TOS_MsgPtr packet);
static inline  




TOS_MsgPtr AMStandard$RadioReceive$receive(TOS_MsgPtr packet);
static   
# 34 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioTiming.nc"
uint16_t MicaHighSpeedRadioM$RadioTiming$currentTime(void);
static   
#line 33
uint16_t MicaHighSpeedRadioM$RadioTiming$getTiming(void);
static  
# 67 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
result_t MicaHighSpeedRadioM$Send$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08);
static   
# 57 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Random.nc"
result_t MicaHighSpeedRadioM$Random$init(void);
static  
# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
result_t MicaHighSpeedRadioM$Code$encode_flush(void);
static  
result_t MicaHighSpeedRadioM$Code$decode(char arg_0x101fe50);
static  
#line 34
result_t MicaHighSpeedRadioM$Code$encode(char arg_0x101fa58);
static  
# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr MicaHighSpeedRadioM$Receive$receive(TOS_MsgPtr arg_0xe14160);
static   
# 36 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
void MicaHighSpeedRadioM$RadioReceiveCoordinator$byte(TOS_MsgPtr arg_0xffba50, uint8_t arg_0xffbba0);
static   
#line 31
void MicaHighSpeedRadioM$RadioReceiveCoordinator$startSymbol(uint8_t arg_0xffb340, uint8_t arg_0xffb488, TOS_MsgPtr arg_0xffb5d8);
static  
# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
result_t MicaHighSpeedRadioM$SpiByteFifo$send(uint8_t arg_0x1049300);
static  



result_t MicaHighSpeedRadioM$SpiByteFifo$phaseShift(void);
static  
#line 35
result_t MicaHighSpeedRadioM$SpiByteFifo$startReadBytes(uint16_t arg_0x10499c0);
static  
#line 34
result_t MicaHighSpeedRadioM$SpiByteFifo$idle(void);
static  
result_t MicaHighSpeedRadioM$SpiByteFifo$txMode(void);
static  result_t MicaHighSpeedRadioM$SpiByteFifo$rxMode(void);
static   
# 36 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
void MicaHighSpeedRadioM$RadioSendCoordinator$byte(TOS_MsgPtr arg_0xffba50, uint8_t arg_0xffbba0);
static   
#line 31
void MicaHighSpeedRadioM$RadioSendCoordinator$startSymbol(uint8_t arg_0xffb340, uint8_t arg_0xffb488, TOS_MsgPtr arg_0xffb5d8);
static  
# 34 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMon.nc"
result_t MicaHighSpeedRadioM$ChannelMon$startSymbolSearch(void);
static  
#line 33
result_t MicaHighSpeedRadioM$ChannelMon$init(void);
static   
# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
void MicaHighSpeedRadioM$PowerState$radioStop(void);
static   
#line 48
void MicaHighSpeedRadioM$PowerState$radioStart(void);
# 51 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
enum MicaHighSpeedRadioM$__nesc_unnamed4308 {
  MicaHighSpeedRadioM$IDLE_STATE, 
  MicaHighSpeedRadioM$SEND_WAITING, 
  MicaHighSpeedRadioM$RX_STATE, 
  MicaHighSpeedRadioM$TRANSMITTING, 
  MicaHighSpeedRadioM$WAITING_FOR_ACK, 
  MicaHighSpeedRadioM$SENDING_STRENGTH_PULSE, 
  MicaHighSpeedRadioM$TRANSMITTING_START, 
  MicaHighSpeedRadioM$RX_DONE_STATE, 
  MicaHighSpeedRadioM$ACK_SEND_STATE
};

enum MicaHighSpeedRadioM$__nesc_unnamed4309 {
  MicaHighSpeedRadioM$ACK_CNT = 4, 
  MicaHighSpeedRadioM$ENCODE_PACKET_LENGTH_DEFAULT = MSG_DATA_SIZE * 3
};






char MicaHighSpeedRadioM$state[1000];
char MicaHighSpeedRadioM$send_state[1000];
char MicaHighSpeedRadioM$tx_count[1000];
unsigned short MicaHighSpeedRadioM$calc_crc[1000];
uint8_t MicaHighSpeedRadioM$ack_count[1000];
char MicaHighSpeedRadioM$rec_count[1000];
TOS_Msg MicaHighSpeedRadioM$buffer[1000];
TOS_Msg *MicaHighSpeedRadioM$rec_ptr[1000];
TOS_Msg *MicaHighSpeedRadioM$send_ptr[1000];
unsigned char MicaHighSpeedRadioM$rx_count[1000];
char MicaHighSpeedRadioM$msg_length[1000];
char MicaHighSpeedRadioM$buf_head[1000];
char MicaHighSpeedRadioM$buf_end[1000];
char MicaHighSpeedRadioM$encoded_buffer[1000][4];
char MicaHighSpeedRadioM$enc_count[1000];
static 


short MicaHighSpeedRadioM$add_crc_byte(char new_byte, short crc);
static inline  
void MicaHighSpeedRadioM$packetReceived(void);
static inline  






void MicaHighSpeedRadioM$packetSent(void);
static inline  
#line 124
result_t MicaHighSpeedRadioM$Control$stop(void);
static inline  



result_t MicaHighSpeedRadioM$Control$start(void);
static inline  





result_t MicaHighSpeedRadioM$Control$init(void);
static inline  








result_t MicaHighSpeedRadioM$ChannelMon$startSymDetect(void);










result_t   finishedTiming(void);
static inline  









result_t MicaHighSpeedRadioM$ChannelMon$idleDetect(void);
static inline  
#line 187
result_t MicaHighSpeedRadioM$Code$decodeDone(char data, char error);
static  
#line 224
result_t MicaHighSpeedRadioM$Code$encodeDone(char data1);
static  






result_t MicaHighSpeedRadioM$SpiByteFifo$dataReady(uint8_t data);
static 
#line 324
short MicaHighSpeedRadioM$add_crc_byte(char new_byte, short crc);
static inline    
#line 341
void MicaHighSpeedRadioM$RadioSendCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff);
static inline    void MicaHighSpeedRadioM$RadioSendCoordinator$default$byte(TOS_MsgPtr msg, uint8_t byteCount);
static inline    void MicaHighSpeedRadioM$RadioReceiveCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff);
static inline    void MicaHighSpeedRadioM$RadioReceiveCoordinator$default$byte(TOS_MsgPtr msg, uint8_t byteCount);
static  
# 37 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
result_t SecDedEncoding$Code$decodeDone(char arg_0x101a2e8, char arg_0x101a428);
static  result_t SecDedEncoding$Code$encodeDone(char arg_0x101a830);
# 44 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SecDedEncoding.nc"
enum SecDedEncoding$__nesc_unnamed4310 {


  SecDedEncoding$IDLE_STATE = 0, 
  SecDedEncoding$DECODING_BYTE_3 = 1, 
  SecDedEncoding$DECODING_BYTE_2 = 2, 
  SecDedEncoding$DECODING_BYTE_1 = 3, 
  SecDedEncoding$ENCODING_BYTE = 4
};

char SecDedEncoding$data1[1000];
char SecDedEncoding$data2[1000];
char SecDedEncoding$data3[1000];
char SecDedEncoding$state[1000];
static inline 
void SecDedEncoding$radio_decode_thread(void);
static inline void SecDedEncoding$radio_encode_thread(void);
static inline  
result_t SecDedEncoding$Code$decode(char d1);
static inline  
#line 81
result_t SecDedEncoding$Code$encode_flush(void);
static  



result_t SecDedEncoding$Code$encode(char d);
static inline 









void SecDedEncoding$radio_encode_thread(void);
static inline 
#line 155
void SecDedEncoding$radio_decode_thread(void);
# 54 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/RandomLFSR.nc"
uint16_t RandomLFSR$shiftReg[1000];
uint16_t RandomLFSR$initSeed[1000];
uint16_t RandomLFSR$mask[1000];
static inline   

result_t RandomLFSR$Random$init(void);
static inline   









uint16_t RandomLFSR$Random$rand(void);
static   
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Random.nc"
uint16_t ChannelMonC$Random$rand(void);
static  
# 39 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMon.nc"
result_t ChannelMonC$ChannelMon$idleDetect(void);
static  
#line 38
result_t ChannelMonC$ChannelMon$startSymDetect(void);
# 39 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMonC.nc"
enum ChannelMonC$__nesc_unnamed4311 {
  ChannelMonC$IDLE_STATE, 
  ChannelMonC$START_SYMBOL_SEARCH, 
  ChannelMonC$PACKET_START, 
  ChannelMonC$DISABLED_STATE
};

enum ChannelMonC$__nesc_unnamed4312 {
  ChannelMonC$SAMPLE_RATE = 100 / 2 * 4
};
event_t  *channelMonEvents[TOSNODES];
unsigned short ChannelMonC$CM_search[1000][2];
char ChannelMonC$CM_state[1000];
unsigned char ChannelMonC$CM_lastBit[1000];
unsigned char ChannelMonC$CM_startSymBits[1000];
short ChannelMonC$CM_waiting[1000];
static inline  
result_t ChannelMonC$ChannelMon$init(void);
static  



result_t ChannelMonC$ChannelMon$startSymbolSearch(void);
static inline 
#line 88
void  SIG_OUTPUT_COMPARE2B_signal(void);
static  
#line 137
result_t ChannelMonC$ChannelMon$stopMonitorChannel(void);
static inline 
#line 154
void ChannelMonC$event_channel_mon_handle(event_t *fevent, 
struct TOS_state *state);
#line 179
void   event_channel_mon_create(event_t *fevent, int mote, long long ftime, int interval);
#line 196
void   event_channel_mon_invalidate(event_t *fevent);
 
# 41 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioTimingC.nc"
event_t  *radioTimingEvents[TOSNODES];
static inline   
uint16_t RadioTimingC$RadioTiming$getTiming(void);
static inline   
#line 76
uint16_t RadioTimingC$RadioTiming$currentTime(void);





result_t   finishedTiming(void);
static inline 
void RadioTimingC$event_radio_timing_handle(event_t *fevent, 
struct TOS_state *state);
#line 130
void   event_radio_timing_create(event_t *fevent, int mote, long long ftime, int interval);
#line 147
void   event_radio_timing_invalidate(event_t *fevent);
static   
# 46 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
void SpiByteFifoC$PowerState$radioRxMode(void);
static   
#line 45
void SpiByteFifoC$PowerState$radioTxMode(void);
static  
# 40 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
result_t SpiByteFifoC$SpiByteFifo$dataReady(uint8_t arg_0x1044618);
# 39 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
uint8_t SpiByteFifoC$nextByte[1000];
uint8_t SpiByteFifoC$state[1000];
uint8_t SpiByteFifoC$spdr[1000];
uint8_t SpiByteFifoC$radioState[1000];


enum SpiByteFifoC$__nesc_unnamed4313 {
  SpiByteFifoC$IDLE, 
  SpiByteFifoC$FULL, 
  SpiByteFifoC$OPEN, 
  SpiByteFifoC$READING
};

enum SpiByteFifoC$__nesc_unnamed4314 {
  SpiByteFifoC$RADIO_RECEIVING, 
  SpiByteFifoC$RADIO_SENDING, 
  SpiByteFifoC$RADIO_IDLE
};

enum SpiByteFifoC$__nesc_unnamed4315 {
  SpiByteFifoC$TOSH_BIT_RATE = 20 * 4 / 2 * 5 / 4
};
static inline 

void  SIG_SPI_signal(void);
static  





result_t SpiByteFifoC$SpiByteFifo$send(uint8_t data);
static  
#line 101
result_t SpiByteFifoC$SpiByteFifo$idle(void);
static inline  
#line 120
result_t SpiByteFifoC$SpiByteFifo$startReadBytes(uint16_t timing);
static inline  
#line 134
result_t SpiByteFifoC$SpiByteFifo$txMode(void);
static inline  






result_t SpiByteFifoC$SpiByteFifo$rxMode(void);
static inline  








result_t SpiByteFifoC$SpiByteFifo$phaseShift(void);
#line 170
void   event_spi_byte_handle(event_t *fevent, 
struct TOS_state *fstate);
#line 252
void   event_spi_byte_create(event_t *fevent, int mote, long long ftime, int interval, int count);
#line 271
void   event_spi_byte_invalidate(event_t *fevent);




void   event_spi_byte_end(event_t *fevent);
static  
# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr CrcFilter$UpperReceive$receive(TOS_MsgPtr arg_0xe14160);
static inline  
# 52 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/CrcFilter.nc"
TOS_MsgPtr CrcFilter$LowerReceive$receive(TOS_MsgPtr msg);
static  
# 67 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
result_t UARTNoCRCPacketM$Send$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08);
static inline  
# 55 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/UARTNoCRCPacketM.nc"
result_t UARTNoCRCPacketM$Control$init(void);
static inline  



result_t UARTNoCRCPacketM$Control$start(void);
static inline  



result_t UARTNoCRCPacketM$Control$stop(void);
#line 82
void   NIDO_uart_send_done(TOS_MsgPtr fmsg, result_t fsuccess);
static inline 
# 132 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
void AMStandard$dbgPacket(TOS_MsgPtr data)
#line 132
{
  uint8_t i;

  for (i = 0; i < sizeof(TOS_Msg ); i++) 
    {
      dbg_clear(DBG_AM, "%02hhx ", ((uint8_t *)data)[i]);
    }
  dbg_clear(DBG_AM, "\n");
}

static inline  
# 84 "TOSwqrsM.nc"
TOS_MsgPtr TOSwqrsM$ReceiveDataMsg$receive(TOS_MsgPtr m)
#line 84
{

  TOSwqrsM$datapck[tos_state.current_node] = *m;

  TOSwqrsM$datapck[tos_state.current_node].addr = 0xAA00;


  TOSwqrsM$datapck[tos_state.current_node].type = 0x0C;
  TOSwqrsM$datapck[tos_state.current_node].group = 0x35;
  TOSwqrsM$datapck[tos_state.current_node].length = 18;

  TOSwqrsM$datapck[tos_state.current_node].crc = 1;






  return m;
}

static inline   
# 242 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
TOS_MsgPtr AMStandard$ReceiveMsg$default$receive(uint8_t id, TOS_MsgPtr msg)
#line 242
{
  return msg;
}

# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr AMStandard$ReceiveMsg$receive(uint8_t arg_0xfe6730, TOS_MsgPtr arg_0xe14160){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  switch (arg_0xfe6730) {
#line 75
    case AM_DATA:
#line 75
      result = TOSwqrsM$ReceiveDataMsg$receive(arg_0xe14160);
#line 75
      break;
#line 75
    default:
#line 75
      result = AMStandard$ReceiveMsg$default$receive(arg_0xfe6730, arg_0xe14160);
#line 75
    }
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 89 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.h"
__inline __nesc_atomic_t  __nesc_atomic_start(void )
{
  return 0;
}

__inline void  __nesc_atomic_end(__nesc_atomic_t oldSreg)
{
}

static inline 
# 56 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/events.c"
void event_cleanup(event_t *fevent)
{
  dbg(DBG_MEM, "event_cleanup: freeing event: 0x%x\n", (unsigned int )fevent);
  fevent->cleanup(fevent);
}

# 40 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
inline static  result_t SpiByteFifoC$SpiByteFifo$dataReady(uint8_t arg_0x1044618){
#line 40
  unsigned char result;
#line 40

#line 40
  result = MicaHighSpeedRadioM$SpiByteFifo$dataReady(arg_0x1044618);
#line 40

#line 40
  return result;
#line 40
}
#line 40
static inline 
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
void  SIG_SPI_signal(void)
#line 63
{
  uint8_t temp = SpiByteFifoC$spdr[tos_state.current_node];

#line 65
  SpiByteFifoC$spdr[tos_state.current_node] = SpiByteFifoC$nextByte[tos_state.current_node];
  SpiByteFifoC$state[tos_state.current_node] = SpiByteFifoC$OPEN;
  SpiByteFifoC$SpiByteFifo$dataReady(temp);
}

#line 271
void   event_spi_byte_invalidate(event_t *fevent)
#line 271
{
  spi_byte_data_t *data = fevent->data;

#line 273
  data->valid = 0;
}

static inline 
# 398 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hpl.c"
void TOSH_rfm_tx_bit(uint8_t data)
{
  tos_state.rfm->transmit(tos_state.current_node, (char )(data & 0x01));
  dbg(DBG_RADIO, "RFM: Mote %i sent bit %x\n", tos_state.current_node, data & 0x01);
}

static inline 
# 262 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
int printTime(char *buf, int len)
#line 262
{
  return printOtherTime(buf, len, tos_state.tos_time);
}

# 80 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/types/dbg.h"
static bool dbg_active(TOS_dbg_mode mode)
{
  return (dbg_modes & mode) != 0;
}

# 170 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
void   event_spi_byte_handle(event_t *fevent, 
struct TOS_state *fstate)
#line 171
{
  event_t *nevent;
  long long ftime;
  int i;
  event_queue_t *queue = & fstate->queue;
  spi_byte_data_t *data = (spi_byte_data_t *)fevent->data;
  uint8_t temp;
  link_t *current_link;

#line 179
  radioWaitingState[tos_state.current_node] = NOT_WAITING;
  if (data->ending) {
      spiByteEvents[tos_state.current_node] = (void *)0;
      tos_state.rfm->stop_transmit(tos_state.current_node);
      dbg(DBG_RADIO, "RADIO: Spi Byte event ending for mote %i at %lli discarded.\n", data->mote, fevent->time);
      event_cleanup(fevent);
    }
  else {
    if (data->valid) {
        tos_state.rfm->stop_transmit(tos_state.current_node);
        if (dbg_active(DBG_RADIO)) {
            char ttime[128];

#line 191
            ttime[0] = 0;
            printTime(ttime, 128);
            dbg(DBG_RADIO, "RADIO: Spi Byte event handled for mote %i at %s with interval of %i.\n", fevent->mote, ttime, data->interval);
          }


        if (SpiByteFifoC$radioState[tos_state.current_node] == SpiByteFifoC$RADIO_RECEIVING) {
            temp = TOSH_rfm_rx_bit();
            temp &= 0x01;
            SpiByteFifoC$spdr[tos_state.current_node] <<= 1;
            SpiByteFifoC$spdr[tos_state.current_node] |= temp;
          }
        else {
          if (SpiByteFifoC$radioState[tos_state.current_node] == SpiByteFifoC$RADIO_SENDING) {
              temp = (SpiByteFifoC$spdr[tos_state.current_node] >> 0x7) & 0x1;
              TOSH_rfm_tx_bit(temp);
              SpiByteFifoC$spdr[tos_state.current_node] <<= 1;


              if (temp) {
                  current_link = tos_state.rfm->neighbors(tos_state.current_node);
                  while (current_link) {
                      i = current_link->mote;
                      if (radioWaitingState[i] == WAITING_FOR_ONE_TO_CAPTURE && (
                      spiByteEvents[i] == (void *)0 || spiByteEvents[i]->time > tos_state.tos_time + 419)) {
                          if (spiByteEvents[i] != (void *)0) {
                              event_spi_byte_invalidate(spiByteEvents[i]);
                            }
                          dbg(DBG_MEM, "malloc spi byte event.\n");
                          nevent = (event_t *)malloc(sizeof(event_t ));
                          ftime = tos_state.tos_time + 419;
                          event_spi_byte_create(nevent, i, ftime, RADIO_TICKS_PER_EVENT, 0);
                          queue_insert_event(& tos_state.queue, nevent);
#line 223
                          ;

                          spiByteEvents[i] = nevent;
                        }
                      current_link = current_link->next_link;
                    }
                }
            }
          else {
              dbg(DBG_ERROR, "SpiByteFifo is seriously wacked\n");
            }
          }

        if (data->count == 7) {
            SIG_SPI_signal();
          }

        data->count = (data->count + 1) & 0x07;
        fevent->time = fevent->time + data->interval;
        queue_insert_event(queue, fevent);
      }
    else 
      {
        dbg(DBG_RADIO, "RADIO: invalid Spi Byte event for mote %i at %lli discarded.\n", data->mote, fevent->time);

        event_cleanup(fevent);
      }
    }
}

static inline 
# 120 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
void expand_heap(heap_t *heap)
#line 120
{
  int new_size = heap->private_size * 2 + 1;
  void *new_data = malloc(sizeof(node_t ) * new_size);

  dbg(DBG_SIM, "Resized heap from %i to %i.\n", heap->private_size, new_size);

  memcpy(new_data, heap->data, sizeof(node_t ) * heap->private_size);
  free(heap->data);

  heap->data = new_data;
  heap->private_size = new_size;
}

static inline 
void heap_insert(heap_t *heap, void *data, long long key)
#line 134
{
  int findex = heap->size;

#line 136
  if (findex == heap->private_size) {
      expand_heap(heap);
    }

  findex = heap->size;
  ((node_t *)heap->data)[findex].key = key;
  ((node_t *)heap->data)[findex].data = data;
  up_heap(heap, findex);

  heap->size++;
}

# 38 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
inline static  result_t SecDedEncoding$Code$encodeDone(char arg_0x101a830){
#line 38
  unsigned char result;
#line 38

#line 38
  result = MicaHighSpeedRadioM$Code$encodeDone(arg_0x101a830);
#line 38

#line 38
  return result;
#line 38
}
#line 38
static inline 
# 97 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SecDedEncoding.nc"
void SecDedEncoding$radio_encode_thread(void)
#line 97
{
  char ret_high = 0;
  char ret_low = 0;
  char parity = 0;
  char val = SecDedEncoding$data1[tos_state.current_node];




  if ((val & 0x1) != 0) {
      parity ^= 0x5b;
      ret_low |= 0x1;
    }
  else 
#line 109
    {
#line 109
      ret_low |= 0x2;
    }
  if ((val & 0x2) != 0) {
      parity ^= 0x58;
      ret_low |= 0x4;
    }
  else 
#line 114
    {
#line 114
      ret_low |= 0x8;
    }
#line 115
  if ((val & 0x4) != 0) {
      parity ^= 0x52;
      ret_low |= 0x10;
    }
  else 
#line 118
    {
#line 118
      ret_low |= 0x20;
    }
#line 119
  if ((val & 0x8) != 0) {
      parity ^= 0x51;
      ret_low |= 0x40;
    }
  else 
#line 122
    {
#line 122
      ret_low |= 0x80;
    }
#line 123
  if ((val & 0x10) != 0) {
      parity ^= 0x4a;
      ret_high |= 0x1;
    }
  else 
#line 126
    {
#line 126
      ret_high |= 0x2;
    }
#line 127
  if ((val & 0x20) != 0) {
      parity ^= 0x49;
      ret_high |= 0x4;
    }
  else 
#line 130
    {
#line 130
      ret_high |= 0x8;
    }
#line 131
  if ((val & 0x40) != 0) {
      parity ^= 0x13;
      ret_high |= 0x10;
    }
  else 
#line 134
    {
#line 134
      ret_high |= 0x20;
    }
#line 135
  if ((val & 0x80) != 0) {
      parity ^= 0x0b;
      ret_high |= 0x40;
    }
  else 
#line 138
    {
#line 138
      ret_high |= 0x80;
    }



  if (!(parity & 0x40)) {
#line 143
    parity |= 0x80;
    }
#line 144
  if (!(parity & 0x50)) {
#line 144
    parity |= 0x20;
    }
#line 145
  if (!(parity & 0xa)) {
#line 145
    parity |= 0x4;
    }
  SecDedEncoding$state[tos_state.current_node] = SecDedEncoding$IDLE_STATE;
  SecDedEncoding$Code$encodeDone(parity);
  SecDedEncoding$Code$encodeDone(ret_high);
  SecDedEncoding$Code$encodeDone(ret_low);
}

static inline    
# 342 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
void MicaHighSpeedRadioM$RadioSendCoordinator$default$byte(TOS_MsgPtr msg, uint8_t byteCount)
#line 342
{
}

# 36 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
inline static   void MicaHighSpeedRadioM$RadioSendCoordinator$byte(TOS_MsgPtr arg_0xffba50, uint8_t arg_0xffbba0){
#line 36
  MicaHighSpeedRadioM$RadioSendCoordinator$default$byte(arg_0xffba50, arg_0xffbba0);
#line 36
}
#line 36
static inline  
# 81 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SecDedEncoding.nc"
result_t SecDedEncoding$Code$encode_flush(void)
#line 81
{

  return 1;
}

# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
inline static  result_t MicaHighSpeedRadioM$Code$encode_flush(void){
#line 33
  unsigned char result;
#line 33

#line 33
  result = SecDedEncoding$Code$encode_flush();
#line 33

#line 33
  return result;
#line 33
}
#line 33
static inline  
# 152 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
result_t SpiByteFifoC$SpiByteFifo$phaseShift(void)
#line 152
{
  event_t *fevent;
  long long ftime;

#line 155
  if (spiByteEvents[tos_state.current_node] != (void *)0) {
      event_spi_byte_invalidate(spiByteEvents[tos_state.current_node]);
    }
  dbg(DBG_MEM, "malloc spi byte event.\n");
  fevent = (event_t *)malloc(sizeof(event_t ));

  ftime = tos_state.tos_time + RADIO_TICKS_PER_EVENT + 50;
  event_spi_byte_create(fevent, tos_state.current_node, ftime, RADIO_TICKS_PER_EVENT, 0);
  queue_insert_event(& tos_state.queue, fevent);
#line 163
  ;

  spiByteEvents[tos_state.current_node] = fevent;

  return SUCCESS;
}

# 38 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
inline static  result_t MicaHighSpeedRadioM$SpiByteFifo$phaseShift(void){
#line 38
  unsigned char result;
#line 38

#line 38
  result = SpiByteFifoC$SpiByteFifo$phaseShift();
#line 38

#line 38
  return result;
#line 38
}
#line 38
# 272 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.nido.h"
static __inline void TOSH_SET_RFM_CTL1_PIN(void)
#line 272
{
#line 272
  set_io_bit(0x43, 6);
}

#line 271
static __inline void TOSH_SET_RFM_CTL0_PIN(void)
#line 271
{
#line 271
  set_io_bit(0x43, 7);
}

static inline 
# 98 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.c"
short clear_io_bit(char port, char bit)
#line 98
{
  dbg(DBG_HARD, "Clear bit %i of port %u\n", (int )bit, port);
  return 0xff;
}

# 270 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.nido.h"
static __inline void TOSH_MAKE_RFM_TXD_INPUT(void)
#line 270
{
#line 270
  clear_io_bit(0x39, 3);
}

#line 270
static __inline void TOSH_CLR_RFM_TXD_PIN(void)
#line 270
{
#line 270
  clear_io_bit(0x37, 3);
}

# 46 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   void SpiByteFifoC$PowerState$radioRxMode(void){
#line 46
  PowerStateM$PowerState$radioRxMode();
#line 46
}
#line 46
static inline  
# 142 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
result_t SpiByteFifoC$SpiByteFifo$rxMode(void)
#line 142
{
  SpiByteFifoC$radioState[tos_state.current_node] = SpiByteFifoC$RADIO_RECEIVING;
  SpiByteFifoC$PowerState$radioRxMode();
  TOSH_CLR_RFM_TXD_PIN();
  TOSH_MAKE_RFM_TXD_INPUT();
  TOSH_SET_RFM_CTL0_PIN();
  TOSH_SET_RFM_CTL1_PIN();
  return SUCCESS;
}

# 37 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
inline static  result_t MicaHighSpeedRadioM$SpiByteFifo$rxMode(void){
#line 37
  unsigned char result;
#line 37

#line 37
  result = SpiByteFifoC$SpiByteFifo$rxMode();
#line 37

#line 37
  return result;
#line 37
}
#line 37
#line 34
inline static  result_t MicaHighSpeedRadioM$SpiByteFifo$idle(void){
#line 34
  unsigned char result;
#line 34

#line 34
  result = SpiByteFifoC$SpiByteFifo$idle();
#line 34

#line 34
  return result;
#line 34
}
#line 34
# 276 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
void   event_spi_byte_end(event_t *fevent)
#line 276
{
  spi_byte_data_t *data = fevent->data;

#line 278
  data->ending = 1;
}

# 196 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMonC.nc"
void   event_channel_mon_invalidate(event_t *fevent)
#line 196
{
  channel_mon_data_t *data = fevent->data;

#line 198
  data->valid = 0;
}

static inline    
# 343 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
void MicaHighSpeedRadioM$RadioReceiveCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff)
#line 343
{
}

# 31 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
inline static   void MicaHighSpeedRadioM$RadioReceiveCoordinator$startSymbol(uint8_t arg_0xffb340, uint8_t arg_0xffb488, TOS_MsgPtr arg_0xffb5d8){
#line 31
  MicaHighSpeedRadioM$RadioReceiveCoordinator$default$startSymbol(arg_0xffb340, arg_0xffb488, arg_0xffb5d8);
#line 31
}
#line 31
static inline  
# 120 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
result_t SpiByteFifoC$SpiByteFifo$startReadBytes(uint16_t timing)
#line 120
{
  if (SpiByteFifoC$state[tos_state.current_node] == SpiByteFifoC$IDLE) {



      SpiByteFifoC$state[tos_state.current_node] = SpiByteFifoC$READING;
      SpiByteFifoC$radioState[tos_state.current_node] = SpiByteFifoC$RADIO_RECEIVING;
      SpiByteFifoC$PowerState$radioRxMode();
      SpiByteFifoC$spdr[tos_state.current_node] = 0;
      return SUCCESS;
    }
  return FAIL;
}

# 35 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
inline static  result_t MicaHighSpeedRadioM$SpiByteFifo$startReadBytes(uint16_t arg_0x10499c0){
#line 35
  unsigned char result;
#line 35

#line 35
  result = SpiByteFifoC$SpiByteFifo$startReadBytes(arg_0x10499c0);
#line 35

#line 35
  return result;
#line 35
}
#line 35
# 157 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t   finishedTiming(void)
#line 157
{

  MicaHighSpeedRadioM$SpiByteFifo$startReadBytes(0);
  MicaHighSpeedRadioM$msg_length[tos_state.current_node] = MSG_DATA_SIZE - 2;
  MicaHighSpeedRadioM$calc_crc[tos_state.current_node] = 0;
  MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->time = tos_state.tos_time;
  MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->strength = 0;
  return SUCCESS;
}

# 147 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioTimingC.nc"
void   event_radio_timing_invalidate(event_t *fevent)
#line 147
{
  radio_timing_data_t *data = fevent->data;

#line 149
  data->valid = 0;
}

static inline 
#line 84
void RadioTimingC$event_radio_timing_handle(event_t *fevent, 
struct TOS_state *state)
#line 85
{
  event_t *nevent;
  long long ntime;
  event_queue_t *queue = & state->queue;
  radio_timing_data_t *data = (radio_timing_data_t *)fevent->data;

  if (data->valid) {
      if (dbg_active(DBG_RADIO)) {
          char ftime[128];

#line 94
          ftime[0] = 0;
          printTime(ftime, 128);
          dbg(DBG_RADIO, "RADIO: radio timing event handled for mote %i at %s with interval of %i.\n", fevent->mote, ftime, data->interval);
        }


      event_radio_timing_invalidate(fevent);
      radioTimingEvents[tos_state.current_node] = (void *)0;
      fevent->time = fevent->time + data->interval;
      queue_insert_event(queue, fevent);

      radioWaitingState[tos_state.current_node] = WAITING_FOR_ONE_TO_CAPTURE;

      if (spiByteEvents[tos_state.current_node] != (void *)0) {
          event_spi_byte_invalidate(spiByteEvents[tos_state.current_node]);
        }

      dbg(DBG_MEM, "malloc spi byte event.\n");
      nevent = (event_t *)malloc(sizeof(event_t ));

      ntime = tos_state.tos_time + 819;
      event_spi_byte_create(nevent, tos_state.current_node, ntime, RADIO_TICKS_PER_EVENT, 0);
      queue_insert_event(& tos_state.queue, nevent);
#line 116
      ;

      spiByteEvents[tos_state.current_node] = nevent;

      finishedTiming();
    }
  else 
    {
      dbg(DBG_RADIO, "RADIO: invalid radio timing event for mote %i at %lli discarded.\n", data->mote, fevent->time);

      event_cleanup(fevent);
    }
}

void   event_radio_timing_create(event_t *fevent, int mote, long long ftime, int interval)
#line 130
{


  radio_timing_data_t *data = (radio_timing_data_t *)malloc(sizeof(radio_timing_data_t ));

#line 134
  dbg(DBG_MEM, "malloc radio timing event data.\n");
  data->interval = interval;
  data->mote = mote;
  data->valid = 1;

  fevent->mote = mote;
  fevent->data = data;
  fevent->time = ftime;
  fevent->handle = RadioTimingC$event_radio_timing_handle;
  fevent->cleanup = event_total_cleanup;
  fevent->pause = 0;
}

static inline   
#line 43
uint16_t RadioTimingC$RadioTiming$getTiming(void)
#line 43
{
  event_t *fevent;
  long long ftime;

  if (radioTimingEvents[tos_state.current_node] != (void *)0) {
      dbg(DBG_ERROR, "radioTIMING is in bad shape...");
    }

  fevent = (event_t *)malloc(sizeof(event_t ));



  ftime = tos_state.tos_time + 400;
  event_radio_timing_create(fevent, tos_state.current_node, ftime, 0);
  queue_insert_event(& tos_state.queue, fevent);
#line 57
  ;

  radioTimingEvents[tos_state.current_node] = fevent;

  return SUCCESS;
}

# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioTiming.nc"
inline static   uint16_t MicaHighSpeedRadioM$RadioTiming$getTiming(void){
#line 33
  unsigned short result;
#line 33

#line 33
  result = RadioTimingC$RadioTiming$getTiming();
#line 33

#line 33
  return result;
#line 33
}
#line 33
static inline  
# 146 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$ChannelMon$startSymDetect(void)
#line 146
{
  uint16_t tmp;

#line 148
  MicaHighSpeedRadioM$ack_count[tos_state.current_node] = 0;
  MicaHighSpeedRadioM$rec_count[tos_state.current_node] = 0;
  MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$RX_STATE;
  dbg(DBG_PACKET, "Detected start symbol.\n");
  tmp = MicaHighSpeedRadioM$RadioTiming$getTiming();
  MicaHighSpeedRadioM$RadioReceiveCoordinator$startSymbol(8, 0, MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]);
  return SUCCESS;
}

# 38 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMon.nc"
inline static  result_t ChannelMonC$ChannelMon$startSymDetect(void){
#line 38
  unsigned char result;
#line 38

#line 38
  result = MicaHighSpeedRadioM$ChannelMon$startSymDetect();
#line 38

#line 38
  return result;
#line 38
}
#line 38
static inline   
# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/RandomLFSR.nc"
uint16_t RandomLFSR$Random$rand(void)
#line 70
{
  bool endbit;
  uint16_t tmpShiftReg;

#line 73
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 73
    {
      tmpShiftReg = RandomLFSR$shiftReg[tos_state.current_node];
      endbit = (tmpShiftReg & 0x8000) != 0;
      tmpShiftReg <<= 1;
      if (endbit) {
        tmpShiftReg ^= 0x100b;
        }
#line 79
      tmpShiftReg++;
      RandomLFSR$shiftReg[tos_state.current_node] = tmpShiftReg;
      tmpShiftReg = tmpShiftReg ^ RandomLFSR$mask[tos_state.current_node];
    }
#line 82
    __nesc_atomic_end(__nesc_atomic); }
  return tmpShiftReg;
}

# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Random.nc"
inline static   uint16_t ChannelMonC$Random$rand(void){
#line 63
  unsigned short result;
#line 63

#line 63
  result = RandomLFSR$Random$rand();
#line 63

#line 63
  return result;
#line 63
}
#line 63
static inline    
# 341 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
void MicaHighSpeedRadioM$RadioSendCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff)
#line 341
{
}

# 31 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
inline static   void MicaHighSpeedRadioM$RadioSendCoordinator$startSymbol(uint8_t arg_0xffb340, uint8_t arg_0xffb488, TOS_MsgPtr arg_0xffb5d8){
#line 31
  MicaHighSpeedRadioM$RadioSendCoordinator$default$startSymbol(arg_0xffb340, arg_0xffb488, arg_0xffb5d8);
#line 31
}
#line 31
static inline   
# 76 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioTimingC.nc"
uint16_t RadioTimingC$RadioTiming$currentTime(void)
#line 76
{

  return tos_state.tos_time;
}

# 34 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioTiming.nc"
inline static   uint16_t MicaHighSpeedRadioM$RadioTiming$currentTime(void){
#line 34
  unsigned short result;
#line 34

#line 34
  result = RadioTimingC$RadioTiming$currentTime();
#line 34

#line 34
  return result;
#line 34
}
#line 34
# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
inline static  result_t MicaHighSpeedRadioM$SpiByteFifo$send(uint8_t arg_0x1049300){
#line 33
  unsigned char result;
#line 33

#line 33
  result = SpiByteFifoC$SpiByteFifo$send(arg_0x1049300);
#line 33

#line 33
  return result;
#line 33
}
#line 33
# 34 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
inline static  result_t MicaHighSpeedRadioM$Code$encode(char arg_0x101fa58){
#line 34
  unsigned char result;
#line 34

#line 34
  result = SecDedEncoding$Code$encode(arg_0x101fa58);
#line 34

#line 34
  return result;
#line 34
}
#line 34
static inline  
# 168 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$ChannelMon$idleDetect(void)
#line 168
{
  if (MicaHighSpeedRadioM$send_state[tos_state.current_node] == MicaHighSpeedRadioM$SEND_WAITING) {
      char first = ((char *)MicaHighSpeedRadioM$send_ptr[tos_state.current_node])[0];

#line 171
      MicaHighSpeedRadioM$buf_end[tos_state.current_node] = MicaHighSpeedRadioM$buf_head[tos_state.current_node] = 0;
      MicaHighSpeedRadioM$enc_count[tos_state.current_node] = 0;
      MicaHighSpeedRadioM$Code$encode(first);
      MicaHighSpeedRadioM$rx_count[tos_state.current_node] = 0;
      MicaHighSpeedRadioM$msg_length[tos_state.current_node] = (unsigned char )MicaHighSpeedRadioM$send_ptr[tos_state.current_node]->length + MSG_DATA_SIZE - DATA_LENGTH - 2;
      MicaHighSpeedRadioM$send_state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
      MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$TRANSMITTING_START;
      MicaHighSpeedRadioM$SpiByteFifo$send(TOSH_MHSR_start[0]);
      MicaHighSpeedRadioM$send_ptr[tos_state.current_node]->time = MicaHighSpeedRadioM$RadioTiming$currentTime();
      MicaHighSpeedRadioM$calc_crc[tos_state.current_node] = MicaHighSpeedRadioM$add_crc_byte(first, 0x00);
    }

  MicaHighSpeedRadioM$RadioSendCoordinator$startSymbol(8, 0, MicaHighSpeedRadioM$send_ptr[tos_state.current_node]);
  return 1;
}

# 39 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMon.nc"
inline static  result_t ChannelMonC$ChannelMon$idleDetect(void){
#line 39
  unsigned char result;
#line 39

#line 39
  result = MicaHighSpeedRadioM$ChannelMon$idleDetect();
#line 39

#line 39
  return result;
#line 39
}
#line 39
static inline 
# 88 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMonC.nc"
void  SIG_OUTPUT_COMPARE2B_signal(void)
#line 88
{
  uint8_t bit = TOSH_rfm_rx_bit();

  if (ChannelMonC$CM_state[tos_state.current_node] == ChannelMonC$IDLE_STATE) {
      ChannelMonC$CM_search[tos_state.current_node][0] <<= 1;
      ChannelMonC$CM_search[tos_state.current_node][0] = ChannelMonC$CM_search[tos_state.current_node][0] | (bit & 0x1);
      if (ChannelMonC$CM_waiting[tos_state.current_node] != -1) {
          ChannelMonC$CM_waiting[tos_state.current_node]--;
          if (ChannelMonC$CM_waiting[tos_state.current_node] == 1) {
              if ((ChannelMonC$CM_search[tos_state.current_node][0] & 0xfff) == 0) {
                  ChannelMonC$CM_waiting[tos_state.current_node] = -1;
                  ChannelMonC$ChannelMon$stopMonitorChannel();
                  ChannelMonC$ChannelMon$idleDetect();
                }
              else 
#line 101
                {
                  ChannelMonC$CM_waiting[tos_state.current_node] = (ChannelMonC$Random$rand() & 0x1ff) + 50;
                }
            }
        }
      if ((ChannelMonC$CM_search[tos_state.current_node][0] & 0x777) == 0x707) {
          ChannelMonC$CM_state[tos_state.current_node] = ChannelMonC$START_SYMBOL_SEARCH;
          ChannelMonC$CM_search[tos_state.current_node][0] = ChannelMonC$CM_search[tos_state.current_node][1] = 0;
          ChannelMonC$CM_startSymBits[tos_state.current_node] = 30;
        }
    }
  else {
#line 112
    if (ChannelMonC$CM_state[tos_state.current_node] == ChannelMonC$START_SYMBOL_SEARCH) {
        unsigned int current = ChannelMonC$CM_search[tos_state.current_node][ChannelMonC$CM_lastBit[tos_state.current_node]];

#line 114
        ChannelMonC$CM_startSymBits[tos_state.current_node]--;
        if (ChannelMonC$CM_startSymBits[tos_state.current_node] == 0) {
            ChannelMonC$CM_state[tos_state.current_node] = ChannelMonC$IDLE_STATE;
            return;
          }
        current <<= 1;
        current &= 0x1ff;
        if (bit) {
#line 121
          current |= 0x1;
          }
#line 122
        if (current == 0x135) {
            ChannelMonC$ChannelMon$stopMonitorChannel();
            ChannelMonC$CM_state[tos_state.current_node] = ChannelMonC$IDLE_STATE;

            radioWaitingState[tos_state.current_node] = WAITING_FOR_ONE_TO_PASS;

            ChannelMonC$ChannelMon$startSymDetect();
            return;
          }
        ChannelMonC$CM_search[tos_state.current_node][ChannelMonC$CM_lastBit[tos_state.current_node]] = current;
        ChannelMonC$CM_lastBit[tos_state.current_node] ^= 1;
      }
    }
#line 134
  return;
}

static inline 
#line 154
void ChannelMonC$event_channel_mon_handle(event_t *fevent, 
struct TOS_state *state)
#line 155
{
  event_queue_t *queue = & state->queue;
  channel_mon_data_t *data = (channel_mon_data_t *)fevent->data;

#line 158
  if (data->valid) {
      if (dbg_active(DBG_RADIO)) {
          char ftime[128];

#line 161
          ftime[0] = 0;
          printTime(ftime, 128);
          dbg(DBG_RADIO, "RADIO: Channel Mon event handled for mote %i at %s with interval of %i.\n", fevent->mote, ftime, data->interval);
        }


      fevent->time = fevent->time + data->interval;
      queue_insert_event(queue, fevent);

      SIG_OUTPUT_COMPARE2B_signal();
    }
  else {
      dbg(DBG_RADIO, "RADIO: invalid Channel Mon event for mote %i at %lli discarded.\n", data->mote, fevent->time);

      event_cleanup(fevent);
    }
}

void   event_channel_mon_create(event_t *fevent, int mote, long long ftime, int interval)
#line 179
{


  channel_mon_data_t *data = (channel_mon_data_t *)malloc(sizeof(channel_mon_data_t ));

#line 183
  dbg(DBG_MEM, "malloc Channel Mon event data.\n");
  data->interval = interval;
  data->mote = mote;
  data->valid = 1;

  fevent->mote = mote;
  fevent->data = data;
  fevent->time = ftime;
  fevent->handle = ChannelMonC$event_channel_mon_handle;
  fevent->cleanup = event_total_cleanup;
  fevent->pause = 0;
}

static inline  
# 210 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$RadioSend$sendDone(TOS_MsgPtr msg, result_t success)
#line 210
{
  return AMStandard$reportSendDone(msg, success);
}

# 67 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t MicaHighSpeedRadioM$Send$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08){
#line 67
  unsigned char result;
#line 67

#line 67
  result = AMStandard$RadioSend$sendDone(arg_0xe15cb8, arg_0xe15e08);
#line 67

#line 67
  return result;
#line 67
}
#line 67
static inline  
# 101 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
void MicaHighSpeedRadioM$packetSent(void)
#line 101
{
  RadioMsgSentEvent ev;

#line 103
  MicaHighSpeedRadioM$send_state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
  MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
  nmemcpy(& ev.message, MicaHighSpeedRadioM$send_ptr[tos_state.current_node], sizeof  ev.message);
  ev.message.crc = 1;
  sendTossimEvent(tos_state.current_node, AM_RADIOMSGSENTEVENT, tos_state.tos_time, &ev);
  MicaHighSpeedRadioM$Send$sendDone((TOS_MsgPtr )MicaHighSpeedRadioM$send_ptr[tos_state.current_node], SUCCESS);
}

static inline  
# 80 "TOSwqrsM.nc"
result_t TOSwqrsM$SendData$sendDone(TOS_MsgPtr pMsg, result_t success)
#line 80
{
  return SUCCESS;
}

static inline   
# 157 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$SendMsg$default$sendDone(uint8_t id, TOS_MsgPtr msg, result_t success)
#line 157
{
  return SUCCESS;
}

# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
inline static  result_t AMStandard$SendMsg$sendDone(uint8_t arg_0xfe6178, TOS_MsgPtr arg_0xf10d30, result_t arg_0xf10e80){
#line 49
  unsigned char result;
#line 49

#line 49
  switch (arg_0xfe6178) {
#line 49
    case AM_DATA:
#line 49
      result = TOSwqrsM$SendData$sendDone(arg_0xf10d30, arg_0xf10e80);
#line 49
      break;
#line 49
    default:
#line 49
      result = AMStandard$SendMsg$default$sendDone(arg_0xfe6178, arg_0xf10d30, arg_0xf10e80);
#line 49
    }
#line 49

#line 49
  return result;
#line 49
}
#line 49
static inline   
# 160 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$default$sendDone(void)
#line 160
{
  return SUCCESS;
}

#line 65
inline static  result_t AMStandard$sendDone(void){
#line 65
  unsigned char result;
#line 65

#line 65
  result = AMStandard$default$sendDone();
#line 65

#line 65
  return result;
#line 65
}
#line 65
static inline    
# 344 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
void MicaHighSpeedRadioM$RadioReceiveCoordinator$default$byte(TOS_MsgPtr msg, uint8_t byteCount)
#line 344
{
}

# 36 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
inline static   void MicaHighSpeedRadioM$RadioReceiveCoordinator$byte(TOS_MsgPtr arg_0xffba50, uint8_t arg_0xffbba0){
#line 36
  MicaHighSpeedRadioM$RadioReceiveCoordinator$default$byte(arg_0xffba50, arg_0xffbba0);
#line 36
}
#line 36
static inline  
# 187 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$Code$decodeDone(char data, char error)
#line 187
{
  if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$IDLE_STATE) {
      return 0;
    }
  else {
#line 190
    if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$RX_STATE) {
        ((char *)MicaHighSpeedRadioM$rec_ptr[tos_state.current_node])[(int )MicaHighSpeedRadioM$rec_count[tos_state.current_node]] = data;
        MicaHighSpeedRadioM$rec_count[tos_state.current_node]++;
        if (MicaHighSpeedRadioM$rec_count[tos_state.current_node] >= MSG_DATA_SIZE) {

            if (MicaHighSpeedRadioM$calc_crc[tos_state.current_node] == MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->crc) {
                dbg(DBG_CRC, "MicaHighSpeedRadioM: Passed CRC. Expected: 0x%hx, received 0x%hx.\n", MicaHighSpeedRadioM$calc_crc[tos_state.current_node], MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->crc);
                MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->crc = 1;
                if (MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->addr == TOS_LOCAL_ADDRESS || 
                MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->addr == TOS_BCAST_ADDR) {
                    MicaHighSpeedRadioM$SpiByteFifo$send(0x55);
                  }
              }
            else 
#line 202
              {
                dbg(DBG_CRC, "MicaHighSpeedRadioM: Failed CRC. Expected: 0x%hx, received 0x%hx.\n", MicaHighSpeedRadioM$calc_crc[tos_state.current_node], MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->crc);
                MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]->crc = 0;
              }
            MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$ACK_SEND_STATE;
            MicaHighSpeedRadioM$RadioReceiveCoordinator$byte(MicaHighSpeedRadioM$rec_ptr[tos_state.current_node], (uint8_t )MicaHighSpeedRadioM$rec_count[tos_state.current_node]);
            return 0;
          }
        else {
#line 209
          if (MicaHighSpeedRadioM$rec_count[tos_state.current_node] <= MSG_DATA_SIZE - 2) {
              MicaHighSpeedRadioM$calc_crc[tos_state.current_node] = MicaHighSpeedRadioM$add_crc_byte(data, MicaHighSpeedRadioM$calc_crc[tos_state.current_node]);
            }
          }
#line 212
        if (MicaHighSpeedRadioM$rec_count[tos_state.current_node] == LENGTH_BYTE_NUMBER) {
            if ((unsigned char )data < DATA_LENGTH) {
                MicaHighSpeedRadioM$msg_length[tos_state.current_node] = (unsigned char )data + MSG_DATA_SIZE - DATA_LENGTH - 2;
              }
          }
        if (MicaHighSpeedRadioM$rec_count[tos_state.current_node] == MicaHighSpeedRadioM$msg_length[tos_state.current_node]) {
            MicaHighSpeedRadioM$rec_count[tos_state.current_node] = MSG_DATA_SIZE - 2;
          }
      }
    }
#line 221
  return SUCCESS;
}

# 37 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
inline static  result_t SecDedEncoding$Code$decodeDone(char arg_0x101a2e8, char arg_0x101a428){
#line 37
  unsigned char result;
#line 37

#line 37
  result = MicaHighSpeedRadioM$Code$decodeDone(arg_0x101a2e8, arg_0x101a428);
#line 37

#line 37
  return result;
#line 37
}
#line 37
static inline 
# 155 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SecDedEncoding.nc"
void SecDedEncoding$radio_decode_thread(void)
#line 155
{


  char ret_high = 0;
  char ret_low = 0;
  char parity;
  char error = 0;
  short encoded_value = 0;

#line 163
  parity = SecDedEncoding$data1[tos_state.current_node];
  ret_high = SecDedEncoding$data2[tos_state.current_node];
  ret_low = SecDedEncoding$data3[tos_state.current_node];
  if ((ret_low & 0x1) != 0) {
#line 166
    encoded_value |= 0x1;
    }
#line 167
  if ((ret_low & 0x4) != 0) {
#line 167
    encoded_value |= 0x2;
    }
#line 168
  if ((ret_low & 0x10) != 0) {
#line 168
    encoded_value |= 0x4;
    }
#line 169
  if ((ret_low & 0x40) != 0) {
#line 169
    encoded_value |= 0x8;
    }
#line 170
  if ((ret_high & 0x01) != 0) {
#line 170
    encoded_value |= 0x10;
    }
#line 171
  if ((ret_high & 0x04) != 0) {
#line 171
    encoded_value |= 0x20;
    }
#line 172
  if ((ret_high & 0x10) != 0) {
#line 172
    encoded_value |= 0x40;
    }
#line 173
  if ((ret_high & 0x40) != 0) {
#line 173
    encoded_value |= 0x80;
    }
#line 174
  parity = ((parity & 0x3) | ((parity & 0x18) >> 1)) | ((parity & 0x40) >> 2);
  encoded_value = (encoded_value << 5) | parity;


  parity = 0;
  if ((encoded_value & 0x1) != 0) {
#line 179
    parity ^= 0x1;
    }
#line 180
  if ((encoded_value & 0x2) != 0) {
#line 180
    parity ^= 0x2;
    }
#line 181
  if ((encoded_value & 0x4) != 0) {
#line 181
    parity ^= 0x4;
    }
#line 182
  if ((encoded_value & 0x8) != 0) {
#line 182
    parity ^= 0x8;
    }
#line 183
  if ((encoded_value & 0x10) != 0) {
#line 183
    parity ^= 0x10;
    }
#line 184
  if ((encoded_value & 0x20) != 0) {
#line 184
    parity ^= 0x1f;
    }
#line 185
  if ((encoded_value & 0x40) != 0) {
#line 185
    parity ^= 0x1c;
    }
#line 186
  if ((encoded_value & 0x80) != 0) {
#line 186
    parity ^= 0x1a;
    }
#line 187
  if ((encoded_value & 0x100) != 0) {
#line 187
    parity ^= 0x19;
    }
#line 188
  if ((encoded_value & 0x200) != 0) {
#line 188
    parity ^= 0x16;
    }
#line 189
  if ((encoded_value & 0x400) != 0) {
#line 189
    parity ^= 0x15;
    }
#line 190
  if ((encoded_value & 0x800) != 0) {
#line 190
    parity ^= 0xb;
    }
#line 191
  if ((encoded_value & 0x1000) != 0) {
#line 191
    parity ^= 0x7;
    }

  error = -1;
  if (parity == 0) {
    }
  else {
#line 196
    if (parity == 0x1) {
#line 196
        encoded_value ^= 0x1;
      }
    else {
#line 197
      if (parity == 0x2) {
#line 197
          encoded_value ^= 0x2;
        }
      else {
#line 198
        if (parity == 0x4) {
#line 198
            encoded_value ^= 0x4;
          }
        else {
#line 199
          if (parity == 0x8) {
#line 199
              encoded_value ^= 0x8;
            }
          else {
#line 200
            if (parity == 0x10) {
#line 200
                encoded_value ^= 0x10;
              }
            else 
#line 201
              {
                error = 0;
                if (parity == 0x1f) {
#line 203
                    encoded_value ^= 0x20;
                  }
                else {
#line 204
                  if (parity == 0x1c) {
#line 204
                      encoded_value ^= 0x40;
                    }
                  else {
#line 205
                    if (parity == 0x1a) {
#line 205
                        encoded_value ^= 0x80;
                      }
                    else {
#line 206
                      if (parity == 0x19) {
#line 206
                          encoded_value ^= 0x100;
                        }
                      else {
#line 207
                        if (parity == 0x16) {
#line 207
                            encoded_value ^= 0x200;
                          }
                        else {
#line 208
                          if (parity == 0x15) {
#line 208
                              encoded_value ^= 0x400;
                            }
                          else {
#line 209
                            if (parity == 0xb) {
#line 209
                                encoded_value ^= 0x800;
                              }
                            else {
#line 210
                              if (parity == 0x7) {
#line 210
                                  encoded_value ^= 0x1000;
                                }
                              else 
#line 211
                                {
                                  error = 1;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
              }
            }
          }
        }
      }
    }
#line 217
  SecDedEncoding$state[tos_state.current_node] = SecDedEncoding$IDLE_STATE;
  dbg(DBG_ENCODE, "Decoded 0x%x to 0x%hhx with error %i\n", (((SecDedEncoding$data1[tos_state.current_node] << 16) | (SecDedEncoding$data2[tos_state.current_node] << 8)) | SecDedEncoding$data3[tos_state.current_node]) & 0xffffff, (char )((encoded_value >> 5) & 0xff), (int )error);
  SecDedEncoding$Code$decodeDone((encoded_value >> 5) & 0xff, error);
}

static inline  
#line 62
result_t SecDedEncoding$Code$decode(char d1)
#line 62
{
  if (SecDedEncoding$state[tos_state.current_node] == SecDedEncoding$IDLE_STATE) {
      SecDedEncoding$state[tos_state.current_node] = SecDedEncoding$DECODING_BYTE_1;
      SecDedEncoding$data1[tos_state.current_node] = d1;
      return 1;
    }
  else {
#line 67
    if (SecDedEncoding$state[tos_state.current_node] == SecDedEncoding$DECODING_BYTE_1) {
        SecDedEncoding$state[tos_state.current_node] = SecDedEncoding$DECODING_BYTE_2;
        SecDedEncoding$data2[tos_state.current_node] = d1;
        return 1;
      }
    else {
#line 71
      if (SecDedEncoding$state[tos_state.current_node] == SecDedEncoding$DECODING_BYTE_2) {
          SecDedEncoding$state[tos_state.current_node] = SecDedEncoding$DECODING_BYTE_3;
          SecDedEncoding$data3[tos_state.current_node] = d1;
          SecDedEncoding$radio_decode_thread();
          return 1;
        }
      }
    }
#line 77
  return 0;
}

# 35 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/RadioEncoding.nc"
inline static  result_t MicaHighSpeedRadioM$Code$decode(char arg_0x101fe50){
#line 35
  unsigned char result;
#line 35

#line 35
  result = SecDedEncoding$Code$decode(arg_0x101fe50);
#line 35

#line 35
  return result;
#line 35
}
#line 35
# 34 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMon.nc"
inline static  result_t MicaHighSpeedRadioM$ChannelMon$startSymbolSearch(void){
#line 34
  unsigned char result;
#line 34

#line 34
  result = ChannelMonC$ChannelMon$startSymbolSearch();
#line 34

#line 34
  return result;
#line 34
}
#line 34
static inline  
# 252 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
TOS_MsgPtr AMStandard$RadioReceive$receive(TOS_MsgPtr packet)
#line 252
{
  return received(packet);
}

# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr CrcFilter$UpperReceive$receive(TOS_MsgPtr arg_0xe14160){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = AMStandard$RadioReceive$receive(arg_0xe14160);
#line 75

#line 75
  return result;
#line 75
}
#line 75
static inline  
# 52 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/CrcFilter.nc"
TOS_MsgPtr CrcFilter$LowerReceive$receive(TOS_MsgPtr msg)
#line 52
{
  if (msg->crc) {
      dbg(DBG_CRC, "CrcFilter: Packet passed CRC, signaling.\n");
      return CrcFilter$UpperReceive$receive(msg);
    }
  else {
      dbg(DBG_CRC, "CrcFilter: Packet failed CRC.\n");
      return msg;
    }
}

# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr MicaHighSpeedRadioM$Receive$receive(TOS_MsgPtr arg_0xe14160){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = CrcFilter$LowerReceive$receive(arg_0xe14160);
#line 75

#line 75
  return result;
#line 75
}
#line 75
static inline  
# 93 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
void MicaHighSpeedRadioM$packetReceived(void)
#line 93
{
  TOS_MsgPtr tmp;

#line 95
  MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
  tmp = MicaHighSpeedRadioM$Receive$receive((TOS_Msg *)MicaHighSpeedRadioM$rec_ptr[tos_state.current_node]);
  if (tmp != 0) {
#line 97
    MicaHighSpeedRadioM$rec_ptr[tos_state.current_node] = tmp;
    }
#line 98
  MicaHighSpeedRadioM$ChannelMon$startSymbolSearch();
}

# 271 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.nido.h"
static __inline void TOSH_CLR_RFM_CTL0_PIN(void)
#line 271
{
#line 271
  clear_io_bit(0x43, 7);
}

# 45 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   void SpiByteFifoC$PowerState$radioTxMode(void){
#line 45
  PowerStateM$PowerState$radioTxMode();
#line 45
}
#line 45
static inline  
# 134 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
result_t SpiByteFifoC$SpiByteFifo$txMode(void)
#line 134
{
  SpiByteFifoC$radioState[tos_state.current_node] = SpiByteFifoC$RADIO_SENDING;
  SpiByteFifoC$PowerState$radioTxMode();
  TOSH_CLR_RFM_CTL0_PIN();
  TOSH_SET_RFM_CTL1_PIN();
  return SUCCESS;
}

# 36 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifo.nc"
inline static  result_t MicaHighSpeedRadioM$SpiByteFifo$txMode(void){
#line 36
  unsigned char result;
#line 36

#line 36
  result = SpiByteFifoC$SpiByteFifo$txMode();
#line 36

#line 36
  return result;
#line 36
}
#line 36
static inline   
# 494 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
result_t Nido$RadioSendMsg$default$sendDone(TOS_MsgPtr msg, result_t success)
#line 494
{
  return FAIL;
}

# 67 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t Nido$RadioSendMsg$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08){
#line 67
  unsigned char result;
#line 67

#line 67
  result = Nido$RadioSendMsg$default$sendDone(arg_0xe15cb8, arg_0xe15e08);
#line 67

#line 67
  return result;
#line 67
}
#line 67
# 498 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void   packet_sim_transmit_done(TOS_MsgPtr msg)
#line 498
{
  dbg(DBG_PACKET, "TossimPacketMica2M: Send done.\n");
  Nido$RadioSendMsg$sendDone(msg, SUCCESS);
}

# 277 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/packet_sim.c"
void   event_send_packet_done_handle(event_t *event, struct TOS_state *state)
#line 277
{
  TOS_MsgPtr bufferPtr = packet_transmitting[tos_state.current_node];

#line 279
  if (dbg_active(DBG_PACKET)) {
      char timeBuf[128];

#line 281
      printTime(timeBuf, 128);
      dbg(DBG_PACKET, "SIM_PACKET: Send done @%s\n", timeBuf);
    }
  packet_transmitting[tos_state.current_node] = (void *)0;
  packet_sim_transmit_done(bufferPtr);
  event_cleanup(event);
}

#line 266
void   event_send_packet_done_create(event_t *event, int node, long long eventTime)
#line 266
{
  event->mote = node;
  event->force = 0;
  event->pause = 0;
  event->time = eventTime;
  event->handle = event_send_packet_done_handle;
  event->cleanup = event_total_cleanup;
  event->data = (void *)0;
}

# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr Nido$RadioReceiveMsg$receive(TOS_MsgPtr arg_0xe14160){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = AMStandard$RadioReceive$receive(arg_0xe14160);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 503 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void   packet_sim_receive_msg(TOS_MsgPtr msg)
#line 503
{
  msg = Nido$RadioReceiveMsg$receive(msg);
}

# 239 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/packet_sim.c"
void   event_receive_packet_handle(event_t *event, struct TOS_state *state)
#line 239
{
  IncomingMsg *receivedPacket;
  IncomingMsg *prevPacket = (void *)0;
  IncomingMsg *nextPacket = (void *)0;

  receivedPacket = (IncomingMsg *)event->data;

  prevPacket = incoming[tos_state.current_node];
  if (prevPacket == receivedPacket) {
      incoming[tos_state.current_node] = prevPacket->next;
    }
  else {
      while (prevPacket->next != (void *)0) {
          nextPacket = prevPacket->next;
          if (nextPacket == receivedPacket) {
              prevPacket->next = nextPacket->next;
              break;
            }
          prevPacket = nextPacket;
        }
    }

  dbg(DBG_PACKET, "SIM_PACKET: Receiving\n");
  packet_sim_receive_msg(& receivedPacket->msg);
  event_cleanup(event);
}

#line 228
void   event_receive_packet_create(event_t *event, int node, long long eventTime, IncomingMsg *msg)
#line 228
{
  event->mote = node;
  event->force = 0;
  event->pause = 0;
  event->time = eventTime;
  event->handle = event_receive_packet_handle;
  event->cleanup = event_total_cleanup;
  event->data = msg;
}

#line 174
void   event_start_transmit_handle(event_t *event, struct TOS_state *state)
#line 174
{
  link_t *connectLink;
  TOS_MsgPtr msg = packet_transmitting[tos_state.current_node];
  int transmitTime = preambleLength + msg->length + headerLength;

#line 178
  transmitTime *= byteTransmitTime;
  connectLink = cc1000_connectivity[tos_state.current_node];

  dbg(DBG_PACKET, "SIM_PACKET: Transmitting, transmit time is %i.\n", transmitTime);

  while (connectLink != (void *)0) {
      int mote = connectLink->mote;

#line 185
      if (mote >= tos_state.num_nodes || 
      !tos_state.moteOn[mote]) {
          connectLink = connectLink->next_link;
          continue;
        }

      if (packet_transmitting[mote] == (void *)0) {
          event_t *recvEvent = (event_t *)malloc(sizeof(event_t ));

          IncomingMsg *msgEvent = (IncomingMsg *)malloc(sizeof(IncomingMsg ));

#line 195
          nmemcpy(& msgEvent->msg, msg, sizeof(TOS_Msg ));
          dbg(DBG_PACKET, "SIM_PACKET: Mote %i sending to mote %i\n", (int )tos_state.current_node, (int )mote);


          if (incoming[mote] != (void *)0) {
              IncomingMsg *incomingMsg = incoming[mote];

#line 201
              corruptPacket(msgEvent, tos_state.current_node, mote);
              while (incomingMsg != (void *)0) {
                  corruptPacket(incomingMsg, tos_state.current_node, mote);
                  incomingMsg = incomingMsg->next;
                }
            }

          msgEvent->next = incoming[mote];
          incoming[mote] = msgEvent;


          event_receive_packet_create(recvEvent, mote, tos_state.tos_time + transmitTime, msgEvent);
          queue_insert_event(& tos_state.queue, recvEvent);
#line 213
          ;
        }
      else {
          dbg(DBG_PACKET, "SIM_PACKET: Mote %i would send to mote %i, but it is transmitting.\n", (int )tos_state.current_node, (int )mote);
        }
      connectLink = connectLink->next_link;
    }

  dbg(DBG_PACKET, "SIM_PACKET: Enqueueing send done.\n");
  event_send_packet_done_create(event, tos_state.current_node, tos_state.tos_time + transmitTime);
  queue_insert_event(& tos_state.queue, event);
#line 223
  ;
}

static inline 
#line 155
void event_start_transmit_create(event_t *event, int node, long long eventTime)
#line 155
{
  event->mote = node;
  event->force = 0;
  event->pause = 0;
  event->data = (void *)0;
  event->time = eventTime;
  event->handle = event_start_transmit_handle;
  event->cleanup = event_total_cleanup;
}

#line 141
void   event_backoff_handle(event_t *event, struct TOS_state *state)
#line 141
{
  if (incoming[tos_state.current_node] != (void *)0) {
      int backoffAmount = backoffLow;

#line 144
      backoffAmount += rand() % (backoffHigh - backoffLow);
      event_backoff_create(event, tos_state.current_node, tos_state.tos_time + backoffAmount);
      dbg(DBG_PACKET, "SIM_PACKET: Backoff more: %i.\n", backoffAmount);
      queue_insert_event(& tos_state.queue, event);
#line 147
      ;
    }
  else {
      event_start_transmit_create(event, tos_state.current_node, tos_state.tos_time + txChangeLatency);
      queue_insert_event(& tos_state.queue, event);
#line 151
      ;
    }
}

# 107 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void   event_boot_handle(event_t *fevent, 
struct TOS_state *fstate)
#line 108
{
  char timeVal[128];

#line 110
  printTime(timeVal, 128);


  if (!tos_state.cancelBoot[tos_state.current_node]) {
      dbg(DBG_BOOT, "BOOT: Mote booting at time %s.\n", timeVal);
      nido_start_mote((uint16_t )tos_state.current_node);
    }
  else 
#line 116
    {
      dbg(DBG_BOOT, "BOOT: Boot cancelled at time %s since mote turned off.\n", 
      timeVal);
    }
}

static inline 
# 120 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/tos.h"
result_t rcombine(result_t r1, result_t r2)



{
  return r1 == FAIL ? FAIL : r2;
}

static inline   
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/RandomLFSR.nc"
result_t RandomLFSR$Random$init(void)
#line 59
{
  dbg(DBG_BOOT, "RANDOM_LFSR initialized.\n");
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 61
    {
      RandomLFSR$shiftReg[tos_state.current_node] = 119 * 119 * (TOS_LOCAL_ADDRESS + 1);
      RandomLFSR$initSeed[tos_state.current_node] = RandomLFSR$shiftReg[tos_state.current_node];
      RandomLFSR$mask[tos_state.current_node] = 137 * 29 * (TOS_LOCAL_ADDRESS + 1);
    }
#line 65
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 57 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Random.nc"
inline static   result_t MicaHighSpeedRadioM$Random$init(void){
#line 57
  unsigned char result;
#line 57

#line 57
  result = RandomLFSR$Random$init();
#line 57

#line 57
  return result;
#line 57
}
#line 57
static inline  
# 56 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMonC.nc"
result_t ChannelMonC$ChannelMon$init(void)
#line 56
{
  ChannelMonC$CM_waiting[tos_state.current_node] = -1;
  return ChannelMonC$ChannelMon$startSymbolSearch();
}

# 33 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMon.nc"
inline static  result_t MicaHighSpeedRadioM$ChannelMon$init(void){
#line 33
  unsigned char result;
#line 33

#line 33
  result = ChannelMonC$ChannelMon$init();
#line 33

#line 33
  return result;
#line 33
}
#line 33
static inline  
# 136 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$Control$init(void)
#line 136
{
  MicaHighSpeedRadioM$rec_ptr[tos_state.current_node] = &MicaHighSpeedRadioM$buffer[tos_state.current_node];
  MicaHighSpeedRadioM$send_state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
  MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
  return rcombine(MicaHighSpeedRadioM$ChannelMon$init(), MicaHighSpeedRadioM$Random$init());
}

# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$RadioControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = MicaHighSpeedRadioM$Control$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
static inline  
# 55 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/UARTNoCRCPacketM.nc"
result_t UARTNoCRCPacketM$Control$init(void)
#line 55
{
  dbg(DBG_BOOT, "UART initialized.\n");
  return SUCCESS;
}

# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$UARTControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = UARTNoCRCPacketM$Control$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
inline static  result_t AMStandard$TimerControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = TimerM$StdControl$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
static inline  
# 87 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
bool AMStandard$Control$init(void)
#line 87
{
  result_t ok1;
#line 88
  result_t ok2;

  AMStandard$TimerControl$init();
  ok1 = AMStandard$UARTControl$init();
  ok2 = AMStandard$RadioControl$init();

  AMStandard$state[tos_state.current_node] = FALSE;
  AMStandard$lastCount[tos_state.current_node] = 0;
  AMStandard$counter[tos_state.current_node] = 0;
  dbg(DBG_BOOT, "AM Module initialized\n");

  return rcombine(ok1, ok2);
}

# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t TOSwqrsM$CommControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = AMStandard$Control$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
static inline 
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/LedsM.nc"
void LedsM$updateLeds(void)
#line 59
{
  LedEvent e;

#line 61
  e.red = (LedsM$ledsOn[tos_state.current_node] & LedsM$RED_BIT) > 0;
  e.green = (LedsM$ledsOn[tos_state.current_node] & LedsM$GREEN_BIT) > 0;
  e.yellow = (LedsM$ledsOn[tos_state.current_node] & LedsM$YELLOW_BIT) > 0;
  sendTossimEvent(tos_state.current_node, AM_LEDEVENT, tos_state.tos_time, &e);
}

static inline   
result_t LedsM$Leds$init(void)
#line 68
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 69
    {
      LedsM$ledsOn[tos_state.current_node] = 0;
      dbg(DBG_BOOT, "LEDS: initialized.\n");
      LedsM$updateLeds();
    }
#line 73
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 56 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Leds.nc"
inline static   result_t TOSwqrsM$Leds$init(void){
#line 56
  unsigned char result;
#line 56

#line 56
  result = LedsM$Leds$init();
#line 56

#line 56
  return result;
#line 56
}
#line 56
static inline  
# 33 "TOSwqrsM.nc"
result_t TOSwqrsM$StdControl$init(void)
#line 33
{

  TOSwqrsM$Leds$init();
  TOSwqrsM$CommControl$init();
  return SUCCESS;
}

# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t Nido$StdControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = TimerM$StdControl$init();
#line 63
  result = rcombine(result, TOSwqrsM$StdControl$init());
#line 63

#line 63
  return result;
#line 63
}
#line 63
static inline   
# 128 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLClock.nc"
result_t HPLClock$Clock$setRate(char interval, char scale)
#line 128
{
  HPLClock$mscale[tos_state.current_node] = scale;
  HPLClock$minterval[tos_state.current_node] = interval;
  TOSH_clock_set_rate(interval, scale);
  return SUCCESS;
}

# 96 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
inline static   result_t TimerM$Clock$setRate(char arg_0xfc2b48, char arg_0xfc2c88){
#line 96
  unsigned char result;
#line 96

#line 96
  result = HPLClock$Clock$setRate(arg_0xfc2b48, arg_0xfc2c88);
#line 96

#line 96
  return result;
#line 96
}
#line 96
static inline 
# 211 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hpl.c"
void event_clocktick_invalidate(event_t *event)
#line 211
{
  clock_tick_data_t *data = event->data;

#line 213
  data->valid = 0;
}

static inline 
#line 115
uint8_t TOSH_get_clock_interval(void)
#line 115
{
  return intervals[tos_state.current_node] - 1;
}

static inline   
# 91 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLClock.nc"
uint8_t HPLClock$Clock$getInterval(void)
#line 91
{
  return TOSH_get_clock_interval();
}

# 121 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
inline static   uint8_t TimerM$Clock$getInterval(void){
#line 121
  unsigned char result;
#line 121

#line 121
  result = HPLClock$Clock$getInterval();
#line 121

#line 121
  return result;
#line 121
}
#line 121
static inline   
# 54 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLPowerManagementM.nc"
uint8_t HPLPowerManagementM$PowerManagement$adjustPower(void)
#line 54
{
  return HPLPowerManagementM$IDLE;
}

# 41 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
inline static   uint8_t TimerM$PowerManagement$adjustPower(void){
#line 41
  unsigned char result;
#line 41

#line 41
  result = HPLPowerManagementM$PowerManagement$adjustPower();
#line 41

#line 41
  return result;
#line 41
}
#line 41
static inline   
# 82 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLClock.nc"
void HPLClock$Clock$setInterval(uint8_t value)
#line 82
{
  TOSH_clock_set_interval(value);
}

# 105 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
inline static   void TimerM$Clock$setInterval(uint8_t arg_0xfc3648){
#line 105
  HPLClock$Clock$setInterval(arg_0xfc3648);
#line 105
}
#line 105
static inline   
# 113 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLClock.nc"
uint8_t HPLClock$Clock$readCounter(void)
#line 113
{
  return TOSH_get_clock0_counter();
}

# 153 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
inline static   uint8_t TimerM$Clock$readCounter(void){
#line 153
  unsigned char result;
#line 153

#line 153
  result = HPLClock$Clock$readCounter();
#line 153

#line 153
  return result;
#line 153
}
#line 153
# 129 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
static void TimerM$adjustInterval(void)
#line 129
{
  uint8_t i;
#line 130
  uint8_t val = TimerM$maxTimerInterval;

#line 131
  if (TimerM$mState[tos_state.current_node]) {
      for (i = 0; i < NUM_TIMERS; i++) {
          if (TimerM$mState[tos_state.current_node] & (0x1L << i) && TimerM$mTimerList[tos_state.current_node][i].ticksLeft < val) {
              val = TimerM$mTimerList[tos_state.current_node][i].ticksLeft;
            }
        }
#line 148
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 148
        {
          i = TimerM$Clock$readCounter() + 3;
          if (val < i) {
              val = i;
            }
          TimerM$mInterval[tos_state.current_node] = val;
          TimerM$Clock$setInterval(TimerM$mInterval[tos_state.current_node]);
          TimerM$setIntervalFlag[tos_state.current_node] = 0;
        }
#line 156
        __nesc_atomic_end(__nesc_atomic); }
    }
  else {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 159
        {
          TimerM$mInterval[tos_state.current_node] = TimerM$maxTimerInterval;
          TimerM$Clock$setInterval(TimerM$mInterval[tos_state.current_node]);
          TimerM$setIntervalFlag[tos_state.current_node] = 0;
        }
#line 163
        __nesc_atomic_end(__nesc_atomic); }
    }
  TimerM$PowerManagement$adjustPower();
}

static inline 
#line 186
void TimerM$enqueue(uint8_t value)
#line 186
{
  if (TimerM$queue_tail[tos_state.current_node] == NUM_TIMERS - 1) {
    TimerM$queue_tail[tos_state.current_node] = -1;
    }
#line 189
  TimerM$queue_tail[tos_state.current_node]++;
  TimerM$queue_size[tos_state.current_node]++;
  TimerM$queue[tos_state.current_node][(uint8_t )TimerM$queue_tail[tos_state.current_node]] = value;
}

# 105 "TOSwqrsM.nc"
static TOSwqrsM$sample_t TOSwqrsM$get_sample_from_core(void)
{
  TOSwqrsM$sample_t input_d;


  input_d = (TOSwqrsM$sample_t )TOSwqrsM$testinput[tos_state.current_node][TOSwqrsM$get_sample_from_core$counter[tos_state.current_node]++];
  if (TOSwqrsM$get_sample_from_core$counter[tos_state.current_node] == 163) {
      TOSwqrsM$get_sample_from_core$counter[tos_state.current_node] = 0;
    }

  return input_d;
}

static inline  
#line 58
result_t TOSwqrsM$Timer$fired(void)
#line 58
{




  TOSwqrsM$sample_t sample;



  dbg(DBG_USR1, "Timer disparado\n");

  sample = TOSwqrsM$get_sample_from_core();







  return SUCCESS;
}

static inline  
# 151 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$ActivityTimer$fired(void)
#line 151
{
  AMStandard$lastCount[tos_state.current_node] = AMStandard$counter[tos_state.current_node];
  AMStandard$counter[tos_state.current_node] = 0;
  return SUCCESS;
}

static inline   
# 182 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
result_t TimerM$Timer$default$fired(uint8_t id)
#line 182
{
  return SUCCESS;
}

# 73 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t TimerM$Timer$fired(uint8_t arg_0xfa7090){
#line 73
  unsigned char result;
#line 73

#line 73
  switch (arg_0xfa7090) {
#line 73
    case 0:
#line 73
      result = TOSwqrsM$Timer$fired();
#line 73
      break;
#line 73
    case 1:
#line 73
      result = AMStandard$ActivityTimer$fired();
#line 73
      break;
#line 73
    default:
#line 73
      result = TimerM$Timer$default$fired(arg_0xfa7090);
#line 73
    }
#line 73

#line 73
  return result;
#line 73
}
#line 73
static inline 
# 194 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
uint8_t TimerM$dequeue(void)
#line 194
{
  if (TimerM$queue_size[tos_state.current_node] == 0) {
    return NUM_TIMERS;
    }
#line 197
  if (TimerM$queue_head[tos_state.current_node] == NUM_TIMERS - 1) {
    TimerM$queue_head[tos_state.current_node] = -1;
    }
#line 199
  TimerM$queue_head[tos_state.current_node]++;
  TimerM$queue_size[tos_state.current_node]--;
  return TimerM$queue[tos_state.current_node][(uint8_t )TimerM$queue_head[tos_state.current_node]];
}

static inline  void TimerM$signalOneTimer(void)
#line 204
{
  uint8_t itimer = TimerM$dequeue();

#line 206
  if (itimer < NUM_TIMERS) {
    TimerM$Timer$fired(itimer);
    }
}

static inline  
#line 210
void TimerM$HandleFire(void)
#line 210
{
  uint8_t i;
  uint16_t int_out;

#line 213
  TimerM$setIntervalFlag[tos_state.current_node] = 1;


  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 216
    {
      int_out = TimerM$interval_outstanding[tos_state.current_node];
      TimerM$interval_outstanding[tos_state.current_node] = 0;
    }
#line 219
    __nesc_atomic_end(__nesc_atomic); }
  if (TimerM$mState[tos_state.current_node]) {
      for (i = 0; i < NUM_TIMERS; i++) {
          if (TimerM$mState[tos_state.current_node] & (0x1L << i)) {
              TimerM$mTimerList[tos_state.current_node][i].ticksLeft -= int_out;
              if (TimerM$mTimerList[tos_state.current_node][i].ticksLeft <= 2) {


                  if (TOS_post(TimerM$signalOneTimer)) {
                      if (TimerM$mTimerList[tos_state.current_node][i].type == TIMER_REPEAT) {
                          TimerM$mTimerList[tos_state.current_node][i].ticksLeft += TimerM$mTimerList[tos_state.current_node][i].ticks;
                        }
                      else 
#line 230
                        {
                          TimerM$mState[tos_state.current_node] &= ~(0x1L << i);
                        }
                      TimerM$enqueue(i);
                    }
                  else {
                      dbg(DBG_ERROR, "TimerM: Have to wait another timer interval.\n");


                      TimerM$mTimerList[tos_state.current_node][i].ticksLeft = TimerM$mInterval[tos_state.current_node];
                    }
                }
            }
        }
    }


  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 247
    int_out = TimerM$interval_outstanding[tos_state.current_node];
#line 247
    __nesc_atomic_end(__nesc_atomic); }
  if (int_out == 0) {
    TimerM$adjustInterval();
    }
}

static inline   result_t TimerM$Clock$fire(void)
#line 253
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 254
    {



      if (TimerM$interval_outstanding[tos_state.current_node] == 0) {
        TOS_post(TimerM$HandleFire);
        }
      else {
#line 261
        dbg(DBG_ERROR, "Don't post handle fire, we're not ready\n");
        }
      TimerM$interval_outstanding[tos_state.current_node] += TimerM$Clock$getInterval() + 1;
    }
#line 264
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 180 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Clock.nc"
inline static   result_t HPLClock$Clock$fire(void){
#line 180
  unsigned char result;
#line 180

#line 180
  result = TimerM$Clock$fire();
#line 180

#line 180
  return result;
#line 180
}
#line 180
static inline 
# 136 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/HPLClock.nc"
void  SIG_OUTPUT_COMPARE2_interrupt(void)
#line 136
{
  if (HPLClock$set_flag[tos_state.current_node]) {
      HPLClock$mscale[tos_state.current_node] = HPLClock$nextScale[tos_state.current_node];
      HPLClock$nextScale[tos_state.current_node] |= 0x8;
      TOSH_clock_set_rate(HPLClock$minterval[tos_state.current_node], HPLClock$nextScale[tos_state.current_node]);
      HPLClock$set_flag[tos_state.current_node] = 0;
    }
  HPLClock$Clock$fire();
}

static inline 
# 156 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hpl.c"
void event_clocktick_handle(event_t *event, 
struct TOS_state *state)
#line 157
{

  event_queue_t *queue = & state->queue;
  clock_tick_data_t *data = (clock_tick_data_t *)event->data;

#line 161
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 161
    TOS_LOCAL_ADDRESS = (short )(event->mote & 0xffff);
#line 161
    __nesc_atomic_end(__nesc_atomic); }
  setTime[tos_state.current_node] = tos_state.tos_time;

  if (TOS_LOCAL_ADDRESS != event->mote) {
      dbg(DBG_ERROR, "ERROR in clock tick event handler! Things are probably ver bad....\n");
    }

  if (data->valid) {
      if (dbg_active(DBG_CLOCK)) {
          char buf[1024];

#line 171
          printTime(buf, 1024);
          dbg(DBG_CLOCK, "CLOCK: event handled for mote %i at %s (%i ticks).\n", event->mote, buf, data->interval);
        }

      event->time = event->time + data->interval;
      queue_insert_event(queue, event);
      if (! data->disabled) {
          SIG_OUTPUT_COMPARE2_interrupt();
        }
      else {
          interruptPending[tos_state.current_node] = 1;
        }
    }
  else {


      event_cleanup(event);
    }
}

static inline 
# 266 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
char *currentTime(void)
#line 266
{
  static char timeBuf[128];

#line 268
  printTime(timeBuf, 128);
  return timeBuf;
}

# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t TOSwqrsM$Timer$start(char arg_0xf3e578, uint32_t arg_0xf3e6d0){
#line 59
  unsigned char result;
#line 59

#line 59
  result = TimerM$Timer$start(0, arg_0xf3e578, arg_0xf3e6d0);
#line 59

#line 59
  return result;
#line 59
}
#line 59
static inline 
# 133 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/tos.h"
result_t rcombine4(result_t r1, result_t r2, result_t r3, 
result_t r4)
{
  return rcombine(r1, rcombine(r2, rcombine(r3, r4)));
}

# 41 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
inline static   uint8_t AMStandard$PowerManagement$adjustPower(void){
#line 41
  unsigned char result;
#line 41

#line 41
  result = HPLPowerManagementM$PowerManagement$adjustPower();
#line 41

#line 41
  return result;
#line 41
}
#line 41
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t AMStandard$ActivityTimer$start(char arg_0xf3e578, uint32_t arg_0xf3e6d0){
#line 59
  unsigned char result;
#line 59

#line 59
  result = TimerM$Timer$start(1, arg_0xf3e578, arg_0xf3e6d0);
#line 59

#line 59
  return result;
#line 59
}
#line 59
static inline   
# 225 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
void PowerStateM$PowerState$radioStart(void)
#line 225
{
  if (!prof_on) {
#line 226
    return;
    }
#line 227
  dbg(DBG_POWER, "POWER: Mote %d RADIO_STATE ON at %lld\n", tos_state.current_node, 
  tos_state.tos_time);

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 230
    {

      {
#line 232
        float td = (tos_state.tos_time - PrevCPUCycles[tos_state.current_node]) / em_CPU_FREQ;
#line 232
        float engConsumed = td * radioCrt[tos_state.current_node] * em_VOLTAGE;
#line 232
        float engProduced = td * scavengerCrt * em_VOLTAGE;

#line 232
        totalRadioEng[tos_state.current_node] += engConsumed;
#line 232
        batteryEnergy[tos_state.current_node] = batteryEnergy[tos_state.current_node] - engConsumed + engProduced;
#line 232
        printf("Alex - mote %d: totalRadioEng=%.5f radioCrt=%.2f PrevCPUCycles=%d tos_state.tos_time=%lld batteryEnergy=%.2f scavengerCrt=%.2f\n", tos_state.current_node, totalRadioEng[tos_state.current_node], radioCrt[tos_state.current_node], PrevCPUCycles[tos_state.current_node], tos_state.tos_time, batteryEnergy[tos_state.current_node], scavengerCrt);
#line 232
        if (tos_state.tos_time - PrevCPUCycles[tos_state.current_node] >= 4000000) {
#line 232
          PowerStateM$ReadScavengerProfile();
          }
#line 232
        if (1) {
#line 232
          PrevCPUCycles[tos_state.current_node] = tos_state.tos_time;
          }
      }
#line 232
      ;

      radioState[tos_state.current_node].on = 1;

      radioState[tos_state.current_node].tx = 0;
      radioCrt[tos_state.current_node] = em_RADIO_RX;

      radioState[tos_state.current_node].txpower = em_RADIO_DEFAULT_POWER;
    }
#line 240
    __nesc_atomic_end(__nesc_atomic); }
}

# 48 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   void MicaHighSpeedRadioM$PowerState$radioStart(void){
#line 48
  PowerStateM$PowerState$radioStart();
#line 48
}
#line 48
static inline  
# 129 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$Control$start(void)
#line 129
{
  MicaHighSpeedRadioM$PowerState$radioStart();
  return SUCCESS;
}

# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$RadioControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = MicaHighSpeedRadioM$Control$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
static inline  
# 60 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/UARTNoCRCPacketM.nc"
result_t UARTNoCRCPacketM$Control$start(void)
#line 60
{
  dbg(DBG_BOOT, "UART started.\n");
  return SUCCESS;
}

# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$UARTControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = UARTNoCRCPacketM$Control$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
static inline  
# 87 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
result_t TimerM$StdControl$start(void)
#line 87
{
  return SUCCESS;
}

# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$TimerControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = TimerM$StdControl$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
static inline  
# 103 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
bool AMStandard$Control$start(void)
#line 103
{
  result_t ok0 = AMStandard$TimerControl$start();
  result_t ok1 = AMStandard$UARTControl$start();
  result_t ok2 = AMStandard$RadioControl$start();
  result_t ok3 = AMStandard$ActivityTimer$start(TIMER_REPEAT, 1000);



  AMStandard$state[tos_state.current_node] = FALSE;

  AMStandard$PowerManagement$adjustPower();

  return rcombine4(ok0, ok1, ok2, ok3);
}

# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t TOSwqrsM$CommControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = AMStandard$Control$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
static inline  
# 40 "TOSwqrsM.nc"
result_t TOSwqrsM$StdControl$start(void)
#line 40
{

  TOSwqrsM$CommControl$start();
  if (TOS_LOCAL_ADDRESS != 0) {

      TOSwqrsM$Timer$start(TIMER_REPEAT, 100);
    }
  return SUCCESS;
}

# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t Nido$StdControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = TimerM$StdControl$start();
#line 70
  result = rcombine(result, TOSwqrsM$StdControl$start());
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 107 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/dbg.c"
void dbg_help(void )
#line 107
{
  int i = 0;

#line 109
  printf("Known dbg modes: ");

  while (dbg_nametab[i].d_name != (void *)0) {
      printf("%s", dbg_nametab[i].d_name);
      if (dbg_nametab[i + 1].d_name != (void *)0) {
          printf(", ");
        }
      i++;
    }

  printf("\n");
}

static inline 
# 74 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void Nido$usage(char *progname)
#line 74
{
  fprintf(_impure_ptr->_stderr, "Usage: %s [-h|--help] [options] num_nodes_total\n", progname);
  exit(-1);
}

# 58 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/dbg.c"
void dbg_add_mode(const char *name)
#line 58
{
  int cancel;
  TOS_dbg_mode_names *mode;

  if (*name == '-') {
      cancel = 1;
      name++;
    }
  else {
    cancel = 0;
    }
  for (mode = dbg_nametab; mode->d_name != (void *)0; mode++) 
    if (strcmp(name, mode->d_name) == 0) {
      break;
      }
#line 72
  if (mode->d_name == (void *)0) {
      fprintf(_impure_ptr->_stderr, "Warning: Unknown debug option: "
      "\"%s\"\n", name);
      return;
    }

  if (cancel) {
    dbg_modes &= ~ mode->d_mode;
    }
  else {
#line 81
    dbg_modes |= mode->d_mode;
    }
}

#line 84
void dbg_add_modes(const char *modes)
#line 84
{
  char env[256];
  char *name;

  strncpy(env, modes, sizeof env);
  for (name = strtok(env, ","); name; name = strtok((void *)0, ",")) 
    dbg_add_mode(name);
}

void dbg_init(void )
#line 93
{
  const char *dbg_env;

  dbg_modes = DBG_NONE;

  dbg_env = getenv("DBG");
  if (!dbg_env) {
      dbg_modes = DBG_DEFAULT;
      return;
    }

  dbg_add_modes(dbg_env);
}

static inline 
# 378 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
int PowerStateM$num_bbs(void)
#line 378
{

  int POWERPROF_NUM_BBS;

#line 381
  return POWERPROF_NUM_BBS;
}

static inline   
#line 27
result_t PowerStateM$PowerState$init(int prof, int cpu_prof)
#line 27
{
  FILE *cycle_file;
  char cycle_map[13] = "bb_cycle_map";
  int bb;
  double bbcyc;

#line 32
  if (power_init == 1) {
      fprintf(_impure_ptr->_stderr, "PowerState.init() called twice...\n");
      return SUCCESS;
    }

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 37
    {
      {
#line 38
        int i;

#line 38
        for (i = 0; i < 256; i++) em_RADIO_TX[i] = -1.0;
      }
#line 38
      em_RADIO_TX[0] = 8.8;
#line 38
      em_RADIO_TX[1] = 9.0;
#line 38
      em_RADIO_TX[2] = 9.0;
#line 38
      em_RADIO_TX[3] = 10.0;
#line 38
      em_RADIO_TX[4] = 10.0;
#line 38
      em_RADIO_TX[5] = 10.0;
#line 38
      em_RADIO_TX[6] = 11.0;
#line 38
      em_RADIO_TX[7] = 11.0;
#line 38
      em_RADIO_TX[8] = 12.0;
#line 38
      em_RADIO_TX[9] = 12.0;
#line 38
      em_RADIO_TX[10] = 12.0;
#line 38
      em_RADIO_TX[11] = 13.0;
#line 38
      em_RADIO_TX[12] = 13.0;
#line 38
      em_RADIO_TX[14] = 14.0;
#line 38
      em_RADIO_TX[15] = 14.0;
#line 38
      em_RADIO_TX[64] = 14.0;
#line 38
      em_RADIO_TX[80] = 14.0;
#line 38
      em_RADIO_TX[96] = 14.0;
#line 38
      em_RADIO_TX[112] = 14.0;
#line 38
      em_RADIO_TX[128] = 14.0;
#line 38
      em_RADIO_TX[144] = 14.0;
#line 38
      em_RADIO_TX[192] = 14.0;
#line 38
      em_RADIO_TX[224] = 14.0;
#line 38
      em_RADIO_TX[255] = 14.0;
#line 38
      em_CPUCrt[0] = em_CPU_IDLE;
#line 38
      em_CPUCrt[1] = em_CPU_ADC_NOISE_REDUCTION;
#line 38
      em_CPUCrt[2] = em_CPU_POWER_DOWN;
#line 38
      em_CPUCrt[3] = em_CPU_POWER_SAVE;
#line 38
      em_CPUCrt[4] = em_CPU_RESERVED;
#line 38
      em_CPUCrt[5] = em_CPU_RESERVED;
#line 38
      em_CPUCrt[6] = em_CPU_STANDBY;
#line 38
      em_CPUCrt[7] = em_CPU_EXTENDED_STANDBY;
#line 38
      ;
    }
#line 39
    __nesc_atomic_end(__nesc_atomic); }

  power_init = 1;
  prof_on = prof;
  cpu_prof_on = cpu_prof;

  if (cpu_prof_on) {
      cycle_file = fopen(cycle_map, "r");
      if (!cycle_file) {
          fprintf(_impure_ptr->_stderr, "Couldn't open '%s', exiting\n", cycle_map);
          exit(-1);
        }

      cycles = calloc(PowerStateM$num_bbs(), sizeof(double ));

      while (-1 != fscanf(cycle_file, " %d %lf", &bb, &bbcyc)) {
          cycles[bb] = bbcyc;
        }
      fclose(cycle_file);
    }
  return SUCCESS;
}

# 14 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   result_t Nido$PowerState$init(int arg_0xe0ab58, int arg_0xe0aca0){
#line 14
  unsigned char result;
#line 14

#line 14
  result = PowerStateM$PowerState$init(arg_0xe0ab58, arg_0xe0aca0);
#line 14

#line 14
  return result;
#line 14
}
#line 14
static inline 
# 40 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/tos.c"
void handle_signal(int sig)
#line 40
{
  if ((sig == 2 || sig == 17) && signaled == 0) {
      char ftime[128];

#line 43
      printTime(ftime, 128);
      printf("Exiting on SIGINT at %s.\n", ftime);


      signaled = 1;
      exit(0);
    }
}

static inline void init_signals(void )
#line 52
{
  struct sigaction action;

#line 54
  action.sa_handler = handle_signal;
  sigemptyset(& action.sa_mask);
  action.sa_flags = 0;
  sigaction(2, &action, (void *)0);
  signal(13, (_sig_func_ptr )1);
}

static inline 
# 124 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/rfm_model.c"
link_t *simple_neighbors(int moteID)
#line 124
{
  link_t *thelink;

#line 126
  pthread_mutex_lock(&radioConnectivityLock);
  thelink = radio_connectivity[moteID];
  pthread_mutex_unlock(&radioConnectivityLock);
  return thelink;
}

static inline 
#line 78
bool simple_connected(int moteID1, int moteID2)
#line 78
{
  return TRUE;
}

static inline 
#line 112
char simple_hears(int moteID)
#line 112
{







  return radio_active[moteID] > 0 ? 1 : 0;
}

static inline 
#line 101
void simple_stops_transmit(int moteID)
#line 101
{
  int i;

  if (transmitting[moteID]) {
      transmitting[moteID] = 0;
      for (i = 0; i < tos_state.num_nodes; i++) {
          radio_active[i]--;
        }
    }
}

static inline 
#line 92
void simple_transmit(int moteID, char bit)
#line 92
{
  int i;

  transmitting[moteID] = bit;
  for (i = 0; i < tos_state.num_nodes; i++) {
      radio_active[i] += bit;
    }
}

static inline 
#line 82
void simple_init(void)
#line 82
{
  int i;

#line 84
  pthread_mutex_init(&radioConnectivityLock, (void *)0);
  adjacency_list_init();
  static_one_cell_init();
  for (i = 0; i < tos_state.num_nodes; i++) {
      radio_active[i] = 0;
    }
}

static inline 
#line 132
rfm_model *create_simple_model(void)
#line 132
{
  rfm_model *model = (rfm_model *)malloc(sizeof(rfm_model ));

#line 134
  model->init = simple_init;
  model->transmit = simple_transmit;
  model->stop_transmit = simple_stops_transmit;
  model->hears = simple_hears;
  model->connected = simple_connected;
  model->neighbors = simple_neighbors;
  return model;
}

static inline 
#line 512
link_t *lossy_neighbors(int moteID)
#line 512
{
  link_t *thelink;

#line 514
  pthread_mutex_lock(&radioConnectivityLock);
  thelink = radio_connectivity[moteID];
  pthread_mutex_unlock(&radioConnectivityLock);
  return thelink;
}

static inline 
#line 313
bool lossy_connected(int moteID1, int moteID2)
#line 313
{




  link_t *current_link;

  pthread_mutex_lock(&radioConnectivityLock);
  current_link = radio_connectivity[moteID1];
  dbg(DBG_TEMP, "connections for %i\n", moteID1);
  while (current_link) {
      if (current_link->mote == moteID2 && 
      current_link->data < 1.0) {
          dbg(DBG_TEMP, "connected to %i\n", moteID2);
          pthread_mutex_unlock(&radioConnectivityLock);
          return TRUE;
        }
      current_link = current_link->next_link;
    }
  pthread_mutex_unlock(&radioConnectivityLock);
  return FALSE;
}

static inline 
#line 371
char lossy_hears(int moteID)
#line 371
{
  char bit_heard = radio_active[moteID] > 0 ? 1 : 0;

#line 373
  if (radio_idle_state[moteID]) {
      int r = rand() % 100000;
      double prob = (double )r / 100000.0;

#line 376
      if (prob < noise_prob) {
          bit_heard = bit_heard ? 0 : 1;
        }
    }
  else {
      short temp_heard = radio_heard[moteID];

#line 382
      temp_heard <<= 1;
      temp_heard |= bit_heard;
      radio_heard[moteID] = temp_heard;
      if ((radio_heard[moteID] & IDLE_STATE_MASK) == 0) {
          radio_idle_state[moteID] = 1;
        }
    }
  return bit_heard;
}

static inline 
#line 357
void lossy_stop_transmit(int moteID)
#line 357
{
  link_t *current_link;

  pthread_mutex_lock(&radioConnectivityLock);
  current_link = radio_connectivity[moteID];
  transmitting[moteID] = 0;
  while (current_link) {
      radio_active[current_link->mote] -= current_link->bit;
      current_link->bit = 0;
      current_link = current_link->next_link;
    }
  pthread_mutex_unlock(&radioConnectivityLock);
}

static inline 
#line 336
void lossy_transmit(int moteID, char bit)
#line 336
{
  link_t *current_link;

  pthread_mutex_lock(&radioConnectivityLock);
  current_link = radio_connectivity[moteID];
  transmitting[moteID] = bit;
  while (current_link) {
      int r = rand() % 100000;
      double prob = (double )r / 100000.0;
      int tmp_bit = bit;

#line 346
      if (prob < current_link->data) {
          tmp_bit = tmp_bit ? 0 : 1;
        }
      radio_active[current_link->mote] += tmp_bit;
      radio_idle_state[current_link->mote] = 0;
      current_link->bit = tmp_bit;
      current_link = current_link->next_link;
    }
  pthread_mutex_unlock(&radioConnectivityLock);
}

static inline 
#line 392
int read_lossy_entry(FILE *file, int *mote_one, int *mote_two, double *loss)
#line 392
{
  char buf[128];
  int findex = 0;
  int ch;


  while (1) {
      ch = getc(file);
      if (ch == -1) {
#line 400
          return 0;
        }
      else {
#line 401
        if (ch >= '0' && ch <= '9') {
            buf[findex] = (char )ch;
            findex++;
          }
        else {
#line 405
          if (ch == ':') {
              buf[findex] = 0;
              break;
            }
          else {
#line 409
            if ((ch == '\n' || ch == ' ') || ch == '\t') {
                if (findex > 0) {
#line 410
                    return 0;
                  }
              }
            else 
#line 412
              {
                return 0;
              }
            }
          }
        }
    }
#line 417
  *mote_one = atoi(buf);
  findex = 0;

  while (1) {
      ch = getc(file);
      if (ch == -1) {
#line 422
          return 0;
        }
      else {
#line 423
        if (ch >= '0' && ch <= '9') {
            buf[findex] = (char )ch;
            findex++;
          }
        else {
#line 427
          if (ch == ':') {
              buf[findex] = 0;
              break;
            }
          else {
#line 431
            if ((ch == '\n' || ch == ' ') || ch == '\t') {
                if (findex == 0) {
#line 432
                    return 0;
                  }
                else 
#line 433
                  {
                    buf[findex] = 0;
                    break;
                  }
              }
            else {
                return 0;
              }
            }
          }
        }
    }
#line 443
  *mote_two = atoi(buf);

  findex = 0;

  while (1) {
      ch = getc(file);
      if (ch == -1) {
#line 449
          return 0;
        }
      else {
#line 451
        if (((((
#line 450
        ch >= '0' && ch <= '9') || ch == '.') || ch == '-') || ch == 'E')
         || ch == 'e') {
            buf[findex] = (char )ch;
            findex++;
          }
        else {
#line 455
          if ((ch == '\n' || ch == ' ') || ch == '\t') {
              if (findex == 0) {
#line 456
                  return 0;
                }
              else 
#line 457
                {
                  buf[findex] = 0;
                  break;
                }
            }
          else {
              return 0;
            }
          }
        }
    }
#line 466
  *loss = atof(buf);

  return 1;
}

static inline void lossy_init(void)
#line 471
{
  int sfd = open(lossyFileName, 0);
  int i;
  FILE *file = fdopen(sfd, "r");
  link_t *new_link;

  dbg_clear(DBG_SIM, "Initializing lossy model from %s.\n", lossyFileName);
  pthread_mutex_init(&radioConnectivityLock, (void *)0);
  adjacency_list_init();

  if (sfd < 0) {
      dbg(DBG_SIM, "Cannot open %s - assuming single radio cell\n", lossyFileName);
      static_one_cell_init();
      return;
    }

  for (i = 0; i < TOSNODES; i++) {
      radio_connectivity[i] = (void *)0;
      radio_idle_state[i] = 0;
      radio_heard[i] = 0;
    }
  while (1) {
      int mote_one;
      int mote_two;
      double loss;

#line 496
      if (read_lossy_entry(file, &mote_one, &mote_two, &loss)) {
          if (mote_one != mote_two) {
              new_link = allocate_link(mote_two);
              new_link->data = loss;
              new_link->next_link = radio_connectivity[mote_one];
              radio_connectivity[mote_one] = new_link;
            }
        }
      else {
          break;
        }
    }
  dbg(DBG_BOOT, "RFM connectivity graph constructed.\n");
}

static inline 








rfm_model *create_lossy_model(char *file)
#line 520
{
  rfm_model *model = (rfm_model *)malloc(sizeof(rfm_model ));

#line 522
  if (file != (void *)0) {
      lossyFileName = file;
    }
  model->init = lossy_init;
  model->transmit = lossy_transmit;
  model->stop_transmit = lossy_stop_transmit;
  model->hears = lossy_hears;
  model->connected = lossy_connected;
  model->neighbors = lossy_neighbors;
  return model;
}

static inline 
# 83 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adc_model.c"
uint16_t generic_adc_read(int moteID, uint8_t port, long long ftime)
#line 83
{
  uint16_t value;

  if (moteID >= TOSNODES || moteID < 0) {
      dbg(DBG_ERROR, "GENERIC_ADC_MODEL: trying to read value with invalid parameters: [moteID = %d] [port = %d]", moteID, port);
      return -1;
    }
  pthread_mutex_lock(&adcValuesLock);
  value = adcValues[moteID][(int )port];
  pthread_mutex_unlock(&adcValuesLock);
  if (value == 0xffff) {
    return (short )(rand() & 0x3ff);
    }
  else {
#line 96
    return value;
    }
}

static inline 
#line 72
void generic_adc_init(void)
#line 72
{
  int i;
#line 73
  int j;

#line 74
  for (i = 0; i < TOSNODES; i++) {
      for (j = 0; j < ADC_NUM_PORTS_PER_NODE; j++) {
          adcValues[i][j] = 0xffff;
        }
    }
  pthread_mutex_init(&adcValuesLock, (void *)0);
}

static inline 
#line 99
adc_model *create_generic_adc_model(void)
#line 99
{
  adc_model *model = (adc_model *)malloc(sizeof(adc_model ));

#line 101
  model->init = generic_adc_init;
  model->read = generic_adc_read;
  return model;
}

static inline 
#line 50
uint16_t random_adc_read(int moteID, uint8_t port, long long ftime)
#line 50
{
  return (uint16_t )(rand() & 0x3ff);
}

static inline 
#line 48
void random_adc_init(void)
#line 48
{
}

static inline 


adc_model *create_random_adc_model(void)
#line 54
{
  adc_model *model = (adc_model *)malloc(sizeof(adc_model ));

#line 56
  model->init = random_adc_init;
  model->read = random_adc_read;
  return model;
}

static inline 
# 104 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/eeprom.c"
int namedEEPROM(char *name, int fnumMotes, int eepromSize)
#line 104
{
  int filedes = createEEPROM(name, fnumMotes, eepromSize);

#line 106
  if (filedes >= 0) {
      return 0;
    }
  else {
      dbg(DBG_ERROR, "ERROR: Unable to create named EEPROM region: %s.\n", name);
      return -1;
    }
}

static inline 
#line 91
int anonymousEEPROM(int fnumMotes, int eepromSize)
#line 91
{
  int filedes;

#line 93
  filedes = createEEPROM("/tmp/anonymous", fnumMotes, eepromSize);
  if (filedes >= 0) {
      unlink("/tmp/anonymous");
      return 0;
    }
  else {
      dbg(DBG_ERROR, "ERROR: Unable to create anonymous EEPROM region.\n");
      return -1;
    }
}

static inline 
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/spatial_model.c"
void simple_spatial_get_position(int moteID, long long ftime, point3D *point)
#line 63
{
  point->xCoordinate = points[moteID].xCoordinate;
  point->yCoordinate = points[moteID].yCoordinate;
  point->zCoordinate = points[moteID].zCoordinate;
}

static inline 
#line 51
void simple_spatial_init(void)
#line 51
{
  int i;

#line 53
  points = (point3D *)malloc(sizeof(point3D ) * TOSNODES);

  for (i = 0; i < TOSNODES; i++) {
      points[i].xCoordinate = (double )(rand() % 1000);
      points[i].yCoordinate = (double )(rand() % 1000);
      points[i].zCoordinate = (double )(rand() % 1000);
    }
}

static inline 







spatial_model *create_simple_spatial_model(void)
#line 70
{
  spatial_model *model = (spatial_model *)malloc(sizeof(spatial_model ));

#line 72
  model->init = simple_spatial_init;
  model->get_position = simple_spatial_get_position;

  return model;
}

static inline 
# 127 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/nido.h"
void tos_state_model_init(void )
{
  tos_state.space->init();
  tos_state.rfm->init();
  tos_state.adc->init();
}

static inline 
# 91 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/packet_sim.c"
void packet_sim_init(void)
#line 91
{
  int i;

#line 93
  for (i = 0; i < TOSNODES; i++) {
      packet_transmitting[i] = (void *)0;
      incoming[i] = (void *)0;
      cc1000_connectivity[i] = (void *)0;
    }
  cc1000_connectivity[0] = (link_t *)malloc(sizeof(link_t ));
  cc1000_connectivity[0]->mote = 1;
  cc1000_connectivity[0]->next_link = (void *)0;
  cc1000_connectivity[2] = (link_t *)malloc(sizeof(link_t ));
  cc1000_connectivity[2]->mote = 1;
  cc1000_connectivity[2]->next_link = (void *)0;
}

static inline 
# 51 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.c"
void init_hardware(void)
#line 51
{
  int i;

#line 53
  for (i = 0; i < tos_state.num_nodes; i++) {
      tos_state.current_node = i;
      TOSH_pc_hardware.status_register = 0xff;
    }
}

static inline 
# 68 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
void init_heap(heap_t *heap)
#line 68
{
  heap->size = 0;
  heap->private_size = STARTING_SIZE;
  heap->data = malloc(sizeof(node_t ) * heap->private_size);
}

static inline 
# 51 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/event_queue.c"
void queue_init(event_queue_t *queue, int fpause)
#line 51
{
  init_heap(& queue->heap);
  queue->pause = fpause;
  pthread_mutex_init(& queue->lock, (void *)0);
}

static inline 
# 352 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
void event_command_cleanup(event_t *event)
#line 352
{
  incoming_command_data_t *cmdData = (incoming_command_data_t *)event->data;

#line 354
  free(cmdData->msg);
  free(cmdData->payLoad);
  event_total_cleanup(event);
}

static inline  
# 246 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
TOS_MsgPtr AMStandard$UARTReceive$receive(TOS_MsgPtr packet)
#line 246
{


  packet->group = TOS_AM_GROUP;
  return received(packet);
}

# 75 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr Nido$UARTReceiveMsg$receive(TOS_MsgPtr arg_0xe14160){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = AMStandard$UARTReceive$receive(arg_0xe14160);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 478 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
TOS_MsgPtr   NIDO_received_uart(TOS_MsgPtr packet)
#line 478
{
  packet->crc = 1;
  return Nido$UARTReceiveMsg$receive(packet);
}

#line 468
TOS_MsgPtr   NIDO_received_radio(TOS_MsgPtr packet)
#line 468
{
  packet->crc = 1;
  return Nido$RadioReceiveMsg$receive(packet);
}

# 68 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t TOSwqrsM$Timer$stop(void){
#line 68
  unsigned char result;
#line 68

#line 68
  result = TimerM$Timer$stop(0);
#line 68

#line 68
  return result;
#line 68
}
#line 68
static inline 
# 128 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/tos.h"
result_t rcombine3(result_t r1, result_t r2, result_t r3)
{
  return rcombine(r1, rcombine(r2, r3));
}

# 68 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t AMStandard$ActivityTimer$stop(void){
#line 68
  unsigned char result;
#line 68

#line 68
  result = TimerM$Timer$stop(1);
#line 68

#line 68
  return result;
#line 68
}
#line 68
static inline   
# 243 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
void PowerStateM$PowerState$radioStop(void)
#line 243
{
  if (!prof_on) {
#line 244
    return;
    }
#line 245
  dbg(DBG_POWER, "POWER: Mote %d RADIO_STATE OFF at %lld\n", tos_state.current_node, 
  tos_state.tos_time);

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 248
    {

      {
#line 250
        float td = (tos_state.tos_time - PrevCPUCycles[tos_state.current_node]) / em_CPU_FREQ;
#line 250
        float engConsumed = td * radioCrt[tos_state.current_node] * em_VOLTAGE;
#line 250
        float engProduced = td * scavengerCrt * em_VOLTAGE;

#line 250
        totalRadioEng[tos_state.current_node] += engConsumed;
#line 250
        batteryEnergy[tos_state.current_node] = batteryEnergy[tos_state.current_node] - engConsumed + engProduced;
#line 250
        printf("Alex - mote %d: totalRadioEng=%.5f radioCrt=%.2f PrevCPUCycles=%d tos_state.tos_time=%lld batteryEnergy=%.2f scavengerCrt=%.2f\n", tos_state.current_node, totalRadioEng[tos_state.current_node], radioCrt[tos_state.current_node], PrevCPUCycles[tos_state.current_node], tos_state.tos_time, batteryEnergy[tos_state.current_node], scavengerCrt);
#line 250
        if (tos_state.tos_time - PrevCPUCycles[tos_state.current_node] >= 4000000) {
#line 250
          PowerStateM$ReadScavengerProfile();
          }
#line 250
        if (1) {
#line 250
          PrevCPUCycles[tos_state.current_node] = tos_state.tos_time;
          }
      }
#line 250
      ;

      radioState[tos_state.current_node].on = 0;
      radioState[tos_state.current_node].tx = 0;
    }
#line 254
    __nesc_atomic_end(__nesc_atomic); }
}

# 49 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   void MicaHighSpeedRadioM$PowerState$radioStop(void){
#line 49
  PowerStateM$PowerState$radioStop();
#line 49
}
#line 49
static inline  
# 124 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$Control$stop(void)
#line 124
{
  MicaHighSpeedRadioM$PowerState$radioStop();
  return SUCCESS;
}

# 78 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$RadioControl$stop(void){
#line 78
  unsigned char result;
#line 78

#line 78
  result = MicaHighSpeedRadioM$Control$stop();
#line 78

#line 78
  return result;
#line 78
}
#line 78
static inline  
# 65 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/UARTNoCRCPacketM.nc"
result_t UARTNoCRCPacketM$Control$stop(void)
#line 65
{
  dbg(DBG_BOOT, "UART stopped.\n");
  return SUCCESS;
}

# 78 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$UARTControl$stop(void){
#line 78
  unsigned char result;
#line 78

#line 78
  result = UARTNoCRCPacketM$Control$stop();
#line 78

#line 78
  return result;
#line 78
}
#line 78
static inline  
# 119 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
bool AMStandard$Control$stop(void)
#line 119
{
  result_t ok1 = AMStandard$UARTControl$stop();
  result_t ok2 = AMStandard$RadioControl$stop();
  result_t ok3 = AMStandard$ActivityTimer$stop();

  AMStandard$PowerManagement$adjustPower();
  return rcombine3(ok1, ok2, ok3);
}

# 78 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t TOSwqrsM$CommControl$stop(void){
#line 78
  unsigned char result;
#line 78

#line 78
  result = AMStandard$Control$stop();
#line 78

#line 78
  return result;
#line 78
}
#line 78
static inline  
# 50 "TOSwqrsM.nc"
result_t TOSwqrsM$StdControl$stop(void)
#line 50
{
  TOSwqrsM$CommControl$stop();
  if (TOS_LOCAL_ADDRESS != 0) {
      TOSwqrsM$Timer$stop();
    }
  return SUCCESS;
}

static inline  
# 91 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
result_t TimerM$StdControl$stop(void)
#line 91
{
  TimerM$mState[tos_state.current_node] = 0;
  TimerM$mInterval[tos_state.current_node] = TimerM$maxTimerInterval;
  TimerM$setIntervalFlag[tos_state.current_node] = 0;
  return SUCCESS;
}

# 78 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t Nido$StdControl$stop(void){
#line 78
  unsigned char result;
#line 78

#line 78
  result = TimerM$StdControl$stop();
#line 78
  result = rcombine(result, TOSwqrsM$StdControl$stop());
#line 78

#line 78
  return result;
#line 78
}
#line 78
# 453 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void   nido_stop_mote(uint16_t moteID)
#line 453
{

  tos_state.cancelBoot[moteID] = 1;

  if (tos_state.moteOn[moteID] && moteID < tos_state.num_nodes) {
      tos_state.moteOn[moteID] = 0;
      tos_state.current_node = moteID;
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 460
        TOS_LOCAL_ADDRESS = tos_state.current_node;
#line 460
        __nesc_atomic_end(__nesc_atomic); }
      tos_state.node_state[moteID].time = tos_state.tos_time;

      Nido$StdControl$stop();
    }
}

static inline 
# 512 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
void event_command_in_handle(event_t *event, 
struct TOS_state *state)
#line 513
{
  incoming_command_data_t *cmdData = (incoming_command_data_t *)event->data;
  GuiMsg *msg = cmdData->msg;

#line 516
  dbg_clear(DBG_SIM, "SIM: Handling incoming command type %d for mote %d\n", msg->msgType, msg->moteID);

  switch (msg->msgType) {

      case AM_TURNONMOTECOMMAND: 
        dbg_clear(DBG_SIM, "SIM: Turning on mote %d\n", msg->moteID);
      nido_start_mote(msg->moteID);
      break;

      case AM_TURNOFFMOTECOMMAND: 
        dbg_clear(DBG_SIM, "SIM: Turning off mote %d\n", msg->moteID);
      nido_stop_mote(msg->moteID);
      break;

      case AM_RADIOMSGSENDCOMMAND: 
        {
          RadioMsgSendCommand *rmsg = (RadioMsgSendCommand *)cmdData->payLoad;
          TOS_MsgPtr buffer;

          dbg_clear(DBG_SIM, "SIM: Enqueueing radio message for mote %d (payloadlen %d)\n", msg->moteID, msg->payLoadLen);
          if (external_comm_buffers_[msg->moteID] == (void *)0) {
            external_comm_buffers_[msg->moteID] = &external_comm_msgs_[msg->moteID];
            }
#line 538
          buffer = external_comm_buffers_[msg->moteID];
          memcpy(buffer, & rmsg->message, msg->payLoadLen);
          buffer->group = TOS_AM_GROUP;
          external_comm_buffers_[msg->moteID] = NIDO_received_radio(buffer);
        }
      break;

      case AM_UARTMSGSENDCOMMAND: 
        {
          UARTMsgSendCommand *umsg = (UARTMsgSendCommand *)cmdData->payLoad;
          TOS_MsgPtr buffer;
          int len = msg->payLoadLen > sizeof(TOS_Msg ) ? sizeof(TOS_Msg ) : msg->payLoadLen;

          dbg_clear(DBG_SIM, "SIM: Enqueueing UART message for mote %d (payloadlen %d)\n", msg->moteID, msg->payLoadLen);
          if (external_comm_buffers_[msg->moteID] == (void *)0) {
            external_comm_buffers_[msg->moteID] = &external_comm_msgs_[msg->moteID];
            }
#line 554
          buffer = external_comm_buffers_[msg->moteID];

          memcpy(buffer, & umsg->message, len);
          buffer->group = TOS_AM_GROUP;
          external_comm_buffers_[msg->moteID] = NIDO_received_uart(buffer);
        }
      break;

      case AM_INTERRUPTCOMMAND: 
        {
          InterruptEvent interruptEvent;
          InterruptCommand *pcmd = (InterruptCommand *)cmdData->payLoad;

#line 566
          interruptEvent.id = pcmd->id;
          dbg_clear(DBG_TEMP, "\nSIM: Interrupt command, id: %i.\n\n", pcmd->id);
          sendTossimEvent(TOS_BCAST_ADDR, AM_INTERRUPTEVENT, 
          tos_state.tos_time, &interruptEvent);
          break;
        }

      default: 
        dbg_clear(DBG_SIM, "SIM: Unrecognizable command type received from TinyViz %i\n", msg->msgType);
      break;
    }

  event_cleanup(event);
}

static inline 
#line 360
void event_command_in_create(event_t *event, 
GuiMsg *msg, 
char *payLoad)
#line 362
{
  incoming_command_data_t *data = (incoming_command_data_t *)malloc(sizeof(incoming_command_data_t ));

#line 364
  data->msg = msg;
  data->payLoad = payLoad;

  event->mote = (int )(msg->moteID & 0xffff);
  if (event->mote < TOSNODES && 
  event->mote >= 0) {
      event->force = 1;
    }
  event->pause = 1;
  event->data = data;
  event->time = msg->time;
  event->handle = event_command_in_handle;
  event->cleanup = event_command_cleanup;
}

# 54 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/dbg.c"
void dbg_set(TOS_dbg_mode modes)
#line 54
{
  dbg_modes = modes;
}

static inline 
# 80 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/tos.c"
void rate_checkpoint(void)
#line 80
{
  rate_checkpoint_time = tos_state.tos_time;
  gettimeofday(&startTime, (void *)0);
}

static inline 
#line 76
void set_rate_value(double rate)
#line 76
{
  rate_value = rate;
}

# 507 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void   set_sim_rate(uint32_t rate)
#line 507
{
  double realRate = (double )rate;

#line 509
  realRate /= 1000.0;
  dbg_clear(DBG_SIM, "SIM: Setting rate to %lf\n", realRate);
  set_rate_value(realRate);
  rate_checkpoint();
}

static inline 
# 106 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adc_model.c"
void set_adc_value(int moteID, uint8_t port, uint16_t value)
#line 106
{
  if (moteID >= TOSNODES || moteID < 0) {
      dbg(DBG_ERROR, "GENERIC_ADC_MODEL: trying to set value with invalid parameters: [moteID = %d] [port = %d]", moteID, port);
      return;
    }
  pthread_mutex_lock(&adcValuesLock);
  adcValues[moteID][(int )port] = value;
  pthread_mutex_unlock(&adcValuesLock);
}

static inline 
# 550 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/rfm_model.c"
void set_link_prob_value(uint16_t moteID1, uint16_t moteID2, double prob)
#line 550
{
  link_t *current_link;
  link_t *new_link;

  pthread_mutex_lock(&radioConnectivityLock);
  current_link = radio_connectivity[moteID1];
  dbg(DBG_SIM, "RFM: MDW: Setting loss prob %d->%d to %0.3f\n", moteID1, moteID2, prob);
  while (current_link) {
      if (current_link->mote == moteID2) {
          current_link->data = prob;
          pthread_mutex_unlock(&radioConnectivityLock);
          return;
        }
      current_link = current_link->next_link;
    }
  new_link = allocate_link(moteID2);
  new_link->next_link = radio_connectivity[moteID1];
  new_link->data = prob;
  radio_connectivity[moteID1] = new_link;
  pthread_mutex_unlock(&radioConnectivityLock);
}

static inline 
# 382 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
int processCommand(int clifd, int clidx, GuiMsg *msg, char *payLoad, 
unsigned char **replyMsg, int *replyLen)
#line 383
{
  int ret = 0;

#line 385
  switch (msg->msgType) {

      case AM_SETLINKPROBCOMMAND: 
        {
          SetLinkProbCommand *linkmsg = (SetLinkProbCommand *)payLoad;
          double prob = (double )linkmsg->scaledProb / 10000;

#line 391
          set_link_prob_value(msg->moteID, linkmsg->moteReceiver, prob);
          break;
        }
      case AM_SETADCPORTVALUECOMMAND: 
        {
          SetADCPortValueCommand *adcmsg = (SetADCPortValueCommand *)payLoad;

#line 397
          set_adc_value(msg->moteID, adcmsg->port, adcmsg->value);
          break;
        }
      case AM_SETRATECOMMAND: 
        {
          SetRateCommand *ratemsg = (SetRateCommand *)payLoad;

#line 403
          set_sim_rate(ratemsg->rate);
          break;
        }
      case AM_VARIABLERESOLVECOMMAND: 
        {
          VariableResolveResponse varResult;
          VariableResolveCommand *rmsg = (VariableResolveCommand *)payLoad;







          if (
#line 415
          __nesc_nido_resolve(msg->moteID, (char *)rmsg->name, 
          (uintptr_t *)& varResult.addr, 
          (size_t *)& varResult.length) != 0) 
            {
              varResult.addr = 0;
              varResult.length = -1;
            }

          dbg_clear(DBG_SIM, "SIM: Resolving variable %s for mote %d: 0x%x %d\n", 
          rmsg->name, msg->moteID, varResult.addr, varResult.length);

          buildTossimEvent(TOS_BCAST_ADDR, AM_VARIABLERESOLVERESPONSE, 
          tos_state.tos_time, &varResult, replyMsg, replyLen);
          ret = 1;
          break;
        }
      case AM_VARIABLEREQUESTCOMMAND: 
        {
          VariableRequestResponse varResult;
          VariableRequestCommand *rmsg = (VariableRequestCommand *)payLoad;
          uint8_t *ptr = (uint8_t *)rmsg->addr;

#line 436
          varResult.length = rmsg->length;

          if (varResult.length == 0) {
            varResult.length = 256;
            }
          memcpy(varResult.value, ptr, varResult.length);

          buildTossimEvent(TOS_BCAST_ADDR, AM_VARIABLEREQUESTRESPONSE, 
          tos_state.tos_time, &varResult, replyMsg, replyLen);
          ret = 1;
          break;
        }

      case AM_GETMOTECOUNTCOMMAND: 
        {
          int i;
          GetMoteCountResponse countResponse;

          countResponse.totalMotes = tos_state.num_nodes;
          bzero(& countResponse.bitmask, sizeof  countResponse.bitmask);

          for (i = 0; i < TOSNODES; i++) {
              countResponse.bitmask[i / 8] |= 1 << (7 - i % 8);
            }

          buildTossimEvent(TOS_BCAST_ADDR, AM_GETMOTECOUNTRESPONSE, 
          tos_state.tos_time, &countResponse, replyMsg, replyLen);
          ret = 1;
          break;
        }
      case AM_SETDBGCOMMAND: 
        {
          SetDBGCommand *cmd = (SetDBGCommand *)payLoad;

#line 469
          dbg_set(cmd->dbg);
          break;
        }
      case AM_SETEVENTMASKCOMMAND: 
        {
          SetEventMaskCommand *setMaskCommand = (SetEventMaskCommand *)payLoad;

#line 475
          eventMask = setMaskCommand->mask;
          break;
        }
      case AM_BEGINBATCHCOMMAND: 
        {
          if (batchState[clidx] != 0) {
              dbg(DBG_SIM | DBG_ERROR, "SIM: duplicate begin batch");
            }
          dbg(DBG_SIM, "SIM: begin batch");
          batchState[clidx] = 1;
          break;
        }
      case AM_ENDBATCHCOMMAND: 
        {
          if (batchState[clidx] == 0) {
              dbg(DBG_SIM | DBG_ERROR, "SIM: end batch without begin");
            }
          dbg(DBG_SIM, "SIM: end batch");
          batchState[clidx] = 0;
          break;
        }

      default: 
        {


          event_t *event = (event_t *)malloc(sizeof(event_t ));

#line 502
          event_command_in_create(event, msg, payLoad);
          dbg(DBG_SIM, "SIM: Enqueuing command event 0x%lx\n", (unsigned long )event);
          queue_insert_event(& tos_state.queue, event);
#line 504
          ;
        }
    }

  return ret;
}

static inline 
#line 583
int readTossimCommand(int clifd, int clidx)
#line 583
{
  GuiMsg *msg;
  unsigned char *header;
  char *payLoad = (void *)0;
  int curlen = 0;
  int rval;
  unsigned char ack;
  int reply;
  unsigned char *replyMsg = 0;
  int replyLen = 0;

  dbg_clear(DBG_SIM, "SIM: Reading command from client fd %d\n", clifd);

  header = (unsigned char *)malloc(14);
  msg = (GuiMsg *)malloc(sizeof(GuiMsg ));

  curlen = 0;
  while (curlen < 14) {
      dbg_clear(DBG_SIM, "SIM: Reading in GuiMsg header of size %d with length %d\n", 14, curlen);
      rval = read(clifd, header + curlen, 14 - curlen);
      if (rval <= 0) {
          dbg_clear(DBG_SIM, "SIM: Closing client socket %d.\n", clifd);
          free(msg);
          close(clifd);
          goto done;
        }
      else 
#line 608
        {
          curlen += rval;
        }
    }


  msg->msgType = ntohs(* (unsigned short *)&header[0]);
  msg->moteID = ntohs(* (unsigned short *)&header[2]);
  msg->time = bswap_64(* (long long *)&header[4]);
  msg->payLoadLen = ntohs(* (unsigned short *)&header[12]);
  dbg_clear(DBG_SIM, "SIM: Command type %d mote %d time 0x%lx payloadlen %d\n", msg->msgType, msg->moteID, msg->time, msg->payLoadLen);
  if (msg->time < tos_state.tos_time) {
      msg->time = tos_state.tos_time;
    }


  if (msg->payLoadLen > 0) {
      payLoad = (char *)malloc(msg->payLoadLen);
      curlen = 0;
      while (curlen < msg->payLoadLen) {
          dbg(DBG_SIM, "SIM: Reading in GuiMsg payload of size %d with length %d\n", msg->payLoadLen, curlen);
          rval = read(clifd, payLoad + curlen, msg->payLoadLen - curlen);
          if (rval <= 0) {
              dbg(DBG_SIM, "SIM: Closing client socket %d.\n", clifd);
              free(msg);
              free(payLoad);
              goto done;
            }
          else 
#line 635
            {
              curlen += rval;
              dbg(DBG_SIM, "SIM: Read from command port, total: %d, need %d\n", curlen, msg->payLoadLen - curlen);
            }
        }
    }

  if (msg->moteID < tos_state.num_nodes) {
      reply = processCommand(clifd, clidx, msg, payLoad, &replyMsg, &replyLen);
    }
  else {
      dbg(DBG_SIM | DBG_ERROR, "SIM: Received command for invalid mote: %i\n", (int )msg->moteID);
    }


  if (batchState[clidx] != 0) {
      if (reply) {
          dbg(DBG_SIM | DBG_ERROR, "SIM: unexpected command response in batch!!\n");
        }
      return 0;
    }

  do {
      rval = write(clifd, &ack, 1);
      if (rval < 0) {
          dbg(DBG_SIM, "SIM: Closing client socket %d.\n", clifd);
          goto done;
        }
    }
  while (
#line 663
  rval != 1);

  if (reply) {
      dbg(DBG_SIM, "SIM: Sending %d byte reply.\n", replyLen);
      writeTossimEvent(replyMsg, replyLen, clifd);
      free(replyMsg);
    }

  done: 
    return 0;
}

static inline 



void *commandReadThreadFunc(void *arg)
#line 679
{
  int i;
  _types_fd_set readset;
#line 681
  _types_fd_set exceptset;
  int highest;
  int numclients;

  dbg_clear(DBG_SIM, "SIM: commandReadThread running.\n");

  while (1) {

      __extension__  (void )({
#line 689
        size_t __i;
#line 689
        char *__tmp = (char *)&readset;

#line 689
        for (__i = 0; __i < sizeof  (* &readset); ++__i) * __tmp++ = 0;
      }
      );
#line 690
      __extension__  (void )({
#line 690
        size_t __i;
#line 690
        char *__tmp = (char *)&exceptset;

#line 690
        for (__i = 0; __i < sizeof  (* &exceptset); ++__i) * __tmp++ = 0;
      }
      );
      (
#line 691
      &readset)->fds_bits[commandServerSocket / (sizeof(fd_mask ) * 8)] |= 1L << commandServerSocket % (sizeof(fd_mask ) * 8);
      (&exceptset)->fds_bits[commandServerSocket / (sizeof(fd_mask ) * 8)] |= 1L << commandServerSocket % (sizeof(fd_mask ) * 8);
      highest = commandServerSocket;
      numclients = 0;

      for (i = 0; i < 4; i++) {
          if (commandClients[i] != -1) {
              if (commandClients[i] > highest) {
#line 698
                highest = commandClients[i];
                }
#line 699
              ;
              (
              &readset)->fds_bits[commandClients[i] / (sizeof(fd_mask ) * 8)] |= 1L << commandClients[i] % (sizeof(fd_mask ) * 8);
              (&exceptset)->fds_bits[commandClients[i] / (sizeof(fd_mask ) * 8)] |= 1L << commandClients[i] % (sizeof(fd_mask ) * 8);
              numclients++;
            }
        }

      ;


      if (select(highest + 1, &readset, (void *)0, &exceptset, 0) < 0) {
          dbg_clear(DBG_SIM, "SIM: commandReadThreadFunc: error in select(): %s\n", strerror(*__errno()));
        }
      ;


      for (i = 0; i < 4; i++) {






          if (commandClients[i] != -1 && (&readset)->fds_bits[commandClients[i] / (sizeof(fd_mask ) * 8)] & (1L << commandClients[i] % (sizeof(fd_mask ) * 8))) {
              if (readTossimCommand(commandClients[i], i) < 0) {
                  close(commandClients[i]);
                  commandClients[i] = -1;
                }
            }
          if (commandClients[i] != -1 && (&exceptset)->fds_bits[commandClients[i] / (sizeof(fd_mask ) * 8)] & (1L << commandClients[i] % (sizeof(fd_mask ) * 8))) {

              close(commandClients[i]);
              commandClients[i] = -1;
            }
        }


      if ((&readset)->fds_bits[commandServerSocket / (sizeof(fd_mask ) * 8)] & (1L << commandServerSocket % (sizeof(fd_mask ) * 8))) {
          int clifd;

#line 739
          ;
          clifd = acceptConnection(commandServerSocket);
          ;
          addClient(commandClients, clifd);
        }
    }
  return 0;
}

static inline 
# 72 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/tos.c"
double get_rate_value(void)
#line 72
{
  return rate_value;
}

# 515 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
uint32_t   get_sim_rate(void)
#line 515
{
  return (uint32_t )(1000.0 * get_rate_value());
}

static inline 
# 286 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
void sendInitEvent(int clifd)
#line 286
{
  TossimInitEvent initEv;
  unsigned char *msg;
  int total_size;

  memset((char *)&initEv, 0, sizeof(TossimInitEvent ));
  initEv.numMotes = tos_state.num_nodes;
  initEv.radioModel = tos_state.radioModel;
  initEv.rate = get_sim_rate();
  buildTossimEvent(0, AM_TOSSIMINITEVENT, 
  tos_state.tos_time, &initEv, &msg, &total_size);
  writeTossimEvent(msg, total_size, clifd);
  free(msg);
}

static inline 



void *eventAcceptThreadFunc(void *arg)
#line 305
{
  int clifd;
  _types_fd_set acceptset;

  dbg_clear(DBG_SIM, "SIM: eventAcceptThread running.\n");

  while (1) {
      __extension__  (void )({
#line 312
        size_t __i;
#line 312
        char *__tmp = (char *)&acceptset;

#line 312
        for (__i = 0; __i < sizeof  (* &acceptset); ++__i) * __tmp++ = 0;
      }
      );
      (
#line 313
      &acceptset)->fds_bits[eventServerSocket / (sizeof(fd_mask ) * 8)] |= 1L << eventServerSocket % (sizeof(fd_mask ) * 8);
      ;
      if (select(eventServerSocket + 1, &acceptset, (void *)0, (void *)0, (void *)0) < 0) {
          ;
        }
      ;

      if ((&acceptset)->fds_bits[eventServerSocket / (sizeof(fd_mask ) * 8)] & (1L << eventServerSocket % (sizeof(fd_mask ) * 8))) {
          ;
          clifd = acceptConnection(eventServerSocket);
          ;
          pthread_mutex_lock(&eventClientsLock);
          addClient(eventClients, clifd);
          sendInitEvent(clifd);
          pthread_cond_broadcast(&eventClientsCond);
          pthread_mutex_unlock(&eventClientsLock);
        }
    }
  return 0;
}

static inline 
#line 125
void initializeSockets(void)
#line 125
{
  int i;

#line 127
  dbg_clear(DBG_SIM, "SIM: Initializing sockets\n");

  pthread_mutex_init(& tos_state.pause_lock, (void *)0);
  pthread_cond_init(& tos_state.pause_cond, (void *)0);
  pthread_cond_init(& tos_state.pause_ack_cond, (void *)0);

  for (i = 0; i < 4; i++) {
      commandClients[i] = -1;
      eventClients[i] = -1;
      batchState[i] = 0;
    }
  eventMask = 0xffff;
  commandServerSocket = createServerSocket(10584);
  eventServerSocket = createServerSocket(10585);
  pthread_mutex_init(&eventClientsLock, (void *)0);
  pthread_cond_init(&eventClientsCond, (void *)0);
  pthread_create(&eventAcceptThread, (void *)0, eventAcceptThreadFunc, (void *)0);
  pthread_create(&commandReadThread, (void *)0, commandReadThreadFunc, (void *)0);
  socketsInitialized = 1;
}

static inline 
#line 225
void waitForGuiConnection(void)
#line 225
{
  int numclients = 0;
  int n;

  dbg_clear(DBG_SIM, "SIM: Waiting for connection from GUI...\n");
  pthread_mutex_lock(&eventClientsLock);
  while (numclients == 0) {
      for (n = 0; n < 4; n++) {
          if (eventClients[n] != -1) {
              dbg_clear(DBG_SIM, "SIM: Got client connection fd %d\n", eventClients[n]);
              numclients++;
            }
        }
      if (numclients == 0) {
          pthread_cond_wait(&eventClientsCond, &eventClientsLock);
        }
    }
  pthread_mutex_unlock(&eventClientsLock);
}

static inline 
# 43 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/events.c"
void event_default_cleanup(event_t *event)
#line 43
{
  free(event->data);
  dbg(DBG_MEM, "event_default_cleanup: freeing event: 0x%x\n", (unsigned int )event);
}

static inline 
# 78 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
int is_empty(heap_t *heap)
#line 78
{
  return heap->size == 0;
}

static inline int heap_is_empty(heap_t *heap)
#line 82
{
  return is_empty(heap);
}

static inline 
# 86 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/event_queue.c"
int queue_is_empty(event_queue_t *queue)
#line 86
{
  int rval;

#line 88
  pthread_mutex_lock(& queue->lock);
  rval = heap_is_empty(& queue->heap);
  pthread_mutex_unlock(& queue->lock);
  return rval;
}

static inline 
# 86 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
long long heap_get_min_key(heap_t *heap)
#line 86
{
  if (is_empty(heap)) {
      return -1;
    }
  else {
      return ((node_t *)heap->data)[0].key;
    }
}

static inline 
# 94 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/event_queue.c"
long long queue_peek_event_time(event_queue_t *queue)
#line 94
{
  long long rval;

  pthread_mutex_lock(& queue->lock);
  if (heap_is_empty(& queue->heap)) {
      rval = -1;
    }
  else {
      rval = heap_get_min_key(& queue->heap);
    }

  pthread_mutex_unlock(& queue->lock);
  return rval;
}

static inline 
#line 63
event_t *queue_pop_event(event_queue_t *queue)
#line 63
{
  long long ftime;
  event_t *event;

  pthread_mutex_lock(& queue->lock);
  event = (event_t *)heap_pop_min_data(& queue->heap, &ftime);
  pthread_mutex_unlock(& queue->lock);

  if (dbg_active(DBG_QUEUE)) {
      char timeStr[128];

#line 73
      timeStr[0] = 0;
      printOtherTime(timeStr, 128, ftime);
      dbg(DBG_QUEUE, "Popping event for mote %i with time %s.\n", event->mote, timeStr);
    }

  if (queue->pause > 0 && event->pause) {
      sleep(queue->pause);
    }


  return event;
}

static inline 
#line 109
void queue_handle_next_event(event_queue_t *queue)
#line 109
{
  event_t *event = queue_pop_event(queue);

#line 111
  if (event != (void *)0) {
      if (tos_state.moteOn[event->mote] || event->force) {
          tos_state.current_node = event->mote;
          dbg(DBG_QUEUE, "Setting TOS_LOCAL_ADDRESS to %hi\n", (short )(event->mote & 0xffff));
          { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 115
            TOS_LOCAL_ADDRESS = (short )(event->mote & 0xffff);
#line 115
            __nesc_atomic_end(__nesc_atomic); }
          event->handle(event, &tos_state);
        }
    }
}

static inline 
# 86 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/tos.c"
void rate_based_wait(void)
#line 86
{
  long long rtElapsed;
  long long diffVal;
  long long secondVal;

#line 90
  gettimeofday(&thisTime, (void *)0);
  rtElapsed = thisTime.tv_usec - startTime.tv_usec;
  secondVal = thisTime.tv_sec - startTime.tv_sec;
  secondVal *= (long long )1000000;
  rtElapsed += secondVal;
  rtElapsed *= (long long )4;
  rtElapsed = (long long )((double )rtElapsed * rate_value);
  if (rtElapsed + 10000 < tos_state.tos_time - rate_checkpoint_time) {
      diffVal = tos_state.tos_time - rate_checkpoint_time - rtElapsed;
      diffVal /= 4;
      usleep(diffVal);
    }
}

static inline 
# 406 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
void PowerStateM$print_power_info(void)
#line 406
{
  int mote;

#line 408
  if (!cpu_prof_on) {
      fprintf(_impure_ptr->_stderr, "print_power_info() called when cpu prof is off!  Shouldn't happen!\n");
      exit(-1);
    }


  if (!power_init) {
      fprintf(_impure_ptr->_stderr, "print_power_info() called before init_power_info()! Should never happen!\n");
      exit(-1);
    }

  for (mote = 0; mote < tos_state.num_nodes; mote++) {

      dbg(DBG_POWER, "POWER: Mote %d CPU_CYCLES %.1lf at %lld\n", mote, 
      PowerStateM$PowerState$get_mote_cycles(mote), 
      tos_state.tos_time);
    }
}

static inline   
#line 456
void PowerStateM$PowerState$CPUCycleCheckpoint(void)
#line 456
{
  if (!cpu_prof_on) {
      fprintf(_impure_ptr->_stderr, "CPUCycleCheckpoint() called when cpu prof is off!  Shouldn't happen!\n");
      exit(-1);
    }


  PowerStateM$print_power_info();
}

# 22 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   void Nido$PowerState$CPUCycleCheckpoint(void){
#line 22
  PowerStateM$PowerState$CPUCycleCheckpoint();
#line 22
}
#line 22
static inline 
# 384 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
int PowerStateM$bb_exec_count(int mote, int bb)
#line 384
{
  int POWERPROF_BB_EXEC_COUNT;

#line 386
  return POWERPROF_BB_EXEC_COUNT;
}

static inline 
#line 428
void PowerStateM$dump_power_details(void)
#line 428
{
  char exec_cnts[12] = "bb_exec_cnt";
  FILE *f;
  int mote;
#line 431
  int bb;

  if (!cpu_prof_on) {
      fprintf(_impure_ptr->_stderr, "dump_power_details() called when cpu prof is off!  Shouldn't happen!\n");
      exit(-1);
    }

  f = fopen(exec_cnts, "w");
  if (!f) {
      fprintf(_impure_ptr->_stderr, "Couldn't open '%s', exiting\n", exec_cnts);
      exit(-1);
    }
  for (mote = 0; mote < tos_state.num_nodes; mote++) {
      fprintf(f, "mote %d total cycles: %.1lf\n", mote, PowerStateM$PowerState$get_mote_cycles(mote));
      dbg(DBG_POWER, "POWER: Mote %d CPU_CYCLES %.1lf at %lld\n", mote, PowerStateM$PowerState$get_mote_cycles(mote), tos_state.tos_time);

      for (bb = 1; bb < PowerStateM$num_bbs(); bb++) {
          fprintf(f, "%6d %6d %8d\n", mote, bb, PowerStateM$bb_exec_count(mote, bb));
        }
    }

  fclose(f);
}

static inline   
#line 63
result_t PowerStateM$PowerState$stop(void)
#line 63
{
  if (cpu_prof_on) {
    PowerStateM$dump_power_details();
    }
  return SUCCESS;
}

# 18 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState.nc"
inline static   result_t Nido$PowerState$stop(void){
#line 18
  unsigned char result;
#line 18

#line 18
  result = PowerStateM$PowerState$stop();
#line 18

#line 18
  return result;
#line 18
}
#line 18
static inline 
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState_Alex_include.h"
void Nido$ReadScavengerProfile(void)
{
  long unixTime;
  int tmp2;
#line 66
  int tmp3;
#line 66
  int tmp4;
#line 66
  int tmp5;
#line 66
  int tmp6;
#line 66
  int crt;

  fscanf(finScavenger, "%ld %d %d %d %d %d %d", &unixTime, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6, &crt);


  printf("Alex: read psuedo-current value %d\n", crt);
  scavengerCrt = 0.02444 * crt;
}

static inline  
# 207 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$UARTSend$sendDone(TOS_MsgPtr msg, result_t success)
#line 207
{
  return AMStandard$reportSendDone(msg, success);
}

# 67 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t UARTNoCRCPacketM$Send$sendDone(TOS_MsgPtr arg_0xe15cb8, result_t arg_0xe15e08){
#line 67
  unsigned char result;
#line 67

#line 67
  result = AMStandard$UARTSend$sendDone(arg_0xe15cb8, arg_0xe15e08);
#line 67

#line 67
  return result;
#line 67
}
#line 67
# 82 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/UARTNoCRCPacketM.nc"
void   NIDO_uart_send_done(TOS_MsgPtr fmsg, result_t fsuccess)
#line 82
{
  UARTNoCRCPacketM$Send$sendDone(fmsg, fsuccess);
}

# 92 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/types/dbg.h"
static void dbg(TOS_dbg_mode mode, const char *format, ...)
{
  DebugMsgEvent ev;

#line 95
  if (dbg_active(mode)) {
      va_list args;

      __builtin_stdarg_start(args, format);
      if (!(mode & DBG_SIM)) {
          vsnprintf(ev.debugMessage, sizeof  ev.debugMessage, format, args);
          sendTossimEvent(tos_state.current_node, AM_DEBUGMSGEVENT, tos_state.tos_time, &ev);
        }
      if (!dbg_suppress_stdout) {

          fprintf(_impure_ptr->_stdout, "%i: ", tos_state.current_node);
          vfprintf(_impure_ptr->_stdout, format, args);
          __builtin_va_end(args);
        }
    }
}

static 
# 845 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
void sendTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data)
#line 845
{
  unsigned char *msg;
  int total_size;
  int n;
  int numclients = 0;
  int clients[4];

  if (!socketsInitialized) {
#line 852
    return;
    }
  pthread_mutex_lock(&eventClientsLock);
  while (numclients == 0) {
      for (n = 0; n < 4; n++) {
          clients[n] = -1;
          if (eventClients[n] != -1) {
              clients[n] = eventClients[n];
              numclients++;
            }
        }

      if (numclients == 0 && GUI_enabled) {
          ;
          pthread_cond_wait(&eventClientsCond, &eventClientsLock);
          ;
        }
      else {
#line 868
        if (numclients == 0) {

            pthread_mutex_unlock(&eventClientsLock);
            return;
          }
        }
    }
#line 874
  pthread_mutex_unlock(&eventClientsLock);

  ;

  buildTossimEvent(moteID, type, ftime, data, &msg, &total_size);

  for (n = 0; n < 4; n++) {
      if (clients[n] != -1 && (type & eventMask) != 0) {
          if (writeTossimEvent(msg, total_size, clients[n]) < 0) {

              pthread_mutex_lock(&eventClientsLock);
              eventClients[n] = -1;
              pthread_mutex_unlock(&eventClientsLock);
            }
        }
    }
  ;
  free(msg);
}

static 
#line 785
void buildTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data, 
unsigned char **msgp, int *lenp)
#line 786
{
  unsigned char *msg;
  int payload_size;
#line 788
  int total_size;



  switch (type) {
      case AM_DEBUGMSGEVENT: 
        payload_size = sizeof(DebugMsgEvent );
      break;
      case AM_RADIOMSGSENTEVENT: 
        payload_size = sizeof(RadioMsgSentEvent );
      break;
      case AM_UARTMSGSENTEVENT: 
        payload_size = sizeof(RadioMsgSentEvent );
      break;
      case AM_ADCDATAREADYEVENT: 
        payload_size = sizeof(ADCDataReadyEvent );
      break;
      case AM_TOSSIMINITEVENT: 
        payload_size = sizeof(TossimInitEvent );
      break;
      case AM_VARIABLERESOLVERESPONSE: 
        payload_size = sizeof(VariableResolveResponse );
      break;
      case AM_VARIABLEREQUESTRESPONSE: 
        payload_size = sizeof(VariableRequestResponse );
      break;
      case AM_INTERRUPTEVENT: 
        payload_size = sizeof(InterruptEvent );
      dbg(DBG_TEMP, "SIM: Sending InterruptEvent, payload is %i\n", (int )payload_size);
      break;
      case AM_LEDEVENT: 
        payload_size = sizeof(LedEvent );
      break;
      default: 
        ;
      return;
    }

  total_size = 14 + payload_size;
  msg = (unsigned char *)malloc(total_size);

  * (unsigned short *)&msg[0] = htons(type);
  * (unsigned short *)&msg[2] = htons(moteID);
  * (long long *)&msg[4] = bswap_64(ftime);
  * (unsigned short *)&msg[12] = htons(payload_size);
  memcpy((unsigned char *)msg + 14, data, payload_size);

  ;


  *msgp = msg;
  *lenp = total_size;
}

static 
#line 36
int64_t bswap_64(int64_t n)
{
  int8_t *p = (int8_t *)&n;

#line 39
  {
#line 39
    int8_t t = p[0];

#line 39
    p[0] = p[7];
#line 39
    p[7] = t;
  }
#line 39
  ;
  {
#line 40
    int8_t t = p[1];

#line 40
    p[1] = p[6];
#line 40
    p[6] = t;
  }
#line 40
  ;
  {
#line 41
    int8_t t = p[2];

#line 41
    p[2] = p[5];
#line 41
    p[5] = t;
  }
#line 41
  ;
  {
#line 42
    int8_t t = p[3];

#line 42
    p[3] = p[4];
#line 42
    p[4] = t;
  }
#line 42
  ;
  return n;
}

static 
#line 754
int writeTossimEvent(void *data, int datalen, int clifd)
#line 754
{
  unsigned char ack;
  int i;
#line 756
  int j;









  ;
  j = 0;


  i = send(clifd, data, datalen, 0);
  ;
  if (i >= 0) {
#line 772
    j = read(clifd, &ack, 1);
    }
#line 773
  ;
  if (i < 0 || j < 0) {
      ;
      close(clifd);
      return -1;
    }


  ;
  return 0;
}

# 215 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
TOS_MsgPtr   received(TOS_MsgPtr packet)
#line 215
{
  uint16_t addr = TOS_LOCAL_ADDRESS;

#line 217
  AMStandard$counter[tos_state.current_node]++;
  dbg(DBG_AM, "AM_address = %hx, %hhx; counter:%i\n", packet->addr, packet->type, (int )AMStandard$counter[tos_state.current_node]);


  if (
#line 220
  packet->crc == 1 && 
  packet->group == TOS_AM_GROUP && (
  packet->addr == TOS_BCAST_ADDR || 
  packet->addr == addr)) 
    {

      uint8_t type = packet->type;
      TOS_MsgPtr tmp;

      dbg(DBG_AM, "Received message:\n\t");
      AMStandard$dbgPacket(packet);
      dbg(DBG_AM, "AM_type = %d\n", type);


      tmp = AMStandard$ReceiveMsg$receive(type, packet);
      if (tmp) {
        packet = tmp;
        }
    }
#line 238
  return packet;
}

# 112 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/types/dbg.h"
static void dbg_clear(TOS_dbg_mode mode, const char *format, ...)
{
  DebugMsgEvent ev;

#line 115
  if (dbg_active(mode)) {
      va_list args;

#line 117
      __builtin_stdarg_start(args, format);
      if (!(mode & DBG_SIM)) {
          vsnprintf(ev.debugMessage, sizeof  ev.debugMessage, format, args);
          sendTossimEvent(tos_state.current_node, AM_DEBUGMSGEVENT, tos_state.tos_time, &ev);
        }
      if (!dbg_suppress_stdout) {

          vfprintf(_impure_ptr->_stdout, format, args);
          __builtin_va_end(args);
        }
    }
}

# 252 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
void   event_spi_byte_create(event_t *fevent, int mote, long long ftime, int interval, int count)
#line 252
{


  spi_byte_data_t *data = (spi_byte_data_t *)malloc(sizeof(spi_byte_data_t ));

#line 256
  dbg(DBG_MEM, "malloc Spi Byte event data.\n");
  data->interval = interval;
  data->mote = mote;
  data->valid = 1;
  data->count = count;
  data->ending = 0;

  fevent->mote = mote;
  fevent->data = data;
  fevent->time = ftime;
  fevent->handle = event_spi_byte_handle;
  fevent->cleanup = event_total_cleanup;
  fevent->pause = 0;
}

static 
# 245 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
int printOtherTime(char *buf, int len, long long int ftime)
#line 245
{
  int hours;
  int minutes;
  int seconds;
  int secondBillionths;

  secondBillionths = (int )(ftime % (long long )4000000);
  seconds = (int )(ftime / (long long )4000000);
  minutes = seconds / 60;
  hours = minutes / 60;
  secondBillionths *= (long long )25;
  seconds %= 60;
  minutes %= 60;

  return snprintf(buf, len, "%i:%i:%i.%08i", hours, minutes, seconds, secondBillionths);
}

static 
# 389 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hpl.c"
uint8_t TOSH_rfm_rx_bit(void )
{
  uint8_t data;

#line 392
  data = tos_state.rfm->hears(tos_state.current_node);
  dbg(DBG_RADIO, "RFM: Mote %i got bit %x\n", tos_state.current_node, data);
  return data;
}

static 
# 57 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/event_queue.c"
void queue_insert_event(event_queue_t *queue, event_t *event)
#line 57
{
  pthread_mutex_lock(& queue->lock);
  heap_insert(& queue->heap, event, event->time);
  pthread_mutex_unlock(& queue->lock);
}

static 
# 187 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
void up_heap(heap_t *heap, int findex)
#line 187
{
  int parent_index;

#line 189
  if (findex == 0) {
      return;
    }

  parent_index = (findex - 1) / 2;

  if (((node_t *)heap->data)[parent_index].key > ((node_t *)heap->data)[findex].key) {
      swap(&((node_t *)heap->data)[findex], &((node_t *)heap->data)[parent_index]);
      up_heap(heap, parent_index);
    }
}

static 
#line 148
void swap(node_t *first, node_t *second)
#line 148
{
  long long key;
  void *data;

  key = first->key;
  first->key = second->key;
  second->key = key;

  data = first->data;
  first->data = second->data;
  second->data = data;
}

static  
# 232 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$SpiByteFifo$dataReady(uint8_t data)
#line 232
{
  if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$TRANSMITTING_START) {
      dbg(DBG_PACKET, "Transmitting start symbol, byte %i\n", MicaHighSpeedRadioM$tx_count[tos_state.current_node]);
      MicaHighSpeedRadioM$SpiByteFifo$send(TOSH_MHSR_start[(int )MicaHighSpeedRadioM$tx_count[tos_state.current_node]]);
      MicaHighSpeedRadioM$tx_count[tos_state.current_node]++;
      if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] == sizeof TOSH_MHSR_start) {
          MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$TRANSMITTING;
          MicaHighSpeedRadioM$tx_count[tos_state.current_node] = 1;
        }
    }
  else {
#line 241
    if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$TRANSMITTING) {
        dbg(DBG_PACKET, "Transmitting data, byte %i\n", MicaHighSpeedRadioM$tx_count[tos_state.current_node]);
        MicaHighSpeedRadioM$SpiByteFifo$send(MicaHighSpeedRadioM$encoded_buffer[tos_state.current_node][(int )MicaHighSpeedRadioM$buf_head[tos_state.current_node]]);
        MicaHighSpeedRadioM$buf_head[tos_state.current_node]++;
        MicaHighSpeedRadioM$buf_head[tos_state.current_node] &= 0x3;
        MicaHighSpeedRadioM$enc_count[tos_state.current_node]--;


        if (MicaHighSpeedRadioM$enc_count[tos_state.current_node] >= 2) {
            ;
          }
        else {
#line 251
          if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] < MSG_DATA_SIZE) {
              char next_data = ((char *)MicaHighSpeedRadioM$send_ptr[tos_state.current_node])[(int )MicaHighSpeedRadioM$tx_count[tos_state.current_node]];

#line 253
              MicaHighSpeedRadioM$Code$encode(next_data);
              MicaHighSpeedRadioM$tx_count[tos_state.current_node]++;
              if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] <= MicaHighSpeedRadioM$msg_length[tos_state.current_node]) {
                  MicaHighSpeedRadioM$calc_crc[tos_state.current_node] = MicaHighSpeedRadioM$add_crc_byte(next_data, MicaHighSpeedRadioM$calc_crc[tos_state.current_node]);
                }
              if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] == MicaHighSpeedRadioM$msg_length[tos_state.current_node]) {


                  MicaHighSpeedRadioM$tx_count[tos_state.current_node] = MSG_DATA_SIZE - 2;
                  MicaHighSpeedRadioM$send_ptr[tos_state.current_node]->crc = MicaHighSpeedRadioM$calc_crc[tos_state.current_node];
                  dbg(DBG_CRC, "MicaHighSpeedRadioM: Send CRC calculated to be 0x%hx.\n", MicaHighSpeedRadioM$calc_crc[tos_state.current_node]);
                }
              MicaHighSpeedRadioM$RadioSendCoordinator$byte(MicaHighSpeedRadioM$send_ptr[tos_state.current_node], (uint8_t )MicaHighSpeedRadioM$tx_count[tos_state.current_node]);
            }
          else {
#line 266
            if (MicaHighSpeedRadioM$buf_head[tos_state.current_node] != MicaHighSpeedRadioM$buf_end[tos_state.current_node]) {
                MicaHighSpeedRadioM$Code$encode_flush();
              }
            else 
#line 268
              {
                MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$SENDING_STRENGTH_PULSE;
                MicaHighSpeedRadioM$tx_count[tos_state.current_node] = 0;
              }
            }
          }
      }
    else {
#line 272
      if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$SENDING_STRENGTH_PULSE) {
          MicaHighSpeedRadioM$tx_count[tos_state.current_node]++;
          dbg(DBG_PACKET, "Transmitting strength pulse, byte %i\n", MicaHighSpeedRadioM$tx_count[tos_state.current_node]);
          if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] == 3) {
              MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$WAITING_FOR_ACK;
              MicaHighSpeedRadioM$tx_count[tos_state.current_node] = 1;
              MicaHighSpeedRadioM$SpiByteFifo$send(0x00);
            }
          else {
              MicaHighSpeedRadioM$SpiByteFifo$send(0xff);
            }
        }
      else {
#line 283
        if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$WAITING_FOR_ACK) {
            data &= 0x7f;
            dbg(DBG_PACKET, "Waiting for ACK, byte %i\n", MicaHighSpeedRadioM$tx_count[tos_state.current_node]);
            MicaHighSpeedRadioM$SpiByteFifo$send(0x00);
            if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] == 1) {
              MicaHighSpeedRadioM$SpiByteFifo$phaseShift();
              }
#line 289
            MicaHighSpeedRadioM$SpiByteFifo$rxMode();
            MicaHighSpeedRadioM$tx_count[tos_state.current_node]++;
            if (MicaHighSpeedRadioM$tx_count[tos_state.current_node] == MicaHighSpeedRadioM$ACK_CNT + 2) {
                MicaHighSpeedRadioM$send_ptr[tos_state.current_node]->ack = data == 0x55;
                MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$IDLE_STATE;
                MicaHighSpeedRadioM$SpiByteFifo$idle();
                MicaHighSpeedRadioM$ChannelMon$startSymbolSearch();
                TOS_post(MicaHighSpeedRadioM$packetSent);
              }
          }
        else {
#line 298
          if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$RX_STATE) {

              MicaHighSpeedRadioM$Code$decode(data);
            }
          else {
#line 301
            if (MicaHighSpeedRadioM$state[tos_state.current_node] == MicaHighSpeedRadioM$ACK_SEND_STATE) {
                dbg(DBG_PACKET, "Sending ACK, count %i\n", (int )MicaHighSpeedRadioM$ack_count[tos_state.current_node]);
                MicaHighSpeedRadioM$ack_count[tos_state.current_node]++;
                if (MicaHighSpeedRadioM$ack_count[tos_state.current_node] > MicaHighSpeedRadioM$ACK_CNT + 1) {
                    MicaHighSpeedRadioM$state[tos_state.current_node] = MicaHighSpeedRadioM$RX_DONE_STATE;
                    MicaHighSpeedRadioM$SpiByteFifo$idle();
                    TOS_post(MicaHighSpeedRadioM$packetReceived);
                  }
                else 
#line 308
                  {
                    MicaHighSpeedRadioM$SpiByteFifo$txMode();
                  }
              }
            }
          }
        }
      }
    }
#line 313
  return 1;
}

static  
# 70 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
result_t SpiByteFifoC$SpiByteFifo$send(uint8_t data)
#line 70
{
  event_t *fevent;
  long long ftime;

  if (SpiByteFifoC$state[tos_state.current_node] == SpiByteFifoC$OPEN) {
      SpiByteFifoC$nextByte[tos_state.current_node] = data;
      SpiByteFifoC$state[tos_state.current_node] = SpiByteFifoC$FULL;
      return SUCCESS;
    }
#line 78
  if (SpiByteFifoC$state[tos_state.current_node] == SpiByteFifoC$IDLE) {
      SpiByteFifoC$state[tos_state.current_node] = SpiByteFifoC$OPEN;
      SpiByteFifoC$SpiByteFifo$dataReady(0);
      SpiByteFifoC$spdr[tos_state.current_node] = data;
      SpiByteFifoC$radioState[tos_state.current_node] = SpiByteFifoC$RADIO_SENDING;
      SpiByteFifoC$PowerState$radioTxMode();
      if (spiByteEvents[tos_state.current_node] != (void *)0) {
          event_spi_byte_invalidate(spiByteEvents[tos_state.current_node]);
        }
      dbg(DBG_MEM, "malloc spi byte event.\n");
      fevent = (event_t *)malloc(sizeof(event_t ));

      ftime = tos_state.tos_time + RADIO_TICKS_PER_EVENT;
      event_spi_byte_create(fevent, tos_state.current_node, ftime, RADIO_TICKS_PER_EVENT, 0);
      queue_insert_event(& tos_state.queue, fevent);
#line 92
      ;

      spiByteEvents[tos_state.current_node] = fevent;

      return SUCCESS;
    }
  return FAIL;
}

static   
# 179 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
void PowerStateM$PowerState$radioTxMode(void)
#line 179
{
  if (!prof_on) {
#line 180
    return;
    }
#line 181
  dbg(DBG_POWER, "POWER: Mote %d RADIO_STATE TX at %lld\n", tos_state.current_node, 
  tos_state.tos_time);

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 184
    {

      {
#line 186
        float td = (tos_state.tos_time - PrevCPUCycles[tos_state.current_node]) / em_CPU_FREQ;
#line 186
        float engConsumed = td * radioCrt[tos_state.current_node] * em_VOLTAGE;
#line 186
        float engProduced = td * scavengerCrt * em_VOLTAGE;

#line 186
        totalRadioEng[tos_state.current_node] += engConsumed;
#line 186
        batteryEnergy[tos_state.current_node] = batteryEnergy[tos_state.current_node] - engConsumed + engProduced;
#line 186
        printf("Alex - mote %d: totalRadioEng=%.5f radioCrt=%.2f PrevCPUCycles=%d tos_state.tos_time=%lld batteryEnergy=%.2f scavengerCrt=%.2f\n", tos_state.current_node, totalRadioEng[tos_state.current_node], radioCrt[tos_state.current_node], PrevCPUCycles[tos_state.current_node], tos_state.tos_time, batteryEnergy[tos_state.current_node], scavengerCrt);
#line 186
        if (tos_state.tos_time - PrevCPUCycles[tos_state.current_node] >= 4000000) {
#line 186
          PowerStateM$ReadScavengerProfile();
          }
#line 186
        if (1) {
#line 186
          PrevCPUCycles[tos_state.current_node] = tos_state.tos_time;
          }
      }
#line 186
      ;

      radioCrt[tos_state.current_node] = radioState[tos_state.current_node].txpower;

      radioState[tos_state.current_node].on = 1;
      radioState[tos_state.current_node].tx = 1;
    }
#line 192
    __nesc_atomic_end(__nesc_atomic); }
}

static 
# 63 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerState_Alex_include.h"
void PowerStateM$ReadScavengerProfile(void)
{
  long unixTime;
  int tmp2;
#line 66
  int tmp3;
#line 66
  int tmp4;
#line 66
  int tmp5;
#line 66
  int tmp6;
#line 66
  int crt;

  fscanf(finScavenger, "%ld %d %d %d %d %d %d", &unixTime, &tmp2, &tmp3, &tmp4, &tmp5, &tmp6, &crt);


  printf("Alex: read psuedo-current value %d\n", crt);
  scavengerCrt = 0.02444 * crt;
}

static  
# 86 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SecDedEncoding.nc"
result_t SecDedEncoding$Code$encode(char d)
#line 86
{
  if (SecDedEncoding$state[tos_state.current_node] == SecDedEncoding$IDLE_STATE) {
      SecDedEncoding$state[tos_state.current_node] = SecDedEncoding$ENCODING_BYTE;
      SecDedEncoding$data1[tos_state.current_node] = d;
      SecDedEncoding$radio_encode_thread();
      return 1;
    }
  return 0;
}

static  
# 224 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/MicaHighSpeedRadioM.nc"
result_t MicaHighSpeedRadioM$Code$encodeDone(char data1)
#line 224
{
  MicaHighSpeedRadioM$encoded_buffer[tos_state.current_node][(int )MicaHighSpeedRadioM$buf_end[tos_state.current_node]] = data1;
  MicaHighSpeedRadioM$buf_end[tos_state.current_node]++;
  MicaHighSpeedRadioM$buf_end[tos_state.current_node] &= 0x3;
  MicaHighSpeedRadioM$enc_count[tos_state.current_node] += 1;
  return SUCCESS;
}

static 
#line 324
short MicaHighSpeedRadioM$add_crc_byte(char new_byte, short crc)
#line 324
{
  uint8_t i;

#line 326
  crc = crc ^ ((int )new_byte << 8);
  i = 8;
  do 
    {
      if (crc & 0x8000) {
        crc = (crc << 1) ^ 0x1021;
        }
      else {
#line 333
        crc = crc << 1;
        }
    }
  while (
#line 334
  --i);
  return crc;
}

static   
# 195 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
void PowerStateM$PowerState$radioRxMode(void)
#line 195
{
  if (!prof_on) {
#line 196
    return;
    }
#line 197
  dbg(DBG_POWER, "POWER: Mote %d RADIO_STATE RX at %lld\n", tos_state.current_node, 
  tos_state.tos_time);

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 200
    {

      {
#line 202
        float td = (tos_state.tos_time - PrevCPUCycles[tos_state.current_node]) / em_CPU_FREQ;
#line 202
        float engConsumed = td * radioCrt[tos_state.current_node] * em_VOLTAGE;
#line 202
        float engProduced = td * scavengerCrt * em_VOLTAGE;

#line 202
        totalRadioEng[tos_state.current_node] += engConsumed;
#line 202
        batteryEnergy[tos_state.current_node] = batteryEnergy[tos_state.current_node] - engConsumed + engProduced;
#line 202
        printf("Alex - mote %d: totalRadioEng=%.5f radioCrt=%.2f PrevCPUCycles=%d tos_state.tos_time=%lld batteryEnergy=%.2f scavengerCrt=%.2f\n", tos_state.current_node, totalRadioEng[tos_state.current_node], radioCrt[tos_state.current_node], PrevCPUCycles[tos_state.current_node], tos_state.tos_time, batteryEnergy[tos_state.current_node], scavengerCrt);
#line 202
        if (tos_state.tos_time - PrevCPUCycles[tos_state.current_node] >= 4000000) {
#line 202
          PowerStateM$ReadScavengerProfile();
          }
#line 202
        if (1) {
#line 202
          PrevCPUCycles[tos_state.current_node] = tos_state.tos_time;
          }
      }
#line 202
      ;

      radioCrt[tos_state.current_node] = em_RADIO_RX;

      radioState[tos_state.current_node].on = 1;
      radioState[tos_state.current_node].tx = 0;
    }
#line 208
    __nesc_atomic_end(__nesc_atomic); }
}

static 
# 59 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hardware.c"
short set_io_bit(char port, char bit)
#line 59
{
  char *register_ptr;

#line 61
  switch (port) {
      case 0x34: 
        register_ptr = & TOSH_pc_hardware.register_A;
      break;

      case 0x37: 
        register_ptr = & TOSH_pc_hardware.register_B;
      break;

      case 0x40: 
        register_ptr = & TOSH_pc_hardware.register_C;
      break;

      case 0x43: 
        register_ptr = & TOSH_pc_hardware.register_D;
      break;

      case 0x70: 
        register_ptr = & TOSH_pc_hardware.register_E;
      break;

      case 0x00: 
        register_ptr = & TOSH_pc_hardware.status_register;
      break;

      default: 
        register_ptr = & TOSH_pc_hardware.register_default;
      break;
    }

  dbg(DBG_HARD, "Set bit %i of port %u\n", (int )bit, port);

  *register_ptr = *register_ptr |= 0x1 << bit;

  return *register_ptr;
}

static  
# 101 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/SpiByteFifoC.nc"
result_t SpiByteFifoC$SpiByteFifo$idle(void)
#line 101
{
  SpiByteFifoC$spdr[tos_state.current_node] = 0;
  SpiByteFifoC$nextByte[tos_state.current_node] = 0;
  SpiByteFifoC$radioState[tos_state.current_node] = SpiByteFifoC$RADIO_IDLE;


  SpiByteFifoC$PowerState$radioRxMode();

  SpiByteFifoC$state[tos_state.current_node] = SpiByteFifoC$IDLE;
  SpiByteFifoC$nextByte[tos_state.current_node] = 0;

  if (spiByteEvents[tos_state.current_node] != (void *)0) {
      event_spi_byte_end(spiByteEvents[tos_state.current_node]);
      spiByteEvents[tos_state.current_node] = (void *)0;
    }

  return SUCCESS;
}

static  
# 61 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/ChannelMonC.nc"
result_t ChannelMonC$ChannelMon$startSymbolSearch(void)
#line 61
{
  event_t *fevent;
  long long ftime;


  ChannelMonC$CM_state[tos_state.current_node] = ChannelMonC$IDLE_STATE;

  if (channelMonEvents[tos_state.current_node] != (void *)0) {
      event_channel_mon_invalidate(channelMonEvents[tos_state.current_node]);
    }
  dbg(DBG_MEM, "malloc channel mon event.\n");
  fevent = (event_t *)malloc(sizeof(event_t ));


  ftime = tos_state.tos_time + 200;

  event_channel_mon_create(fevent, tos_state.current_node, ftime, 200);
  queue_insert_event(& tos_state.queue, fevent);
#line 78
  ;

  channelMonEvents[tos_state.current_node] = fevent;


  return SUCCESS;
}

static  
#line 137
result_t ChannelMonC$ChannelMon$stopMonitorChannel(void)
#line 137
{

  event_channel_mon_invalidate(channelMonEvents[tos_state.current_node]);
  channelMonEvents[tos_state.current_node] = (void *)0;

  ChannelMonC$CM_state[tos_state.current_node] = ChannelMonC$DISABLED_STATE;
  return SUCCESS;
}

static 
# 48 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/events.c"
void event_total_cleanup(event_t *event)
#line 48
{
  free(event->data);
  dbg(DBG_MEM, "event_total_cleanup: freeing event data: 0x%x\n", (unsigned int )event->data);
  event->data = (void *)0;
  free(event);
  dbg(DBG_MEM, "event_total_cleanup: freeing event: 0x%x\n", (unsigned int )event);
}

static 
# 149 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/tos.h"
void *nmemcpy(void *to, const void *from, size_t n)
{
  char *cto = to;
  const char *cfrom = from;

  while (n--) * cto++ = * cfrom++;

  return to;
}

static 
# 143 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/AMStandard.nc"
result_t AMStandard$reportSendDone(TOS_MsgPtr msg, result_t success)
#line 143
{
  AMStandard$state[tos_state.current_node] = FALSE;
  AMStandard$SendMsg$sendDone(msg->type, msg, success);
  AMStandard$sendDone();

  return SUCCESS;
}

# 106 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/sched.c"
bool  TOS_post(void (*tp)(void))
#line 106
{
  __nesc_atomic_t fInterruptFlags;
  uint8_t tmp;



  fInterruptFlags = __nesc_atomic_start();

  tmp = TOSH_sched_free;

  if (TOSH_queue[tmp].tp == (void *)0) {
      TOSH_sched_free = (tmp + 1) & TOSH_TASK_BITMASK;
      TOSH_queue[tmp].tp = tp;
      __nesc_atomic_end(fInterruptFlags);

      return TRUE;
    }
  else {
      __nesc_atomic_end(fInterruptFlags);

      return FALSE;
    }
}

static 
# 130 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/packet_sim.c"
void event_backoff_create(event_t *event, int node, long long eventTime)
#line 130
{
  event->mote = node;
  event->force = 0;
  event->pause = 0;
  event->data = (void *)0;
  event->time = eventTime;
  event->handle = event_backoff_handle;
  event->cleanup = event_total_cleanup;
}

static 
#line 165
void corruptPacket(IncomingMsg *msg, int src, int dest)
#line 165
{
  int i;
  uint8_t *buf = (uint8_t *)& msg->msg;

#line 168
  dbg(DBG_PACKET, "SIM_PACKET: Corrupting message from %i to %i\n", src, dest);
  for (i = 0; i < 29 + 7; i++) {
      buf[i] = (uint8_t )(rand() & 0xff);
    }
}

# 406 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
void   nido_start_mote(uint16_t moteID)
#line 406
{
  if (!tos_state.moteOn[moteID] && moteID < tos_state.num_nodes) {
      __nesc_nido_initialise(moteID);
      tos_state.moteOn[moteID] = 1;
      tos_state.current_node = moteID;
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 411
        TOS_LOCAL_ADDRESS = tos_state.current_node;
#line 411
        __nesc_atomic_end(__nesc_atomic); }
      tos_state.node_state[moteID].time = tos_state.tos_time;
      Nido$StdControl$init();
      Nido$StdControl$start();
      tos_state.node_state[moteID].pot_setting = 73;
      while (TOSH_run_next_task()) {
        }

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
        {
          batteryEnergy[tos_state.current_node] = 300.0;

          radioState[tos_state.current_node].on = 0;
          radioState[tos_state.current_node].tx = 0;
          radioState[tos_state.current_node].txpower = em_RADIO_DEFAULT_POWER;

          totalRadioEng[tos_state.current_node] = 0.0;
          radioCrt[tos_state.current_node] = 0.0;

          CPUState[tos_state.current_node] = 0;
          CPUCrt[tos_state.current_node] = em_CPUCrt[CPUState[tos_state.current_node]];
          totalCPUEng[tos_state.current_node] = 0.0;

          if (startSimTime < 0) {
            startSimTime = tos_state.tos_time;
            }
          PrevCPUCycles[tos_state.current_node] = startSimTime;

          printf("Alex - mote=%d: totalCPUEng=%.5f CPUCrt=%.2f PrevCPUCycles=%d batteryEnergy=%.2f\n", 
          tos_state.current_node, 
          totalCPUEng[tos_state.current_node], 
          CPUCrt[tos_state.current_node], 
          PrevCPUCycles[tos_state.current_node], 
          batteryEnergy[tos_state.current_node]);


          finScavenger = fopen("node-2.dat", "rt");
        }
#line 448
        __nesc_atomic_end(__nesc_atomic); }
    }
}

static  
# 77 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
result_t TimerM$StdControl$init(void)
#line 77
{
  TimerM$mState[tos_state.current_node] = 0;
  TimerM$setIntervalFlag[tos_state.current_node] = 0;
  TimerM$queue_head[tos_state.current_node] = TimerM$queue_tail[tos_state.current_node] = -1;
  TimerM$queue_size[tos_state.current_node] = 0;
  TimerM$mScale[tos_state.current_node] = 3;
  TimerM$mInterval[tos_state.current_node] = TimerM$maxTimerInterval;
  return TimerM$Clock$setRate(TimerM$mInterval[tos_state.current_node], TimerM$mScale[tos_state.current_node]);
}

static 
# 86 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/hpl.c"
void TOSH_clock_set_rate(char interval, char scale)
{
  long long ticks;
  event_t *event = (void *)0;

#line 90
  interval = interval + 1;

  dbg(DBG_CLOCK, "CLOCK: Setting clock rate to interval %u, scale %u\n", (unsigned int )(interval & 0xff), (unsigned int )(scale & 0xff));
  if (clockEvents[tos_state.current_node] != (void *)0) {
      event_clocktick_invalidate(clockEvents[tos_state.current_node]);
    }

  ticks = clockScales[(int )(scale & 0xff)] * (int )(interval & 0xff);

  if (ticks > 0) {
      ticks = clockScales[(int )(scale & 0xff)] * (int )(interval & 0xff);


      event = (event_t *)malloc(sizeof(event_t ));

      event_clocktick_create(event, tos_state.current_node, tos_state.tos_time, ticks);
      queue_insert_event(& tos_state.queue, event);
#line 106
      ;
    }
  intervals[tos_state.current_node] = interval;
  scales[tos_state.current_node] = scale;
  clockEvents[tos_state.current_node] = event;
  setTime[tos_state.current_node] = tos_state.tos_time;
  return;
}

static 
#line 191
void event_clocktick_create(event_t *event, int mote, long long eventTime, int interval)
#line 191
{


  clock_tick_data_t *data = malloc(sizeof(clock_tick_data_t ));

#line 195
  dbg(DBG_MEM, "malloc data entry for clock event: 0x%x\n", (int )data);
  data->interval = interval;
  data->mote = mote;
  data->valid = 1;
  data->disabled = 0;

  event->mote = mote;
  event->force = 0;
  event->pause = 1;
  event->data = data;
  event->time = eventTime + interval;
  event->handle = event_clocktick_handle;
  event->cleanup = event_total_cleanup;
}

static 
#line 124
uint8_t TOSH_get_clock0_counter(void)
#line 124
{

  if (scales[tos_state.current_node] == 0 || 
  intervals[tos_state.current_node] == 0) {
#line 127
      return 0;
    }
  else 
#line 128
    {
      long long timeDiff = tos_state.tos_time - setTime[tos_state.current_node];

#line 130
      timeDiff /= (long long )clockScales[scales[tos_state.current_node]];
      timeDiff %= 256;
      return (uint8_t )timeDiff;
    }
}

static 
#line 54
void TOSH_clock_set_interval(uint8_t interval)
#line 54
{
  long long elapsed_time;
  long long ticks;
  int elapsedTicks;
  int realInterval;

  event_t *event = (void *)0;

#line 61
  interval = interval + 1;

  dbg(DBG_CLOCK, "CLOCK: Setting clock interval to %u @ %s\n", (unsigned int )(interval & 0xff), currentTime());
  if (clockEvents[tos_state.current_node] != (void *)0) {
      event_clocktick_invalidate(clockEvents[tos_state.current_node]);
    }


  elapsed_time = tos_state.tos_time - setTime[tos_state.current_node];
  elapsedTicks = elapsed_time / (long long )clockScales[scales[tos_state.current_node]];

  realInterval = interval - elapsedTicks;
  if (realInterval <= 0) {
      realInterval += 256;
    }

  ticks = clockScales[(int )(scales[tos_state.current_node] & 0xff)] * realInterval;
  event = (event_t *)malloc(sizeof(event_t ));

  event_clocktick_create(event, tos_state.current_node, tos_state.tos_time, ticks);
  queue_insert_event(& tos_state.queue, event);
#line 81
  ;
  intervals[tos_state.current_node] = interval;
  clockEvents[tos_state.current_node] = event;
}

static  
# 98 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
result_t TimerM$Timer$start(uint8_t id, char type, 
uint32_t interval)
#line 99
{
  uint8_t diff;

#line 101
  if (id >= NUM_TIMERS) {
#line 101
    return FAIL;
    }
#line 102
  if (type > TIMER_ONE_SHOT) {
#line 102
    return FAIL;
    }





  if (type == TIMER_REPEAT && interval <= 2) {
#line 109
    return FAIL;
    }
  TimerM$mTimerList[tos_state.current_node][id].ticks = interval;
  TimerM$mTimerList[tos_state.current_node][id].type = type;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 114
    {
      diff = TimerM$Clock$readCounter();
      interval += diff;
      TimerM$mTimerList[tos_state.current_node][id].ticksLeft = interval;
      TimerM$mState[tos_state.current_node] |= 0x1L << id;
      if (interval < TimerM$mInterval[tos_state.current_node]) {
          TimerM$mInterval[tos_state.current_node] = interval;
          TimerM$Clock$setInterval(TimerM$mInterval[tos_state.current_node]);
          TimerM$setIntervalFlag[tos_state.current_node] = 0;
          TimerM$PowerManagement$adjustPower();
        }
    }
#line 125
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

static 
# 140 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/sched.c"
bool TOSH_run_next_task(void)
{
  __nesc_atomic_t fInterruptFlags;
  uint8_t old_full;
  void (*func)(void );

  fInterruptFlags = __nesc_atomic_start();
  old_full = TOSH_sched_full;
  func = TOSH_queue[old_full].tp;
  if (func == (void *)0) 
    {
      __nesc_atomic_end(fInterruptFlags);
      return 0;
    }

  TOSH_queue[old_full].tp = (void *)0;
  TOSH_sched_full = (old_full + 1) & TOSH_TASK_BITMASK;
  __nesc_atomic_end(fInterruptFlags);
  func();

  return 1;
}

# 124 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/Nido.nc"
int   main(int argc, char **argv)
#line 124
{
  long long i;
  long long last_power_time = 0;

  int power_profiling = 0;
  int cpu_profiling = 0;
  int num_nodes_total;
  int num_nodes_start = -1;
  int random_seed = 0;
  int random_seed_set = 0;

  unsigned long long max_run_time = 0;

  char *adc_model_name = (void *)0;
  char *model_name = (void *)0;
  char *eeprom_name = (void *)0;

  int start_time = 0;
  int pause_time = 0;
  int start_interval = 10;
  char *rate_constant = "1000.0";
  char *lossy_file = (void *)0;

  int radio_kb_rate = 40;

  int currentArg;

  if (argc == 2 && (strcmp(argv[1], "-h") == 0 || 
  strcmp(argv[1], "--help") == 0)) {
      Nido$help(argv[0]);
    }

  if (argc < 2) {
#line 156
      Nido$usage(argv[0]);
    }
  dbg_init();

  for (currentArg = 1; currentArg < argc - 1; currentArg++) {
      char *arg = argv[currentArg];

#line 162
      if (strcmp(arg, "-h") == 0 || 
      strcmp(arg, "--help") == 0) {
          Nido$help(argv[0]);
        }
      else {
#line 166
        if (strcmp(argv[currentArg], "--help") == 0) {
            Nido$help(argv[0]);
          }
        else {
#line 169
          if (strcmp(arg, "-gui") == 0) {
              GUI_enabled = 1;
            }
          else {
#line 172
            if (strcmp(arg, "-nodbgout") == 0) {
                dbg_suppress_stdout = 1;
              }
            else {
#line 175
              if (strncmp(arg, "-a=", 3) == 0) {
                  arg += 3;
                  adc_model_name = arg;
                }
              else {
#line 179
                if (strncmp(arg, "-b=", 3) == 0) {
                    arg += 3;
                    start_interval = atoi(arg);
                    if (start_interval < 0) {
                        fprintf(_impure_ptr->_stderr, "SIM: boot time value must be a positive integer, not %s\n", arg);
                        exit(-1);
                      }
                  }
                else {
#line 187
                  if (strncmp(arg, "-ef=", 3) == 0) {
                      arg += 4;
                      eeprom_name = arg;
                    }
                  else {
#line 191
                    if (strncmp(arg, "-l=", 3) == 0) {
                        arg += 3;
                        rate_constant = arg;
                      }
                    else {
#line 195
                      if (strncmp(arg, "-r=", 3) == 0) {
                          arg += 3;
                          model_name = arg;
                        }
                      else {
#line 199
                        if (strncmp(arg, "-rf=", 4) == 0) {
                            arg += 4;
                            model_name = "lossy";
                            lossy_file = arg;
                          }
                        else {
#line 204
                          if (strncmp(arg, "-s=", 3) == 0) {
                              arg += 3;
                              num_nodes_start = atoi(arg);
                            }
                          else {
#line 208
                            if (strncmp(arg, "-t=", 3) == 0) {
                                arg += 3;
                                max_run_time = (unsigned long long )atoi(arg);
                                max_run_time *= 4000000;
                              }
                            else {
#line 213
                              if (strncmp(arg, "-seed=", 6) == 0) {
                                  arg += 6;
                                  random_seed = atoi(arg);
                                  random_seed_set = 1;
                                }
                              else {
#line 218
                                if (strcmp(arg, "-p") == 0) {
                                    power_profiling = 1;
                                  }
                                else {
#line 221
                                  if (strcmp(arg, "-cpuprof") == 0) {
                                      cpu_profiling = 1;
                                    }
                                  else {
                                      Nido$usage(argv[0]);
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
    }
#line 229
  set_rate_value(atof(rate_constant));
  if (get_rate_value() <= 0.0) {
      fprintf(_impure_ptr->_stderr, "SIM: Invalid rate constant: %s.\n", rate_constant);
      exit(-1);
    }

  num_nodes_total = atoi(argv[argc - 1]);
  if (num_nodes_total <= 0) {
#line 236
      Nido$usage(argv[0]);
    }
  if (num_nodes_start < 0 || num_nodes_start > num_nodes_total) {
      num_nodes_start = num_nodes_total;
    }



  Nido$PowerState$init(power_profiling, cpu_profiling);


  if (num_nodes_total > TOSNODES) {
      fprintf(_impure_ptr->_stderr, "Nido: I am compiled for maximum of %d nodes and you have specified %d nodes.\n", TOSNODES, num_nodes_total);
      fprintf(_impure_ptr->_stderr, "Nido: Exiting...\n");
      exit(-1);
    }

  init_signals();

  tos_state.num_nodes = num_nodes_total;



  if (model_name == (void *)0 || strcmp(model_name, "simple") == 0) {
      tos_state.rfm = create_simple_model();
      tos_state.radioModel = TOSSIM_RADIO_MODEL_SIMPLE;
    }
  else {
#line 263
    if (strcmp(model_name, "lossy") == 0) {
        tos_state.rfm = create_lossy_model(lossy_file);
        tos_state.radioModel = TOSSIM_RADIO_MODEL_LOSSY;
      }
    else {
        fprintf(_impure_ptr->_stderr, "SIM: Don't recognize RFM model type %s.\n", model_name);
        exit(-1);
      }
    }


  if (adc_model_name == (void *)0 || strcmp(adc_model_name, "generic") == 0) {
      tos_state.adc = create_generic_adc_model();
    }
  else {
#line 277
    if (strcmp(adc_model_name, "random") == 0) {
        tos_state.adc = create_random_adc_model();
      }
    else {
        fprintf(_impure_ptr->_stderr, "SIM: Bad ADC model name: %s\n", adc_model_name);
        exit(-1);
      }
    }
#line 284
  if (eeprom_name != (void *)0) {
      namedEEPROM(eeprom_name, num_nodes_total, DEFAULT_EEPROM_SIZE);
    }
  else {
      anonymousEEPROM(num_nodes_total, DEFAULT_EEPROM_SIZE);
    }
  dbg_clear(DBG_SIM | DBG_BOOT, "SIM: EEPROM system initialized.\n");

  tos_state.space = create_simple_spatial_model();

  tos_state.radio_kb_rate = radio_kb_rate;
  tos_state_model_init();
  packet_sim_init();

  init_hardware();

  queue_init(& tos_state.queue, pause_time);
  dbg_clear(DBG_SIM, "SIM: event queue initialized.\n");

  if (!random_seed_set) {
      struct timeval tv;

#line 305
      gettimeofday(&tv, (void *)0);
      random_seed = tv.tv_usec;
    }


  dbg_clear(DBG_ALL, "SIM: Random seed is %i\n", random_seed);
  srand(random_seed);

  initializeSockets();

  if (GUI_enabled) {
      waitForGuiConnection();
    }

  for (i = 0; i < num_nodes_start; i++) {

      int rval = rand();

#line 322
      if (start_interval > 0) {
          rval %= 4000000 * start_interval;
          start_time = rval + i;
        }
      else {
#line 325
        if (start_interval == 0) {
            start_time = i;
          }
        }
      tos_state.node_state[i].time = start_time;
      dbg_clear(DBG_SIM | DBG_USR3, "SIM: Time for mote %lli initialized to %lli.\n", 
      i, tos_state.node_state[i].time);
    }

  for (i = 0; i < num_nodes_start; i++) {
      char timeVal[128];
      event_t *fevent = (event_t *)malloc(sizeof(event_t ));

#line 337
      fevent->mote = i;
      fevent->time = tos_state.node_state[i].time;
      fevent->handle = event_boot_handle;
      fevent->cleanup = event_default_cleanup;
      fevent->pause = 0;
      fevent->force = 1;
      queue_insert_event(& tos_state.queue, fevent);
#line 343
      ;
      printOtherTime(timeVal, 128, tos_state.node_state[i].time);
      dbg(DBG_BOOT, "BOOT: Scheduling for boot at %s.\n", timeVal);
    }

  rate_checkpoint();

  for (; ; ) {
      if (max_run_time > 0 && tos_state.tos_time >= max_run_time) {
          break;
        }

      pthread_mutex_lock(& tos_state.pause_lock);
      if (tos_state.paused == TRUE) {
          pthread_cond_signal(& tos_state.pause_ack_cond);
          pthread_cond_wait(& tos_state.pause_cond, & tos_state.pause_lock);
        }
      pthread_mutex_unlock(& tos_state.pause_lock);

      while (TOSH_run_next_task()) {
        }
#line 363
      if (!queue_is_empty(& tos_state.queue)) {
          tos_state.tos_time = queue_peek_event_time(& tos_state.queue);
          queue_handle_next_event(& tos_state.queue);



          rate_based_wait();
        }
      if (cpu_profiling) {



          if (tos_state.tos_time - last_power_time > (long long )4000000 / 5) 
            {
              Nido$PowerState$CPUCycleCheckpoint();
              last_power_time = tos_state.tos_time;
            }
        }
    }
  if (power_profiling || cpu_profiling) {
      Nido$PowerState$stop();
    }
  printf("Simulation of %i motes completed.\n", num_nodes_total);



  {
    int moteID;

#line 391
    for (moteID = 0; moteID < tos_state.num_nodes; moteID++) 
      {
        { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
          {
            {
#line 395
              float td = (tos_state.tos_time - PrevCPUCycles[moteID]) / em_CPU_FREQ;
#line 395
              float engConsumed = td * CPUCrt[moteID] * em_VOLTAGE;
#line 395
              float engProduced = td * scavengerCrt * em_VOLTAGE;

#line 395
              batteryEnergy[moteID] = batteryEnergy[moteID] - engConsumed + engProduced;
#line 395
              totalCPUEng[moteID] += engConsumed;
#line 395
              printf("Alex - mote %d: totalCPUEng=%.5f CPUCrt=%.2f PrevCPUCycles=%d tos_state.tos_time=%lld batteryEnergy=%.2f scavengerCrt=%.2f\n", moteID, totalCPUEng[moteID], CPUCrt[moteID], PrevCPUCycles[moteID], tos_state.tos_time, batteryEnergy[moteID], scavengerCrt);
#line 395
              if (0) {
#line 395
                PrevCPUCycles[moteID] = tos_state.tos_time;
                }
            }
#line 395
            ;
            {
#line 396
              float td = (tos_state.tos_time - PrevCPUCycles[moteID]) / em_CPU_FREQ;
#line 396
              float engConsumed = td * radioCrt[moteID] * em_VOLTAGE;
#line 396
              float engProduced = td * scavengerCrt * em_VOLTAGE;

#line 396
              totalRadioEng[moteID] += engConsumed;
#line 396
              batteryEnergy[moteID] = batteryEnergy[moteID] - engConsumed + engProduced;
#line 396
              printf("Alex - mote %d: totalRadioEng=%.5f radioCrt=%.2f PrevCPUCycles=%d tos_state.tos_time=%lld batteryEnergy=%.2f scavengerCrt=%.2f\n", moteID, totalRadioEng[moteID], radioCrt[moteID], PrevCPUCycles[moteID], tos_state.tos_time, batteryEnergy[moteID], scavengerCrt);
#line 396
              if (tos_state.tos_time - PrevCPUCycles[moteID] >= 4000000) {
#line 396
                Nido$ReadScavengerProfile();
                }
#line 396
              if (0) {
#line 396
                PrevCPUCycles[moteID] = tos_state.tos_time;
                }
            }
#line 396
            ;
          }
#line 397
          __nesc_atomic_end(__nesc_atomic); }
      }
  }

  fclose(finScavenger);

  return 0;
}

static 
#line 79
void Nido$help(char *progname)
#line 79
{
  fprintf(_impure_ptr->_stderr, "Usage: %s [options] num_nodes\n", progname);
  fprintf(_impure_ptr->_stderr, "  [options] are:\n");
  fprintf(_impure_ptr->_stderr, "  -h, --help        Display this message.\n");
  fprintf(_impure_ptr->_stderr, "  -gui              pauses simulation waiting for GUI to connect\n");
  fprintf(_impure_ptr->_stderr, "  -nodbgout     only send dbg messages to GUI, not to stdout\n");
  fprintf(_impure_ptr->_stderr, "  -a=<model>        specifies ADC model (generic is default)\n");
  fprintf(_impure_ptr->_stderr, "                    options: generic random\n");
  fprintf(_impure_ptr->_stderr, "  -b=<sec>          motes boot over first <sec> seconds (default 10)\n");
  fprintf(_impure_ptr->_stderr, "  -ef=<file>        use <file> for eeprom; otherwise anonymous file is used\n");
  fprintf(_impure_ptr->_stderr, "  -l=<scale>        run sim at <scale> times real time (fp constant)\n");
  fprintf(_impure_ptr->_stderr, "  -r=<model>        specifies a radio model (simple is default)\n");
  fprintf(_impure_ptr->_stderr, "                    options: simple lossy\n");
  fprintf(_impure_ptr->_stderr, "  -rf=<file>        specifies file for lossy mode (lossy.nss is default)\n");
  fprintf(_impure_ptr->_stderr, "                    implicitly selects lossy model\n");
  fprintf(_impure_ptr->_stderr, "  -s=<num>          only boot <num> of nodes\n");
  fprintf(_impure_ptr->_stderr, "  -t=<sec>          run simulation for <sec> virtual seconds\n");
  fprintf(_impure_ptr->_stderr, "  -seed=<seed>      use random seed <seed>\n");
  fprintf(_impure_ptr->_stderr, "  -p                do power profiling\n");
  fprintf(_impure_ptr->_stderr, "  -cpuprof          do cpu profiling (only if compiled with cilly!)\n");
  fprintf(_impure_ptr->_stderr, "  num_nodes         number of nodes to simulate\n");

  fprintf(_impure_ptr->_stderr, "\n");
  dbg_help();
  fprintf(_impure_ptr->_stderr, "\n");
  exit(-1);
}

static 
# 78 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adjacency_list.c"
int adjacency_list_init(void)
#line 78
{
  int i;

#line 80
  free_list = (link_t *)malloc(sizeof(link_t ) * NUM_NODES_ALLOC);
  for (i = 0; i < NUM_NODES_ALLOC - 1; i++) {
      free_list[i].next_link = &free_list[i + 1];
    }
  free_list[NUM_NODES_ALLOC - 1].next_link = (void *)0;
  num_free_links = NUM_NODES_ALLOC;
  return SUCCESS;
}

static 
# 194 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/rfm_model.c"
void static_one_cell_init(void)
#line 194
{
  int i;
#line 195
  int j;
  link_t *new_link;

  pthread_mutex_init(&radioConnectivityLock, (void *)0);
  radio_connectivity[0] = (void *)0;

  for (i = 0; i < tos_state.num_nodes; i++) {
      for (j = 0; j < tos_state.num_nodes; j++) {
          if (i != j) {
              new_link = allocate_link(j);
              new_link->data = 0.0;

              new_link->next_link = radio_connectivity[i];
              radio_connectivity[i] = new_link;
            }
        }
    }
}

static 
# 47 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/adjacency_list.c"
link_t *allocate_link(int mote)
#line 47
{
  link_t *alloc_link;
  int i;

#line 50
  if (0 == num_free_links) {
      alloc_link = (link_t *)malloc(sizeof(link_t ) * NUM_NODES_ALLOC);
      for (i = 0; i < NUM_NODES_ALLOC - 1; i++) {
          alloc_link[i].next_link = &alloc_link[i + 1];
        }
      alloc_link[NUM_NODES_ALLOC - 1].next_link = free_list;
      free_list = alloc_link;
      num_free_links += NUM_NODES_ALLOC;
    }
  else {
      alloc_link = free_list;
    }

  free_list = free_list->next_link;
  alloc_link->mote = mote;
  alloc_link->next_link = (void *)0;
  num_free_links--;
  return alloc_link;
}

static 
# 58 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/eeprom.c"
int createEEPROM(char *file, int motes, int eempromBytes)
#line 58
{
  int rval;
  char val = 0;

  local_filename = file;
  numMotes = motes;
  moteSize = eempromBytes;

  if (initialized) {
      dbg(DBG_ERROR, "ERROR: Trying to initialize EEPROM twice.\n");
      return -1;
    }
  local_fd = open(file, 2 | 0x0200, (((0000400 | 0000200) | 0000100) | 0000040) | 0000004);

  if (local_fd < 0) {
      dbg(DBG_ERROR, "ERROR: Unable to create EEPROM backing store file.\n");
      return -1;
    }

  rval = (int )lseek(local_fd, moteSize * numMotes, 0);
  if (rval < 0) {
      dbg(DBG_ERROR, "ERROR: Unable to establish EEPROM of correct size.\n");
    }

  rval = write(local_fd, &val, 1);
  if (rval < 0) {
      dbg(DBG_ERROR, "ERROR: Unable to establish EEPROM of correct size.\n");
    }
  initialized = 1;

  return local_fd;
}

static 
# 168 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/external_comm.c"
int createServerSocket(short port)
#line 168
{
  struct sockaddr_in sock;
  int sfd;
  int rval = -1;
  long enable = 1;

  memset(&sock, 0, sizeof sock);
  sock.sin_family = 2;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = htonl(0x7f000001);

  sfd = socket(2, 1, 0);
  if (sfd < 0) {
      dbg_clear(DBG_SIM | DBG_ERROR, "SIM: Could not create server socket: %s\n", strerror(*__errno()));
      exit(-1);
    }
  setsockopt(sfd, 0xffff, 0x0004, (char *)&enable, sizeof(int ));

  while (rval < 0) {
      rval = bind(sfd, (struct sockaddr *)&sock, sizeof sock);
      if (rval < 0) {
          dbg_clear(DBG_SIM | DBG_ERROR, "SIM: Could not bind server socket to port %d: %s\n", port, strerror(*__errno()));
          dbg_clear(DBG_SIM | DBG_ERROR, "SIM: Perhaps another copy of TOSSIM is already running?\n");
          dbg_clear(DBG_SIM | DBG_ERROR, "SIM: Will retry in 10 seconds.\n");
          sleep(10);
        }
    }

  if (listen(sfd, 1) < 0) {
      dbg_clear(DBG_SIM | DBG_ERROR, "SIM: Could not listen on server socket: %s\n", strerror(*__errno()));
      exit(-1);
    }
  dbg_clear(DBG_SIM, "SIM: Created server socket listening on port %d.\n", port);
  return sfd;
}

static 
#line 152
int acceptConnection(int servfd)
#line 152
{
  struct sockaddr_in cli_addr;
  int clilen = sizeof cli_addr;
  int clifd;

  ;
  clifd = accept(servfd, (struct sockaddr *)&cli_addr, &clilen);
  if (clifd < 0) {
      ;

      exit(-1);
    }
  ;
  return clifd;
}

static 
#line 272
void addClient(int *clientSockets, int clifd)
#line 272
{
  int i;

  for (i = 0; i < 4; i++) {
      if (clientSockets[i] == -1) {
          clientSockets[i] = clifd;
          return;
        }
    }


  close(clifd);
}

static  
# 168 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/system/TimerM.nc"
result_t TimerM$Timer$stop(uint8_t id)
#line 168
{

  if (id >= NUM_TIMERS) {
#line 170
    return FAIL;
    }
#line 171
  if (TimerM$mState[tos_state.current_node] & (0x1L << id)) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 172
        TimerM$mState[tos_state.current_node] &= ~(0x1L << id);
#line 172
        __nesc_atomic_end(__nesc_atomic); }
      if (!TimerM$mState[tos_state.current_node]) {
          TimerM$setIntervalFlag[tos_state.current_node] = 1;
        }
      return SUCCESS;
    }
  return FAIL;
}

static 
# 104 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/heap_array.c"
void *heap_pop_min_data(heap_t *heap, long long *key)
#line 104
{
  int last_index = heap->size - 1;
  void *data = ((node_t *)heap->data)[0].data;

#line 107
  if (key != (void *)0) {
      *key = ((node_t *)heap->data)[0].key;
    }
  ((node_t *)heap->data)[0].data = ((node_t *)heap->data)[last_index].data;
  ((node_t *)heap->data)[0].key = ((node_t *)heap->data)[last_index].key;

  heap->size--;

  down_heap(heap, 0);

  return data;
}

static 
#line 161
void down_heap(heap_t *heap, int findex)
#line 161
{
  int right_index = (findex + 1) * 2;
  int left_index = findex * 2 + 1;

  if (right_index < heap->size) {
      long long left_key = ((node_t *)heap->data)[left_index].key;
      long long right_key = ((node_t *)heap->data)[right_index].key;
      int min_key_index = left_key < right_key ? left_index : right_index;

      if (((node_t *)heap->data)[min_key_index].key < ((node_t *)heap->data)[findex].key) {
          swap(&((node_t *)heap->data)[findex], &((node_t *)heap->data)[min_key_index]);
          down_heap(heap, min_key_index);
        }
    }
  else {
#line 175
    if (left_index >= heap->size) {
        return;
      }
    else {
        long long left_key = ((node_t *)heap->data)[left_index].key;

#line 180
        if (left_key < ((node_t *)heap->data)[findex].key) {
            swap(&((node_t *)heap->data)[findex], &((node_t *)heap->data)[left_index]);
            return;
          }
      }
    }
}

static   
# 389 "C:/tinyos/cygwin/opt/tinyos-1.x/tos/platform/pc/PowerStateM.nc"
double PowerStateM$PowerState$get_mote_cycles(int mote)
#line 389
{
  int bb;
  double total;

#line 392
  if (!cpu_prof_on) {
      fprintf(_impure_ptr->_stderr, "get_mote_cycles() called when cpu prof is off!  Shouldn't happen!\n");
      exit(-1);
    }

  total = 0;
  for (bb = 1; bb < PowerStateM$num_bbs(); bb++) {
      total += PowerStateM$bb_exec_count(mote, bb) * cycles[bb];
    }
  return total;
}

/* Nido variable resolver function */

static int __nesc_nido_resolve(int __nesc_mote,
                               char* varname,
                               uintptr_t* addr, size_t* size)
{
  /* Module Nido */

  /* Module PotM */

  /* Module HPLPotC */

  /* Module PowerStateM */

  /* Module TOSwqrsM */
  if (!strcmp(varname, "TOSwqrsM$testinput"))
  {
    *addr = (uintptr_t)&TOSwqrsM$testinput[__nesc_mote];
    *size = sizeof(TOSwqrsM$testinput[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TOSwqrsM$datapck"))
  {
    *addr = (uintptr_t)&TOSwqrsM$datapck[__nesc_mote];
    *size = sizeof(TOSwqrsM$datapck[__nesc_mote]);
    return 0;
  }

  /* Module LedsM */
  if (!strcmp(varname, "LedsM$ledsOn"))
  {
    *addr = (uintptr_t)&LedsM$ledsOn[__nesc_mote];
    *size = sizeof(LedsM$ledsOn[__nesc_mote]);
    return 0;
  }

  /* Module TimerM */
  if (!strcmp(varname, "TimerM$mState"))
  {
    *addr = (uintptr_t)&TimerM$mState[__nesc_mote];
    *size = sizeof(TimerM$mState[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$setIntervalFlag"))
  {
    *addr = (uintptr_t)&TimerM$setIntervalFlag[__nesc_mote];
    *size = sizeof(TimerM$setIntervalFlag[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$mScale"))
  {
    *addr = (uintptr_t)&TimerM$mScale[__nesc_mote];
    *size = sizeof(TimerM$mScale[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$mInterval"))
  {
    *addr = (uintptr_t)&TimerM$mInterval[__nesc_mote];
    *size = sizeof(TimerM$mInterval[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$queue_head"))
  {
    *addr = (uintptr_t)&TimerM$queue_head[__nesc_mote];
    *size = sizeof(TimerM$queue_head[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$queue_tail"))
  {
    *addr = (uintptr_t)&TimerM$queue_tail[__nesc_mote];
    *size = sizeof(TimerM$queue_tail[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$queue_size"))
  {
    *addr = (uintptr_t)&TimerM$queue_size[__nesc_mote];
    *size = sizeof(TimerM$queue_size[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$queue"))
  {
    *addr = (uintptr_t)&TimerM$queue[__nesc_mote];
    *size = sizeof(TimerM$queue[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$interval_outstanding"))
  {
    *addr = (uintptr_t)&TimerM$interval_outstanding[__nesc_mote];
    *size = sizeof(TimerM$interval_outstanding[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "TimerM$mTimerList"))
  {
    *addr = (uintptr_t)&TimerM$mTimerList[__nesc_mote];
    *size = sizeof(TimerM$mTimerList[__nesc_mote]);
    return 0;
  }

  /* Module HPLClock */
  if (!strcmp(varname, "HPLClock$set_flag"))
  {
    *addr = (uintptr_t)&HPLClock$set_flag[__nesc_mote];
    *size = sizeof(HPLClock$set_flag[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "HPLClock$mscale"))
  {
    *addr = (uintptr_t)&HPLClock$mscale[__nesc_mote];
    *size = sizeof(HPLClock$mscale[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "HPLClock$nextScale"))
  {
    *addr = (uintptr_t)&HPLClock$nextScale[__nesc_mote];
    *size = sizeof(HPLClock$nextScale[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "HPLClock$minterval"))
  {
    *addr = (uintptr_t)&HPLClock$minterval[__nesc_mote];
    *size = sizeof(HPLClock$minterval[__nesc_mote]);
    return 0;
  }

  /* Module NoLeds */

  /* Module HPLPowerManagementM */

  /* Module AMStandard */
  if (!strcmp(varname, "AMStandard$state"))
  {
    *addr = (uintptr_t)&AMStandard$state[__nesc_mote];
    *size = sizeof(AMStandard$state[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "AMStandard$lastCount"))
  {
    *addr = (uintptr_t)&AMStandard$lastCount[__nesc_mote];
    *size = sizeof(AMStandard$lastCount[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "AMStandard$counter"))
  {
    *addr = (uintptr_t)&AMStandard$counter[__nesc_mote];
    *size = sizeof(AMStandard$counter[__nesc_mote]);
    return 0;
  }

  /* Module MicaHighSpeedRadioM */
  if (!strcmp(varname, "MicaHighSpeedRadioM$state"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$state[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$state[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$send_state"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$send_state[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$send_state[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$tx_count"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$tx_count[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$tx_count[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$calc_crc"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$calc_crc[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$calc_crc[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$ack_count"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$ack_count[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$ack_count[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$rec_count"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$rec_count[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$rec_count[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$buffer"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$buffer[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$buffer[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$rec_ptr"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$rec_ptr[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$rec_ptr[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$send_ptr"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$send_ptr[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$send_ptr[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$rx_count"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$rx_count[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$rx_count[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$msg_length"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$msg_length[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$msg_length[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$buf_head"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$buf_head[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$buf_head[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$buf_end"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$buf_end[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$buf_end[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$encoded_buffer"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$encoded_buffer[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$encoded_buffer[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "MicaHighSpeedRadioM$enc_count"))
  {
    *addr = (uintptr_t)&MicaHighSpeedRadioM$enc_count[__nesc_mote];
    *size = sizeof(MicaHighSpeedRadioM$enc_count[__nesc_mote]);
    return 0;
  }

  /* Module SecDedEncoding */
  if (!strcmp(varname, "SecDedEncoding$data1"))
  {
    *addr = (uintptr_t)&SecDedEncoding$data1[__nesc_mote];
    *size = sizeof(SecDedEncoding$data1[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "SecDedEncoding$data2"))
  {
    *addr = (uintptr_t)&SecDedEncoding$data2[__nesc_mote];
    *size = sizeof(SecDedEncoding$data2[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "SecDedEncoding$data3"))
  {
    *addr = (uintptr_t)&SecDedEncoding$data3[__nesc_mote];
    *size = sizeof(SecDedEncoding$data3[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "SecDedEncoding$state"))
  {
    *addr = (uintptr_t)&SecDedEncoding$state[__nesc_mote];
    *size = sizeof(SecDedEncoding$state[__nesc_mote]);
    return 0;
  }

  /* Module RandomLFSR */
  if (!strcmp(varname, "RandomLFSR$shiftReg"))
  {
    *addr = (uintptr_t)&RandomLFSR$shiftReg[__nesc_mote];
    *size = sizeof(RandomLFSR$shiftReg[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "RandomLFSR$initSeed"))
  {
    *addr = (uintptr_t)&RandomLFSR$initSeed[__nesc_mote];
    *size = sizeof(RandomLFSR$initSeed[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "RandomLFSR$mask"))
  {
    *addr = (uintptr_t)&RandomLFSR$mask[__nesc_mote];
    *size = sizeof(RandomLFSR$mask[__nesc_mote]);
    return 0;
  }

  /* Module ChannelMonC */
  if (!strcmp(varname, "channelMonEvents"))
  {
    *addr = (uintptr_t)&channelMonEvents[__nesc_mote];
    *size = sizeof(channelMonEvents[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "ChannelMonC$CM_search"))
  {
    *addr = (uintptr_t)&ChannelMonC$CM_search[__nesc_mote];
    *size = sizeof(ChannelMonC$CM_search[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "ChannelMonC$CM_state"))
  {
    *addr = (uintptr_t)&ChannelMonC$CM_state[__nesc_mote];
    *size = sizeof(ChannelMonC$CM_state[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "ChannelMonC$CM_lastBit"))
  {
    *addr = (uintptr_t)&ChannelMonC$CM_lastBit[__nesc_mote];
    *size = sizeof(ChannelMonC$CM_lastBit[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "ChannelMonC$CM_startSymBits"))
  {
    *addr = (uintptr_t)&ChannelMonC$CM_startSymBits[__nesc_mote];
    *size = sizeof(ChannelMonC$CM_startSymBits[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "ChannelMonC$CM_waiting"))
  {
    *addr = (uintptr_t)&ChannelMonC$CM_waiting[__nesc_mote];
    *size = sizeof(ChannelMonC$CM_waiting[__nesc_mote]);
    return 0;
  }

  /* Module RadioTimingC */
  if (!strcmp(varname, "radioTimingEvents"))
  {
    *addr = (uintptr_t)&radioTimingEvents[__nesc_mote];
    *size = sizeof(radioTimingEvents[__nesc_mote]);
    return 0;
  }

  /* Module SpiByteFifoC */
  if (!strcmp(varname, "SpiByteFifoC$nextByte"))
  {
    *addr = (uintptr_t)&SpiByteFifoC$nextByte[__nesc_mote];
    *size = sizeof(SpiByteFifoC$nextByte[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "SpiByteFifoC$state"))
  {
    *addr = (uintptr_t)&SpiByteFifoC$state[__nesc_mote];
    *size = sizeof(SpiByteFifoC$state[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "SpiByteFifoC$spdr"))
  {
    *addr = (uintptr_t)&SpiByteFifoC$spdr[__nesc_mote];
    *size = sizeof(SpiByteFifoC$spdr[__nesc_mote]);
    return 0;
  }
  if (!strcmp(varname, "SpiByteFifoC$radioState"))
  {
    *addr = (uintptr_t)&SpiByteFifoC$radioState[__nesc_mote];
    *size = sizeof(SpiByteFifoC$radioState[__nesc_mote]);
    return 0;
  }

  /* Module CrcFilter */

  /* Module UARTNoCRCPacketM */

  /* Module BeaconM */

  return -1;
}
/* Invoke static initialisers for mote '__nesc_mote' */

static void __nesc_nido_initialise(int __nesc_mote)
{
  /* Module Nido */

  /* Module PotM */

  /* Module HPLPotC */

  /* Module PowerStateM */

  /* Module TOSwqrsM */
  memcpy(&TOSwqrsM$testinput[__nesc_mote], &(int [163]){ 1208, 1144, 1033, 962, 934, 931, 943, 946, 946, 948, 946, 946, 948, 944, 941, 945, 944, 945, 948, 945, 942, 944, 946, 942, 942, 942, 941, 942, 944, 944, 942, 945, 947, 942, 944, 948, 945, 942, 946, 946, 941, 942, 944, 940, 940, 940, 939, 937, 938, 937, 932, 935, 935, 931, 931, 934, 930, 930, 934, 935, 937, 943, 950, 951, 955, 960, 958, 958, 962, 963, 959, 962, 964, 960, 960, 964, 961, 960, 962, 961, 960, 963, 965, 960, 961, 962, 960, 959, 960, 959, 956, 956, 958, 955, 954, 958, 956, 954, 958, 957, 954, 957, 957, 953, 952, 955, 955, 954, 957, 957, 953, 955, 956, 953, 954, 957, 956, 956, 957, 956, 955, 956, 962, 964, 966, 970, 971, 972, 977, 979, 975, 975, 976, 972, 968, 973, 980, 975, 968, 966, 960, 956, 957, 951, 952, 954, 951, 948, 950, 950, 947, 948, 951, 945, 941, 932, 922, 910, 923, 973, 1039, 1140, 1211 }, sizeof TOSwqrsM$testinput[__nesc_mote]);
  memset(&TOSwqrsM$datapck[__nesc_mote], 0, sizeof TOSwqrsM$datapck[__nesc_mote]);
  TOSwqrsM$get_sample_from_core$counter[__nesc_mote] = 0;

  /* Module LedsM */
  memset(&LedsM$ledsOn[__nesc_mote], 0, sizeof LedsM$ledsOn[__nesc_mote]);

  /* Module TimerM */
  memset(&TimerM$mState[__nesc_mote], 0, sizeof TimerM$mState[__nesc_mote]);
  memset(&TimerM$setIntervalFlag[__nesc_mote], 0, sizeof TimerM$setIntervalFlag[__nesc_mote]);
  memset(&TimerM$mScale[__nesc_mote], 0, sizeof TimerM$mScale[__nesc_mote]);
  memset(&TimerM$mInterval[__nesc_mote], 0, sizeof TimerM$mInterval[__nesc_mote]);
  memset(&TimerM$queue_head[__nesc_mote], 0, sizeof TimerM$queue_head[__nesc_mote]);
  memset(&TimerM$queue_tail[__nesc_mote], 0, sizeof TimerM$queue_tail[__nesc_mote]);
  memset(&TimerM$queue_size[__nesc_mote], 0, sizeof TimerM$queue_size[__nesc_mote]);
  memset(&TimerM$queue[__nesc_mote], 0, sizeof TimerM$queue[__nesc_mote]);
  memset(&TimerM$interval_outstanding[__nesc_mote], 0, sizeof TimerM$interval_outstanding[__nesc_mote]);
  memset(&TimerM$mTimerList[__nesc_mote], 0, sizeof TimerM$mTimerList[__nesc_mote]);

  /* Module HPLClock */
  memset(&HPLClock$set_flag[__nesc_mote], 0, sizeof HPLClock$set_flag[__nesc_mote]);
  memset(&HPLClock$mscale[__nesc_mote], 0, sizeof HPLClock$mscale[__nesc_mote]);
  memset(&HPLClock$nextScale[__nesc_mote], 0, sizeof HPLClock$nextScale[__nesc_mote]);
  memset(&HPLClock$minterval[__nesc_mote], 0, sizeof HPLClock$minterval[__nesc_mote]);

  /* Module NoLeds */

  /* Module HPLPowerManagementM */

  /* Module AMStandard */
  memset(&AMStandard$state[__nesc_mote], 0, sizeof AMStandard$state[__nesc_mote]);
  memset(&AMStandard$lastCount[__nesc_mote], 0, sizeof AMStandard$lastCount[__nesc_mote]);
  memset(&AMStandard$counter[__nesc_mote], 0, sizeof AMStandard$counter[__nesc_mote]);

  /* Module MicaHighSpeedRadioM */
  memset(&MicaHighSpeedRadioM$state[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$state[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$send_state[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$send_state[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$tx_count[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$tx_count[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$calc_crc[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$calc_crc[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$ack_count[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$ack_count[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$rec_count[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$rec_count[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$buffer[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$buffer[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$rec_ptr[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$rec_ptr[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$send_ptr[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$send_ptr[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$rx_count[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$rx_count[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$msg_length[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$msg_length[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$buf_head[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$buf_head[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$buf_end[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$buf_end[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$encoded_buffer[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$encoded_buffer[__nesc_mote]);
  memset(&MicaHighSpeedRadioM$enc_count[__nesc_mote], 0, sizeof MicaHighSpeedRadioM$enc_count[__nesc_mote]);

  /* Module SecDedEncoding */
  memset(&SecDedEncoding$data1[__nesc_mote], 0, sizeof SecDedEncoding$data1[__nesc_mote]);
  memset(&SecDedEncoding$data2[__nesc_mote], 0, sizeof SecDedEncoding$data2[__nesc_mote]);
  memset(&SecDedEncoding$data3[__nesc_mote], 0, sizeof SecDedEncoding$data3[__nesc_mote]);
  memset(&SecDedEncoding$state[__nesc_mote], 0, sizeof SecDedEncoding$state[__nesc_mote]);

  /* Module RandomLFSR */
  memset(&RandomLFSR$shiftReg[__nesc_mote], 0, sizeof RandomLFSR$shiftReg[__nesc_mote]);
  memset(&RandomLFSR$initSeed[__nesc_mote], 0, sizeof RandomLFSR$initSeed[__nesc_mote]);
  memset(&RandomLFSR$mask[__nesc_mote], 0, sizeof RandomLFSR$mask[__nesc_mote]);

  /* Module ChannelMonC */
  memset(&channelMonEvents[__nesc_mote], 0, sizeof channelMonEvents[__nesc_mote]);
  memset(&ChannelMonC$CM_search[__nesc_mote], 0, sizeof ChannelMonC$CM_search[__nesc_mote]);
  memset(&ChannelMonC$CM_state[__nesc_mote], 0, sizeof ChannelMonC$CM_state[__nesc_mote]);
  memset(&ChannelMonC$CM_lastBit[__nesc_mote], 0, sizeof ChannelMonC$CM_lastBit[__nesc_mote]);
  memset(&ChannelMonC$CM_startSymBits[__nesc_mote], 0, sizeof ChannelMonC$CM_startSymBits[__nesc_mote]);
  memset(&ChannelMonC$CM_waiting[__nesc_mote], 0, sizeof ChannelMonC$CM_waiting[__nesc_mote]);

  /* Module RadioTimingC */
  memset(&radioTimingEvents[__nesc_mote], 0, sizeof radioTimingEvents[__nesc_mote]);

  /* Module SpiByteFifoC */
  memset(&SpiByteFifoC$nextByte[__nesc_mote], 0, sizeof SpiByteFifoC$nextByte[__nesc_mote]);
  memset(&SpiByteFifoC$state[__nesc_mote], 0, sizeof SpiByteFifoC$state[__nesc_mote]);
  memset(&SpiByteFifoC$spdr[__nesc_mote], 0, sizeof SpiByteFifoC$spdr[__nesc_mote]);
  memset(&SpiByteFifoC$radioState[__nesc_mote], 0, sizeof SpiByteFifoC$radioState[__nesc_mote]);

  /* Module CrcFilter */

  /* Module UARTNoCRCPacketM */

  /* Module BeaconM */

}
