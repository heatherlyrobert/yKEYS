/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


char
ykeys_group_reset       (void)
{
   int         i           =   0;
   myKEYS.r_level = 0;
   for (i = 0; i < LEN_LABEL; ++i) {
      myKEYS.r_reps  [i]  = -1;
      myKEYS.r_beg   [i]  = -1;
      myKEYS.r_end   [i]  = -1;
      myKEYS.r_macro [i]  = '-';
   }
   return 0;
}

char
ykeys_group_analyze     (void)
{
}


char
yKEYS_group_beg         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =    0;
   int         r           =    0;
   /*---(defense)------------------------*/
   if (myKEYS.r_level >= LEN_LABEL)  return 0;
   /*> if (myKEYS.r_count <= 0)  return 0;                                            <*/
   /*---(populate new level)-------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   n = ++(myKEYS.r_level);
   DEBUG_KEYS   yLOG_sint    (n);
   IF_MACRO_PLAYING {
      DEBUG_KEYS   yLOG_snote   ("macro");
      yMACRO_exe_pos (&(myKEYS.r_macro [n]), &(myKEYS.r_beg [n]));
   } else {
      DEBUG_KEYS   yLOG_snote   ("normal");
      myKEYS.r_macro [n] = '´';
      myKEYS.r_beg   [n] = yKEYS_position ();
   }
   myKEYS.r_reps [n] = myKEYS.r_count;
   DEBUG_KEYS   yLOG_sint    (myKEYS.r_reps  [n]);
   DEBUG_KEYS   yLOG_schar   (myKEYS.r_macro [n]);
   DEBUG_KEYS   yLOG_sint    (myKEYS.r_beg   [n]);
   DEBUG_KEYS   yLOG_sint    (myKEYS.r_end   [n]);
   /*---(clear normal repeat)------------*/
   yKEYS_repeat_reset ();
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yKEYS_group_end         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        n           =    0;
   char        rc          =    0;
   /*---(defense)------------------------*/
   if (myKEYS.r_level <= 0)  return 0;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   n = myKEYS.r_level;
   DEBUG_KEYS   yLOG_sint    (n);
   /*---(check for done)-----------------*/
   if (myKEYS.r_reps [n] == 0) {
      DEBUG_KEYS   yLOG_snote   ("pass thru");
      myKEYS.r_reps  [n] = -1;
      myKEYS.r_macro [n] = '-';
      myKEYS.r_beg   [n] = -1;
      myKEYS.r_end   [n] = -1;
      n = --(myKEYS.r_level);
      DEBUG_KEYS   yLOG_sint    (n);
      rc = 0;
   }
   /*---(return to beginning)------------*/
   else if (myKEYS.r_reps [n] > 0) {
      /*---(mark end)--------------------*/
      if (myKEYS.r_end [n] < 0) {
         IF_MACRO_PLAYING {
            DEBUG_KEYS   yLOG_snote   ("mark end macro");
            yMACRO_exe_pos (NULL, &(myKEYS.r_end [n]));
         } else {
            DEBUG_KEYS   yLOG_snote   ("mark end normal");
            myKEYS.r_end   [n] = yKEYS_position ();
         }
         DEBUG_KEYS   yLOG_sint    (myKEYS.r_end [n]);
      }
      /*---(update)----------------------*/
      DEBUG_KEYS   yLOG_snote   ("next");
      if (myKEYS.r_macro [n] == (uchar) '´')  yKEYS_repos       (myKEYS.r_beg  [n]);
      else                                    yMACRO_exe_repos  (myKEYS.r_beg  [n]);
      --(myKEYS.r_reps [n]);
      DEBUG_KEYS   yLOG_sint    (myKEYS.r_reps  [n]);
      DEBUG_KEYS   yLOG_schar   (myKEYS.r_macro [n]);
      DEBUG_KEYS   yLOG_sint    (myKEYS.r_beg   [n]);
      DEBUG_KEYS   yLOG_sint    (myKEYS.r_end   [n]);
      rc = 1;
      /*---(done)------------------------*/
   }
   /*---(check for done)-----------------*/
   /*> if (myKEYS.r_reps [n] <  0) {                                                  <* 
    *>    DEBUG_KEYS   yLOG_snote   ("set done");                                     <* 
    *>    myKEYS.r_reps  [n] = -1;                                                    <* 
    *>    myKEYS.r_macro [n] = '-';                                                   <* 
    *>    myKEYS.r_beg   [n] = -1;                                                    <* 
    *>    n = --(myKEYS.r_level);                                                     <* 
    *>    DEBUG_KEYS   yLOG_sint    (n);                                              <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
ykeys_group_check_end   (void)
{
   char        rc          =    0;
   short       x_end       =    0;
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   IF_MACRO_PLAYING {
      yMACRO_exe_pos (NULL, &(x_end));
   } else {
      x_end = yKEYS_position ();
   }
   DEBUG_KEYS   yLOG_value   ("x_end"     , x_end);
   DEBUG_KEYS   yLOG_value   ("r_level"   , myKEYS.r_level);
   if (myKEYS.r_level <= 0) {
      DEBUG_KEYS   yLOG_note    ("no groups open");
      DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_KEYS   yLOG_value   ("r_end"     , myKEYS.r_end [myKEYS.r_level]);
   if (myKEYS.r_end [myKEYS.r_level] == x_end) {
      DEBUG_KEYS   yLOG_note    ("found it");
      yKEYS_group_end ();
      DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   DEBUG_KEYS   yLOG_note    ("top group does not match");
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_group_hmode       (uchar a_major, uchar a_minor)
{
   char        rc          =    0;
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_char    ("yMODE_curr", yMODE_curr ());
   DEBUG_KEYS   yLOG_info    ("GROUPING"  , MODES_GROUPING);
   if (strchr (MODES_GROUPING, yMODE_curr ()) == NULL) {
      DEBUG_KEYS   yLOG_note    ("can not process grouping in this mode");
      DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_KEYS   yLOG_char    ("a_minor"   , a_minor);
   switch (a_minor) {
   case '(' :
      DEBUG_KEYS   yLOG_note    ("begin group, handle now");
      rc = yKEYS_group_beg ();
      DEBUG_KEYS   yLOG_value   ("logger"    , rc);
      rc = 1;
      break;
   case ')' :
      DEBUG_KEYS   yLOG_note    ("end group, handle in main");
      rc = yKEYS_group_end ();
      if (rc > 0)  yKEYS_logger ('('); /* must log here or miss token */
      rc = 1;
      break;
   default  :
      DEBUG_KEYS   yLOG_note    ("no match found");
      break;
   }
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

