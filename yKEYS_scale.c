/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


/*===[[ SCALE ]]==============================================================*/
static float   s_inc      =  1;             /* increment in movement          */
static char    s_base     = ' ';            /* scale prefix for labels        */
static float   s_multi    =  1;             /* increment in movement          */
static char    s_max      =  0;
static char    s_def      =  0;

const tSCALE g_scale_info [MAX_SCALE] = {
   { 'm' , "p"  , "pico"      , "pico  (1 trillonth)"   , -12 ,             0.000000000001  },
   { 'm' , "nh-", "nano/h-"   , "nano  (300 billionth)" , -12 ,             0.0000000000032 },
   { 'm' , "nh" , "nano/h"    , "nano  (100 billionth)" , -11 ,             0.00000000001   },
   { 'm' , "nd-", "nano/d-"   , "nano  (30 billionth)"  , -11 ,             0.000000000032  },
   { 'm' , "nd" , "nano/d"    , "nano  (10 billionth)"  , -10 ,             0.0000000001    },
   { 'm' , "n-" , "nano-"     , "nano  (3 billionth)"   , -10 ,             0.00000000032   },
   { 'm' , "n"  , "nano"      , "nano  (1 billionth)"   ,  -9 ,             0.000000001     },
   { 'm' , "uh-", "micr/h-"   , "micro (300 millionth)" ,  -9 ,             0.0000000032    },
   { 'm' , "uh" , "micr/h"    , "micro (100 millionth)" ,  -8 ,             0.00000001      },
   { 'm' , "ud-", "micr/d-"   , "micro (30 millionth)"  ,  -8 ,             0.000000032     },
   { 'm' , "ud" , "micr/d"    , "micro (10 millionth)"  ,  -7 ,             0.0000001       },
   { 'm' , "u-" , "micr-"     , "micro (3 millionth)"   ,  -7 ,             0.00000032      },
   { 'm' , "u"  , "micr"      , "micro (1 millionth)"   ,  -6 ,             0.000001        },
   { 'm' , "mh-", "mill/h-"   , "milli (300 thousandth)",  -6 ,             0.0000032       },
   { 'm' , "mh" , "mill/h"    , "milli (100 thousandth)",  -5 ,             0.00001         },
   { 'm' , "md-", "mill/d-"   , "milli (30 thousandth)" ,  -5 ,             0.000032        },
   { 'm' , "md" , "mill/d"    , "milli (10 thousandth)" ,  -4 ,             0.0001          },
   { 'm' , "m-" , "mill-"     , "milli (3 thousandth)"  ,  -4 ,             0.00032         },
   { 'm' , "m"  , "mill"      , "milli (1 thousandth)"  ,  -3 ,             0.001           },
   { 'm' , "c-" , "cent-"     , "centi (3 hundredth)"   ,  -3 ,             0.0032          },
   { 'm' , "c"  , "cent"      , "centi (1 hundredth)"   ,  -2 ,             0.01            },
   { 'm' , "d-" , "deci-"     , "deci  (thirteth)"      ,  -2 ,             0.032           },
   { 'm' , "d"  , "deci"      , "deci  (tenth)"         ,  -1 ,             0.1             },
   { 'm' , "+"  , "base+"     , "norm  (three)"         ,   0 ,             3.2             },
   { 'm' , "~"  , "base"      , "norm  (one)"           ,   0 ,             1.0             },
   { 'm' , "-"  , "base+"     , "norm  (third)"         ,  -1 ,             0.32            },
   { 'm' , "D"  , "deca"      , "deca  (ten)"           ,   1 ,            10.0             },
   { 'm' , "D+" , "deca+"     , "deca  (thirty)"        ,   1 ,            32.0             },
   { 'm' , "H"  , "heka"      , "hecto (1 hundred)"     ,   2 ,           100.0             },
   { 'm' , "H+" , "heka+"     , "hecto (3 hundred)"     ,   2 ,           320.0             },
   { 'm' , "K"  , "kilo"      , "kilo  (1 thousand)"    ,   3 ,          1000.0             },
   { 'm' , "K+" , "kilo+"     , "kilo  (3 thousand)"    ,   3 ,          3200.0             },
   { 'm' , "KD" , "kilo/D"    , "kilo  (10 thousand)"   ,   4 ,         10000.0             },
   { 'm' , "KD+", "kilo/D+"   , "kilo  (30 thousand)"   ,   4 ,         32000.0             },
   { 'm' , "KH" , "kilo/H"    , "kilo  (100 thousand)"  ,   5 ,        100000.0             },
   { 'm' , "KH+", "kilo/H+"   , "kilo  (300 thousand)"  ,   5 ,        320000.0             },
   { 'm' , "M"  , "mega"      , "mega  (1 million)"     ,   6 ,       1000000.0             },
   { 'm' , "M+" , "mega+"     , "mega  (3 million)"     ,   6 ,       3200000.0             },
   { 'm' , "MD" , "mega/D"    , "mega  (10 million)"    ,   7 ,      10000000.0             },
   { 'm' , "MD+", "mega/D+"   , "mega  (30 million)"    ,   7 ,      32000000.0             },
   { 'm' , "MH" , "mega/H"    , "mega  (100 million)"   ,   8 ,     100000000.0             },
   { 'm' , "MH+", "mega/H+"   , "mega  (300 million)"   ,   8 ,     320000000.0             },
   { 'm' , "G"  , "giga"      , "giga  (1 billion)"     ,   9 ,    1000000000.0             },
   { 'm' , "G+" , "giga+"     , "giga  (3 billion)"     ,   9 ,    3200000000.0             },
   { 'm' , "GD" , "giga/D"    , "giga  (10 billion)"    ,  10 ,   10000000000.0             },
   { 'm' , "GD+", "giga/D+"   , "giga  (30 billion)"    ,  10 ,   32000000000.0             },
   { 'm' , "GH" , "giga/H"    , "giga  (100 billion)"   ,  11 ,  100000000000.0             },
   { 'm' , "GH+", "giga/H+"   , "giga  (300 billion)"   ,  11 ,  320000000000.0             },
   { 'm' , "T"  , "tera"      , "tera  (1 trillion)"    ,  12 , 1000000000000.0             },
   { 'm' , "---", "----"      , "end-of-scales"         ,   0 ,             0.0             },
};

