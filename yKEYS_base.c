/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


tMY         myKEYS;

#define     NSEC        1000000000
#define     NSEC2USEC   1000
#define     NSEC2MSEC   1000000
#define     NSEC2SEC    1000000000

static   char s_print   [LEN_RECD]  = "";


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
   /*---(hook to yVIHUB)-----------------*/
   yVIHUB_from_yKEYS (yKEYS_init, yKEYS_quit, yKEYS_set_warning, yKEYS_check_repeat, yKEYS_repeat_umode, yKEYS_group_hmode, yKEYS_repeat_check);
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
   /*---(update status)------------------*/
   DEBUG_YKEYS   yLOG_note    ("update status");
   yMODE_init_set   (FMOD_KEYS, NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_init_after        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(other updates)------------------*/
   rc = yVIHUB_yFILE_dump_add ("keys"      , "", "log of keystrokes"           , ykeys_dump         );
   DEBUG_YMODE   yLOG_value   ("dump_add"  , rc);
   rc = yVIHUB_yVIEW_switch_add ('s', "key"   , "keylog"       , yKEYS_keylog_status    , "displays keystroke history"               );
   DEBUG_YMODE   yLOG_value   ("switch_add", rc);
   rc = yVIHUB_yVIEW_switch_add ('s', "log"   , "logger"       , yKEYS_logger_status    , "displays logging statistics"              );
   DEBUG_YMODE   yLOG_value   ("switch_add", rc);
   rc = yVIHUB_yVIEW_switch_add ('s', "loo"   , "loop"         , yKEYS_loop_status      , "displays main looping statistics"         );
   DEBUG_YMODE   yLOG_value   ("switch_add", rc);
   rc = yVIHUB_yVIEW_switch_add ('s', "repl"  , "replay"       , yKEYS_replay_status    , "displays main looping statistics"         );
   DEBUG_YMODE   yLOG_value   ("switch_add", rc);
   yMODE_after_set  (FMOD_KEYS);
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yKEYS_reinit            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(resets)-------------------------*/
   rc = ykeys_logger_init    ();
   rc = ykeys_repeat_init    ();
   rc = ykeys_loop_init      ();
   rc = ykeys_progress_init  ();
   rc = ykeys_scale_init     ();
   rc = ykeys_speed_init     ();
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
   char        t           [LEN_LABEL] = "";
   char       *x_valid     = " --script --playback --follow --rapido --blitz ";
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
      myKEYS.a_style  = '-';
      ystrlcpy (myKEYS.a_script, "", LEN_RECD);
      ystrlcpy (myKEYS.a_layout, "", LEN_LABEL);
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
   snprintf (t, " %s ", a_arg);
   --rce;  if (strstr (x_valid, t) != NULL) {
      DEBUG_YKEYS  yLOG_note    ("found script running option");
      if (n < 2 || a_next [0] == '-') {
         DEBUG_YKEYS  yLOG_note    ("not provided script name as second argument");
         DEBUG_YKEYS  yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      switch (a_arg [2]) {
      case 's' :  myKEYS.a_style = '.';   break;
      case 'p' :  myKEYS.a_style = ',';   break;
      case 'f' :  myKEYS.a_style = '!';   break;
      case 'r' :  myKEYS.a_style = '>';   break;
      case 'b' :  myKEYS.a_style = '¬';   break;
      }
      DEBUG_YKEYS  yLOG_char    ("a_style"   , myKEYS.a_style);
      ystrlcpy (myKEYS.a_script, a_next, LEN_RECD);
      ++(*i);
      ++x_used;
      DEBUG_YKEYS  yLOG_info    ("a_script"  , myKEYS.a_script);
   }
   /*---(layout)-------------------------*/
   --rce;  if (strncmp (a_arg, "--layout-"   ,  9) == 0) {
      DEBUG_YKEYS  yLOG_note    ("found --layout option");
      ystrlcpy (myKEYS.a_layout, a_arg + 9, LEN_LABEL);
      ++(*i);
      ++x_used;
      DEBUG_YKEYS  yLOG_info    ("a_layout"  , myKEYS.a_layout);
   }
   /*---(status)-------------------------*/
   --rce;  if (strncmp (a_arg, "--status-"   ,  9) == 0) {
      DEBUG_YKEYS  yLOG_note    ("found --status option");
      ystrlcpy (myKEYS.a_status, a_arg + 9, LEN_LABEL);
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
 *>       if (i < a_argc)  ystrlcpy (myVIKEYS.m_script, a_argv [++i], LEN_DESC);                    <* 
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
   /*---(opengl)-------------------------*/
   if (a_env == 'c') {
      DEBUG_YKEYS   yLOG_snote   ("curses");
      switch (x_key) {
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
   case G_KEY_NOOP     :
      DEBUG_YKEYS   yLOG_snote   ("handle G_KEY_NOOP");
      ++myKEYS.h_noops;
      break;
   case 1              :
      yKEYS_set_skip ();
      x_key = 0;
      break;
   case G_KEY_SKIP     :
      DEBUG_YKEYS   yLOG_snote   ("handle G_KEY_SKIP");
      ++myKEYS.h_acks;
      break;
   case G_CHAR_SPACE   : case G_CHAR_STORAGE :
      DEBUG_YKEYS   yLOG_snote   ("handle G_KEY_SPACE, G_KEY_STORAGE");
      ++myKEYS.h_spaces;
      break;
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
   ystrlcpy    (a_out, a_keys  , LEN_RECD);
   ystrlencode (a_out, ySTR_MAX, LEN_RECD);
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
   DEBUG_YKEYS   yLOG_complex ("*a_key"    , "%3d, %c", *a_key, ychrvisible (*a_key));
   if (a_str != NULL) {
      x_len = strlen (a_str);
      DEBUG_YKEYS   yLOG_complex ("a_str"     , "%2då%sæ", strlen (a_str), a_str);
      if (n != NULL) {
         DEBUG_YKEYS   yLOG_value   ("*n"        , *n);
      }
   }
   /*---(get normal key)-----------------*/
   DEBUG_YKEYS   yLOG_complex ("hist pos"  , "%3dc, %3dt", myKEYS.h_curr, myKEYS.h_total);
   --rce;  IF_MACRO_OFF {
      if (a_str != NULL && n != NULL && myKEYS.h_curr >= myKEYS.h_total) {
         DEBUG_YKEYS   yLOG_note    ("taking in new key from string");
         DEBUG_YKEYS   yLOG_complex ("string pos", "%3dn, %3d len", *n, x_len);
         if (*n < 0 || *n >= x_len) {
            *a_key = 0;
            DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         x_key = ychrworking (a_str [*n]);
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
         DEBUG_YKEYS   yLOG_complex ("string pos", "%3dn, %3d len", *n, x_len);
         if (*n < 0 || *n >= x_len) {
            *a_key = 0;
            DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         x_key = ychrworking (a_str [*n]);
         x_key = ykeys__input_fix (a_env, x_key); ++(*n);
         x_source = 3;
      } else {
         DEBUG_YKEYS   yLOG_note    ("no new playback keys, just wait");
         *a_key = 0;
         DEBUG_YKEYS   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_key = yVIHUB_yMACRO_exec  (x_key);
      x_source = 4;
   }
   /*---(get macro execution)------------*/
   else {
      DEBUG_YKEYS   yLOG_note    ("macro execution, call yMACRO");
      if (a_str == NULL)    x_key = yVIHUB_yMACRO_exec  (*a_key);
      else                  x_key = yVIHUB_yMACRO_exec  (0);
      switch (x_key) {
      case G_KEY_NOOP     :
         DEBUG_YKEYS   yLOG_snote   ("handle G_KEY_NOOP");
         ++myKEYS.h_mnoops;
         break;
      case G_KEY_SKIP     :
         DEBUG_YKEYS   yLOG_snote   ("handle G_KEY_SKIP");
         ++myKEYS.h_macks;
         break;
      }
      x_source = 5;
   }
   /*---(double cleanse controls)--------*/
   DEBUG_YKEYS   yLOG_complex ("x_key"     , "%ds, %3d, %c", x_source, x_key, ychrvisible (x_key));
   /*> if (x_key > 0 && x_key < 32) {                                                 <* 
    *>    if      (x_key == G_KEY_ESCAPE)  ;                                          <* 
    *>    else if (x_key == G_KEY_RETURN)  ;                                          <* 
    *>    else     x_key = 0;                                                         <* 
    *> }                                                                              <*/
   /*---(logger)-------------------------*/
   DEBUG_YKEYS   yLOG_complex ("hist pos"  , "%3dc, %3dt", myKEYS.h_curr, myKEYS.h_total);
   rc = yKEYS_logger (x_key);
   DEBUG_YKEYS   yLOG_value   ("logger"    , rc);
   DEBUG_YKEYS   yLOG_complex ("hist pos"  , "%3dc, %3dt", myKEYS.h_curr, myKEYS.h_total);
   /*---(check unlock)-------------------*/
   rc = yKEYS_check_unlock (&x_key);
   DEBUG_YKEYS   yLOG_value   ("unlock"    , rc);
   /*---(save-back)----------------------*/
   DEBUG_YKEYS   yLOG_value   ("x_source"  , x_source);
   *a_key = x_key;
   DEBUG_YKEYS   yLOG_complex ("hist pos"  , "%3dc, %3dt", myKEYS.h_curr, myKEYS.h_total);
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
         DEBUG_YKEYS   yLOG_complex ("normal"    , "%3d, %c, %4d", a_key, ychrvisible (a_key), rc);
      } else {
         DEBUG_YKEYS   yLOG_complex ("error"     , "%3d, %c, %4d", a_key, ychrvisible (a_key), rc);
         if (a_error != NULL)  *a_error += 1;
      }
   } else {
      DEBUG_YKEYS   yLOG_complex ("skipped"   , "%3d, %c", a_key, ychrvisible (a_key));
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
   /*> n = x_end - x_len;                                                             <*/
   DEBUG_YKEYS   yLOG_complex ("position"  , "%3dn, %3dl, %3de", n, x_len, x_end);
   while (n < x_end || yVIHUB_yMACRO_exe_mode ("play") == 1) {
      DEBUG_YKEYS   yLOG_char    ("rec_mode"  , yVIHUB_yMACRO_rec_mode ("show"));
      DEBUG_YKEYS   yLOG_char    ("exe_mode"  , yVIHUB_yMACRO_exe_mode ("show"));
      /*---(get next char)---------------*/
      rc = ykeys__input ('-', &x_key, x_keys, &n);
      DEBUG_YKEYS   yLOG_value   ("input"     , rc);
      if (rc < 0)  break;
      /*---(handle keystroke)------------*/
      rc = ykeys__handle (x_key, &x_error);
      DEBUG_YKEYS   yLOG_value   ("handle"    , rc);
      if (rc < 0)  ++x_error;
      /*---(refresh maps)----------------*/
      rc = yVIHUB_yMAP_refresh ();
      DEBUG_YKEYS   yLOG_value   ("refresh"   , rc);
      /*---(next)------------------------*/
      DEBUG_YKEYS   yLOG_char    ("notplay"   , yVIHUB_yMACRO_exe_mode ("notplaying"));
      IF_MACRO_NOT_PLAYING   yKEYS_nextpos ();
      DEBUG_YKEYS   yLOG_complex ("position"  , "%3dn, %3dl, %3de", n, x_len, x_end);
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
   rc = yVIHUB_yMAP_refresh_full ();
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
      switch (myKEYS.a_style) {
      case '.' :   sprintf (t, ":script   %s", myKEYS.a_script);  break;
      case ',' :   sprintf (t, ":playback %s", myKEYS.a_script);  break;
      case '!' :   sprintf (t, ":follow   %s", myKEYS.a_script);  break;
      case '>' :   sprintf (t, ":rapido   %s", myKEYS.a_script);  break;
      case '¬' :   sprintf (t, ":blitz    %s", myKEYS.a_script);  break;
      }
      DEBUG_YKEYS   yLOG_info    ("t"         , t);
      rc = yVIHUB_yCMD_direct (t);
      DEBUG_YKEYS   yLOG_value   ("cmds"      , rc);
   }
   /*---(CLA for layout)-----------------*/
   DEBUG_YKEYS   yLOG_info    ("a_layout"  , myKEYS.a_layout);
   if (strcmp (myKEYS.a_layout, "") != 0) {
      DEBUG_YKEYS   yLOG_note    ("command line layout argument");
      sprintf (t, ":layout %s", myKEYS.a_layout);
      DEBUG_YKEYS   yLOG_info    ("t"         , t);
      rc = yVIHUB_yCMD_direct (t);
      DEBUG_YKEYS   yLOG_value   ("cmds"      , rc);
   }
   /*---(CLA for status)-----------------*/
   DEBUG_YKEYS   yLOG_info    ("a_status"  , myKEYS.a_status);
   if (strcmp (myKEYS.a_status, "") != 0) {
      DEBUG_YKEYS   yLOG_note    ("command line status argument");
      sprintf (t, ":status %s", myKEYS.a_status);
      DEBUG_YKEYS   yLOG_info    ("t"         , t);
      rc = yVIHUB_yCMD_direct (t);
      DEBUG_YKEYS   yLOG_value   ("cmds"      , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return 0;
}

uchar
ykeys__handler          (char a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char        x_one       =  '·';
   char        x_two       =  '·';
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(if control key)--------------*/
   switch (a_key) {
   case  14 : x_one = 'g'; x_two = 'T'; rc = 1; break;
   case  15 : x_one = 'g'; x_two = 'B'; rc = 1; break;
   case  16 : x_one = 'g'; x_two = 'S'; rc = 1; break;
   case  17 : x_one = 'g'; x_two = 'E'; rc = 1; break;
   default :
   }
   /*---(handle control)--------------*/
   if (rc == 1) {
      DEBUG_YKEYS   yLOG_note    ("handling special paging keys");
      rc = yKEYS_logger  (x_one);
      rc = ykeys__handle (x_one, NULL);
      rc = yKEYS_logger  (x_two);
      rc = ykeys__handle (x_two, NULL);
   }
   /*---(handle normal)---------------*/
   else {
      DEBUG_YKEYS   yLOG_note    ("handling normal keys");
      /*---(keyboard input)--------------*/
      rc = ykeys__input (myKEYS.c_env, &a_key, NULL, NULL);
      DEBUG_YKEYS  yLOG_complex ("input_adj" , "%-4d, %d, %c", rc, a_key, ychrvisible (a_key));
      /*---(non-action)------------------*/
      if (a_key == G_KEY_NOOP) {
         DEBUG_YKEYS   yLOG_note    ("non-action key, do not wait or update screen");
      }
      /*---(skip/delay)------------------*/
      else if (a_key == G_KEY_SKIP) {
         DEBUG_YKEYS   yLOG_note    ("skip/delay key, do not wait or update screen");
      }
      /*---(handle keystroke)------------*/
      else if (a_key != G_KEY_NOOP) {
         DEBUG_YKEYS   yLOG_note    ("real-key, not SKIP or NOOP");
         rc = ykeys__handle (a_key, NULL);
         DEBUG_YKEYS   yLOG_value   ("handle"    , rc);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   return a_key;
}

char
ykeys_main_beg          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTSPEC      x_dur;
   /*---(reset timing);------------------*/
   myKEYS.m_beg   = 0;
   myKEYS.m_end   = 0;
   /*---(get beginning time)-------------*/
   clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);
   myKEYS.m_beg   = x_dur.tv_sec * NSEC;
   myKEYS.m_beg  += x_dur.tv_nsec;
   /*---(complete)-----------------------*/
   return 0;
}

char
ykeys_main_end          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tTSPEC      x_dur;
   /*---(get beginning time)-------------*/
   clock_gettime  (CLOCK_MONOTONIC_RAW, &x_dur);
   myKEYS.m_end   = x_dur.tv_sec * NSEC;
   myKEYS.m_end  += x_dur.tv_nsec;
   myKEYS.m_dur   = myKEYS.m_end - myKEYS.m_beg;
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> handle main loop for ncurses -------[ ------ [gn.842.232.99]*/ /*-[01.0000.000.!]-*/ /*-[--.---.---.--]-*/
yKEYS_main              (char *a_delay, char *a_update, int a_loops, char a_env, void *a_draw, void *a_input, void *a_altinput)
{  /*---(note)---------------------------*/
   /*
    *  10ms update = 101ms for 10 loops (not sure where the 1ms extra is ;))
    *  then, the last loop is without delay/sleep after, so minus 10ms
    *
    *  10 loops = 90ms    (101 * 1) - 10
    *  30 loops = 293ms   (101 * 3) - 10
    *
    *
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_temp      =    0;
   int         x_ch        =  ' ';
   uchar       x_key       =  ' ';
   char        x_draw      =  '-';
   char        t           [LEN_DESC]  = "";
   char        x_block     =  '-';
   uchar       x_final      = ' ';
   /*---(header)-------------------------*/
   DEBUG_YKEYS   yLOG_break   ();
   DEBUG_YKEYS   yLOG_enter   (__FUNCTION__);
   /*---(start timer)--------------------*/
   ykeys_main_beg ();
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
      /*---(start timer)-----------------*/
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
      DEBUG_YKEYS  yLOG_complex ("input"     , "%-4d, %d, %c", rc, x_key, ychrvisible (x_key));
      /*---(if control key)--------------*/
      x_final = ykeys__handler (x_key);
      DEBUG_YKEYS   yLOG_complex ("handler"   , "%4dl, %4d/%c, %4dn, %4da, %4dmn, %4dma, %4dh, %4de", myKEYS.loops, x_final, ychrvisible (x_final), myKEYS.h_noops, myKEYS.h_acks, myKEYS.h_mnoops, myKEYS.h_macks, myKEYS.h_total, myKEYS.e_total);
      /*---(refresh maps)----------------*/
      rc = yVIHUB_yMAP_refresh ();
      DEBUG_YKEYS   yLOG_value   ("refresh"   , rc);
      /*---(loop counter)----------------*/
      ++myKEYS.loops;
      /*---(exiting)---------------------*/
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
      ykeys_loop_sleep (x_final, x_draw);
      /*---(done)------------------------*/
   }
   /*---(end timer)----------------------*/
   ykeys_main_end ();
   /*---(complete)-----------------------*/
   DEBUG_YKEYS   yLOG_exit    (__FUNCTION__);
   DEBUG_YKEYS  yLOG_break   ();
   return 0;
}

char
yKEYS__unit_main        (char *a_delay, char *a_update, int a_loops, char a_env, char *a_keys)
{
   yKEYS_reinit ();
   ykeys__unit_prep (a_keys);
   return yKEYS_main (a_delay, a_update, a_loops, a_env, ykeys__unit_draw, ykeys__unit_input, ykeys__unit_altinput);
}

/*> char*                                                                             <* 
 *> yKEYS_main_dur_nsec     (llong *r_beg, llong *r_end, llong *r_dur)                <* 
 *> {                                                                                 <* 
 *>    strcpy (s_print, "");                                                          <* 
 *>    if (r_beg != NULL)  *r_beg = myMACRO.m_beg;                                    <* 
 *>    if (r_end != NULL)  *r_end = myMACRO.m_end;                                    <* 
 *>    if (r_dur != NULL)  *r_dur = myMACRO.m_dur;                                    <* 
 *>    return s_print;                                                                <* 
 *> }                                                                                 <*/

char*
yKEYS_main_dur_usec     (int *r_beg, int *r_end, int *r_dur, int *r_loop, int *r_draw, int *r_keys)
{
   int         x_beg       = myKEYS.m_beg / NSEC2USEC;
   int         x_end       = myKEYS.m_end / NSEC2USEC;
   int         x_dur       = myKEYS.m_dur / NSEC2USEC;
   strcpy (s_print, "");
   if (r_beg  != NULL)  *r_beg  = x_beg;
   if (r_end  != NULL)  *r_end  = x_end;
   if (r_dur  != NULL)  *r_dur  = x_dur;
   sprintf (s_print, "KEYS run usec    : %10.10db  %10.10de  %10.10dd   %10.10dl  %10.10dd  %10.10dk", x_beg, x_end, x_dur, myKEYS.loops, myKEYS.l_draw, myKEYS.l_keys);
   if (r_loop != NULL)  *r_loop = myKEYS.loops;
   if (r_draw != NULL)  *r_draw = myKEYS.l_draw;
   if (r_keys != NULL)  *r_keys = myKEYS.l_keys;
   return s_print;
}

char*
yKEYS_main_dur_msec     (int *r_beg, int *r_end, int *r_dur, int *r_loop, int *r_draw, int *r_keys)
{
   int         x_beg       = myKEYS.m_beg / NSEC2MSEC;
   int         x_end       = myKEYS.m_end / NSEC2MSEC;
   int         x_dur       = myKEYS.m_dur / NSEC2MSEC;
   strcpy (s_print, "");
   if (r_beg  != NULL)  *r_beg  = x_beg;
   if (r_end  != NULL)  *r_end  = x_end;
   if (r_dur  != NULL)  *r_dur  = x_dur;
   sprintf (s_print, "KEYS run msec    : %6dd   all (%3dl %3dg %3dk)   ops (%3dn %3da %3dk)   mac (%3dn %3da %3dk)", x_dur, myKEYS.loops, myKEYS.l_draw, myKEYS.e_all, myKEYS.h_noops, myKEYS.h_acks, myKEYS.h_all, myKEYS.h_mnoops, myKEYS.h_macks, myKEYS.e_all - myKEYS.h_all);
   if (r_loop != NULL)  *r_loop = myKEYS.loops;
   if (r_draw != NULL)  *r_draw = myKEYS.l_draw;
   if (r_keys != NULL)  *r_keys = myKEYS.h_total;
   return s_print;
}




