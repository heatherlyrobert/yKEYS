/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


tMY         myKEYS;


char  g_last      [LEN_LABEL] = "";



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yKEYS_ver [LEN_HUND] = "";

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
   snprintf (yKEYS_ver, LEN_HUND, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yKEYS_ver;
}



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
   fprintf (a_file, "len = %d¦", myKEYS.h_total);
   fprintf (a_file, "          ");
   for (i = 0; i < (myKEYS.h_total / 10) + 1; ++i)  fprintf (a_file, "%-10d", i);
   fprintf (a_file, "\n");
   fprintf (a_file, "type----  ");
   for (i = 0; i < (myKEYS.h_total / 10) + 1; ++i)  fprintf (a_file, "-123456789");
   fprintf (a_file, "\n");
   fprintf (a_file, "keys      %s¦", myKEYS.h_log);
   fprintf (a_file, "mode      %s¦", myKEYS.h_mode);
   fprintf (a_file, "multi     %s¦", myKEYS.h_multi);
   fprintf (a_file, "error     %s¦", myKEYS.h_errs);
   fprintf (a_file, "type----  ");
   for (i = 0; i < (myKEYS.h_total / 10) + 1; ++i)  fprintf (a_file, "-123456789");
   fprintf (a_file, "\n");
   fprintf (a_file, "          ");
   for (i = 0; i < (myKEYS.h_total / 10) + 1; ++i)  fprintf (a_file, "%-10d", i);
   fprintf (a_file, "\n");
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_init              (void)
{
   char        rc          =    0;
   /*> yvikeys_view_keys ("-- -");                                                    <*/
   rc = ykeys_logger_init ();
   rc = ykeys_repeat_init ();
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
   x_key = a_key;
   /*---(opengl)-------------------------*/
   if (a_env == 'g') {
      DEBUG_KEYS   yLOG_snote   ("opengl");
      switch (x_key) {
      case  G_KEY_ENTER :
         DEBUG_KEYS   yLOG_snote   ("fix ENTER");
         x_key = G_KEY_RETURN; /* X11 sends incorrently  */
         break;
      case  G_KEY_DEL   :
         DEBUG_KEYS   yLOG_snote   ("fix DEL");
         x_key = G_KEY_BS;     /* X11 sends incorrectly  */
         break;
      }
      DEBUG_KEYS   yLOG_sint    (x_key);
   }
   /*---(switch)-------------------------*/
   switch (x_key) {
   case  G_KEY_RETURN :
      DEBUG_KEYS   yLOG_snote   ("encode RETURN");
      x_key = G_CHAR_RETURN;
      break;
   case  G_KEY_ESCAPE :
      DEBUG_KEYS   yLOG_snote   ("encode ESCAPE");
      x_key = G_CHAR_ESCAPE;
      break;
   case  G_KEY_SPACE  :
      DEBUG_KEYS   yLOG_snote   ("encode SPACE");
      x_key = G_CHAR_SPACE;
      break;
   case  G_KEY_BS     :
      DEBUG_KEYS   yLOG_snote   ("encode BACKSPACE");
      x_key = G_CHAR_BS;
      break;
   case  G_KEY_DEL    :
      DEBUG_KEYS   yLOG_snote   ("encode DELETE");
      x_key = G_CHAR_DEL;
      break;
   case  G_KEY_GROUP  :
      DEBUG_KEYS   yLOG_snote   ("encode GROUP");
      x_key = G_CHAR_GROUP;
      break;
   case  G_KEY_FIELD  :
      DEBUG_KEYS   yLOG_snote   ("encode FIELD");
      x_key = G_CHAR_FIELD;
      break;
   }
   /*---(accumulate)---------------------*/
   switch (x_key) {
   case 0              :  ++myKEYS.h_noops;                     break;
   case 1              :  yKEYS_set_skip ();  x_key = 0;        break;
   case G_KEY_ACK      :  ++myKEYS.h_acks;                      break;
   case G_CHAR_SPACE   :  ++myKEYS.h_spaces;                    break;
   case G_CHAR_STORAGE :  ++myKEYS.h_spaces;                    break;
   }
   /*---(cleanse controls)---------------*/
   if (x_key > 0 && x_key <= 32)  x_key = 0;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return x_key;
}

