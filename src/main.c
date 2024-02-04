/* vim: set tabstop=4:softtabstop=0:shiftSC_WIDTH=4:noexpandtab */
/*
 * Title:		Agon Light Keyboard Multi-key test
 * Author:		James Grimwood
 * Created:		4/2/2024
 *
 */

#include <string.h>
#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>
#include <stdlib.h>
#include <stdint.h>
#include "keyboard.h"

static volatile SYSVAR *sv;
int main()
{
	sv = vdp_vdu_init();
	if (vdp_key_init() == -1)
		return 1;

	volatile uint8_t *keymap = init_keys();

	uint8_t keys[4] = {0,0,0,0};
	while (1) {
		update_keys();
		vdp_clear_screen();
		printf ("Agon Light 2 Keyboard multi-keypress test\n");
		printf ("James Grimwood - https://ncot.uk 2024\n");
		printf ("If this doesn't work, read the readme!\n");
		printf ("\n\n");
		printf ("Arrow key test:\n");
		printf ("Press the arrow keys on your keyboard!\n");
		
		keys[0] = IS_KEY_HELD(KEY_UP);
		keys[1] = IS_KEY_HELD(KEY_DOWN);
		keys[2] = IS_KEY_HELD(KEY_LEFT);
		keys[3] = IS_KEY_HELD(KEY_RIGHT);

		printf ("Keys pressed: ");
		if (keys[0]) printf ("[U] ");
		if (keys[1]) printf ("[D] ");
		if (keys[2]) printf ("[L] ");
		if (keys[3]) printf ("[R] ");
		printf ("\n\n");

		printf ("Raw key data for the whole keyboard:\n");
		for (int i = 0; i < 15; i++) {
			printf ("%02x ", *(keymap+i));
		}
		printf ("\n");

		waitvblank();
	}

	return 0;
}
