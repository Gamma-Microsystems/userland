/**
 * @file  apps/misaka-test.c
 * @brief Test app for Misaka with a bunch of random stuff.
 * @copyright
 * This file is part of ToaruOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2021 K. Lange
 * Copyright (C) 2024 Gamma Microsystems
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>

#include <sirius/graphics.h>

static void demo_drawWallpaper(void) {
	/* Set up a wrapper context for the framebuffer */
	gfx_context_t * ctx = init_graphics_fullscreen();

	/* Load the wallpaper. */
	sprite_t wallpaper = { 0 };
	load_sprite(&wallpaper, "/usr/share/wallpaper.jpg");
	wallpaper.alpha = ALPHA_EMBEDDED;

	printf("wallpaper sprite info: %d x %d\n", wallpaper.width, wallpaper.height);

	draw_sprite_scaled(ctx, &wallpaper, 0, 0, 1440, 900);
	flip(ctx);
	//blur_context_box(&ctx, 10);
}

int main(int argc, char * argv[]) {
	demo_drawWallpaper();

	//execve("/bin/kuroko",(char*[]){"kuroko",NULL},(char*[]){NULL});
	char * args[] = {
		"/bin/sh",
		"-c",
		"sleep 2; echo hi; echo glorp",
		NULL,
	};
	pid_t pid = fork();
	if (!pid) {
		printf("returned from fork in child\n");
		execvp(args[0], args);
		exit(1);
	} else {
		printf("returned from fork with pid = %d\n", pid);
		int status;
		waitpid(pid, &status, 0);
		printf("done with waitpid, looping\n");
		while (1) {
			sched_yield();
		}
		return WEXITSTATUS(status);
	}

	return 0;
}
