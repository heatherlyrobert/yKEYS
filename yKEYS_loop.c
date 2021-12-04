/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



#define     NSEC        1000000000


static float     s_pct    = 0.0;

static long long s_total_time =    0;
static long long s_draw_time  =    0;
static long long s_keys_time  =    0;
static long long s_miss_time  =    0;




/*===[[ UPDATES ]]============================================================*/
const tUPDATE g_updates [MAX_UPDATE] = {
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
char    g_nupdate  =   0;          /* number of update options                */
char    g_cupdate  =   0;          /* current update option                   */
char    g_supdate  [LEN_LABEL] = "every";
float   g_bupdate  = 0.0;          /* pre-blitz updates per second            */


/*===[[ DELAYS ]]=============================================================*/


const tDELAY g_delays [MAX_DELAY] = {
   /*---(default)---------------------------------*/
   { "keys"  , "keyboard"           ,   0.00     },
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
   { "100ms" , "tenth"              ,   0.10     },
   /*---(glacial)---------------------------------*/
   { "1s"    , "second"             ,   1.00     },
   /*---(end of list)-----------------------------*/
   { "---"   , "end-of-list"        ,   0.00     },
   /*---(done)------------------------------------*/
};
char    g_ndelay   =  0;           /* number of delay options                 */
char    g_cdelay   =  0;           /* current delay option                    */
char    g_sdelay   [LEN_LABEL] = "keys";
float   g_bdelay   = 0.0;          /* pre-blitz delay seconds between loops   */
char    g_bskip    =   0;          /* pre-blitz delay skips                   */



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
ykeys_loop_clear        (void)
{
   /*---(overall)------------------------*/
   myKEYS.loops       = 0;
   myKEYS.done        = '-';
   /*---(timing)-------------------------*/
   myKEYS.l_exp       = 0;
   myKEYS.l_act       = 0;
   myKEYS.l_slept     = 0;
   myKEYS.l_used      = 0;
   myKEYS.l_sleep     = 0;
   myKEYS.l_beg       = 0;
   myKEYS.l_end       = 0;
   myKEYS.l_prev      = 0;
   myKEYS.l_avg_all   = 0;
   myKEYS.l_avg_miss  = 0;
   /*---(stats)--------------------------*/
   myKEYS.l_draw      = 0;
   myKEYS.l_avg_draw  = 0;
   myKEYS.l_keys      = 0;
   myKEYS.l_avg_keys  = 0;
   myKEYS.l_idle      = 0;
   /*---(totals)-------------------------*/
   s_total_time       = 0.0;
   s_draw_time        = 0.0;
   s_keys_time        = 0.0;
   s_miss_time        = 0.0;
   /*---(complete)-----------------------*/
   return 0;
}

char
ykeys_loop_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(delay/updapte)------------------*/
   myKEYS.l_delay     = 0.0;
   myKEYS.l_update    = 0.0;
   myKEYS.l_skip      = 0;
   myKEYS.l_secs      = 0;
   myKEYS.l_nsec      = 0;
   myKEYS.l_loops     = 1;
   myKEYS.l_blocking  = '-';
   /*---(clear other)--------------------*/
   ykeys_loop_clear ();
   /*---(count updates)------------------*/
   g_cupdate = 4;
   g_nupdate = 0;
   for (i = 0; i < MAX_UPDATE; ++i) {
      if (strcmp (g_updates [i].terse, "---"   ) == 0)  break;
      ++g_nupdate;
   }
   /*---(count delays)-------------------*/
   g_cdelay  = 7;
   g_ndelay  = 0;
   for (i = 0; i < MAX_DELAY;  ++i) {
      if (strcmp (g_delays  [i].terse, "---"   ) == 0)  break;
      ++g_ndelay;
   }
   /*---(initial setting)----------------*/
   yKEYS_loop_set ("10ms" , "100ms");
   /*---(saves)--------------------------*/
   /*> strcpy (g_sdelay , "keys" );                                                   <*/
   /*> strcpy (g_supdate, "every");                                                   <*/
   /*---(blitzing)-----------------------*/
   g_bdelay  = 0.0;
   g_bskip   =   0;
   g_bupdate = 0.0;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     shared functions                         ----===*/
/*====================------------------------------------====================*/
static void      o___SHARED__________________o (void) {;}

char
ykeys__loop_calc        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   float       x_base      =  0.0;
   /*---(initialize)---------------------*/
   myKEYS.l_secs  = 0;
   myKEYS.l_nsec  = 0;
   myKEYS.l_loops = 1;
   /*---(keyboard only)------------------*/
   if      (myKEYS.l_delay  == 0.0 && myKEYS.l_update == 0.0) {
      x_base = myKEYS.l_delay;
   }
   /*---(delay, no update)---------------*/
   else if (myKEYS.l_delay  >  0.0 && myKEYS.l_update == 0.0) {
      x_base = myKEYS.l_delay;
   }
   /*---(update, no delay)---------------*/
   else if (myKEYS.l_update  > 0.0 && myKEYS.l_delay  == 0.0) {
      x_base = myKEYS.l_update;
   }
   /*---(fast enough)--------------------*/
   else if (myKEYS.l_delay <= myKEYS.l_update) {
      x_base = myKEYS.l_delay;
   }
   /*---(too slow)-----------------------*/
   else {
      x_base = myKEYS.l_update;
   }
   /*---(update timing)------------------*/
   if (x_base >= 1.0)  myKEYS.l_secs  = trunc (x_base);
   myKEYS.l_nsec  = (x_base - myKEYS.l_secs) * NSEC;
   /*---(update loops)-------------------*/
   if (myKEYS.l_update != 0.0 && myKEYS.l_delay != 0.0)  {
      myKEYS.l_loops = trunc (myKEYS.l_update / myKEYS.l_delay);
   }
   if (myKEYS.l_loops == 0)  myKEYS.l_loops = 1;
   /*---(flag blocking)------------------*/
   if (x_base == 0.0)        myKEYS.l_blocking = 'y';
   else                      myKEYS.l_blocking = '-';
   /*---(progress advance)---------------*/
   /*> myVIKEYS.p_inc  = s_scale_info [myVIKEYS.p_scale].unit / 10.0;                                                 <* 
    *> /+> myVIKEYS.p_inc  = s_scale_info [myVIKEYS.p_scale].unit;                        <+/                         <* 
    *> /+> printf ("x_base   = %f\n", x_base);                                            <+/                         <* 
    *> x_base         *= myKEYS.l_loops;                                                                              <* 
    *> /+> printf ("x_base   = %f\n", x_base);                                            <+/                         <* 
    *> if (x_base == 0.0) {                                                                                           <* 
    *>    myVIKEYS.p_adv  = 0.0;                                                                                      <* 
    *> } else {                                                                                                       <* 
    *>    myVIKEYS.p_adv  = (float) (s_scale_info [myVIKEYS.p_scale].unit * s_speed_info [myVIKEYS.p_speed].speed);   <* 
    *>    /+> printf ("p_adv    = %lf\n", myVIKEYS.p_adv);                                <+/                         <* 
    *>    myVIKEYS.p_adv *= x_base;                                                                                   <* 
    *>    /+> printf ("p_adv    = %lf\n", myVIKEYS.p_adv);                                <+/                         <* 
    *>    /+> printf ("p_adv    = %28.14lf\n", myVIKEYS.p_adv);                           <+/                         <* 
    *> }                                                                                                              <*/
   /*---(redraw)-------------------------*/
   /*> myVIKEYS.p_redraw = 'y';                                                       <*/
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       main loop timing                       ----===*/
/*====================------------------------------------====================*/
static void      o___LOOPING_________________o (void) {;}

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



/*====================------------------------------------====================*/
/*===----                      setting values                          ----===*/
/*====================------------------------------------====================*/
static void      o___SETTING_________________o (void) {;}

char
ykeys__loop_shared      (char a_type, char *a_string)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_prefix    =  ' ';
   int         i           =    0;
   char        x_new       =   -1;
   char        x_max       =   -1;
   char        x_curr      =   -1;
   char        x_save      =   -1;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   /*---(determine max)------------------*/
   DEBUG_KEYS   yLOG_schar   (a_type);
   --rce;  switch (a_type) {
   case 'u' :
      x_curr = g_cupdate;
      x_max  = g_nupdate - 1;
      break;
   case 'd' :
      x_curr = g_cdelay;
      x_max  = g_ndelay - 1;
      break;
   default  :
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_sint    (x_max);
   /*---(assign prefix)------------------*/
   DEBUG_KEYS   yLOG_spoint  (a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_snote   (a_string);
   x_prefix = a_string [0];
   DEBUG_KEYS   yLOG_sint    (x_prefix);
   /*---(find entry in table)------------*/
   DEBUG_KEYS   yLOG_sint    (x_curr);
   switch (x_prefix) {
   case '[' :
      x_new  = 0;
      break;
   case '<' :
      if (x_curr >  1    )  x_new  = --x_curr;
      else {
         x_new  = 0;
         rc = -4;
      }
      break;
   case '.' : case '=' :
      x_new  = x_curr;
      break;
   case '>' :
      if (x_curr <  x_max)  x_new  = ++x_curr;
      else {
         x_new  = x_max;
         rc = -3;
      }
      break;
   case ']' :
      x_new  = x_max;
      break;
   default  :
      for (i = 0; i <= x_max; ++i) {
         if (a_type == 'u' && strcmp (g_updates [i].terse, a_string) != 0)  continue;
         if (a_type == 'd' && strcmp (g_delays  [i].terse, a_string) != 0)  continue;
         x_new  = i;
         break;
      }
      if (x_new  == -1) {
         x_new  = x_curr;
         rc = -2;
      }
      break;
   }
   DEBUG_KEYS   yLOG_sint    (x_new);
   /*---(set key values)-----------------*/
   --rce;  switch (a_type) {
   case 'u' :
      g_cupdate       = x_new;
      myKEYS.l_update = g_updates [x_new].update;
      DEBUG_KEYS   yLOG_sdouble (myKEYS.l_update);
      break;
   case 'd' :
      g_cdelay        = x_new;
      myKEYS.l_delay  = g_delays  [x_new].delay;
      DEBUG_KEYS   yLOG_sdouble (myKEYS.l_delay);
      break;
   default  :
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   /*---(update looping)-----------------*/
   ykeys__loop_calc   ();
   /*---(complete)-----------------------*/
   return rc;
}

char ykeys_loop_update       (char *a_update)  { return ykeys__loop_shared ('u', a_update); }
char ykeys_loop_delay        (char *a_delay)   { return ykeys__loop_shared ('d', a_delay);  }

char
yKEYS_loop_set          (char *a_delay, char *a_update)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        rc1         =    0;
   char        rc2         =    0;
   /*---(set values)---------------------*/
   rc1 = ykeys_loop_delay   (a_delay);
   if (rc1 >= 0)  strlcpy (g_sdelay , g_delays  [g_cdelay ].terse, LEN_LABEL);
   else           rc = rc1;
   rc2 = ykeys_loop_update  (a_update);
   if (rc2 >= 0)  strlcpy (g_supdate, g_updates [g_cupdate].terse, LEN_LABEL);
   else           rc = rc2;
   /*---(complete)-----------------------*/
   return rc;
}



/*====================------------------------------------====================*/
/*===----                       macro support                          ----===*/
/*====================------------------------------------====================*/
static void      o___MACROS__________________o (void) {;}

char
yKEYS_loop_macro        (char a_delay, char a_update)
{
   /*---(no change for playback)---------*/
   IF_MACRO_PLAYBACK {
      yKEYS_loop_return ();
      return 0;
   }
   /*---(change to macro speed)----------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_KEYS   yLOG_schar   (yMACRO_exe_mode ());
   DEBUG_KEYS   yLOG_sint    (a_delay);
   DEBUG_KEYS   yLOG_schar   (a_delay);
   /*---(run mode)-----------------------*/
   /*> IF_MACRO_RUN   a_delay = '0';                                                  <*/
   /*---(delay mode)---------------------*/
   switch (a_delay) {
   case MACRO_BLITZ  :  ykeys_loop_delay ("1us"  );   myKEYS.l_skip =  0;   break;
   case MACRO_FAST   :  ykeys_loop_delay ("100us");   myKEYS.l_skip =  0;   break;
   case MACRO_THOU   :  ykeys_loop_delay ("1ms"  );   myKEYS.l_skip =  0;   break;
   case MACRO_HUND   :  ykeys_loop_delay ("10ms" );   myKEYS.l_skip =  0;   break;
   case MACRO_TWENTY :  ykeys_loop_delay ("10ms" );   myKEYS.l_skip =  4;   break;
   case MACRO_TENTH  :  ykeys_loop_delay ("100ms");   myKEYS.l_skip =  0;   break;
   case MACRO_HALF   :  ykeys_loop_delay ("100ms");   myKEYS.l_skip =  4;   break;
   case MACRO_SEC    :  ykeys_loop_delay ("100ms");   myKEYS.l_skip =  9;   break;
   case MACRO_DOUBLE :  ykeys_loop_delay ("100ms");   myKEYS.l_skip = 19;   break;
   case MACRO_TRIPLE :  ykeys_loop_delay ("100ms");   myKEYS.l_skip = 29;   break;
   }
   DEBUG_KEYS   yLOG_sint    (myKEYS.l_skip);
   /*---(change update basis)------------*/
   DEBUG_KEYS   yLOG_sint    (a_update);
   DEBUG_KEYS   yLOG_schar   (a_update);
   switch (a_update) {
   case MACRO_NORMAL :  ykeys_loop_update ("100ms");  break;
   case MACRO_SLOWER :  ykeys_loop_update ("500ms");  break;
   case MACRO_BLINKS :  ykeys_loop_update ("2s");     break;
   case MACRO_PEEKS  :  ykeys_loop_update ("5s");     break;
   case MACRO_BLIND  :  ykeys_loop_update ("100s");   break;
   }
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yKEYS_loop_return       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(return to normal)---------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_KEYS   yLOG_schar   (yMACRO_exe_mode ());
   DEBUG_KEYS   yLOG_snote   (g_sdelay);
   rc = ykeys_loop_delay   (g_sdelay);
   myKEYS.l_skip = 0;
   DEBUG_KEYS   yLOG_sint    (myKEYS.l_skip);
   DEBUG_KEYS   yLOG_snote   (g_supdate);
   rc = ykeys_loop_update  (g_supdate);
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yKEYS_loop_blitz        (void)
{
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_double  ("delay"     , myKEYS.l_delay);
   if (myKEYS.l_delay <  0.00001) {
      DEBUG_KEYS   yLOG_note    ("already in blitz, nothing to do");
      DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   g_bdelay        = myKEYS.l_delay;
   myKEYS.l_delay  =   0.000001;
   g_bskip         = myKEYS.l_skip;
   myKEYS.l_skip   =   0;
   g_bupdate       = myKEYS.l_update;
   myKEYS.l_update =   100.000000;
   ykeys__loop_calc ();
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_loop_unblitz      (void)
{
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_double  ("delay"     , myKEYS.l_delay);
   if (myKEYS.l_delay >= 0.00001) {
      DEBUG_KEYS   yLOG_note    ("not in blitz, nothing to do");
      DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   myKEYS.l_delay  = g_bdelay;
   myKEYS.l_skip   = g_bskip;
   myKEYS.l_update = g_bupdate;
   g_bdelay        = 0.0;
   g_bskip         =   0;
   g_bupdate       = 0.0;
   ykeys__loop_calc ();
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}


char
yKEYS_loop_beg          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTSPEC      x_dur;
   /*---(reset timing);------------------*/
   myKEYS.l_beg   = 0;
   myKEYS.l_graf  = 0;
   myKEYS.l_end   = 0;
   /*---(get beginning time)-------------*/
   clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);
   myKEYS.l_beg   = x_dur.tv_sec * NSEC;
   myKEYS.l_beg  += x_dur.tv_nsec;
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_loop_graf         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTSPEC      x_dur;
   /*---(get beginning time)-------------*/
   clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);
   myKEYS.l_graf  = x_dur.tv_sec * NSEC;
   myKEYS.l_graf += x_dur.tv_nsec;
   /*---(complete)-----------------------*/
   return 0;
}
char
yKEYS_loop_end          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTSPEC      x_dur;
   /*---(get beginning time)-------------*/
   clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);
   myKEYS.l_end   = x_dur.tv_sec * NSEC;
   myKEYS.l_end  += x_dur.tv_nsec;
   if (myKEYS.l_graf == 0)  myKEYS.l_graf = myKEYS.l_end;
   /*---(calc diffs)---------------------*/
   myKEYS.l_exp   = (myKEYS.l_secs * NSEC) + myKEYS.l_nsec;
   myKEYS.l_act   = myKEYS.l_end - myKEYS.l_prev;
   s_miss_time   += myKEYS.l_exp - myKEYS.l_act;
   myKEYS.l_slept = myKEYS.l_beg - myKEYS.l_prev;
   myKEYS.l_used  = myKEYS.l_end - myKEYS.l_beg;
   myKEYS.l_sleep = myKEYS.l_exp - myKEYS.l_used;
   /*---(calc run diffs)-----------------*/
   if (myKEYS.l_blocking == 'y')  myKEYS.l_sleep = 0;
   myKEYS.l_prev  = myKEYS.l_end;
   /*---(for timer)----------------------*/
   s_pct        = (myKEYS.l_used / (float) myKEYS.l_exp) * 100.0;
   DEBUG_KEYS   yLOG_complex ("timing"    , "%10ds, %10dn, %10db, %10dt, %10de, %10du, %10dr, %8.6f", myKEYS.l_secs, myKEYS.l_nsec, myKEYS.l_beg, myKEYS.l_exp, myKEYS.l_end, myKEYS.l_used, myKEYS.l_sleep, s_pct);
   /*---(complete)-----------------------*/
   return 0;
}

char
ykeys_loop_sleep        (uchar a_key, char a_draw)
{
   /*---(locals)-----------+-----+-----+-*/
   static long x_secs      =    0;
   static long x_nsec      =    0;
   tTSPEC      x_dur;
   static int  x_draws     =    0;
   static int  x_idles     =    0;
   char        x_flag      =  '-';
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_complex ("args"      , "%3d, %c, %c, %c blocking", a_key, chrvisible (a_key), a_draw, myKEYS.l_blocking);
   /*---(get ending time)----------------*/
   yKEYS_loop_end ();
   /*---(statistics)---------------------*/
   s_total_time     += myKEYS.l_end  - myKEYS.l_beg;
   myKEYS.l_avg_all  = s_total_time / (float) myKEYS.loops;
   myKEYS.l_avg_miss = s_miss_time  / (float) myKEYS.loops;
   if (a_key  != 0) {
      ++(myKEYS.l_keys);
      s_keys_time      += myKEYS.l_graf - myKEYS.l_beg;
      myKEYS.l_avg_keys = s_keys_time  / (float) myKEYS.l_keys;
      x_flag = 'y';
   }
   if (a_draw == 'y') {
      ++(myKEYS.l_draw);
      s_draw_time      += myKEYS.l_end  - myKEYS.l_graf;
      myKEYS.l_avg_draw = s_draw_time / (float) myKEYS.l_draw;
      x_flag = 'y';
   }
   if (x_flag != 'y') {
      ++(myKEYS.l_idle);
   }
   DEBUG_KEYS   yLOG_complex ("counts"    , "%6dd, %6dk, %6di", x_draws, myKEYS.l_keys, x_idles);
   /*---(sleeping)-----------------------*/
   if (myKEYS.l_blocking != 'y') {
      x_dur.tv_sec  = myKEYS.l_sleep / NSEC;
      x_dur.tv_nsec = myKEYS.l_sleep % NSEC;
      DEBUG_KEYS   yLOG_note    ("nano-sleeping");
      nanosleep      (&x_dur, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return 0;
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
    *>       myKEYS.l_exp, myKEYS.l_sleep, myKEYS.l_used, s_avg, myKEYS.l_draw, myKEYS.a_keys, myKEYS.l_idle);    <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> return 0;                                                                      <*/
}


