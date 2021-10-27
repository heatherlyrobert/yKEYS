/*============================----beg-of-source---============================*/
#ifndef yKEYS
#define yKEYS yes



typedef  unsigned char        uchar;


#define     YKEYS_LOCK        -120
#define     YKEYS_ERROR       -110
#define     YKEYS_WARN        -100



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yKEYS_version           (void);
char        yKEYS_init              (void);
char        yKEYS_wrap              (void);
char        yKEYS_input             (char a_env, uchar *a_key, uchar *a_str, int *n);
char        yKEYS_string            (uchar *a_keys);
/*---(base)-----------------*/
char        yKEYS_logger            (uchar a_key);
char        yKEYS_handled           (void);
char        yKEYS_unique            (void);
/*---(status)---------------*/
int         yKEYS_count             (void);
int         yKEYS_position          (void);
uchar       yKEYS_current           (void);
char        yKEYS_oldkeys           (void);
/*---(action)---------------*/
char        yKEYS_repos             (int a_pos);
char        yKEYS_nextpos           (void);
char        yKEYS_toend             (void);
/*---(errors)---------------*/
char        yKEYS_set_warning       (void);
char        yKEYS_set_error         (void);
char        yKEYS_set_lock          (void);
char        yKEYS_set_skip          (void);
char        yKEYS_is_error          (void);
char        yKEYS_is_locked         (void);
char        yKEYS_lock              (void);
char        yKEYS_unlock            (void);
char        yKEYS_check_unlock      (uchar *a_key);
/*---(reporting)------------*/
char*       yKEYS_last              (void);
char        yKEYS_keylog_status     (char a_size, short a_wide, char *a_list);
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
char        yKEYS_group_hmode       (uchar a_major, uchar a_minor);
/*---(mode)-----------------*/
char        yKEYS_repeat_umode      (uchar a_major, uchar a_minor);
/*---(done)-----------------*/
char*       yKEYS__unit             (char *a_question, char a_index);



/*---(check)----------------*/
char        yKEYS_is_repeater       (uchar a_minor);
char        yKEYS_is_multi_map      (uchar a_minor);
char        yKEYS_is_multi_visu     (uchar a_minor);
char        yKEYS_is_multi_wdr      (uchar a_minor);
char        yKEYS_is_multi_src      (uchar a_minor);
char        yKEYS_is_multi_selc     (uchar a_minor);
char        yKEYS_is_horz_simple    (uchar a_minor);
char        yKEYS_is_horz_goto      (uchar a_minor);
char        yKEYS_is_horz_scroll    (uchar a_minor);
char        yKEYS_is_horz_word      (uchar a_minor);
char        yKEYS_is_macro          (uchar a_minor);
char        yKEYS_is_findchar       (uchar a_minor);



#endif
/*============================----end-of-source---============================*/
