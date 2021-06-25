<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* keytable क्रम Twinhan DTV CAB CI Remote Controller
 *
 * Copyright (c) 2010 by Igor M. Liplianin <liplianin@me.by>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table twinhan_dtv_cab_ci[] = अणु
	अणु 0x29, KEY_POWERपूर्ण,
	अणु 0x28, KEY_FAVORITESपूर्ण,
	अणु 0x30, KEY_TEXTपूर्ण,
	अणु 0x17, KEY_INFOपूर्ण,              /* Preview */
	अणु 0x23, KEY_EPGपूर्ण,
	अणु 0x3b, KEY_F22पूर्ण,               /* Record List */

	अणु 0x3c, KEY_NUMERIC_1पूर्ण,
	अणु 0x3e, KEY_NUMERIC_2पूर्ण,
	अणु 0x39, KEY_NUMERIC_3पूर्ण,
	अणु 0x36, KEY_NUMERIC_4पूर्ण,
	अणु 0x22, KEY_NUMERIC_5पूर्ण,
	अणु 0x20, KEY_NUMERIC_6पूर्ण,
	अणु 0x32, KEY_NUMERIC_7पूर्ण,
	अणु 0x26, KEY_NUMERIC_8पूर्ण,
	अणु 0x24, KEY_NUMERIC_9पूर्ण,
	अणु 0x2a, KEY_NUMERIC_0पूर्ण,

	अणु 0x33, KEY_CANCELपूर्ण,
	अणु 0x2c, KEY_BACKपूर्ण,
	अणु 0x15, KEY_CLEARपूर्ण,
	अणु 0x3f, KEY_TABपूर्ण,
	अणु 0x10, KEY_ENTERपूर्ण,
	अणु 0x14, KEY_UPपूर्ण,
	अणु 0x0d, KEY_RIGHTपूर्ण,
	अणु 0x0e, KEY_DOWNपूर्ण,
	अणु 0x11, KEY_LEFTपूर्ण,

	अणु 0x21, KEY_VOLUMEUPपूर्ण,
	अणु 0x35, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x3d, KEY_CHANNELDOWNपूर्ण,
	अणु 0x3a, KEY_CHANNELUPपूर्ण,
	अणु 0x2e, KEY_RECORDपूर्ण,
	अणु 0x2b, KEY_PLAYपूर्ण,
	अणु 0x13, KEY_PAUSEपूर्ण,
	अणु 0x25, KEY_STOPपूर्ण,

	अणु 0x1f, KEY_REWINDपूर्ण,
	अणु 0x2d, KEY_FASTFORWARDपूर्ण,
	अणु 0x1e, KEY_PREVIOUSपूर्ण,          /* Replay |< */
	अणु 0x1d, KEY_NEXTपूर्ण,              /* Skip   >| */

	अणु 0x0b, KEY_CAMERAपूर्ण,            /* Capture */
	अणु 0x0f, KEY_LANGUAGEपूर्ण,          /* SAP */
	अणु 0x18, KEY_MODEपूर्ण,              /* PIP */
	अणु 0x12, KEY_ZOOMपूर्ण,              /* Full screen */
	अणु 0x1c, KEY_SUBTITLEपूर्ण,
	अणु 0x2f, KEY_MUTEपूर्ण,
	अणु 0x16, KEY_F20पूर्ण,               /* L/R */
	अणु 0x38, KEY_F21पूर्ण,               /* Hibernate */

	अणु 0x37, KEY_SWITCHVIDEOMODEपूर्ण,   /* A/V */
	अणु 0x31, KEY_AGAINपूर्ण,             /* Recall */
	अणु 0x1a, KEY_KPPLUSपूर्ण,            /* Zoom+ */
	अणु 0x19, KEY_KPMINUSपूर्ण,           /* Zoom- */
	अणु 0x27, KEY_REDपूर्ण,
	अणु 0x0C, KEY_GREENपूर्ण,
	अणु 0x01, KEY_YELLOWपूर्ण,
	अणु 0x00, KEY_BLUEपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list twinhan_dtv_cab_ci_map = अणु
	.map = अणु
		.scan     = twinhan_dtv_cab_ci,
		.size     = ARRAY_SIZE(twinhan_dtv_cab_ci),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_TWINHAN_DTV_CAB_CI,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_twinhan_dtv_cab_ci(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&twinhan_dtv_cab_ci_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_twinhan_dtv_cab_ci(व्योम)
अणु
	rc_map_unरेजिस्टर(&twinhan_dtv_cab_ci_map);
पूर्ण

module_init(init_rc_map_twinhan_dtv_cab_ci);
module_निकास(निकास_rc_map_twinhan_dtv_cab_ci);

MODULE_LICENSE("GPL");
