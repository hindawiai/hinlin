<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2009 Nokia Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "init.h"
#समावेश "wl12xx_80211.h"
#समावेश "acx.h"
#समावेश "cmd.h"
#समावेश "reg.h"

पूर्णांक wl1251_hw_init_hwenc_config(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_feature_cfg(wl, 0);
	अगर (ret < 0) अणु
		wl1251_warning("couldn't set feature config");
		वापस ret;
	पूर्ण

	ret = wl1251_acx_शेष_key(wl, wl->शेष_key);
	अगर (ret < 0) अणु
		wl1251_warning("couldn't set default key");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_ढाँचाs_config(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;
	u8 partial_vbm[PARTIAL_VBM_MAX];

	/* send empty ढाँचाs क्रम fw memory reservation */
	ret = wl1251_cmd_ढाँचा_set(wl, CMD_PROBE_REQ, शून्य,
				      माप(काष्ठा wl12xx_probe_req_ढाँचा));
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_शून्य_DATA, शून्य,
				      माप(काष्ठा wl12xx_null_data_ढाँचा));
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_PS_POLL, शून्य,
				      माप(काष्ठा wl12xx_ps_poll_ढाँचा));
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_QOS_शून्य_DATA, शून्य,
				      माप
				      (काष्ठा wl12xx_qos_null_data_ढाँचा));
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_PROBE_RESP, शून्य,
				      माप
				      (काष्ठा wl12xx_probe_resp_ढाँचा));
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_cmd_ढाँचा_set(wl, CMD_BEACON, शून्य,
				      माप
				      (काष्ठा wl12xx_beacon_ढाँचा));
	अगर (ret < 0)
		वापस ret;

	/* tim ढाँचाs, first reserve space then allocate an empty one */
	स_रखो(partial_vbm, 0, PARTIAL_VBM_MAX);
	ret = wl1251_cmd_vbm(wl, TIM_ELE_ID, partial_vbm, PARTIAL_VBM_MAX, 0);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_cmd_vbm(wl, TIM_ELE_ID, partial_vbm, 1, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_rx_config(काष्ठा wl1251 *wl, u32 config, u32 filter)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_rx_msdu_lअगरe_समय(wl, RX_MSDU_LIFETIME_DEF);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_rx_config(wl, config, filter);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_phy_config(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_pd_threshold(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_slot(wl, DEFAULT_SLOT_TIME);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_group_address_tbl(wl, true, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_service_period_समयout(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_rts_threshold(wl, RTS_THRESHOLD_DEF);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_beacon_filter(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	/* disable beacon filtering at this stage */
	ret = wl1251_acx_beacon_filter_opt(wl, false);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_beacon_filter_table(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_pta(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_sg_enable(wl);
	अगर (ret < 0)
		वापस ret;

	ret = wl1251_acx_sg_cfg(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_energy_detection(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_cca_threshold(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_beacon_broadcast(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_bcn_dtim_options(wl);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक wl1251_hw_init_घातer_auth(काष्ठा wl1251 *wl)
अणु
	वापस wl1251_acx_sleep_auth(wl, WL1251_PSM_CAM);
पूर्ण

पूर्णांक wl1251_hw_init_mem_config(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	ret = wl1251_acx_mem_cfg(wl);
	अगर (ret < 0)
		वापस ret;

	wl->target_mem_map = kzalloc(माप(काष्ठा wl1251_acx_mem_map),
					  GFP_KERNEL);
	अगर (!wl->target_mem_map) अणु
		wl1251_error("couldn't allocate target memory map");
		वापस -ENOMEM;
	पूर्ण

	/* we now ask क्रम the firmware built memory map */
	ret = wl1251_acx_mem_map(wl, wl->target_mem_map,
				 माप(काष्ठा wl1251_acx_mem_map));
	अगर (ret < 0) अणु
		wl1251_error("couldn't retrieve firmware memory map");
		kमुक्त(wl->target_mem_map);
		wl->target_mem_map = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_hw_init_txq_fill(u8 qid,
				   काष्ठा acx_tx_queue_qos_config *config,
				   u32 num_blocks)
अणु
	config->qid = qid;

	चयन (qid) अणु
	हाल QOS_AC_BE:
		config->high_threshold =
			(QOS_TX_HIGH_BE_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_BE_DEF * num_blocks) / 100;
		अवरोध;
	हाल QOS_AC_BK:
		config->high_threshold =
			(QOS_TX_HIGH_BK_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_BK_DEF * num_blocks) / 100;
		अवरोध;
	हाल QOS_AC_VI:
		config->high_threshold =
			(QOS_TX_HIGH_VI_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_VI_DEF * num_blocks) / 100;
		अवरोध;
	हाल QOS_AC_VO:
		config->high_threshold =
			(QOS_TX_HIGH_VO_DEF * num_blocks) / 100;
		config->low_threshold =
			(QOS_TX_LOW_VO_DEF * num_blocks) / 100;
		अवरोध;
	शेष:
		wl1251_error("Invalid TX queue id: %d", qid);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl1251_hw_init_tx_queue_config(काष्ठा wl1251 *wl)
अणु
	काष्ठा acx_tx_queue_qos_config *config;
	काष्ठा wl1251_acx_mem_map *wl_mem_map = wl->target_mem_map;
	पूर्णांक ret, i;

	wl1251_debug(DEBUG_ACX, "acx tx queue config");

	config = kzalloc(माप(*config), GFP_KERNEL);
	अगर (!config) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < MAX_NUM_OF_AC; i++) अणु
		ret = wl1251_hw_init_txq_fill(i, config,
					      wl_mem_map->num_tx_mem_blocks);
		अगर (ret < 0)
			जाओ out;

		ret = wl1251_cmd_configure(wl, ACX_TX_QUEUE_CFG,
					   config, माप(*config));
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	wl1251_acx_ac_cfg(wl, AC_BE, CWMIN_BE, CWMAX_BE, AIFS_DIFS, TXOP_BE);
	wl1251_acx_ac_cfg(wl, AC_BK, CWMIN_BK, CWMAX_BK, AIFS_DIFS, TXOP_BK);
	wl1251_acx_ac_cfg(wl, AC_VI, CWMIN_VI, CWMAX_VI, AIFS_DIFS, TXOP_VI);
	wl1251_acx_ac_cfg(wl, AC_VO, CWMIN_VO, CWMAX_VO, AIFS_DIFS, TXOP_VO);

out:
	kमुक्त(config);
	वापस ret;
पूर्ण

अटल पूर्णांक wl1251_hw_init_data_path_config(काष्ठा wl1251 *wl)
अणु
	पूर्णांक ret;

	/* asking क्रम the data path parameters */
	wl->data_path = kzalloc(माप(काष्ठा acx_data_path_params_resp),
				GFP_KERNEL);
	अगर (!wl->data_path)
		वापस -ENOMEM;

	ret = wl1251_acx_data_path_params(wl, wl->data_path);
	अगर (ret < 0) अणु
		kमुक्त(wl->data_path);
		wl->data_path = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक wl1251_hw_init(काष्ठा wl1251 *wl)
अणु
	काष्ठा wl1251_acx_mem_map *wl_mem_map;
	पूर्णांक ret;

	ret = wl1251_hw_init_hwenc_config(wl);
	अगर (ret < 0)
		वापस ret;

	/* Template settings */
	ret = wl1251_hw_init_ढाँचाs_config(wl);
	अगर (ret < 0)
		वापस ret;

	/* Default memory configuration */
	ret = wl1251_hw_init_mem_config(wl);
	अगर (ret < 0)
		वापस ret;

	/* Default data path configuration  */
	ret = wl1251_hw_init_data_path_config(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* RX config */
	ret = wl1251_hw_init_rx_config(wl,
				       RX_CFG_PROMISCUOUS | RX_CFG_TSF,
				       RX_FILTER_OPTION_DEF);
	/* RX_CONFIG_OPTION_ANY_DST_ANY_BSS,
	   RX_FILTER_OPTION_FILTER_ALL); */
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* TX queues config */
	ret = wl1251_hw_init_tx_queue_config(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* PHY layer config */
	ret = wl1251_hw_init_phy_config(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Initialize connection monitoring thresholds */
	ret = wl1251_acx_conn_monit_params(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Beacon filtering */
	ret = wl1251_hw_init_beacon_filter(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Bluetooth WLAN coexistence */
	ret = wl1251_hw_init_pta(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Energy detection */
	ret = wl1251_hw_init_energy_detection(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Beacons and boradcast settings */
	ret = wl1251_hw_init_beacon_broadcast(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Enable rx data path */
	ret = wl1251_cmd_data_path_rx(wl, wl->channel, 1);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Enable tx data path */
	ret = wl1251_cmd_data_path_tx(wl, wl->channel, 1);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	/* Default घातer state */
	ret = wl1251_hw_init_घातer_auth(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_data_path;

	wl_mem_map = wl->target_mem_map;
	wl1251_info("%d tx blocks at 0x%x, %d rx blocks at 0x%x",
		    wl_mem_map->num_tx_mem_blocks,
		    wl->data_path->tx_control_addr,
		    wl_mem_map->num_rx_mem_blocks,
		    wl->data_path->rx_control_addr);

	वापस 0;

 out_मुक्त_data_path:
	kमुक्त(wl->data_path);

 out_मुक्त_memmap:
	kमुक्त(wl->target_mem_map);

	वापस ret;
पूर्ण
