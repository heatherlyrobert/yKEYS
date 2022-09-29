/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


tMY         myKEYS;



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
   fprintf (a_file, "error     %s¦", myKEYS.h_error);
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
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (FMOD_KEYS)) {
      DEBUG_YKEYS   yLOG_note    ("status is not ready for init");
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   myKEYS.c_env       =  '-';
   myKEYS.c_draw      = NULL;
   myKEYS.c_input     = NULL;
   myKEYS.c_altinput  = NULL;
   myKEYS.c_max_loop  =    0;
   /*---(sub-inits)----------------------*/
   rc = ykeys_logger_init    ();
   rc = ykeys_repeat_init    ();
   rc = ykeys_loop_init      ();
   rc = ykeys_progress_init  ();
   rc = ykeys_scale_init     ();
   rc = ykeys_speed_init     ();
   /*---(other updates)------------------*/
   rc = yFILE_dump_add ("keys"      , "", "log of keystrokes"           , ykeys_dump         );
   /*---(update status)------------------*/
   DEBUG_YKEYS   yLOG_note    ("update status");
   yMODE_init_set   (FMOD_KEYS, NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_arg_handle        (int *i, char *a_arg, char *a_next)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =    1;
   char        x_used      =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS  yLOG_enter   (__FUNCTION__);
   /*---(pointer defense)----------------*/
   DEBUG_YKEYS  yLOG_point   ("i"         , i);
   --rce;  if (i         == NULL) {
      DEBUG_YKEYS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS  yLOG_value   ("i"         , *i);
   /*---(quick reset)--------------------*/
   if (*i <= 1) {
      DEBUG_YKEYS  yLOG_note    ("quick reset of before processing args");
      strlcpy (myKEYS.a_script, "", LEN_RECD);
      strlcpy (myKEYS.a_layout, "", LEN_LABEL);
      if (*i < 1) {
         DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(pointer defense)----------------*/
   DEBUG_YKEYS  yLOG_point   ("a_arg"     , a_arg);
   --rce;  if (a_arg     == NULL) {
      DEBUG_YKEYS  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS  yLOG_info    ("a_arg"     , a_arg);
   DEBUG_YKEYS  yLOG_point   ("a_next"    , a_next);
   if (a_next    != NULL) {
      ++n;
      DEBUG_YKEYS  yLOG_info    ("a_next"    , a_next);
   }
   DEBUG_YKEYS  yLOG_value   ("n"         , n);
   /*---(script running)-----------------*/
   --rce;  if (strcmp (a_arg, "--script"        ) == 0) {
      DEBUG_YKEYS  yLOG_note    ("found --script option");
      if (n < 2 || a_next [0] == '-') {
         DEBUG_YKEYS  yLOG_note    ("not provided script name as second argument");
         DEBUG_YKEYS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strlcpy (myKEYS.a_script, a_next, LEN_RECD);
      ++(*i);
      ++x_used;
      DEBUG_YKEYS  yLOG_info    ("a_script"  , myKEYS.a_script);
   }
   /*---(layout)-------------------------*/
   --rce;  if (strncmp (a_arg, "--layout-"   ,  9) == 0) {
      DEBUG_YKEYS  yLOG_note    ("found --layout option");
      strlcpy (myKEYS.a_layout, a_arg + 9, LEN_LABEL);
      ++(*i);
      ++x_used;
      DEBUG_YKEYS  yLOG_info    ("a_layout"  , myKEYS.a_layout);
   }
   /*---(status)-------------------------*/
   --rce;  if (strncmp (a_arg, "--status-"   ,  9) == 0) {
      DEBUG_YKEYS  yLOG_note    ("found --status option");
      strlcpy (myKEYS.a_status, a_arg + 9, LEN_LABEL);
      ++(*i);
      ++x_used;
      DEBUG_YKEYS  yLOG_info    ("a_status"  , myKEYS.a_status);
   }
   /*---(report-out)---------------------*/
   DEBUG_YKEYS  yLOG_value   ("x_used"    , x_used);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS  yLOG_exit    (__FUNCTION__);
   return x_used;
}

/*> else if (strncmp (a, "--formula-"          , 10) == 0)  PROG_layout_set ("cli", "formula"  , a + 10);   <* 
 *> else if (strncmp (a, "--command-"          , 10) == 0)  PROG_layout_set ("cli", "command"  , a + 10);   <* 
 *> else if (strncmp (a, "--function-list"     ,  9) == 0)  CALC_func_list  ();                             <*/



/*> /+---(locals)-----------+-----------+-+/                                                       <* 
 *> int         i           = 0;             /+ loop iterator -- arguments     +/                  <* 
 *> char       *a           = NULL;          /+ current argument               +/                  <* 
 *> int         len         = 0;             /+ argument length                +/                  <* 
 *> int         x_total     = 0;                                                                   <* 
 *> int         x_args      = 0;                                                                   <* 
 *> /+---(begin)--------------------------+/                                                       <* 
 *> DEBUG_TOPS   yLOG_enter   (__FUNCTION__);                                                      <* 
 *> /+---(process)------------------------+/                                                       <* 
 *> for (i = 1; i < a_argc; ++i) {                                                                 <* 
 *>    /+---(read)------------------------+/                                                       <* 
 *>    a   = a_argv [i];                                                                           <* 
 *>    len = strlen(a);                                                                            <* 
 *>    ++x_total;                                                                                  <* 
 *>    /+---(filter)----------------------+/                                                       <* 
 *>    if (a[0] == '@')  continue;                                                                 <* 
 *>    ++x_args;                                                                                   <* 
 *>    DEBUG_ARGS  yLOG_complex ("argument"  , "%2d of %2d, %s", i, a_argc, a);                    <* 
 *>    /+---(configuration)---------------+/                                                       <* 
 *>    if      (strcmp (a, "--nav"          ) == 0)    yVIKEYS_cmds_direct   (":nav show");        <* 
 *>    else if (strcmp (a, "--nonav"        ) == 0)    yVIKEYS_cmds_direct   (":nav hide");        <* 
 *>    else if (strcmp (a, "--progress"     ) == 0)    yVIKEYS_cmds_direct   (":progress show");   <* 
 *>    else if (strcmp (a, "--noprogress"   ) == 0)    yVIKEYS_cmds_direct   (":progress hide");   <* 
 *>    else if (strcmp (a, "--play"         ) == 0)    yVIKEYS_cmds_direct   (":play");            <* 
 *>    else if (strcmp (a, "--stop"         ) == 0)    yVIKEYS_cmds_direct   (":stop");            <* 
 *>    else if (strcmp (a, "--status"       ) == 0)    yVIKEYS_cmds_direct   (":status show");     <* 
 *>    else if (strcmp (a, "--nostatus"     ) == 0)    yVIKEYS_cmds_direct   (":status hide");     <* 
 *>    else if (strcmp (a, "--script"       ) == 0) {                                              <* 
 *>       DEBUG_TOPS   yLOG_note    ("found --script option");                                     <* 
 *>       if (i < a_argc)  strlcpy (myVIKEYS.m_script, a_argv [++i], LEN_DESC);                    <* 
 *>    }                                                                                           <* 
 *> }                                                                                              <* 
 *> DEBUG_TOPS   yLOG_info    ("m_script"  , myVIKEYS.m_script);                                   <* 
 *> /+---(complete)-----------------------+/                                                       <* 
 *> DEBUG_TOPS   yLOG_exit    (__FUNCTION__);                                                      <* 
 *> return 0;                                                                                      <* 
 *> }                                                                                              <*/

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
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   DEBUG_YKEYS   yLOG_schar   (a_env);
   DEBUG_YKEYS   yLOG_sint    (a_key);
   /*---(default)------------------------*/
   x_key = a_key;
   /*---(opengl)-------------------------*/
   if (a_env == 'g') {
      DEBUG_YKEYS   yLOG_snote   ("opengl");
      switch (x_key) {
      case  G_KEY_ENTER :
         DEBUG_YKEYS   yLOG_snote   ("fix ENTER");
         x_key = G_KEY_RETURN; /* X11 sends incorrently  */
         break;
      case  G_KEY_DEL   :
         DEBUG_YKEYS   yLOG_snote   ("fix DEL");
         x_key = G_KEY_BS;     /* X11 sends incorrectly  */
         break;
      }
      DEBUG_YKEYS   yLOG_sint    (x_key);
   }
   /*---(switch)-------------------------*/
   switch (x_key) {
   case  G_KEY_RETURN :
      DEBUG_YKEYS   yLOG_snote   ("encode RETURN");
      x_key = G_CHAR_RETURN;
      break;
   case  G_KEY_ESCAPE :
      DEBUG_YKEYS   yLOG_snote   ("encode ESCAPE");
      x_key = G_CHAR_ESCAPE;
      break;
   case  G_KEY_SPACE  :
      DEBUG_YKEYS   yLOG_snote   ("encode SPACE");
      x_key = G_CHAR_SPACE;
      break;
   case  G_KEY_BS     :
      DEBUG_YKEYS   yLOG_snote   ("encode BACKSPACE");
      x_key = G_CHAR_BS;
      break;
   case  G_KEY_DEL    :
      DEBUG_YKEYS   yLOG_snote   ("encode DELETE");
      x_key = G_CHAR_DEL;
      break;
   case  G_KEY_GROUP  :
      DEBUG_YKEYS   yLOG_snote   ("encode GROUP");
      x_key = G_CHAR_GROUP;
      break;
   case  G_KEY_FIELD  :
      DEBUG_YKEYS   yLOG_snote   ("encode FIELD");
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
   else if (x_key > 0 && x_key <  32)  x_key = 0;
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
   return x_key;
}

char
ykeys__string_prepare   (uchar *a_keys, uchar *a_out, int *a_len, int *a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YKEYS   yLOG_spoint  (a_keys);
   --rce;  if (a_keys == NULL) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_snote   (a_keys);
   DEBUG_YKEYS   yLOG_spoint  (a_out);
   --rce;  if (a_out  == NULL) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_spoint  (a_len);
   --rce;  if (a_len == NULL) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YKEYS   yLOG_spoint  (a_end);
   --rce;  if (a_end == NULL) {
      DEBUG_YKEYS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(transform)----------------------*/
   strlcpy    (a_out, a_keys  , LEN_RECD);
   strlencode (a_out, ySTR_MAX, LEN_RECD);
   *a_len = strlen (a_out);
   DEBUG_YKEYS   yLOG_sint    (*a_len);
   DEBUG_YKEYS   yLOG_snote   (a_out);
   /*---(endpoint)-----------------------*/
   *a_end = myKEYS.h_all + *a_len;
   DEBUG_YKEYS   yLOG_sint    (*a_end);
   /*---(place at end)-------------------*/
   myKEYS.h_curr = myKEYS.h_total;
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   DEBUG_YKEYS   yLOG_complex ("args"      , "%c, %p, %p, %p", a_env, a_key, a_str, n);
   /*---(defense)------------------------*/
   --rce;  if (a_key == NULL) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_str != NULL) {
      x_len = strlen (a_str);
      DEBUG_YKEYS   yLOG_complex ("a_str"     , "%2då%sæ", strlen (a_str), a_str);
   }
   /*---(get normal key)-----------------*/
   DEBUG_YKEYS   yLOG_complex ("pos"       , "%3dc, %3dt", myKEYS.h_curr, myKEYS.h_total);
   --rce;  IF_MACRO_OFF {
      if (a_str != NULL && n != NULL && myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_YKEYS   yLOG_note    ("taking in new key from string");
         DEBUG_YKEYS   yLOG_complex ("pos"       , "%3dn, %3d len", *n, x_len);
         if (*n < 0 || *n >= x_len) {
            *a_key = 0;
            DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         x_key = chrworking (a_str [*n]);
         x_key = ykeys__input_fix (a_env, x_key);
         ++(*n);
         x_source = 2;
      } else if (myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_YKEYS   yLOG_note    ("use new key");
         x_key = ykeys__input_fix (a_env, *a_key);
         x_source = 0;
      } else {
         DEBUG_YKEYS   yLOG_note    ("repeating older keys from log");
         x_key = myKEYS.h_log [myKEYS.h_curr];
         x_source = 1;
      }
   }
   /*---(get macro playback)-------------*/
   else IF_MACRO_PLAYBACK {
      DEBUG_YKEYS   yLOG_note    ("macro playback, get key, then call yMACRO");
      if (a_str != NULL && n != NULL && myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_YKEYS   yLOG_note    ("taking in playback key from string");
         DEBUG_YKEYS   yLOG_complex ("pos"       , "%3dn, %3d len", *n, x_len);
         if (*n < 0 || *n >= x_len) {
            *a_key = 0;
            DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         x_key = chrworking (a_str [*n]);
         x_key = ykeys__input_fix (a_env, x_key);
         ++(*n);
         x_source = 3;
      } else {
         DEBUG_YKEYS   yLOG_note    ("no new playback keys, just wait");
         *a_key = 0;
         DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_key = yMACRO_exec  (x_key);
      x_source = 4;
   }
   /*---(get macro execution)------------*/
   else {
      DEBUG_YKEYS   yLOG_note    ("macro execution, call yMACRO");
      x_key = yMACRO_exec  (*a_key);
      x_source = 5;
   }
   /*---(double cleanse controls)--------*/
   DEBUG_YKEYS   yLOG_complex ("x_key"     , "%ds, %3d, %c", x_source, x_key, chrvisible (x_key));
   /*> if (x_key > 0 && x_key < 32) {                                                 <* 
    *>    if      (x_key == G_KEY_ESCAPE)  ;                                          <* 
    *>    else if (x_key == G_KEY_RETURN)  ;                                          <* 
    *>    else     x_key = 0;                                                         <* 
    *> }                                                                              <*/
   /*---(logger)-------------------------*/
   rc = yKEYS_logger (x_key);
   DEBUG_YKEYS   yLOG_value   ("logger"    , rc);
   /*---(check unlock)-------------------*/
   rc = yKEYS_check_unlock (&x_key);
   DEBUG_YKEYS   yLOG_value   ("unlock"    , rc);
   /*---(save-back)----------------------*/
   DEBUG_YKEYS   yLOG_value   ("x_source"  , x_source);
   *a_key = x_key;
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
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
         DEBUG_YKEYS   yLOG_complex ("normal"    , "%3d, %c, %4d", a_key, chrvisible (a_key), rc);
      } else {
         DEBUG_YKEYS   yLOG_complex ("error"     , "%3d, %c, %4d", a_key, chrvisible (a_key), rc);
         if (a_error != NULL)  *a_error += 1;
      }
   } else {
      DEBUG_YKEYS   yLOG_complex ("skipped"   , "%3d, %c", a_key, chrvisible (a_key));
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
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ykeys__string_prepare (a_keys, x_keys, &x_len, &x_end);
   DEBUG_YKEYS   yLOG_value   ("prepare"   , rc);
   if (rc < 0) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(walk characters)----------------*/
   DEBUG_YKEYS   yLOG_complex ("position"  , "%3dn, %3de", n, x_end);
   while (n < x_end || yMACRO_exe_mode () != MACRO_STOP) {
      /*---(get next char)---------------*/
      rc = ykeys__input ('-', &x_key, x_keys, &n);
      DEBUG_YKEYS   yLOG_value   ("input"     , rc);
      if (rc < 0)  break;
      /*---(handle keystroke)------------*/
      rc = ykeys__handle (x_key, &x_error);
      DEBUG_YKEYS   yLOG_value   ("handle"    , rc);
      if (rc < 0)  ++x_error;
      /*---(refresh maps)----------------*/
      rc = yMAP_refresh ();
      DEBUG_YKEYS   yLOG_value   ("refresh"   , rc);
      /*---(next)------------------------*/
      IF_MACRO_NOT_PLAYING   yKEYS_nextpos ();
      /*> else {                                                                      <* 
       *>    if (n == x_end)   --n;                                                   <* 
       *> }                                                                           <*/
      DEBUG_YKEYS   yLOG_complex ("position"  , "%3dn, %3de", n, x_end);
      /*---(done)------------------------*/
   }
   DEBUG_YKEYS   yLOG_note    ("main loop done");
   if (x_error < -99)  x_error = -99;
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return x_error;
}

char
ykeys__prepare          (char *a_delay, char *a_update, int a_loops, char a_env, void *a_draw, void *a_input, void *a_altinput)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   myKEYS.c_env      = '-';
   myKEYS.c_draw     = NULL;
   myKEYS.c_input    = NULL;
   myKEYS.c_altinput = NULL;
   myKEYS.c_max_loop = 0;
   /*---(timing)-------------------------*/
   rc = yKEYS_loop_set     (a_delay, a_update);
   DEBUG_YKEYS   yLOG_value   ("loop_set"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(loops)--------------------------*/
   DEBUG_YKEYS   yLOG_value   ("a_loops"   , a_loops);
   if (a_loops > 0)  myKEYS.c_max_loop = a_loops;
   /*---(environment)--------------------*/
   DEBUG_YKEYS   yLOG_char    ("a_env"     , a_env);
   --rce;  if (a_env == 0 || strchr ("gc", a_env) == NULL) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myKEYS.c_env      = a_env;
   /*---(draw)---------------------------*/
   DEBUG_YKEYS   yLOG_point   ("a_draw"    , a_draw);
   --rce;  if (a_draw == NULL) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myKEYS.c_draw     = a_draw;
   /*---(input)--------------------------*/
   DEBUG_YKEYS   yLOG_point   ("a_input"   , a_input);
   --rce;  if (a_input == NULL) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myKEYS.c_input    = a_input;
   /*---(alt-input)----------------------*/
   DEBUG_YKEYS   yLOG_point   ("a_altinput", a_altinput);
   myKEYS.c_altinput = a_altinput;
   /*---(initial mapping)----------------*/
   rc = yMAP_refresh_full ();
   DEBUG_YKEYS   yLOG_value   ("refresh"   , rc);
   /*---(run drawer)---------------------*/
   rc = myKEYS.c_draw (0.0);
   DEBUG_YKEYS   yLOG_value   ("drawing"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yKEYS_quit        (void) { myKEYS.done = 'y'; }
char yKEYS_writequit   (void) { myKEYS.done = 'y'; }
char yKEYS_writequitall(void) { myKEYS.done = 'y'; }
char ykeys_quitting    (void) { if (myKEYS.done    == 'y') return 1; return 0; }

char
ykeys__premain          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        t           [LEN_DESC]  = "";
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(CLA for script)-----------------*/
   DEBUG_YKEYS   yLOG_info    ("a_script"  , myKEYS.a_script);
   if (strcmp (myKEYS.a_script, "") != 0) {
      DEBUG_YKEYS   yLOG_note    ("command line script argument");
      sprintf (t, ":script %s", myKEYS.a_script);
      DEBUG_YKEYS   yLOG_info    ("t"         , t);
      rc = yCMD_direct (t);
      DEBUG_YKEYS   yLOG_value   ("cmds"      , rc);
   }
   /*---(CLA for layout)-----------------*/
   DEBUG_YKEYS   yLOG_info    ("a_layout"  , myKEYS.a_layout);
   if (strcmp (myKEYS.a_layout, "") != 0) {
      DEBUG_YKEYS   yLOG_note    ("command line layout argument");
      sprintf (t, ":layout %s", myKEYS.a_layout);
      DEBUG_YKEYS   yLOG_info    ("t"         , t);
      rc = yCMD_direct (t);
      DEBUG_YKEYS   yLOG_value   ("cmds"      , rc);
   }
   /*---(CLA for status)-----------------*/
   DEBUG_YKEYS   yLOG_info    ("a_status"  , myKEYS.a_status);
   if (strcmp (myKEYS.a_status, "") != 0) {
      DEBUG_YKEYS   yLOG_note    ("command line status argument");
      sprintf (t, ":status %s", myKEYS.a_status);
      DEBUG_YKEYS   yLOG_info    ("t"         , t);
      rc = yCMD_direct (t);
      DEBUG_YKEYS   yLOG_value   ("cmds"      , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

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
   char        x_block     =  '-';
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_break   ();
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ykeys__prepare (a_delay, a_update, a_loops, a_env, a_draw, a_input, a_altinput);
   DEBUG_YKEYS   yLOG_value   ("loop_set"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(command line args)--------------*/
   rc = ykeys__premain ();
   /*---(main-loop)----------------------*/
   while (1) {
      DEBUG_YKEYS  yLOG_value   ("LOOP"      , myKEYS.loops);
      /*---(start loop)------------------*/
      yKEYS_loop_beg   ();
      /*---(alternate input)-------------*/
      DEBUG_YKEYS  yLOG_point   ("c_altinput", myKEYS.c_altinput);
      if (myKEYS.c_altinput != NULL) {
         rc = myKEYS.c_altinput ();
         DEBUG_YKEYS  yLOG_value   ("altinput"  , rc);
      }
      /*---(get input)-------------------*/
      IF_MACRO_PLAYING   x_block = '-';
      else               x_block = myKEYS.l_blocking;
      DEBUG_YKEYS  yLOG_complex ("blocking"  , "%c, %c", myKEYS.l_blocking, x_block);
      rc = myKEYS.c_input (x_block, &x_key);
      DEBUG_YKEYS  yLOG_complex ("input"     , "%-4d, %d, %c", rc, x_key, chrvisible (x_key));
      /*---(keyboard input)--------------*/
      rc = ykeys__input (myKEYS.c_env, &x_key, NULL, NULL);
      DEBUG_YKEYS  yLOG_complex ("input_adj" , "%-4d, %d, %c", rc, x_key, chrvisible (x_key));
      if (x_key == G_KEY_SKIP) {
         DEBUG_YKEYS   yLOG_note    ("non-action key, do not wait or update screen");
         continue;
      }
      /*---(handle keystroke)------------*/
      if (x_key != G_KEY_NOOP) {
         rc = ykeys__handle (x_key, NULL);
         DEBUG_YKEYS   yLOG_value   ("handle"    , rc);
      }
      /*---(refresh maps)----------------*/
      rc = yMAP_refresh ();
      DEBUG_YKEYS   yLOG_value   ("refresh"   , rc);
      /*---(exiting)---------------------*/
      ++myKEYS.loops;
      if (ykeys_quitting ()) {
         DEBUG_YKEYS   yLOG_note    ("user requested quitting");
         break;
      }
      if (myKEYS.c_max_loop > 0 && myKEYS.loops >= myKEYS.c_max_loop) {
         DEBUG_YKEYS   yLOG_note    ("hit max loops, stopping");
         break;
      }
      /*---(next)------------------------*/
      IF_MACRO_NOT_PLAYING   yKEYS_nextpos ();
      /*---(showing)---------------------*/
      x_draw = '-';
      if ((myKEYS.loops % myKEYS.l_loops) == 0) {
         x_draw = 'y';
         yKEYS_loop_graf  ();
         ykeys_loop_prog  ();
         rc = myKEYS.c_draw (0.0);
         DEBUG_YKEYS   yLOG_value   ("drawing"   , rc);
      }
      /*---(sleeping)--------------------*/
      ykeys_loop_sleep (x_key, x_draw);
      /*---(done)------------------------*/
   }
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   DEBUG_YKEYS  yLOG_break   ();
   /*---(complete)-----------------------*/
   return 0;
}




