/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



#define     NSEC        1000000000



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
float   g_bupdate  = 0.0;          /* pre-blitz updates per second            */
char    g_supdate  [LEN_LABEL] = "every";


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
float   g_bdelay   = 0.0;          /* pre-blitz delay seconds between loops   */
char    g_sdelay   [LEN_LABEL] = "keys";



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

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
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(determine max)------------------*/
   DEBUG_LOOP   yLOG_schar   (a_type);
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
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_sint    (x_max);
   /*---(assign prefix)------------------*/
   DEBUG_LOOP   yLOG_spoint  (a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_snote   (a_string);
   x_prefix = a_string [0];
   DEBUG_LOOP   yLOG_sint    (x_prefix);
   /*---(find entry in table)------------*/
   DEBUG_LOOP   yLOG_sint    (x_curr);
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
   DEBUG_LOOP   yLOG_sint    (x_new);
   /*---(set key values)-----------------*/
   --rce;  switch (a_type) {
   case 'u' :
      g_cupdate       = x_new;
      myKEYS.l_update = g_updates [x_new].update;
      DEBUG_LOOP   yLOG_sdouble (myKEYS.l_update);
      break;
   case 'd' :
      g_cdelay        = x_new;
      myKEYS.l_delay  = g_delays  [x_new].delay;
      DEBUG_LOOP   yLOG_sdouble (myKEYS.l_delay);
      break;
   default  :
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   /*---(update looping)-----------------*/
   ykeys__loop_calc   ();
   /*---(complete)-----------------------*/
   return rc;
}

char ykeys_loop_update       (char *a_update)  { return ykeys__loop_shared ('u', a_update); }
char ykeys_loop_delay        (char *a_delay)   { return ykeys__loop_shared ('d', a_delay);  }

/*> char                                                                                          <* 
 *> yvikeys_loop_delay      (char *a_delay)                                                       <* 
 *> {                                                                                             <* 
 *>    /+> /+---(locals)-----------+-----+-----+-+/                                       <*      <* 
 *>     *> char        rc          =    0;                                                <*      <* 
 *>     *> char        x_prefix    =  ' ';                                                <*      <* 
 *>     *> int         i           =    0;                                                <*      <* 
 *>     *> char        x_index     =   -1;                                                <*      <* 
 *>     *> char        x_max       =   -1;                                                <*      <* 
 *>     *> /+---(header)-------------------------+/                                       <*      <* 
 *>     *> DEBUG_LOOP   yLOG_senter  (__FUNCTION__);                                      <*      <* 
 *>     *> /+---(assign prefix)------------------+/                                       <*      <* 
 *>     *> DEBUG_LOOP   yLOG_snote   (a_delay);                                           <*      <* 
 *>     *> if (a_delay  == NULL)   x_prefix = 0;                                          <*      <* 
 *>     *> else                    x_prefix = a_delay [0];                                <*      <* 
 *>     *> DEBUG_LOOP   yLOG_sint    (x_prefix);                                          <*      <* 
 *>     *> /+---(determine max)------------------+/                                       <*      <* 
 *>     *> for (i = 0; i < MAX_DELAY; ++i) {                                              <*      <* 
 *>     *>    if (strcmp (g_delays [i].terse, "---"  ) == 0)  break;                  <*          <* 
 *>     *>    ++x_max;                                                                    <*      <* 
 *>     *> }                                                                              <*      <* 
 *>     *> /+---(find entry in table)------------+/                                       <*      <* 
 *>     *> DEBUG_LOOP   yLOG_sint    (g_cdelay);                                           <*     <* 
 *>     *> switch (x_prefix) {                                                            <*      <* 
 *>     *> case  0  :                                                                     <*      <* 
 *>     *>    x_index = g_cdelay;                                                          <*     <* 
 *>     *>    rc = -1;                                                                    <*      <* 
 *>     *>    break;                                                                      <*      <* 
 *>     *> case '0' :                                                                     <*      <* 
 *>     *>    x_index = 0;                                                                <*      <* 
 *>     *>    break;                                                                      <*      <* 
 *>     *> case '=' :                                                                     <*      <* 
 *>     *>    x_index = g_cdelay;                                                          <*     <* 
 *>     *>    break;                                                                      <*      <* 
 *>     *> case '>' :                                                                     <*      <* 
 *>     *>    if (g_cdelay  <  x_max)  x_index = ++g_cdelay;                                <*    <* 
 *>     *>    else {                                                                      <*      <* 
 *>     *>       x_index = x_max;                                                         <*      <* 
 *>     *>       rc = -3;                                                                 <*      <* 
 *>     *>    }                                                                           <*      <* 
 *>     *>    break;                                                                      <*      <* 
 *>     *> case '<' :                                                                     <*      <* 
 *>     *>    if (g_cdelay  >  1    )  x_index = --g_cdelay;                                <*    <* 
 *>     *>    else {                                                                      <*      <* 
 *>     *>       x_index = 1;                                                             <*      <* 
 *>     *>       rc = -4;                                                                 <*      <* 
 *>     *>    }                                                                           <*      <* 
 *>     *>    break;                                                                      <*      <* 
 *>     *> default  :                                                                     <*      <* 
 *>     *>    for (i = 0; i < x_max; ++i) {                                               <*      <* 
 *>     *>       if (strcmp (g_delays [i].terse, a_delay) != 0)  continue;            <*          <* 
 *>     *>       x_index = i;                                                             <*      <* 
 *>     *>       break;                                                                   <*      <* 
 *>     *>    }                                                                           <*      <* 
 *>     *>    if (x_index == -1) {                                                        <*      <* 
 *>     *>       x_index = g_cdelay;                                                       <*     <* 
 *>     *>       rc = -2;                                                                 <*      <* 
 *>     *>    }                                                                           <*      <* 
 *>     *>    break;                                                                      <*      <* 
 *>     *> }                                                                              <*      <* 
 *>     *> /+---(set key values)-----------------+/                                       <*      <* 
 *>     *> DEBUG_LOOP   yLOG_sint    (x_index);                                           <*      <* 
 *>     *> g_cdelay         = x_index;                                                     <*     <* 
 *>     *> myKEYS.l_delay  = g_delays [x_index].delay;                                <*          <* 
 *>     *> DEBUG_LOOP   yLOG_sdouble (myKEYS.l_delay);                                    <*      <* 
 *>     *> DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);                                      <*      <* 
 *>     *> /+---(update looping)-----------------+/                                       <*      <* 
 *>     *> yvikeys__loop_calc   ();                                                       <*      <* 
 *>     *> /+---(complete)-----------------------+/                                       <*      <* 
 *>     *> return rc;                                                                     <+/     <* 
 *> }                                                                                             <*/

char
ykeys_loop_blitz        (void)
{
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   DEBUG_LOOP   yLOG_double  ("delay"     , myKEYS.l_delay);
   if (myKEYS.l_delay <  0.00001) {
      DEBUG_LOOP   yLOG_note    ("already in blitz, nothing to do");
      DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   g_bdelay        = myKEYS.l_delay;
   myKEYS.l_delay  =   0.000001;
   g_bupdate  = myKEYS.l_update;
   myKEYS.l_update =   100.000000;
   ykeys__loop_calc ();
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ykeys_loop_unblitz      (void)
{
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   DEBUG_LOOP   yLOG_double  ("delay"     , myKEYS.l_delay);
   if (myKEYS.l_delay >= 0.00001) {
      DEBUG_LOOP   yLOG_note    ("not in blitz, nothing to do");
      DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   myKEYS.l_delay  = g_bdelay;
   myKEYS.l_update = g_bupdate;
   ykeys__loop_calc ();
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_loop_set          (char *a_delay, char *a_update)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        rc1         =    0;
   char        rc2         =    0;
   /*---(set values)---------------------*/
   rc1 = ykeys_loop_delay   (a_delay);
   if (rc1 >= 0)  strlcpy (g_sdelay , a_delay , LEN_LABEL);
   else           rc = rc1;
   rc2 = ykeys_loop_update  (a_update);
   if (rc2 >= 0)  strlcpy (g_supdate, a_update, LEN_LABEL);
   else           rc = rc2;
   /*---(complete)-----------------------*/
   return rc;
}

char
yKEYS_loop_normal       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(return to normal)---------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   DEBUG_LOOP   yLOG_schar   (yMACRO_exe_mode ());
   DEBUG_LOOP   yLOG_snote   (g_sdelay);
   rc = ykeys_loop_delay   (g_sdelay);
   myKEYS.l_skip = 0;
   DEBUG_LOOP   yLOG_sint    (myKEYS.l_skip);
   DEBUG_LOOP   yLOG_snote   (g_supdate);
   rc = ykeys_loop_update  (g_supdate);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yKEYS_loop_macro        (char a_delay, char a_update)
{
   /*---(no change for playback)---------*/
   IF_MACRO_PLAYBACK {
      yKEYS_loop_normal ();
      return 0;
   }
   /*---(change to macro speed)----------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   DEBUG_LOOP   yLOG_schar   (yMACRO_exe_mode ());
   DEBUG_LOOP   yLOG_sint    (a_delay);
   DEBUG_LOOP   yLOG_schar   (a_delay);
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
   DEBUG_LOOP   yLOG_sint    (myKEYS.l_skip);
   /*---(change update basis)------------*/
   DEBUG_LOOP   yLOG_sint    (a_update);
   DEBUG_LOOP   yLOG_schar   (a_update);
   switch (a_update) {
   case MACRO_NORMAL :  ykeys_loop_update ("100ms");  break;
   case MACRO_SLOWER :  ykeys_loop_update ("500ms");  break;
   case MACRO_BLINKS :  ykeys_loop_update ("2s");     break;
   case MACRO_PEEKS  :  ykeys_loop_update ("5s");     break;
   case MACRO_BLIND  :  ykeys_loop_update ("100s");   break;
   }
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
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
    *>       g_delays [g_cdelay].terse, g_delays [g_cdelay].delay, myKEYS.l_secs, myKEYS.l_nsec,              <* 
    *>       g_updates [g_cupdate].terse, g_updates [g_cupdate].update, myKEYS.l_loops, myKEYS.l_blocking);   <* 
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


