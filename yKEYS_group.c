/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"



char
yKEYS_group_beg         (void)
{
   /*---(defense)------------------------*/
   if (g_repeats <= 0)  return 0;
   /*---(populate new level)-------------*/
   ++g_level;
   IF_MACRO_PLAYING {
      yMACRO_exe_pos (&(g_src [g_level]), &(g_pos [g_level]));
   } else {
      g_pos [g_level] = yKEYS_position ();
      g_src [g_level] = '´';
   }
   g_rep [g_level] = g_repeats;
   /*---(clear normal repeat)------------*/
   g_repeats = 0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yKEYS_group_end         (void)
{
   /*---(defense)------------------------*/
   if (g_level <= 0)  return 0;
   /*---(check for done)-----------------*/
   if (g_rep [g_level] <= 0) {
      g_rep [g_level] = -1;
      g_src [g_level] = '-';
      g_pos [g_level] = -1;
      --g_level;
   }
   /*---(return to beginning)------------*/
   else {
      --(g_rep [g_level]);
      if (g_src [g_level] == (uchar) '´')  yKEYS_repos       (g_pos [g_level]);
      else                                 yMACRO_exe_repos  (g_pos [g_level]);
   }
   /*---(complete)-----------------------*/
   return 0;
}
