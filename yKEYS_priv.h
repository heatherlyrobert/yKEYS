/*============================----beg-of-source---============================*/
#ifndef yKEYS_priv
#define yKEYS_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "keys tracking and control
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "hermes-tresmegistus (thrice greatest)"
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    "god of letters and writing"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yMODE"
#define     P_FULLNAME  "/usr/local/lib64/libyMODE"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, separated into independent library"
#define     P_VERNUM    "2.0h"
#define     P_VERTXT    "logger and repeat mode in place"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
/*---(custom)----------------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
#include    <yMODE.h>             /* heatherly yVIKEYS mode tracking          */
#include    <yMACRO.h>            /* heatherly yVIKEYS macro processing       */
#include    <yVIKEYS_solo.h>      /* heatherly yVIKEYS constants              */



extern char  g_vsimple   [LEN_DESC ];
extern char  g_vgoto     [LEN_DESC ];
extern char  g_vpage     [LEN_DESC ];
extern char  g_vends     [LEN_DESC ];
extern char  g_vscroll   [LEN_DESC ];

extern char  g_hsimple   [LEN_DESC ];
extern char  g_hgoto     [LEN_DESC ];
extern char  g_hpage     [LEN_DESC ];
extern char  g_hends     [LEN_DESC ];
extern char  g_hscroll   [LEN_DESC ];

extern char  g_hword     [LEN_DESC ];

extern char  g_multimap  [LEN_DESC ];
extern char  g_multivisu [LEN_DESC ];
extern char  g_multiwdr  [LEN_DESC ];

extern char  g_multisrc  [LEN_DESC ];
extern char  g_multiselc [LEN_DESC ];

extern char  g_repeat    [LEN_DESC ];
extern char  g_search    [LEN_DESC ];

extern char  g_logkeys;
extern char  g_log       [LEN_FULL];
extern char  g_multi     [LEN_FULL];
extern char  g_mode      [LEN_FULL];
extern char  g_errs      [LEN_FULL];
extern int   g_all;
extern int   g_total;
extern int   g_curr;
extern char  g_last      [LEN_LABEL];
extern int   g_acks;
extern int   g_spaces;
extern int   g_noops;



/*---(repeating)------------*/
extern int   g_requested;
extern int   g_repeats;
extern char  g_repeating;
/*---(groups)---------------*/
extern int   g_level;
extern int   g_rep     [LEN_LABEL];
extern uchar g_src     [LEN_LABEL];
extern int   g_pos     [LEN_LABEL];



/*===[[ yMACRO_base.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(input)----------------*/
uchar       ykeys__input_fix        (char a_env, uchar a_key);
uchar       ykeys__input            (uchar a_key);
/*---(unittest)-------------*/
char        ykeys__unit_quiet       (void);
char        ykeys__unit_loud        (void);
char        ykeys__unit_end         (void);
char*       yKEYS__unit             (char *a_question, char a_index);


/*===[[ yMACRO_logger.c ]]====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ykeys_logger_init       (void);
/*---(history)--------------*/
char        ykeys__roll             (void);
char        ykeys__multi            (int a_pos);
char        yKEYS_logger            (uchar a_key);
/*---(undo)-----------------*/
char        yKEYS_unique            (void);
/*---(status)---------------*/
int         yKEYS_count             (void);
int         yKEYS_position          (void);
uchar       yKEYS_current           (void);
char        yKEYS_oldkeys           (void);
/*---(action)---------------*/
char        yKEYS_repos             (int a_pos);
char        yKEYS_toend             (void);
char        yKEYS_error             (void);
/*---(done)-----------------*/



/*===[[ yMACRO_repeat.c ]]====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ykeys_repeat_init       (void);
/*---(status)---------------*/
char        yKEYS_normal            (void);
char        yKEYS_repeating         (void);
int         yKEYS_repeats           (void);
int         yKEYS_repeat_orig       (void);
/*---(action)---------------*/
char        yKEYS_repeat_dec        (void);
int         yKEYS_repeat_useall     (void);
char        yKEYS_repeat_reset      (void);
char        ykeys_repeat_set        (int a_repeat);
/*---(mode)-----------------*/
char        yKEYS_repeat_umode      (uchar a_major, uchar a_minor);
/*---(done)-----------------*/


/*===[[ yMACRO_rptg.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yKEYS_status            (char *a_msg);




#endif

