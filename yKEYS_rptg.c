/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"

/*> char*                                                                             <* 
 *> yVIKEYS_keys_last       (void)                                                    <* 
 *> {                                                                                 <* 
 *>    sprintf (g_last, "(%c) %c", g_mode [g_total - 1], g_log [g_total - 1]);          <* 
 *>    return g_last;                                                                 <* 
 *> }                                                                                 <*/

char         /*-> tbd --------------------------------[ leaf   [gz.430.151.10]*/ /*-[00.0000.104.!]-*/ /*-[--.---.---.--]-*/
yKEYS_status            (char *a_msg)
{
   /*---(locals)-----------+-----------+-*/
   char        t           [LEN_RECD];
   int         x_key       = 0;
   int         x_len       = 0;             /* string length                  */
   int         i           = 0;             /* iterator -- keys               */
   int         x_start     = 0;             /* iterator -- keys               */
   x_len = strlen (g_log) - 1;
   x_start = x_len - 39;
   if (x_start < 0) x_start = 0;
   snprintf (a_msg, 500, "keys    %-5d %s¤", g_all, g_log + x_start);
   return 0;
}
