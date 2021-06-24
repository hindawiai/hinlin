<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-rc6-mce.c - Keytable क्रम Winकरोws Media Center RC-6 remotes क्रम use
 * with the Media Center Edition eHome Infrared Transceiver.
 *
 * Copyright (c) 2010 by Jarod Wilson <jarod@redhat.com>
 *
 * See http://mediacenterguides.com/book/export/hपंचांगl/31 क्रम details on
 * key mappings.
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table rc6_mce[] = अणु

	अणु 0x800f0400, KEY_NUMERIC_0 पूर्ण,
	अणु 0x800f0401, KEY_NUMERIC_1 पूर्ण,
	अणु 0x800f0402, KEY_NUMERIC_2 पूर्ण,
	अणु 0x800f0403, KEY_NUMERIC_3 पूर्ण,
	अणु 0x800f0404, KEY_NUMERIC_4 पूर्ण,
	अणु 0x800f0405, KEY_NUMERIC_5 पूर्ण,
	अणु 0x800f0406, KEY_NUMERIC_6 पूर्ण,
	अणु 0x800f0407, KEY_NUMERIC_7 पूर्ण,
	अणु 0x800f0408, KEY_NUMERIC_8 पूर्ण,
	अणु 0x800f0409, KEY_NUMERIC_9 पूर्ण,

	अणु 0x800f040a, KEY_DELETE पूर्ण,
	अणु 0x800f040b, KEY_ENTER पूर्ण,
	अणु 0x800f040c, KEY_SLEEP पूर्ण,		/* Formerly PC Power */
	अणु 0x800f040d, KEY_MEDIA पूर्ण,		/* Winकरोws MCE button */
	अणु 0x800f040e, KEY_MUTE पूर्ण,
	अणु 0x800f040f, KEY_INFO पूर्ण,

	अणु 0x800f0410, KEY_VOLUMEUP पूर्ण,
	अणु 0x800f0411, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x800f0412, KEY_CHANNELUP पूर्ण,
	अणु 0x800f0413, KEY_CHANNELDOWN पूर्ण,

	अणु 0x800f0414, KEY_FASTFORWARD पूर्ण,
	अणु 0x800f0415, KEY_REWIND पूर्ण,
	अणु 0x800f0416, KEY_PLAY पूर्ण,
	अणु 0x800f0417, KEY_RECORD पूर्ण,
	अणु 0x800f0418, KEY_PAUSE पूर्ण,
	अणु 0x800f0419, KEY_STOP पूर्ण,
	अणु 0x800f041a, KEY_NEXT पूर्ण,
	अणु 0x800f041b, KEY_PREVIOUS पूर्ण,
	अणु 0x800f041c, KEY_NUMERIC_POUND पूर्ण,
	अणु 0x800f041d, KEY_NUMERIC_STAR पूर्ण,

	अणु 0x800f041e, KEY_UP पूर्ण,
	अणु 0x800f041f, KEY_DOWN पूर्ण,
	अणु 0x800f0420, KEY_LEFT पूर्ण,
	अणु 0x800f0421, KEY_RIGHT पूर्ण,

	अणु 0x800f0422, KEY_OK पूर्ण,
	अणु 0x800f0423, KEY_EXIT पूर्ण,
	अणु 0x800f0424, KEY_DVD पूर्ण,
	अणु 0x800f0425, KEY_TUNER पूर्ण,		/* LiveTV */
	अणु 0x800f0426, KEY_EPG पूर्ण,		/* Guide */
	अणु 0x800f0427, KEY_ZOOM पूर्ण,		/* Aspect */

	अणु 0x800f0432, KEY_MODE पूर्ण,		/* Visualization */
	अणु 0x800f0433, KEY_PRESENTATION पूर्ण,	/* Slide Show */
	अणु 0x800f0434, KEY_EJECTCD पूर्ण,
	अणु 0x800f043a, KEY_BRIGHTNESSUP पूर्ण,

	अणु 0x800f0446, KEY_TV पूर्ण,
	अणु 0x800f0447, KEY_AUDIO पूर्ण,		/* My Music */
	अणु 0x800f0448, KEY_PVR पूर्ण,		/* RecordedTV */
	अणु 0x800f0449, KEY_CAMERA पूर्ण,
	अणु 0x800f044a, KEY_VIDEO पूर्ण,
	अणु 0x800f044c, KEY_LANGUAGE पूर्ण,
	अणु 0x800f044d, KEY_TITLE पूर्ण,
	अणु 0x800f044e, KEY_PRINT पूर्ण,	/* Prपूर्णांक - HP OEM version of remote */

	अणु 0x800f0450, KEY_RADIO पूर्ण,

	अणु 0x800f045a, KEY_SUBTITLE पूर्ण,		/* Caption/Teletext */
	अणु 0x800f045b, KEY_RED पूर्ण,
	अणु 0x800f045c, KEY_GREEN पूर्ण,
	अणु 0x800f045d, KEY_YELLOW पूर्ण,
	अणु 0x800f045e, KEY_BLUE पूर्ण,

	अणु 0x800f0465, KEY_POWER2 पूर्ण,	/* TV Power */
	अणु 0x800f0469, KEY_MESSENGER पूर्ण,
	अणु 0x800f046e, KEY_PLAYPAUSE पूर्ण,
	अणु 0x800f046f, KEY_PLAYER पूर्ण,	/* Start media application (NEW) */

	अणु 0x800f0480, KEY_BRIGHTNESSDOWN पूर्ण,
	अणु 0x800f0481, KEY_PLAYPAUSE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list rc6_mce_map = अणु
	.map = अणु
		.scan     = rc6_mce,
		.size     = ARRAY_SIZE(rc6_mce),
		.rc_proto = RC_PROTO_RC6_MCE,
		.name     = RC_MAP_RC6_MCE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_rc6_mce(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&rc6_mce_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_rc6_mce(व्योम)
अणु
	rc_map_unरेजिस्टर(&rc6_mce_map);
पूर्ण

module_init(init_rc_map_rc6_mce)
module_निकास(निकास_rc_map_rc6_mce)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
