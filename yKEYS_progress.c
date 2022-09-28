/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



char
ykeys_progress_init     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (MODE_PROGRESS)) {
      DEBUG_YKEYS    yLOG_note    ("status is not ready for init");
      DEBUG_YKEYS    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   DEBUG_YKEYS  yLOG_note    ("globals");
   strlcpy (myKEYS.p_unit, "", LEN_TERSE);
   myKEYS.p_play   = '-';
   myKEYS.p_anchor = 's';
   myKEYS.p_adv    =  0.00;
   myKEYS.p_inc    =  0.00;
   myKEYS.p_repeat = '-';
   myKEYS.p_debug  = '-';
   myKEYS.p_redraw = '-';
   /*---(source program)-----------------*/
   DEBUG_YKEYS  yLOG_note    ("lines");
   myKEYS.p_line   =  0;
   myKEYS.p_lines  =  0;
   /*---(as read)------------------------*/
   DEBUG_YKEYS  yLOG_note    ("position");
   myKEYS.p_beg    =  0.00;
   myKEYS.p_end    =  0.00;
   myKEYS.p_len    =  0.00;
   myKEYS.p_cur    =  0.00;
   /*---(update status)------------------*/
   DEBUG_YKEYS    yLOG_note    ("update status");
   yMODE_init_set   (MODE_PROGRESS, NULL, ykeys_progress_mode);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_progress_lines    (int a_lines)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (MODE_PROGRESS)) {
      DEBUG_YMACRO   yLOG_note    ("init must complete before config");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save data)----------------------*/
   myKEYS.p_lines  = a_lines;
   DEBUG_YKEYS  yLOG_value   ("p_lines"   , myKEYS.p_lines);
   /*---(update status)------------------*/
   DEBUG_YKEYS    yLOG_note    ("update config");
   yMODE_conf_set   (MODE_PROGRESS, '1');
   /*---(complete)-----------------------*/
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_progress_length   (float a_beg, float a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS  yLOG_complex ("limits"    , "%fb, %fe", a_beg, a_end);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (MODE_PROGRESS)) {
      DEBUG_YMACRO   yLOG_note    ("init must complete before config");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save data)----------------------*/
   myKEYS.p_beg    = a_beg;
   DEBUG_YKEYS  yLOG_double  ("p_beg"     , myKEYS.p_beg);
   myKEYS.p_end    = a_end;
   DEBUG_YKEYS  yLOG_double  ("p_end"     , myKEYS.p_end);
   /*---(calc length)--------------------*/
   myKEYS.p_len    = a_end - a_beg;
   DEBUG_YKEYS  yLOG_double  ("p_len"     , myKEYS.p_len);
   myKEYS.p_cur    = a_beg;
   DEBUG_YKEYS  yLOG_double  ("p_cur"     , myKEYS.p_cur);
   /*---(update status)------------------*/
   DEBUG_YKEYS    yLOG_note    ("update config");
   yMODE_conf_set   (MODE_PROGRESS, '2');
   /*---(complete)-----------------------*/
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_progress_config   (char a_repeat, char *a_unit, char *a_scale, char *a_speed, char a_play)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (MODE_PROGRESS)) {
      DEBUG_YMACRO   yLOG_note    ("init must complete before config");
      DEBUG_YMACRO   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save data)----------------------*/
   if (a_unit  != NULL)  strlcpy (myKEYS.p_unit, a_unit, LEN_TERSE);
   if (a_scale != NULL)  yKEYS_progress_scale (a_scale, NULL, NULL, NULL, NULL, NULL);
   if (a_speed != NULL)  yKEYS_progress_speed (a_speed, NULL, NULL, NULL);
   /*---(set play and repeat)------------*/
   myKEYS.p_repeat = a_repeat;
   DEBUG_YKEYS  yLOG_char    ("p_repeat"  , myKEYS.p_repeat);
   myKEYS.p_play = a_play;
   DEBUG_YKEYS  yLOG_char    ("p_play"    , myKEYS.p_play);
   /*---(update status)------------------*/
   DEBUG_YKEYS    yLOG_note    ("update config");
   yMODE_conf_set   (MODE_PROGRESS, '3');
   /*---(complete)-----------------------*/
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_progress_cur      (float *a_len, char *a_anchor, float *a_sec, float *a_scale, float *a_inc, int *a_line)
{
   if (a_len    != NULL)  *a_len    = myKEYS.p_len;
   if (a_anchor != NULL)  *a_anchor = myKEYS.p_anchor;
   if (a_sec    != NULL)  *a_sec    = myKEYS.p_cur;
   if (a_scale  != NULL)  *a_scale  = g_scale_info [myKEYS.p_scale].unit;
   if (a_inc    != NULL)  *a_inc    = myKEYS.p_inc;
   if (a_line   != NULL)  *a_line   = myKEYS.p_line;
   return 0;
}

