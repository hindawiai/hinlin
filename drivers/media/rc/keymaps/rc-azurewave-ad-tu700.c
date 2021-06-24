<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TwinHan AzureWave AD-TU700(704J) remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table azurewave_ad_tu700[] = अणु
	अणु 0x0000, KEY_TAB पूर्ण,             /* Tab */
	अणु 0x0001, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0002, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0003, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0004, KEY_MENU पूर्ण,            /* Record List */
	अणु 0x0005, KEY_CHANNELUP पूर्ण,
	अणु 0x0006, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0007, KEY_SLEEP पूर्ण,           /* Hibernate */
	अणु 0x0008, KEY_VIDEO पूर्ण,           /* A/V */
	अणु 0x0009, KEY_NUMERIC_4 पूर्ण,
	अणु 0x000a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x000c, KEY_CANCEL पूर्ण,          /* Cancel */
	अणु 0x000d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x000e, KEY_AGAIN पूर्ण,           /* Recall */
	अणु 0x000f, KEY_TEXT पूर्ण,            /* Teletext */
	अणु 0x0010, KEY_MUTE पूर्ण,
	अणु 0x0011, KEY_RECORD पूर्ण,
	अणु 0x0012, KEY_FASTFORWARD पूर्ण,     /* FF >> */
	अणु 0x0013, KEY_BACK पूर्ण,            /* Back */
	अणु 0x0014, KEY_PLAY पूर्ण,
	अणु 0x0015, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0016, KEY_POWER2 पूर्ण,          /* [red घातer button] */
	अणु 0x0017, KEY_FAVORITES पूर्ण,       /* Favorite List */
	अणु 0x0018, KEY_RED पूर्ण,
	अणु 0x0019, KEY_NUMERIC_8 पूर्ण,
	अणु 0x001a, KEY_STOP पूर्ण,
	अणु 0x001b, KEY_NUMERIC_9 पूर्ण,
	अणु 0x001c, KEY_EPG पूर्ण,             /* Info/EPG */
	अणु 0x001d, KEY_NUMERIC_5 पूर्ण,
	अणु 0x001e, KEY_VOLUMEUP पूर्ण,
	अणु 0x001f, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0040, KEY_REWIND पूर्ण,          /* FR << */
	अणु 0x0041, KEY_PREVIOUS पूर्ण,        /* Replay */
	अणु 0x0042, KEY_NEXT पूर्ण,            /* Skip */
	अणु 0x0043, KEY_SUBTITLE पूर्ण,        /* Subtitle / CC */
	अणु 0x0045, KEY_KPPLUS पूर्ण,          /* Zoom+ */
	अणु 0x0046, KEY_KPMINUS पूर्ण,         /* Zoom- */
	अणु 0x0047, KEY_NEW पूर्ण,             /* PIP */
	अणु 0x0048, KEY_INFO पूर्ण,            /* Preview */
	अणु 0x0049, KEY_MODE पूर्ण,            /* L/R */
	अणु 0x004a, KEY_CLEAR पूर्ण,           /* Clear */
	अणु 0x004b, KEY_UP पूर्ण,              /* up arrow */
	अणु 0x004c, KEY_PAUSE पूर्ण,
	अणु 0x004d, KEY_ZOOM पूर्ण,            /* Full Screen */
	अणु 0x004e, KEY_LEFT पूर्ण,            /* left arrow */
	अणु 0x004f, KEY_OK पूर्ण,              /* Enter / ok */
	अणु 0x0050, KEY_LANGUAGE पूर्ण,        /* SAP */
	अणु 0x0051, KEY_DOWN पूर्ण,            /* करोwn arrow */
	अणु 0x0052, KEY_RIGHT पूर्ण,           /* right arrow */
	अणु 0x0053, KEY_GREEN पूर्ण,
	अणु 0x0054, KEY_CAMERA पूर्ण,          /* Capture */
	अणु 0x005e, KEY_YELLOW पूर्ण,
	अणु 0x005f, KEY_BLUE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list azurewave_ad_tu700_map = अणु
	.map = अणु
		.scan     = azurewave_ad_tu700,
		.size     = ARRAY_SIZE(azurewave_ad_tu700),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_AZUREWAVE_AD_TU700,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_azurewave_ad_tu700(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&azurewave_ad_tu700_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_azurewave_ad_tu700(व्योम)
अणु
	rc_map_unरेजिस्टर(&azurewave_ad_tu700_map);
पूर्ण

module_init(init_rc_map_azurewave_ad_tu700)
module_निकास(निकास_rc_map_azurewave_ad_tu700)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
