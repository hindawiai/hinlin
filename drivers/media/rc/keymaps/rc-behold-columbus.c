<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// behold-columbus.h - Keytable क्रम behold_columbus Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Beholder Intl. Ltd. 2008
 * Dmitry Belimov d.belimov@google.com
 * Keytable is used by BeholdTV Columbus
 * The "ascii-art picture" below (in comments, first row
 * is the keycode in hex, and subsequent row(s) shows
 * the button labels (several variants when appropriate)
 * helps to decide which keycodes to assign to the buttons.
 */

अटल काष्ठा rc_map_table behold_columbus[] = अणु

	/*  0x13   0x11   0x1C   0x12  *
	 *  Mute  Source  TV/FM  Power *
	 *                             */

	अणु 0x13, KEY_MUTE पूर्ण,
	अणु 0x11, KEY_VIDEO पूर्ण,
	अणु 0x1C, KEY_TUNER पूर्ण,	/* KEY_TV/KEY_RADIO	*/
	अणु 0x12, KEY_POWER पूर्ण,

	/*  0x01    0x02    0x03  0x0D    *
	 *   1       2       3   Stereo   *
	 *				  *
	 *  0x04    0x05    0x06  0x19    *
	 *   4       5       6   Snapshot *
	 *				  *
	 *  0x07    0x08    0x09  0x10    *
	 *   7       8       9    Zoom	  *
	 *                                */
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0D, KEY_SETUP पूर्ण,	  /* Setup key */
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x19, KEY_CAMERA पूर्ण,	/* Snapshot key */
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x10, KEY_ZOOM पूर्ण,

	/*  0x0A    0x00    0x0B       0x0C   *
	 * RECALL    0    ChannelUp  VolumeUp *
	 *                                    */
	अणु 0x0A, KEY_AGAIN पूर्ण,
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0B, KEY_CHANNELUP पूर्ण,
	अणु 0x0C, KEY_VOLUMEUP पूर्ण,

	/*   0x1B      0x1D      0x15        0x18     *
	 * Timeshअगरt  Record  ChannelDown  VolumeDown *
	 *                                            */

	अणु 0x1B, KEY_TIME पूर्ण,
	अणु 0x1D, KEY_RECORD पूर्ण,
	अणु 0x15, KEY_CHANNELDOWN पूर्ण,
	अणु 0x18, KEY_VOLUMEDOWN पूर्ण,

	/*   0x0E   0x1E     0x0F     0x1A  *
	 *   Stop   Pause  Previous   Next  *
	 *                                  */

	अणु 0x0E, KEY_STOP पूर्ण,
	अणु 0x1E, KEY_PAUSE पूर्ण,
	अणु 0x0F, KEY_PREVIOUS पूर्ण,
	अणु 0x1A, KEY_NEXT पूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list behold_columbus_map = अणु
	.map = अणु
		.scan     = behold_columbus,
		.size     = ARRAY_SIZE(behold_columbus),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_BEHOLD_COLUMBUS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_behold_columbus(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&behold_columbus_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_behold_columbus(व्योम)
अणु
	rc_map_unरेजिस्टर(&behold_columbus_map);
पूर्ण

module_init(init_rc_map_behold_columbus)
module_निकास(निकास_rc_map_behold_columbus)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
