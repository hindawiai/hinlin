<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2018 - 2019 Intel Corporation
 *
 * Portions of this file are derived from the ipw3945 project, as well
 * as portions of the ieee80211 subप्रणाली header files.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>

#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/mac80211.h>

#समावेश <यंत्र/भाग64.h>

#समावेश "iwl-io.h"
#समावेश "iwl-trans.h"
#समावेश "iwl-op-mode.h"
#समावेश "iwl-modparams.h"

#समावेश "dev.h"
#समावेश "calib.h"
#समावेश "agn.h"

/*****************************************************************************
 *
 * mac80211 entry poपूर्णांक functions
 *
 *****************************************************************************/

अटल स्थिर काष्ठा ieee80211_अगरace_limit iwlagn_sta_ap_limits[] = अणु
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_AP),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit iwlagn_2sta_limits[] = अणु
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination
iwlagn_अगरace_combinations_dualmode[] = अणु
	अणु .num_dअगरferent_channels = 1,
	  .max_पूर्णांकerfaces = 2,
	  .beacon_पूर्णांक_infra_match = true,
	  .limits = iwlagn_sta_ap_limits,
	  .n_limits = ARRAY_SIZE(iwlagn_sta_ap_limits),
	पूर्ण,
	अणु .num_dअगरferent_channels = 1,
	  .max_पूर्णांकerfaces = 2,
	  .limits = iwlagn_2sta_limits,
	  .n_limits = ARRAY_SIZE(iwlagn_2sta_limits),
	पूर्ण,
पूर्ण;

/*
 * Not a mac80211 entry poपूर्णांक function, but it fits in with all the
 * other mac80211 functions grouped here.
 */
पूर्णांक iwlagn_mac_setup_रेजिस्टर(काष्ठा iwl_priv *priv,
			      स्थिर काष्ठा iwl_ucode_capabilities *capa)
अणु
	पूर्णांक ret;
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा iwl_rxon_context *ctx;

	hw->rate_control_algorithm = "iwl-agn-rs";

	/* Tell mac80211 our अक्षरacteristics */
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, NEED_DTIM_BEFORE_ASSOC);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, QUEUE_CONTROL);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, WANT_MONITOR_VIF);

	अगर (priv->trans->max_skb_frags)
		hw->netdev_features = NETIF_F_HIGHDMA | NETIF_F_SG;

	hw->offchannel_tx_hw_queue = IWL_AUX_QUEUE;
	hw->radiotap_mcs_details |= IEEE80211_RADIOTAP_MCS_HAVE_FMT;

	/*
	 * Including the following line will crash some AP's.  This
	 * workaround हटाओs the stimulus which causes the crash until
	 * the AP software can be fixed.
	hw->max_tx_aggregation_subframes = LINK_QUAL_AGG_FRAME_LIMIT_DEF;
	 */

	अगर (priv->nvm_data->sku_cap_11n_enable)
		hw->wiphy->features |= NL80211_FEATURE_DYNAMIC_SMPS |
				       NL80211_FEATURE_STATIC_SMPS;

	/*
	 * Enable 11w अगर advertised by firmware and software crypto
	 * is not enabled (as the firmware will पूर्णांकerpret some mgmt
	 * packets, so enabling it with software crypto isn't safe)
	 */
	अगर (priv->fw->ucode_capa.flags & IWL_UCODE_TLV_FLAGS_MFP &&
	    !iwlwअगरi_mod_params.swcrypto)
		ieee80211_hw_set(hw, MFP_CAPABLE);

	hw->sta_data_size = माप(काष्ठा iwl_station_priv);
	hw->vअगर_data_size = माप(काष्ठा iwl_vअगर_priv);

	क्रम_each_context(priv, ctx) अणु
		hw->wiphy->पूर्णांकerface_modes |= ctx->पूर्णांकerface_modes;
		hw->wiphy->पूर्णांकerface_modes |= ctx->exclusive_पूर्णांकerface_modes;
	पूर्ण

	BUILD_BUG_ON(NUM_IWL_RXON_CTX != 2);

	अगर (hw->wiphy->पूर्णांकerface_modes & BIT(NL80211_IFTYPE_AP)) अणु
		hw->wiphy->अगरace_combinations =
			iwlagn_अगरace_combinations_dualmode;
		hw->wiphy->n_अगरace_combinations =
			ARRAY_SIZE(iwlagn_अगरace_combinations_dualmode);
	पूर्ण

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	hw->wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
				       REGULATORY_DISABLE_BEACON_HINTS;

#अगर_घोषित CONFIG_PM_SLEEP
	अगर (priv->fw->img[IWL_UCODE_WOWLAN].num_sec &&
	    priv->trans->ops->d3_suspend &&
	    priv->trans->ops->d3_resume &&
	    device_can_wakeup(priv->trans->dev)) अणु
		priv->wowlan_support.flags = WIPHY_WOWLAN_MAGIC_PKT |
					     WIPHY_WOWLAN_DISCONNECT |
					     WIPHY_WOWLAN_EAP_IDENTITY_REQ |
					     WIPHY_WOWLAN_RFKILL_RELEASE;
		अगर (!iwlwअगरi_mod_params.swcrypto)
			priv->wowlan_support.flags |=
				WIPHY_WOWLAN_SUPPORTS_GTK_REKEY |
				WIPHY_WOWLAN_GTK_REKEY_FAILURE;

		priv->wowlan_support.n_patterns = IWLAGN_WOWLAN_MAX_PATTERNS;
		priv->wowlan_support.pattern_min_len =
					IWLAGN_WOWLAN_MIN_PATTERN_LEN;
		priv->wowlan_support.pattern_max_len =
					IWLAGN_WOWLAN_MAX_PATTERN_LEN;
		hw->wiphy->wowlan = &priv->wowlan_support;
	पूर्ण
