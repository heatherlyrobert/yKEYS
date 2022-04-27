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
   /*---(every)--------------------------*/
   strlcpy (myKEYS.e_log  , "", LEN_HUGE);
   strlcpy (myKEYS.e_mode , "", LEN_HUGE);
   strlcpy (myKEYS.e_multi, "", LEN_HUGE);
   strlcpy (myKEYS.e_error, "", LEN_HUGE);
   strlcpy (myKEYS.e_status, "", LEN_HUGE);
   myKEYS.e_all      = 0;
   myKEYS.e_total    = 0;
   /*---(logs)---------------------------*/
   myKEYS.h_logkeys  = 'y';
   strlcpy (myKEYS.h_log  , "", LEN_FULL);
   strlcpy (myKEYS.h_mode , "", LEN_FULL);
   strlcpy (myKEYS.h_multi, "", LEN_FULL);
   strlcpy (myKEYS.h_error , "", LEN_FULL);
   myKEYS.h_locked   = '-';
   /*---(positions)----------------------*/
   myKEYS.h_all      = 0;
   myKEYS.h_total    = 0;
   myKEYS.h_curr     = 0;
   myKEYS.h_used     = '-';
   /*---(errors)-------------------------*/
   myKEYS.h_errors   = 0;
   myKEYS.h_warnings = 0;
   myKEYS.h_skips    = 0;
   /*---(counters)-----------------------*/
   myKEYS.h_acks     = 0;
   myKEYS.h_spaces   = 0;
   myKEYS.h_noops    = 0;
   myKEYS.h_combos   = 0;
   /*---(grouping)-----------------------*/
   myKEYS.h_open     = 0;
   myKEYS.h_close    = 0;
   myKEYS.h_balanced = 'y';
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    logging and history                       ----===*/
/*====================------------------------------------====================*/
static void  o___HISTORY_________o () { return; }

char
ykeys__roll_every       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_off       = LEN_HUGE / 2;
   char        t           [LEN_HUGE];
   /*---(log)----------------------------*/
   strlcpy (t, myKEYS.e_log    + x_off, LEN_HUGE);
   strlcpy (myKEYS.e_log  , t         , LEN_HUGE);
   /*---(mode)---------------------------*/
   strlcpy (t, myKEYS.e_mode   + x_off, LEN_HUGE);
   strlcpy (myKEYS.e_mode , t         , LEN_HUGE);
   /*---(error)--------------------------*/
   strlcpy (t, myKEYS.e_error  + x_off, LEN_HUGE);
   strlcpy (myKEYS.e_error, t         , LEN_HUGE);
   /*---(multi)--------------------------*/
   strlcpy (t, myKEYS.e_multi  + x_off, LEN_HUGE);
   strlcpy (myKEYS.e_multi, t         , LEN_HUGE);
   /*---(status)-------------------------*/
   strlcpy (t, myKEYS.e_status + x_off, LEN_HUGE);
   strlcpy (myKEYS.e_status, t        , LEN_HUGE);
   /*---(position)-----------------------*/
   myKEYS.e_total -= x_off;
   /*---(complete)-----------------------*/
   return 0;
}

