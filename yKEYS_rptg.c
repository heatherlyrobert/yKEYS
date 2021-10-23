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

char         /*-> tbd --------------------------------[ leaf   [gz.430.151.10]*/ /*-[00.0000.104.!]-*/ /*-[--.---.---.--]-*/
yKEYS_status            (char *a_msg)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD];
   int         x_key       = 0;
   int         x_len       = 0;             /* string length                  */
   int         i           = 0;             /* iterator -- keys               */
   int         x_start     = 0;             /* iterator -- keys               */
   x_len = strlen (myKEYS.h_log) - 1;
   x_start = x_len - 39;
   if (x_start < 0) x_start = 0;
   snprintf (a_msg, 500, "keys    %-5d %s¤", myKEYS.h_all, myKEYS.h_log + x_start);
   return 0;
}
