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


static struct {
   char        abbr;
   char        terse       [LEN_TERSE];
   char        skip;
   char        desc        [LEN_DESC];
} const s_mdelay [20] = {
   { MACRO_BLITZ  , "1us"  ,   0, "million times a sec"   },
   { MACRO_FAST   , "100us",   0, "ten-thousand a sec"    },
   { MACRO_THOU   , "1ms"  ,   0, "thousand times a sec"  },
   { MACRO_HUND   , "10ms" ,   0, "hundred a sec (normal)"},
   { MACRO_TWENTY , "10ms" ,   4, "twenty times a sec"    },
   { MACRO_TENTH  , "100ms",   0, "ten times a sec"       },
   { MACRO_HALF   , "100ms",   4, "twice a sec"           },
   { MACRO_SEC    , "100ms",   9, "every sec"             },
   { MACRO_DOUBLE , "100ms",  19, "every two secs"        },
   { MACRO_TRIPLE , "100ms",  29, "every three secs"      },
   { 0            , ""     ,   0, ""                      },

};

static struct {
   char        abbr;
   char        terse       [LEN_TERSE];
   char        desc        [LEN_DESC];
} const s_mupdate [20] = {
   { MACRO_FAST   , "10ms" , "hundred times a sec"        },
   { MACRO_NORMAL , "100ms", "ten times a sec (normal)"   },
   { MACRO_SLOWER , "500ms", "twice times a sec"          },
   { MACRO_BLINKS , "2s"   , "two secs before update"     },
   { MACRO_PEEKS  , "5s"   , "five secs before update"    },
   { MACRO_BLIND  , "100s" , "hundred secs before update" },
   { 0            , ""     , ""                           },
};



/*====================------------------------------------====================*/
/*===----                        description                           ----===*/
/*====================------------------------------------====================*/
static void      o___INFO____________________o (void) {;}

char
yKEYS_edelay_info       (char n, char *a_terse, char *a_desc, float *a_delay)
{
   if (a_terse  != NULL)  strcpy (a_terse, "");
   if (a_desc   != NULL)  strcpy (a_desc , "");
   if (a_delay  != NULL)  *a_delay  = 0.0;
   if (n < 0 || n >= myKEYS.l_ndelay)  return -1;
   if (a_terse  != NULL)  strcpy (a_terse, g_delays [n].terse);
   if (a_desc   != NULL)  strcpy (a_desc , g_delays [n].desc);
   if (a_delay  != NULL)  *a_delay  = g_delays [n].delay;
   return 0;
}

char
yKEYS_eupdate_info      (char n, char *a_terse, char *a_desc, float *a_update)
{
   if (a_terse  != NULL)  strcpy (a_terse, "");
   if (a_desc   != NULL)  strcpy (a_desc , "");
   if (a_update != NULL)  *a_update = 0.0;
   if (n < 0 || n >= myKEYS.l_nupdate)  return -1;
   if (a_terse  != NULL)  strcpy (a_terse, g_updates [n].terse);
   if (a_desc   != NULL)  strcpy (a_desc , g_updates [n].desc);
   if (a_update != NULL)  *a_update = g_updates [n].update;
   return 0;
}

char
yKEYS_ddelay_info       (char a_abbr, char *a_terse, char *a_skip, char *a_desc)
{
   int         i           =    0;
   if (a_terse != NULL)  strcpy (a_terse, "");
   if (a_skip  != NULL)  *a_skip = 0;
   if (a_desc  != NULL)  strcpy (a_desc , "");
   for (i = 0; i < 20; ++i) {
      if (s_mdelay [i].abbr == 0)      break;
      if (s_mdelay [i].abbr != a_abbr) continue;
      if (a_terse != NULL)  strcpy (a_terse, s_mdelay [i].terse);
      if (a_skip  != NULL)  *a_skip = s_mdelay [i].skip;
      if (a_desc  != NULL)  strcpy (a_desc , s_mdelay [i].desc);
      return 0;
   }
   return -1;
}

