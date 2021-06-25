<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * keymap imported from cxusb.c
 *
 * Copyright (C) 2016 Sean Young
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table rc_map_d680_dmb_table[] = अणु
	अणु 0x0038, KEY_SWITCHVIDEOMODE पूर्ण,	/* TV/AV */
	अणु 0x080c, KEY_ZOOM पूर्ण,
	अणु 0x0800, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0001, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0802, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0003, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0804, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0005, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0806, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0007, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0808, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0009, KEY_NUMERIC_9 पूर्ण,
	अणु 0x000a, KEY_MUTE पूर्ण,
	अणु 0x0829, KEY_BACK पूर्ण,
	अणु 0x0012, KEY_CHANNELUP पूर्ण,
	अणु 0x0813, KEY_CHANNELDOWN पूर्ण,
	अणु 0x002b, KEY_VOLUMEUP पूर्ण,
	अणु 0x082c, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0020, KEY_UP पूर्ण,
	अणु 0x0821, KEY_DOWN पूर्ण,
	अणु 0x0011, KEY_LEFT पूर्ण,
	अणु 0x0810, KEY_RIGHT पूर्ण,
	अणु 0x000d, KEY_OK पूर्ण,
	अणु 0x081f, KEY_RECORD पूर्ण,
	अणु 0x0017, KEY_PLAYPAUSE पूर्ण,
	अणु 0x0816, KEY_PLAYPAUSE पूर्ण,
	अणु 0x000b, KEY_STOP पूर्ण,
	अणु 0x0827, KEY_FASTFORWARD पूर्ण,
	अणु 0x0026, KEY_REWIND पूर्ण,
	अणु 0x081e, KEY_UNKNOWN पूर्ण,    /* Time Shअगरt */
	अणु 0x000e, KEY_UNKNOWN पूर्ण,    /* Snapshot */
	अणु 0x082d, KEY_UNKNOWN पूर्ण,    /* Mouse Cursor */
	अणु 0x000f, KEY_UNKNOWN पूर्ण,    /* Minimize/Maximize */
	अणु 0x0814, KEY_SHUFFLE पूर्ण,    /* Shuffle */
	अणु 0x0025, KEY_POWER पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list d680_dmb_map = अणु
	.map = अणु
		.scan     = rc_map_d680_dmb_table,
		.size     = ARRAY_SIZE(rc_map_d680_dmb_table),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_D680_DMB,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_d680_dmb(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&d680_dmb_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_d680_dmb(व्योम)
अणु
	rc_map_unरेजिस्टर(&d680_dmb_map);
पूर्ण

module_init(init_rc_map_d680_dmb)
module_निकास(निकास_rc_map_d680_dmb)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
