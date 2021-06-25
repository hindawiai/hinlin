<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// adstech-dvb-t-pci.h - Keytable क्रम adstech_dvb_t_pci Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* ADS Tech Instant TV DVB-T PCI Remote */

अटल काष्ठा rc_map_table adstech_dvb_t_pci[] = अणु
	/* Keys 0 to 9 */
	अणु 0x4d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x57, KEY_NUMERIC_1 पूर्ण,
	अणु 0x4f, KEY_NUMERIC_2 पूर्ण,
	अणु 0x53, KEY_NUMERIC_3 पूर्ण,
	अणु 0x56, KEY_NUMERIC_4 पूर्ण,
	अणु 0x4e, KEY_NUMERIC_5 पूर्ण,
	अणु 0x5e, KEY_NUMERIC_6 पूर्ण,
	अणु 0x54, KEY_NUMERIC_7 पूर्ण,
	अणु 0x4c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x5c, KEY_NUMERIC_9 पूर्ण,

	अणु 0x5b, KEY_POWER पूर्ण,
	अणु 0x5f, KEY_MUTE पूर्ण,
	अणु 0x55, KEY_GOTO पूर्ण,
	अणु 0x5d, KEY_SEARCH पूर्ण,
	अणु 0x17, KEY_EPG पूर्ण,		/* Guide */
	अणु 0x1f, KEY_MENU पूर्ण,
	अणु 0x0f, KEY_UP पूर्ण,
	अणु 0x46, KEY_DOWN पूर्ण,
	अणु 0x16, KEY_LEFT पूर्ण,
	अणु 0x1e, KEY_RIGHT पूर्ण,
	अणु 0x0e, KEY_SELECT पूर्ण,		/* Enter */
	अणु 0x5a, KEY_INFO पूर्ण,
	अणु 0x52, KEY_EXIT पूर्ण,
	अणु 0x59, KEY_PREVIOUS पूर्ण,
	अणु 0x51, KEY_NEXT पूर्ण,
	अणु 0x58, KEY_REWIND पूर्ण,
	अणु 0x50, KEY_FORWARD पूर्ण,
	अणु 0x44, KEY_PLAYPAUSE पूर्ण,
	अणु 0x07, KEY_STOP पूर्ण,
	अणु 0x1b, KEY_RECORD पूर्ण,
	अणु 0x13, KEY_TUNER पूर्ण,		/* Live */
	अणु 0x0a, KEY_A पूर्ण,
	अणु 0x12, KEY_B पूर्ण,
	अणु 0x03, KEY_RED पूर्ण,		/* 1 */
	अणु 0x01, KEY_GREEN पूर्ण,		/* 2 */
	अणु 0x00, KEY_YELLOW पूर्ण,		/* 3 */
	अणु 0x06, KEY_DVD पूर्ण,
	अणु 0x48, KEY_AUX पूर्ण,		/* Photo */
	अणु 0x40, KEY_VIDEO पूर्ण,
	अणु 0x19, KEY_AUDIO पूर्ण,		/* Music */
	अणु 0x0b, KEY_CHANNELUP पूर्ण,
	अणु 0x08, KEY_CHANNELDOWN पूर्ण,
	अणु 0x15, KEY_VOLUMEUP पूर्ण,
	अणु 0x1c, KEY_VOLUMEDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list adstech_dvb_t_pci_map = अणु
	.map = अणु
		.scan     = adstech_dvb_t_pci,
		.size     = ARRAY_SIZE(adstech_dvb_t_pci),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_ADSTECH_DVB_T_PCI,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_adstech_dvb_t_pci(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&adstech_dvb_t_pci_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_adstech_dvb_t_pci(व्योम)
अणु
	rc_map_unरेजिस्टर(&adstech_dvb_t_pci_map);
पूर्ण

module_init(init_rc_map_adstech_dvb_t_pci)
module_निकास(निकास_rc_map_adstech_dvb_t_pci)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
