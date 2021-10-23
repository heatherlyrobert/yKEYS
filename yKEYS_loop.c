/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



/*===[[ UPDATES ]]============================================================*/
#define     MAX_UPDATE  50
static int     s_update   =  0;    /* how many screen updates per second      */

typedef  struct cUPDATE tUPDATE;
struct cUPDATE {
   char        terse       [LEN_LABEL];
   char        desc        [LEN_LABEL];
   float       update;
};
static const tUPDATE s_update_info [] = {
   /*---(default)--------------------------*/
   { "every" , "every loop"         ,   0.00     },
   /*---(faster)---------------------------*/
   { "10ms"  , "very fast"          ,   0.01     },
   { "20ms"  , "faster"             ,   0.02     },
   { "50ms"  , "fast"               ,   0.05     },
   /*---(normal)---------------------------*/
   { "100ms" , "normal"             ,   0.10     },
   /*---(slower)---------------------------*/
   { "250ms" , "slow"               ,   0.25     },
   { "500ms" , "slower"             ,   0.50     },
   { "1s"    , "very slow"          ,   1.00     },
   /*---(macro debugging)------------------*/
   { "2s"    , "stop action"        ,   2.00     },
   { "5s"    , "occasional peeks"   ,   5.00     },
   { "100s"  , "flying blind"       , 100.00     },
   /*---(end)------------------------------*/
   { "---"   , "end-of-list"        ,   0.00     },
   /*---(done)-----------------------------*/
};



/*===[[ DELAYS ]]=============================================================*/
#define     NSEC        1000000000
#define     MAX_DELAY   50
static int     s_delay    =  0;    /* how many seconds between main loops     */

typedef  struct cDELAY tDELAY;
struct cDELAY {
   char        terse       [LEN_LABEL];
   char        desc        [LEN_LABEL];
   float       delay;
};
static const tDELAY s_delay_info [] = {
   /*---(default)---------------------------------*/
   { "keys"  , "keyboard"           ,   0.0      },
   /*---(faster)----------------------------------*/
   { "1us"   , "millionth"          ,   0.000001 },
   { "10us"  , "ten millionths"     ,   0.00001  },
   { "100us" , "hundred millionths" ,   0.0001   },
   { "500us" , "500 millionths"     ,   0.0005   },
   /*---(normal)----------------------------------*/
   { "1ms"   , "thousandth"         ,   0.001    },
   { "5ms"   , "five thousandths"   ,   0.005    },
   { "10ms"  , "hundreth (normal)"  ,   0.01     },
   /*---(slower)----------------------------------*/
   { "20ms"  , "fifteth"            ,   0.02     },
   { "50ms"  , "twenteth"           ,   0.05     },
   { "100ms" , "tenth"              ,   0.1      },
   /*---(glacial)---------------------------------*/
   { "1s"    , "second"             ,   1.0      },
   /*---(end of list)-----------------------------*/
   { "---"   , "end-of-list"        ,   0.0      },
   /*---(done)------------------------------------*/
};



/*====================------------------------------------====================*/
/*===----                       main loop timing                       ----===*/
/*====================------------------------------------====================*/
static void      o___LOOPING_________________o (void) {;}

char
yvikeys_loop_init       (void)
{
   /*---(delay/updapte)------------------*/
   /*> s_delay             = 0;                                                       <* 
    *> s_update            = 0;                                                       <* 
    *> myKEYS.l_delay        = 0.0;                                                   <* 
    *> myKEYS.l_update     = 0.0;                                                     <* 
    *> myKEYS.l_skip       = 0;                                                       <* 
    *> myKEYS.l_secs         = 0;                                                     <* 
    *> myKEYS.l_nsec         = 0;                                                     <* 
    *> myKEYS.l_loops        = 1;                                                     <* 
    *> myKEYS.l_blocking     = ' ';                                                   <* 
    *> yvikeys_loop_delay  ("");                                                      <* 
    *> yvikeys_loop_update ("");                                                      <*/
   /*---(complete)-----------------------*/
   return 0;
}

