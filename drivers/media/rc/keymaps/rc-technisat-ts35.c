<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-technisat-ts35.c - Keytable क्रम TechniSat TS35 remote
 *
 * Copyright (c) 2013 by Jan Klथघtzke <jan@kloetzke.net>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table technisat_ts35[] = अणु
	अणु0x32, KEY_MUTEपूर्ण,
	अणु0x07, KEY_MEDIAपूर्ण,
	अणु0x1c, KEY_ABपूर्ण,
	अणु0x33, KEY_POWERपूर्ण,

	अणु0x3e, KEY_NUMERIC_1पूर्ण,
	अणु0x3d, KEY_NUMERIC_2पूर्ण,
	अणु0x3c, KEY_NUMERIC_3पूर्ण,
	अणु0x3b, KEY_NUMERIC_4पूर्ण,
	अणु0x3a, KEY_NUMERIC_5पूर्ण,
	अणु0x39, KEY_NUMERIC_6पूर्ण,
	अणु0x38, KEY_NUMERIC_7पूर्ण,
	अणु0x37, KEY_NUMERIC_8पूर्ण,
	अणु0x36, KEY_NUMERIC_9पूर्ण,
	अणु0x3f, KEY_NUMERIC_0पूर्ण,
	अणु0x35, KEY_DIGITSपूर्ण,
	अणु0x2c, KEY_TVपूर्ण,

	अणु0x20, KEY_INFOपूर्ण,
	अणु0x2d, KEY_MENUपूर्ण,
	अणु0x1f, KEY_UPपूर्ण,
	अणु0x1e, KEY_DOWNपूर्ण,
	अणु0x2e, KEY_LEFTपूर्ण,
	अणु0x2f, KEY_RIGHTपूर्ण,
	अणु0x28, KEY_OKपूर्ण,
	अणु0x10, KEY_EPGपूर्ण,
	अणु0x1d, KEY_BACKपूर्ण,

	अणु0x14, KEY_REDपूर्ण,
	अणु0x13, KEY_GREENपूर्ण,
	अणु0x12, KEY_YELLOWपूर्ण,
	अणु0x11, KEY_BLUEपूर्ण,

	अणु0x09, KEY_SELECTपूर्ण,
	अणु0x03, KEY_TEXTपूर्ण,
	अणु0x16, KEY_STOPपूर्ण,
	अणु0x30, KEY_HELPपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list technisat_ts35_map = अणु
	.map = अणु
		.scan     = technisat_ts35,
		.size     = ARRAY_SIZE(technisat_ts35),
		.rc_proto = RC_PROTO_UNKNOWN,
		.name     = RC_MAP_TECHNISAT_TS35,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&technisat_ts35_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&technisat_ts35_map);
पूर्ण

module_init(init_rc_map)
module_निकास(निकास_rc_map)

MODULE_LICENSE("GPL");
