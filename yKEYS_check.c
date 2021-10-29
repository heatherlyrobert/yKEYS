/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yKEYS.h"
#include    "yKEYS_priv.h"


static  uchar   s_repeat    [LEN_DESC ]   = "123456789";

static  uchar   s_vsimple   [LEN_DESC ]   = "_ Kk jJ ~                 �  ";
static  uchar   s_vgoto     [LEN_DESC ]   = "TK tkmjb JB   azud AZUD .   g";
static  uchar   s_vscroll   [LEN_DESC ]   = "   tkmjb      azud      .    ";
static  uchar   s_vpage     [LEN_DESC ]   = "   tk jb      azud AZUD      ";
static  uchar   s_vends     [LEN_DESC ]   = "T  tkmjb  B M azud      .    ";

static  uchar   s_hsimple   [LEN_DESC ]   = "0 Hh lL $                 �  ";
static  uchar   s_hgoto     [LEN_DESC ]   = "SH shcle LE   azud AZUD .   g";
static  uchar   s_hscroll   [LEN_DESC ]   = "   shcle      azud      .    ";
static  uchar   s_hpage     [LEN_DESC ]   = "   sh le      azud AZUD      ";
static  uchar   s_hends     [LEN_DESC ]   = "S  shcle  E C azud      .    ";
static  uchar   s_hword     [LEN_LABEL]   = "wbe WBE";
static  uchar   s_hchar     [LEN_LABEL]   = "#fFnN";

static  uchar   s_multimap  [LEN_DESC ]   = "cgz e pdx ai  DA             ";
static  uchar   s_multivisu [LEN_DESC ]   = "cgz e pd  ai  DA             ";
static  uchar   s_multiwdr  [LEN_DESC ]   = "cg  e                        ";

static  uchar   s_multisrc  [LEN_DESC ]   = "cgz   pdx     Ff             ";
static  uchar   s_multiselc [LEN_DESC ]   = "cgz   p       Ff             ";

static  uchar   s_search    [LEN_LABEL]   = "[<>]";

static  uchar   s_macro     [LEN_LABEL]   = "@qQ";


char yKEYS_is_repeater       (uchar a_minor) { if (strchr (s_repeat   , a_minor) != NULL)  return 1; return 0; }

char yKEYS_is_multi_map      (uchar a_minor) { if (strchr (s_multimap , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_multi_visu     (uchar a_minor) { if (strchr (s_multivisu, a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_multi_wdr      (uchar a_minor) { if (strchr (s_multiwdr , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_multi_src      (uchar a_minor) { if (strchr (s_multisrc , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_multi_selc     (uchar a_minor) { if (strchr (s_multiselc, a_minor) != NULL)  return 1; return 0; }

char yKEYS_is_horz_simple    (uchar a_minor) { if (strchr (s_hsimple  , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_horz_goto      (uchar a_minor) { if (strchr (s_hgoto    , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_horz_scroll    (uchar a_minor) { if (strchr (s_hscroll  , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_horz_word      (uchar a_minor) { if (strchr (s_hword    , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_horz_ends      (uchar a_minor) { if (strchr (s_hends    , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_horz_char      (uchar a_minor) { if (strchr (s_hchar    , a_minor) != NULL)  return 1; return 0; }

char yKEYS_is_vert_simple    (uchar a_minor) { if (strchr (s_vsimple  , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_vert_goto      (uchar a_minor) { if (strchr (s_vgoto    , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_vert_ends      (uchar a_minor) { if (strchr (s_vends    , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_vert_scroll    (uchar a_minor) { if (strchr (s_vscroll  , a_minor) != NULL)  return 1; return 0; }

char yKEYS_is_macro          (uchar a_minor) { if (strchr (s_macro    , a_minor) != NULL)  return 1; return 0; }
char yKEYS_is_search         (uchar a_minor) { if (strchr (s_search   , a_minor) != NULL)  return 1; return 0; }


