#include "main.h"

/**
 * change_def - changes to a directory given
 * by the user
 *
 * @globvar: data relevant (directories)
 * Return: no return
 */
void change_def(globals_t *globvar)
{
	char *pdr = NULL, *rep_thsdir = NULL, *copydir = NULL;
	char *opwd = "OLDPWD", *tpwd = "PWD";
	char p_w_d[PMXA];

	getcwd(p_w_d, sizeof(p_w_d));

	pdr = globvar->mytok[1];
	if (chdir(pdr) == -1)
	{
		err_choose(globvar, DEFERR);
		return;
	}
	rep_thsdir = _strdup(p_w_d);
	assisst_senv(opwd, rep_thsdir, globvar);
	copydir = _strdup(pdr);
	assisst_senv(tpwd, copydir, globvar);
	globvar->exitstat = 0;
	free(copydir);
	free(rep_thsdir);

	chdir(pdr);
}

/**
 * d_navigation - changes to the parent directory
 *
 * @globvar: data relevant (environ)
 *
 * Return: no return
 */
void d_navigation(globals_t *globvar)
{
	char *p_dr = NULL, *rep_thsdir = NULL, *tk_thsdir = NULL;
	char *opwd = "OLDPWD", *tpwd = "PWD", *fs = "/", *dot = ".", *nol = "\0";
	char p_w_d[PMXA];

	getcwd(p_w_d, sizeof(p_w_d));
	rep_thsdir = _strdup(p_w_d);
	assisst_senv(opwd, rep_thsdir, globvar);
	p_dr = globvar->mytok[1];
	if (_strcmp(dot, p_dr) == 0)
	{
		assisst_senv(tpwd, rep_thsdir, globvar);
		free(rep_thsdir);
		return;
	}
	if (_strcmp(fs, rep_thsdir) == 0)
	{
		free(rep_thsdir);
		return;
	}
	tk_thsdir = rep_thsdir;
	reverse_str(tk_thsdir);
	tk_thsdir = str_tok(tk_thsdir, fs);
	if (tk_thsdir != NULL)
	{
		tk_thsdir = str_tok(NULL, nol);
		if (tk_thsdir != NULL)
			reverse_str(tk_thsdir);
	}
	if (tk_thsdir != NULL)
	{
		chdir(tk_thsdir);
		assisst_senv(tpwd, tk_thsdir, globvar);
	}
	else
	{
		chdir(fs);
		assisst_senv(tpwd, fs, globvar);
	}
	globvar->exitstat = 0;
	free(rep_thsdir);
}

/**
 * cntrl_cd - changes current directory
 *
 * @globvar: data relevant
 * Return: 1 on success
 */
int cntrl_cd(globals_t *globvar)
{
	char *dir = NULL;
	int ret = 1, ret2 = 1, ret3 = 1;
	char *home = "$HOME", *ddash = "--", *tilda = "~", *ddot = "..";
	char *dash = "-", *dot = ".";

	dir = globvar->mytok[1];

	if (dir != NULL)
	{
		ret = _strcmp(home, dir);
		ret3 = _strcmp(ddash, dir);
		ret2 = _strcmp(tilda, dir);
	}

	if (dir == NULL || ret == 0 || ret2 == 0 ||
	ret3 == 0)
	{
		go_homdir(globvar);
		return (1);
	}
	if (_strcmp(dash, dir) == 0)
	{
		go_prev(globvar);
		return (1);
	}
	if (_strcmp(dot, dir) == 0 || _strcmp(ddot, dir) == 0)
	{
		d_navigation(globvar);
		return (1);
	}
	change_def(globvar);
	return (1);
}


/**
 * go_prev - changes to the previous directory
 *
 * @globvar: data relevant (environ)
 * Return: no return
 */
void go_prev(globals_t *globvar)
{
	char *prev = NULL, *popd = NULL, *rep_thsdir = NULL, *cpopd = NULL;
	char p_w_d[PMXA];
	char *opwd = "OLDPWD", *tpwd = "PWD";

	getcwd(p_w_d, sizeof(p_w_d));
	rep_thsdir = _strdup(p_w_d);

	popd = ret_enviro(opwd, globvar->my_env);

	if (popd == NULL)
		cpopd = rep_thsdir;
	else
		cpopd = _strdup(popd);

	assisst_senv(opwd, rep_thsdir, globvar);

	if (chdir(cpopd) == -1)
		assisst_senv(tpwd, rep_thsdir, globvar);
	else
		assisst_senv(tpwd, cpopd, globvar);

	prev = ret_enviro(tpwd, globvar->my_env);

	display_out(prev);
	display_out("\n");

	free(rep_thsdir);
	if (popd)
		free(cpopd);
	globvar->exitstat = 0;
	chdir(prev);
}

/**
 * go_homdir - changes to home directory
 *
 * @globvar: data relevant (environ)
 * Return: no return
 */
void go_homdir(globals_t *globvar)
{
	char *prev = NULL, *root = NULL;
	char *opwd = "OLDPWD", *tpwd = "PWD", *hm = "HOME";
	char p_w_d[PMXA];

	getcwd(p_w_d, sizeof(p_w_d));
	prev = _strdup(p_w_d);

	root = ret_enviro(hm, globvar->my_env);
	if (root == NULL)
	{
		assisst_senv(opwd, prev, globvar);
		free(prev);
		return;
	}
	if (chdir(root) == -1)
	{
		err_choose(globvar, DEFERR);
		free(prev);
		return;
	}
	assisst_senv(opwd, prev, globvar);
	assisst_senv(tpwd, root, globvar);
	free(prev);
	globvar->exitstat = 0;
}
