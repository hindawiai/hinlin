<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2013-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_coex_h__
#घोषणा __iwl_fw_api_coex_h__

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#घोषणा BITS(nb) (BIT(nb) - 1)

क्रमागत iwl_bt_coex_lut_type अणु
	BT_COEX_TIGHT_LUT = 0,
	BT_COEX_LOOSE_LUT,
	BT_COEX_TX_DIS_LUT,

	BT_COEX_MAX_LUT,
	BT_COEX_INVALID_LUT = 0xff,
पूर्ण; /* BT_COEX_DECISION_LUT_INDEX_API_E_VER_1 */

#घोषणा BT_REDUCED_TX_POWER_BIT BIT(7)

क्रमागत iwl_bt_coex_mode अणु
	BT_COEX_DISABLE			= 0x0,
	BT_COEX_NW			= 0x1,
	BT_COEX_BT			= 0x2,
	BT_COEX_WIFI			= 0x3,
पूर्ण; /* BT_COEX_MODES_E */

क्रमागत iwl_bt_coex_enabled_modules अणु
	BT_COEX_MPLUT_ENABLED		= BIT(0),
	BT_COEX_MPLUT_BOOST_ENABLED	= BIT(1),
	BT_COEX_SYNC2SCO_ENABLED	= BIT(2),
	BT_COEX_CORUN_ENABLED		= BIT(3),
	BT_COEX_HIGH_BAND_RET		= BIT(4),
पूर्ण; /* BT_COEX_MODULES_ENABLE_E_VER_1 */

/**
 * काष्ठा iwl_bt_coex_cmd - bt coex configuration command
 * @mode: &क्रमागत iwl_bt_coex_mode
 * @enabled_modules: &क्रमागत iwl_bt_coex_enabled_modules
 *
 * The काष्ठाure is used क्रम the BT_COEX command.
 */
काष्ठा iwl_bt_coex_cmd अणु
	__le32 mode;
	__le32 enabled_modules;
पूर्ण __packed; /* BT_COEX_CMD_API_S_VER_6 */

/**
 * काष्ठा iwl_bt_coex_reduced_txp_update_cmd
 * @reduced_txp: bit BT_REDUCED_TX_POWER_BIT to enable / disable, rest of the
 *	bits are the sta_id (value)
 */
काष्ठा iwl_bt_coex_reduced_txp_update_cmd अणु
	__le32 reduced_txp;
पूर्ण __packed; /* BT_COEX_UPDATE_REDUCED_TX_POWER_API_S_VER_1 */

/**
 * काष्ठा iwl_bt_coex_ci_cmd - bt coex channel inhibition command
 * @bt_primary_ci: primary channel inhibition biपंचांगap
 * @primary_ch_phy_id: primary channel PHY ID
 * @bt_secondary_ci: secondary channel inhibition biपंचांगap
 * @secondary_ch_phy_id: secondary channel PHY ID
 *
 * Used क्रम BT_COEX_CI command
 */
काष्ठा iwl_bt_coex_ci_cmd अणु
	__le64 bt_primary_ci;
	__le32 primary_ch_phy_id;

	__le64 bt_secondary_ci;
	__le32 secondary_ch_phy_id;
पूर्ण __packed; /* BT_CI_MSG_API_S_VER_2 */

#घोषणा BT_MBOX(n_dw, _msg, _pos, _nbits)	\
	BT_MBOX##n_dw##_##_msg##_POS = (_pos),	\
	BT_MBOX##n_dw##_##_msg = BITS(_nbits) << BT_MBOX##n_dw##_##_msg##_POS

क्रमागत iwl_bt_mxbox_dw0 अणु
	BT_MBOX(0, LE_SLAVE_LAT, 0, 3),
	BT_MBOX(0, LE_PROF1, 3, 1),
	BT_MBOX(0, LE_PROF2, 4, 1),
	BT_MBOX(0, LE_PROF_OTHER, 5, 1),
	BT_MBOX(0, CHL_SEQ_N, 8, 4),
	BT_MBOX(0, INBAND_S, 13, 1),
	BT_MBOX(0, LE_MIN_RSSI, 16, 4),
	BT_MBOX(0, LE_SCAN, 20, 1),
	BT_MBOX(0, LE_ADV, 21, 1),
	BT_MBOX(0, LE_MAX_TX_POWER, 24, 4),
	BT_MBOX(0, OPEN_CON_1, 28, 2),
पूर्ण;

क्रमागत iwl_bt_mxbox_dw1 अणु
	BT_MBOX(1, BR_MAX_TX_POWER, 0, 4),
	BT_MBOX(1, IP_SR, 4, 1),
	BT_MBOX(1, LE_MSTR, 5, 1),
	BT_MBOX(1, AGGR_TRFC_LD, 8, 6),
	BT_MBOX(1, MSG_TYPE, 16, 3),
	BT_MBOX(1, SSN, 19, 2),