#पूर्ण_अगर

	अगर (iwlwअगरi_mod_params.घातer_save)
		hw->wiphy->flags |= WIPHY_FLAG_PS_ON_BY_DEFAULT;
	अन्यथा
		hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->max_scan_ssids = PROBE_OPTION_MAX;
	/* we create the 802.11 header and a max-length SSID element */
	hw->wiphy->max_scan_ie_len = capa->max_probe_length - 24 - 34;

	/*
	 * We करोn't use all queues: 4 and 9 are unused and any
	 * aggregation queue माला_लो mapped करोwn to the AC queue.
	 */
	hw->queues = IWLAGN_FIRST_AMPDU_QUEUE;

	hw->max_listen_पूर्णांकerval = IWL_CONN_MAX_LISTEN_INTERVAL;

	अगर (priv->nvm_data->bands[NL80211_BAND_2GHZ].n_channels)
		priv->hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&priv->nvm_data->bands[NL80211_BAND_2GHZ];
	अगर (priv->nvm_data->bands[NL80211_BAND_5GHZ].n_channels)
		priv->hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&priv->nvm_data->bands[NL80211_BAND_5GHZ];

	hw->wiphy->hw_version = priv->trans->hw_id;

	iwl_leds_init(priv);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_EXT_KEY_ID);

	ret = ieee80211_रेजिस्टर_hw(priv->hw);
	अगर (ret) अणु
		IWL_ERR(priv, "Failed to register hw (error %d)\n", ret);
		iwl_leds_निकास(priv);
		वापस ret;
	पूर्ण
	priv->mac80211_रेजिस्टरed = 1;

	वापस 0;
पूर्ण

व्योम iwlagn_mac_unरेजिस्टर(काष्ठा iwl_priv *priv)
अणु
	अगर (!priv->mac80211_रेजिस्टरed)
		वापस;
	iwl_leds_निकास(priv);
	ieee80211_unरेजिस्टर_hw(priv->hw);
	priv->mac80211_रेजिस्टरed = 0;
पूर्ण

