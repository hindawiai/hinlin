<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DigitalNow TinyTwin remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table digitalnow_tinytwin[] = अणु
	अणु 0x0000, KEY_MUTE पूर्ण,            /* [symbol speaker] */
	अणु 0x0001, KEY_VOLUMEUP पूर्ण,
	अणु 0x0002, KEY_POWER2 पूर्ण,          /* TV [घातer button] */
	अणु 0x0003, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0004, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0005, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0006, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0007, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0008, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0009, KEY_NUMERIC_STAR पूर्ण,    /* [*] */
	अणु 0x000a, KEY_NUMERIC_0 पूर्ण,
	अणु 0x000b, KEY_NUMERIC_POUND पूर्ण,   /* [#] */
	अणु 0x000c, KEY_RIGHT पूर्ण,           /* [right arrow] */
	अणु 0x000d, KEY_HOMEPAGE पूर्ण,        /* [symbol home] Start */
	अणु 0x000e, KEY_RED पूर्ण,             /* [red] Videos */
	अणु 0x0010, KEY_POWER पूर्ण,           /* PC [घातer button] */
	अणु 0x0011, KEY_YELLOW पूर्ण,          /* [yellow] Pictures */
	अणु 0x0012, KEY_DOWN पूर्ण,            /* [करोwn arrow] */
	अणु 0x0013, KEY_GREEN पूर्ण,           /* [green] Music */
	अणु 0x0014, KEY_CYCLEWINDOWS पूर्ण,    /* BACK */
	अणु 0x0015, KEY_FAVORITES पूर्ण,       /* MORE */
	अणु 0x0016, KEY_UP पूर्ण,              /* [up arrow] */
	अणु 0x0017, KEY_LEFT पूर्ण,            /* [left arrow] */
	अणु 0x0018, KEY_OK पूर्ण,              /* OK */
	अणु 0x0019, KEY_BLUE पूर्ण,            /* [blue] MyTV */
	अणु 0x001a, KEY_REWIND पूर्ण,          /* REW [<<] */
	अणु 0x001b, KEY_PLAY पूर्ण,            /* PLAY */
	अणु 0x001c, KEY_NUMERIC_5 पूर्ण,
	अणु 0x001d, KEY_NUMERIC_9 पूर्ण,
	अणु 0x001e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x001f, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0040, KEY_STOP पूर्ण,            /* STOP */
	अणु 0x0042, KEY_PAUSE पूर्ण,           /* PAUSE */
	अणु 0x0043, KEY_SCREEN पूर्ण,          /* Aspect */
	अणु 0x0044, KEY_FORWARD पूर्ण,         /* FWD [>>] */
	अणु 0x0045, KEY_NEXT पूर्ण,            /* SKIP */
	अणु 0x0048, KEY_RECORD पूर्ण,          /* RECORD */
	अणु 0x0049, KEY_VIDEO पूर्ण,           /* RTV */
	अणु 0x004a, KEY_EPG पूर्ण,             /* Guide */
	अणु 0x004b, KEY_CHANNELUP पूर्ण,
	अणु 0x004c, KEY_HELP पूर्ण,            /* Help */
	अणु 0x004d, KEY_RADIO पूर्ण,           /* Radio */
	अणु 0x004f, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0050, KEY_DVD पूर्ण,             /* DVD */
	अणु 0x0051, KEY_AUDIO पूर्ण,           /* Audio */
	अणु 0x0052, KEY_TITLE पूर्ण,           /* Title */
	अणु 0x0053, KEY_NEW पूर्ण,             /* [symbol PIP?] */
	अणु 0x0057, KEY_MENU पूर्ण,            /* Mouse */
	अणु 0x005a, KEY_PREVIOUS पूर्ण,        /* REPLAY */
पूर्ण;

अटल काष्ठा rc_map_list digitalnow_tinytwin_map = अणु
	.map = अणु
		.scan     = digitalnow_tinytwin,
		.size     = ARRAY_SIZE(digitalnow_tinytwin),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_DIGITALNOW_TINYTWIN,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_digitalnow_tinytwin(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&digitalnow_tinytwin_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_digitalnow_tinytwin(व्योम)
अणु
	rc_map_unरेजिस्टर(&digitalnow_tinytwin_map);
पूर्ण

module_init(init_rc_map_digitalnow_tinytwin)
module_निकास(निकास_rc_map_digitalnow_tinytwin)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