char
yKEYS_dupdate_info      (char a_abbr, char *a_terse, char *a_desc)
{
   int         i           =    0;
   if (a_terse != NULL)  strcpy (a_terse, "");
   if (a_desc   != NULL)  strcpy (a_desc  , "");
   for (i = 0; i < 20; ++i) {
      if (s_mupdate [i].abbr == 0)      break;
      if (s_mupdate [i].abbr != a_abbr) continue;
      if (a_terse != NULL)  strcpy (a_terse, s_mupdate [i].terse);
      if (a_desc  != NULL)  strcpy (a_desc , s_mupdate [i].desc);
      return 0;
   }
   return -1;
}




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
   /*---(delay)--------------------------*/
   myKEYS.l_ndelay   =   0;
   myKEYS.l_cdelay   =   7;
   strcpy (myKEYS.l_sdelay, "keys");
   myKEYS.l_delay    = 0.0;
   myKEYS.l_skip     =   0;
   myKEYS.l_bdelay   = 0.0;
   myKEYS.l_bskip    =   0;
   /*---(update)-------------------------*/
   myKEYS.l_nupdate  =   0;
   myKEYS.l_cupdate  =   0;
   strcpy (myKEYS.l_supdate, "every");
   myKEYS.l_update   = 0.0;
   myKEYS.l_secs     =   0;
   myKEYS.l_nsec     =   0;
   myKEYS.l_loops    =   1;
   myKEYS.l_blocking = '-';
   /*---(clear other)--------------------*/
   ykeys_loop_clear ();
   /*---(count updates)------------------*/
   myKEYS.l_cupdate = 4;
   for (i = 0; i < MAX_UPDATE; ++i) {
      if (strcmp (g_updates [i].terse, "---"   ) == 0)  break;
      ++myKEYS.l_nupdate;
   }
   /*---(count delays)-------------------*/
   for (i = 0; i < MAX_DELAY;  ++i) {
      if (strcmp (g_delays  [i].terse, "---"   ) == 0)  break;
      ++myKEYS.l_ndelay;
   }
   /*---(initial setting)----------------*/
   yKEYS_loop_set ("10ms" , "100ms");
   /*---(saves)--------------------------*/
   /*> strcpy (myKEYS.l_sdelay , "keys" );                                                   <*/
   /*> strcpy (myKEYS.l_supdate, "every");                                                   <*/
   /*---(blitzing)-----------------------*/
   myKEYS.l_bupdate = 0.0;
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
   /*---(header)-------------------------*/
   DEBUG_LOOP    yLOG_senter  (__FUNCTION__);
   /*---(initialize)---------------------*/
   myKEYS.l_secs  = 0;
   myKEYS.l_nsec  = 0;
   myKEYS.l_loops = 1;
   DEBUG_LOOP    yLOG_sint    (myKEYS.l_delay);
   DEBUG_LOOP    yLOG_sint    (myKEYS.l_update);
   /*---(keyboard only)------------------*/
   if      (myKEYS.l_delay  == 0.0 && myKEYS.l_update == 0.0) {
      DEBUG_LOOP    yLOG_snote   ("l_delay and l_update zero");
      x_base = myKEYS.l_delay;
   }
   /*---(delay, no update)---------------*/
   else if (myKEYS.l_delay  >  0.0 && myKEYS.l_update == 0.0) {
      DEBUG_LOOP    yLOG_snote   ("l_delay positive but l_update zero");
      x_base = myKEYS.l_delay;
   }
   /*---(update, no delay)---------------*/
   else if (myKEYS.l_update  > 0.0 && myKEYS.l_delay  == 0.0) {
      DEBUG_LOOP    yLOG_snote   ("l_update positive but l_delay zero");
      x_base = myKEYS.l_update;
   }
   /*---(fast enough)--------------------*/
   else if (myKEYS.l_delay <= myKEYS.l_update) {
      DEBUG_LOOP    yLOG_snote   ("l_delay less than or equal l_update");
      x_base = myKEYS.l_delay;
   }
   /*---(too slow)-----------------------*/
   else {
      DEBUG_LOOP    yLOG_snote   ("l_delay greater than l_update");
      x_base = myKEYS.l_update;
   }
   /*---(update timing)------------------*/
   DEBUG_LOOP    yLOG_sint    (x_base);
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
   DEBUG_LOOP    yLOG_schar   (myKEYS.l_blocking);
   /*---(progress advance)---------------*/
   myKEYS.p_inc  = g_scale_info [myKEYS.p_scale].unit / 10.0;
   /*> myKEYS.p_inc  = g_scale_info [myKEYS.p_scale].unit;                        <*/
   /*> printf ("x_base   = %f\n", x_base);                                            <*/
   x_base         *= myKEYS.l_loops;
   /*> printf ("x_base   = %f\n", x_base);                                            <*/
   if (x_base == 0.0) {
      myKEYS.p_adv  = 0.0;
   } else {
      myKEYS.p_adv  = (float) (g_scale_info [myKEYS.p_scale].unit * g_speed_info [myKEYS.p_speed].speed);
      /*> printf ("p_adv    = %lf\n", myKEYS.p_adv);                                <*/
      myKEYS.p_adv *= x_base;
      /*> printf ("p_adv    = %lf\n", myKEYS.p_adv);                                <*/
      /*> printf ("p_adv    = %28.14lf\n", myKEYS.p_adv);                           <*/
   }
   /*---(redraw)-------------------------*/
   /*> myKEYS.p_redraw = 'y';                                                       <*/
   /*---(complete)-----------------------*/
   DEBUG_LOOP    yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       main loop timing                       ----===*/
