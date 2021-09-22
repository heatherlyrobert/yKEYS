/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


int   g_requested = 0;
int   g_repeats   = 0;
char  g_repeating = '-';

int   g_level                 = 0;;
int   g_rep     [LEN_LABEL];
uchar g_src     [LEN_LABEL];
int   g_pos     [LEN_LABEL];



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
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (PMOD_REPEAT)) {
      DEBUG_PROG   yLOG_note    ("status is not ready for init");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(setup)--------------------------*/
   yKEYS_repeat_reset ();
   /*---(group)--------------------------*/
   for (i = 0; i < LEN_LABEL; ++i) {
      g_pos [i]  = -1;
      g_src [i]  = '-';
      g_rep [i]  = -1;
   }
   /*---(update status)------------------*/
   yMODE_init_set   (PMOD_REPEAT, yKEYS_repeat_umode);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      status functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___STATUS__________o () { return; }

char yKEYS_repeating    (void) { if (g_repeating == 'y')  return 1; return 0; }
char yKEYS_normal       (void) { if (g_repeating == '-')  return 1; return 0; }
int  yKEYS_repeats      (void) { if (g_repeats < 0) yKEYS_repeat_reset ();  return g_repeats; }
int  yKEYS_repeat_orig  (void) { return g_requested;}



/*====================------------------------------------====================*/
/*===----                      action functions                        ----===*/
/*====================------------------------------------====================*/
static void  o___ACTION__________o () { return; }

char yKEYS_repeat_dec   (void) { if (g_repeats > 0)  --g_repeats; else yKEYS_repeat_reset ();  return 0;}
int  yKEYS_repeat_useall(void) { if (g_repeats < 0) yKEYS_repeat_reset (); int a = g_repeats; g_repeats = 0;  return a; }

char
yKEYS_repeat_reset      (void)
{
   g_repeating = '-';
   g_requested = 0;
   g_repeats   = 0;
   return 0;
}

char
ykeys_repeat_set        (int a_repeat)
{
   g_requested = g_repeats = a_repeat;
   g_repeating = 'y';
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
   DEBUG_USER   yLOG_enter   (__FUNCTION__);
   DEBUG_USER   yLOG_char    ("a_major"   , a_major);
   DEBUG_USER   yLOG_char    ("a_minor"   , a_minor);
   /*---(defenses)-----------------------*/
   DEBUG_USER   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (PMOD_REPEAT )) {
      DEBUG_USER   yLOG_note    ("not the correct mode");
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(turn off repeating)--------------------*/
   g_repeating = '-';
   /*---(major mode changes)-------------*/
   if (a_minor == G_KEY_RETURN || a_minor == G_KEY_ENTER || a_minor == G_KEY_ESCAPE) {
      DEBUG_USER   yLOG_note    ("aborting repeat");
      yMODE_exit  ();
      g_repeats = 0;
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(check for major)-----------------------*/
   if (g_repeats ==  0 && strchr ("123456789", a_major) != NULL) {
      DEBUG_USER   yLOG_note    ("assign starting repeat");
      g_repeats  = a_major - '0';
      DEBUG_USER   yLOG_value   ("g_repeats"  , g_repeats);
   }
   /*---(check for minor)-----------------------*/
   if (a_minor == '0' && g_repeats == 0) {
      DEBUG_USER   yLOG_note    ("leading zero key");
      yMODE_exit  ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return  a_minor;
   } else if (strchr ("0123456789",  a_minor) != NULL) {
      DEBUG_USER   yLOG_note    ("increment repeat");
      g_repeats *= 10;
      g_repeats += a_minor - '0';
      DEBUG_USER   yLOG_value   ("g_repeats"  , g_repeats);
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return 0;
   } else if (g_repeats == 0) {
      DEBUG_USER   yLOG_note    ("non-digit key");
      yMODE_exit  ();
      DEBUG_USER   yLOG_exit    (__FUNCTION__);
      return  a_minor;
   }
   /*---(pass through)-------------------*/
   DEBUG_USER   yLOG_note    ("prepare repeat for use");
   DEBUG_USER   yLOG_value   ("g_repeats"  , g_repeats);
   --g_repeats;
   if (g_repeats <  0) g_repeats =  0;
   g_requested = g_repeats;
   g_repeating = 'y';
   /*---(complete)-----------------------*/
   yMODE_exit  ();
   DEBUG_USER   yLOG_exit    (__FUNCTION__);
   return a_minor;
}