uchar
ykeys__input_OLD        (uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   uchar       x_key       =  ' ';
   char        x_lock      =    0;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   /*---(repeating)---------*/
   if (yKEYS_oldkeys () == 1) {
      DEBUG_KEYS   yLOG_note    ("normal mode, group repeating older keys");
      x_key = myKEYS.h_log [myKEYS.h_curr];
      ++myKEYS.h_curr;
   }
   /*---(not-repeating)-----*/
   else {
      /*---(check key)---------*/
      x_key  = a_key;
      DEBUG_KEYS   yLOG_char    ("log_keys"  , myKEYS.h_logkeys);
      if (x_key == 0) {
         DEBUG_KEYS   yLOG_note    ("null key, nothing to do");
      } else if (myKEYS.h_logkeys == 'y') {
         DEBUG_KEYS   yLOG_note    ("normal mode, new keystroke and recording");
         yKEYS_logger (x_key);
      } else {
         DEBUG_KEYS   yLOG_note    ("normal mode, NO recording");
      }
      /*---(check locking)-----*/
      rc = yKEYS_check_unlock (&x_key);
      /*> x_lock = yKEYS_is_locked ();                                                <* 
       *> DEBUG_KEYS   yLOG_value   ("x_lock"    , x_lock);                           <* 
       *> if (x_lock) {                                                               <* 
       *>    if (yKEYS_check_unlock ()) {                                             <* 
       *>       DEBUG_LOOP   yLOG_note    ("received ¥¥ and key, unlocking");         <* 
       *>       x_key = 1;                                                            <* 
       *>    } else {                                                                 <* 
       *>       DEBUG_LOOP   yLOG_note    ("not ready to unlock, skipping");          <* 
       *>       x_key = 1;                                                            <* 
       *>    }                                                                        <* 
       *> }                                                                           <*/
      /*---(done)--------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return x_key;
}

uchar        /*-> gather main loop keyboard input ----[ ------ [gc.D44.233.C7]*/ /*-[02.0000.111.R]-*/ /*-[--.---.---.--]-*/
yKEYS_input_OLD         (char a_env, uchar a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   uchar       x_ch        = ' ';
   uchar       x_play      = ' ';
   char        x_used      =   0;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_complex ("a_env"     , "%c, %3d, %c", a_env, a_key, yMACRO_rec_mode ());
   /*---(fixes)--------------------------*/
   a_key = ykeys__input_fix (a_env, a_key);
   /*---(normal)-------------------------*/
   IF_MACRO_NOT_PLAYING   x_ch = ykeys__input_OLD (a_key);
   /*---(run, delay, or playback)--------*/
   IF_MACRO_PLAYING       x_ch = yMACRO_exec  (a_key);
   /*---(categorize)---------------------*/
   switch (x_ch) {
   case 0              :  ++myKEYS.h_noops;                     break;
   case 1              :  yKEYS_set_skip ();  x_ch = 0;         break;
   case G_KEY_ACK      :  ++myKEYS.h_acks;                      break;
   case G_KEY_SPACE    :  ++myKEYS.h_spaces;                    break;
   case G_CHAR_SPACE   :  ++myKEYS.h_spaces;                    break;
   case G_CHAR_STORAGE :  ++myKEYS.h_spaces;                    break;
   }
   /*---(logger)-------------------------*/
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return x_ch;
}

char         /*-> process input string in main loop --[ ------ [ge.C74.153.42]*/ /*-[02.0000.00#.D]-*/ /*-[--.---.---.--]-*/
yKEYS_string_OLD        (uchar *a_keys)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;     /* return code for errors              */
   char        rc          =    0;
   int         i           =    0;
   int         j           =   -1;
   int         x_len       =    0;
   uchar       x_ch        =  ' ';     /* current keystroke                   */
   char        x_keys      [LEN_RECD];
   char        x_error     =    0;          /* count of badly handled keys    */
   char        x_old       =  '-';
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
   x_len = strlen (a_keys);
   DEBUG_LOOP   yLOG_complex ("x_keys"    , "%3då%sæ", x_len, x_keys);
   --rce;
   for (i = 0; i < x_len; ++i) {
      /*---(get next char)---------------*/
      if (i != j) {
         x_ch = chrworking (a_keys [i]);
         DEBUG_LOOP   yLOG_complex ("new key"   , "%3di, %3dj, %3d, %c  -----------------------------------------------", i, j, x_ch, chrvisible (x_ch));
      } else {
         x_ch = 0;
         DEBUG_LOOP   yLOG_complex ("repeat key", "%3di, %3dj, %3d, %c  -----------------------------------------------", i, j, x_ch, chrvisible (x_ch));
      }
      j = i;
      /*---(handle input)----------------*/
      x_ch = yKEYS_input_OLD ('-', x_ch);
      /*---(handle keystroke)------------*/
      if (!yKEYS_is_locked ()) {
         rc = yMODE_handle (x_ch);
         DEBUG_LOOP   yLOG_complex ("normal"    , "%3d, %c, %4d", x_ch, chrvisible (x_ch), rc);
         if (rc < 0)  ++x_error;
      } else {
         DEBUG_LOOP   yLOG_complex ("skipped"   , "%3d, %c", x_ch, chrvisible (x_ch));
      }
      yKEYS_handled ();
      /*---(check for macro)-------------*/
      DEBUG_LOOP   yLOG_complex ("macro"     , "exe %c, rep %3d, h_total %3d, h_curr %3d", yMACRO_exe_mode (), yKEYS_repeats (), myKEYS.h_total, myKEYS.h_curr);
      IF_MACRO_MOVING  {
         DEBUG_LOOP   yLOG_note    ("macro running and used step, back up loop counter");
         --i;
      }
      /*---(check for old keys)----------*/
      rc = yKEYS_oldkeys ();
      DEBUG_LOOP   yLOG_value   ("old keys"  , rc);
      if (rc == 1) {
         DEBUG_LOOP   yLOG_note    ("group using older keystrokes, back up loop counter");
         --i;
         x_old = 'y';
      } else {
         x_ch = chrworking (a_keys [i]);
         DEBUG_LOOP   yLOG_complex ("group?"    , "%3d, %3d, %c", i, x_ch, chrvisible (x_ch));
         if (x_ch == ')') {
            rc = ykeys_group_check_end ();
            DEBUG_LOOP   yLOG_value   ("check"     , rc);
            if (rc > 0)   --i;
         }
      }
      /*---(done)------------------------*/
   }
   DEBUG_LOOP   yLOG_note    ("main loop done");
   if (x_error < -99)  x_error = -99;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return x_error;
}

char
ykeys__string_prepare   (uchar *a_keys, uchar *a_out, int *a_len, int *a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_LOOP   yLOG_spoint  (a_keys);
   --rce;  if (a_keys == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_spoint  (a_out);
   --rce;  if (a_out  == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_spoint  (a_len);
   --rce;  if (a_len == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_LOOP   yLOG_spoint  (a_end);
   --rce;  if (a_end == NULL) {
      DEBUG_LOOP   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(transform)----------------------*/
   strlcpy    (a_out, a_keys  , LEN_RECD);
   strlencode (a_out, ySTR_MAX, LEN_RECD);
   *a_len = strlen (a_out);
   DEBUG_LOOP   yLOG_sint    (*a_len);
   DEBUG_LOOP   yLOG_snote   (a_out);
   /*---(endpoint)-----------------------*/
   *a_end = myKEYS.h_all + *a_len;
   DEBUG_LOOP   yLOG_sint    (*a_end);
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> gather main loop keyboard input ----[ ------ [gc.D44.233.C7]*/ /*-[02.0000.111.R]-*/ /*-[--.---.---.--]-*/
yKEYS_input             (char a_env, uchar *a_key, uchar *a_str, int *n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_source    =    0;
   uchar       x_key       =  ' ';
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_KEYS   yLOG_complex ("args"      , "%c, %p, %p, %p", a_env, a_key, a_str, n);
   /*---(defense)------------------------*/
   --rce;  if (a_key == NULL) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get normal key)-----------------*/
   DEBUG_KEYS   yLOG_complex ("pos"       , "%3dc, %3dt", myKEYS.h_curr, myKEYS.h_total);
   IF_MACRO_NOT_PLAYING {
      if (a_str != NULL && n != NULL && myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_KEYS   yLOG_note    ("taking in new key from string");
         x_key = chrworking (a_str [*n]);
         ++(*n);
         x_source = 2;
      } else if (myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_KEYS   yLOG_note    ("use new key");
         x_key = ykeys__input_fix (a_env, *a_key);
         x_source = 0;
      } else {
         DEBUG_KEYS   yLOG_note    ("repeating older keys from log");
         x_key = myKEYS.h_log [myKEYS.h_curr];
         x_source = 1;
      }
   }
   /*---(get macro key)------------------*/
   else {
      DEBUG_KEYS   yLOG_note    ("macro execution, call yMACRO");
      x_key = yMACRO_exec  (*a_key);
      x_source = 3;
   }
   /*---(double cleanse controls)--------*/
   if (x_key > 0 && x_key < 32)  x_key = 0;
   /*---(logger)-------------------------*/
   rc = yKEYS_logger (x_key);
   DEBUG_KEYS   yLOG_value   ("logger"    , rc);
   /*---(check unlock)-------------------*/
   rc = yKEYS_check_unlock (&x_key);
   DEBUG_KEYS   yLOG_value   ("unlock"    , rc);
   /*---(save-back)----------------------*/
   DEBUG_KEYS   yLOG_value   ("x_source"  , x_source);
   *a_key = x_key;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return x_source;
}

char
ykeys_input_force       (char a_env, uchar *a_key, uchar *a_str, int *n)
{
   myKEYS.h_curr = myKEYS.h_total;
   return yKEYS_input (a_env, a_key, a_str, n);
}


uchar
ykeys__string_char      (void)
{
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_senter  (__FUNCTION__);
   /*---(get character)------------------*/
   if      (myKEYS.h_curr < myKEYS.h_total - 1) {
      return 1;
   }
   else if (myKEYS.h_curr < myKEYS.h_total)      return 2;
   return 0;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> process input string in main loop --[ ------ [ge.C74.153.42]*/ /*-[02.0000.00#.D]-*/ /*-[--.---.---.--]-*/
yKEYS_string            (uchar *a_keys)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =    0;
   int         i           =    0;
   int         j           =   -1;
   int         x_len       =    0;
   uchar       x_ch        =  ' ';     /* current keystroke                   */
   char        x_keys      [LEN_RECD];
   char        x_error     =    0;          /* count of badly handled keys    */
   char        x_old       =  '-';
   int         x_end       =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_LOOP   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ykeys__string_prepare (a_keys, x_keys, &x_len, &x_end);
   DEBUG_LOOP   yLOG_value   ("prepare"   , rc);
   if (rc < 0) {
      DEBUG_LOOP   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(walk characters)----------------*/
   while (n < x_end) {
      /*---(get next char)---------------*/
      rc = yKEYS_input ('-', &x_ch, x_keys, &n);
      /*---(handle keystroke)------------*/
      if (!yKEYS_is_locked ()) {
         rc = yMODE_handle (x_ch);
         DEBUG_LOOP   yLOG_complex ("normal"    , "%3d, %c, %4d", x_ch, chrvisible (x_ch), rc);
         if (rc < 0)  ++x_error;
      } else {
         DEBUG_LOOP   yLOG_complex ("skipped"   , "%3d, %c", x_ch, chrvisible (x_ch));
      }
      /*---(next)------------------------*/
      IF_MACRO_NOT_PLAYING   yKEYS_handled ();
      /*---(done)------------------------*/
   }
   DEBUG_LOOP   yLOG_note    ("main loop done");
   if (x_error < -99)  x_error = -99;
   /*---(complete)-----------------------*/
   DEBUG_LOOP   yLOG_exit    (__FUNCTION__);
   return x_error;
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
   char        rc           =    0;
   rc = yKEYS_init ();
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
   yURG_name  ("mode"         , YURG_ON);
   yURG_name  ("keys"         , YURG_ON);
   DEBUG_KEYS  yLOG_info     ("yKEYS"     , yKEYS_version   ());
   rc = yKEYS_init ();
   return rc;
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
   char        x_open      =  'å';
   int         i           =    0;
   char        x_list      [LEN_RECD]  = "";
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
   else if (strcmp (a_question, "pos"          )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS pos         : %4da  %4dn  %4dp", myKEYS.h_all, myKEYS.h_total, myKEYS.h_curr);
   }
   else if (strcmp (a_question, "counts"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS counts      : %3dg § %3da %3dt %c %3dc %c § %3da %3ds %3dz %3dp § %3de %3dw %3ds %c § %2do %2dc %c", myKEYS.h_grand, myKEYS.h_all, myKEYS.h_total, myKEYS.h_logkeys, myKEYS.h_curr, myKEYS.h_used, myKEYS.h_acks, myKEYS.h_spaces, myKEYS.h_noops, myKEYS.h_combos, myKEYS.h_errors, myKEYS.h_warnings, myKEYS.h_skips, myKEYS.h_locked, myKEYS.h_open, myKEYS.h_close, myKEYS.h_balanced);
   }
   else if (strcmp (a_question, "repeats"      )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS repeats     : %c  %4d  %4d", myKEYS.r_repeating, myKEYS.r_asked, myKEYS.r_count);
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
   /*---(complete)-----------------------*/
   return unit_answer;
}
