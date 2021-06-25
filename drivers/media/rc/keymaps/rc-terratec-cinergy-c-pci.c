<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* keytable क्रम Terratec Cinergy C PCI Remote Controller
 *
 * Copyright (c) 2010 by Igor M. Liplianin <liplianin@me.by>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table terratec_cinergy_c_pci[] = अणु
	अणु 0x3e, KEY_POWERपूर्ण,
	अणु 0x3d, KEY_NUMERIC_1पूर्ण,
	अणु 0x3c, KEY_NUMERIC_2पूर्ण,
	अणु 0x3b, KEY_NUMERIC_3पूर्ण,
	अणु 0x3a, KEY_NUMERIC_4पूर्ण,
	अणु 0x39, KEY_NUMERIC_5पूर्ण,
	अणु 0x38, KEY_NUMERIC_6पूर्ण,
	अणु 0x37, KEY_NUMERIC_7पूर्ण,
	अणु 0x36, KEY_NUMERIC_8पूर्ण,
	अणु 0x35, KEY_NUMERIC_9पूर्ण,
	अणु 0x34, KEY_VIDEO_NEXTपूर्ण, /* AV */
	अणु 0x33, KEY_NUMERIC_0पूर्ण,
	अणु 0x32, KEY_REFRESHपूर्ण,
	अणु 0x30, KEY_EPGपूर्ण,
	अणु 0x2f, KEY_UPपूर्ण,
	अणु 0x2e, KEY_LEFTपूर्ण,
	अणु 0x2d, KEY_OKपूर्ण,
	अणु 0x2c, KEY_RIGHTपूर्ण,
	अणु 0x2b, KEY_DOWNपूर्ण,
	अणु 0x29, KEY_INFOपूर्ण,
	अणु 0x28, KEY_REDपूर्ण,
	अणु 0x27, KEY_GREENपूर्ण,
	अणु 0x26, KEY_YELLOWपूर्ण,
	अणु 0x25, KEY_BLUEपूर्ण,
	अणु 0x24, KEY_CHANNELUPपूर्ण,
	अणु 0x23, KEY_VOLUMEUPपूर्ण,
	अणु 0x22, KEY_MUTEपूर्ण,
	अणु 0x21, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x20, KEY_CHANNELDOWNपूर्ण,
	अणु 0x1f, KEY_PAUSEपूर्ण,
	अणु 0x1e, KEY_HOMEपूर्ण,
	अणु 0x1d, KEY_MENUपूर्ण, /* DVD Menu */
	अणु 0x1c, KEY_SUBTITLEपूर्ण,
	अणु 0x1b, KEY_TEXTपूर्ण, /* Teletext */
	अणु 0x1a, KEY_DELETEपूर्ण,
	अणु 0x19, KEY_TVपूर्ण,
	अणु 0x18, KEY_DVDपूर्ण,
	अणु 0x17, KEY_STOPपूर्ण,
	अणु 0x16, KEY_VIDEOपूर्ण,
	अणु 0x15, KEY_AUDIOपूर्ण, /* Music */
	अणु 0x14, KEY_SCREENपूर्ण, /* Pic */
	अणु 0x13, KEY_PLAYपूर्ण,
	अणु 0x12, KEY_BACKपूर्ण,
	अणु 0x11, KEY_REWINDपूर्ण,
	अणु 0x10, KEY_FASTFORWARDपूर्ण,
	अणु 0x0b, KEY_PREVIOUSपूर्ण,
	अणु 0x07, KEY_RECORDपूर्ण,
	अणु 0x03, KEY_NEXTपूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list terratec_cinergy_c_pci_map = अणु
	.map = अणु
		.scan     = terratec_cinergy_c_pci,
		.size     = ARRAY_SIZE(terratec_cinergy_c_pci),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_TERRATEC_CINERGY_C_PCI,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_terratec_cinergy_c_pci(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&terratec_cinergy_c_pci_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_terratec_cinergy_c_pci(व्योम)
अणु
	rc_map_unरेजिस्टर(&terratec_cinergy_c_pci_map);
पूर्ण

module_init(init_rc_map_terratec_cinergy_c_pci);
module_निकास(निकास_rc_map_terratec_cinergy_c_pci);

MODULE_LICENSE("GPL");