int
yvikeys_loop_getch      (void)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                            <* 
    *> char        x_ch        =    0;                                                     <* 
    *> XKeyEvent  *key_event;                                                              <* 
    *> int         the_bytes;                                                              <* 
    *> char        the_keys    [5];                                                        <* 
    *> /+---(opengl)-------------------------+/                                            <* 
    *> if (myKEYS.env == YVIKEYS_OPENGL) {                                                 <* 
    *>    if (myKEYS.l_blocking == 'y') {                                                  <* 
    *>       XNextEvent(YX_DISP, &YX_EVNT);                                                <* 
    *>    }                                                                                <* 
    *>    else {                                                                           <* 
    *>       if (XPending(YX_DISP))   XNextEvent(YX_DISP, &YX_EVNT);                       <* 
    *>       else                  return 0;                                               <* 
    *>    }                                                                                <* 
    *>    switch(YX_EVNT.type) {                                                           <* 
    *>    case KeyPress:                                                                   <* 
    *>       key_event  = (XKeyEvent *) &YX_EVNT;                                          <* 
    *>       the_bytes = XLookupString((XKeyEvent *) &YX_EVNT, the_keys, 5, NULL, NULL);   <* 
    *>       if (the_bytes < 1) break;                                                     <* 
    *>       /+---(handle)----------------+/                                               <* 
    *>       x_ch  = the_keys [0];                                                         <* 
    *>       break;                                                                        <* 
    *>    }                                                                                <* 
    *> }                                                                                   <* 
    *> /+---(ncurses)------------------------+/                                            <* 
    *> else if (myKEYS.env == YVIKEYS_CURSES) {                                            <* 
    *>    if (myKEYS.l_blocking == 'y')   nodelay  (stdscr, FALSE);                        <* 
    *>    else                            nodelay  (stdscr, TRUE );                        <* 
    *>    x_ch = getch ();                                                                 <* 
    *> }                                                                                   <* 
    *> /+---(complete)-----------------------+/                                            <* 
    *> return x_ch;                                                                        <*/
}

