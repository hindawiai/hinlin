<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Sigma Designs
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table tango_table[] = अणु
	अणु 0x4cb4a, KEY_POWER पूर्ण,
	अणु 0x4cb48, KEY_खाता पूर्ण,
	अणु 0x4cb0f, KEY_SETUP पूर्ण,
	अणु 0x4cb4d, KEY_SUSPEND पूर्ण,
	अणु 0x4cb4e, KEY_VOLUMEUP पूर्ण,
	अणु 0x4cb44, KEY_EJECTCD पूर्ण,
	अणु 0x4cb13, KEY_TV पूर्ण,
	अणु 0x4cb51, KEY_MUTE पूर्ण,
	अणु 0x4cb52, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x4cb41, KEY_NUMERIC_1 पूर्ण,
	अणु 0x4cb03, KEY_NUMERIC_2 पूर्ण,
	अणु 0x4cb42, KEY_NUMERIC_3 पूर्ण,
	अणु 0x4cb45, KEY_NUMERIC_4 पूर्ण,
	अणु 0x4cb07, KEY_NUMERIC_5 पूर्ण,
	अणु 0x4cb46, KEY_NUMERIC_6 पूर्ण,
	अणु 0x4cb55, KEY_NUMERIC_7 पूर्ण,
	अणु 0x4cb17, KEY_NUMERIC_8 पूर्ण,
	अणु 0x4cb56, KEY_NUMERIC_9 पूर्ण,
	अणु 0x4cb1b, KEY_NUMERIC_0 पूर्ण,
	अणु 0x4cb59, KEY_DELETE पूर्ण,
	अणु 0x4cb5a, KEY_CAPSLOCK पूर्ण,

	अणु 0x4cb47, KEY_BACK पूर्ण,
	अणु 0x4cb05, KEY_SWITCHVIDEOMODE पूर्ण,
	अणु 0x4cb06, KEY_UP पूर्ण,
	अणु 0x4cb43, KEY_LEFT पूर्ण,
	अणु 0x4cb01, KEY_RIGHT पूर्ण,
	अणु 0x4cb0a, KEY_DOWN पूर्ण,
	अणु 0x4cb02, KEY_ENTER पूर्ण,
	अणु 0x4cb4b, KEY_INFO पूर्ण,
	अणु 0x4cb09, KEY_HOME पूर्ण,

	अणु 0x4cb53, KEY_MENU पूर्ण,
	अणु 0x4cb12, KEY_PREVIOUS पूर्ण,
	अणु 0x4cb50, KEY_PLAY पूर्ण,
	अणु 0x4cb11, KEY_NEXT पूर्ण,
	अणु 0x4cb4f, KEY_TITLE पूर्ण,
	अणु 0x4cb0e, KEY_REWIND पूर्ण,
	अणु 0x4cb4c, KEY_STOP पूर्ण,
	अणु 0x4cb0d, KEY_FORWARD पूर्ण,
	अणु 0x4cb57, KEY_MEDIA_REPEAT पूर्ण,
	अणु 0x4cb16, KEY_ANGLE पूर्ण,
	अणु 0x4cb54, KEY_PAUSE पूर्ण,
	अणु 0x4cb15, KEY_SLOW पूर्ण,
	अणु 0x4cb5b, KEY_TIME पूर्ण,
	अणु 0x4cb1a, KEY_AUDIO पूर्ण,
	अणु 0x4cb58, KEY_SUBTITLE पूर्ण,
	अणु 0x4cb19, KEY_ZOOM पूर्ण,

	अणु 0x4cb5f, KEY_RED पूर्ण,
	अणु 0x4cb1e, KEY_GREEN पूर्ण,
	अणु 0x4cb5c, KEY_YELLOW पूर्ण,
	अणु 0x4cb1d, KEY_BLUE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tango_map = अणु
	.map = अणु
		.scan = tango_table,
		.size = ARRAY_SIZE(tango_table),
		.rc_proto = RC_PROTO_NECX,
		.name = RC_MAP_TANGO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tango(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tango_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tango(व्योम)
अणु
	rc_map_unरेजिस्टर(&tango_map);
पूर्ण

module_init(init_rc_map_tango)
module_निकास(निकास_rc_map_tango)

MODULE_AUTHOR("Sigma Designs");
MODULE_LICENSE("GPL");
