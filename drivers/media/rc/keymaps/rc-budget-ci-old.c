<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// budget-ci-old.h - Keytable क्रम budget_ci_old Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * From पढ़ोing the following remotes:
 * Zenith Universal 7 / TV Mode 807 / VCR Mode 837
 * Hauppauge (from NOVA-CI-s box product)
 * This is a "middle of the road" approach, dअगरferences are noted
 */

अटल काष्ठा rc_map_table budget_ci_old[] = अणु
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0a, KEY_ENTER पूर्ण,
	अणु 0x0b, KEY_RED पूर्ण,
	अणु 0x0c, KEY_POWER पूर्ण,		/* RADIO on Hauppauge */
	अणु 0x0d, KEY_MUTE पूर्ण,
	अणु 0x0f, KEY_A पूर्ण,		/* TV on Hauppauge */
	अणु 0x10, KEY_VOLUMEUP पूर्ण,
	अणु 0x11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x14, KEY_B पूर्ण,
	अणु 0x1c, KEY_UP पूर्ण,
	अणु 0x1d, KEY_DOWN पूर्ण,
	अणु 0x1e, KEY_OPTION पूर्ण,		/* RESERVED on Hauppauge */
	अणु 0x1f, KEY_BREAK पूर्ण,
	अणु 0x20, KEY_CHANNELUP पूर्ण,
	अणु 0x21, KEY_CHANNELDOWN पूर्ण,
	अणु 0x22, KEY_PREVIOUS पूर्ण,		/* Prev Ch on Zenith, SOURCE on Hauppauge */
	अणु 0x24, KEY_RESTART पूर्ण,
	अणु 0x25, KEY_OK पूर्ण,
	अणु 0x26, KEY_CYCLEWINDOWS पूर्ण,	/* MINIMIZE on Hauppauge */
	अणु 0x28, KEY_ENTER पूर्ण,		/* VCR mode on Zenith */
	अणु 0x29, KEY_PAUSE पूर्ण,
	अणु 0x2b, KEY_RIGHT पूर्ण,
	अणु 0x2c, KEY_LEFT पूर्ण,
	अणु 0x2e, KEY_MENU पूर्ण,		/* FULL SCREEN on Hauppauge */
	अणु 0x30, KEY_SLOW पूर्ण,
	अणु 0x31, KEY_PREVIOUS पूर्ण,		/* VCR mode on Zenith */
	अणु 0x32, KEY_REWIND पूर्ण,
	अणु 0x34, KEY_FASTFORWARD पूर्ण,
	अणु 0x35, KEY_PLAY पूर्ण,
	अणु 0x36, KEY_STOP पूर्ण,
	अणु 0x37, KEY_RECORD पूर्ण,
	अणु 0x38, KEY_TUNER पूर्ण,		/* TV/VCR on Zenith */
	अणु 0x3a, KEY_C पूर्ण,
	अणु 0x3c, KEY_EXIT पूर्ण,
	अणु 0x3d, KEY_POWER2 पूर्ण,
	अणु 0x3e, KEY_TUNER पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list budget_ci_old_map = अणु
	.map = अणु
		.scan     = budget_ci_old,
		.size     = ARRAY_SIZE(budget_ci_old),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_BUDGET_CI_OLD,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_budget_ci_old(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&budget_ci_old_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_budget_ci_old(व्योम)
अणु
	rc_map_unरेजिस्टर(&budget_ci_old_map);
पूर्ण

module_init(init_rc_map_budget_ci_old)
module_निकास(निकास_rc_map_budget_ci_old)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
