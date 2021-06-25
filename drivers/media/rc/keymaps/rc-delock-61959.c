<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-delock-61959.c - Keytable क्रम Delock
 *
 * Copyright (c) 2013 by Jakob Haufe <sur5r@sur5r.net>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Keytable क्रम remote provided with Delock 61959
 */
अटल काष्ठा rc_map_table delock_61959[] = अणु
	अणु 0x866b16, KEY_POWER2 पूर्ण,	/* Power */
	अणु 0x866b0c, KEY_POWER पूर्ण,	/* Shut Down */

	अणु 0x866b00, KEY_NUMERIC_1पूर्ण,
	अणु 0x866b01, KEY_NUMERIC_2पूर्ण,
	अणु 0x866b02, KEY_NUMERIC_3पूर्ण,
	अणु 0x866b03, KEY_NUMERIC_4पूर्ण,
	अणु 0x866b04, KEY_NUMERIC_5पूर्ण,
	अणु 0x866b05, KEY_NUMERIC_6पूर्ण,
	अणु 0x866b06, KEY_NUMERIC_7पूर्ण,
	अणु 0x866b07, KEY_NUMERIC_8पूर्ण,
	अणु 0x866b08, KEY_NUMERIC_9पूर्ण,
	अणु 0x866b14, KEY_NUMERIC_0पूर्ण,

	अणु 0x866b0a, KEY_ZOOMपूर्ण,		/* Full Screen */
	अणु 0x866b10, KEY_CAMERAपूर्ण,	/* Photo */
	अणु 0x866b0e, KEY_CHANNELपूर्ण,	/* circular arrow / Recall */
	अणु 0x866b13, KEY_ESCपूर्ण,           /* Back */

	अणु 0x866b20, KEY_UPपूर्ण,
	अणु 0x866b21, KEY_DOWNपूर्ण,
	अणु 0x866b42, KEY_LEFTपूर्ण,
	अणु 0x866b43, KEY_RIGHTपूर्ण,
	अणु 0x866b0b, KEY_OKपूर्ण,

	अणु 0x866b11, KEY_CHANNELUPपूर्ण,
	अणु 0x866b1b, KEY_CHANNELDOWNपूर्ण,

	अणु 0x866b12, KEY_VOLUMEUPपूर्ण,
	अणु 0x866b48, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x866b44, KEY_MUTEपूर्ण,

	अणु 0x866b1a, KEY_RECORDपूर्ण,
	अणु 0x866b41, KEY_PLAYपूर्ण,
	अणु 0x866b40, KEY_STOPपूर्ण,
	अणु 0x866b19, KEY_PAUSEपूर्ण,
	अणु 0x866b1c, KEY_FASTFORWARDपूर्ण,	/* >> / FWD */
	अणु 0x866b1e, KEY_REWINDपूर्ण,	/* << / REW */

पूर्ण;

अटल काष्ठा rc_map_list delock_61959_map = अणु
	.map = अणु
		.scan     = delock_61959,
		.size     = ARRAY_SIZE(delock_61959),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_DELOCK_61959,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_delock_61959(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&delock_61959_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_delock_61959(व्योम)
अणु
	rc_map_unरेजिस्टर(&delock_61959_map);
पूर्ण

module_init(init_rc_map_delock_61959)
module_निकास(निकास_rc_map_delock_61959)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jakob Haufe <sur5r@sur5r.net>");
MODULE_DESCRIPTION("Delock 61959 remote keytable");