char
yvikeys_loop_update     (char *a_update)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rc          =    0;                                                <* 
    *> char        x_prefix    =  ' ';                                                <* 
    *> int         i           =    0;                                                <* 
    *> char        x_index     =   -1;                                                <* 
    *> char        x_max       =   -1;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_senter  (__FUNCTION__);                                      <* 
    *> /+---(assign prefix)------------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_snote   (a_update);                                          <* 
    *> if (a_update == NULL)   x_prefix = 0;                                          <* 
    *> else                    x_prefix = a_update [0];                               <* 
    *> DEBUG_LOOP   yLOG_sint    (x_prefix);                                          <* 
    *> /+---(determine max)------------------+/                                       <* 
    *> for (i = 0; i < MAX_UPDATE; ++i) {                                             <* 
    *>    if (strcmp (s_update_info [i].terse, "---"   ) == 0)  break;                <* 
    *>    ++x_max;                                                                    <* 
    *> }                                                                              <* 
    *> /+---(find entry in table)------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_sint    (s_update);                                          <* 
    *> switch (x_prefix) {                                                            <* 
    *> case  0  :                                                                     <* 
    *>    x_index = s_update;                                                         <* 
    *>    rc = -1;                                                                    <* 
    *>    break;                                                                      <* 
    *> case '0' :                                                                     <* 
    *>    x_index = 0;                                                                <* 
    *>    break;                                                                      <* 
    *> case '=' :                                                                     <* 
    *>    x_index = s_update;                                                         <* 
    *>    break;                                                                      <* 
    *> case '>' :                                                                     <* 
    *>    if (s_update <  x_max)  x_index = ++s_update;                               <* 
    *>    else {                                                                      <* 
    *>       x_index = x_max;                                                         <* 
    *>       rc = -3;                                                                 <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> case '<' :                                                                     <* 
    *>    if (s_update >  1    )  x_index = --s_update;                               <* 
    *>    else {                                                                      <* 
    *>       x_index = 1;                                                             <* 
    *>       rc = -4;                                                                 <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> default  :                                                                     <* 
    *>    for (i = 0; i <= x_max; ++i) {                                              <* 
    *>       if (strcmp (s_update_info [i].terse, a_update) != 0)  continue;          <* 
    *>       x_index = i;                                                             <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *>    if (x_index == -1) {                                                        <* 
    *>       x_index = s_update;                                                      <* 
    *>       rc = -2;                                                                 <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> }                                                                              <* 
    *> /+---(set key values)-----------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_sint    (x_index);                                           <* 
    *> s_update        = x_index;                                                     <* 
    *> myKEYS.l_update = s_update_info [x_index].update;                              <* 
    *> DEBUG_LOOP   yLOG_sdouble (myKEYS.l_update);                                   <* 
    *> DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);                                      <* 
    *> /+---(update looping)-----------------+/                                       <* 
    *> yvikeys__loop_calc   ();                                                       <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return rc;                                                                     <*/
}

char
yvikeys_loop_delay      (char *a_delay)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rc          =    0;                                                <* 
    *> char        x_prefix    =  ' ';                                                <* 
    *> int         i           =    0;                                                <* 
    *> char        x_index     =   -1;                                                <* 
    *> char        x_max       =   -1;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_senter  (__FUNCTION__);                                      <* 
    *> /+---(assign prefix)------------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_snote   (a_delay);                                           <* 
    *> if (a_delay  == NULL)   x_prefix = 0;                                          <* 
    *> else                    x_prefix = a_delay [0];                                <* 
    *> DEBUG_LOOP   yLOG_sint    (x_prefix);                                          <* 
    *> /+---(determine max)------------------+/                                       <* 
    *> for (i = 0; i < MAX_DELAY; ++i) {                                              <* 
    *>    if (strcmp (s_delay_info [i].terse, "---"  ) == 0)  break;                  <* 
    *>    ++x_max;                                                                    <* 
    *> }                                                                              <* 
    *> /+---(find entry in table)------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_sint    (s_delay);                                           <* 
    *> switch (x_prefix) {                                                            <* 
    *> case  0  :                                                                     <* 
    *>    x_index = s_delay;                                                          <* 
    *>    rc = -1;                                                                    <* 
    *>    break;                                                                      <* 
    *> case '0' :                                                                     <* 
    *>    x_index = 0;                                                                <* 
    *>    break;                                                                      <* 
    *> case '=' :                                                                     <* 
    *>    x_index = s_delay;                                                          <* 
    *>    break;                                                                      <* 
    *> case '>' :                                                                     <* 
    *>    if (s_delay  <  x_max)  x_index = ++s_delay;                                <* 
    *>    else {                                                                      <* 
    *>       x_index = x_max;                                                         <* 
    *>       rc = -3;                                                                 <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> case '<' :                                                                     <* 
    *>    if (s_delay  >  1    )  x_index = --s_delay;                                <* 
    *>    else {                                                                      <* 
    *>       x_index = 1;                                                             <* 
    *>       rc = -4;                                                                 <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> default  :                                                                     <* 
    *>    for (i = 0; i < x_max; ++i) {                                               <* 
    *>       if (strcmp (s_delay_info [i].terse, a_delay) != 0)  continue;            <* 
    *>       x_index = i;                                                             <* 
    *>       break;                                                                   <* 
    *>    }                                                                           <* 
    *>    if (x_index == -1) {                                                        <* 
    *>       x_index = s_delay;                                                       <* 
    *>       rc = -2;                                                                 <* 
    *>    }                                                                           <* 
    *>    break;                                                                      <* 
    *> }                                                                              <* 
    *> /+---(set key values)-----------------+/                                       <* 
    *> DEBUG_LOOP   yLOG_sint    (x_index);                                           <* 
    *> s_delay         = x_index;                                                     <* 
    *> myKEYS.l_delay  = s_delay_info [x_index].delay;                                <* 
    *> DEBUG_LOOP   yLOG_sdouble (myKEYS.l_delay);                                    <* 
    *> DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);                                      <* 
    *> /+---(update looping)-----------------+/                                       <* 
    *> yvikeys__loop_calc   ();                                                       <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return rc;                                                                     <*/
}

static float   s_blitz_delay   = 0.0;
static float   s_blitz_update  = 0.0;

char
yvikeys_loop_blitz      (void)
{
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   DEBUG_LOOP   yLOG_double  ("delay"     , myKEYS.l_delay);
   /*> if (myKEYS.l_delay <  0.00001) {                                               <* 
    *>    DEBUG_LOOP   yLOG_note    ("already in blitz, nothing to do");              <* 
    *>    DEBUG_LOOP   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <* 
    *> s_blitz_delay   = myKEYS.l_delay;                                              <* 
    *> myKEYS.l_delay  =   0.000001;                                                  <* 
    *> s_blitz_update  = myKEYS.l_update;                                             <* 
    *> myKEYS.l_update =   100.000000;                                                <* 
    *> yvikeys__loop_calc ();                                                         <*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvikeys_loop_unblitz    (void)
{
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   DEBUG_LOOP   yLOG_double  ("delay"     , myKEYS.l_delay);
   /*> if (myKEYS.l_delay >= 0.00001) {                                               <* 
    *>    DEBUG_LOOP   yLOG_note    ("not in blitz, nothing to do");                  <* 
    *>    DEBUG_LOOP   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <* 
    *> myKEYS.l_delay  = s_blitz_delay;                                               <* 
    *> myKEYS.l_update = s_blitz_update;                                              <* 
    *> yvikeys__loop_calc ();                                                         <*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

static char   s_save_delay   [LEN_LABEL] = "keys";
static char   s_save_update  [LEN_LABEL] = "every";

char
yvikeys_loop_set        (char *a_delay, char *a_update)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        rc          =    0;                                                <* 
    *> /+---(set values)---------------------+/                                       <* 
    *> rc = yvikeys_loop_delay   (a_delay);                                           <* 
    *> if (rc >= 0)  strlcpy (s_save_delay , a_delay , LEN_LABEL);                    <* 
    *> rc = yvikeys_loop_update  (a_update);                                          <* 
    *> if (rc >= 0)  strlcpy (s_save_update, a_update, LEN_LABEL);                    <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return rc;                                                                     <*/
}

char
yvikeys_loop_normal     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(return to normal)---------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   DEBUG_LOOP   yLOG_schar   (yMACRO_exe_mode ());
   DEBUG_LOOP   yLOG_snote   (s_save_delay);
   /*> rc = yvikeys_loop_delay   (s_save_delay);                                      <* 
    *> myKEYS.l_skip = 0;                                                             <* 
    *> DEBUG_LOOP   yLOG_sint    (myKEYS.l_skip);                                     <* 
    *> DEBUG_LOOP   yLOG_snote   (s_save_update);                                     <* 
    *> rc = yvikeys_loop_update  (s_save_update);                                     <*/
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yvikeys_loop_macro      (char a_delay, char a_update)
{
   /*---(no change for playback)---------*/
   /*> IF_MACRO_PLAYBACK {                                                                      <* 
    *>    yvikeys_loop_normal ();                                                               <* 
    *>    return 0;                                                                             <* 
    *> }                                                                                        <* 
    *> /+---(change to macro speed)----------+/                                                 <* 
    *> DEBUG_LOOP   yLOG_senter  (__FUNCTION__);                                                <* 
    *> DEBUG_LOOP   yLOG_schar   (yMACRO_exe_mode ());                                          <* 
    *> DEBUG_LOOP   yLOG_sint    (a_delay);                                                     <* 
    *> DEBUG_LOOP   yLOG_schar   (a_delay);                                                     <* 
    *> /+---(run mode)-----------------------+/                                                 <* 
    *> /+> IF_MACRO_RUN   a_delay = '0';                                                  <+/   <* 
    *> /+---(delay mode)---------------------+/                                                 <* 
    *> switch (a_delay) {                                                                       <* 
    *> case MACRO_BLITZ  :  yvikeys_loop_delay ("1us"  );   myKEYS.l_skip =  0;   break;        <* 
    *> case MACRO_FAST   :  yvikeys_loop_delay ("100us");   myKEYS.l_skip =  0;   break;        <* 
    *> case MACRO_THOU   :  yvikeys_loop_delay ("1ms"  );   myKEYS.l_skip =  0;   break;        <* 
    *> case MACRO_HUND   :  yvikeys_loop_delay ("10ms" );   myKEYS.l_skip =  0;   break;        <* 
    *> case MACRO_TWENTY :  yvikeys_loop_delay ("10ms" );   myKEYS.l_skip =  4;   break;        <* 
    *> case MACRO_TENTH  :  yvikeys_loop_delay ("100ms");   myKEYS.l_skip =  0;   break;        <* 
    *> case MACRO_HALF   :  yvikeys_loop_delay ("100ms");   myKEYS.l_skip =  4;   break;        <* 
    *> case MACRO_SEC    :  yvikeys_loop_delay ("100ms");   myKEYS.l_skip =  9;   break;        <* 
    *> case MACRO_DOUBLE :  yvikeys_loop_delay ("100ms");   myKEYS.l_skip = 19;   break;        <* 
    *> case MACRO_TRIPLE :  yvikeys_loop_delay ("100ms");   myKEYS.l_skip = 29;   break;        <* 
    *> }                                                                                        <* 
    *> DEBUG_LOOP   yLOG_sint    (myKEYS.l_skip);                                               <* 
    *> /+---(change update basis)------------+/                                                 <* 
    *> DEBUG_LOOP   yLOG_sint    (a_update);                                                    <* 
    *> DEBUG_LOOP   yLOG_schar   (a_update);                                                    <* 
    *> switch (a_update) {                                                                      <* 
    *> case MACRO_NORMAL :  yvikeys_loop_update ("100ms");  break;                              <* 
    *> case MACRO_SLOWER :  yvikeys_loop_update ("500ms");  break;                              <* 
    *> case MACRO_BLINKS :  yvikeys_loop_update ("2s");     break;                              <* 
    *> case MACRO_PEEKS  :  yvikeys_loop_update ("5s");     break;                              <* 
    *> case MACRO_BLIND  :  yvikeys_loop_update ("100s");   break;                              <* 
    *> }                                                                                        <* 
    *> /+---(complete)-----------------------+/                                                 <* 
    *> DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);                                                <* 
    *> return 0;                                                                                <*/
}

static long long s_loop_targ   = 0;
static long long s_loop_used   = 0;
static long long s_loop_rem    = 0;

static long long s_loop_slept  = 0;
static long long s_loop_miss   = 0;

static long long s_loop_prev   = 0;
static long long s_loop_beg    = 0;
static long long s_loop_end    = 0;
static long long s_loop_dur    = 0;


static long long x_used   = 0;
static float     x_pct    = 0.0;

static long      s_avg    = 0.0;
static long      s_draw   = 0.0;
static long      s_keys   = 0.0;
static long      s_idle   = 0.0;

char
yvikeys_loop_beg        (void)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> tTSPEC      x_dur;                                                             <* 
    *> /+---(get beginning time)-------------+/                                       <* 
    *> clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);                                  <* 
    *> s_loop_beg   = x_dur.tv_sec * NSEC;                                            <* 
    *> s_loop_beg  += x_dur.tv_nsec;                                                  <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return 0;                                                                      <*/
}

