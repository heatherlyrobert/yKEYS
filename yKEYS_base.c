/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



char  g_logkeys   = 'y';
char  g_log   [LEN_FULL];
char  g_multi [LEN_FULL];
char  g_mode  [LEN_FULL];
char  g_errs [LEN_FULL];

int   g_all       = 0;                      /* all key count, from init       */
int   g_total      = 0;                      /* end of key log postion         */
int   g_curr      = 0;                      /* current key position           */

char  g_last  [LEN_LABEL];
int   g_acks      = 0;
int   g_spaces    = 0;
int   g_noops     = 0;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yKEYS_ver [200] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yKEYS_version           (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yKEYS_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yKEYS_ver;
}

char yKEYS_logging_on  (void) { g_logkeys = 'y'; return 0; }
char yKEYS_logging_off (void) { g_logkeys = '-'; return 0; }



/*====================------------------------------------====================*/
/*===----                        key logging                           ----===*/
/*====================------------------------------------====================*/
static void  o___LOGGING_________o () { return; }


char
yvikeys_keys_dump       (FILE *a_file)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   fprintf (a_file, "yVIKEYS, key logging report                                                               (:dump keys)\n");
   fprintf (a_file, "len = %d¦", g_total);
   fprintf (a_file, "          ");
   for (i = 0; i < (g_total / 10) + 1; ++i)  fprintf (a_file, "%-10d", i);
   fprintf (a_file, "\n");
   fprintf (a_file, "type----  ");
   for (i = 0; i < (g_total / 10) + 1; ++i)  fprintf (a_file, "-123456789");
   fprintf (a_file, "\n");
   fprintf (a_file, "keys      %s¦", g_log);
   fprintf (a_file, "mode      %s¦", g_mode);
   fprintf (a_file, "multi     %s¦", g_multi);
   fprintf (a_file, "error     %s¦", g_errs);
   fprintf (a_file, "type----  ");
   for (i = 0; i < (g_total / 10) + 1; ++i)  fprintf (a_file, "-123456789");
   fprintf (a_file, "\n");
   fprintf (a_file, "          ");
   for (i = 0; i < (g_total / 10) + 1; ++i)  fprintf (a_file, "%-10d", i);
   fprintf (a_file, "\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_init              (void)
{
   /*> yvikeys_view_keys ("-- -");                                                    <*/
   ykeys_logger_init ();
   ykeys_repeat_init ();
   return 0;
}

char
yKEYS_wrap              (void)
{
   return 0;
}

uchar
ykeys__input_fix        (char a_env, uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_key       = ' ';
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_KEYS   yLOG_schar   (a_env);
   DEBUG_KEYS   yLOG_sint    (a_key);
   /*---(default)------------------------*/
   if (a_env != 'g') {
      DEBUG_KEYS   yLOG_snote   ("not opengl, no fixes necessary");
      DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
      return a_key;
   }
   /*---(fixes)--------------------------*/
   DEBUG_KEYS   yLOG_snote   ("check");
   switch (a_key) {
   case  G_KEY_ENTER :
      DEBUG_KEYS   yLOG_snote   ("fix ENTER");
      x_key = G_KEY_RETURN; /* X11 sends incorrently  */
      break;
   case  G_KEY_DEL   :
      DEBUG_KEYS   yLOG_snote   ("fix DEL");
      x_key = G_KEY_BS;     /* X11 sends incorrectly  */
      break;
   default           :
      DEBUG_KEYS   yLOG_snote   ("fine");
      x_key = a_key;
      break;
   }
   DEBUG_KEYS   yLOG_sint    (x_key);
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return x_key;
}

uchar
ykeys__input            (uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_key       = ' ';
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   /*---(repeating)---------*/
   if (yKEYS_oldkeys ()) {
      DEBUG_KEYS   yLOG_note    ("normal mode, group repeating older keys");
      x_key = g_log [g_curr];
      ++g_curr;
   }
   /*---(not-repeating)-----*/
   else {
      x_key  = a_key;
      DEBUG_KEYS   yLOG_char    ("log_keys"  , g_logkeys);
      if (x_key == 0) {
         DEBUG_KEYS   yLOG_note    ("null key, nothing to do");
      } else if (g_logkeys == 'y') {
         DEBUG_KEYS   yLOG_note    ("normal mode, new keystroke and recording");
         yKEYS_logger (x_key);
      } else {
         DEBUG_KEYS   yLOG_note    ("normal mode, NO recording");
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return x_key;
}

uchar        /*-> gather main loop keyboard input ----[ ------ [gc.D44.233.C7]*/ /*-[02.0000.111.R]-*/ /*-[--.---.---.--]-*/
yKEYS_input             (char a_env, uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_ch        = ' ';
   uchar       x_play      = ' ';
   char        x_used      =   0;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_char    ("a_env"     , a_env);
   DEBUG_KEYS   yLOG_value   ("a_key"     , a_key);
   DEBUG_KEYS   yLOG_char    ("macro rec" , yMACRO_rec_mode ());
   /*---(fixes)--------------------------*/
   a_key = ykeys__input_fix (a_env, a_key);
   /*---(normal)-------------------------*/
   IF_MACRO_NOT_PLAYING   x_ch = ykeys__input (a_key);
   /*---(run, delay, or playback)--------*/
   IF_MACRO_PLAYING       x_ch = yMACRO_exec  (a_key);
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return x_ch;
}

char         /*-> process input string in main loop --[ ------ [ge.C74.153.42]*/ /*-[02.0000.00#.D]-*/ /*-[--.---.---.--]-*/
yKEYS_string         (uchar *a_keys)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;     /* return code for errors              */
   char        rc          =    0;
   int         i           =    0;
   int         j           =   -1;
   int         x_len       =    0;
   uchar       x_ch        =  ' ';     /* current keystroke                   */
   char        x_keys      [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   DEBUG_LOOP   yLOG_point   ("a_keys"    , a_keys);
   --rce;  if (a_keys == NULL) {
      DEBUG_LOOP   yLOG_note    ("a_keys is null");
      DEBUG_LOOP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy    (x_keys, a_keys  , LEN_RECD);
   strlencode (x_keys, ySTR_MAX, LEN_RECD);
   DEBUG_LOOP   yLOG_info    ("x_keys"    , x_keys);
   x_len = strlen (a_keys);
   DEBUG_LOOP   yLOG_value   ("x_len"     , x_len);
   --rce;
   for (i = 0; i < x_len; ++i) {
      DEBUG_LOOP   yLOG_value   ("LOOP"      , i);
      /*---(get next char)---------------*/
      if (i != j) {
         DEBUG_LOOP   yLOG_note    ("new keystroke");
         DEBUG_LOOP   yLOG_value   ("a_keys[i]" , a_keys[i]);
         DEBUG_LOOP   yLOG_char    ("a_keys[i]" , chrvisible (a_keys[i]));
         x_ch = chrworking (a_keys [i]);
      } else {
         DEBUG_LOOP   yLOG_note    ("repeat loop");
         x_ch = 0;
      }
      j = i;
      DEBUG_LOOP   yLOG_value   ("x_ch"      , x_ch);
      DEBUG_LOOP   yLOG_char    ("x_ch"      , chrvisible (x_ch));
      /*---(handle input)----------------*/
      x_ch = yKEYS_input ('-', x_ch);
      DEBUG_LOOP   yLOG_value   ("x_ch"      , x_ch);
      if (x_ch  == G_KEY_ACK)     ++g_acks;
      if (x_ch  == G_KEY_SPACE)   ++g_spaces;
      if (x_ch  == 0)             ++g_noops;
      /*---(handle keystroke)------------*/
      rc = yMODE_handle (x_ch);
      DEBUG_LOOP   yLOG_value   ("rc"        , rc);
      /*---(check for macro)-------------*/
      DEBUG_LOOP   yLOG_char    ("macro exe" , yMACRO_exe_mode ());
      DEBUG_LOOP   yLOG_value   ("macro cnt" , yKEYS_repeats ());
      DEBUG_LOOP   yLOG_value   ("s_nkey"    , g_total);
      DEBUG_LOOP   yLOG_value   ("s_gpos"    , g_curr);
      IF_MACRO_MOVING  {
         DEBUG_LOOP   yLOG_note    ("macro running and used step, back up loop counter");
         --i;
      }
      if (yKEYS_oldkeys ()) {
         DEBUG_LOOP   yLOG_note    ("group using older keystrokes, back up loop counter");
         --i;
      }
      /*---(done)------------------------*/
   }
   DEBUG_LOOP   yLOG_note    ("main loop done");
   if (rc >= 0)  rc = 0;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char          unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ykeys__unit_quiet       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yKEYS_unit" };
   yKEYS_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ykeys__unit_loud        (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yKEYS_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   DEBUG_KEYS  yLOG_info     ("yKEYS"     , yKEYS_version   ());
   yKEYS_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ykeys__unit_end         (void)
{
   DEBUG_KEYS  yLOG_enter   (__FUNCTION__);
   yKEYS_wrap ();
   DEBUG_KEYS  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yKEYS__unit             (char *a_question, char a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_RECD ] = "";
   int         x_beg       =    0;
   char        x_open      =  '[';
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "KEYS unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if (g_total > 40) {
      x_beg  = g_total - 40;
      x_open = '<';
   }
   if      (strcmp (a_question, "log"            )   == 0) {
      sprintf (t, "%s", g_log   + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS log         : %3d %3d %3d %c%-.40s]", g_all, g_total, g_curr, x_open, t);
   }
   else if (strcmp (a_question, "mode"           )   == 0) {
      sprintf (t, "%s", g_mode  + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS mode        : %3d %3d %3d %c%-.40s]", g_all, g_total, g_curr, x_open, t);
   }
   else if (strcmp (a_question, "multi"          )   == 0) {
      sprintf (t, "%s", g_multi + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS multi       : %3d %3d %3d %c%-.40s]", g_all, g_total, g_curr, x_open, t);
   }
   else if (strcmp (a_question, "error"          )   == 0) {
      sprintf (t, "%s", g_errs  + x_beg);
      snprintf (unit_answer, LEN_FULL, "KEYS error       : %3d %3d %3d %c%-.40s]", g_all, g_total, g_curr, x_open, t);
   }
   else if (strcmp (a_question, "full"           )   == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS full        : %3d %3d %3d [%s]", g_all, g_total, g_curr, g_log);
   }
   else if (strcmp (a_question, "status"         )   == 0) {
      yKEYS_status (t);
      strltrim (t, ySTR_BOTH, LEN_RECD);
      snprintf (unit_answer, LEN_FULL, "%-.60s", t);
   }
   else if (strcmp (a_question, "pos"          )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS pos         : %4da  %4dn  %4dp", g_all, g_total, g_curr);
   }
   /*> else if (strcmp (a_question, "acks"         )  == 0) {                                                          <* 
    *>    snprintf (unit_answer, LEN_FULL, "KEYS acks        : %3da %3ds %3dz", s_acks, s_spaces, s_noops);   <* 
    *> }                                                                                                               <*/
   else if (strcmp (a_question, "repeats"      )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS repeats     : %c  %4d  %4d", g_repeating, g_requested, g_repeats);
   }
   /*> else if (strcmp (a_question, "groups"       )  == 0) {                                        <* 
    *>    for (i = 1; i <= 5; ++i) {                                                                 <* 
    *>       if (s_pos [i] >= 0)  sprintf (t, "%02d/%c/%03d", s_rep [i], s_src [i], s_pos [i]);      <* 
    *>       else                 sprintf (t, "--/-/---");                                           <* 
    *>       strlcat (x_list, t, LEN_FULL);                                                          <* 
    *>       if (i < 5)  strlcat (x_list, ", ", LEN_FULL);                                           <* 
    *>    }                                                                                          <* 
    *>    snprintf (yVIKEYS__unit_answer, LEN_FULL, "KEYS groups      : %1d %s", s_level, x_list);   <* 
    *> }                                                                                             <*/
   /*---(complete)-----------------------*/
   return unit_answer;
}
