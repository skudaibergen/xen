/**
 *  xen
 *
 *  Created by Sanzhar Kudaibergen on 7/12/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#include "orchestra.h"


int pull(const char *prj_name, const char *usrname, const char *passw);
int build(const char *prj_name);
int run(const char *prj_name);
void all();

int orchestrate(int argc, const char **argv)
{
    Stack *proj_stack;
    stack_init(&proj_stack);
    
    int mode = 3;
    const char *username = NULL, *git_pass;
    const char *projnames[argc];
    
    for (int i = 1; i < argc; i++)      // skipping first arg - ./xen
    {
        // USERNAME
        if(strcmp(argv[i], "-u") == 0)
        {
            username = argv[i + 1];
            
            if (!username || username[0] == '-' || (username[0] == '-' && username[1] == '-'))
            {
                printf(BOLDRED "username must not be empty!\n" RESET );
                return 1;
            }
            else
            {
                printf("FOUND USER: %s\n", username);
                git_pass = getpass(BOLDGREEN "GIT Password: " RESET);
                // printf(BOLDGREEN "PASSWORD: %s\n" RESET , git_pass);
                i++;     // skip the username argument
            }
            
            continue;
        }
        
        if (strcmp(argv[i], "--pull") == 0)
        {
            mode = 0;
            continue;
        }
        
        if (strcmp(argv[i], "--build") == 0)
        {
            mode = 1;
            continue;
        }
        
        if (strcmp(argv[i], "--run") == 0)
        {
            mode = 2;
            continue;
        }
        
        // PROJECT NAMES
        char *formatted_arg = (char *) argv[i];
        if (formatted_arg[strlen(formatted_arg) - 1] == '/')
            formatted_arg[strlen(formatted_arg) - 1] = 0;

        stack_push(proj_stack, (void *) formatted_arg);
    }
    
    // CHECKING IF ARGUMENT CONSIST PROJECT NAMES e.g without -- or - prefix
    // TODO: if there are no projects specified, scan curr dir for all possible projects
    if (stack_size(proj_stack) == 0)
    {
        printf(BOLDRED "there are no projects specified!\n" RESET );
        return 1;
    }
    
    // MODES EXECUTION
    if (mode == 0)
    {
        /*
        if (!username)
        {
            printf(BOLDRED "git username must be defined!\n" RESET );
            return 1;
        }
         */
        
        while (stack_size(proj_stack) != 0)
        {
            const char* projname = (char*) stack_pop(proj_stack);
            
            int res = pull(projname, username, git_pass);
            if (res > 0)
            {
                printf(BOLDRED "PULL MODE FAILED\n");
                printf(RESET);
                return 1;
            }
        }
    }
    else if (mode == 1)
    {
        while (stack_size(proj_stack) != 0)
        {
            const char* projname = (char*) stack_pop(proj_stack);
            
            int res = build(projname);
            if (res > 0)
            {
                printf(BOLDRED "BUILD MODE FAILED\n");
                printf(RESET);
                return 1;
            }
        }
    }
    else if (mode == 2) {
        while (stack_size(proj_stack) != 0)
        {
            const char* projname = (char*) stack_pop(proj_stack);
            
            int res = run(projname);
            if (res > 0)
            {
                printf(BOLDRED "RUN MODE FAILED\n");
                printf(RESET);
                return 1;
            }
        }
    }
    else
        all();
    
    return 0;
}

int pull(const char *prj_name, const char *usrname, const char *passw)
{
    printf(BOLDMAGENTA "PULL MODE. project: %s\n" RESET, prj_name);
    
    if (sys_call_cd(prj_name) != 0)
    {
        printf(BOLDRED "there is no such project!\n" RESET );
        return 5;
    }
    sys_call_pwd();
    
    int res = sys_call_git_pull(usrname, passw);
    sys_call_cd("..");      // return to root rel path
    return res;
}

int build(const char *prj_name)
{
    printf(BOLDMAGENTA "BUILD MODE. project: %s\n" RESET, prj_name);
    
    if (sys_call_cd(prj_name) != 0)
    {
        printf(BOLDRED "there is no such project!\n" RESET );
        return 5;
    }
    sys_call_pwd();
    
    int res = sys_call_mvn_build();
    sys_call_cd("..");
    return res;
}

int run(const char *prj_name)
{
    printf(BOLDMAGENTA "RUN MODE. project: %s\n" RESET, prj_name);
    
    int size = strlen(prj_name) + 7;
    char dirr[size];      // command name
    snprintf(dirr, size + 1, "%s%s", prj_name, "/target");
    
    if (sys_call_cd(dirr) != 0)
    {
        printf(BOLDRED "there is no such project!\n" RESET );
        return 5;
    }
    sys_call_pwd();
    
    int killres = sys_call_kill_prcss(prj_name);
    int runres = sys_call_run_java();
    
    sys_call_cd("../..");
    return runres;
}

void all()
{
    printf(BOLDMAGENTA "FULL MODE\n" RESET);
//    pull();
//    build();
//    run();
}
