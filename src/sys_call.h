/**
 *  xen
 *
 *  Created by Sanzhar Kudaibergen on 7/12/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>     // for executing os commands
#include <unistd.h>
#include <signal.h>
#include <dirent.h>


int sys_call_git_pull(const char *usrname, const char *passw);
int sys_call_mvn_build();
int sys_call_cd(const char *relpath);
int sys_call_pwd();
int sys_call_run_java();
int sys_call_kill_prcss(const char *pname);
char *sys_call_prcss_name(int pid);
