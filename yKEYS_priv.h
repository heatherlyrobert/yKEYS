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
#define     P_PRONOUNCE ""
#define     P_HERITAGE  ""
#define     P_SHORTER   "god of letters and writing"
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yMODE"
#define     P_FULLPATH  "/usr/local/lib64/libyMODE"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.1-, complete and tie yVIKEYS back into it"
#define     P_VERNUM    "2.1a"
#define     P_VERTXT    "grouping and all unit testing caught up, clean"

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



typedef    struct    cMY    tMY;
struct cMY {
   /*---(global flags)---------*/
   char        done;                        /* flag indicating ready to quit  */
   char        redraw;                      /* force redraw based on changes  */
   char        repeating;                   /* note for repeating actions     */
   char        log_keys;                    /* allows keys to be hidden       */
   /*---(history every)--------*/
   char        h_every     [LEN_HUGE];      /* every key  (hidden or not)     */
   char        h_emode     [LEN_HUGE];      /* every mode (hidden or not)     */
   short       h_grand;                     /* total of every key             */
   /*---(history normal)-------*/
   char        h_logkeys;                   /* log current keys (y/-)         */
   uchar       h_mode      [LEN_FULL];      /* mode when key logged           */
   uchar       h_log       [LEN_FULL];      /* key logged                     */
   uchar       h_multi     [LEN_FULL];      /* prefix for multi key           */
   uchar       h_errs      [LEN_FULL];      /* key handling error/warns       */
   char        h_locked;                    /* key handling locked due to err */
   /*---(history positions)----*/
   short       h_all;                       /* all keys counted, from init    */
   short       h_total;                     /* end of key log position        */
   short       h_curr;                      /* current key position           */
   char        h_used;                      /* is last logged handled already */
   char        h_last      [LEN_LABEL];     /* last keys for display          */
   /*---(history counts)-------*/
   short       h_acks;                      /* count of display acks          */
   short       h_spaces;                    /* count of spaces/no action      */
   short       h_noops;                     /* count of no-op keys            */
   short       h_combos;                    /* count of combo (p multi)       */
   /*---(history errors)-------*/
   short       h_errors;                    /* count of key errors            */
   short       h_warnings;                  /* count of key warnings          */
   short       h_skips;                     /* count of keys skipped (locked) */
   /*---(history grouping)-----*/
   short       h_open;                      /* count of open parens           */
   short       h_close;                     /* count of close parens          */
   char        h_balanced;                  /* parens are balanced (y/-)      */
   /*---(loop speed)-----------*/
   float       l_delay;                     /* requested loop sleep timing    */
   float       l_update;                    /* requested screen update timing */
   int         l_skip;                      /* diff between playback and exec */
   /*---(loop tracking)--------*/
   int         l_secs;                      /* loop sleep second part         */
   long        l_nsec;                      /* loop sleep nanosec part        */
   int         l_loops;                     /* loops before screen update     */
   char        l_blocking;                  /* keyboard input blocks          */
   /*---(repeat main)----------*/
   int         r_asked;                     /* originally requested repeats   */
   int         r_count;                     /* remaining repeats              */
   char        r_repeating;                 /* repeat status (y/-)            */
   /*---(repeat groups)--------*/
   char        r_level;                     /* repeat/grouping level          */
   short       r_reps    [LEN_LABEL];       /* repeats by group level         */
   uchar       r_macro   [LEN_LABEL];       /* macro abbr for level           */
   short       r_beg     [LEN_LABEL];       /* current position               */
   short       r_end     [LEN_LABEL];       /* current position               */
   /*---(done)-----------------*/
};
extern tMY         myKEYS;




/*===[[ yMACRO_base.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(input)----------------*/
uchar       ykeys__input_fix        (char a_env, uchar a_key);
char        ykeys__input            (char a_env, uchar *a_key, uchar *a_str, int *n);
char        ykeys__input_force      (char a_env, uchar *a_key, uchar *a_str, int *n);
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
char        ykeys_logger_force      (uchar a_key);
char        ykeys_logstr            (char a_mode, uchar *a_keys);
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
/*---(errors)---------------*/
char        yKEYS_set_warning       (void);
char        yKEYS_set_error         (void);
char        yKEYS_set_lock          (void);
char        yKEYS_set_skip          (void);
char        yKEYS_is_error          (void);
char        yKEYS_is_locked         (void);
char        yKEYS_lock              (void);
char        yKEYS_unlock            (void);
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
char        yKEYS_keylog_status     (char a_size, short a_wide, char *a_list);


char        ykeys_group_reset       (void);
char        ykeys_group_check_end   (void);


#endif

