/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"




/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char          unit_answer [LEN_RECD];

char       /*----: set up program urgents/debugging --------------------------*/
ykeys__unit_quiet       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yKEYS_unit" };
   char        rc           =    0;
   rc = yMODE_init  (MODE_MAP);
   rc = yKEYS_init  ();
   rc = yMACRO_global_init  ();
   return rc;
}

char       /*----: set up program urgents/debugging --------------------------*/
ykeys__unit_loud        (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yKEYS_unit" };
   char        rc           =    0;
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("ymode"        , YURG_ON);
   yURG_name  ("ykeys"        , YURG_ON);
   DEBUG_YKEYS  yLOG_info     ("yKEYS"     , yKEYS_version   ());
   rc = yMODE_init  (MODE_MAP);
   rc = yKEYS_init  ();
   rc = yMACRO_global_init  ();
   return rc;
}

char       /*----: stop logging ----------------------------------------------*/
ykeys__unit_end         (void)
{
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   yKEYS_wrap ();
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

static   int  s_draws      = 0;
static   int  s_inputs     = 0;
static   int  s_alts       = 0;
static   int  s_pos        = 0;
static   char s_keys       [LEN_RECD] = "";
static   int  s_len        = 0;

char
ykeys__unit_prep        (char *a_keys)
{
   s_draws  = 0;
   s_inputs = 0;
   s_alts   = 0;
   s_pos    = 0;
   if (a_keys != NULL)  strlcpy (s_keys, a_keys, LEN_RECD);
   else                 strlcpy (s_keys, ""    , LEN_RECD);
   s_len = strlen (s_keys);
   return 0;
}

char
ykeys__unit_input       (char a_blocking, char *a_key)
{
   ++s_inputs;
   if (a_key == NULL)  return -1;
   if (s_pos >= s_len)  *a_key = 0;
   *a_key = s_keys [s_pos++];
   return 0;
}

char
ykeys__unit_draw        (float a_zoom)
{
   ++s_draws;
   return 0;
}

char
ykeys__unit_altinput    (void)
{
   ++s_alts;
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yKEYS__unit             (char *a_question, char a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD ] = "";
   int         x_beg       =    0;
   char        x_open      =  'å';
   int         i           =    0;
   char        x_list      [LEN_RECD]  = "";
   char        c           =  '·';
   char        d           =  '·';
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "KEYS unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if (myKEYS.h_total > 40) {
      x_beg  = myKEYS.h_total - 40;
      x_open = '<';
   }
   if      (strcmp (a_question, "log"            )   == 0) {
      sprintf (t, "%s", myKEYS.h_log   + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS log         : %c%-.40sæ", x_open, t);
   }
   else if (strcmp (a_question, "mode"           )   == 0) {
      sprintf (t, "%s", myKEYS.h_mode  + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS mode        : %c%-.40sæ", x_open, t);
   }
   else if (strcmp (a_question, "multi"          )   == 0) {
      sprintf (t, "%s", myKEYS.h_multi + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS multi       : %c%-.40sæ", x_open, t);
   }
   else if (strcmp (a_question, "error"          )   == 0) {
      sprintf (t, "%s", myKEYS.h_errs  + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS error       : %c%-.40sæ", x_open, t);
   }
   else if (strcmp (a_question, "ugly_every"     )   == 0) {
      snprintf (unit_answer, LEN_RECD, "KEYS ugly every  : å%sæ", myKEYS.h_every);
   }
   else if (strcmp (a_question, "ugly_emode"     )   == 0) {
      snprintf (unit_answer, LEN_RECD, "KEYS ugly emode  : å%sæ", myKEYS.h_emode);
   }
   else if (strcmp (a_question, "every"          )   == 0) {
      x_beg  = 0;
      x_open = 'å';
      if (myKEYS.h_grand > 70) {
         x_beg  = myKEYS.h_grand - 70;
         x_open = '<';
      }
      sprintf (t, "%s", myKEYS.h_every + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS every       : %c%-.70sæ", x_open, t);
   }
   else if (strcmp (a_question, "emode"          )   == 0) {
      x_beg  = 0;
      x_open = 'å';
      if (myKEYS.h_grand > 70) {
         x_beg  = myKEYS.h_grand - 70;
         x_open = '<';
      }
      sprintf (t, "%s", myKEYS.h_emode + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS emode       : %c%-.70sæ", x_open, t);
   }
   else if (strcmp (a_question, "estat"          )   == 0) {
      x_beg  = 0;
      x_open = 'å';
      if (myKEYS.h_grand > 70) {
         x_beg  = myKEYS.h_grand - 70;
         x_open = '<';
      }
      sprintf (t, "%s", myKEYS.h_estat + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS estat       : %c%-.70sæ", x_open, t);
   }
   else if (strcmp (a_question, "pos"          )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS pos         : %4da  %4dn  %4dp", myKEYS.h_all, myKEYS.h_total, myKEYS.h_curr);
   }
   else if (strcmp (a_question, "counts"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS counts      : %3dg § %3da %3dt %c %3dc %c § %3da %3ds %3dz %3dp § %3de %3dw %3ds %c § %2do %2dc %c", myKEYS.h_grand, myKEYS.h_all, myKEYS.h_total, myKEYS.h_logkeys, myKEYS.h_curr, chrvisible (myKEYS.h_log [myKEYS.h_curr]), myKEYS.h_acks, myKEYS.h_spaces, myKEYS.h_noops, myKEYS.h_combos, myKEYS.h_errors, myKEYS.h_warnings, myKEYS.h_skips, myKEYS.h_locked, myKEYS.h_open, myKEYS.h_close, myKEYS.h_balanced);
   }
   else if (strcmp (a_question, "repeats"      )  == 0) {
      if (yKEYS_repeat_beg ())   c = 'y';
      if (yKEYS_repeat_end ())   d = 'y';
      snprintf (unit_answer, LEN_FULL, "KEYS repeats     : %c  %4da  %4dc   %c   %c", myKEYS.r_repeating, myKEYS.r_asked, myKEYS.r_count, c, d);
   }
   else if (strcmp (a_question, "groups"       )  == 0) {
      for (i = 1; i <= 5; ++i) {
         if (myKEYS.r_beg [i] >= 0) {
            if (myKEYS.r_end [i] >= 0)
               sprintf (t, "%02d(%c)%03d:%03d", myKEYS.r_reps [i], myKEYS.r_macro [i], myKEYS.r_beg [i], myKEYS.r_end [i]);
            else 
               sprintf (t, "%02d(%c)%03d:···", myKEYS.r_reps [i], myKEYS.r_macro [i], myKEYS.r_beg [i]);
         } else sprintf (t, "············");
         strlcat (x_list, t, LEN_FULL);
         if (i < 5)  strlcat (x_list, ", ", LEN_FULL);
      }
      snprintf (unit_answer, LEN_FULL, "KEYS groups      : %1d %s", myKEYS.r_level, x_list);
   }
   else if (strcmp (a_question, "loop"        )   == 0) {
      yKEYS_loop_status ('l', 70, t);
      snprintf (unit_answer, LEN_RECD, "KEYS loop        : %s", t + 9);
   }
   else if (strcmp (a_question, "runs"         )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS runs        : A %4d %c, D %-10.10p %-4d, I %-10.10p %-4d, A %-10.10p %d",
            myKEYS.c_max_loop, myKEYS.c_env,
            myKEYS.c_draw, s_draws,
            myKEYS.c_input, s_inputs,
            myKEYS.c_altinput, s_alts);
   }
   else if (strcmp (a_question, "timing"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS timing      : A %4ld %8lld, D %4ld %8lld, K %4ld %8lld, I %4ld, M %8lld",
            myKEYS.loops,  myKEYS.l_avg_all,
            myKEYS.l_draw, myKEYS.l_avg_draw,
            myKEYS.l_keys, myKEYS.l_avg_keys,
            myKEYS.l_idle,
            myKEYS.l_avg_miss);
   }
   /*> sprintf (a_list, "main, %8lldt, %8lldr, %8lldu, %6ldt, %6ldd, %6ldk, %6ldi",   <* 
    *>       s_loop_targ, s_loop_rem, s_loop_used, s_avg, myMACRO.c_draw, s_keys, s_idle);    <*/
   /*---(complete)-----------------------*/
   return unit_answer;
}


