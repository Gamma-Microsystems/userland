/**
 * @brief Print the number of available processors.
 *
 * @copyright
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2021 K. Lange
 * Copyright (C) 2024 Gamma Microsystems
 */
#include <stdio.h>
#include <sys/sysfunc.h>

int main(int argc, char * argv[]) {
	printf("%d\n", sysfunc(SIRIUS_SYS_FUNC_NPROC, NULL));
	return 0;
}
