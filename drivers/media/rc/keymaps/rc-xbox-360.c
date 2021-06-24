<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Keytable क्रम Xbox 360 Universal Media remote
// Copyright (c) 2021 Bastien Nocera <hadess@hadess.net>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Manual क्रम remote available at:
 * http://करोwnload.microsoft.com/करोwnload/b/c/e/bce76f3f-db51-4c98-b79d-b3d21e90ccc1/universalmediaremote_na_0609.pdf
 */
अटल काष्ठा rc_map_table xbox_360[] = अणु
	अणुKEY_EJECTCD, 0x800f7428पूर्ण,
	अणुKEY_HOMEPAGE, 0x800f7464पूर्ण,
	अणुKEY_POWER, 0x800f740cपूर्ण,
	अणुKEY_STOP, 0x800f7419पूर्ण,
	अणुKEY_PAUSE, 0x800f7418पूर्ण,
	अणुKEY_REWIND, 0x800f7415पूर्ण,
	अणुKEY_FASTFORWARD, 0x800f7414पूर्ण,
	अणुKEY_PREVIOUS, 0x800f741bपूर्ण,
	अणुKEY_NEXT, 0x800f741aपूर्ण,
	अणुKEY_PLAY, 0x800f7416पूर्ण,
	अणुKEY_PROPS, 0x800f744fपूर्ण, /* "Display" */
	अणुKEY_BACK, 0x800f7423पूर्ण,
	अणुKEY_MEDIA_TOP_MENU, 0x800f7424पूर्ण, /* "DVD Menu" */
	अणुKEY_ROOT_MENU, 0x800f7451पूर्ण, /* "Title" */
	अणुKEY_INFO, 0x800f740fपूर्ण,
	अणुKEY_UP, 0x800f741eपूर्ण,
	अणुKEY_LEFT, 0x800f7420पूर्ण,
	अणुKEY_RIGHT, 0x800f7421पूर्ण,
	अणुKEY_DOWN, 0x800f741fपूर्ण,
	अणुKEY_OK, 0x800f7422पूर्ण,
	अणुKEY_YELLOW, 0x800f7426पूर्ण,
	अणुKEY_BLUE, 0x800f7468पूर्ण,
	अणुKEY_GREEN, 0x800f7466पूर्ण,
	अणुKEY_RED, 0x800f7425पूर्ण,
	अणुKEY_VOLUMEUP, 0x800f7410पूर्ण,
	अणुKEY_VOLUMEDOWN, 0x800f7411पूर्ण,
	/* TV key करोesn't light the IR LED */
	अणुKEY_MUTE, 0x800f740eपूर्ण,
	अणुKEY_CHANNELUP, 0x800f746cपूर्ण,
	अणुKEY_CHANNELDOWN, 0x800f746dपूर्ण,
	अणुKEY_LEFTMETA, 0x800f740dपूर्ण,
	अणुKEY_ENTER, 0x800f740bपूर्ण,
	अणुKEY_RECORD, 0x800f7417पूर्ण,
	अणुKEY_CLEAR, 0x800f740aपूर्ण,
	अणुKEY_NUMERIC_1, 0x800f7401पूर्ण,
	अणुKEY_NUMERIC_2, 0x800f7402पूर्ण,
	अणुKEY_NUMERIC_3, 0x800f7403पूर्ण,
	अणुKEY_NUMERIC_4, 0x800f7404पूर्ण,
	अणुKEY_NUMERIC_5, 0x800f7405पूर्ण,
	अणुKEY_NUMERIC_6, 0x800f7406पूर्ण,
	अणुKEY_NUMERIC_7, 0x800f7407पूर्ण,
	अणुKEY_NUMERIC_8, 0x800f7408पूर्ण,
	अणुKEY_NUMERIC_9, 0x800f7409पूर्ण,
	अणुKEY_NUMERIC_0, 0x800f7400पूर्ण,
	अणुKEY_102ND, 0x800f741dपूर्ण, /* "100" */
	अणुKEY_CANCEL, 0x800f741cपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list xbox_360_map = अणु
	.map = अणु
		.scan     = xbox_360,
		.size     = ARRAY_SIZE(xbox_360),
		.rc_proto = RC_PROTO_RC6_MCE,
		.name     = RC_MAP_XBOX_360,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&xbox_360_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&xbox_360_map);
पूर्ण

module_init(init_rc_map)
module_निकास(निकास_rc_map)

MODULE_LICENSE("GPL");
