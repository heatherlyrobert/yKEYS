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
   strlcpy (myKEYS.h_every, "", LEN_HUGE);
   strlcpy (myKEYS.h_emode, "", LEN_HUGE);
   myKEYS.h_grand    = 0;
   /*---(logs)---------------------------*/
   myKEYS.h_logkeys  = 'y';
   strlcpy (myKEYS.h_log  , "", LEN_FULL);
   strlcpy (myKEYS.h_mode , "", LEN_FULL);
   strlcpy (myKEYS.h_multi, "", LEN_FULL);
   strlcpy (myKEYS.h_errs , "", LEN_FULL);
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
   char        x_off       = LEN_HUGE / 2;
   char        t           [LEN_HUGE];
   /*---(log)----------------------------*/
   strlcpy (t, myKEYS.h_every + x_off, LEN_HUGE);
   strlcpy (myKEYS.h_every, t        , LEN_HUGE);
   /*---(mode)---------------------------*/
   strlcpy (t, myKEYS.h_emode + x_off, LEN_HUGE);
   strlcpy (myKEYS.h_emode, t        , LEN_HUGE);
   /*---(position)-----------------------*/
   myKEYS.h_grand -= x_off;
   /*---(complete)-----------------------*/
   return 0;
}

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
   strlcpy (t, myKEYS.h_log   + x_off, LEN_FULL);
   strlcpy (myKEYS.h_log  , t        , LEN_FULL);
   /*---(mode)---------------------------*/
   DEBUG_KEYS   yLOG_snote   ("mode");
   strlcpy (t, myKEYS.h_mode  + x_off, LEN_FULL);
   strlcpy (myKEYS.h_mode , t        , LEN_FULL);
   /*---(error)--------------------------*/
   DEBUG_KEYS   yLOG_snote   ("error");
   strlcpy (t, myKEYS.h_errs  + x_off, LEN_FULL);
   strlcpy (myKEYS.h_errs, t         , LEN_FULL);
   /*---(multi)--------------------------*/
   DEBUG_KEYS   yLOG_snote   ("multi");
   strlcpy (t, myKEYS.h_multi + x_off, LEN_FULL);
   strlcpy (myKEYS.h_multi, t        , LEN_FULL);
   /*---(position)-----------------------*/
   myKEYS.h_total -= x_off;
   myKEYS.h_curr  -= x_off;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