/*====================------------------------------------====================*/
static void      o___LOOPING_________________o (void) {;}

char
ykeys_loop_prog         (void)
{
   if (myKEYS.p_play == 'y') {
      myKEYS.p_cur += myKEYS.p_adv;
   }
   if (myKEYS.p_cur <  myKEYS.p_beg) {
      if (myKEYS.p_repeat == 'y' && myKEYS.p_play == 'y') {
         myKEYS.p_cur  = myKEYS.p_end;
         myKEYS.p_play = 'y';
      } else {
         myKEYS.p_cur  = myKEYS.p_beg;
         myKEYS.p_play = '-';
      }
   }
   if (myKEYS.p_cur >  myKEYS.p_end) {
      if (myKEYS.p_repeat == 'y' && myKEYS.p_play == 'y') {
         myKEYS.p_cur  = myKEYS.p_beg;
         myKEYS.p_play = 'y';
      } else {
         myKEYS.p_cur  = myKEYS.p_end;
         myKEYS.p_play = '-';
      }
   }
   return 0;
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
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(determine max)------------------*/
   DEBUG_YKEYS   yLOG_schar   (a_type);
   --rce;  switch (a_type) {
   case 'u' :
      x_curr = myKEYS.l_cupdate;
      x_max  = myKEYS.l_nupdate - 1;
      break;
   case 'd' :
      x_curr = myKEYS.l_cdelay;
      x_max  = myKEYS.l_ndelay - 1;
      break;
   default  :
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_sint    (x_max);
   /*---(assign prefix)------------------*/
   DEBUG_YKEYS   yLOG_spoint  (a_string);
   --rce;  if (a_string == NULL) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_snote   (a_string);
   x_prefix = a_string [0];
   DEBUG_YKEYS   yLOG_sint    (x_prefix);
   /*---(find entry in table)------------*/
   DEBUG_YKEYS   yLOG_sint    (x_curr);
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
   DEBUG_YKEYS   yLOG_sint    (x_new);
   /*---(set key values)-----------------*/
   --rce;  switch (a_type) {
   case 'u' :
      myKEYS.l_cupdate       = x_new;
      myKEYS.l_update = g_updates [x_new].update;
      DEBUG_YKEYS   yLOG_sdouble (myKEYS.l_update);
      break;
   case 'd' :
      myKEYS.l_cdelay        = x_new;
      myKEYS.l_delay  = g_delays  [x_new].delay;
      DEBUG_YKEYS   yLOG_sdouble (myKEYS.l_delay);
      break;
   default  :
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
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
   if (rc1 >= 0)  ystrlcpy (myKEYS.l_sdelay , g_delays  [myKEYS.l_cdelay ].terse, LEN_LABEL);
   else           rc = rc1;
   rc2 = ykeys_loop_update  (a_update);
   if (rc2 >= 0)  ystrlcpy (myKEYS.l_supdate, g_updates [myKEYS.l_cupdate].terse, LEN_LABEL);
   else           rc = rc2;
   /*---(complete)-----------------------*/
   return rc;
}

char
yKEYS_loop_get          (float *a_delay, char *a_dterse, float *a_update, char *a_uterse)
{
   char        n           =    0;
   n = myKEYS.l_cdelay;
   yKEYS_edelay_info  (n, a_dterse, NULL, a_delay);
   n = myKEYS.l_cupdate;
   yKEYS_eupdate_info (n, a_uterse, NULL, a_update);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                       macro support                          ----===*/
/*====================------------------------------------====================*/
static void      o___MACROS__________________o (void) {;}

char
yKEYS_loop_macro        (char a_delay, char a_update)
{
   char        rce         =  -10;
   char        rc          =    0;
   char        x_terse     [LEN_LABEL] = "";
   /*---(no change for playback)---------*/
   IF_MACRO_PLAYBACK {
      yKEYS_loop_return ();
      return 0;
   }
   /*---(change to macro speed)----------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_YKEYS   yLOG_schar   (yVIHUB_yMACRO_exe_mode ("show"));
   /*---(run mode)-----------------------*/
   /*> IF_MACRO_RUN   a_delay = '0';                                                  <*/
   /*---(delay mode)---------------------*/
   DEBUG_YKEYS   yLOG_schar   (a_delay);
   rc = yKEYS_ddelay_info (a_delay, x_terse, &(myKEYS.l_skip), NULL);
   DEBUG_YKEYS   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_snote   (x_terse);
   DEBUG_YKEYS   yLOG_sint    (myKEYS.l_skip);
   ykeys_loop_delay (x_terse);
   /*---(change update basis)------------*/
   DEBUG_YKEYS   yLOG_schar   (a_update);
   rc = yKEYS_dupdate_info (a_update, x_terse, NULL);
   DEBUG_YKEYS   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_snote   (x_terse);
   ykeys_loop_update (x_terse);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yKEYS_loop_return       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(return to normal)---------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_char    ("emode"     , yVIHUB_yMACRO_exe_mode ("show"));
   DEBUG_YKEYS   yLOG_info    ("sdelay"    , myKEYS.l_sdelay);
   rc = ykeys_loop_delay   (myKEYS.l_sdelay);
   myKEYS.l_skip = 0;
   DEBUG_YKEYS   yLOG_value   ("skip"      , myKEYS.l_skip);
   DEBUG_YKEYS   yLOG_info    ("supdate"   , myKEYS.l_supdate);
   rc = ykeys_loop_update  (myKEYS.l_supdate);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yKEYS_loop_blitz        (void)
{
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_double  ("delay"     , myKEYS.l_delay);
   if (myKEYS.l_delay <  0.00001) {
      DEBUG_YKEYS   yLOG_note    ("already in blitz, nothing to do");
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   myKEYS.l_bdelay        = myKEYS.l_delay;
   myKEYS.l_delay  =   0.000001;
   myKEYS.l_bskip         = myKEYS.l_skip;
   myKEYS.l_skip   =   0;
   myKEYS.l_bupdate       = myKEYS.l_update;
   myKEYS.l_update =   100.000000;
   ykeys__loop_calc ();
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_loop_unblitz      (void)
{
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_double  ("delay"     , myKEYS.l_delay);
   if (myKEYS.l_delay >= 0.00001) {
      DEBUG_YKEYS   yLOG_note    ("not in blitz, nothing to do");
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   myKEYS.l_delay  = myKEYS.l_bdelay;
   myKEYS.l_skip   = myKEYS.l_bskip;
   myKEYS.l_update = myKEYS.l_bupdate;
   myKEYS.l_bdelay        = 0.0;
   myKEYS.l_bskip         =   0;
   myKEYS.l_bupdate       = 0.0;
   ykeys__loop_calc ();
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YKEYS   yLOG_complex ("timing"    , "%10ds, %10dn, %10db, %10dt, %10de, %10du, %10dr, %8.6f", myKEYS.l_secs, myKEYS.l_nsec, myKEYS.l_beg, myKEYS.l_exp, myKEYS.l_end, myKEYS.l_used, myKEYS.l_sleep, s_pct);
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
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_complex ("args"      , "%3d, %c, %c, %c blocking", a_key, ychrvisible (a_key), a_draw, myKEYS.l_blocking);
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
   DEBUG_YKEYS   yLOG_complex ("counts"    , "%6dd, %6dk, %6di", x_draws, myKEYS.l_keys, x_idles);
   /*---(sleeping)-----------------------*/
   if (myKEYS.l_blocking != 'y') {
      x_dur.tv_sec  = myKEYS.l_sleep / NSEC;
      x_dur.tv_nsec = myKEYS.l_sleep % NSEC;
      DEBUG_YKEYS   yLOG_note    ("nano-sleeping");
      nanosleep      (&x_dur, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
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


