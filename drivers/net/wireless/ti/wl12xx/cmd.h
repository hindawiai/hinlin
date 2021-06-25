<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 1998-2009, 2011 Texas Instruments. All rights reserved.
 * Copyright (C) 2009 Nokia Corporation
 */

#अगर_अघोषित __WL12XX_CMD_H__
#घोषणा __WL12XX_CMD_H__

#समावेश "conf.h"

#घोषणा TEST_CMD_INI_खाता_RADIO_PARAM       0x19
#घोषणा TEST_CMD_INI_खाता_GENERAL_PARAM     0x1E

काष्ठा wl1271_general_parms_cmd अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा wl1271_cmd_test_header test;

	काष्ठा wl1271_ini_general_params general_params;

	u8 sr_debug_table[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 sr_sen_n_p;
	u8 sr_sen_n_p_gain;
	u8 sr_sen_nrn;
	u8 sr_sen_prn;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl128x_general_parms_cmd अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा wl1271_cmd_test_header test;

	काष्ठा wl128x_ini_general_params general_params;

	u8 sr_debug_table[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 sr_sen_n_p;
	u8 sr_sen_n_p_gain;
	u8 sr_sen_nrn;
	u8 sr_sen_prn;
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl1271_radio_parms_cmd अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा wl1271_cmd_test_header test;

	/* Static radio parameters */
	काष्ठा wl1271_ini_band_params_2 अटल_params_2;
	काष्ठा wl1271_ini_band_params_5 अटल_params_5;

	/* Dynamic radio parameters */
	काष्ठा wl1271_ini_fem_params_2 dyn_params_2;
	u8 padding2;
	काष्ठा wl1271_ini_fem_params_5 dyn_params_5;
	u8 padding3[2];
पूर्ण __packed;

काष्ठा wl128x_radio_parms_cmd अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा wl1271_cmd_test_header test;

	/* Static radio parameters */
	काष्ठा wl128x_ini_band_params_2 अटल_params_2;
	काष्ठा wl128x_ini_band_params_5 अटल_params_5;

	u8 fem_venकरोr_and_options;

	/* Dynamic radio parameters */
	काष्ठा wl128x_ini_fem_params_2 dyn_params_2;
	u8 padding2;
	काष्ठा wl128x_ini_fem_params_5 dyn_params_5;
पूर्ण __packed;

#घोषणा TEST_CMD_INI_खाता_RF_EXTENDED_PARAM 0x26

काष्ठा wl1271_ext_radio_parms_cmd अणु
	काष्ठा wl1271_cmd_header header;

	काष्ठा wl1271_cmd_test_header test;

	u8 tx_per_channel_घातer_compensation_2[CONF_TX_PWR_COMPENSATION_LEN_2];
	u8 tx_per_channel_घातer_compensation_5[CONF_TX_PWR_COMPENSATION_LEN_5];
	u8 padding[3];
पूर्ण __packed;

काष्ठा wl12xx_cmd_channel_चयन अणु
	काष्ठा wl1271_cmd_header header;

	u8 role_id;

	/* The new serving channel */
	u8 channel;
	/* Relative समय of the serving channel चयन in TBTT units */
	u8 चयन_समय;
	/* Stop the role TX, should expect it after radar detection */
	u8 stop_tx;
	/* The target channel tx status 1-stopped 0-खोलो*/
	u8 post_चयन_tx_disable;

	u8 padding[3];
पूर्ण __packed;

पूर्णांक wl1271_cmd_general_parms(काष्ठा wl1271 *wl);
पूर्णांक wl128x_cmd_general_parms(काष्ठा wl1271 *wl);
पूर्णांक wl1271_cmd_radio_parms(काष्ठा wl1271 *wl);
पूर्णांक wl128x_cmd_radio_parms(काष्ठा wl1271 *wl);
पूर्णांक wl1271_cmd_ext_radio_parms(काष्ठा wl1271 *wl);
पूर्णांक wl12xx_cmd_channel_चयन(काष्ठा wl1271 *wl,
			      काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा ieee80211_channel_चयन *ch_चयन);

#पूर्ण_अगर /* __WL12XX_CMD_H__ */