ykeys__multi            (int a_pos)
{
   char        x_mode      =  ' ';
   /*---(defense)------------------------*/
   if (a_pos < 0 || a_pos >  myKEYS.h_total)                             return 0;
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

char         /*-> tbd --------------------------------[ ------ [gz.420.121.11]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
yKEYS_logger            (uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   uchar       x_key       =    0;
   uchar       x_mode      =    0;
   char        x_multi     =  '-';
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_KEYS   yLOG_sint    (a_key);
   /*---(null key)-----------------------*/
   --rce;  if (a_key == 0) {
      DEBUG_KEYS   yLOG_snote   ("null/noop, zero recording");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   x_key  = chrvisible (a_key);
   DEBUG_KEYS   yLOG_schar   (x_key);
   x_mode = yMODE_curr ();
   DEBUG_KEYS   yLOG_schar   (x_mode);
   /*---(every)--------------------------*/
   DEBUG_KEYS   yLOG_snote   ("every logged");
   myKEYS.h_every [myKEYS.h_grand    ] = x_key;
   myKEYS.h_every [myKEYS.h_grand + 1] = 0;
   myKEYS.h_emode [myKEYS.h_grand    ] = x_mode;
   myKEYS.h_emode [myKEYS.h_grand + 1] = 0;
   ++(myKEYS.h_grand);
   DEBUG_KEYS   yLOG_svalue  ("grand"     , myKEYS.h_grand);
   /*---(TAIL -- check roll)-------------*/
   if (myKEYS.h_grand >= LEN_HUGE - 2)  ykeys__roll_every ();
   /*---(check logging)------------------*/
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_logkeys);
   --rce;  if (myKEYS.h_logkeys != 'y') {
      DEBUG_KEYS   yLOG_snote   ("NO recording");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_total);
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_curr);
   --rce;  if (myKEYS.h_curr < myKEYS.h_total) {
      DEBUG_KEYS   yLOG_snote   ("key already processed");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_schar   (yMACRO_exe_mode ());
   --rce;  IF_MACRO_PLAYING  {
      DEBUG_KEYS   yLOG_snote   ("do not record running macros");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_used);
   /*> if (myKEYS.h_used == 'y') {                                                    <* 
    *>    DEBUG_KEYS   yLOG_snote   ("key already processed");                        <* 
    *>    DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   DEBUG_KEYS   yLOG_snote   ("record");
   /*---(mode)---------------------------*/
   DEBUG_KEYS   yLOG_schar   (x_mode);
   myKEYS.h_mode  [myKEYS.h_total]     = x_mode;
   myKEYS.h_mode  [myKEYS.h_total + 1] = 0;
   /*---(key)----------------------------*/
   DEBUG_KEYS   yLOG_schar   (x_key);
   myKEYS.h_log   [myKEYS.h_total]     = x_key;
   myKEYS.h_log   [myKEYS.h_total + 1] = 0;
   /*---(error)--------------------------*/
   DEBUG_KEYS   yLOG_schar   ('-');
   if (myKEYS.h_locked != 'y')  myKEYS.h_errs [myKEYS.h_total]     = '-';
   else                         myKEYS.h_errs [myKEYS.h_total]     = '╖';
   myKEYS.h_errs [myKEYS.h_total + 1] = 0;
   /*---(multi)--------------------------*/
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
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_multi [myKEYS.h_total]);
   myKEYS.h_multi [myKEYS.h_total + 1] = 0;
   /*---(mark unused)--------------------*/
   myKEYS.h_used = '-';
   /*---(update count)-------------------*/
   ++(myKEYS.h_all);
   myKEYS.h_curr = myKEYS.h_total;
   ++(myKEYS.h_total);
   DEBUG_KEYS   yLOG_svalue  ("all"       , myKEYS.h_all);
   DEBUG_KEYS   yLOG_svalue  ("total"     , myKEYS.h_total);
   DEBUG_KEYS   yLOG_svalue  ("curr"      , myKEYS.h_curr );
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   /*---(TAIL -- check roll)-------------*/
   if (myKEYS.h_total >= LEN_FULL - 2)  ykeys__roll ();
   /*---(TAIL -- check recording)--------*/
   IF_MACRO_RECORDING {
      yMACRO_rec_key (x_key);
   }
   /*---(complete)-----------------------*/
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
         myKEYS.h_errs  [myKEYS.h_curr] = YSTR_RULER [a];
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
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_KEYS   yLOG_sint    (myKEYS.h_total);
   /*---(basic defense)------------------*/
   if (myKEYS.h_total < 2) {
      DEBUG_KEYS   yLOG_snote   ("too few keys, unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   /*---(prepare)------------------------*/
   c3 = myKEYS.h_log   [myKEYS.h_total - 2];
   m3 = myKEYS.h_multi [myKEYS.h_total - 2];
   c4 = myKEYS.h_log   [myKEYS.h_total - 1];
   m4 = myKEYS.h_multi [myKEYS.h_total - 1];
   /*---(filter)-------------------------*/
   DEBUG_KEYS   yLOG_sint    (m3);
   if (strchr ("ps-", m3) == NULL) {
      DEBUG_KEYS   yLOG_snote   ("m3 is weird, unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_KEYS   yLOG_sint    (m4);
   if (strchr ("ps-", m4) == NULL) {
      DEBUG_KEYS   yLOG_snote   ("m4 is weird, unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   if (m3 == 's' && m4 == '-') {
      DEBUG_KEYS   yLOG_snote   ("coming off combo, obviously unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   if (m4 == 'p') {
      DEBUG_KEYS   yLOG_snote   ("starting combo, obviously unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_KEYS   yLOG_sint    (c3);
   if (c3 == G_CHAR_SPACE) {
      DEBUG_KEYS   yLOG_snote   ("c3 is space, so unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
      return 1;
   }
   DEBUG_KEYS   yLOG_sint    (c4);
   if (c4 == G_CHAR_SPACE) {
      DEBUG_KEYS   yLOG_snote   ("c4 is space, so unique");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
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
   DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, 1);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      status functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

int   yKEYS_count      (void) { return myKEYS.h_total; }
int   yKEYS_position   (void) { return myKEYS.h_curr; }
uchar yKEYS_current    (void) { if (myKEYS.h_curr < 0 || myKEYS.h_curr >= myKEYS.h_total)   return 0; return myKEYS.h_log [myKEYS.h_curr]; }

char
yKEYS_oldkeys           (void)
{
   if (myKEYS.h_curr < myKEYS.h_total - 1)  return 1;
   if (myKEYS.h_curr < myKEYS.h_total)      return 2;
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
 *  -- yMODE processes no input until ее received
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
 *  -- checks for last two characters to be ее in input stream
 *  -- single е is common, or е separated by other characters
 *  -- double е is easy to type, but uncommon enough to be unlock
 *
 *
 */

char
yKEYS_set_error         (void)
{
   if (myKEYS.h_total > 0) {
      myKEYS.h_errs [myKEYS.h_total - 1] = 'E';
      yKEYS_repeat_reset ();
      ++(myKEYS.h_errors);
   }
   return 0;
}

char
yKEYS_set_lock          (void)
{
   if (myKEYS.h_total > 0) { 
      myKEYS.h_errs [myKEYS.h_total - 1] = '╧';
      yKEYS_lock ();
      yKEYS_repeat_reset ();
      ++(myKEYS.h_errors);
   }
   return 0;
}

char
yKEYS_set_warning       (void)
{  /* set if not already set */
   if (myKEYS.h_total > 0 && myKEYS.h_errs [myKEYS.h_total - 1] == '-') {
      myKEYS.h_errs [myKEYS.h_total - 1] = 'w';
      ++(myKEYS.h_warnings);
   }
   return 0;
}

char
yKEYS_set_skip          (void)
{  /* set if not already set */
   if (myKEYS.h_total > 0 && myKEYS.h_errs [myKEYS.h_total - 1] == G_CHAR_SPACE) {
      myKEYS.h_errs [myKEYS.h_total - 1] = G_CHAR_SPACE;
      ++(myKEYS.h_skips);
   }
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
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   /*---(quick-out)----------------------*/
   x_lock = yKEYS_is_locked ();
   DEBUG_KEYS   yLOG_value   ("x_lock"    , x_lock);
   if (!x_lock) {
      DEBUG_KEYS   yLOG_snote   ("key handling not locked");
      DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   *a_key = 1;
   /*---(enough keys)--------------------*/
   DEBUG_KEYS   yLOG_svalue  ("total"     , myKEYS.h_total);
   --rce;  if (myKEYS.h_total < 2) {
      DEBUG_KEYS   yLOG_snote   ("not ready to unlock, skipping");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(current escape)-----------------*/
   x_ch = myKEYS.h_log [myKEYS.h_total - 1];
   DEBUG_KEYS   yLOG_schar   (x_ch);
   --rce;  if (x_ch != G_CHAR_ESCAPE) {
      DEBUG_KEYS   yLOG_snote   ("current key not е, skipping");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(previous escape)----------------*/
   x_ch = myKEYS.h_log [myKEYS.h_total - 2];
   DEBUG_KEYS   yLOG_schar   (x_ch);
   --rce;  if (x_ch != G_CHAR_ESCAPE) {
      DEBUG_KEYS   yLOG_snote   ("previous key not е, skipping");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(during lock-down)---------------*/
   x_ch = myKEYS.h_errs [myKEYS.h_total - 2];
   DEBUG_KEYS   yLOG_schar   (x_ch);
   --rce;  if (x_ch != G_CHAR_SPACE) {
      DEBUG_KEYS   yLOG_snote   ("previous key not during lock-down, skipping");
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(unlock)-------------------------*/
   myKEYS.h_errs [myKEYS.h_total - 1] = '╧';
   yKEYS_unlock ();
   DEBUG_KEYS   yLOG_snote   ("received ее, unlocking");
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
yKEYS_lock              (void)
{
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_locked);
   myKEYS.h_locked = 'y';
   DEBUG_KEYS   yLOG_schar   (myKEYS.h_locked);
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
}

char yKEYS_unlock            (void)      { myKEYS.h_locked = '-'; }

char
yKEYS_is_error          (void)
{
   if (myKEYS.h_total > 0) {
      if (myKEYS.h_errs [myKEYS.h_total - 1] == 'E') return 1;
      if (myKEYS.h_locked == 'y')             return 1;
   }
   return 0;
}

char
yKEYS_is_locked         (void)
{
   if (myKEYS.h_locked == 'y')  return 1;
   return 0;
}