char
yvikeys_loop_prog       (void)
{
   /*> if (myKEYS.p_play == 'y') {                                                    <* 
    *>    myKEYS.p_cur += myKEYS.p_adv;                                               <* 
    *> }                                                                              <* 
    *> if (myKEYS.p_cur <  myKEYS.p_beg) {                                            <* 
    *>    if (myKEYS.p_repeat == 'y' && myKEYS.p_play == 'y') {                       <* 
    *>       myKEYS.p_cur  = myKEYS.p_end;                                            <* 
    *>       myKEYS.p_play = 'y';                                                     <* 
    *>    } else {                                                                    <* 
    *>       myKEYS.p_cur  = myKEYS.p_beg;                                            <* 
    *>       myKEYS.p_play = '-';                                                     <* 
    *>    }                                                                           <* 
    *> }                                                                              <* 
    *> if (myKEYS.p_cur >  myKEYS.p_end) {                                            <* 
    *>    if (myKEYS.p_repeat == 'y' && myKEYS.p_play == 'y') {                       <* 
    *>       myKEYS.p_cur  = myKEYS.p_beg;                                            <* 
    *>       myKEYS.p_play = 'y';                                                     <* 
    *>    } else {                                                                    <* 
    *>       myKEYS.p_cur  = myKEYS.p_end;                                            <* 
    *>       myKEYS.p_play = '-';                                                     <* 
    *>    }                                                                           <* 
    *> }                                                                              <* 
    *> return 0;                                                                      <*/
}