char         /*--> process keystrokes in progress mode ---[--------[--------]-*/
ykeys_progress_mode     (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          = 0;
   int         x_leg       = 0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS  yLOG_char    ("a_major"   , a_major);
   DEBUG_YKEYS  yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*---(defenses)-----------------------*/
   DEBUG_YKEYS  yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (MODE_PROGRESS)) {
      DEBUG_YKEYS  yLOG_note    ("not the correct mode");
      yMODE_exit  ();
      DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(nothing to do)------------------*/
   if (a_minor == G_KEY_SPACE ) {
      DEBUG_YKEYS  yLOG_note    ("space, nothing to do");
      DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(major mode changes)-------------*/
   if (a_minor == G_KEY_RETURN || a_minor == G_KEY_ESCAPE) {
      DEBUG_YKEYS  yLOG_note    ("enter/escape, leave progress mode");
      yMODE_exit  ();
      DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(single key)---------------------*/
   --rce;
   if (a_major == ' ') {
      DEBUG_YKEYS  yLOG_note    ("review single keys");
      /*---(modes)-----------------------*/
      switch (a_minor) {
      case ':' :
         DEBUG_YKEYS  yLOG_note    ("start the command mode");
         ySRC_start   (":");
         DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
         rc = 'a';
         break;
      case ';' :
         DEBUG_YKEYS  yLOG_note    ("start the hint micro-mode");
         ySRC_start   (";");
         DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
         rc = 'a';
         break;
      case '\\'     :
         DEBUG_YKEYS  yLOG_note    ("entering menu sub-mode");
         yMODE_enter  (SMOD_MENUS   );
         /*> yvikeys_menu_start  ();                                                  <*/
         DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
         return a_minor;
         break;
      case '^':
         DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
         return a_minor;
         break;
      }
      /*---(unit test data)--------------*/
      /*> if (a_minor == '#') {                                                       <* 
       *>    KINE_unitcond ();                                                        <* 
       *> }                                                                           <*/
      /*---(vertical movement)-----------*/
      if (strchr ("_KkjJ~", a_minor) != 0) {
         DEBUG_YKEYS  yLOG_note    ("handle the horizontal keys");
         DEBUG_YKEYS  yLOG_value   ("p_line"    , myKEYS.p_line);
         DEBUG_YKEYS  yLOG_value   ("p_nline"   , myKEYS.p_lines);
         switch (a_minor) {
         case '_' :  myKEYS.p_line   = 0;                     break;
         case 'K' :  myKEYS.p_line  -= 5;                     break;
         case 'k' :  myKEYS.p_line  -= 1;                     break;
         case 'j' :  myKEYS.p_line  += 1;                     break;
         case 'J' :  myKEYS.p_line  += 5;                     break;
         case '~' :  myKEYS.p_line   = myKEYS.p_lines;      break;
         }
         if (myKEYS.p_line < 0                )  myKEYS.p_line = 0;
         if (myKEYS.p_line >= myKEYS.p_lines)  myKEYS.p_line = myKEYS.p_lines - 1;
         DEBUG_YKEYS  yLOG_value   ("p_line"    , myKEYS.p_line);
      }
      /*---(zoom and retreat)------------*/
      switch (a_minor) {
      case 'i':
         yKEYS_progress_scale  ("<", NULL, NULL, NULL, NULL, NULL);
         ykeys__loop_calc ();
         myKEYS.p_redraw = 'y';
         break;
      case 'o':
         yKEYS_progress_scale  (">", NULL, NULL, NULL, NULL, NULL);
         ykeys__loop_calc ();
         myKEYS.p_redraw = 'y';
         break;
      }
      /*---(play and stop)---------------*/
      switch (a_minor) {
      case '<':
         yKEYS_progress_speed ("<", NULL, NULL, NULL);
         ykeys__loop_calc ();
         myKEYS.p_redraw = 'y';
         break;
      case '>':
         yKEYS_progress_speed (">", NULL, NULL, NULL);
         ykeys__loop_calc ();
         myKEYS.p_redraw = 'y';
         break;
      case ',':
         myKEYS.p_play = 'y';
         if (myKEYS.p_adv == 0.0)  yKEYS_progress_speed ("+1.00x", NULL, NULL, NULL);
         ykeys__loop_calc ();
         myKEYS.p_redraw = 'y';
         break;
      case '.':
         myKEYS.p_play   = '-';
         myKEYS.p_redraw = '-';
         ykeys__loop_calc ();
         break;
      }
      /*---(horizontal movement)---------*/
      if (strchr ("0HhlL$", a_minor) != 0) {
         DEBUG_YKEYS  yLOG_double  ("p_beg"     , myKEYS.p_beg);
         DEBUG_YKEYS  yLOG_double  ("p_end"     , myKEYS.p_end);
         DEBUG_YKEYS  yLOG_double  ("p_inc"     , myKEYS.p_inc);
         DEBUG_YKEYS  yLOG_double  ("p_cur"     , myKEYS.p_cur);
         switch (a_minor) {
         case '0' :  myKEYS.p_cur  = myKEYS.p_beg;        break;
         case 'H' :  myKEYS.p_cur -= myKEYS.p_inc * 5.0;  break;
         case 'h' :  myKEYS.p_cur -= myKEYS.p_inc      ;  break;
         case 'l' :  myKEYS.p_cur += myKEYS.p_inc      ;  break;
         case 'L' :  myKEYS.p_cur += myKEYS.p_inc * 5.0;  break;
         case '$' :  myKEYS.p_cur  = myKEYS.p_end;        break;
         }
         if (myKEYS.p_cur < myKEYS.p_beg) myKEYS.p_cur = myKEYS.p_beg;
         if (myKEYS.p_cur > myKEYS.p_end) myKEYS.p_cur = myKEYS.p_end;
         DEBUG_YKEYS  yLOG_double  ("p_cur"     , myKEYS.p_cur);
      }
   }
   /*---(alignment)----------------------*/
   if (a_major == '^') {
      if (strchr ("0shcle$", a_minor) != NULL) {
         myKEYS.p_anchor = a_minor;
         ykeys__loop_calc ();
         myKEYS.p_redraw = '-';
      } else {
         return -1;
      }
   }
   /*---(complete)------------------------------*/
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   return 0;
}


