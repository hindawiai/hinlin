<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// msi-tvanywhere-plus.h - Keytable क्रम msi_tvanywhere_plus Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
  Keycodes क्रम remote on the MSI TV@nywhere Plus. The controller IC on the card
  is marked "KS003". The controller is I2C at address 0x30, but करोes not seem
  to respond to probes until a पढ़ो is perक्रमmed from a valid device.
  I करोn't know why...

  Note: This remote may be of similar or identical design to the
  Pixelview remote (?).  The raw codes and duplicate button codes
  appear to be the same.

  Henry Wong <henry@stuffedcow.net>
  Some changes to क्रमmatting and keycodes by Mark Schultz <n9xmj@yahoo.com>
*/

अटल काष्ठा rc_map_table msi_tvanywhere_plus[] = अणु

/*  ---- Remote Button Layout ----

    POWER   SOURCE  SCAN    MUTE
    TV/FM   1       2       3
    |>      4       5       6
    <|      7       8       9
    ^^UP    0       +       RECALL
    vvDN    RECORD  STOP    PLAY

	MINIMIZE          ZOOM

		  CH+
      VOL-                   VOL+
		  CH-

	SNAPSHOT           MTS

     <<      FUNC    >>     RESET
*/

	अणु 0x01, KEY_NUMERIC_1 पूर्ण,	/* 1 */
	अणु 0x0b, KEY_NUMERIC_2 पूर्ण,	/* 2 */
	अणु 0x1b, KEY_NUMERIC_3 पूर्ण,	/* 3 */
	अणु 0x05, KEY_NUMERIC_4 पूर्ण,	/* 4 */
	अणु 0x09, KEY_NUMERIC_5 पूर्ण,	/* 5 */
	अणु 0x15, KEY_NUMERIC_6 पूर्ण,	/* 6 */
	अणु 0x06, KEY_NUMERIC_7 पूर्ण,	/* 7 */
	अणु 0x0a, KEY_NUMERIC_8 पूर्ण,	/* 8 */
	अणु 0x12, KEY_NUMERIC_9 पूर्ण,	/* 9 */
	अणु 0x02, KEY_NUMERIC_0 पूर्ण,	/* 0 */
	अणु 0x10, KEY_KPPLUS पूर्ण,		/* + */
	अणु 0x13, KEY_AGAIN पूर्ण,		/* Recall */

	अणु 0x1e, KEY_POWER पूर्ण,		/* Power */
	अणु 0x07, KEY_VIDEO पूर्ण,		/* Source */
	अणु 0x1c, KEY_SEARCH पूर्ण,		/* Scan */
	अणु 0x18, KEY_MUTE पूर्ण,		/* Mute */

	अणु 0x03, KEY_RADIO पूर्ण,		/* TV/FM */
	/* The next four keys are duplicates that appear to send the
	   same IR code as Ch+, Ch-, >>, and << .  The raw code asचिन्हित
	   to them is the actual code + 0x20 - they will never be
	   detected as such unless some way is discovered to distinguish
	   these buttons from those that have the same code. */
	अणु 0x3f, KEY_RIGHT पूर्ण,		/* |> and Ch+ */
	अणु 0x37, KEY_LEFT पूर्ण,		/* <| and Ch- */
	अणु 0x2c, KEY_UP पूर्ण,		/* ^^Up and >> */
	अणु 0x24, KEY_DOWN पूर्ण,		/* vvDn and << */

	अणु 0x00, KEY_RECORD पूर्ण,		/* Record */
	अणु 0x08, KEY_STOP पूर्ण,		/* Stop */
	अणु 0x11, KEY_PLAY पूर्ण,		/* Play */

	अणु 0x0f, KEY_CLOSE पूर्ण,		/* Minimize */
	अणु 0x19, KEY_ZOOM पूर्ण,		/* Zoom */
	अणु 0x1a, KEY_CAMERA पूर्ण,		/* Snapshot */
	अणु 0x0d, KEY_LANGUAGE पूर्ण,		/* MTS */

	अणु 0x14, KEY_VOLUMEDOWN पूर्ण,	/* Vol- */
	अणु 0x16, KEY_VOLUMEUP पूर्ण,		/* Vol+ */
	अणु 0x17, KEY_CHANNELDOWN पूर्ण,	/* Ch- */
	अणु 0x1f, KEY_CHANNELUP पूर्ण,	/* Ch+ */

	अणु 0x04, KEY_REWIND पूर्ण,		/* << */
	अणु 0x0e, KEY_MENU पूर्ण,		/* Function */
	अणु 0x0c, KEY_FASTFORWARD पूर्ण,	/* >> */
	अणु 0x1d, KEY_RESTART पूर्ण,		/* Reset */
पूर्ण;

अटल काष्ठा rc_map_list msi_tvanywhere_plus_map = अणु
	.map = अणु
		.scan     = msi_tvanywhere_plus,
		.size     = ARRAY_SIZE(msi_tvanywhere_plus),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_MSI_TVANYWHERE_PLUS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_msi_tvanywhere_plus(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&msi_tvanywhere_plus_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_msi_tvanywhere_plus(व्योम)
अणु
	rc_map_unरेजिस्टर(&msi_tvanywhere_plus_map);
पूर्ण

module_init(init_rc_map_msi_tvanywhere_plus)
module_निकास(निकास_rc_map_msi_tvanywhere_plus)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
