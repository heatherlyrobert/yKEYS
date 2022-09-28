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
char        ykeys__input            (char a_env, uchar *a_key, uchar *a_str, int *n);
char        yKEYS_string            (uchar *a_keys);
char        yKEYS_quit              (void);
char        yKEYS_writequit         (void);
char        yKEYS_writequitall      (void);
char        yKEYS_main              (char *a_delay, char *a_update, int a_loops, char a_env, void *a_draw, void *a_input, void *a_altinput);
/*---(base)-----------------*/
char        yKEYS_logger            (uchar a_key);
char        yKEYS_unique            (void);
/*---(status)---------------*/
int         yKEYS_count             (void);
int         yKEYS_position          (void);
uchar       yKEYS_current           (void);
uchar       yKEYS_multi             (void);
char        yKEYS_is_menu           (void);
char        yKEYS_oldkeys           (void);
char        yKEYS_every_current     (uchar *a_mode, uchar *a_curr, uchar *a_multi, uchar *a_menu, uchar *a_error, uchar *a_status);
/*---(action)---------------*/
char        yKEYS_logging_on        (void);
char        yKEYS_logging_off       (void);
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
/*---(repeat)---------------*/

/*---(status)---------------*/
char        yKEYS_normal            (void);
char        yKEYS_repeating         (void);
int         yKEYS_repeats           (void);
int         yKEYS_repeat_orig       (void);
/*> int         yKEYS_repeat_set_multi  (void);                                       <*/
/*> char        yKEYS_repeat_dec_multi  (void);                                       <*/
/*> int         yKEYS_repeat_use_multi  (void);                                       <*/
char        yKEYS_repeat_beg        (void);
char        yKEYS_repeat_end        (void);
char        yKEYS_check_repeat      (void);
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
char        yKEYS_repeat_check      (uchar a_major, uchar a_minor, char a_prev, char a_curr, char a_rc);
/*---(done)-----------------*/
char*       yKEYS__unit             (char *a_question, char a_index);



/*===[[ yKEYS_check.c ]]======================================================*/
/*---(overall)--------------*/
char        yKEYS_is_repeater       (uchar a_minor);
char        yKEYS_is_macro          (uchar a_minor);
char        yKEYS_is_search         (uchar a_minor);
/*---(multi)----------------*/
char        yKEYS_is_multi_map      (uchar a_minor);
char        yKEYS_is_multi_visu     (uchar a_minor);
char        yKEYS_is_multi_wdr      (uchar a_minor);
char        yKEYS_is_multi_src      (uchar a_minor);
char        yKEYS_is_multi_selc     (uchar a_minor);
/*---(horizontal)-----------*/
char        yKEYS_is_horz_simple    (uchar a_minor);
char        yKEYS_is_horz_goto      (uchar a_minor);
char        yKEYS_is_horz_scroll    (uchar a_minor);
char        yKEYS_is_horz_word      (uchar a_minor);
char        yKEYS_is_horz_ends      (uchar a_minor);
char        yKEYS_is_horz_char      (uchar a_minor);
/*---(vertical)-------------*/
char        yKEYS_is_vert_simple    (uchar a_minor);
char        yKEYS_is_vert_goto      (uchar a_minor);
char        yKEYS_is_vert_scroll    (uchar a_minor);
char        yKEYS_is_vert_ends      (uchar a_minor);
/*---(depth)----------------*/
char        yKEYS_is_deep_simple    (uchar a_minor);
char        yKEYS_is_deep_goto      (uchar a_minor);
char        yKEYS_is_deep_scroll    (uchar a_minor);
char        yKEYS_is_deep_ends      (uchar a_minor);
/*---(complex)--------------*/
char        yKEYS_check_multi       (uchar a_major, uchar a_minor);
/*---(done)-----------------*/




/*---(reporting)------------*/
char        yKEYS_keylog_status     (char a_size, short a_wide, char *a_list);
char        yKEYS_logger_status     (char a_size, short a_wide, char *a_list);
char        yKEYS_loop_status       (char a_size, short a_wide, char *a_list);
char        yKEYS_replay_status     (char a_size, short a_wide, char *a_list);


/*---(normal)---------------*/
char        yKEYS_loop_set          (char *a_delay, char *a_update);
char        yKEYS_loop_get          (float *a_delay, char *a_dterse, float *a_update, char *a_uterse);
/*---(macro)----------------*/
char        yKEYS_loop_macro        (char a_delay, char a_update);
char        yKEYS_loop_return       (void);
char        yKEYS_loop_blitz        (void);
char        yKEYS_loop_unblitz      (void);
char        yKEYS_loop_beg          (void);
char        yKEYS_loop_graf         (void);
char        yKEYS_loop_end          (void);


char        yKEYS_edelay_info       (char n, char *a_terse, char *a_desc, float *a_delay);
char        yKEYS_eupdate_info      (char n, char *a_terse, char *a_desc, float *a_update);
char        yKEYS_ddelay_info       (char a_abbr, char *a_terse, char *a_skip, char *a_desc);
char        yKEYS_dupdate_info      (char a_abbr, char *a_terse, char *a_desc);


char        yKEYS_replay            (void);


char        yKEYS_progress_scale    (uchar *a_scale, uchar *a_terse, uchar *a_label, uchar *a_desc, char *a_power, float *a_unit);
char        yKEYS_progress_speed    (uchar *a_speed, uchar *a_terse, uchar *a_desc, float *a_unit);
char        yKEYS_progress_lines    (int a_lines);
char        yKEYS_progress_length   (float a_beg, float a_end);
char        yKEYS_progress_config   (char a_repeat, char *a_unit, char *a_scale, char *a_speed, char a_play);
char        yKEYS_progress_cur      (float *a_len, char *a_anchor, float *a_sec, float *a_scale, float *a_inc, int *a_line);




#endif
/*============================----end-of-source---============================*/
