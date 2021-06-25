<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MSI DIGIVOX mini III remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* MSI DIGIVOX mini III */
/* Uses NEC extended 0x61d6. */
/* This remote seems to be same as rc-kworld-315u.c. Anyhow, add new remote
   since rc-kworld-315u.c lacks NEC extended address byte. */
अटल काष्ठा rc_map_table msi_digivox_iii[] = अणु
	अणु 0x61d601, KEY_VIDEO पूर्ण,           /* Source */
	अणु 0x61d602, KEY_NUMERIC_3 पूर्ण,
	अणु 0x61d603, KEY_POWER पूर्ण,           /* ShutDown */
	अणु 0x61d604, KEY_NUMERIC_1 पूर्ण,
	अणु 0x61d605, KEY_NUMERIC_5 पूर्ण,
	अणु 0x61d606, KEY_NUMERIC_6 पूर्ण,
	अणु 0x61d607, KEY_CHANNELDOWN पूर्ण,     /* CH- */
	अणु 0x61d608, KEY_NUMERIC_2 पूर्ण,
	अणु 0x61d609, KEY_CHANNELUP पूर्ण,       /* CH+ */
	अणु 0x61d60a, KEY_NUMERIC_9 पूर्ण,
	अणु 0x61d60b, KEY_ZOOM पूर्ण,            /* Zoom */
	अणु 0x61d60c, KEY_NUMERIC_7 पूर्ण,
	अणु 0x61d60d, KEY_NUMERIC_8 पूर्ण,
	अणु 0x61d60e, KEY_VOLUMEUP पूर्ण,        /* Vol+ */
	अणु 0x61d60f, KEY_NUMERIC_4 पूर्ण,
	अणु 0x61d610, KEY_ESC पूर्ण,             /* [back up arrow] */
	अणु 0x61d611, KEY_NUMERIC_0 पूर्ण,
	अणु 0x61d612, KEY_OK पूर्ण,              /* [enter arrow] */
	अणु 0x61d613, KEY_VOLUMEDOWN पूर्ण,      /* Vol- */
	अणु 0x61d614, KEY_RECORD पूर्ण,          /* Rec */
	अणु 0x61d615, KEY_STOP पूर्ण,            /* Stop */
	अणु 0x61d616, KEY_PLAY पूर्ण,            /* Play */
	अणु 0x61d617, KEY_MUTE पूर्ण,            /* Mute */
	अणु 0x61d618, KEY_UP पूर्ण,
	अणु 0x61d619, KEY_DOWN पूर्ण,
	अणु 0x61d61a, KEY_LEFT पूर्ण,
	अणु 0x61d61b, KEY_RIGHT पूर्ण,
	अणु 0x61d61c, KEY_RED पूर्ण,
	अणु 0x61d61d, KEY_GREEN पूर्ण,
	अणु 0x61d61e, KEY_YELLOW पूर्ण,
	अणु 0x61d61f, KEY_BLUE पूर्ण,
	अणु 0x61d643, KEY_POWER2 पूर्ण,          /* [red घातer button] */
पूर्ण;

अटल काष्ठा rc_map_list msi_digivox_iii_map = अणु
	.map = अणु
		.scan     = msi_digivox_iii,
		.size     = ARRAY_SIZE(msi_digivox_iii),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_MSI_DIGIVOX_III,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_msi_digivox_iii(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&msi_digivox_iii_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_msi_digivox_iii(व्योम)
अणु
	rc_map_unरेजिस्टर(&msi_digivox_iii_map);
पूर्ण

module_init(init_rc_map_msi_digivox_iii)
module_निकास(निकास_rc_map_msi_digivox_iii)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
