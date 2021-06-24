<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-tivo.c - Keytable क्रम TiVo remotes
 *
 * Copyright (c) 2011 by Jarod Wilson <jarod@redhat.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Initial mapping is क्रम the TiVo remote included in the Nero LiquidTV bundle,
 * which also ships with a TiVo-bअक्रमed IR transceiver, supported by the mceusb
 * driver. Note that the remote uses an NEC-ish protocol, but instead of having
 * a command/not_command pair, it has a venकरोr ID of 0x3085, but some keys, the
 * NEC extended checksums करो pass, so the table presently has the पूर्णांकended
 * values and the checksum-passed versions क्रम those keys.
 */
अटल काष्ठा rc_map_table tivo[] = अणु
	अणु 0x3085f009, KEY_MEDIA पूर्ण,	/* TiVo Button */
	अणु 0x3085e010, KEY_POWER2 पूर्ण,	/* TV Power */
	अणु 0x3085e011, KEY_TV पूर्ण,		/* Live TV/Swap */
	अणु 0x3085c034, KEY_VIDEO_NEXT पूर्ण,	/* TV Input */
	अणु 0x3085e013, KEY_INFO पूर्ण,
	अणु 0x3085a05f, KEY_CYCLEWINDOWS पूर्ण, /* Winकरोw */
	अणु 0x0085305f, KEY_CYCLEWINDOWS पूर्ण,
	अणु 0x3085c036, KEY_EPG पूर्ण,	/* Guide */

	अणु 0x3085e014, KEY_UP पूर्ण,
	अणु 0x3085e016, KEY_DOWN पूर्ण,
	अणु 0x3085e017, KEY_LEFT पूर्ण,
	अणु 0x3085e015, KEY_RIGHT पूर्ण,

	अणु 0x3085e018, KEY_SCROLLDOWN पूर्ण,	/* Red Thumbs Down */
	अणु 0x3085e019, KEY_SELECT पूर्ण,
	अणु 0x3085e01a, KEY_SCROLLUP पूर्ण,	/* Green Thumbs Up */

	अणु 0x3085e01c, KEY_VOLUMEUP पूर्ण,
	अणु 0x3085e01d, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x3085e01b, KEY_MUTE पूर्ण,
	अणु 0x3085d020, KEY_RECORD पूर्ण,
	अणु 0x3085e01e, KEY_CHANNELUP पूर्ण,
	अणु 0x3085e01f, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0085301f, KEY_CHANNELDOWN पूर्ण,

	अणु 0x3085d021, KEY_PLAY पूर्ण,
	अणु 0x3085d023, KEY_PAUSE पूर्ण,
	अणु 0x3085d025, KEY_SLOW पूर्ण,
	अणु 0x3085d022, KEY_REWIND पूर्ण,
	अणु 0x3085d024, KEY_FASTFORWARD पूर्ण,
	अणु 0x3085d026, KEY_PREVIOUS पूर्ण,
	अणु 0x3085d027, KEY_NEXT पूर्ण,	/* ->| */

	अणु 0x3085b044, KEY_ZOOM पूर्ण,	/* Aspect */
	अणु 0x3085b048, KEY_STOP पूर्ण,
	अणु 0x3085b04a, KEY_DVD पूर्ण,	/* DVD Menu */

	अणु 0x3085d028, KEY_NUMERIC_1 पूर्ण,
	अणु 0x3085d029, KEY_NUMERIC_2 पूर्ण,
	अणु 0x3085d02a, KEY_NUMERIC_3 पूर्ण,
	अणु 0x3085d02b, KEY_NUMERIC_4 पूर्ण,
	अणु 0x3085d02c, KEY_NUMERIC_5 पूर्ण,
	अणु 0x3085d02d, KEY_NUMERIC_6 पूर्ण,
	अणु 0x3085d02e, KEY_NUMERIC_7 पूर्ण,
	अणु 0x3085d02f, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0085302f, KEY_NUMERIC_8 पूर्ण,
	अणु 0x3085c030, KEY_NUMERIC_9 पूर्ण,
	अणु 0x3085c031, KEY_NUMERIC_0 पूर्ण,
	अणु 0x3085c033, KEY_ENTER पूर्ण,
	अणु 0x3085c032, KEY_CLEAR पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tivo_map = अणु
	.map = अणु
		.scan     = tivo,
		.size     = ARRAY_SIZE(tivo),
		.rc_proto = RC_PROTO_NEC32,
		.name     = RC_MAP_TIVO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tivo(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tivo_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tivo(व्योम)
अणु
	rc_map_unरेजिस्टर(&tivo_map);
पूर्ण

module_init(init_rc_map_tivo)
module_निकास(निकास_rc_map_tivo)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
