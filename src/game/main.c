/*
Copyright (c) 2016-2017 Jorge Giner Cordero

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "cfg/cfg.h"

#ifdef DEBUG
#ifdef HAVE_MCHECK_H
#include <mcheck.h>
#endif
#endif

#include "game.h"
#include "bitmaps.h"
#include "sounds.h"
#include "data.h"
#include "cheats.h"
#include "initfile.h"
#include "input.h"
#include "menu.h"
#include "balloon.h"
#include "cosmonau.h"
#include "oxigen.h"
#include "wasp.h"
#include "caterpil.h"
#include "spider.h"
#include "platform.h"
#include "drop.h"
#include "moth.h"
#include "grasshop.h"
#include "lavatong.h"
#include "stargate.h"
#include "bat.h"
#include "fish.h"
#include "fenix.h"
#include "draco.h"
#include "lavashot.h"
#include "hud.h"
#include "menu_st.h"
#include "buy_st.h"
#include "gameover.h"
#include "hiscore.h"
#include "arrow.h"
#include "pad.h"
#include "text.h"
#include "prefs.h"
#include "strdraw.h"
#include "modplay.h"
#include "msgbox.h"
#include "demosave.h"
#include "confpath.h"
#include "log.h"
#include "tilengin.h"
#include "crypt.h"
#include "coroutin.h"
#include "cmdline.h"
#include "gamelib/bmp.h"
#include "gamelib/lang.h"
#include "gamelib/mixer.h"
#include "gamelib/state.h"
#include "gamelib/vfs.h"
#include "kernel/kernel.h"
#include "cbase/kassert.h"
#include <SDL.h>

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

int main(int argc, char *argv[])
{
#ifdef DEBUG
#ifdef HAVE_MCHECK_H
	mtrace();
#endif
#endif
	/*
	 * All modules are initialized here.
	 */

	srand(time(0));

	/* Log to console always. */
	kassert_init();
	kassert_set_log_fun(kernel_get_device()->trace);

	/* I suppose it is safe to run this on a mobile, but just
	 * in case it is not, don't do it there.
	 */
	if (!PP_ANDROID) {
		read_cmd_line(argc, argv);
	}

	crypt_init();
	coroutin_init();
	bmp_draw_init();
	lang_init();
	state_init();
	vfs_init();
	game_init();
	cheats_init();
	initfile_init();
	input_init();
	menu_init();
	tilengin_init();

	confpath_init();
	log_init();
	text_init();
	prefs_init();
	mixer_init();
	data_init();
	strdraw_init();
	msgbox_init();
	balloon_init();
	cosmonau_init();
	oxigen_init();
	wasp_init();
	caterpil_init();
	spider_init();
	platform_init();
	drop_init();
	moth_init();
	grasshop_init();
	lavatong_init();
	stargate_init();
	bat_init();
	fish_init();
	fenix_init();
	draco_init();
	lavashot_init();
	hud_init();
	menu_st_init();
	buy_st_init();
	gameover_init();
	hiscore_init();
	demosave_init();
	arrow_init();
	pad_init();

	/* Main loop */

	game_run();

	/*
	 * All modules are de-initialized here.
	 */

	modplay_done();
	bitmaps_done();
	sounds_done();
	text_done();
	log_done();

	return EXIT_SUCCESS;
}
