#include "initfile.h"
#include "gamelib/vfs.h"
#include "cbase/kassert.h"
#include "cbase/cbase.h"

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#include <string.h>

/* Must be alphabetically sorted. */
static struct initvar {
	const char *name;
	int val;
} s_initvars[] = {
	{ "active_portal", 8 },
	{ "arrow", 1 },
	{ "credits_map", 0x33 },
	{ "demo", 1 },
	{ "demo_version", 0 },
	{ "end_map", 0x41 },
	{ "help_map", 0x31 },
	{ "menu_map", 0x30 },
	{ "ndemos", 49 },
	{ "nmaps_to_win", 60 },
	{ "over_map", 0x40 },
	{ "start_map", 0x02 },
	{ "start_portal", 1 },
	{ "translators_portal", 2 },
	{ "win_map", 0x43 },
};

static int compar(const void *pk, const void *pe)
{
	const struct initvar *pivar;

	pivar = (const struct initvar *) pe;
	return strcmp((const char *) pk, pivar->name);
}

int initfile_getvar(const char *name)
{
	struct initvar *pivar;

	pivar = bsearch(name, s_initvars, NELEMS(s_initvars),
			sizeof(s_initvars[0]), compar);
	if (pivar != NULL) {
		return pivar->val;
	} else {
		ktrace("unknown init var %s", name);
		return 0;
	}
}

void initfile_load(void)
{
	int n;
	FILE *fp;
	struct initvar *pivar;
	char name[32];

	if ((fp = open_file("data/init.txt", NULL)) == NULL) {
		ktrace("cannot open init.txt");
		return;
	}

	while (fscanf(fp, " %31s %i ", name, &n) == 2) {
		if (name[0] == '~')
			break;

		pivar = bsearch(name, s_initvars, NELEMS(s_initvars),
				sizeof(s_initvars[0]), compar);
		if (pivar != NULL) {
			pivar->val = n;
		} else {
			ktrace("unknown init var %s when loading", name);
		}
	}

	fclose(fp);
	return;
}
