<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// manli.h - Keytable क्रम manli Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Michael Tokarev <mjt@tls.msk.ru>
   keytable is used by MANLI MTV00[0x0c] and BeholdTV 40[13] at
   least, and probably other cards too.
   The "ascii-art picture" below (in comments, first row
   is the keycode in hex, and subsequent row(s) shows
   the button labels (several variants when appropriate)
   helps to decide which keycodes to assign to the buttons.
 */

अटल काष्ठा rc_map_table manli[] = अणु

	/*  0x1c            0x12  *
	 * FUNCTION         POWER *
	 *   FM              (|)  *
	 *                        */
	अणु 0x1c, KEY_RADIO पूर्ण,	/*XXX*/
	अणु 0x12, KEY_POWER पूर्ण,

	/*  0x01    0x02    0x03  *
	 *   1       2       3    *
	 *                        *
	 *  0x04    0x05    0x06  *
	 *   4       5       6    *
	 *                        *
	 *  0x07    0x08    0x09  *
	 *   7       8       9    *
	 *                        */
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,

	/*  0x0a    0x00    0x17  *
	 * RECALL    0      +100  *
	 *                  PLUS  *
	 *                        */
	अणु 0x0a, KEY_AGAIN पूर्ण,	/*XXX KEY_REWIND? */
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x17, KEY_DIGITS पूर्ण,	/*XXX*/

	/*  0x14            0x10  *
	 *  MENU            INFO  *
	 *  OSD                   */
	अणु 0x14, KEY_MENU पूर्ण,
	अणु 0x10, KEY_INFO पूर्ण,

	/*          0x0b          *
	 *           Up           *
	 *                        *
	 *  0x18    0x16    0x0c  *
	 *  Left     Ok     Right *
	 *                        *
	 *         0x015          *
	 *         Down           *
	 *                        */
	अणु 0x0b, KEY_UP पूर्ण,
	अणु 0x18, KEY_LEFT पूर्ण,
	अणु 0x16, KEY_OK पूर्ण,	/*XXX KEY_SELECT? KEY_ENTER? */
	अणु 0x0c, KEY_RIGHT पूर्ण,
	अणु 0x15, KEY_DOWN पूर्ण,

	/*  0x11            0x0d  *
	 *  TV/AV           MODE  *
	 *  SOURCE         STEREO *
	 *                        */
	अणु 0x11, KEY_TV पूर्ण,	/*XXX*/
	अणु 0x0d, KEY_MODE पूर्ण,	/*XXX there's no KEY_STEREO	*/

	/*  0x0f    0x1b    0x1a  *
	 *  AUDIO   Vol+    Chan+ *
	 *        TIMESHIFT???    *
	 *                        *
	 *  0x0e    0x1f    0x1e  *
	 *  SLEEP   Vol-    Chan- *
	 *                        */
	अणु 0x0f, KEY_AUDIO पूर्ण,
	अणु 0x1b, KEY_VOLUMEUP पूर्ण,
	अणु 0x1a, KEY_CHANNELUP पूर्ण,
	अणु 0x0e, KEY_TIME पूर्ण,
	अणु 0x1f, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1e, KEY_CHANNELDOWN पूर्ण,

	/*         0x13     0x19  *
	 *         MUTE   SNAPSHOT*
	 *                        */
	अणु 0x13, KEY_MUTE पूर्ण,
	अणु 0x19, KEY_CAMERA पूर्ण,

	/* 0x1d unused ? */
पूर्ण;

अटल काष्ठा rc_map_list manli_map = अणु
	.map = अणु
		.scan     = manli,
		.size     = ARRAY_SIZE(manli),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_MANLI,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_manli(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&manli_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_manli(व्योम)
अणु
	rc_map_unरेजिस्टर(&manli_map);
पूर्ण

module_init(init_rc_map_manli)
module_निकास(निकास_rc_map_manli)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
