/**
 *  xen
 *
 *  Created by Sanzhar Kudaibergen on 7/12/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#include "sys_call.h"
#include "color_scheme.h"

#define GIT_PULL    "git pull"
#define MVN_BUILD   "mvn clean install"
#define PWD         "pwd"
#define NOHUP_JAVA_RUN "nohup java -Xms256m -Xmx512m -jar"


int str_ends_with(const char *str, const char *suffix);

int sys_call_git_pull(const char *usrname, const char *passw)
{
    printf("--- executing cmd: ");
    printf(BOLDYELLOW "%s\n" RESET, GIT_PULL);
    printf("\n" RESET);
    
    int res = system(GIT_PULL);
    
    printf("\n--- executing cmd: ");
    printf(BOLDYELLOW "%s " RESET, GIT_PULL);
    printf("finished with result: ");
    printf(BOLDYELLOW "%d \n" RESET, res);

    return res;
}

int sys_call_mvn_build()
{
    return system(MVN_BUILD);
}

int sys_call_cd(const char *relpath)
{
    int size = strlen(relpath);
    char buffer[size];      // command name
    snprintf(buffer, size + 1, "%s %s", "cd", relpath);
    
    printf("--- executing cmd: ");
    printf(BOLDYELLOW "cd %s\n", relpath);
    printf(RESET);
    
    return chdir(relpath);
}

int sys_call_run_java()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if (str_ends_with(ent->d_name, ".jar"))
            {
                printf ("--- found jar: %s\n", ent->d_name);
                char buffer[100];
                snprintf(buffer, sizeof(buffer), "%s %s %s", NOHUP_JAVA_RUN, ent->d_name, "&");
                
                printf("--- executing cmd: ");
                printf(BOLDYELLOW "%s\n", buffer);
                printf(RESET);
                
                closedir (dir);
                return system(buffer);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    
    return 1;
}

int sys_call_pwd()
{
    return system(PWD);
}

int sys_call_kill_prcss(const char *pname)
{
    int pid = 0;
    int size = strlen("ps aux | grep java | grep") + strlen(pname) + strlen("| awk '{print $2}'");
    char buffer[size];
    snprintf(buffer, size + 3, "%s %s %s", "ps aux | grep java | grep", pname, "| awk '{print $2}'");
    
    printf("--- executing cmd: ");
    printf(BOLDYELLOW "%s\n", buffer);
    printf(RESET);
    
    FILE *cmd;
    char res[1024];

    cmd = popen(buffer, "r");
    if (cmd == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(res, sizeof(res), cmd))
    {
        int pid = (int) strtol(res, (char **)NULL, 10);
        const char *pn = sys_call_prcss_name(pid);
        printf("killing process -- ");
        printf(BOLDYELLOW "{ pid: %d, name: %s }\n", pid, pname);
        printf(RESET);
        kill(pid, SIGTERM);
    }
    
    pclose(cmd);
    return 0;
}

char *sys_call_prcss_name(int pid)
{
    int size = strlen("ps -c") + 5 + strlen("| awk '{print $4}'");
    char buffer[size];
    snprintf(buffer, size + 3, "%s %d %s", "ps -c", pid, "| awk '{print $4}'");
    
    printf("--- executing cmd: ");
    printf(BOLDYELLOW "%s\n", buffer);
    printf(RESET);
    
    FILE *cmd;
    char res[1024];
    
    cmd = popen(buffer, "r");
    if (cmd == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    if (fgets(res, sizeof(res), cmd))
    {
        char *name = res;
        pclose(cmd);
        return name;
    }
    
    return NULL;
}

int str_ends_with(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}
