/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
ykeys_logger_init       (void)
{
   strlcpy (g_log  , "", LEN_FULL);
   strlcpy (g_mode , "", LEN_FULL);
   strlcpy (g_multi, "", LEN_FULL);
   strlcpy (g_errs, "", LEN_FULL);
   g_all   = 0;
   g_total = 0;
   g_curr  = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    logging and history                       ----===*/
/*====================------------------------------------====================*/
static void  o___HISTORY_________o () { return; }

char
ykeys__roll             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_off       = LEN_FULL / 2;
   char        t           [LEN_FULL];
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   /*---(log)----------------------------*/
   DEBUG_KEYS   yLOG_snote   ("log");
   strlcpy (t, g_log   + x_off, LEN_FULL);
   strlcpy (g_log  , t        , LEN_FULL);
   /*---(mode)---------------------------*/
   DEBUG_KEYS   yLOG_snote   ("mode");
   strlcpy (t, g_mode  + x_off, LEN_FULL);
   strlcpy (g_mode , t        , LEN_FULL);
   /*---(error)--------------------------*/
   DEBUG_KEYS   yLOG_snote   ("error");
   strlcpy (t, g_errs + x_off, LEN_FULL);
   strlcpy (g_errs, t        , LEN_FULL);
   /*---(multi)--------------------------*/
   DEBUG_KEYS   yLOG_snote   ("multi");
   strlcpy (t, g_multi + x_off, LEN_FULL);
   strlcpy (g_multi, t        , LEN_FULL);
   /*---(position)-----------------------*/
   g_total -= x_off;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ykeys__multi            (int a_pos)
{
   char        x_mode      =  ' ';
   /*---(defense)------------------------*/
   if (a_pos < 0 || a_pos >  g_total)                             return 0;
   if (g_log [a_pos] == G_KEY_NULL )                        return 0;
   if (g_log [a_pos] == G_KEY_SPACE)                        return 0;
   if (g_log [a_pos] == G_CHAR_SPACE)                       return 0;
   /*---(key for mode)-------------------*/
   x_mode = g_mode [a_pos];
   if (a_pos > 0 && x_mode == PMOD_REPEAT)  x_mode = g_mode [a_pos - 1];
   if (a_pos > 1 && x_mode == PMOD_REPEAT)  x_mode = g_mode [a_pos - 2];
   if (a_pos > 2 && x_mode == PMOD_REPEAT)  x_mode = g_mode [a_pos - 3];
   if (a_pos > 3 && x_mode == PMOD_REPEAT)  x_mode = g_mode [a_pos - 4];
   switch (x_mode) {
   case MODE_SOURCE  : case MODE_COMMAND : case MODE_SEARCH  : case SMOD_HINT  :
      if (strchr (g_multisrc, g_log [a_pos]) != NULL)       return 1;
      break;
   case MODE_MAP     :
      if (strchr (g_multimap, g_log [a_pos]) != NULL)       return 1;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
yKEYS_logger            (uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_key       =    0;
   int         x_multi     =  '-';
   /*---(key)----------------------------*/
   x_key = chrvisible (a_key);
   g_log   [g_total]     = x_key;
   g_log   [g_total + 1] = 0;
   /*---(mode)---------------------------*/
   g_mode  [g_total]     = yMODE_curr ();
   g_mode  [g_total + 1] = 0;
   /*---(error)--------------------------*/
   g_errs [g_total]     = '-';
   g_errs [g_total + 1] = 0;
   /*---(multi)--------------------------*/
   x_multi = ykeys__multi (g_total);
   switch (g_multi [g_total - 1]) {
   case 'p' :
      g_multi [g_total] = 's';
      break;
   case 's' : case '-' : default  :
      if (x_multi)  g_multi [g_total] = 'p';
      else          g_multi [g_total] = '-';
      break;
   }
   g_multi [g_total + 1] = 0;
   /*---(update count)-------------------*/
   ++g_all;
   g_curr = g_total;
   ++g_total;
   /*---(roll)---------------------------*/
   if (g_total >= LEN_FULL - 2)  ykeys__roll ();
   /*---(macro)--------------------------*/
   IF_MACRO_RECORDING {
      yMACRO_rec_key (x_key);
   }
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    sundo/mundo support                       ----===*/
/*====================------------------------------------====================*/
static void  o___UNDO____________o () { return; }

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
yKEYS_unique            (void)
{  /*    return 1 if not a repeat sequence, 0 if repeating   */
   /*    five mode options :    - -    - p    p s    s -    s p
   */
   /*---(locals)-----------+-----+-----+-*/
   uchar       m1, m2, m3, m4;
   uchar       c1, c2, c3, c4;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   DEBUG_LOOP   yLOG_sint    (g_total);
   /*---(basic defense)------------------*/
   if (g_total < 2) {
      DEBUG_LOOP   yLOG_snote   ("too few keys, unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   /*---(prepare)------------------------*/
   c3 = g_log   [g_total - 2];
   m3 = g_multi [g_total - 2];
   c4 = g_log   [g_total - 1];
   m4 = g_multi [g_total - 1];
   /*---(filter)-------------------------*/
   DEBUG_LOOP   yLOG_sint    (m3);
   if (strchr ("ps-", m3) == NULL) {
      DEBUG_LOOP   yLOG_snote   ("m3 is weird, unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_LOOP   yLOG_sint    (m4);
   if (strchr ("ps-", m4) == NULL) {
      DEBUG_LOOP   yLOG_snote   ("m4 is weird, unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   if (m3 == 's' && m4 == '-') {
      DEBUG_LOOP   yLOG_snote   ("coming off combo, obviously unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   if (m4 == 'p') {
      DEBUG_LOOP   yLOG_snote   ("starting combo, obviously unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_LOOP   yLOG_sint    (c3);
   if (c3 == G_CHAR_SPACE) {
      DEBUG_LOOP   yLOG_snote   ("c3 is space, so unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_LOOP   yLOG_sint    (c4);
   if (c4 == G_CHAR_SPACE) {
      DEBUG_LOOP   yLOG_snote   ("c4 is space, so unique");
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   /*---(single)-------------------------*/
   if (m3 == '-' && m4 == '-' && c3 == c4)       return 0;
   /*---(filter)-------------------------*/
   if (g_total < 4)                               return 1;
   /*---(prepare)------------------------*/
   c1 = g_log   [g_total - 4];
   m1 = g_multi [g_total - 4];
   c2 = g_log   [g_total - 3];
   m2 = g_multi [g_total - 3];
   /*---(filter)-------------------------*/
   if (strchr ("ps-", m1) == NULL)               return 0;
   if (strchr ("ps-", m2) == NULL)               return 0;
   if (m1 != 'p')                                return 1;
   if (m2 != 's')                                return 1;
   /*---(double)-------------------------*/
   if (c4 == c2 && c3 == c1)                     return 0;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, 1);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      status functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

int   yKEYS_count      (void) { return g_total; }
int   yKEYS_position   (void) { return g_curr; }
uchar yKEYS_current    (void) { if (g_curr < 0 || g_curr >= g_total)   return 0; return g_log [g_curr]; }
char  yKEYS_oldkeys    (void) { if (g_curr < g_total - 1)  return 1; return 0; }



/*====================------------------------------------====================*/
/*===----                      action functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___ACTION__________o () { return; }

char yKEYS_repos             (int a_pos) { if (a_pos < 0 || a_pos >= g_total) return -1; g_curr = a_pos; return 0;}
char yKEYS_toend             (void)      { if (g_total > 0) g_curr = g_total - 1; else g_curr = 0; return 0; } 
char yKEYS_error             (void)      { if (g_total > 0) g_errs [g_total - 1] = 'E'; return 0; }



