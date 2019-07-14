/**
 *  xen
 *
 *  Created by Sanzhar Kudaibergen on 7/11/19.
 *  Copyright © 2019 Sanzhar Kudaibergen. All rights reserved.
 */

#include <stdio.h>

#include "color_scheme.h"
#include "orchestra.h"


int main(int argc, const char **argv) {
    printf(BOLDMAGENTA   "welcome.\n" RESET);
    int res = orchestrate(argc, argv);
    
    if (res != 0)
        return res;
    
    printf(BOLDMAGENTA   "thanks.\n" RESET);
    return 0;
    
}