char
ykeys__roll             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_off       = LEN_FULL / 2;
   char        t           [LEN_FULL];
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(log)----------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("log");
   strlcpy (t, myKEYS.h_log   + x_off, LEN_FULL);
   strlcpy (myKEYS.h_log  , t        , LEN_FULL);
   /*---(mode)---------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("mode");
   strlcpy (t, myKEYS.h_mode  + x_off, LEN_FULL);
   strlcpy (myKEYS.h_mode , t        , LEN_FULL);
   /*---(error)--------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("error");
   strlcpy (t, myKEYS.h_error  + x_off, LEN_FULL);
   strlcpy (myKEYS.h_error, t         , LEN_FULL);
   /*---(multi)--------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("multi");
   strlcpy (t, myKEYS.h_multi + x_off, LEN_FULL);
   strlcpy (myKEYS.h_multi, t        , LEN_FULL);
   /*---(position)-----------------------*/
   myKEYS.h_total -= x_off;
   myKEYS.h_curr  -= x_off;
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ykeys__multi_every      (int a_pos)
{
   char        x_mode      =  ' ';
   /*---(defense)------------------------*/
   if (a_pos < 0 || a_pos >  myKEYS.e_total)                       return 0;
   if (myKEYS.e_log [a_pos] == G_KEY_NULL )                        return 0;
   if (myKEYS.e_log [a_pos] == G_KEY_SPACE)                        return 0;
   if (myKEYS.e_log [a_pos] == G_CHAR_SPACE)                       return 0;
   /*---(key for mode)-------------------*/
   x_mode = myKEYS.e_mode [a_pos];
   if (a_pos > 0 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.e_mode [a_pos - 1];
   if (a_pos > 1 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.e_mode [a_pos - 2];
   if (a_pos > 2 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.e_mode [a_pos - 3];
   if (a_pos > 3 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.e_mode [a_pos - 4];
   switch (x_mode) {
   case MODE_SOURCE  : case MODE_COMMAND : case MODE_SEARCH  : case SMOD_HINT  :
      if (yKEYS_is_multi_src (myKEYS.e_log [a_pos]))  return 1;
      break;
   case MODE_MAP     :
      if (yKEYS_is_multi_map (myKEYS.e_log [a_pos]))  return 1;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ykeys__multi            (int a_pos)
{
   char        x_mode      =  ' ';
   /*---(defense)------------------------*/
   if (a_pos < 0 || a_pos >  myKEYS.h_total)                       return 0;
   if (myKEYS.h_log [a_pos] == G_KEY_NULL )                        return 0;
   if (myKEYS.h_log [a_pos] == G_KEY_SPACE)                        return 0;
   if (myKEYS.h_log [a_pos] == G_CHAR_SPACE)                       return 0;
   /*---(key for mode)-------------------*/
   x_mode = myKEYS.h_mode [a_pos];
   if (a_pos > 0 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.h_mode [a_pos - 1];
   if (a_pos > 1 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.h_mode [a_pos - 2];
   if (a_pos > 2 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.h_mode [a_pos - 3];
   if (a_pos > 3 && x_mode == PMOD_REPEAT)  x_mode = myKEYS.h_mode [a_pos - 4];
   switch (x_mode) {
   case MODE_SOURCE  : case MODE_COMMAND : case MODE_SEARCH  : case SMOD_HINT  :
      if (yKEYS_is_multi_src (myKEYS.h_log [a_pos]))  return 1;
      break;
   case MODE_MAP     :
      if (yKEYS_is_multi_map (myKEYS.h_log [a_pos]))  return 1;
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ykeys__every            (uchar a_mode, uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_final     =    1;
   uchar       x_key       =  '-';
   uchar       x_multi     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_key  = chrvisible (a_key);
   /*---(mode)---------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("mode");
   DEBUG_YKEYS   yLOG_schar   (a_mode);
   myKEYS.e_mode  [myKEYS.e_total    ] = a_mode;
   myKEYS.e_mode  [myKEYS.e_total + 1] = 0;
   /*---(log)----------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("log");
   DEBUG_YKEYS   yLOG_schar   (x_key);
   myKEYS.e_log   [myKEYS.e_total    ] = x_key;
   myKEYS.e_log   [myKEYS.e_total + 1] = 0;
   /*---(multi)--------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("multi");
   x_multi = ykeys__multi_every (myKEYS.e_total);
   switch (myKEYS.e_multi [myKEYS.e_total - 1]) {
   case 'p' :
      myKEYS.e_multi [myKEYS.e_total] = 's';
      break;
   case 's' : case '-' : default  :
      if (x_multi)   myKEYS.e_multi [myKEYS.e_total] = 'p';
      else           myKEYS.e_multi [myKEYS.e_total] = '-';
      break;
   }
   DEBUG_YKEYS   yLOG_schar   (myKEYS.e_multi [myKEYS.e_total]);
   myKEYS.e_multi [myKEYS.e_total + 1] = 0;
   /*---(errors)-------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("error");
   if (myKEYS.h_locked != 'y')  myKEYS.e_error [myKEYS.e_total]     = '-';
   else                         myKEYS.e_error [myKEYS.e_total]     = '·';
   myKEYS.e_error [myKEYS.e_total + 1] = 0;
   DEBUG_YKEYS   yLOG_schar   (myKEYS.e_error [myKEYS.e_total]);
   /*---(status)-------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("status");
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_logkeys);
   --rce;  if (myKEYS.h_logkeys != 'y') {
      DEBUG_YKEYS   yLOG_snote   ("NO REC");
      myKEYS.e_status [myKEYS.e_total    ] = '·';
      myKEYS.e_status [myKEYS.e_total + 1] = 0;
      x_final = 0;
   }
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_total);
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_curr);
   --rce;  if (myKEYS.h_curr < myKEYS.h_total) {
      DEBUG_YKEYS   yLOG_snote   ("OLD KEY");
      myKEYS.e_status [myKEYS.e_total    ] = '>';
      myKEYS.e_status [myKEYS.e_total + 1] = 0;
      x_final = 0;
   }
   DEBUG_YKEYS   yLOG_schar   (yMACRO_exe_mode ());
   --rce;  IF_MACRO_PLAYING  {
      DEBUG_YKEYS   yLOG_snote   ("MACRO PLAYING");
      myKEYS.e_status [myKEYS.e_total    ] = '>';
      myKEYS.e_status [myKEYS.e_total + 1] = 0;
      x_final = 0;
   }
   if (x_final == 1) {
      DEBUG_YKEYS   yLOG_snote   ("normal");
      myKEYS.e_status [myKEYS.e_total    ] = '-';
      myKEYS.e_status [myKEYS.e_total + 1] = 0;
   }
   /*---(update count)-------------------*/
   ++(myKEYS.e_all);
   DEBUG_YKEYS   yLOG_sint    (myKEYS.e_all);
   ++(myKEYS.e_total);
   DEBUG_YKEYS   yLOG_sint    (myKEYS.e_total);
   /*---(TAIL -- check roll)-------------*/
   if (myKEYS.e_total >= LEN_HUGE - 2) {
      DEBUG_YKEYS   yLOG_snote   ("ROLL KEYS");
      ykeys__roll_every ();
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return x_final;
}

char
ykeys__normal           (uchar a_mode, uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_key       =  '-';
   uchar       x_multi     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_key  = chrvisible (a_key);
   /*---(mode)---------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("mode");
   DEBUG_YKEYS   yLOG_schar   (a_mode);
   myKEYS.h_mode  [myKEYS.h_total]     = a_mode;
   myKEYS.h_mode  [myKEYS.h_total + 1] = 0;
   /*---(log)----------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("log");
   DEBUG_YKEYS   yLOG_schar   (x_key);
   myKEYS.h_log   [myKEYS.h_total]     = x_key;
   myKEYS.h_log   [myKEYS.h_total + 1] = 0;
   /*---(multi)--------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("multi");
   x_multi = ykeys__multi (myKEYS.h_total);
   switch (myKEYS.h_multi [myKEYS.h_total - 1]) {
   case 'p' :
      myKEYS.h_multi [myKEYS.h_total] = 's';
      break;
   case 's' : case '-' : default  :
      if (x_multi) {
         myKEYS.h_multi [myKEYS.h_total] = 'p';
         ++(myKEYS.h_combos);
      } else  myKEYS.h_multi [myKEYS.h_total] = '-';
      break;
   }
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_multi [myKEYS.h_total]);
   myKEYS.h_multi [myKEYS.h_total + 1] = 0;
   /*---(errors)-------------------------*/
   DEBUG_YKEYS   yLOG_snote   ("error");
   if (myKEYS.h_locked != 'y')  myKEYS.h_error [myKEYS.h_total]     = '-';
   else                         myKEYS.h_error [myKEYS.h_total]     = '·';
   myKEYS.h_error [myKEYS.h_total + 1] = 0;
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_error [myKEYS.h_total]);
   /*---(update count)-------------------*/
   ++(myKEYS.h_all);
   DEBUG_YKEYS   yLOG_svalue  ("all"       , myKEYS.h_all);
   myKEYS.h_curr = myKEYS.h_total;
   ++(myKEYS.h_total);
   DEBUG_YKEYS   yLOG_svalue  ("total"     , myKEYS.h_total);
   DEBUG_YKEYS   yLOG_svalue  ("curr"      , myKEYS.h_curr );
   /*---(TAIL -- check roll)-------------*/
   if (myKEYS.h_total >= LEN_FULL - 2) {
      DEBUG_YKEYS   yLOG_snote   ("ROLL KEYS");
      ykeys__roll ();
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
yKEYS_logger            (uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   uchar       x_mode      =    0;
   uchar       x_key       =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_value   ("a_key"     , a_key);
   /*---(null key)-----------------------*/
   --rce;  if (a_key == 0) {
      DEBUG_YKEYS   yLOG_note    ("null/noop, zero recording");
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_mode = yMODE_curr ();
   x_key  = chrvisible (a_key);
   /*---(every)--------------------------*/
   rc = ykeys__every  (x_mode, x_key);
   DEBUG_YKEYS   yLOG_value   ("hidden"    , rc);
   if (rc == 0) {
      DEBUG_YKEYS   yLOG_note    ("keys are not for normal log or macro recording");
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   ykeys__normal (x_mode, x_key);
   /*---(mark unused)--------------------*/
   myKEYS.h_used = '-';
   /*---(check recording)----------------*/
   IF_MACRO_RECORDING {
      yMACRO_rec_key (x_key, x_mode);
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ykeys_logger_force      (uchar a_key)
{
   if (myKEYS.h_logkeys == 'y')  myKEYS.h_curr = myKEYS.h_total;
   return yKEYS_logger (a_key);
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ykeys_logstr            (char a_mode, uchar *a_keys)
{
   int         i           =    0;
   int         a           =    0;
   int         x_len       =    0;
   if (a_keys == NULL)  return 0;
   x_len = strlen (a_keys);
   for (i = 0; i < x_len; ++i) {
      ykeys_logger_force (a_keys [i]);
      if (a_mode == 'T') {
         a = myKEYS.h_curr - 1;
         myKEYS.h_mode  [myKEYS.h_curr] = YSTR_RULER [a];
         myKEYS.h_multi [myKEYS.h_curr] = YSTR_RULER [a];
         myKEYS.h_error  [myKEYS.h_curr] = YSTR_RULER [a];
      }
   }
   return 0;
}

/*> char yKEYS_handled           (void) { myKEYS.h_used = 'y'; ; return 0; }          <*/



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
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_YKEYS   yLOG_sint    (myKEYS.h_total);
   /*---(basic defense)------------------*/
   if (myKEYS.h_total < 2) {
      DEBUG_YKEYS   yLOG_snote   ("too few keys, unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   /*---(prepare)------------------------*/
   c3 = myKEYS.h_log   [myKEYS.h_total - 2];
   m3 = myKEYS.h_multi [myKEYS.h_total - 2];
   c4 = myKEYS.h_log   [myKEYS.h_total - 1];
   m4 = myKEYS.h_multi [myKEYS.h_total - 1];
   /*---(filter)-------------------------*/
   DEBUG_YKEYS   yLOG_sint    (m3);
   if (strchr ("ps-", m3) == NULL) {
      DEBUG_YKEYS   yLOG_snote   ("m3 is weird, unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_YKEYS   yLOG_sint    (m4);
   if (strchr ("ps-", m4) == NULL) {
      DEBUG_YKEYS   yLOG_snote   ("m4 is weird, unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   if (m3 == 's' && m4 == '-') {
      DEBUG_YKEYS   yLOG_snote   ("coming off combo, obviously unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   if (m4 == 'p') {
      DEBUG_YKEYS   yLOG_snote   ("starting combo, obviously unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_YKEYS   yLOG_sint    (c3);
   if (c3 == G_CHAR_SPACE) {
      DEBUG_YKEYS   yLOG_snote   ("c3 is space, so unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_YKEYS   yLOG_sint    (c4);
   if (c4 == G_CHAR_SPACE) {
      DEBUG_YKEYS   yLOG_snote   ("c4 is space, so unique");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   /*---(single)-------------------------*/
   if (m3 == '-' && m4 == '-' && c3 == c4)       return 0;
   /*---(filter)-------------------------*/
   if (myKEYS.h_total < 4)                               return 1;
   /*---(prepare)------------------------*/
   c1 = myKEYS.h_log   [myKEYS.h_total - 4];
   m1 = myKEYS.h_multi [myKEYS.h_total - 4];
   c2 = myKEYS.h_log   [myKEYS.h_total - 3];
   m2 = myKEYS.h_multi [myKEYS.h_total - 3];
   /*---(filter)-------------------------*/
   if (strchr ("ps-", m1) == NULL)               return 0;
   if (strchr ("ps-", m2) == NULL)               return 0;
   if (m1 != 'p')                                return 1;
   if (m2 != 's')                                return 1;
   /*---(double)-------------------------*/
   if (c4 == c2 && c3 == c1)                     return 0;
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, 1);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      status functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

int   yKEYS_count      (void) { return myKEYS.h_total; }
int   yKEYS_position   (void) { return myKEYS.h_curr; }

uchar
yKEYS_current           (void)
{
   if (myKEYS.h_curr < 0 || myKEYS.h_curr >= myKEYS.h_total)   return 0;
   return myKEYS.h_log [myKEYS.h_curr];
}

uchar
yKEYS_multi             (void)
{
   if (myKEYS.e_total <= 0)                         return 0;
   if (myKEYS.e_multi [myKEYS.h_total - 1] != 's')  return 0;
   return myKEYS.h_log [myKEYS.h_curr - 1];
}

char
yKEYS_is_menu           (void)
{
   if (myKEYS.e_total <= 0)       return 0;
   if (myKEYS.e_mode [myKEYS.e_total - 1] == SMOD_MENUS) return 1;
   return 0;
}

char
yKEYS_oldkeys           (void)
{
   if (myKEYS.h_curr < myKEYS.h_total - 1)  return 1;
   if (myKEYS.h_curr < myKEYS.h_total)      return 2;
   return 0;
}

char
yKEYS_every_current     (uchar *a_mode, uchar *a_curr, uchar *a_multi, uchar *a_menu, uchar *a_error, uchar *a_status)
{
   char        rce         =  -10;
   if (a_mode   != NULL)  *a_mode   = '-';
   if (a_curr   != NULL)  *a_curr   = '-';
   if (a_multi  != NULL)  *a_multi  = '-';
   if (a_menu   != NULL)  *a_menu   =   0;
   if (a_error  != NULL)  *a_error  = '-';
   if (a_status != NULL)  *a_status = '-';
   --rce;  if (myKEYS.e_total <= 0)  return rce;
   if (a_mode   != NULL)  *a_mode   = myKEYS.e_mode   [myKEYS.e_total - 1];
   if (a_curr   != NULL)  *a_curr   = myKEYS.e_log    [myKEYS.e_total - 1];
   if (a_multi  != NULL)  *a_multi  = myKEYS.e_multi  [myKEYS.e_total - 1];
   if (a_menu   != NULL) { if (myKEYS.e_mode   [myKEYS.e_total - 1] == SMOD_MENUS)  *a_menu   = 1; }
   if (a_error  != NULL)  *a_error  = myKEYS.e_error  [myKEYS.e_total - 1];
   if (a_status != NULL)  *a_status = myKEYS.e_status [myKEYS.e_total - 1];
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      action functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___ACTION__________o () { return; }

char yKEYS_logging_on  (void)      { myKEYS.h_logkeys = 'y'; return 0; }
char yKEYS_logging_off (void)      { myKEYS.h_logkeys = '-'; return 0; }

char yKEYS_repos       (int a_pos) { if (a_pos < 0 || a_pos >= myKEYS.h_total) return -1; myKEYS.h_curr = a_pos; return 0; }
char yKEYS_nextpos     (void)      { if (myKEYS.h_curr  < myKEYS.h_total) ++(myKEYS.h_curr); else return -1;  return 0; }
char yKEYS_toend       (void)      { if (myKEYS.h_total > 0) myKEYS.h_curr = myKEYS.h_total - 1; else myKEYS.h_curr = 0; return 0; } 



/*====================------------------------------------====================*/
/*===----                       error handling                         ----===*/
/*====================------------------------------------====================*/
static void  o___ERRORS__________o () { return; }

/*
 *  yKEYS_set_lock and yKEYS_set_error are explicitly set within mode
 *  handlers to make sure the take effect -- don't relay on clever return
 *  codes or message passing.
 *
 *  yKEYS_set_warning is the default of a negative return from a mode
 *  handler, if error or lock not already set.
 *
 *  yKEYS_set_lock
 *  -- something really wrong that continued typing makes notification hard
 *  -- allows a status bar or other visual notification
 *  -- yMODE processes no input until ¥¥ received
 *  -- illegal mode changes, making accepting more keys very dangerous
 *  -- repeats on complicated actions, would be deceptive
 *
 *  yKEYS_set_error
 *  -- something wrong, but not dangerous
 *  -- allows a status bar or other visual notification
 *  -- does not effect further key processing
 *  -- includes illegal keys for mode
 *  -- or, action not possible in context
 *
 *  yKEYS_set_warning
 *  -- not right, but automatically recovered/addressed
 *  -- like, navigation that bounces off beg/end
 *  -- or, no more input to process
 *
 *  if x_major has a value, it is a part of a sequence.  if a zero
 *  is returned, then time to handle repeats
 *
 *
 *  yKEYS_check_unlock
 *  -- checks for last two characters to be ¥¥ in input stream
 *  -- single ¥ is common, or ¥ separated by other characters
 *  -- double ¥ is easy to type, but uncommon enough to be unlock
 *
 *
 */

char
yKEYS_set_error         (void)
{
   /*---(every)--------------------------*/
   if (myKEYS.e_total > 0) {
      myKEYS.e_error [myKEYS.e_total - 1] = 'E';
   }
   /*---(normal)-------------------------*/
   if (myKEYS.h_total > 0) {
      myKEYS.h_error  [myKEYS.h_total - 1] = 'E';
      yKEYS_repeat_reset ();
      ++(myKEYS.h_errors);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_set_lock          (void)
{
   /*---(every)--------------------------*/
   if (myKEYS.e_total > 0) {
      myKEYS.e_error [myKEYS.e_total - 1] = 'Ï';
   }
   /*---(normal)-------------------------*/
   if (myKEYS.h_total > 0) { 
      myKEYS.h_error  [myKEYS.h_total - 1] = 'Ï';
      yKEYS_lock ();
      yKEYS_repeat_reset ();
      ++(myKEYS.h_errors);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_set_warning       (void)
{  /* set if not already set */
   /*---(every)--------------------------*/
   if (myKEYS.e_total > 0 && myKEYS.e_error [myKEYS.e_total - 1] == '-') {
      myKEYS.e_error [myKEYS.e_total - 1] = 'w';
   }
   /*---(normal)-------------------------*/
   if (myKEYS.h_total > 0 && myKEYS.h_error  [myKEYS.h_total - 1] == '-') {
      myKEYS.h_error  [myKEYS.h_total - 1] = 'w';
      ++(myKEYS.h_warnings);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_set_skip          (void)
{  /* set if not already set */
   /*---(every)--------------------------*/
   if (myKEYS.e_total > 0 && myKEYS.e_error [myKEYS.e_total - 1] == G_CHAR_SPACE) {
      myKEYS.e_error [myKEYS.e_total - 1] = G_CHAR_SPACE;
   }
   /*---(normal)-------------------------*/
   if (myKEYS.h_total > 0 && myKEYS.h_error  [myKEYS.h_total - 1] == G_CHAR_SPACE) {
      myKEYS.h_error  [myKEYS.h_total - 1] = G_CHAR_SPACE;
      ++(myKEYS.h_skips);
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_check_unlock      (uchar *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_lock      =    0;
   uchar       x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(quick-out)----------------------*/
   x_lock = yKEYS_is_locked ();
   DEBUG_YKEYS   yLOG_value   ("x_lock"    , x_lock);
   if (!x_lock) {
      DEBUG_YKEYS   yLOG_snote   ("key handling not locked");
      DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   *a_key = 1;
   /*---(enough keys)--------------------*/
   DEBUG_YKEYS   yLOG_svalue  ("total"     , myKEYS.h_total);
   --rce;  if (myKEYS.h_total < 2) {
      DEBUG_YKEYS   yLOG_snote   ("not ready to unlock, skipping");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(current escape)-----------------*/
   x_ch = myKEYS.h_log [myKEYS.h_total - 1];
   DEBUG_YKEYS   yLOG_schar   (x_ch);
   --rce;  if (x_ch != G_CHAR_ESCAPE) {
      DEBUG_YKEYS   yLOG_snote   ("current key not ¥, skipping");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(previous escape)----------------*/
   x_ch = myKEYS.h_log [myKEYS.h_total - 2];
   DEBUG_YKEYS   yLOG_schar   (x_ch);
   --rce;  if (x_ch != G_CHAR_ESCAPE) {
      DEBUG_YKEYS   yLOG_snote   ("previous key not ¥, skipping");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(during lock-down)---------------*/
   x_ch = myKEYS.h_error [myKEYS.h_total - 2];
   DEBUG_YKEYS   yLOG_schar   (x_ch);
   --rce;  if (x_ch != G_CHAR_SPACE) {
      DEBUG_YKEYS   yLOG_snote   ("previous key not during lock-down, skipping");
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(unlock)-------------------------*/
   myKEYS.h_error [myKEYS.h_total - 1] = 'Ï';
   yKEYS_unlock ();
   DEBUG_YKEYS   yLOG_snote   ("received ¥¥, unlocking");
   /*---(exit menu)----------------------*/
   if (yKEYS_is_menu ()) {
      DEBUG_YKEYS   yLOG_snote   ("get out of menus");
      yMODE_exit ();
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
yKEYS_lock              (void)
{
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_locked);
   myKEYS.h_locked = 'y';
   DEBUG_YKEYS   yLOG_schar   (myKEYS.h_locked);
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
}

char yKEYS_unlock            (void)      { myKEYS.h_locked = '-'; }

char
yKEYS_is_error          (void)
{
   if (myKEYS.h_total > 0) {
      if (myKEYS.h_error [myKEYS.h_total - 1] == 'E') return 1;
      if (myKEYS.h_locked == 'y')                    return 1;
   }
   return 0;
}

char
yKEYS_is_locked         (void)
{
   if (myKEYS.h_locked == 'y')  return 1;
   return 0;
}


