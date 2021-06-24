<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Keytable क्रम Xbox DVD remote
// Copyright (c) 2018 by Benjamin Valentin <benpicco@googlemail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* based on lircd.conf.xbox */
अटल काष्ठा rc_map_table xbox_dvd[] = अणु
	अणु0xa0b, KEY_OKपूर्ण,
	अणु0xaa6, KEY_UPपूर्ण,
	अणु0xaa7, KEY_DOWNपूर्ण,
	अणु0xaa8, KEY_RIGHTपूर्ण,
	अणु0xaa9, KEY_LEFTपूर्ण,
	अणु0xac3, KEY_INFOपूर्ण,

	अणु0xac6, KEY_NUMERIC_9पूर्ण,
	अणु0xac7, KEY_NUMERIC_8पूर्ण,
	अणु0xac8, KEY_NUMERIC_7पूर्ण,
	अणु0xac9, KEY_NUMERIC_6पूर्ण,
	अणु0xaca, KEY_NUMERIC_5पूर्ण,
	अणु0xacb, KEY_NUMERIC_4पूर्ण,
	अणु0xacc, KEY_NUMERIC_3पूर्ण,
	अणु0xacd, KEY_NUMERIC_2पूर्ण,
	अणु0xace, KEY_NUMERIC_1पूर्ण,
	अणु0xacf, KEY_NUMERIC_0पूर्ण,

	अणु0xad5, KEY_ANGLEपूर्ण,
	अणु0xad8, KEY_BACKपूर्ण,
	अणु0xadd, KEY_PREVIOUSSONGपूर्ण,
	अणु0xadf, KEY_NEXTSONGपूर्ण,
	अणु0xae0, KEY_STOPपूर्ण,
	अणु0xae2, KEY_REWINDपूर्ण,
	अणु0xae3, KEY_FASTFORWARDपूर्ण,
	अणु0xae5, KEY_TITLEपूर्ण,
	अणु0xae6, KEY_PAUSEपूर्ण,
	अणु0xaea, KEY_PLAYपूर्ण,
	अणु0xaf7, KEY_MENUपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list xbox_dvd_map = अणु
	.map = अणु
		.scan     = xbox_dvd,
		.size     = ARRAY_SIZE(xbox_dvd),
		.rc_proto = RC_PROTO_XBOX_DVD,
		.name     = RC_MAP_XBOX_DVD,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&xbox_dvd_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&xbox_dvd_map);
पूर्ण

module_init(init_rc_map)
module_निकास(निकास_rc_map)

MODULE_LICENSE("GPL");
