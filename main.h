#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>

#define OUT STDOUT_FILENO
#define IN STDIN_FILENO
#define ERR STDERR_FILENO
#define FAILED EXIT_FAILURE
#define SYNERR 127
#define PERMERR 126
#define DEFERR 2
#define STTEMAX 256
#define ENVERR -1
#define PMXA PATH_MAX

extern char **environ;

typedef unsigned int usnd_int;

/**
 * struct globals - struct that contains all relevant data on runtime
 * @line: command line written by the user
 * @mytok: tokens of the command line
 * @argv: argument vector
 * @this_pid: process ID of the shell
 * @my_env: environment variable
 * @exitstat: last status of the shell
 * @linecount: lines counter
 */
typedef struct globals
{
	char **argv;
	char **my_env;
	int exitstat;
	char *line;
	char **mytok;
	char *this_pid;
	int linecount;
} globals_t;

/**
 * struct built_ins_s - Builtin struct for command mytok.
 * @exec_name: The exec_name of the command builtin i.e cd, exit, env
 * @call_func: data type pointer function.
 */
typedef struct built_ins_s
{
	char *exec_name;
	int (*call_func)(globals_t *globvar);
} my_built_ins;

/**
 * struct partition_s - single linked list
 * @parts: ; | &
 * @link: next node
 * Description: single linked list to store separators
 */
typedef struct partition_s
{
	char parts;
	struct partition_s *link;
} partition;

/**
 * struct variable_s - single linked list
 * @len1: length of the variable
 * @myvalue: value of the variable
 * @len2: length of the value
 * @link: next node
 * Description: single linked list to store variables
 */
typedef struct variable_s
{
	int len1;
	int len2;
	char *myvalue;
	struct variable_s *link;
} variable_t;

/**
 * struct cmd_s - single linked list
 * @cmd_args: command line
 * @link: next node
 * Description: single linked list to store command lines
 */
typedef struct cmd_s
{
	char *cmd_args;
	struct cmd_s *link;
} cmd_t;


void free_partition(partition **h);
cmd_t *cmdln_add_end(cmd_t **h, char *line);
variable_t *varadd_node(variable_t **h, int lvar, char *var, int lval);
void free_variables(variable_t **h);
char *str_cat(char *destination, const char *source);
int _strcmp(char *str1, char *str2);
void *_realloc(void *pptr, usnd_int o_sze, usnd_int n_sze);
void init_data(globals_t *globvar, char **argv);

char **dprllc(char **pptr, usnd_int o_sze, usnd_int n_sze);
void free_my_globals(globals_t *globvar);
partition *partition_add_end(partition **h, char delim);
char *_strdup(const char *s);
int str_len(const char *s);
char *str_tok(char my_str[], const char *seperator);
void reverse_str(char *str);
int rep_check(char *line, int idx);

int partition_err(char *line, int idx, char end);
void free_cmd_t(cmd_t **h);
char *_strcpy(char *destination, char *source);
int init_ind(char *line, int *idx);
void gen_syn_err(globals_t *globvar, char *line, int idx, int status);
int syn_err_ch(globals_t *globvar, char *line);
int _strspn(char *str, char *acpt);

char *_strchr(char *str, char letter);
char *replacement(char *line, globals_t *globvar);
int letter_ch(char my_str[], const char *seperator);
char *ignore_comm(char *in);
void display_prompt(void);
void display_err(char *message);
void display_out(char *message);

char *line_buff(int *ret_eof);
int num_detect(const char *str);
char *rep_sep(char *line, int stat);
void place_nds(partition **h_start, cmd_t **h_last, char *line);
void jump_to(partition **start_l, cmd_t **last_l, globals_t *globvar);
int process_cmd(globals_t *globvar, char *line);
char **split_to_arr(char *line);

void is_envar(variable_t **h, char *in, globals_t *data);
int varbl_ch(variable_t **h, char *in, char *st, globals_t *data);
char *convert_var(variable_t **h, char *line, char *n_in, int len);
int run_exec(globals_t *globvar);
void loop_parser(globals_t *globvar);
int scolon_ch(char *path, int *idx);

char *pathfinder(char *command, char **e_n_v);
int exec_ch(globals_t *globvar);
int err_cmd_type(char *dir, globals_t *globvar);
int handle_ex(globals_t *globvar);
char *build_cd_err(globals_t *globvar, char *message, char *err, char *str);
char *num_tostr(int num);

char *ret_enviro(const char *exec_name, char **e_n_v);
int env_printer(globals_t *globvar);
int handle_exit(globals_t *globvar);
int mat_nm(const char *nenv, const char *name);
char *alenv_cp(char *exec_name, char *value);
void assisst_senv(char *exec_name, char *value, globals_t *globvar);

int senv(globals_t *globvar);
int err_choose(globals_t *globvar, int vlerr);
int usenv(globals_t *globvar);
void d_navigation(globals_t *globvar);
void change_def(globals_t *globvar);
char *handle_enviro_err(globals_t *globvar);

void go_prev(globals_t *globvar);
void go_homdir(globals_t *globvar);
int cntrl_cd(globals_t *globvar);
int (*ret_builts(char *cmd))(globals_t *globvar);
int cnt_dgts(int num);

int str_toint(char *s);
char *check_cd_er(globals_t *globvar);
char *location_err(globals_t *globvar);
char *gen_ext_err(globals_t *globvar);
char *gen_perm_err(globals_t *globvar);
void handle_C_sig(int sig);

#endif