पूर्ण;

क्रमागत iwl_bt_mxbox_dw2 अणु
	BT_MBOX(2, SNIFF_ACT, 0, 3),
	BT_MBOX(2, PAG, 3, 1),
	BT_MBOX(2, INQUIRY, 4, 1),
	BT_MBOX(2, CONN, 5, 1),
	BT_MBOX(2, SNIFF_INTERVAL, 8, 5),
	BT_MBOX(2, DISC, 13, 1),
	BT_MBOX(2, SCO_TX_ACT, 16, 2),
	BT_MBOX(2, SCO_RX_ACT, 18, 2),
	BT_MBOX(2, ESCO_RE_TX, 20, 2),
	BT_MBOX(2, SCO_DURATION, 24, 6),
पूर्ण;

क्रमागत iwl_bt_mxbox_dw3 अणु
	BT_MBOX(3, SCO_STATE, 0, 1),
	BT_MBOX(3, SNIFF_STATE, 1, 1),
	BT_MBOX(3, A2DP_STATE, 2, 1),
	BT_MBOX(3, ACL_STATE, 3, 1),
	BT_MBOX(3, MSTR_STATE, 4, 1),
	BT_MBOX(3, OBX_STATE, 5, 1),
	BT_MBOX(3, A2DP_SRC, 6, 1),
	BT_MBOX(3, OPEN_CON_2, 8, 2),
	BT_MBOX(3, TRAFFIC_LOAD, 10, 2),
	BT_MBOX(3, CHL_SEQN_LSB, 12, 1),
	BT_MBOX(3, INBAND_P, 13, 1),
	BT_MBOX(3, MSG_TYPE_2, 16, 3),
	BT_MBOX(3, SSN_2, 19, 2),
	BT_MBOX(3, UPDATE_REQUEST, 21, 1),
पूर्ण;

#घोषणा BT_MBOX_MSG(_notअगर, _num, _field)				     \
	((le32_to_cpu((_notअगर)->mbox_msg[(_num)]) & BT_MBOX##_num##_##_field)\
	>> BT_MBOX##_num##_##_field##_POS)

#घोषणा BT_MBOX_PRINT(_num, _field, _end)				    \
			pos += scnम_लिखो(buf + pos, bufsz - pos,	    \
					 "\t%s: %d%s",			    \
					 #_field,			    \
					 BT_MBOX_MSG(notअगर, _num, _field),  \
					 true ? "\n" : ", ");
क्रमागत iwl_bt_activity_grading अणु
	BT_OFF			= 0,
	BT_ON_NO_CONNECTION	= 1,
	BT_LOW_TRAFFIC		= 2,
	BT_HIGH_TRAFFIC		= 3,
	BT_VERY_HIGH_TRAFFIC	= 4,

	BT_MAX_AG,
पूर्ण; /* BT_COEX_BT_ACTIVITY_GRADING_API_E_VER_1 */

क्रमागत iwl_bt_ci_compliance अणु
	BT_CI_COMPLIANCE_NONE		= 0,
	BT_CI_COMPLIANCE_PRIMARY	= 1,
	BT_CI_COMPLIANCE_SECONDARY	= 2,
	BT_CI_COMPLIANCE_BOTH		= 3,
पूर्ण; /* BT_COEX_CI_COMPLIENCE_E_VER_1 */

/**
 * काष्ठा iwl_bt_coex_profile_notअगर - notअगरication about BT coex
 * @mbox_msg: message from BT to WiFi
 * @msg_idx: the index of the message
 * @bt_ci_compliance: क्रमागत %iwl_bt_ci_compliance
 * @primary_ch_lut: LUT used क्रम primary channel &क्रमागत iwl_bt_coex_lut_type
 * @secondary_ch_lut: LUT used क्रम secondary channel &क्रमागत iwl_bt_coex_lut_type
 * @bt_activity_grading: the activity of BT &क्रमागत iwl_bt_activity_grading
 * @ttc_status: is TTC enabled - one bit per PHY
 * @rrc_status: is RRC enabled - one bit per PHY
 * @reserved: reserved
 */
काष्ठा iwl_bt_coex_profile_notअगर अणु
	__le32 mbox_msg[4];
	__le32 msg_idx;
	__le32 bt_ci_compliance;

	__le32 primary_ch_lut;
	__le32 secondary_ch_lut;
	__le32 bt_activity_grading;
	u8 ttc_status;
	u8 rrc_status;
	__le16 reserved;
पूर्ण __packed; /* BT_COEX_PROखाता_NTFY_API_S_VER_4 */

#पूर्ण_अगर /* __iwl_fw_api_coex_h__ */
