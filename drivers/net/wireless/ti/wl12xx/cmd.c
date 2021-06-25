<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl12xx
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#समावेश "../wlcore/cmd.h"
#समावेश "../wlcore/debug.h"

#समावेश "wl12xx.h"
#समावेश "cmd.h"

पूर्णांक wl1271_cmd_ext_radio_parms(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_ext_radio_parms_cmd *ext_radio_parms;
	काष्ठा wl12xx_priv *priv = wl->priv;
	काष्ठा wl12xx_conf_rf *rf = &priv->conf.rf;
	पूर्णांक ret;

	अगर (!wl->nvs)
		वापस -ENODEV;

	ext_radio_parms = kzalloc(माप(*ext_radio_parms), GFP_KERNEL);
	अगर (!ext_radio_parms)
		वापस -ENOMEM;

	ext_radio_parms->test.id = TEST_CMD_INI_खाता_RF_EXTENDED_PARAM;

	स_नकल(ext_radio_parms->tx_per_channel_घातer_compensation_2,
	       rf->tx_per_channel_घातer_compensation_2,
	       CONF_TX_PWR_COMPENSATION_LEN_2);
	स_नकल(ext_radio_parms->tx_per_channel_घातer_compensation_5,
	       rf->tx_per_channel_घातer_compensation_5,
	       CONF_TX_PWR_COMPENSATION_LEN_5);

	wl1271_dump(DEBUG_CMD, "TEST_CMD_INI_FILE_EXT_RADIO_PARAM: ",
		    ext_radio_parms, माप(*ext_radio_parms));

	ret = wl1271_cmd_test(wl, ext_radio_parms, माप(*ext_radio_parms), 0);
	अगर (ret < 0)
		wl1271_warning("TEST_CMD_INI_FILE_RF_EXTENDED_PARAM failed");

	kमुक्त(ext_radio_parms);
	वापस ret;
पूर्ण

पूर्णांक wl1271_cmd_general_parms(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_general_parms_cmd *gen_parms;
	काष्ठा wl1271_ini_general_params *gp =
		&((काष्ठा wl1271_nvs_file *)wl->nvs)->general_params;
	काष्ठा wl12xx_priv *priv = wl->priv;
	bool answer = false;
	पूर्णांक ret;

	अगर (!wl->nvs)
		वापस -ENODEV;

	अगर (gp->tx_bip_fem_manufacturer >= WL1271_INI_FEM_MODULE_COUNT) अणु
		wl1271_warning("FEM index from INI out of bounds");
		वापस -EINVAL;
	पूर्ण

	gen_parms = kzalloc(माप(*gen_parms), GFP_KERNEL);
	अगर (!gen_parms)
		वापस -ENOMEM;

	gen_parms->test.id = TEST_CMD_INI_खाता_GENERAL_PARAM;

	स_नकल(&gen_parms->general_params, gp, माप(*gp));

	/* If we started in PLT FEM_DETECT mode, क्रमce स्वतः detect */
	अगर (wl->plt_mode == PLT_FEM_DETECT)
		gen_parms->general_params.tx_bip_fem_स्वतः_detect = true;

	अगर (gen_parms->general_params.tx_bip_fem_स्वतः_detect)
		answer = true;

	/* Override the REF CLK from the NVS with the one from platक्रमm data */
	gen_parms->general_params.ref_घड़ी = priv->ref_घड़ी;

	ret = wl1271_cmd_test(wl, gen_parms, माप(*gen_parms), answer);
	अगर (ret < 0) अणु
		wl1271_warning("CMD_INI_FILE_GENERAL_PARAM failed");
		जाओ out;
	पूर्ण

	gp->tx_bip_fem_manufacturer =
		gen_parms->general_params.tx_bip_fem_manufacturer;

	अगर (gp->tx_bip_fem_manufacturer >= WL1271_INI_FEM_MODULE_COUNT) अणु
		wl1271_warning("FEM index from FW out of bounds");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* If we are in calibrator based fem स्वतः detect - save fem nr */
	अगर (wl->plt_mode == PLT_FEM_DETECT)
		wl->fem_manuf = gp->tx_bip_fem_manufacturer;

	wl1271_debug(DEBUG_CMD, "FEM autodetect: %s, manufacturer: %d\n",
		answer == false ?
			"manual" :
		wl->plt_mode == PLT_FEM_DETECT ?
			"calibrator_fem_detect" :
			"auto",
		gp->tx_bip_fem_manufacturer);

out:
	kमुक्त(gen_parms);
	वापस ret;
पूर्ण

पूर्णांक wl128x_cmd_general_parms(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl128x_general_parms_cmd *gen_parms;
	काष्ठा wl128x_ini_general_params *gp =
		&((काष्ठा wl128x_nvs_file *)wl->nvs)->general_params;
	काष्ठा wl12xx_priv *priv = wl->priv;
	bool answer = false;
	पूर्णांक ret;

	अगर (!wl->nvs)
		वापस -ENODEV;

	अगर (gp->tx_bip_fem_manufacturer >= WL1271_INI_FEM_MODULE_COUNT) अणु
		wl1271_warning("FEM index from ini out of bounds");
		वापस -EINVAL;
	पूर्ण

	gen_parms = kzalloc(माप(*gen_parms), GFP_KERNEL);
	अगर (!gen_parms)
		वापस -ENOMEM;

	gen_parms->test.id = TEST_CMD_INI_खाता_GENERAL_PARAM;

	स_नकल(&gen_parms->general_params, gp, माप(*gp));

	/* If we started in PLT FEM_DETECT mode, क्रमce स्वतः detect */
	अगर (wl->plt_mode == PLT_FEM_DETECT)
		gen_parms->general_params.tx_bip_fem_स्वतः_detect = true;

	अगर (gen_parms->general_params.tx_bip_fem_स्वतः_detect)
		answer = true;

	/* Replace REF and TCXO CLKs with the ones from platक्रमm data */
	gen_parms->general_params.ref_घड़ी = priv->ref_घड़ी;
	gen_parms->general_params.tcxo_ref_घड़ी = priv->tcxo_घड़ी;

	ret = wl1271_cmd_test(wl, gen_parms, माप(*gen_parms), answer);
	अगर (ret < 0) अणु
		wl1271_warning("CMD_INI_FILE_GENERAL_PARAM failed");
		जाओ out;
	पूर्ण

	gp->tx_bip_fem_manufacturer =
		gen_parms->general_params.tx_bip_fem_manufacturer;

	अगर (gp->tx_bip_fem_manufacturer >= WL1271_INI_FEM_MODULE_COUNT) अणु
		wl1271_warning("FEM index from FW out of bounds");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* If we are in calibrator based fem स्वतः detect - save fem nr */
	अगर (wl->plt_mode == PLT_FEM_DETECT)
		wl->fem_manuf = gp->tx_bip_fem_manufacturer;

	wl1271_debug(DEBUG_CMD, "FEM autodetect: %s, manufacturer: %d\n",
		answer == false ?
			"manual" :
		wl->plt_mode == PLT_FEM_DETECT ?
			"calibrator_fem_detect" :
			"auto",
		gp->tx_bip_fem_manufacturer);

out:
	kमुक्त(gen_parms);
	वापस ret;
पूर्ण

पूर्णांक wl1271_cmd_radio_parms(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl1271_nvs_file *nvs = (काष्ठा wl1271_nvs_file *)wl->nvs;
	काष्ठा wl1271_radio_parms_cmd *radio_parms;
	काष्ठा wl1271_ini_general_params *gp = &nvs->general_params;
	पूर्णांक ret, fem_idx;

	अगर (!wl->nvs)
		वापस -ENODEV;

	radio_parms = kzalloc(माप(*radio_parms), GFP_KERNEL);
	अगर (!radio_parms)
		वापस -ENOMEM;

	radio_parms->test.id = TEST_CMD_INI_खाता_RADIO_PARAM;

	fem_idx = WL12XX_FEM_TO_NVS_ENTRY(gp->tx_bip_fem_manufacturer);

	/* 2.4GHz parameters */
	स_नकल(&radio_parms->अटल_params_2, &nvs->stat_radio_params_2,
	       माप(काष्ठा wl1271_ini_band_params_2));
	स_नकल(&radio_parms->dyn_params_2,
	       &nvs->dyn_radio_params_2[fem_idx].params,
	       माप(काष्ठा wl1271_ini_fem_params_2));

	/* 5GHz parameters */
	स_नकल(&radio_parms->अटल_params_5,
	       &nvs->stat_radio_params_5,
	       माप(काष्ठा wl1271_ini_band_params_5));
	स_नकल(&radio_parms->dyn_params_5,
	       &nvs->dyn_radio_params_5[fem_idx].params,
	       माप(काष्ठा wl1271_ini_fem_params_5));

	wl1271_dump(DEBUG_CMD, "TEST_CMD_INI_FILE_RADIO_PARAM: ",
		    radio_parms, माप(*radio_parms));

	ret = wl1271_cmd_test(wl, radio_parms, माप(*radio_parms), 0);
	अगर (ret < 0)
		wl1271_warning("CMD_INI_FILE_RADIO_PARAM failed");

	kमुक्त(radio_parms);
	वापस ret;
पूर्ण

पूर्णांक wl128x_cmd_radio_parms(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl128x_nvs_file *nvs = (काष्ठा wl128x_nvs_file *)wl->nvs;
	काष्ठा wl128x_radio_parms_cmd *radio_parms;
	काष्ठा wl128x_ini_general_params *gp = &nvs->general_params;
	पूर्णांक ret, fem_idx;

	अगर (!wl->nvs)
		वापस -ENODEV;

	radio_parms = kzalloc(माप(*radio_parms), GFP_KERNEL);
	अगर (!radio_parms)
		वापस -ENOMEM;

	radio_parms->test.id = TEST_CMD_INI_खाता_RADIO_PARAM;

	fem_idx = WL12XX_FEM_TO_NVS_ENTRY(gp->tx_bip_fem_manufacturer);

	/* 2.4GHz parameters */
	स_नकल(&radio_parms->अटल_params_2, &nvs->stat_radio_params_2,
	       माप(काष्ठा wl128x_ini_band_params_2));
	स_नकल(&radio_parms->dyn_params_2,
	       &nvs->dyn_radio_params_2[fem_idx].params,
	       माप(काष्ठा wl128x_ini_fem_params_2));

	/* 5GHz parameters */
	स_नकल(&radio_parms->अटल_params_5,
	       &nvs->stat_radio_params_5,
	       माप(काष्ठा wl128x_ini_band_params_5));
	स_नकल(&radio_parms->dyn_params_5,
	       &nvs->dyn_radio_params_5[fem_idx].params,
	       माप(काष्ठा wl128x_ini_fem_params_5));

	radio_parms->fem_venकरोr_and_options = nvs->fem_venकरोr_and_options;

	wl1271_dump(DEBUG_CMD, "TEST_CMD_INI_FILE_RADIO_PARAM: ",
		    radio_parms, माप(*radio_parms));

	ret = wl1271_cmd_test(wl, radio_parms, माप(*radio_parms), 0);
	अगर (ret < 0)
		wl1271_warning("CMD_INI_FILE_RADIO_PARAM failed");

	kमुक्त(radio_parms);
	वापस ret;
पूर्ण

पूर्णांक wl12xx_cmd_channel_चयन(काष्ठा wl1271 *wl,
			      काष्ठा wl12xx_vअगर *wlvअगर,
			      काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा wl12xx_cmd_channel_चयन *cmd;
	पूर्णांक ret;

	wl1271_debug(DEBUG_ACX, "cmd channel switch");

	cmd = kzalloc(माप(*cmd), GFP_KERNEL);
	अगर (!cmd) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cmd->role_id = wlvअगर->role_id;
	cmd->channel = ch_चयन->chandef.chan->hw_value;
	cmd->चयन_समय = ch_चयन->count;
	cmd->stop_tx = ch_चयन->block_tx;

	/* FIXME: control from mac80211 in the future */
	/* Enable TX on the target channel */
	cmd->post_चयन_tx_disable = 0;

	ret = wl1271_cmd_send(wl, CMD_CHANNEL_SWITCH, cmd, माप(*cmd), 0);
	अगर (ret < 0) अणु
		wl1271_error("failed to send channel switch command");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(cmd);

out:
	वापस ret;
पूर्ण
