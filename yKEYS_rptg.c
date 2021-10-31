/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"

char*
yKEYS_last              (void)
{
   sprintf (myKEYS.h_last, "(%c) %c", myKEYS.h_mode [myKEYS.h_total - 1], myKEYS.h_log [myKEYS.h_total - 1]);
   return myKEYS.h_last;
}

char
ykeys_num2str           (int a_val, char a_len, char *a_out)
{
   int         i           =    0;
   int         x_max       =    0;
   char        t           [LEN_LABEL] = "";
   /*---(max limit)----------------------*/
   for (i = 0; i < a_len; ++i)  x_max = (x_max * 10) + 9;
   if (a_val < 0)      a_val = 0;
   if (a_val > x_max)  a_val = x_max;
   /*---(print and fill)-----------------*/
   sprintf (t, "%d", a_val);
   strlpad (t, a_out, '.', '>', a_len);
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_logger_status     (char a_size, short a_wide, char *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   short       w;
   short       h;
   uchar       x_grand     [LEN_TERSE] = "";
   uchar       x_all       [LEN_TERSE] = "";
   uchar       x_total     [LEN_TERSE] = "";
   uchar       x_curr      [LEN_TERSE] = "";
   uchar       x_error     [LEN_TERSE] = "";
   uchar       x_warn      [LEN_TERSE] = "";
   uchar       x_skip      [LEN_TERSE] = "";
   uchar       x_ack       [LEN_TERSE] = "";
   uchar       x_space     [LEN_TERSE] = "";
   uchar       x_noop      [LEN_TERSE] = "";
   uchar       x_combo     [LEN_TERSE] = "";
   uchar       x_open      [LEN_TERSE] = "";
   uchar       x_close     [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   if (a_size == '-') { /* no adapt option */
      if      (a_wide <  20)  a_size = 'u';
      else if (a_wide <  40)  a_size = 't';
      else if (a_wide <  70)  a_size = 's';
      else if (a_wide < 110)  a_size = 'm';
      else if (a_wide < 160)  a_size = 'l';
      else if (a_wide < 220)  a_size = 'h';
      else                    a_size = 'g';
   }
   /*---(prepare)------------------------*/
   ykeys_num2str (myKEYS.h_grand   , 4, x_grand);
   ykeys_num2str (myKEYS.h_all     , 4, x_all);
   ykeys_num2str (myKEYS.h_total   , 3, x_total);
   ykeys_num2str (myKEYS.h_curr    , 3, x_curr);
   ykeys_num2str (myKEYS.h_errors  , 2, x_error);
   ykeys_num2str (myKEYS.h_warnings, 2, x_warn);
   ykeys_num2str (myKEYS.h_skips   , 2, x_skip);
   ykeys_num2str (myKEYS.h_acks    , 3, x_ack);
   ykeys_num2str (myKEYS.h_spaces  , 3, x_space);
   ykeys_num2str (myKEYS.h_noops   , 3, x_noop);
   ykeys_num2str (myKEYS.h_combos  , 3, x_combo);
   ykeys_num2str (myKEYS.h_open    , 2, x_open);
   ykeys_num2str (myKEYS.h_close   , 2, x_close);
   /*---(make)---------------------------*/
   switch (a_size) {
   case 'u' :
      sprintf (a_list, "log %3s %c´", x_total, myKEYS.h_logkeys);
      break;
   case 't' :
      sprintf (a_list, "log %4sg %3st %c %c ´", x_grand, x_total, myKEYS.h_logkeys, myKEYS.h_locked);
      break;
   case 's' :
      sprintf (a_list, "logger  %4sg %4sa %3st %c %3sc %c %2se %c´",
            x_grand, x_all, x_total, myKEYS.h_logkeys,
            x_curr , myKEYS.h_used,
            x_error, myKEYS.h_locked);
      break;
   case 'm' :
      sprintf (a_list, "logger  %4sg %4sa %3st %c %3sc %c %2se %2sw %2ss %c %3sa %3ss %3sz %3sp  ´",
            x_grand, x_all, x_total, myKEYS.h_logkeys,
            x_curr , myKEYS.h_used,
            x_error, x_warn, x_skip, myKEYS.h_locked,
            x_ack, x_space, x_noop, x_combo);
      break;
   default  :
      sprintf (a_list, "logger  %4sg %4sa %3st %c § %3sc %c § %2se %2sw %2ss %c § %3sa %3ss %3sz %3sp § %2so %2sc %c ´",
            x_grand, x_all, x_total, myKEYS.h_logkeys,
            x_curr , myKEYS.h_used,
            x_error, x_warn, x_skip, myKEYS.h_locked,
            x_ack, x_space, x_noop, x_combo,
            x_open, x_close, myKEYS.h_balanced);
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_keylog_status     (char a_size, short a_wide, char *a_list)
{
   /*---(locals)-----------+-----+-----+-*/
   short       w;
   short       h;
   uchar       x_grand     [LEN_TERSE] = "";
   uchar       x_total     [LEN_TERSE] = "";
   uchar       x_mode      =  '¬';
   uchar       x_err       =  '¬';
   uchar       x_ch        =  '¬';
   uchar       x_log       [LEN_RECD]  = "";
   uchar       x_cont      =  'å';
   short       x_max       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_SCRP   yLOG_enter   (__FUNCTION__);
   /*---(get size)-----------------------*/
   if (a_size == '-') { /* no adapt option */
      if      (a_wide <  20)  a_size = 'u';
      else if (a_wide <  40)  a_size = 't';
      else if (a_wide <  70)  a_size = 's';
      else if (a_wide < 110)  a_size = 'm';
      else if (a_wide < 160)  a_size = 'l';
      else if (a_wide < 220)  a_size = 'h';
      else                    a_size = 'g';
   }
   /*> ymacro_status__sizes (&a_size, &a_wide, &w);                                   <*/
   switch (a_size) {
   case  'u' :  h =   0;  break;
   case  't' :  h =   0;  break;
   case  's' :  h =   7;  break;
   case  'm' :  h =  37;  break;
   case  'l' :  h =  77;  break;
   case  'h' :  h = 127;  break;
   case  'g' :  h = 187;  break;
   }
   /*---(prepare)------------------------*/
   ykeys_num2str (myKEYS.h_grand, 4, x_grand);
   ykeys_num2str (myKEYS.h_total, 3, x_total);
   if (myKEYS.h_total > 0) {
      x_mode = myKEYS.h_mode [myKEYS.h_curr];
      x_err  = myKEYS.h_errs [myKEYS.h_curr];
      x_ch   = myKEYS.h_log  [myKEYS.h_curr];
   }
   /*---(log part)-----------------------*/
   strlcpy (x_log, YSTR_PLUS, h + 1);
   x_max = myKEYS.h_total;
   if (x_max > h) { x_max = h; x_cont = '<'; }
   for (i = 0; i <= x_max; ++i) {
      x_log [h - i] = myKEYS.h_log [myKEYS.h_total - i];
   }
   /*---(make)---------------------------*/
   if (myKEYS.h_total > 0)  x_log [h - 1] = '¬';
   switch (a_size) {
   case 'u' :
      sprintf (a_list, "key %3s %c´", x_total, myKEYS.h_logkeys);
      break;
   case 't' :
      sprintf (a_list, "key %3st %c %c %c %c %c ´", x_total, myKEYS.h_logkeys, myKEYS.h_locked, x_mode, x_ch, x_err);
      break;
   default  :
      sprintf (a_list, "keylog  %4sg %3st %c %c  %c %c %c %c%s ´", x_grand, x_total, myKEYS.h_logkeys, myKEYS.h_locked, x_mode, x_ch, x_err, x_cont, x_log);
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_loop_status       (char a_size, short a_wide, char *a_list)
{
   char        t           [LEN_LABEL] = "";
   char        x_delay     [LEN_LABEL] = "";
   char        x_skip      [LEN_LABEL] = "";
   char        x_update    [LEN_LABEL] = "";
   char        x_nsec      [LEN_LABEL] = "";
   char        x_loops     [LEN_LABEL] = "";
   char        x_bdelay    [LEN_LABEL] = "";
   char        x_bskip     [LEN_LABEL] = "";
   char        x_bupdate   [LEN_LABEL] = "";
   /*---(delays)-------------------------*/
   sprintf (x_delay  , "%8.6f", myKEYS.l_delay);
   sprintf (x_bdelay , "%8.6f", g_bdelay);
   sprintf (t        , "%d"  , myKEYS.l_skip);
   strlpad (t, x_skip  , '.', '>', 2);
   sprintf (t        , "%d"  , g_bskip);
   strlpad (t, x_bskip , '.', '>', 2);
   /*---(updates)------------------------*/
   sprintf (t        , "%.4f", myKEYS.l_update);
   strlpad (t, x_update , '.', '>', 8);
   sprintf (t        , "%.4f", g_bupdate);
   strlpad (t, x_bupdate, '.', '>', 8);
   /*---(timing)-------------------------*/
   sprintf (t        , "%ld" , myKEYS.l_nsec);
   strlpad (t, x_nsec   , '.', '>', 9);
   sprintf (t        , "%d"  , myKEYS.l_loops);
   strlpad (t, x_loops  , '.', '>', 4);
   /*---(output)-------------------------*/
   switch (a_size) {
   case 'u' :
      sprintf (a_list, "%-4.4s %-4.4s ´",
            g_delays  [g_cdelay ].terse,
            g_updates [g_cupdate].terse);
      break;
   case 't' :
      sprintf (a_list, "loo %-5.5s %-5.5s %c  ´",
            g_delays  [g_cdelay ].terse,
            g_updates [g_cupdate].terse,
            myKEYS.l_blocking);
      break;
   case 's' :
      sprintf (a_list, "loop    D %-5.5s %-2.2s, U %-5.5s, L %-4.4s %c  ´",
            g_delays  [g_cdelay ].terse, x_skip,
            g_updates [g_cupdate].terse,
            x_loops, myKEYS.l_blocking);
      break;
   case 'm' :
      sprintf (a_list, "loop    D %-5.5s %-8.8s %-2.2s, U %-5.5s %-8.8s, %1ds %-9.9sns %-4.4s %c ´",
            g_delays  [g_cdelay ].terse, x_delay, x_skip,
            g_updates [g_cupdate].terse, x_update,
            myKEYS.l_secs, x_nsec, x_loops, myKEYS.l_blocking);
      break;
   case 'l' :
      sprintf (a_list, "loop    D %-5.5s %-8.8s %-2.2s, U %-5.5s %-8.8s, L %1ds %-9.9sns %-4.4s %c, S %-5.5s %-5.5s, B %-8.8s %-2.2s %-8.8s´",
            g_delays  [g_cdelay ].terse, x_delay, x_skip,
            g_updates [g_cupdate].terse, x_update,
            myKEYS.l_secs, x_nsec, x_loops, myKEYS.l_blocking,
            g_sdelay, g_supdate, x_bdelay, x_bskip, x_bupdate);
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

