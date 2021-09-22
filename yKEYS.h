/*============================----beg-of-source---============================*/
#ifndef yKEYS
#define yKEYS yes



typedef  unsigned char        uchar;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yKEYS_version           (void);
char        yKEYS_init              (void);
char        yKEYS_wrap              (void);
uchar       yKEYS_input             (char a_env, uchar a_key);
/*---(base)-----------------*/
char        yKEYS_logger            (uchar a_key);
char        yKEYS_error             (void);
char        yKEYS_unique            (void);
int         yKEYS_count             (void);
int         yKEYS_position          (void);
uchar       yKEYS_current           (void);
char        yKEYS_oldkeys           (void);
char        yKEYS_repos             (int a_pos);
char        yKEYS_toend             (void);
/*---(reporting)------------*/
char        yKEYS_status            (char *a_msg);
/*---(repeat)---------------*/

/*---(status)---------------*/
char        yKEYS_normal            (void);
char        yKEYS_repeating         (void);
int         yKEYS_repeats           (void);
int         yKEYS_repeat_orig       (void);
/*---(action)---------------*/
char        yKEYS_repeat_dec        (void);
int         yKEYS_repeat_useall     (void);
char        yKEYS_repeat_reset      (void);
/*---(grouping)-------------*/
char        yKEYS_group_beg         (void);
char        yKEYS_group_end         (void);
/*---(mode)-----------------*/
char        yKEYS_repeat_umode      (uchar a_major, uchar a_minor);
/*---(done)-----------------*/
char*       yKEYS__unit             (char *a_question, char a_index);

#endif
/*============================----end-of-source---============================*/
