<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TrekStor remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* TrekStor DVB-T USB Stick remote controller. */
/* Imported from af9015.h.
   Initial keytable was from Marc Schneider <macke@macke.org> */
अटल काष्ठा rc_map_table trekstor[] = अणु
	अणु 0x0084, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0085, KEY_MUTE पूर्ण,            /* Mute */
	अणु 0x0086, KEY_HOMEPAGE पूर्ण,        /* Home */
	अणु 0x0087, KEY_UP पूर्ण,              /* Up */
	अणु 0x0088, KEY_OK पूर्ण,              /* OK */
	अणु 0x0089, KEY_RIGHT पूर्ण,           /* Right */
	अणु 0x008a, KEY_FASTFORWARD पूर्ण,     /* Fast क्रमward */
	अणु 0x008b, KEY_VOLUMEUP पूर्ण,        /* Volume + */
	अणु 0x008c, KEY_DOWN पूर्ण,            /* Down */
	अणु 0x008d, KEY_PLAY पूर्ण,            /* Play/Pause */
	अणु 0x008e, KEY_STOP पूर्ण,            /* Stop */
	अणु 0x008f, KEY_EPG पूर्ण,             /* Info/EPG */
	अणु 0x0090, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0091, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0092, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0093, KEY_CHANNELDOWN पूर्ण,     /* Channel - */
	अणु 0x0094, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0095, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0096, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0097, KEY_CHANNELUP पूर्ण,       /* Channel + */
	अणु 0x0098, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0099, KEY_NUMERIC_6 पूर्ण,
	अणु 0x009a, KEY_NUMERIC_3 पूर्ण,
	अणु 0x009b, KEY_VOLUMEDOWN पूर्ण,      /* Volume - */
	अणु 0x009c, KEY_TV पूर्ण,              /* TV */
	अणु 0x009d, KEY_RECORD पूर्ण,          /* Record */
	अणु 0x009e, KEY_REWIND पूर्ण,          /* Rewind */
	अणु 0x009f, KEY_LEFT पूर्ण,            /* Left */
पूर्ण;

अटल काष्ठा rc_map_list trekstor_map = अणु
	.map = अणु
		.scan     = trekstor,
		.size     = ARRAY_SIZE(trekstor),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_TREKSTOR,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_trekstor(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&trekstor_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_trekstor(व्योम)
अणु
	rc_map_unरेजिस्टर(&trekstor_map);
पूर्ण

module_init(init_rc_map_trekstor)
module_निकास(निकास_rc_map_trekstor)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
