/*============================----beg-of-source---============================*/
#ifndef yKEYS_priv
#define yKEYS_priv yes


/*===[[ HEADER BEG ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_NAME      "yKEYS"
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "keyboard input and tracking"
#define     P_PURPOSE   "gather, clean, and track all keyboard input for yvikeys"
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "hermes-tresmegistus (thrice greatest)"
#define     P_PRONOUNCE ""
#define     P_HERITAGE  ""
#define     P_BRIEFLY   "god of letters and writing"
#define     P_IMAGERY   ""
#define     P_REASON    ""
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/yKEYS.vi_keys_tracking"
#define     P_BASENAME  "yKEYS"
#define     P_FULLNAME  "/usr/local/lib64/libyKEYS"
#define     P_SUFFIX    "···"
#define     P_CONTENT   "···"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 11.3.0"
#define     P_CODESIZE  "moderate    ()"
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,stdlib,string,math,time"
#define     P_DEPGRAPH  "···"
#define     P_DEPCORE   "yURG,yLOG,ySTR"
#define     P_DEPVIKEYS "yVIHUB,yMODE"
#define     P_DEPOTHER  "···"
#define     P_DEPSOLO   "···"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2016-11"
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.3-, moved into SSH githud and nearly done"
#define     P_VERNUM    "2.3i"
#define     P_VERTXT    "handling control keys for page up, down, left, and right"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*===[[ HEADER END ]]=========================================================*/



/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <math.h>              /* clibc  standard math library             */
#include    <time.h>              /* clibc  time related functions            */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom yvikeys)--------------------*/
#include    <yVIHUB.h>            /* heatherly yVIKEYS integration            */
#include    <yMODE.h>             /* heatherly yVIKEYS mode tracking          */
/*---(done)------------------------------*/


typedef     struct timespec   tTSPEC;

typedef    struct    cMY    tMY;
struct cMY {
   /*---(global flags)---------*/
   long        loops;                       /* number of loops in main        */
   char        done;                        /* flag indicating ready to quit  */
   char        redraw;                      /* force redraw based on changes  */
   char        log_keys;                    /* allows keys to be hidden       */
   /*---(arguments)------------*/
   char        a_script    [LEN_RECD];      /* cli script name request        */
   char        a_layout    [LEN_LABEL];     /* cli screen layout request      */
   char        a_status    [LEN_LABEL];     /* cli screen status request      */
   /*---(config)---------------*/
   char        c_env;
   char      (*c_draw)     (float);
   char      (*c_input)    (char, char*);
   char      (*c_altinput) (void);
   int         c_max_loop;
   /*---(history every)--------*/
   char        e_log       [LEN_HUGE];      /* every key  (hidden or not)     */
   char        e_mode      [LEN_HUGE];      /* every mode (hidden or not)     */
   char        e_multi     [LEN_HUGE];      /* every mode (hidden or not)     */
   char        e_error     [LEN_HUGE];      /* every mode (hidden or not)     */
   char        e_status    [LEN_HUGE];      /* note normal vs hidden          */
   short       e_all;                       /* all keys counted, from init    */
   short       e_total;                     /* entries in arrays              */
   /*---(history normal)-------*/
   char        h_logkeys;                   /* log current keys (y/-)         */
   uchar       h_mode      [LEN_FULL];      /* mode when key logged           */
   uchar       h_log       [LEN_FULL];      /* key logged                     */
   uchar       h_multi     [LEN_FULL];      /* prefix for multi key           */
   uchar       h_error     [LEN_FULL];      /* key handling error/warns       */
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
   /*---(replay keys)----------*/
   char        r_capture;                   /* capturing a replay (y/-)       */
   char        r_reinput   [LEN_RECD];      /* catpured replay keys           */
   char        r_replay;                    /* currently replaying (y/-)      */
   /*---(delay)----------------*/
   char        l_ndelay;                    /* number of delay options        */
   char        l_cdelay;                    /* current delay index            */
   char        l_sdelay   [LEN_LABEL];      /* current delay terse            */
   float       l_delay;                     /* requested loop sleep timing    */
   int         l_skip;                      /* diff between playback and exec */
   float       l_bdelay;                    /* pre-blitz delay between loops  */
   char        l_bskip;                     /* pre-blitz delay skips          */
   /*---(update)---------------*/
   char        l_nupdate;                   /* number of update options       */
   char        l_cupdate;                   /* current update option          */
   char        l_supdate  [LEN_LABEL];      /* current update terse           */
   float       l_update;                    /* requested screen update timing */
   float       l_bupdate;                   /* pre-blitz updates per second   */
   /*---(loop tracking)--------*/
   int         l_secs;                      /* loop sleep second part         */
   long        l_nsec;                      /* loop sleep nanosec part        */
   int         l_loops;                     /* loops before screen update     */
   char        l_blocking;                  /* keyboard input blocks          */
   /*---(loop timing)----------*/
   long long   l_exp;                       /* expected loop duration         */
   long long   l_act;                       /* actual loop duration           */
   long long   l_slept;                     /* actual dur of last sleep       */
   long long   l_used;                      /* actual dur of processing       */
   long long   l_sleep;                     /* expected dur of next sleep     */
   long long   l_beg;                       /* nsec of current start          */
   long long   l_graf;                      /* nsec of graphics/drawing start */
   long long   l_end;                       /* nsec of current end            */
   long long   l_prev;                      /* nsec of previous end           */
   long long   l_avg_all;                   /* average processing time        */
   long long   l_avg_miss;                  /* total variance of exp to act   */
   /*---(loop stats)-----------*/
   long        l_draw;                      /* count of drawing loops         */
   long long   l_avg_draw;                  /* average drawing time           */
   long        l_keys;                      /* count of key handling loops    */
   long long   l_avg_keys;                  /* average key processing time    */
   long        l_idle;                      /* count of idle/noop loops       */
   /*---(repeat main)----------*/
   int         r_asked;                     /* originally requested repeats   */
   int         r_count;                     /* remaining repeats              */
   char        r_repeating;                 /* repeat status (y/-)            */
   /*---(repeat groups)--------*/
   char        r_level;                     /* repeat/grouping level          */
   short       r_reps      [LEN_LABEL];     /* repeats by group level         */
   uchar       r_macro     [LEN_LABEL];     /* macro abbr for level           */
   short       r_beg       [LEN_LABEL];     /* current position               */
   short       r_end       [LEN_LABEL];     /* current position               */
   /*---(progress)--------*/
   char        p_unit      [LEN_TERSE];
   char        p_play;                      /* is progress playing            */
   int         p_scale;                     /* progress bar scale             */
   int         p_speed;                     /* progress bar speed             */
   float       p_adv;                       /* progress play advancing        */
   float       p_inc;                       /* progress horizontal moves      */
   char        p_anchor;                    /* position of current bar (shcle)*/
   float       p_cur;                       /* current timeline seconds       */
   float       p_beg;                       /* beg second for timeline play   */
   float       p_end;                       /* end second for timeline play   */
   float       p_len;                       /* length of script               */
   char        p_repeat;                    /* progress is loop/continuous    */
   int         p_line;                      /* current progress window line   */
   int         p_lines;                     /* progress window lines avail    */
   char        p_debug; 
   char        p_redraw;                    /* force redraw based on changes  */
   /*---(done)-----------------*/
};
extern tMY         myKEYS;