अटल पूर्णांक __iwl_up(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_rxon_context *ctx;
	पूर्णांक ret;

	lockdep_निश्चित_held(&priv->mutex);

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status)) अणु
		IWL_WARN(priv, "Exit pending; will not bring the NIC up\n");
		वापस -EIO;
	पूर्ण

	क्रम_each_context(priv, ctx) अणु
		ret = iwlagn_alloc_bcast_station(priv, ctx);
		अगर (ret) अणु
			iwl_dealloc_bcast_stations(priv);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = iwl_trans_start_hw(priv->trans);
	अगर (ret) अणु
		IWL_ERR(priv, "Failed to start HW: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = iwl_run_init_ucode(priv);
	अगर (ret) अणु
		IWL_ERR(priv, "Failed to run INIT ucode: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = iwl_trans_start_hw(priv->trans);
	अगर (ret) अणु
		IWL_ERR(priv, "Failed to start HW: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = iwl_load_ucode_रुको_alive(priv, IWL_UCODE_REGULAR);
	अगर (ret) अणु
		IWL_ERR(priv, "Failed to start RT ucode: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = iwl_alive_start(priv);
	अगर (ret)
		जाओ error;
	वापस 0;

 error:
	set_bit(STATUS_EXIT_PENDING, &priv->status);
	iwl_करोwn(priv);
	clear_bit(STATUS_EXIT_PENDING, &priv->status);

	IWL_ERR(priv, "Unable to initialize device.\n");
	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_mac_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	पूर्णांक ret;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	/* we should be verअगरying the device is पढ़ोy to be खोलोed */
	mutex_lock(&priv->mutex);
	ret = __iwl_up(priv);
	mutex_unlock(&priv->mutex);
	अगर (ret)
		वापस ret;

	IWL_DEBUG_INFO(priv, "Start UP work done.\n");

	/* Now we should be करोne, and the READY bit should be set. */
	अगर (WARN_ON(!test_bit(STATUS_READY, &priv->status)))
		ret = -EIO;

	iwlagn_led_enable(priv);

	priv->is_खोलो = 1;
	IWL_DEBUG_MAC80211(priv, "leave\n");
	वापस 0;
पूर्ण

अटल व्योम iwlagn_mac_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	IWL_DEBUG_MAC80211(priv, "enter\n");

	अगर (!priv->is_खोलो)
		वापस;

	priv->is_खोलो = 0;

	mutex_lock(&priv->mutex);
	iwl_करोwn(priv);
	mutex_unlock(&priv->mutex);

	iwl_cancel_deferred_work(priv);

	flush_workqueue(priv->workqueue);

	IWL_DEBUG_MAC80211(priv, "leave\n");
पूर्ण

अटल व्योम iwlagn_mac_set_rekey_data(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	अगर (iwlwअगरi_mod_params.swcrypto)
		वापस;

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	अगर (priv->contexts[IWL_RXON_CTX_BSS].vअगर != vअगर)
		जाओ out;

	स_नकल(priv->kek, data->kek, NL80211_KEK_LEN);
	स_नकल(priv->kck, data->kck, NL80211_KCK_LEN);
	priv->replay_ctr =
		cpu_to_le64(be64_to_cpup((__be64 *)&data->replay_ctr));
	priv->have_rekey_data = true;

 out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक iwlagn_mac_suspend(काष्ठा ieee80211_hw *hw,
			      काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	पूर्णांक ret;

	अगर (WARN_ON(!wowlan))
		वापस -EINVAL;

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	/* Don't attempt WoWLAN when not associated, tear करोwn instead. */
	अगर (!ctx->vअगर || ctx->vअगर->type != NL80211_IFTYPE_STATION ||
	    !iwl_is_associated_ctx(ctx)) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	ret = iwlagn_suspend(priv, wowlan);
	अगर (ret)
		जाओ error;

	/* let the ucode operate on its own */
	iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_SET,
		    CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE);

	iwl_trans_d3_suspend(priv->trans, false, true);

	जाओ out;

 error:
	priv->wowlan = false;
	iwlagn_prepare_restart(priv);
	ieee80211_restart_hw(priv->hw);
 out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	वापस ret;
पूर्ण

काष्ठा iwl_resume_data अणु
	काष्ठा iwl_priv *priv;
	काष्ठा iwlagn_wowlan_status *cmd;
	bool valid;
पूर्ण;

अटल bool iwl_resume_status_fn(काष्ठा iwl_notअगर_रुको_data *notअगर_रुको,
				 काष्ठा iwl_rx_packet *pkt, व्योम *data)
अणु
	काष्ठा iwl_resume_data *resume_data = data;
	काष्ठा iwl_priv *priv = resume_data->priv;

	अगर (iwl_rx_packet_payload_len(pkt) != माप(*resume_data->cmd)) अणु
		IWL_ERR(priv, "rx wrong size data\n");
		वापस true;
	पूर्ण
	स_नकल(resume_data->cmd, pkt->data, माप(*resume_data->cmd));
	resume_data->valid = true;

	वापस true;
पूर्ण

अटल पूर्णांक iwlagn_mac_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	काष्ठा ieee80211_vअगर *vअगर;
	u32 base;
	पूर्णांक ret;
	क्रमागत iwl_d3_status d3_status;
	काष्ठा error_table_start अणु
		/* cf. काष्ठा iwl_error_event_table */
		u32 valid;
		u32 error_id;
	पूर्ण err_info;
	काष्ठा iwl_notअगरication_रुको status_रुको;
	अटल स्थिर u16 status_cmd[] = अणु
		REPLY_WOWLAN_GET_STATUS,
	पूर्ण;
	काष्ठा iwlagn_wowlan_status status_data = अणुपूर्ण;
	काष्ठा iwl_resume_data resume_data = अणु
		.priv = priv,
		.cmd = &status_data,
		.valid = false,
	पूर्ण;
	काष्ठा cfg80211_wowlan_wakeup wakeup = अणु
		.pattern_idx = -1,
	पूर्ण;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	स्थिर काष्ठा fw_img *img;
#पूर्ण_अगर

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	/* we'll clear ctx->vअगर during iwlagn_prepare_restart() */
	vअगर = ctx->vअगर;

	ret = iwl_trans_d3_resume(priv->trans, &d3_status, false, true);
	अगर (ret)
		जाओ out_unlock;

	अगर (d3_status != IWL_D3_STATUS_ALIVE) अणु
		IWL_INFO(priv, "Device was reset during suspend\n");
		जाओ out_unlock;
	पूर्ण

	/* uCode is no दीर्घer operating by itself */
	iwl_ग_लिखो32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
		    CSR_UCODE_DRV_GP1_BIT_D3_CFG_COMPLETE);

	base = priv->device_poपूर्णांकers.error_event_table;
	अगर (!iwlagn_hw_valid_rtc_data_addr(base)) अणु
		IWL_WARN(priv, "Invalid error table during resume!\n");
		जाओ out_unlock;
	पूर्ण

	iwl_trans_पढ़ो_mem_bytes(priv->trans, base,
				 &err_info, माप(err_info));

	अगर (err_info.valid) अणु
		IWL_INFO(priv, "error table is valid (%d, 0x%x)\n",
			 err_info.valid, err_info.error_id);
		अगर (err_info.error_id == RF_KILL_INDICATOR_FOR_WOWLAN) अणु
			wakeup.rfसमाप्त_release = true;
			ieee80211_report_wowlan_wakeup(vअगर, &wakeup,
						       GFP_KERNEL);
		पूर्ण
		जाओ out_unlock;
	पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	img = &priv->fw->img[IWL_UCODE_WOWLAN];
	अगर (!priv->wowlan_sram)
		priv->wowlan_sram =
			kzalloc(img->sec[IWL_UCODE_SECTION_DATA].len,
				GFP_KERNEL);

	अगर (priv->wowlan_sram)
		iwl_trans_पढ़ो_mem(priv->trans, 0x800000,
				   priv->wowlan_sram,
				   img->sec[IWL_UCODE_SECTION_DATA].len / 4);
#पूर्ण_अगर

	/*
	 * This is very strange. The GET_STATUS command is sent but the device
	 * करोesn't reply properly, it seems it doesn't बंद the RBD so one is
	 * always left खोलो ... As a result, we need to send another command
	 * and have to reset the driver afterwards. As we need to चयन to
	 * runसमय firmware again that'll happen.
	 */

	iwl_init_notअगरication_रुको(&priv->notअगर_रुको, &status_रुको, status_cmd,
				   ARRAY_SIZE(status_cmd), iwl_resume_status_fn,
				   &resume_data);

	iwl_dvm_send_cmd_pdu(priv, REPLY_WOWLAN_GET_STATUS, CMD_ASYNC, 0, शून्य);
	iwl_dvm_send_cmd_pdu(priv, REPLY_ECHO, CMD_ASYNC, 0, शून्य);
	/* an RBD is left खोलो in the firmware now! */

	ret = iwl_रुको_notअगरication(&priv->notअगर_रुको, &status_रुको, HZ/5);
	अगर (ret)
		जाओ out_unlock;

	अगर (resume_data.valid && priv->contexts[IWL_RXON_CTX_BSS].vअगर) अणु
		u32 reasons = le32_to_cpu(status_data.wakeup_reason);
		काष्ठा cfg80211_wowlan_wakeup *wakeup_report;

		IWL_INFO(priv, "WoWLAN wakeup reason(s): 0x%.8x\n", reasons);

		अगर (reasons) अणु
			अगर (reasons & IWLAGN_WOWLAN_WAKEUP_MAGIC_PACKET)
				wakeup.magic_pkt = true;
			अगर (reasons & IWLAGN_WOWLAN_WAKEUP_PATTERN_MATCH)
				wakeup.pattern_idx = status_data.pattern_number;
			अगर (reasons & (IWLAGN_WOWLAN_WAKEUP_BEACON_MISS |
				       IWLAGN_WOWLAN_WAKEUP_LINK_CHANGE))
				wakeup.disconnect = true;
			अगर (reasons & IWLAGN_WOWLAN_WAKEUP_GTK_REKEY_FAIL)
				wakeup.gtk_rekey_failure = true;
			अगर (reasons & IWLAGN_WOWLAN_WAKEUP_EAP_IDENT_REQ)
				wakeup.eap_identity_req = true;
			अगर (reasons & IWLAGN_WOWLAN_WAKEUP_4WAY_HANDSHAKE)
				wakeup.four_way_handshake = true;
			wakeup_report = &wakeup;
		पूर्ण अन्यथा अणु
			wakeup_report = शून्य;
		पूर्ण

		ieee80211_report_wowlan_wakeup(vअगर, wakeup_report, GFP_KERNEL);
	पूर्ण

	priv->wowlan = false;

	iwlagn_prepare_restart(priv);

	स_रखो((व्योम *)&ctx->active, 0, माप(ctx->active));
	iwl_connection_init_rx_config(priv, ctx);
	iwlagn_set_rxon_chain(priv, ctx);

 out_unlock:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	ieee80211_resume_disconnect(vअगर);

	वापस 1;
पूर्ण

अटल व्योम iwlagn_mac_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	device_set_wakeup_enable(priv->trans->dev, enabled);
पूर्ण
#पूर्ण_अगर

अटल व्योम iwlagn_mac_tx(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_tx_control *control,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	अगर (iwlagn_tx_skb(priv, control->sta, skb))
		ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

अटल व्योम iwlagn_mac_update_tkip_key(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_key_conf *keyconf,
				       काष्ठा ieee80211_sta *sta,
				       u32 iv32, u16 *phase1key)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	iwl_update_tkip_key(priv, vअगर, keyconf, sta, iv32, phase1key);
पूर्ण

अटल पूर्णांक iwlagn_mac_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;
	काष्ठा iwl_rxon_context *ctx = vअगर_priv->ctx;
	पूर्णांक ret;
	bool is_शेष_wep_key = false;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	अगर (iwlwअगरi_mod_params.swcrypto) अणु
		IWL_DEBUG_MAC80211(priv, "leave - hwcrypto disabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * We could program these keys पूर्णांकo the hardware as well, but we
	 * करोn't expect much multicast traffic in IBSS and having keys
	 * क्रम more stations is probably more useful.
	 *
	 * Mark key TX-only and वापस 0.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		key->hw_key_idx = WEP_INVALID_OFFSET;
		वापस 0;
	पूर्ण

	/* If they key was TX-only, accept deletion */
	अगर (cmd == DISABLE_KEY && key->hw_key_idx == WEP_INVALID_OFFSET)
		वापस 0;

	mutex_lock(&priv->mutex);
	iwl_scan_cancel_समयout(priv, 100);

	BUILD_BUG_ON(WEP_INVALID_OFFSET == IWLAGN_HW_KEY_DEFAULT);

	/*
	 * If we are getting WEP group key and we didn't receive any key mapping
	 * so far, we are in legacy wep mode (group key only), otherwise we are
	 * in 1X mode.
	 * In legacy wep mode, we use another host command to the uCode.
	 */
	अगर ((key->cipher == WLAN_CIPHER_SUITE_WEP40 ||
	     key->cipher == WLAN_CIPHER_SUITE_WEP104) && !sta) अणु
		अगर (cmd == SET_KEY)
			is_शेष_wep_key = !ctx->key_mapping_keys;
		अन्यथा
			is_शेष_wep_key =
				key->hw_key_idx == IWLAGN_HW_KEY_DEFAULT;
	पूर्ण


	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (is_शेष_wep_key) अणु
			ret = iwl_set_शेष_wep_key(priv, vअगर_priv->ctx, key);
			अवरोध;
		पूर्ण
		ret = iwl_set_dynamic_key(priv, vअगर_priv->ctx, key, sta);
		अगर (ret) अणु
			/*
			 * can't add key for RX, but we don't need it
			 * in the device क्रम TX so still वापस 0
			 */
			ret = 0;
			key->hw_key_idx = WEP_INVALID_OFFSET;
		पूर्ण

		IWL_DEBUG_MAC80211(priv, "enable hwcrypto key\n");
		अवरोध;
	हाल DISABLE_KEY:
		अगर (is_शेष_wep_key)
			ret = iwl_हटाओ_शेष_wep_key(priv, ctx, key);
		अन्यथा
			ret = iwl_हटाओ_dynamic_key(priv, ctx, key, sta);

		IWL_DEBUG_MAC80211(priv, "disable hwcrypto key\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_mac_ampdu_action(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	पूर्णांक ret = -EINVAL;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	u8 buf_size = params->buf_size;
	काष्ठा iwl_station_priv *sta_priv = (व्योम *) sta->drv_priv;

	IWL_DEBUG_HT(priv, "A-MPDU action on addr %pM tid %d\n",
		     sta->addr, tid);

	अगर (!(priv->nvm_data->sku_cap_11n_enable))
		वापस -EACCES;

	IWL_DEBUG_MAC80211(priv, "enter\n");
	mutex_lock(&priv->mutex);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		अगर (!iwl_enable_rx_ampdu())
			अवरोध;
		IWL_DEBUG_HT(priv, "start Rx\n");
		ret = iwl_sta_rx_agg_start(priv, sta, tid, *ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		IWL_DEBUG_HT(priv, "stop Rx\n");
		ret = iwl_sta_rx_agg_stop(priv, sta, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		अगर (!priv->trans->ops->txq_enable)
			अवरोध;
		अगर (!iwl_enable_tx_ampdu())
			अवरोध;
		IWL_DEBUG_HT(priv, "start Tx\n");
		ret = iwlagn_tx_agg_start(priv, vअगर, sta, tid, ssn);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		IWL_DEBUG_HT(priv, "Flush Tx\n");
		ret = iwlagn_tx_agg_flush(priv, vअगर, sta, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		IWL_DEBUG_HT(priv, "stop Tx\n");
		ret = iwlagn_tx_agg_stop(priv, vअगर, sta, tid);
		अगर ((ret == 0) && (priv->agg_tids_count > 0)) अणु
			priv->agg_tids_count--;
			IWL_DEBUG_HT(priv, "priv->agg_tids_count = %u\n",
				     priv->agg_tids_count);
		पूर्ण
		अगर (!priv->agg_tids_count &&
		    priv->hw_params.use_rts_क्रम_aggregation) अणु
			/*
			 * चयन off RTS/CTS अगर it was previously enabled
			 */
			sta_priv->lq_sta.lq.general_params.flags &=
				~LINK_QUAL_FLAGS_SET_STA_TLC_RTS_MSK;
			iwl_send_lq_cmd(priv, iwl_rxon_ctx_from_vअगर(vअगर),
					&sta_priv->lq_sta.lq, CMD_ASYNC, false);
		पूर्ण
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		ret = iwlagn_tx_agg_oper(priv, vअगर, sta, tid, buf_size);
		अवरोध;
	पूर्ण
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_mac_sta_add(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;
	bool is_ap = vअगर->type == NL80211_IFTYPE_STATION;
	पूर्णांक ret;
	u8 sta_id;

	IWL_DEBUG_INFO(priv, "proceeding to add station %pM\n",
			sta->addr);
	sta_priv->sta_id = IWL_INVALID_STATION;

	atomic_set(&sta_priv->pending_frames, 0);
	अगर (vअगर->type == NL80211_IFTYPE_AP)
		sta_priv->client = true;

	ret = iwl_add_station_common(priv, vअगर_priv->ctx, sta->addr,
				     is_ap, sta, &sta_id);
	अगर (ret) अणु
		IWL_ERR(priv, "Unable to add station %pM (%d)\n",
			sta->addr, ret);
		/* Should we वापस success अगर वापस code is EEXIST ? */
		वापस ret;
	पूर्ण

	sta_priv->sta_id = sta_id;

	वापस 0;
पूर्ण

अटल पूर्णांक iwlagn_mac_sta_हटाओ(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	पूर्णांक ret;

	IWL_DEBUG_INFO(priv, "proceeding to remove station %pM\n", sta->addr);

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		/*
		 * Station will be हटाओd from device when the RXON
		 * is set to unassociated -- just deactivate it here
		 * to aव्योम re-programming it.
		 */
		ret = 0;
		iwl_deactivate_station(priv, sta_priv->sta_id, sta->addr);
	पूर्ण अन्यथा अणु
		ret = iwl_हटाओ_station(priv, sta_priv->sta_id, sta->addr);
		अगर (ret)
			IWL_DEBUG_QUIET_RFKILL(priv,
				"Error removing station %pM\n", sta->addr);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक iwlagn_mac_sta_state(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta,
				क्रमागत ieee80211_sta_state old_state,
				क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;
	क्रमागत अणु
		NONE, ADD, REMOVE, HT_RATE_INIT, ADD_RATE_INIT,
	पूर्ण op = NONE;
	पूर्णांक ret;

	IWL_DEBUG_MAC80211(priv, "station %pM state change %d->%d\n",
			   sta->addr, old_state, new_state);

	mutex_lock(&priv->mutex);
	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		अगर (old_state == IEEE80211_STA_NOTEXIST &&
		    new_state == IEEE80211_STA_NONE)
			op = ADD;
		अन्यथा अगर (old_state == IEEE80211_STA_NONE &&
			 new_state == IEEE80211_STA_NOTEXIST)
			op = REMOVE;
		अन्यथा अगर (old_state == IEEE80211_STA_AUTH &&
			 new_state == IEEE80211_STA_ASSOC)
			op = HT_RATE_INIT;
	पूर्ण अन्यथा अणु
		अगर (old_state == IEEE80211_STA_AUTH &&
		    new_state == IEEE80211_STA_ASSOC)
			op = ADD_RATE_INIT;
		अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
			 new_state == IEEE80211_STA_AUTH)
			op = REMOVE;
	पूर्ण

	चयन (op) अणु
	हाल ADD:
		ret = iwlagn_mac_sta_add(hw, vअगर, sta);
		अगर (ret)
			अवरोध;
		/*
		 * Clear the in-progress flag, the AP station entry was added
		 * but we'll initialize LQ only when we've associated (which
		 * would also clear the in-progress flag). This is necessary
		 * in हाल we never initialize LQ because association fails.
		 */
		spin_lock_bh(&priv->sta_lock);
		priv->stations[iwl_sta_id(sta)].used &=
			~IWL_STA_UCODE_INPROGRESS;
		spin_unlock_bh(&priv->sta_lock);
		अवरोध;
	हाल REMOVE:
		ret = iwlagn_mac_sta_हटाओ(hw, vअगर, sta);
		अवरोध;
	हाल ADD_RATE_INIT:
		ret = iwlagn_mac_sta_add(hw, vअगर, sta);
		अगर (ret)
			अवरोध;
		/* Initialize rate scaling */
		IWL_DEBUG_INFO(priv,
			       "Initializing rate scaling for station %pM\n",
			       sta->addr);
		iwl_rs_rate_init(priv, sta, iwl_sta_id(sta));
		ret = 0;
		अवरोध;
	हाल HT_RATE_INIT:
		/* Initialize rate scaling */
		ret = iwl_sta_update_ht(priv, vअगर_priv->ctx, sta);
		अगर (ret)
			अवरोध;
		IWL_DEBUG_INFO(priv,
			       "Initializing rate scaling for station %pM\n",
			       sta->addr);
		iwl_rs_rate_init(priv, sta, iwl_sta_id(sta));
		ret = 0;
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	/*
	 * mac80211 might WARN अगर we fail, but due the way we
	 * (badly) handle hard rfसमाप्त, we might fail here
	 */
	अगर (iwl_is_rfसमाप्त(priv))
		ret = 0;

	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	वापस ret;
पूर्ण

अटल व्योम iwlagn_mac_channel_चयन(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_channel *channel = ch_चयन->chandef.chan;
	काष्ठा iwl_ht_config *ht_conf = &priv->current_ht_config;
	/*
	 * MULTI-FIXME
	 * When we add support क्रम multiple पूर्णांकerfaces, we need to
	 * revisit this. The channel चयन command in the device
	 * only affects the BSS context, but what करोes that really
	 * mean? And what अगर we get a CSA on the second पूर्णांकerface?
	 * This needs a lot of work.
	 */
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];
	u16 ch;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	mutex_lock(&priv->mutex);

	अगर (iwl_is_rfसमाप्त(priv))
		जाओ out;

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status) ||
	    test_bit(STATUS_SCANNING, &priv->status) ||
	    test_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status))
		जाओ out;

	अगर (!iwl_is_associated_ctx(ctx))
		जाओ out;

	अगर (!priv->lib->set_channel_चयन)
		जाओ out;

	ch = channel->hw_value;
	अगर (le16_to_cpu(ctx->active.channel) == ch)
		जाओ out;

	priv->current_ht_config.smps = conf->smps_mode;

	/* Configure HT40 channels */
	चयन (cfg80211_get_chandef_type(&ch_चयन->chandef)) अणु
	हाल NL80211_CHAN_NO_HT:
	हाल NL80211_CHAN_HT20:
		ctx->ht.is_40mhz = false;
		ctx->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_NONE;
		अवरोध;
	हाल NL80211_CHAN_HT40MINUS:
		ctx->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
		ctx->ht.is_40mhz = true;
		अवरोध;
	हाल NL80211_CHAN_HT40PLUS:
		ctx->ht.extension_chan_offset = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
		ctx->ht.is_40mhz = true;
		अवरोध;
	पूर्ण

	अगर ((le16_to_cpu(ctx->staging.channel) != ch))
		ctx->staging.flags = 0;

	iwl_set_rxon_channel(priv, channel, ctx);
	iwl_set_rxon_ht(priv, ht_conf);
	iwl_set_flags_क्रम_band(priv, ctx, channel->band, ctx->vअगर);

	/*
	 * at this poपूर्णांक, staging_rxon has the
	 * configuration क्रम channel चयन
	 */
	set_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status);
	priv->चयन_channel = cpu_to_le16(ch);
	अगर (priv->lib->set_channel_चयन(priv, ch_चयन)) अणु
		clear_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status);
		priv->चयन_channel = 0;
		ieee80211_chचयन_करोne(ctx->vअगर, false);
	पूर्ण

out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
पूर्ण

व्योम iwl_chचयन_करोne(काष्ठा iwl_priv *priv, bool is_success)
अणु
	/*
	 * MULTI-FIXME
	 * See iwlagn_mac_channel_चयन.
	 */
	काष्ठा iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status))
		वापस;

	अगर (!test_and_clear_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status))
		वापस;

	अगर (ctx->vअगर)
		ieee80211_chचयन_करोne(ctx->vअगर, is_success);
पूर्ण

अटल व्योम iwlagn_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *total_flags,
				    u64 multicast)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	__le32 filter_or = 0, filter_nand = 0;
	काष्ठा iwl_rxon_context *ctx;

#घोषणा CHK(test, flag)	करो अणु \
	अगर (*total_flags & (test))		\
		filter_or |= (flag);		\
	अन्यथा					\
		filter_nand |= (flag);		\
	पूर्ण जबतक (0)

	IWL_DEBUG_MAC80211(priv, "Enter: changed: 0x%x, total: 0x%x\n",
			changed_flags, *total_flags);

	CHK(FIF_OTHER_BSS, RXON_FILTER_PROMISC_MSK);
	/* Setting _just_ RXON_FILTER_CTL2HOST_MSK causes FH errors */
	CHK(FIF_CONTROL, RXON_FILTER_CTL2HOST_MSK | RXON_FILTER_PROMISC_MSK);
	CHK(FIF_BCN_PRBRESP_PROMISC, RXON_FILTER_BCON_AWARE_MSK);

#अघोषित CHK

	mutex_lock(&priv->mutex);

	क्रम_each_context(priv, ctx) अणु
		ctx->staging.filter_flags &= ~filter_nand;
		ctx->staging.filter_flags |= filter_or;

		/*
		 * Not committing directly because hardware can perक्रमm a scan,
		 * but we'll eventually commit the filter flags change anyway.
		 */
	पूर्ण

	mutex_unlock(&priv->mutex);

	/*
	 * Receiving all multicast frames is always enabled by the
	 * शेष flags setup in iwl_connection_init_rx_config()
	 * since we currently करो not support programming multicast
	 * filters पूर्णांकo the device.
	 */
	*total_flags &= FIF_OTHER_BSS | FIF_ALLMULTI |
			FIF_BCN_PRBRESP_PROMISC | FIF_CONTROL;
पूर्ण

अटल व्योम iwlagn_mac_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     u32 queues, bool drop)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	u32 scd_queues;

	mutex_lock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "enter\n");

	अगर (test_bit(STATUS_EXIT_PENDING, &priv->status)) अणु
		IWL_DEBUG_TX(priv, "Aborting flush due to device shutdown\n");
		जाओ करोne;
	पूर्ण
	अगर (iwl_is_rfसमाप्त(priv)) अणु
		IWL_DEBUG_TX(priv, "Aborting flush due to RF Kill\n");
		जाओ करोne;
	पूर्ण

	scd_queues = BIT(priv->trans->trans_cfg->base_params->num_of_queues) - 1;
	scd_queues &= ~(BIT(IWL_IPAN_CMD_QUEUE_NUM) |
			BIT(IWL_DEFAULT_CMD_QUEUE_NUM));

	अगर (drop) अणु
		IWL_DEBUG_TX_QUEUES(priv, "Flushing SCD queues: 0x%x\n",
				    scd_queues);
		अगर (iwlagn_txfअगरo_flush(priv, scd_queues)) अणु
			IWL_ERR(priv, "flush request fail\n");
			जाओ करोne;
		पूर्ण
	पूर्ण

	IWL_DEBUG_TX_QUEUES(priv, "wait transmit/flush all frames\n");
	iwl_trans_रुको_tx_queues_empty(priv->trans, scd_queues);
करोne:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");
पूर्ण

अटल व्योम iwlagn_mac_event_callback(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      स्थिर काष्ठा ieee80211_event *event)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	अगर (event->type != RSSI_EVENT)
		वापस;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	अगर (priv->lib->bt_params &&
	    priv->lib->bt_params->advanced_bt_coexist) अणु
		अगर (event->u.rssi.data == RSSI_EVENT_LOW)
			priv->bt_enable_pspoll = true;
		अन्यथा अगर (event->u.rssi.data == RSSI_EVENT_HIGH)
			priv->bt_enable_pspoll = false;

		queue_work(priv->workqueue, &priv->bt_runसमय_config);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_MAC80211(priv, "Advanced BT coex disabled,"
				"ignoring RSSI callback\n");
	पूर्ण

	IWL_DEBUG_MAC80211(priv, "leave\n");
पूर्ण

अटल पूर्णांक iwlagn_mac_set_tim(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_sta *sta, bool set)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	queue_work(priv->workqueue, &priv->beacon_update);

	वापस 0;
पूर्ण

अटल पूर्णांक iwlagn_mac_conf_tx(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			      स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;
	काष्ठा iwl_rxon_context *ctx = vअगर_priv->ctx;
	पूर्णांक q;

	अगर (WARN_ON(!ctx))
		वापस -EINVAL;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	अगर (!iwl_is_पढ़ोy_rf(priv)) अणु
		IWL_DEBUG_MAC80211(priv, "leave - RF not ready\n");
		वापस -EIO;
	पूर्ण

	अगर (queue >= AC_NUM) अणु
		IWL_DEBUG_MAC80211(priv, "leave - queue >= AC_NUM %d\n", queue);
		वापस 0;
	पूर्ण

	q = AC_NUM - 1 - queue;

	mutex_lock(&priv->mutex);

	ctx->qos_data.def_qos_parm.ac[q].cw_min =
		cpu_to_le16(params->cw_min);
	ctx->qos_data.def_qos_parm.ac[q].cw_max =
		cpu_to_le16(params->cw_max);
	ctx->qos_data.def_qos_parm.ac[q].aअगरsn = params->aअगरs;
	ctx->qos_data.def_qos_parm.ac[q].edca_txop =
			cpu_to_le16((params->txop * 32));

	ctx->qos_data.def_qos_parm.ac[q].reserved1 = 0;

	mutex_unlock(&priv->mutex);

	IWL_DEBUG_MAC80211(priv, "leave\n");
	वापस 0;
पूर्ण

अटल पूर्णांक iwlagn_mac_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);

	वापस priv->ibss_manager == IWL_IBSS_MANAGER;
पूर्ण

अटल पूर्णांक iwl_set_mode(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx)
अणु
	iwl_connection_init_rx_config(priv, ctx);

	iwlagn_set_rxon_chain(priv, ctx);

	वापस iwlagn_commit_rxon(priv, ctx);
पूर्ण

अटल पूर्णांक iwl_setup_पूर्णांकerface(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx)
अणु
	काष्ठा ieee80211_vअगर *vअगर = ctx->vअगर;
	पूर्णांक err, ac;

	lockdep_निश्चित_held(&priv->mutex);

	/*
	 * This variable will be correct only when there's just
	 * a single context, but all code using it is क्रम hardware
	 * that supports only one context.
	 */
	priv->iw_mode = vअगर->type;

	ctx->is_active = true;

	err = iwl_set_mode(priv, ctx);
	अगर (err) अणु
		अगर (!ctx->always_active)
			ctx->is_active = false;
		वापस err;
	पूर्ण

	अगर (priv->lib->bt_params && priv->lib->bt_params->advanced_bt_coexist &&
	    vअगर->type == NL80211_IFTYPE_ADHOC) अणु
		/*
		 * pretend to have high BT traffic as दीर्घ as we
		 * are operating in IBSS mode, as this will cause
		 * the rate scaling etc. to behave as पूर्णांकended.
		 */
		priv->bt_traffic_load = IWL_BT_COEX_TRAFFIC_LOAD_HIGH;
	पूर्ण

	/* set up queue mappings */
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		vअगर->hw_queue[ac] = ctx->ac_to_queue[ac];

	अगर (vअगर->type == NL80211_IFTYPE_AP)
		vअगर->cab_queue = ctx->mcast_queue;
	अन्यथा
		vअगर->cab_queue = IEEE80211_INVAL_HW_QUEUE;

	वापस 0;
पूर्ण

अटल पूर्णांक iwlagn_mac_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;
	काष्ठा iwl_rxon_context *पंचांगp, *ctx = शून्य;
	पूर्णांक err;
	क्रमागत nl80211_अगरtype vअगरtype = ieee80211_vअगर_type_p2p(vअगर);
	bool reset = false;

	IWL_DEBUG_MAC80211(priv, "enter: type %d, addr %pM\n",
			   vअगरtype, vअगर->addr);

	mutex_lock(&priv->mutex);

	अगर (!iwl_is_पढ़ोy_rf(priv)) अणु
		IWL_WARN(priv, "Try to add interface when device not ready\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम_each_context(priv, पंचांगp) अणु
		u32 possible_modes =
			पंचांगp->पूर्णांकerface_modes | पंचांगp->exclusive_पूर्णांकerface_modes;

		अगर (पंचांगp->vअगर) अणु
			/* On reset we need to add the same पूर्णांकerface again */
			अगर (पंचांगp->vअगर == vअगर) अणु
				reset = true;
				ctx = पंचांगp;
				अवरोध;
			पूर्ण

			/* check अगर this busy context is exclusive */
			अगर (पंचांगp->exclusive_पूर्णांकerface_modes &
						BIT(पंचांगp->vअगर->type)) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			जारी;
		पूर्ण

		अगर (!(possible_modes & BIT(vअगरtype)))
			जारी;

		/* have maybe usable context w/o पूर्णांकerface */
		ctx = पंचांगp;
		अवरोध;
	पूर्ण

	अगर (!ctx) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	vअगर_priv->ctx = ctx;
	ctx->vअगर = vअगर;

	/*
	 * In SNIFFER device type, the firmware reports the FCS to
	 * the host, rather than snipping it off. Unक्रमtunately,
	 * mac80211 करोesn't (yet) provide a per-packet flag क्रम
	 * this, so that we have to set the hardware flag based
	 * on the पूर्णांकerfaces added. As the monitor पूर्णांकerface can
	 * only be present by itself, and will be हटाओd beक्रमe
	 * other पूर्णांकerfaces are added, this is safe.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_MONITOR)
		ieee80211_hw_set(priv->hw, RX_INCLUDES_FCS);
	अन्यथा
		__clear_bit(IEEE80211_HW_RX_INCLUDES_FCS, priv->hw->flags);

	err = iwl_setup_पूर्णांकerface(priv, ctx);
	अगर (!err || reset)
		जाओ out;

	ctx->vअगर = शून्य;
	priv->iw_mode = NL80211_IFTYPE_STATION;
 out:
	mutex_unlock(&priv->mutex);

	IWL_DEBUG_MAC80211(priv, "leave\n");
	वापस err;
पूर्ण

अटल व्योम iwl_tearकरोwn_पूर्णांकerface(काष्ठा iwl_priv *priv,
				   काष्ठा ieee80211_vअगर *vअगर,
				   bool mode_change)
अणु
	काष्ठा iwl_rxon_context *ctx = iwl_rxon_ctx_from_vअगर(vअगर);

	lockdep_निश्चित_held(&priv->mutex);

	अगर (priv->scan_vअगर == vअगर) अणु
		iwl_scan_cancel_समयout(priv, 200);
		iwl_क्रमce_scan_end(priv);
	पूर्ण

	अगर (!mode_change) अणु
		iwl_set_mode(priv, ctx);
		अगर (!ctx->always_active)
			ctx->is_active = false;
	पूर्ण

	/*
	 * When removing the IBSS पूर्णांकerface, overग_लिखो the
	 * BT traffic load with the stored one from the last
	 * notअगरication, अगर any. If this is a device that
	 * करोesn't implement this, this has no effect since
	 * both values are the same and zero.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
		priv->bt_traffic_load = priv->last_bt_traffic_load;
पूर्ण

अटल व्योम iwlagn_mac_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_rxon_context *ctx = iwl_rxon_ctx_from_vअगर(vअगर);

	IWL_DEBUG_MAC80211(priv, "enter\n");

	mutex_lock(&priv->mutex);

	WARN_ON(ctx->vअगर != vअगर);
	ctx->vअगर = शून्य;

	iwl_tearकरोwn_पूर्णांकerface(priv, vअगर, false);

	mutex_unlock(&priv->mutex);

	IWL_DEBUG_MAC80211(priv, "leave\n");

पूर्ण

अटल पूर्णांक iwlagn_mac_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       क्रमागत nl80211_अगरtype newtype, bool newp2p)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_rxon_context *ctx, *पंचांगp;
	क्रमागत nl80211_अगरtype newvअगरtype = newtype;
	u32 पूर्णांकerface_modes;
	पूर्णांक err;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	newtype = ieee80211_अगरtype_p2p(newtype, newp2p);

	mutex_lock(&priv->mutex);

	ctx = iwl_rxon_ctx_from_vअगर(vअगर);

	/*
	 * To simplअगरy this code, only support changes on the
	 * BSS context. The PAN context is usually reasचिन्हित
	 * by creating/removing P2P पूर्णांकerfaces anyway.
	 */
	अगर (ctx->ctxid != IWL_RXON_CTX_BSS) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!ctx->vअगर || !iwl_is_पढ़ोy_rf(priv)) अणु
		/*
		 * Huh? But रुको ... this can maybe happen when
		 * we're in the middle of a firmware restart!
		 */
		err = -EBUSY;
		जाओ out;
	पूर्ण

	/* Check अगर the चयन is supported in the same context */
	पूर्णांकerface_modes = ctx->पूर्णांकerface_modes | ctx->exclusive_पूर्णांकerface_modes;
	अगर (!(पूर्णांकerface_modes & BIT(newtype))) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (ctx->exclusive_पूर्णांकerface_modes & BIT(newtype)) अणु
		क्रम_each_context(priv, पंचांगp) अणु
			अगर (ctx == पंचांगp)
				जारी;

			अगर (!पंचांगp->is_active)
				जारी;

			/*
			 * The current mode चयन would be exclusive, but
			 * another context is active ... refuse the चयन.
			 */
			err = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	/* success */
	iwl_tearकरोwn_पूर्णांकerface(priv, vअगर, true);
	vअगर->type = newvअगरtype;
	vअगर->p2p = newp2p;
	err = iwl_setup_पूर्णांकerface(priv, ctx);
	WARN_ON(err);
	/*
	 * We've चयनed पूर्णांकernally, but submitting to the
	 * device may have failed क्रम some reason. Mask this
	 * error, because otherwise mac80211 will not चयन
	 * (and set the पूर्णांकerface type back) and we'll be
	 * out of sync with it.
	 */
	err = 0;

 out:
	mutex_unlock(&priv->mutex);
	IWL_DEBUG_MAC80211(priv, "leave\n");

	वापस err;
पूर्ण

अटल पूर्णांक iwlagn_mac_hw_scan(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	पूर्णांक ret;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	अगर (req->n_channels == 0)
		वापस -EINVAL;

	mutex_lock(&priv->mutex);

	/*
	 * If an पूर्णांकernal scan is in progress, just set
	 * up the scan_request as per above.
	 */
	अगर (priv->scan_type != IWL_SCAN_NORMAL) अणु
		IWL_DEBUG_SCAN(priv,
			       "SCAN request during internal scan - defer\n");
		priv->scan_request = req;
		priv->scan_vअगर = vअगर;
		ret = 0;
	पूर्ण अन्यथा अणु
		priv->scan_request = req;
		priv->scan_vअगर = vअगर;
		/*
		 * mac80211 will only ask क्रम one band at a समय
		 * so using channels[0] here is ok
		 */
		ret = iwl_scan_initiate(priv, vअगर, IWL_SCAN_NORMAL,
					req->channels[0]->band);
		अगर (ret) अणु
			priv->scan_request = शून्य;
			priv->scan_vअगर = शून्य;
		पूर्ण
	पूर्ण

	IWL_DEBUG_MAC80211(priv, "leave\n");

	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल व्योम iwl_sta_modअगरy_ps_wake(काष्ठा iwl_priv *priv, पूर्णांक sta_id)
अणु
	काष्ठा iwl_addsta_cmd cmd = अणु
		.mode = STA_CONTROL_MODIFY_MSK,
		.station_flags_msk = STA_FLG_PWR_SAVE_MSK,
		.sta.sta_id = sta_id,
	पूर्ण;

	iwl_send_add_sta(priv, &cmd, CMD_ASYNC);
पूर्ण

अटल व्योम iwlagn_mac_sta_notअगरy(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  क्रमागत sta_notअगरy_cmd cmd,
				  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_priv *priv = IWL_MAC80211_GET_DVM(hw);
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	पूर्णांक sta_id;

	IWL_DEBUG_MAC80211(priv, "enter\n");

	चयन (cmd) अणु
	हाल STA_NOTIFY_SLEEP:
		WARN_ON(!sta_priv->client);
		sta_priv->asleep = true;
		अगर (atomic_पढ़ो(&sta_priv->pending_frames) > 0)
			ieee80211_sta_block_awake(hw, sta, true);
		अवरोध;
	हाल STA_NOTIFY_AWAKE:
		WARN_ON(!sta_priv->client);
		अगर (!sta_priv->asleep)
			अवरोध;
		sta_priv->asleep = false;
		sta_id = iwl_sta_id(sta);
		अगर (sta_id != IWL_INVALID_STATION)
			iwl_sta_modअगरy_ps_wake(priv, sta_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	IWL_DEBUG_MAC80211(priv, "leave\n");
पूर्ण

स्थिर काष्ठा ieee80211_ops iwlagn_hw_ops = अणु
	.tx = iwlagn_mac_tx,
	.start = iwlagn_mac_start,
	.stop = iwlagn_mac_stop,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend = iwlagn_mac_suspend,
	.resume = iwlagn_mac_resume,
	.set_wakeup = iwlagn_mac_set_wakeup,
#पूर्ण_अगर
	.add_पूर्णांकerface = iwlagn_mac_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = iwlagn_mac_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface = iwlagn_mac_change_पूर्णांकerface,
	.config = iwlagn_mac_config,
	.configure_filter = iwlagn_configure_filter,
	.set_key = iwlagn_mac_set_key,
	.update_tkip_key = iwlagn_mac_update_tkip_key,
	.set_rekey_data = iwlagn_mac_set_rekey_data,
	.conf_tx = iwlagn_mac_conf_tx,
	.bss_info_changed = iwlagn_bss_info_changed,
	.ampdu_action = iwlagn_mac_ampdu_action,
	.hw_scan = iwlagn_mac_hw_scan,
	.sta_notअगरy = iwlagn_mac_sta_notअगरy,
	.sta_state = iwlagn_mac_sta_state,
	.channel_चयन = iwlagn_mac_channel_चयन,
	.flush = iwlagn_mac_flush,
	.tx_last_beacon = iwlagn_mac_tx_last_beacon,
	.event_callback = iwlagn_mac_event_callback,
	.set_tim = iwlagn_mac_set_tim,
पूर्ण;

/* This function both allocates and initializes hw and priv. */
काष्ठा ieee80211_hw *iwl_alloc_all(व्योम)
अणु
	काष्ठा iwl_priv *priv;
	काष्ठा iwl_op_mode *op_mode;
	/* mac80211 allocates memory क्रम this device instance, including
	 *   space क्रम this driver's निजी काष्ठाure */
	काष्ठा ieee80211_hw *hw;

	hw = ieee80211_alloc_hw(माप(काष्ठा iwl_priv) +
				माप(काष्ठा iwl_op_mode), &iwlagn_hw_ops);
	अगर (!hw)
		जाओ out;

	op_mode = hw->priv;
	priv = IWL_OP_MODE_GET_DVM(op_mode);
	priv->hw = hw;

out:
	वापस hw;
पूर्ण
