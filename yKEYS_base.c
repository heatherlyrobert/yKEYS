/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


tMY         myKEYS;


char    s_env          = 'c';
char    (*s_draw)      (float) = NULL;
char    (*s_input)     (char, char*) = NULL;
char    (*s_altinput)  (void)  = NULL;
int     s_max_loop     =   0;



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
   rc = ykeys_loop_init   ();
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
   case G_KEY_SKIP     :  ++myKEYS.h_acks;                      break;
   case G_CHAR_SPACE   :  ++myKEYS.h_spaces;                    break;
   case G_CHAR_STORAGE :  ++myKEYS.h_spaces;                    break;
   }
   /*---(cleanse controls)---------------*/
   if      (x_key == G_KEY_SKIP) ;
   else if (x_key > 0 && x_key <= 32)  x_key = 0;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return x_key;
}

char
ykeys__string_prepare   (uchar *a_keys, uchar *a_out, int *a_len, int *a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_KEYS   yLOG_spoint  (a_keys);
   --rce;  if (a_keys == NULL) {
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_spoint  (a_out);
   --rce;  if (a_out  == NULL) {
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_spoint  (a_len);
   --rce;  if (a_len == NULL) {
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_KEYS   yLOG_spoint  (a_end);
   --rce;  if (a_end == NULL) {
      DEBUG_KEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(transform)----------------------*/
   strlcpy    (a_out, a_keys  , LEN_RECD);
   strlencode (a_out, ySTR_MAX, LEN_RECD);
   *a_len = strlen (a_out);
   DEBUG_KEYS   yLOG_sint    (*a_len);
   DEBUG_KEYS   yLOG_snote   (a_out);
   /*---(endpoint)-----------------------*/
   *a_end = myKEYS.h_all + *a_len;
   DEBUG_KEYS   yLOG_sint    (*a_end);
   /*---(place at end)-------------------*/
   myKEYS.h_curr = myKEYS.h_total;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char         /*-> gather main loop keyboard input ----[ ------ [gc.D44.233.C7]*/ /*-[02.0000.111.R]-*/ /*-[--.---.---.--]-*/
ykeys__input             (char a_env, uchar *a_key, uchar *a_str, int *n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_source    =    0;
   uchar       x_key       =  ' ';
   int         x_len       =    0;
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
   --rce;  IF_MACRO_OFF {
      if (a_str != NULL && n != NULL && myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_KEYS   yLOG_note    ("taking in new key from string");
         x_len = strlen (a_str);
         DEBUG_KEYS   yLOG_complex ("pos"       , "%3dn, %3d len", *n, x_len);
         if (*n < 0 || *n >= x_len) {
            *a_key = 0;
            DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         x_key = chrworking (a_str [*n]);
         x_key = ykeys__input_fix (a_env, x_key);
         DEBUG_KEYS   yLOG_value   ("x_key"     , x_key);
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
   /*---(get macro playback)-------------*/
   else IF_MACRO_PLAYBACK {
      DEBUG_KEYS   yLOG_note    ("macro playback, get key, then call yMACRO");
      if (a_str != NULL && n != NULL && myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_KEYS   yLOG_note    ("taking in playback key from string");
         x_len = strlen (a_str);
         DEBUG_KEYS   yLOG_complex ("pos"       , "%3dn, %3d len", *n, x_len);
         if (*n < 0 || *n >= x_len) {
            *a_key = 0;
            DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         x_key = chrworking (a_str [*n]);
         x_key = ykeys__input_fix (a_env, x_key);
         DEBUG_KEYS   yLOG_value   ("x_key"     , x_key);
         ++(*n);
         x_source = 3;
      } else {
         DEBUG_KEYS   yLOG_note    ("no new playback keys, just wait");
         *a_key = 0;
         DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_key = yMACRO_exec  (x_key);
      x_source = 4;
   }
   /*---(get macro execution)------------*/
   else {
      DEBUG_KEYS   yLOG_note    ("macro execution, call yMACRO");
      x_key = yMACRO_exec  (*a_key);
      x_source = 5;
   }
   /*---(double cleanse controls)--------*/
   if (x_key > 0 && x_key < 32) {
      if      (x_key == G_KEY_ESCAPE)  ;
      else if (x_key == G_KEY_RETURN)  ;
      else     x_key = 0;
   }
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
ykeys__input_force      (char a_env, uchar *a_key, uchar *a_str, int *n)
{
   myKEYS.h_curr = myKEYS.h_total;
   return ykeys__input (a_env, a_key, a_str, n);
}

char
ykeys__handle     (uchar a_key, int *a_error)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(handle keystroke)---------------*/
   if (!yKEYS_is_locked () && a_key != G_KEY_NOOP && a_key != G_KEY_SKIP) {
      rc = yMODE_handle (a_key);
      if (rc >= 0) {
         DEBUG_KEYS   yLOG_complex ("normal"    , "%3d, %c, %4d", a_key, chrvisible (a_key), rc);
      } else {
         DEBUG_KEYS   yLOG_complex ("error"     , "%3d, %c, %4d", a_key, chrvisible (a_key), rc);
         if (a_error != NULL)  *a_error += 1;
      }
   } else {
      DEBUG_KEYS   yLOG_complex ("skipped"   , "%3d, %c", a_key, chrvisible (a_key));
   }
   /*---(complete)-----------------------*/
   return rc;
}

char         /*-> process input string in main loop --[ ------ [ge.C74.153.42]*/ /*-[02.0000.00#.D]-*/ /*-[--.---.---.--]-*/
yKEYS_string            (uchar *a_keys)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          =    0;
   int         x_len       =    0;
   uchar       x_key       =  ' ';     /* current keystroke                   */
   char        x_keys      [LEN_RECD];
   int         x_error     =    0;          /* count of badly handled keys    */
   int         x_end       =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ykeys__string_prepare (a_keys, x_keys, &x_len, &x_end);
   DEBUG_KEYS   yLOG_value   ("prepare"   , rc);
   if (rc < 0) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(walk characters)----------------*/
   while (n < x_end) {
      /*---(get next char)---------------*/
      rc = ykeys__input ('-', &x_key, x_keys, &n);
      DEBUG_KEYS   yLOG_value   ("input"     , rc);
      if (rc < 0)  break;
      /*---(handle keystroke)------------*/
      rc = ykeys__handle (x_key, &x_error);
      DEBUG_KEYS   yLOG_value   ("handle"    , rc);
      if (rc < 0)  ++x_error;
      /*---(next)------------------------*/
      IF_MACRO_NOT_PLAYING   yKEYS_nextpos ();
      /*---(done)------------------------*/
   }
   DEBUG_KEYS   yLOG_note    ("main loop done");
   if (x_error < -99)  x_error = -99;
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return x_error;
}

char
ykeys__prepare          (char *a_delay, char *a_update, int a_loops, char a_env, void *a_draw, void *a_input, void *a_altinput)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   s_env      = '-';
   s_max_loop = 0;
   s_draw     = NULL;
   s_input    = NULL;
   s_altinput = NULL;
   /*---(timing)-------------------------*/
   rc = yKEYS_loop_set     (a_delay, a_update);
   DEBUG_KEYS   yLOG_value   ("loop_set"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(loops)--------------------------*/
   DEBUG_KEYS   yLOG_value   ("a_loops"   , a_loops);
   if (a_loops > 0)  s_max_loop = a_loops;
   /*---(environment)--------------------*/
   DEBUG_KEYS   yLOG_char    ("a_env"     , a_env);
   --rce;  if (a_env == 0 || strchr ("gc", a_env) == NULL) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_env      = a_env;
   /*---(draw)---------------------------*/
   DEBUG_KEYS   yLOG_point   ("a_draw"    , a_draw);
   --rce;  if (a_draw == NULL) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_draw     = a_draw;
   /*---(input)--------------------------*/
   DEBUG_KEYS   yLOG_point   ("a_input"   , a_input);
   --rce;  if (a_input == NULL) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_input    = a_input;
   /*---(alt-input)----------------------*/
   DEBUG_KEYS   yLOG_point   ("a_altinput", a_altinput);
   s_altinput = a_altinput;
   /*---(run drawer)---------------------*/
   rc = s_draw (0.0);
   DEBUG_KEYS   yLOG_value   ("drawing"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yKEYS_quit        (void) { myKEYS.done = 'y'; }
char yKEYS_writequit   (void) { myKEYS.done = 'y'; }
char yKEYS_writequitall(void) { myKEYS.done = 'y'; }
char ykeys_quitting    (void) { if (myKEYS.done    == 'y') return 1; return 0; }

char         /*-> handle main loop for ncurses -------[ ------ [gn.842.232.99]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
yKEYS_main              (char *a_delay, char *a_update, int a_loops, char a_env, void *a_draw, void *a_input, void *a_altinput)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_temp      =    0;
   int         x_ch        =  ' ';
   uchar       x_key       =  ' ';
   char        x_draw      =  '-';
   char        t           [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_KEYS   yLOG_break   ();
   DEBUG_KEYS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ykeys__prepare (a_delay, a_update, a_loops, a_env, a_draw, a_input, a_altinput);
   DEBUG_KEYS   yLOG_value   ("loop_set"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_KEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(CLA for script)-----------------*/
   /*> DEBUG_KEYS   yLOG_info    ("script"    , myVIKEYS.m_script);                   <*/
   /*> if (strcmp (myVIKEYS.m_script, "") != 0) {                                     <* 
    *>    DEBUG_KEYS   yLOG_note    ("command line script argument");                 <* 
    *>    sprintf (t, ":script %s", myVIKEYS.m_script);                               <* 
    *>    DEBUG_KEYS   yLOG_info    ("t"         , t);                                <* 
    *>    rc = yVIKEYS_cmds_direct (t);                                               <* 
    *>    DEBUG_KEYS   yLOG_value   ("cmds"      , rc);                               <* 
    *> }                                                                              <*/
   /*---(main-loop)----------------------*/
   while (1) {
      DEBUG_KEYS  yLOG_value   ("LOOP"      , myKEYS.loops);
      /*---(start loop)------------------*/
      yKEYS_loop_beg   ();
      /*---(alternate input)-------------*/
      if (s_altinput != NULL) {
         rc = s_altinput ();
         DEBUG_KEYS  yLOG_value   ("altinput"  , rc);
      }
      /*---(get input)-------------------*/
      rc = s_input (myKEYS.l_blocking, &x_key);
      DEBUG_KEYS  yLOG_complex ("input"     , "%-4d, %d, %c", rc, x_key, chrvisible (x_key));
      /*---(keyboard input)--------------*/
      rc = ykeys__input (s_env, &x_key, NULL, NULL);
      DEBUG_KEYS  yLOG_complex ("input_adj" , "%-4d, %d, %c", rc, x_key, chrvisible (x_key));
      /*---(handle keystroke)------------*/
      rc = ykeys__handle (x_key, NULL);
      DEBUG_KEYS   yLOG_value   ("handle"    , rc);
      /*---(exiting)---------------------*/
      ++myKEYS.loops;
      if (ykeys_quitting ()) {
         DEBUG_KEYS   yLOG_note    ("user requested quitting");
         break;
      }
      if (s_max_loop > 0 && myKEYS.loops >= s_max_loop) {
         DEBUG_KEYS   yLOG_note    ("hit max loops, stopping");
         break;
      }
      /*---(next)------------------------*/
      IF_MACRO_NOT_PLAYING   yKEYS_nextpos ();
      /*---(showing)---------------------*/
      x_draw = '-';
      if ((myKEYS.loops % myKEYS.l_loops) == 0) {
         x_draw = 'y';
         yKEYS_loop_graf  ();
         rc = s_draw (0.0);
         DEBUG_KEYS   yLOG_value   ("drawing"   , rc);
      }
      /*---(sleeping)--------------------*/
      ykeys_loop_sleep (x_key, x_draw);
      /*---(done)------------------------*/
   }
   DEBUG_KEYS   yLOG_exit    (__FUNCTION__);
   DEBUG_KEYS  yLOG_break   ();
   /*---(complete)-----------------------*/
   return 0;
}



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
   yURG_name  ("mode"         , YURG_ON);
   yURG_name  ("keys"         , YURG_ON);
   DEBUG_KEYS  yLOG_info     ("yKEYS"     , yKEYS_version   ());
   rc = yKEYS_init  ();
   rc = yMACRO_global_init  ();
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
   else if (strcmp (a_question, "pos"          )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS pos         : %4da  %4dn  %4dp", myKEYS.h_all, myKEYS.h_total, myKEYS.h_curr);
   }
   else if (strcmp (a_question, "counts"       )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS counts      : %3dg § %3da %3dt %c %3dc %c § %3da %3ds %3dz %3dp § %3de %3dw %3ds %c § %2do %2dc %c", myKEYS.h_grand, myKEYS.h_all, myKEYS.h_total, myKEYS.h_logkeys, myKEYS.h_curr, chrvisible (myKEYS.h_log [myKEYS.h_curr]), myKEYS.h_acks, myKEYS.h_spaces, myKEYS.h_noops, myKEYS.h_combos, myKEYS.h_errors, myKEYS.h_warnings, myKEYS.h_skips, myKEYS.h_locked, myKEYS.h_open, myKEYS.h_close, myKEYS.h_balanced);
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
   else if (strcmp (a_question, "loop"        )   == 0) {
      yKEYS_loop_status ('l', 70, t);
      snprintf (unit_answer, LEN_RECD, "KEYS loop        : %s", t + 9);
   }
   else if (strcmp (a_question, "runs"         )  == 0) {
      snprintf (unit_answer, LEN_FULL, "KEYS runs        : A %4d %c, D %-10.10p %-4d, I %-10.10p %-4d, A %-10.10p %d",
            s_max_loop, s_env,
            s_draw, s_draws,
            s_input, s_inputs,
            s_altinput, s_alts);
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
    *>       s_loop_targ, s_loop_rem, s_loop_used, s_avg, s_draw, s_keys, s_idle);    <*/
   /*---(complete)-----------------------*/
   return unit_answer;
}