#define     MAX_DELAY   15
typedef  struct cDELAY tDELAY;
struct cDELAY {
   char        terse       [LEN_LABEL];
   char        desc        [LEN_LABEL];
   float       delay;
};
extern const tDELAY g_delays [MAX_DELAY];

#define     MAX_UPDATE  15
typedef  struct cUPDATE tUPDATE;
struct cUPDATE {
   char        terse       [LEN_LABEL];
   char        desc        [LEN_LABEL];
   float       update;
};
extern const tUPDATE g_updates [MAX_UPDATE];

#define     MAX_SCALE   100
typedef   struct cSCALE  tSCALE;
struct cSCALE {
   char        type;
   char        terse       [LEN_TERSE];
   char        label       [LEN_LABEL];
   char        desc        [LEN_FULL  ];
   char        power;
   float       unit;
};
extern const tSCALE g_scale_info [MAX_SCALE];

#define     MAX_SPEED   50
typedef   struct cSPEED  tSPEED;
struct cSPEED {
   char        terse       [LEN_TERSE];
   char        desc        [LEN_FULL  ];
   float       speed;   
};
extern const tSPEED g_speed_info [MAX_SPEED];


/*===[[ yKEYS_base.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(input)----------------*/
uchar       ykeys__input_fix        (char a_env, uchar a_key);
char        ykeys__input            (char a_env, uchar *a_key, uchar *a_str, int *n);
char        ykeys__input_force      (char a_env, uchar *a_key, uchar *a_str, int *n);
char        ykeys_quitting          (void);
char        ykeys__prepare          (char *a_delay, char *a_update, int a_loops, char a_env, void *a_draw, void *a_input, void *a_altinput);
/*---(unittest)-------------*/
char        ykeys__unit_quiet       (void);
char        ykeys__unit_loud        (void);
char        ykeys__unit_end         (void);
char        ykeys__unit_prep        (char *a_keys);
char        ykeys__unit_draw        (float a_zoom);
char        ykeys__unit_input       (char a_blocking, char *a_key);
char        ykeys__unit_altinput    (void);
char*       yKEYS__unit             (char *a_question, char a_index);


/*===[[ yKEYS_logger.c ]]=====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ykeys_logger_init       (void);
/*---(history)--------------*/
char        ykeys__roll             (void);
char        ykeys__multi            (int a_pos);
char        ykeys__every            (uchar a_mode, uchar a_key);
char        ykeys__normal           (uchar a_mode, uchar a_key);
char        ykeys__reinput          (uchar a_mode, uchar a_key);
char        yKEYS_logger            (uchar a_key);
char        ykeys_logger_force      (uchar a_key);
char        ykeys_logstr            (char a_mode, uchar *a_keys);
/*---(undo)-----------------*/
char        yKEYS_unique            (void);
/*---(status)---------------*/
int         yKEYS_count             (void);
int         yKEYS_position          (void);
uchar       yKEYS_ecurrent          (void);
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



/*===[[ yKEYS_repeat.c ]]=====================================================*/
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


/*===[[ yKEYS_rptg.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yKEYS_keylog_status     (char a_size, short a_wide, char *a_list);
char        ykeys_dump              (FILE *f);


char        ykeys_group_reset       (void);
char        ykeys_group_check_end   (void);



/*===[[ yKEYS_loop.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ykeys_loop_clear        (void);
char        ykeys_loop_init         (void);
char        ykeys__loop_calc        (void);
char        ykeys_loop_update       (char *a_update);
char        ykeys_loop_delay        (char *a_delay);
char        yKEYS_loop_normal       (void);
char        ykeys_loop_prog         (void);



/*===[[ yKEYS_scale.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ykeys_scale_init        (void);
char        ykeys_scale             (uchar a_mode, uchar *a_scale);
char        yKEYS_progress_scale    (uchar *a_scale, uchar *a_terse, uchar *a_label, uchar *a_desc, char *a_power, float *a_unit);

char        ykeys_speed_init        (void);
char        ykeys_progress_init     (void);
char        ykeys_progress_mode     (uchar a_major, uchar a_minor);



#endif