/*> const tSCALE g_scale_info [MAX_SCALE] = {                                                        <* 
 *>    { 'm' , "T"  , "tera"      , "tera  (1 trillion)"    ,  12 , 1000000000000.0             },   <* 
 *>    { 'm' , "GH+", "giga/H+"   , "giga  (300 billion)"   ,  11 ,  320000000000.0             },   <* 
 *>    { 'm' , "GH" , "giga/H"    , "giga  (100 billion)"   ,  11 ,  100000000000.0             },   <* 
 *>    { 'm' , "GD+", "giga/D+"   , "giga  (30 billion)"    ,  10 ,   32000000000.0             },   <* 
 *>    { 'm' , "GD" , "giga/D"    , "giga  (10 billion)"    ,  10 ,   10000000000.0             },   <* 
 *>    { 'm' , "G+" , "giga+"     , "giga  (3 billion)"     ,   9 ,    3200000000.0             },   <* 
 *>    { 'm' , "G"  , "giga"      , "giga  (1 billion)"     ,   9 ,    1000000000.0             },   <* 
 *>    { 'm' , "MH+", "mega/H+"   , "mega  (300 million)"   ,   8 ,     320000000.0             },   <* 
 *>    { 'm' , "MH" , "mega/H"    , "mega  (100 million)"   ,   8 ,     100000000.0             },   <* 
 *>    { 'm' , "MD+", "mega/D+"   , "mega  (30 million)"    ,   7 ,      32000000.0             },   <* 
 *>    { 'm' , "MD" , "mega/D"    , "mega  (10 million)"    ,   7 ,      10000000.0             },   <* 
 *>    { 'm' , "M+" , "mega+"     , "mega  (3 million)"     ,   6 ,       3200000.0             },   <* 
 *>    { 'm' , "M"  , "mega"      , "mega  (1 million)"     ,   6 ,       1000000.0             },   <* 
 *>    { 'm' , "KH+", "kilo/H+"   , "kilo  (300 thousand)"  ,   5 ,        320000.0             },   <* 
 *>    { 'm' , "KH" , "kilo/H"    , "kilo  (100 thousand)"  ,   5 ,        100000.0             },   <* 
 *>    { 'm' , "KD+", "kilo/D+"   , "kilo  (30 thousand)"   ,   4 ,         32000.0             },   <* 
 *>    { 'm' , "KD" , "kilo/D"    , "kilo  (10 thousand)"   ,   4 ,         10000.0             },   <* 
 *>    { 'm' , "K+" , "kilo+"     , "kilo  (3 thousand)"    ,   3 ,          3200.0             },   <* 
 *>    { 'm' , "K"  , "kilo"      , "kilo  (1 thousand)"    ,   3 ,          1000.0             },   <* 
 *>    { 'm' , "H+" , "heka+"     , "hecto (3 hundred)"     ,   2 ,           320.0             },   <* 
 *>    { 'm' , "H"  , "heka"      , "hecto (1 hundred)"     ,   2 ,           100.0             },   <* 
 *>    { 'm' , "D+" , "deca+"     , "deca  (thirty)"        ,   1 ,            32.0             },   <* 
 *>    { 'm' , "D"  , "deca"      , "deca  (ten)"           ,   1 ,            10.0             },   <* 
 *>    { 'm' , "+"  , "base+"     , "norm  (three)"         ,   0 ,             3.2             },   <* 
 *>    { 'm' , "~"  , "base"      , "norm  (one)"           ,   0 ,             1.0             },   <* 
 *>    { 'm' , "-"  , "base+"     , "norm  (third)"         ,  -1 ,             0.32            },   <* 
 *>    { 'm' , "d"  , "deci"      , "deci  (tenth)"         ,  -1 ,             0.1             },   <* 
 *>    { 'm' , "d-" , "deci-"     , "deci  (thirteth)"      ,  -2 ,             0.032           },   <* 
 *>    { 'm' , "c"  , "cent"      , "centi (1 hundredth)"   ,  -2 ,             0.01            },   <* 
 *>    { 'm' , "c-" , "cent-"     , "centi (3 hundredth)"   ,  -3 ,             0.0032          },   <* 
 *>    { 'm' , "m"  , "mill"      , "milli (1 thousandth)"  ,  -3 ,             0.001           },   <* 
 *>    { 'm' , "m-" , "mill-"     , "milli (3 thousandth)"  ,  -4 ,             0.00032         },   <* 
 *>    { 'm' , "md" , "mill/d"    , "milli (10 thousandth)" ,  -4 ,             0.0001          },   <* 
 *>    { 'm' , "md-", "mill/d-"   , "milli (30 thousandth)" ,  -5 ,             0.000032        },   <* 
 *>    { 'm' , "mh" , "mill/h"    , "milli (100 thousandth)",  -5 ,             0.00001         },   <* 
 *>    { 'm' , "mh-", "mill/h-"   , "milli (300 thousandth)",  -6 ,             0.0000032       },   <* 
 *>    { 'm' , "u"  , "micr"      , "micro (1 millionth)"   ,  -6 ,             0.000001        },   <* 
 *>    { 'm' , "u-" , "micr-"     , "micro (3 millionth)"   ,  -7 ,             0.00000032      },   <* 
 *>    { 'm' , "ud" , "micr/d"    , "micro (10 millionth)"  ,  -7 ,             0.0000001       },   <* 
 *>    { 'm' , "ud-", "micr/d-"   , "micro (30 millionth)"  ,  -8 ,             0.000000032     },   <* 
 *>    { 'm' , "uh" , "micr/h"    , "micro (100 millionth)" ,  -8 ,             0.00000001      },   <* 
 *>    { 'm' , "uh-", "micr/h-"   , "micro (300 millionth)" ,  -9 ,             0.0000000032    },   <* 
 *>    { 'm' , "n"  , "nano"      , "nano  (1 billionth)"   ,  -9 ,             0.000000001     },   <* 
 *>    { 'm' , "n-" , "nano-"     , "nano  (3 billionth)"   , -10 ,             0.00000000032   },   <* 
 *>    { 'm' , "nd" , "nano/d"    , "nano  (10 billionth)"  , -10 ,             0.0000000001    },   <* 
 *>    { 'm' , "nd-", "nano/d-"   , "nano  (30 billionth)"  , -11 ,             0.000000000032  },   <* 
 *>    { 'm' , "nh" , "nano/h"    , "nano  (100 billionth)" , -11 ,             0.00000000001   },   <* 
 *>    { 'm' , "nh-", "nano/h-"   , "nano  (300 billionth)" , -12 ,             0.0000000000032 },   <* 
 *>    { 'm' , "p"  , "pico"      , "pico  (1 trillonth)"   , -12 ,             0.000000000001  },   <* 
 *>    { 'm' , "---", "----"      , "end-of-scales"         ,   0 ,             0.0             },   <* 
 *> };                                                                                               <*/

