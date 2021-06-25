<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Digittrade DVB-T USB Stick remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Digittrade DVB-T USB Stick remote controller. */
/* Imported from af9015.h.
   Initial keytable was from Alain Kalker <miki@dds.nl> */

/* Digittrade DVB-T USB Stick */
अटल काष्ठा rc_map_table digittrade[] = अणु
	अणु 0x0000, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0001, KEY_EPG पूर्ण,             /* EPG */
	अणु 0x0002, KEY_VOLUMEDOWN पूर्ण,      /* Vol Dn */
	अणु 0x0003, KEY_TEXT पूर्ण,            /* TELETEXT */
	अणु 0x0004, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0005, KEY_MUTE पूर्ण,            /* MUTE */
	अणु 0x0006, KEY_POWER2 पूर्ण,          /* POWER */
	अणु 0x0009, KEY_ZOOM पूर्ण,            /* FULLSCREEN */
	अणु 0x000a, KEY_RECORD पूर्ण,          /* RECORD */
	अणु 0x000d, KEY_SUBTITLE पूर्ण,        /* SUBTITLE */
	अणु 0x000e, KEY_STOP पूर्ण,            /* STOP */
	अणु 0x0010, KEY_OK पूर्ण,              /* RETURN */
	अणु 0x0011, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0012, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0015, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0016, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0017, KEY_CHANNELDOWN पूर्ण,     /* Ch Dn */
	अणु 0x0019, KEY_CHANNELUP पूर्ण,       /* CH Up */
	अणु 0x001a, KEY_PAUSE पूर्ण,           /* PAUSE */
	अणु 0x001b, KEY_NUMERIC_1 पूर्ण,
	अणु 0x001d, KEY_AUDIO पूर्ण,           /* DUAL SOUND */
	अणु 0x001e, KEY_PLAY पूर्ण,            /* PLAY */
	अणु 0x001f, KEY_CAMERA पूर्ण,          /* SNAPSHOT */
	अणु 0x0040, KEY_VOLUMEUP पूर्ण,        /* Vol Up */
	अणु 0x0048, KEY_NUMERIC_7 पूर्ण,
	अणु 0x004c, KEY_NUMERIC_6 पूर्ण,
	अणु 0x004d, KEY_PLAYPAUSE पूर्ण,       /* TIMESHIFT */
	अणु 0x0054, KEY_NUMERIC_0 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list digittrade_map = अणु
	.map = अणु
		.scan     = digittrade,
		.size     = ARRAY_SIZE(digittrade),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_DIGITTRADE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_digittrade(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&digittrade_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_digittrade(व्योम)
अणु
	rc_map_unरेजिस्टर(&digittrade_map);
पूर्ण

module_init(init_rc_map_digittrade)
module_निकास(निकास_rc_map_digittrade)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