char
yvikeys_loop_sleep      (uchar a_key, char a_draw)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                                                                                                                                 <* 
    *> static long x_secs      =    0;                                                                                                                                                                          <* 
    *> static long x_nsec      =    0;                                                                                                                                                                          <* 
    *> tTSPEC      x_dur;                                                                                                                                                                                       <* 
    *> static int  x_loops     =    0;                                                                                                                                                                          <* 
    *> static int  x_draws     =    0;                                                                                                                                                                          <* 
    *> static int  x_keys      =    0;                                                                                                                                                                          <* 
    *> static int  x_idles     =    0;                                                                                                                                                                          <* 
    *> static long long x_total =    0;                                                                                                                                                                         <* 
    *> static long long x_draw  =    0;                                                                                                                                                                         <* 
    *> static long long x_key   =    0;                                                                                                                                                                         <* 
    *> static long long x_idle  =    0;                                                                                                                                                                         <* 
    *> char        x_type       =  '-';                                                                                                                                                                         <* 
    *> /+---(header)-------------------------+/                                                                                                                                                                 <* 
    *> DEBUG_LOOP   yLOG_enter   (__FUNCTION__);                                                                                                                                                                <* 
    *> /+---(get ending time)----------------+/                                                                                                                                                                 <* 
    *> DEBUG_LOOP   yLOG_complex ("args"      , "%3d, %c, %c, %c blocking", a_key, chrvisible (a_key), a_draw, myKEYS.l_blocking);                                                                              <* 
    *> clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);                                                                                                                                                            <* 
    *> s_loop_end   = x_dur.tv_sec * NSEC;                                                                                                                                                                      <* 
    *> s_loop_end  += x_dur.tv_nsec;                                                                                                                                                                            <* 
    *> /+---(classify)-----------------------+/                                                                                                                                                                 <* 
    *> if      (a_draw == 'y')  x_type = 'g';                                                                                                                                                                   <* 
    *> else if (a_key  !=  0 )  x_type = 'k';                                                                                                                                                                   <* 
    *> else                     x_type = '-';                                                                                                                                                                   <* 
    *> /+---(calc sleep diffs)---------------+/                                                                                                                                                                 <* 
    *> /+> s_loop_slept = s_loop_beg - s_loop_prev;                                       <+/                                                                                                                   <* 
    *> /+> s_loop_miss  = s_loop_beg - s_loop_prev;                                       <+/                                                                                                                   <* 
    *> /+---(calc run diffs)-----------------+/                                                                                                                                                                 <* 
    *> s_loop_targ  = (myKEYS.l_secs * NSEC) + myKEYS.l_nsec;                                                                                                                                                   <* 
    *> s_loop_used  = s_loop_end  - s_loop_beg;                                                                                                                                                                 <* 
    *> s_loop_rem   = s_loop_targ - s_loop_used;                                                                                                                                                                <* 
    *> if (myKEYS.l_blocking == 'y')  s_loop_rem = 0;                                                                                                                                                           <* 
    *> /+> s_loop_prev  = s_loop_end;                                                     <+/                                                                                                                   <* 
    *> /+---(for timer)----------------------+/                                                                                                                                                                 <* 
    *> x_pct    = (s_loop_used / (float) s_loop_targ) * 100.0;                                                                                                                                                  <* 
    *> DEBUG_LOOP   yLOG_complex ("timing"    , "%10ds, %10dn, %10db, %10dt, %10de, %10du, %10dr, %8.6f", myKEYS.l_secs, myKEYS.l_nsec, s_loop_beg, s_loop_targ, s_loop_end, s_loop_used, s_loop_rem, x_pct);   <* 
    *> /+---(statistics)---------------------+/                                                                                                                                                                 <* 
    *> ++x_loops;                                                                                                                                                                                               <* 
    *> x_total += s_loop_used;                                                                                                                                                                                  <* 
    *> s_avg    = x_total / (float) x_loops;                                                                                                                                                                    <* 
    *> switch (x_type) {                                                                                                                                                                                        <* 
    *> case 'g' :                                                                                                                                                                                               <* 
    *>    ++x_draws;                                                                                                                                                                                            <* 
    *>    x_draw += s_loop_used;                                                                                                                                                                                <* 
    *>    s_draw  = x_draw / (float) x_draws;                                                                                                                                                                   <* 
    *>    break;                                                                                                                                                                                                <* 
    *> case 'k' :                                                                                                                                                                                               <* 
    *>    ++x_keys;                                                                                                                                                                                             <* 
    *>    x_key  += s_loop_used;                                                                                                                                                                                <* 
    *>    s_keys  = x_key  / (float) x_keys;                                                                                                                                                                    <* 
    *>    break;                                                                                                                                                                                                <* 
    *> default  :                                                                                                                                                                                               <* 
    *>    ++x_idles;                                                                                                                                                                                            <* 
    *>    x_idle += s_loop_used;                                                                                                                                                                                <* 
    *>    s_idle  = x_idle / (float) x_idles;                                                                                                                                                                   <* 
    *>    break;                                                                                                                                                                                                <* 
    *> }                                                                                                                                                                                                        <* 
    *> /+> s_avg     = x_total / x_loops;                                                 <+/                                                                                                                   <* 
    *> DEBUG_LOOP   yLOG_complex ("counts"    , "%c, %6dd, %6dk, %6di", x_type, x_draws, x_keys, x_idles);                                                                                                      <* 
    *> /+---(sleeping)-----------------------+/                                                                                                                                                                 <* 
    *> if (myKEYS.l_blocking != 'y') {                                                                                                                                                                          <* 
    *>    x_dur.tv_sec  = s_loop_rem / NSEC;                                                                                                                                                                    <* 
    *>    x_dur.tv_nsec = s_loop_rem % NSEC;                                                                                                                                                                    <* 
    *>    DEBUG_LOOP   yLOG_note    ("nano-sleeping");                                                                                                                                                          <* 
    *>    nanosleep      (&x_dur, NULL);                                                                                                                                                                        <* 
    *> }                                                                                                                                                                                                        <* 
    *> /+---(complete)-----------------------+/                                                                                                                                                                 <* 
    *> DEBUG_LOOP   yLOG_exit    (__FUNCTION__);                                                                                                                                                                <* 
    *> return 0;                                                                                                                                                                                                <*/
}

