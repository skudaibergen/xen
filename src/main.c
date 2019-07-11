/**
 *
 *  buildx
 *
 *  Created by Sanzhar Kudaibergen on 7/11/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>     // for password
#include <stdlib.h>     // for executing os commands

#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */

int main(int argc, const char *argv[]) {
    int mode = 2;
    char *git_pass;
    
    int i;
    for (i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-u") == 0)
        {
            const char *username = argv[i + 1];
            
            if (username)
            {
                printf("FOUND USER: %s\n", username);
                git_pass = getpass(BOLDGREEN "GIT Password: " RESET);
                printf(BOLDGREEN "PASSWORD: %s\n" RESET , git_pass);
            }
            else
            {
                printf(BOLDRED "username must be defined!\n" RESET );
                return 1;
            }
        }
        if (strcmp(argv[i], "--pull") == 0)
        {
            mode = 0;
        }
        
        if (strcmp(argv[i], "--build") == 0)
        {
            mode = 1;
        }
        
        if (strcmp(argv[i], "--run") == 0)
        {
            mode = 2;
        }
        
//        printf("argv[%d] = %s\n", i, argv[i]);
    }
    
    
    if (mode == 0)
    {
        printf(BOLDMAGENTA "PULL MODE!\n" RESET);
        char *git_pull_cmd = "git pull origin dev";
//        sprintf(git_pull_cmd,"%s: %s: %s", "git pull origin dev");

        printf("--- executing cmd: ");
        printf(BOLDYELLOW "%s\n" RESET, git_pull_cmd);
        
        int res = system(git_pull_cmd);
        
        printf("--- executing cmd: ");
        printf(BOLDYELLOW "%s " RESET, git_pull_cmd);
        printf("finished with result: ");
        printf(BOLDYELLOW "%d \n" RESET, res);
        
        if (res > 0)
            return 1;
    }
    else if (mode == 1)
    {
        printf(BOLDMAGENTA "BUILD MODE!\n" RESET);
    
    }
    else if (mode == 2) {
        printf(BOLDMAGENTA "RUN MODE!\n" RESET);
    }
    
    printf(BOLDMAGENTA   "thanks.\n" RESET);
    return 0;
}
