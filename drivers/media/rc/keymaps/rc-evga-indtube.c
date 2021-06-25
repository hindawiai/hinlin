<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// evga-indtube.h - Keytable क्रम evga_indtube Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* EVGA inDtube
   Devin Heiपंचांगueller <devin.heiपंचांगueller@gmail.com>
 */

अटल काष्ठा rc_map_table evga_indtube[] = अणु
	अणु 0x12, KEY_POWERपूर्ण,
	अणु 0x02, KEY_MODEपूर्ण,	/* TV */
	अणु 0x14, KEY_MUTEपूर्ण,
	अणु 0x1a, KEY_CHANNELUPपूर्ण,
	अणु 0x16, KEY_TV2पूर्ण,	/* PIP */
	अणु 0x1d, KEY_VOLUMEUPपूर्ण,
	अणु 0x05, KEY_CHANNELDOWNपूर्ण,
	अणु 0x0f, KEY_PLAYPAUSEपूर्ण,
	अणु 0x19, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x1c, KEY_REWINDपूर्ण,
	अणु 0x0d, KEY_RECORDपूर्ण,
	अणु 0x18, KEY_FORWARDपूर्ण,
	अणु 0x1e, KEY_PREVIOUSपूर्ण,
	अणु 0x1b, KEY_STOPपूर्ण,
	अणु 0x1f, KEY_NEXTपूर्ण,
	अणु 0x13, KEY_CAMERAपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list evga_indtube_map = अणु
	.map = अणु
		.scan     = evga_indtube,
		.size     = ARRAY_SIZE(evga_indtube),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_EVGA_INDTUBE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_evga_indtube(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&evga_indtube_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_evga_indtube(व्योम)
अणु
	rc_map_unरेजिस्टर(&evga_indtube_map);
पूर्ण

module_init(init_rc_map_evga_indtube)
module_निकास(निकास_rc_map_evga_indtube)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
