/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



const tSPEED g_speed_info [MAX_SPEED] = {
   { "-50.0x"    , "blur"             ,    -50.00 },
   { "-20.0x"    , "super fast"       ,    -20.00 },
   { "-10.0x"    , "very fast"        ,    -10.00 },
   { "-5.00x"    , "faster"           ,     -5.00 },
   { "-2.00x"    , "double"           ,     -2.00 },
   { "-1.00x"    , "normal"           ,     -1.00 },
   { "-0.75x"    , "three-fourth"     ,     -0.75 },
   { "-0.50x"    , "half"             ,     -0.50 },
   { "-0.25x"    , "quarter"          ,     -0.25 },
   { "-0.10x"    , "slow"             ,     -0.10 },
   { "-0.05x"    , "super slow"       ,     -0.05 },
   { "-0.02x"    , "ultra slow"       ,     -0.02 },
   { "+0.00x"    , "stopped"          ,      0.00 },
   { "+0.02x"    , "ultra slow"       ,      0.02 },
   { "+0.05x"    , "super slow"       ,      0.05 },
   { "+0.10x"    , "slow"             ,      0.10 },
   { "+0.25x"    , "quarter"          ,      0.25 },
   { "+0.50x"    , "half"             ,      0.50 },
   { "+0.75x"    , "three-fourth"     ,      0.75 },
   { "+1.00x"    , "normal"           ,      1.00 },
   { "+2.00x"    , "double"           ,      2.00 },
   { "+5.00x"    , "faster"           ,      5.00 },
   { "+10.0x"    , "very fast"        ,     10.00 },
   { "+20.0x"    , "super fast"       ,     20.00 },
   { "+50.0x"    , "blur"             ,     50.00 },
   { "---"       , "end-of-list"      ,      0.00 },
};
static char    s_max      =  0;
static char    s_def      =  0;

char
ykeys_speed_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   s_max =  0;
   s_def =  0;
   for (i = 0; i < MAX_SCALE; ++i) {
      if (strcmp (g_speed_info [i].terse, "---"   ) == 0)  break;
      if (strcmp (g_speed_info [i].terse, "+0.00x") == 0)  s_def = i;
      ++s_max;
   }
   DEBUG_YKEYS   yLOG_value   ("s_max"     , s_max);
   DEBUG_YKEYS   yLOG_complex ("s_def"     , "%3d, %s", s_def, g_speed_info [s_def].desc);
   myKEYS.p_speed    = 0;
   yKEYS_progress_speed ("0", NULL, NULL, NULL);
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ykeys_speed             (uchar a_mode, uchar *a_speed)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_speed     =    0;
   char        rc          =    0;
   char        x_prefix    =  ' ';
   int         i           =    0;
   char        x_index     =   -1;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(types)--------------------------*/
   DEBUG_YKEYS   yLOG_char    ("a_mode"    , a_mode);
   /*---(types)--------------------------*/
   --rce;  switch (a_mode) {
   case MODE_PROGRESS :
      x_speed = myKEYS.p_speed;
      break;
   default            :
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(assign prefix)------------------*/
   DEBUG_YKEYS   yLOG_point   ("a_speed"   , a_speed);
   if (a_speed == NULL || a_speed [0] == '\0') {
      DEBUG_YKEYS   yLOG_note    ("null/empty speed request");
      x_prefix = '=';
      rc = -1;
   } else {
      DEBUG_YKEYS   yLOG_info    ("a_speed"   , a_speed);
      x_prefix = a_speed [0];
   }
   DEBUG_YKEYS   yLOG_value   ("x_prefix"  , x_prefix);
   /*---(find entry in table)------------*/
   switch (x_prefix) {
   case '0' :
      x_index = s_def;
      break;
   case '=' :
      x_index = x_speed;
      break;
   case '>' :
      if (x_speed <  s_max - 1)  x_index = ++x_speed;
      else {
         x_index = s_max - 1;
         rc      = -3;
      }
      break;
   case '<' :
      if (x_speed >  0    )  x_index = --x_speed;
      else {
         x_index = 0;
         rc      = -4;
      }
      break;
   default  :
      for (i = 0; i <= s_max; ++i) {
         if (strcmp (g_speed_info [i].terse, a_speed) != 0)  continue;
         x_index = i;
         break;
      }
      if (x_index == -1) {
         x_index = x_speed;
         rc      = -2;
      }
      break;
   }
   DEBUG_YKEYS   yLOG_value   ("x_index"   , x_index);
   /*---(set key values)-----------------*/
   switch (a_mode) {
   case MODE_PROGRESS :
      myKEYS.p_speed = x_index;
      break;
   }
   /*---(update looping)-----------------*/
   ykeys__loop_calc   ();
   if (x_speed == x_index)  myKEYS.p_redraw = '-';
   DEBUG_YKEYS   yLOG_char    ("p_redraw"  , myKEYS.p_redraw);
   /*---(complete)-----------------------*/
   return rc;
}

char
yKEYS_progress_speed    (uchar *a_speed, uchar *a_terse, uchar *a_desc, float *a_unit)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(set)----------------------------*/
   rc = ykeys_speed  (MODE_PROGRESS, a_speed);
   /*---(trouble)------------------------*/
   if (rc < 0 || myKEYS.p_speed < 0 || myKEYS.p_speed > s_max) {
      if (a_terse  != NULL)  strlcpy (a_terse, "", LEN_TERSE);
      if (a_desc   != NULL)  strlcpy (a_desc , "", LEN_FULL);
      if (a_unit   != NULL)  *a_unit  = 0.0;
      return -1;
   }
   /*---(trouble)------------------------*/
   if (a_terse  != NULL)  strlcpy (a_terse, g_speed_info [myKEYS.p_speed].terse, LEN_TERSE);
   if (a_desc   != NULL)  strlcpy (a_desc , g_speed_info [myKEYS.p_speed].desc , LEN_FULL);
   if (a_unit   != NULL)  *a_unit  = g_speed_info [myKEYS.p_speed].speed;
   /*---(complete)-----------------------*/
   return 0;
}



