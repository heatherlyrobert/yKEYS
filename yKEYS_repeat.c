/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
ykeys_repeat_init       (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   int         i           =   0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (PMOD_REPEAT)) {
      DEBUG_YKEYS   yLOG_note    ("status is not ready for init");
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(setup)--------------------------*/
   yKEYS_repeat_reset ();
   /*---(group)--------------------------*/
   ykeys_group_reset ();
   /*---(update status)------------------*/
   yMODE_init_set   (PMOD_REPEAT, NULL, yKEYS_repeat_umode);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      status functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

char yKEYS_check_repeat (void) { if (myKEYS.r_count <= 0) yKEYS_repeat_reset (); }
char yKEYS_repeating    (void) { if (myKEYS.r_repeating == 'y')  return 1; return 0; }
char yKEYS_normal       (void) { if (myKEYS.r_repeating == '-')  return 1; return 0; }
int  yKEYS_repeats      (void) { return myKEYS.r_count; }
int  yKEYS_repeat_orig  (void) { return myKEYS.r_asked;}

char yKEYS_repeat_beg   (void) { if (myKEYS.r_asked == myKEYS.r_count) return 1;  return 0; }
char yKEYS_repeat_end   (void) { if (myKEYS.r_count == 0) return 1;  return 0; }



/*====================------------------------------------====================*/
/*===----                      action functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___ACTION__________o () { return; }

char yKEYS_repeat_dec   (void) { if (myKEYS.r_count > 0)  --myKEYS.r_count; return 0;}
int  yKEYS_repeat_useall(void) { int a = myKEYS.r_count; yKEYS_repeat_reset ();  return a; }

char
yKEYS_repeat_reset      (void)
{
   myKEYS.r_repeating = '-';
   myKEYS.r_asked     = 0;
   myKEYS.r_count     = 0;
   return 0;
}

char
ykeys_repeat_set        (int a_repeat)
{
   myKEYS.r_asked     = myKEYS.r_count = a_repeat;
   myKEYS.r_repeating = 'y';
   yKEYS_check_repeat ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        mode handling                         ----===*/
/*====================------------------------------------====================*/
static void  o___MODE____________o () { return; }

char         /*-> accumulate multiplier --------------[ ------ [ge.A43.214.63]*/ /*-[01.0000.102.!]-*/ /*-[--.---.---.--]-*/
yKEYS_repeat_umode      (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_char    ("a_major"   , a_major);
   DEBUG_YKEYS   yLOG_char    ("a_minor"   , a_minor);
   /*---(defenses)-----------------------*/
   DEBUG_YKEYS   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (PMOD_REPEAT )) {
      DEBUG_YKEYS   yLOG_note    ("not the correct mode");
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(turn off repeating)--------------------*/
   myKEYS.r_repeating = '-';
   /*---(major mode changes)-------------*/
   if (a_minor == G_KEY_RETURN || a_minor == G_KEY_ENTER || a_minor == G_KEY_ESCAPE) {
      DEBUG_YKEYS   yLOG_note    ("aborting repeat");
      yMODE_exit  ();
      myKEYS.r_count = 0;
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(check for major)-----------------------*/
   if (myKEYS.r_count ==  0 && strchr ("123456789", a_major) != NULL) {
      DEBUG_YKEYS   yLOG_note    ("assign starting repeat");
      myKEYS.r_count  = a_major - '0';
      DEBUG_YKEYS   yLOG_value   ("myKEYS.r_count"  , myKEYS.r_count);
   }
   /*---(check for minor)-----------------------*/
   if (a_minor == '0' && myKEYS.r_count == 0) {
      DEBUG_YKEYS   yLOG_note    ("leading zero key");
      yMODE_exit  ();
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return  a_minor;
   } else if (strchr ("0123456789",  a_minor) != NULL) {
      DEBUG_YKEYS   yLOG_note    ("increment repeat");
      myKEYS.r_count *= 10;
      myKEYS.r_count += a_minor - '0';
      DEBUG_YKEYS   yLOG_value   ("myKEYS.r_count"  , myKEYS.r_count);
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return 0;
   } else if (myKEYS.r_count == 0) {
      DEBUG_YKEYS   yLOG_note    ("non-digit key");
      yMODE_exit  ();
      DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
      return  a_minor;
   }
   /*---(pass through)-------------------*/
   DEBUG_YKEYS   yLOG_note    ("prepare repeat for use");
   DEBUG_YKEYS   yLOG_value   ("myKEYS.r_count"  , myKEYS.r_count);
   --myKEYS.r_count;
   if (myKEYS.r_count <  0) myKEYS.r_count =  0;
   myKEYS.r_asked     = myKEYS.r_count;
   myKEYS.r_repeating = 'y';
   /*---(complete)-----------------------*/
   yMODE_exit  ();
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return a_minor;
}

char
yKEYS_repeat_check      (uchar a_major, uchar a_minor, char a_prev, char a_curr, char a_rc)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_repeat    =    0;
   char        rc          =    0;
   /*---(header)----------------------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(capture repeats)-------------*/
   x_repeat = yKEYS_repeats ();
   DEBUG_YKEYS   yLOG_sint    (x_repeat);
   if (x_repeat <= 0) {
      DEBUG_YKEYS   yLOG_snote   ("no repeats requested");
      DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(check mode change)-----------*/
   x_repeat = yKEYS_repeats ();
   if (a_prev != a_curr) {
      DEBUG_YKEYS   yLOG_snote   ("no repeats across mode changes");
      yKEYS_repeat_reset ();
      DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(multi-key repeats)-----------*/
   rc = yKEYS_check_multi (a_major, a_minor);
   DEBUG_YKEYS   yLOG_sint    (rc);
   if (rc == 1) {
      DEBUG_YKEYS   yLOG_snote   ("multi-key, so defer repeating");
      DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(loop repeats)----------------*/
   if (a_rc >= 0 && x_repeat > 0 && a_curr != PMOD_REPEAT) {
      DEBUG_YKEYS   yLOG_note    ("repeating");
      yKEYS_repeat_dec ();
      DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
      return 1;
   }
   /*---(loop repeats)----------------*/
   if (a_rc < 0 && a_curr != PMOD_REPEAT) {
      DEBUG_YKEYS   yLOG_note    ("complete repeat");
      yKEYS_repeat_reset ();
      DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}