char       /*----: give current looping info ---------------------------------*/
yvikeys_prog_status     (char *a_list)
{
   /*> /+---(locals)-----------+-----------+-+/                                                            <* 
    *> char        rce         = -10;                                                                      <* 
    *> /+---(defenses)-----------------------+/                                                            <* 
    *> --rce;  if (a_list  == NULL)  return rce;                                                           <* 
    *> /+---(write status)-------------------+/                                                            <* 
    *> sprintf (a_list, "progress, play=%c, %8.6fa, %8.6fi", myKEYS.p_play, myKEYS.p_adv, myKEYS.p_inc);   <* 
    *> /+---(complete)-----------------------+/                                                            <* 
    *> return 0;                                                                                           <*/
}

char       /*----: give current looping info ---------------------------------*/
yvikeys_delay_status    (char *a_list)
{
   /*> /+---(locals)-----------+-----------+-+/                                                                     <* 
    *> char        rce         = -10;                                                                               <* 
    *> /+---(defenses)-----------------------+/                                                                     <* 
    *> --rce;  if (a_list  == NULL)  return rce;                                                                    <* 
    *> /+---(write status)-------------------+/                                                                     <* 
    *> sprintf (a_list, "delay, %-5s = %8.6f, %1ds, %10dns, update %-5s = %5.3fs, %4d loop(s), %c",                 <* 
    *>       s_delay_info [s_delay].terse, s_delay_info [s_delay].delay, myKEYS.l_secs, myKEYS.l_nsec,              <* 
    *>       s_update_info [s_update].terse, s_update_info [s_update].update, myKEYS.l_loops, myKEYS.l_blocking);   <* 
    *> /+---(complete)-----------------------+/                                                                     <* 
    *> return 0;                                                                                                    <*/
}

char       /*----: give current looping info ---------------------------------*/
yvikeys_main_status     (char *a_list)
{
   /*> /+---(locals)-----------+-----------+-+/                                       <* 
    *> char        rce         = -10;                                                 <* 
    *> /+---(defenses)-----------------------+/                                       <* 
    *> --rce;  if (a_list  == NULL)  return rce;                                      <* 
    *> /+---(write status)-------------------+/                                       <* 
    *> sprintf (a_list, "main, %8lldt, %8lldr, %8lldu, %6ldt, %6ldd, %6ldk, %6ldi",   <* 
    *>       s_loop_targ, s_loop_rem, s_loop_used, s_avg, s_draw, s_keys, s_idle);    <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return 0;                                                                      <*/
}