char
ykeys_scale_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   s_max =  0;
   s_def =  0;
   for (i = 0; i < MAX_SCALE; ++i) {
      if (strcmp (g_scale_info [i].terse, "---"   ) == 0)  break;
      if (strcmp (g_scale_info [i].terse, "~"     ) == 0)  s_def = i;
      ++s_max;
   }
   DEBUG_YKEYS   yLOG_value   ("s_max"     , s_max);
   DEBUG_YKEYS   yLOG_complex ("s_def"     , "%3d, %s", s_def, g_scale_info [s_def].desc);
   myKEYS.p_scale    = 0;
   yKEYS_progress_scale ("0", NULL, NULL, NULL, NULL, NULL);
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ykeys_scale             (uchar a_mode, uchar *a_scale)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_scale     =    0;
   char        rc          =    0;
   char        x_prefix    =  ' ';
   int         i           =    0;
   char        x_index     =   -1;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(types)--------------------------*/
   DEBUG_YKEYS   yLOG_char    ("a_mode"    , a_mode);
   --rce;  switch (a_mode) {
   case MODE_PROGRESS :
      x_scale = myKEYS.p_scale;
      break;
   default            :
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(assign prefix)------------------*/
   DEBUG_YKEYS   yLOG_point   ("a_scale"   , a_scale);
   if (a_scale == NULL || a_scale [0] == '\0') {
      DEBUG_YKEYS   yLOG_note    ("null/empty scale request");
      x_prefix = '=';
      rc = -1;
   } else {
      DEBUG_YKEYS   yLOG_info    ("a_scale"   , a_scale);
      x_prefix = a_scale [0];
   }
   DEBUG_YKEYS   yLOG_value   ("x_prefix"  , x_prefix);
   /*---(find entry in table)------------*/
   switch (x_prefix) {
   case '=' :  /* nothing to do */
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return 0;
      break;
   case '0' :
      x_index = s_def;
      break;
   case '>' :
      if (x_scale < s_max - 1)  x_index = ++x_scale;
      else {
         x_index = s_max - 1;
         rc      = -3;
      }
      break;
   case '<' :
      if (x_scale >  0    )  x_index = --x_scale;
      else {
         x_index = 0;
         rc      = -4;
      }
      break;
   default  :
      for (i = 0; i <= s_max; ++i) {
         if (strcmp (g_scale_info [i].terse, a_scale) != 0)  continue;
         x_index = i;
         break;
      }
      if (x_index == -1) {
         x_index = x_scale;
         rc      = -2;
      }
      break;
   }
   DEBUG_YKEYS   yLOG_value   ("x_index"   , x_index);
   /*---(set key values)-----------------*/
   switch (a_mode) {
   case MODE_PROGRESS : myKEYS.p_scale = x_index;   break;
   }
   /*> printf ("end : myKEYS.p_scale = %d\n", myKEYS.p_scale);                    <*/
   /*---(update looping)-----------------*/
   ykeys__loop_calc   ();
   if (x_scale == x_index)  myKEYS.p_redraw = '-';
   DEBUG_YKEYS   yLOG_char    ("p_redraw"  , myKEYS.p_redraw);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yKEYS_progress_scale    (uchar *a_scale, uchar *a_terse, uchar *a_label, uchar *a_desc, char *a_power, float *a_unit)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(set)----------------------------*/
   rc = ykeys_scale  (MODE_PROGRESS, a_scale);
   /*---(trouble)------------------------*/
   if (rc < 0 || myKEYS.p_scale < 0 || myKEYS.p_scale > s_max) {
      if (a_terse  != NULL)  strlcpy (a_terse, "", LEN_TERSE);
      if (a_label  != NULL)  strlcpy (a_label, "", LEN_LABEL);
      if (a_desc   != NULL)  strlcpy (a_desc , "", LEN_FULL);
      if (a_power  != NULL)  *a_power = 0;
      if (a_unit   != NULL)  *a_unit  = 0.0;
      return -1;
   }
   /*---(normal)-------------------------*/
   if (a_terse  != NULL)  strlcpy (a_terse, g_scale_info [myKEYS.p_scale].terse, LEN_TERSE);
   if (a_label  != NULL)  strlcpy (a_label, g_scale_info [myKEYS.p_scale].label, LEN_LABEL);
   if (a_desc   != NULL)  strlcpy (a_desc , g_scale_info [myKEYS.p_scale].desc , LEN_FULL);
   if (a_power  != NULL)  *a_power = g_scale_info [myKEYS.p_scale].power;
   if (a_unit   != NULL)  *a_unit  = g_scale_info [myKEYS.p_scale].unit;
   /*---(complete)-----------------------*/
   return 0;
}


