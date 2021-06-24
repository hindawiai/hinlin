<शैली गुरु>
/*
 * NXP Wireless LAN device driver: functions क्रम station ioctl
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "cfg80211.h"

अटल पूर्णांक disconnect_on_suspend;
module_param(disconnect_on_suspend, पूर्णांक, 0644);

/*
 * Copies the multicast address list from device to driver.
 *
 * This function करोes not validate the destination memory क्रम
 * size, and the calling function must ensure enough memory is
 * available.
 */
पूर्णांक mwअगरiex_copy_mcast_addr(काष्ठा mwअगरiex_multicast_list *mlist,
			    काष्ठा net_device *dev)
अणु
	पूर्णांक i = 0;
	काष्ठा netdev_hw_addr *ha;

	netdev_क्रम_each_mc_addr(ha, dev)
		स_नकल(&mlist->mac_list[i++], ha->addr, ETH_ALEN);

	वापस i;
पूर्ण

/*
 * Wait queue completion handler.
 *
 * This function रुकोs on a cmd रुको queue. It also cancels the pending
 * request after waking up, in हाल of errors.
 */
पूर्णांक mwअगरiex_रुको_queue_complete(काष्ठा mwअगरiex_adapter *adapter,
				काष्ठा cmd_ctrl_node *cmd_queued)
अणु
	पूर्णांक status;

	/* Wait क्रम completion */
	status = रुको_event_पूर्णांकerruptible_समयout(adapter->cmd_रुको_q.रुको,
						  *(cmd_queued->condition),
						  (12 * HZ));
	अगर (status <= 0) अणु
		अगर (status == 0)
			status = -ETIMEDOUT;
		mwअगरiex_dbg(adapter, ERROR, "cmd_wait_q terminated: %d\n",
			    status);
		mwअगरiex_cancel_all_pending_cmd(adapter);
		वापस status;
	पूर्ण

	status = adapter->cmd_रुको_q.status;
	adapter->cmd_रुको_q.status = 0;

	वापस status;
पूर्ण

/*
 * This function prepares the correct firmware command and
 * issues it to set the multicast list.
 *
 * This function can be used to enable promiscuous mode, or enable all
 * multicast packets, or to enable selective multicast.
 */
पूर्णांक mwअगरiex_request_set_multicast_list(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा mwअगरiex_multicast_list *mcast_list)
अणु
	पूर्णांक ret = 0;
	u16 old_pkt_filter;

	old_pkt_filter = priv->curr_pkt_filter;

	अगर (mcast_list->mode == MWIFIEX_PROMISC_MODE) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: Enable Promiscuous mode\n");
		priv->curr_pkt_filter |= HostCmd_ACT_MAC_PROMISCUOUS_ENABLE;
		priv->curr_pkt_filter &=
			~HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE;
	पूर्ण अन्यथा अणु
		/* Multicast */
		priv->curr_pkt_filter &= ~HostCmd_ACT_MAC_PROMISCUOUS_ENABLE;
		अगर (mcast_list->mode == MWIFIEX_ALL_MULTI_MODE) अणु
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: Enabling All Multicast!\n");
			priv->curr_pkt_filter |=
				HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE;
		पूर्ण अन्यथा अणु
			priv->curr_pkt_filter &=
				~HostCmd_ACT_MAC_ALL_MULTICAST_ENABLE;
			mwअगरiex_dbg(priv->adapter, INFO,
				    "info: Set multicast list=%d\n",
				    mcast_list->num_multicast_addr);
			/* Send multicast addresses to firmware */
			ret = mwअगरiex_send_cmd(priv,
					       HostCmd_CMD_MAC_MULTICAST_ADR,
					       HostCmd_ACT_GEN_SET, 0,
					       mcast_list, false);
		पूर्ण
	पूर्ण
	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: old_pkt_filter=%#x, curr_pkt_filter=%#x\n",
		    old_pkt_filter, priv->curr_pkt_filter);
	अगर (old_pkt_filter != priv->curr_pkt_filter) अणु
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_MAC_CONTROL,
				       HostCmd_ACT_GEN_SET,
				       0, &priv->curr_pkt_filter, false);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function fills bss descriptor काष्ठाure using provided
 * inक्रमmation.
 * beacon_ie buffer is allocated in this function. It is caller's
 * responsibility to मुक्त the memory.
 */
पूर्णांक mwअगरiex_fill_new_bss_desc(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा cfg80211_bss *bss,
			      काष्ठा mwअगरiex_bssdescriptor *bss_desc)
अणु
	u8 *beacon_ie;
	माप_प्रकार beacon_ie_len;
	काष्ठा mwअगरiex_bss_priv *bss_priv = (व्योम *)bss->priv;
	स्थिर काष्ठा cfg80211_bss_ies *ies;

	rcu_पढ़ो_lock();
	ies = rcu_dereference(bss->ies);
	beacon_ie = kmemdup(ies->data, ies->len, GFP_ATOMIC);
	beacon_ie_len = ies->len;
	bss_desc->बारtamp = ies->tsf;
	rcu_पढ़ो_unlock();

	अगर (!beacon_ie) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    " failed to alloc beacon_ie\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(bss_desc->mac_address, bss->bssid, ETH_ALEN);
	bss_desc->rssi = bss->संकेत;
	/* The caller of this function will मुक्त beacon_ie */
	bss_desc->beacon_buf = beacon_ie;
	bss_desc->beacon_buf_size = beacon_ie_len;
	bss_desc->beacon_period = bss->beacon_पूर्णांकerval;
	bss_desc->cap_info_biपंचांगap = bss->capability;
	bss_desc->bss_band = bss_priv->band;
	bss_desc->fw_tsf = bss_priv->fw_tsf;
	अगर (bss_desc->cap_info_biपंचांगap & WLAN_CAPABILITY_PRIVACY) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: InterpretIE: AP WEP enabled\n");
		bss_desc->privacy = MWIFIEX_802_11_PRIV_FILTER_8021X_WEP;
	पूर्ण अन्यथा अणु
		bss_desc->privacy = MWIFIEX_802_11_PRIV_FILTER_ACCEPT_ALL;
	पूर्ण
	अगर (bss_desc->cap_info_biपंचांगap & WLAN_CAPABILITY_IBSS)
		bss_desc->bss_mode = NL80211_IFTYPE_ADHOC;
	अन्यथा
		bss_desc->bss_mode = NL80211_IFTYPE_STATION;

	/* Disable 11ac by शेष. Enable it only where there
	 * exist VHT_CAP IE in AP beacon
	 */
	bss_desc->disable_11ac = true;

	अगर (bss_desc->cap_info_biपंचांगap & WLAN_CAPABILITY_SPECTRUM_MGMT)
		bss_desc->sensed_11h = true;

	वापस mwअगरiex_update_bss_desc_with_ie(priv->adapter, bss_desc);
पूर्ण

व्योम mwअगरiex_dnld_txpwr_table(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (priv->adapter->dt_node) अणु
		अक्षर txpwr[] = अणु"marvell,00_txpwrlimit"पूर्ण;

		स_नकल(&txpwr[8], priv->adapter->country_code, 2);
		mwअगरiex_dnld_dt_cfgdata(priv, priv->adapter->dt_node, txpwr);
	पूर्ण
पूर्ण

अटल पूर्णांक mwअगरiex_process_country_ie(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा cfg80211_bss *bss)
अणु
	स्थिर u8 *country_ie;
	u8 country_ie_len;
	काष्ठा mwअगरiex_802_11d_करोमुख्य_reg *करोमुख्य_info =
					&priv->adapter->करोमुख्य_reg;

	rcu_पढ़ो_lock();
	country_ie = ieee80211_bss_get_ie(bss, WLAN_EID_COUNTRY);
	अगर (!country_ie) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	country_ie_len = country_ie[1];
	अगर (country_ie_len < IEEE80211_COUNTRY_IE_MIN_LEN) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	अगर (!म_भेदन(priv->adapter->country_code, &country_ie[2], 2)) अणु
		rcu_पढ़ो_unlock();
		mwअगरiex_dbg(priv->adapter, INFO,
			    "11D: skip setting domain info in FW\n");
		वापस 0;
	पूर्ण

	अगर (country_ie_len >
	    (IEEE80211_COUNTRY_STRING_LEN + MWIFIEX_MAX_TRIPLET_802_11D)) अणु
		rcu_पढ़ो_unlock();
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "11D: country_ie_len overflow!, deauth AP\n");
		वापस -EINVAL;
	पूर्ण

	स_नकल(priv->adapter->country_code, &country_ie[2], 2);

	करोमुख्य_info->country_code[0] = country_ie[2];
	करोमुख्य_info->country_code[1] = country_ie[3];
	करोमुख्य_info->country_code[2] = ' ';

	country_ie_len -= IEEE80211_COUNTRY_STRING_LEN;

	करोमुख्य_info->no_of_triplet =
		country_ie_len / माप(काष्ठा ieee80211_country_ie_triplet);

	स_नकल((u8 *)करोमुख्य_info->triplet,
	       &country_ie[2] + IEEE80211_COUNTRY_STRING_LEN, country_ie_len);

	rcu_पढ़ो_unlock();

	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11D_DOMAIN_INFO,
			     HostCmd_ACT_GEN_SET, 0, शून्य, false)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "11D: setting domain info in FW fail\n");
		वापस -1;
	पूर्ण

	mwअगरiex_dnld_txpwr_table(priv);

	वापस 0;
पूर्ण

/*
 * In Ad-Hoc mode, the IBSS is created अगर not found in scan list.
 * In both Ad-Hoc and infra mode, an deauthentication is perक्रमmed
 * first.
 */
पूर्णांक mwअगरiex_bss_start(काष्ठा mwअगरiex_निजी *priv, काष्ठा cfg80211_bss *bss,
		      काष्ठा cfg80211_ssid *req_ssid)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_bssdescriptor *bss_desc = शून्य;

	priv->scan_block = false;

	अगर (bss) अणु
		अगर (adapter->region_code == 0x00 &&
		    mwअगरiex_process_country_ie(priv, bss))
			वापस -EINVAL;

		/* Allocate and fill new bss descriptor */
		bss_desc = kzalloc(माप(काष्ठा mwअगरiex_bssdescriptor),
				   GFP_KERNEL);
		अगर (!bss_desc)
			वापस -ENOMEM;

		ret = mwअगरiex_fill_new_bss_desc(priv, bss, bss_desc);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	अगर (priv->bss_mode == NL80211_IFTYPE_STATION ||
	    priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT) अणु
		u8 config_bands;

		अगर (!bss_desc)
			वापस -1;

		अगर (mwअगरiex_band_to_radio_type(bss_desc->bss_band) ==
						HostCmd_SCAN_RADIO_TYPE_BG) अणु
			config_bands = BAND_B | BAND_G | BAND_GN;
		पूर्ण अन्यथा अणु
			config_bands = BAND_A | BAND_AN;
			अगर (adapter->fw_bands & BAND_AAC)
				config_bands |= BAND_AAC;
		पूर्ण

		अगर (!((config_bands | adapter->fw_bands) & ~adapter->fw_bands))
			adapter->config_bands = config_bands;

		ret = mwअगरiex_check_network_compatibility(priv, bss_desc);
		अगर (ret)
			जाओ करोne;

		अगर (mwअगरiex_11h_get_csa_बंदd_channel(priv) ==
							(u8)bss_desc->channel) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "Attempt to reconnect on csa closed chan(%d)\n",
				    bss_desc->channel);
			ret = -1;
			जाओ करोne;
		पूर्ण

		mwअगरiex_dbg(adapter, INFO,
			    "info: SSID found in scan list ...\t"
			    "associating...\n");

		mwअगरiex_stop_net_dev_queue(priv->netdev, adapter);
		अगर (netअगर_carrier_ok(priv->netdev))
			netअगर_carrier_off(priv->netdev);

		/* Clear any past association response stored क्रम
		 * application retrieval */
		priv->assoc_rsp_size = 0;
		ret = mwअगरiex_associate(priv, bss_desc);

		/* If auth type is स्वतः and association fails using खोलो mode,
		 * try to connect using shared mode */
		अगर (ret == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG &&
		    priv->sec_info.is_authtype_स्वतः &&
		    priv->sec_info.wep_enabled) अणु
			priv->sec_info.authentication_mode =
						NL80211_AUTHTYPE_SHARED_KEY;
			ret = mwअगरiex_associate(priv, bss_desc);
		पूर्ण

		अगर (bss)
			cfg80211_put_bss(priv->adapter->wiphy, bss);
	पूर्ण अन्यथा अणु
		/* Adhoc mode */
		/* If the requested SSID matches current SSID, वापस */
		अगर (bss_desc && bss_desc->ssid.ssid_len &&
		    (!mwअगरiex_ssid_cmp(&priv->curr_bss_params.bss_descriptor.
				       ssid, &bss_desc->ssid))) अणु
			ret = 0;
			जाओ करोne;
		पूर्ण

		priv->adhoc_is_link_sensed = false;

		ret = mwअगरiex_check_network_compatibility(priv, bss_desc);

		mwअगरiex_stop_net_dev_queue(priv->netdev, adapter);
		अगर (netअगर_carrier_ok(priv->netdev))
			netअगर_carrier_off(priv->netdev);

		अगर (!ret) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: network found in scan\t"
				    " list. Joining...\n");
			ret = mwअगरiex_adhoc_join(priv, bss_desc);
			अगर (bss)
				cfg80211_put_bss(priv->adapter->wiphy, bss);
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: Network not found in\t"
				    "the list, creating adhoc with ssid = %s\n",
				    req_ssid->ssid);
			ret = mwअगरiex_adhoc_start(priv, req_ssid);
		पूर्ण
	पूर्ण

करोne:
	/* beacon_ie buffer was allocated in function
	 * mwअगरiex_fill_new_bss_desc(). Free it now.
	 */
	अगर (bss_desc)
		kमुक्त(bss_desc->beacon_buf);
	kमुक्त(bss_desc);

	अगर (ret < 0)
		priv->attempted_bss_desc = शून्य;

	वापस ret;
पूर्ण

/*
 * IOCTL request handler to set host sleep configuration.
 *
 * This function prepares the correct firmware command and
 * issues it.
 */
पूर्णांक mwअगरiex_set_hs_params(काष्ठा mwअगरiex_निजी *priv, u16 action,
			  पूर्णांक cmd_type, काष्ठा mwअगरiex_ds_hs_cfg *hs_cfg)

अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक status = 0;
	u32 prev_cond = 0;

	अगर (!hs_cfg)
		वापस -ENOMEM;

	चयन (action) अणु
	हाल HostCmd_ACT_GEN_SET:
		अगर (adapter->pps_uapsd_mode) अणु
			mwअगरiex_dbg(adapter, INFO,
				    "info: Host Sleep IOCTL\t"
				    "is blocked in UAPSD/PPS mode\n");
			status = -1;
			अवरोध;
		पूर्ण
		अगर (hs_cfg->is_invoke_hostcmd) अणु
			अगर (hs_cfg->conditions == HS_CFG_CANCEL) अणु
				अगर (!test_bit(MWIFIEX_IS_HS_CONFIGURED,
					      &adapter->work_flags))
					/* Alपढ़ोy cancelled */
					अवरोध;
				/* Save previous condition */
				prev_cond = le32_to_cpu(adapter->hs_cfg
							.conditions);
				adapter->hs_cfg.conditions =
						cpu_to_le32(hs_cfg->conditions);
			पूर्ण अन्यथा अगर (hs_cfg->conditions) अणु
				adapter->hs_cfg.conditions =
						cpu_to_le32(hs_cfg->conditions);
				adapter->hs_cfg.gpio = (u8)hs_cfg->gpio;
				अगर (hs_cfg->gap)
					adapter->hs_cfg.gap = (u8)hs_cfg->gap;
			पूर्ण अन्यथा अगर (adapter->hs_cfg.conditions ==
				   cpu_to_le32(HS_CFG_CANCEL)) अणु
				/* Return failure अगर no parameters क्रम HS
				   enable */
				status = -1;
				अवरोध;
			पूर्ण

			status = mwअगरiex_send_cmd(priv,
						  HostCmd_CMD_802_11_HS_CFG_ENH,
						  HostCmd_ACT_GEN_SET, 0,
						  &adapter->hs_cfg,
						  cmd_type == MWIFIEX_SYNC_CMD);

			अगर (hs_cfg->conditions == HS_CFG_CANCEL)
				/* Restore previous condition */
				adapter->hs_cfg.conditions =
						cpu_to_le32(prev_cond);
		पूर्ण अन्यथा अणु
			adapter->hs_cfg.conditions =
						cpu_to_le32(hs_cfg->conditions);
			adapter->hs_cfg.gpio = (u8)hs_cfg->gpio;
			adapter->hs_cfg.gap = (u8)hs_cfg->gap;
		पूर्ण
		अवरोध;
	हाल HostCmd_ACT_GEN_GET:
		hs_cfg->conditions = le32_to_cpu(adapter->hs_cfg.conditions);
		hs_cfg->gpio = adapter->hs_cfg.gpio;
		hs_cfg->gap = adapter->hs_cfg.gap;
		अवरोध;
	शेष:
		status = -1;
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/*
 * Sends IOCTL request to cancel the existing Host Sleep configuration.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक mwअगरiex_cancel_hs(काष्ठा mwअगरiex_निजी *priv, पूर्णांक cmd_type)
अणु
	काष्ठा mwअगरiex_ds_hs_cfg hscfg;

	hscfg.conditions = HS_CFG_CANCEL;
	hscfg.is_invoke_hostcmd = true;

	वापस mwअगरiex_set_hs_params(priv, HostCmd_ACT_GEN_SET,
				    cmd_type, &hscfg);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_cancel_hs);

/*
 * Sends IOCTL request to cancel the existing Host Sleep configuration.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक mwअगरiex_enable_hs(काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_ds_hs_cfg hscfg;
	काष्ठा mwअगरiex_निजी *priv;
	पूर्णांक i;

	अगर (disconnect_on_suspend) अणु
		क्रम (i = 0; i < adapter->priv_num; i++) अणु
			priv = adapter->priv[i];
			अगर (priv)
				mwअगरiex_deauthenticate(priv, शून्य);
		पूर्ण
	पूर्ण

	priv = mwअगरiex_get_priv(adapter, MWIFIEX_BSS_ROLE_STA);

	अगर (priv && priv->sched_scanning) अणु
#अगर_घोषित CONFIG_PM
		अगर (priv->wdev.wiphy->wowlan_config &&
		    !priv->wdev.wiphy->wowlan_config->nd_config) अणु
#पूर्ण_अगर
			mwअगरiex_dbg(adapter, CMD, "aborting bgscan!\n");
			mwअगरiex_stop_bg_scan(priv);
			cfg80211_sched_scan_stopped(priv->wdev.wiphy, 0);
#अगर_घोषित CONFIG_PM
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (adapter->hs_activated) अणु
		mwअगरiex_dbg(adapter, CMD,
			    "cmd: HS Already activated\n");
		वापस true;
	पूर्ण

	adapter->hs_activate_रुको_q_woken = false;

	स_रखो(&hscfg, 0, माप(hscfg));
	hscfg.is_invoke_hostcmd = true;

	set_bit(MWIFIEX_IS_HS_ENABLING, &adapter->work_flags);
	mwअगरiex_cancel_all_pending_cmd(adapter);

	अगर (mwअगरiex_set_hs_params(mwअगरiex_get_priv(adapter,
						   MWIFIEX_BSS_ROLE_STA),
				  HostCmd_ACT_GEN_SET, MWIFIEX_SYNC_CMD,
				  &hscfg)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "IOCTL request HS enable failed\n");
		वापस false;
	पूर्ण

	अगर (रुको_event_पूर्णांकerruptible_समयout(adapter->hs_activate_रुको_q,
					     adapter->hs_activate_रुको_q_woken,
					     (10 * HZ)) <= 0) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "hs_activate_wait_q terminated\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_enable_hs);

/*
 * IOCTL request handler to get BSS inक्रमmation.
 *
 * This function collates the inक्रमmation from dअगरferent driver काष्ठाures
 * to send to the user.
 */
पूर्णांक mwअगरiex_get_bss_info(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा mwअगरiex_bss_info *info)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;

	अगर (!info)
		वापस -1;

	bss_desc = &priv->curr_bss_params.bss_descriptor;

	info->bss_mode = priv->bss_mode;

	स_नकल(&info->ssid, &bss_desc->ssid, माप(काष्ठा cfg80211_ssid));

	स_नकल(&info->bssid, &bss_desc->mac_address, ETH_ALEN);

	info->bss_chan = bss_desc->channel;

	स_नकल(info->country_code, adapter->country_code,
	       IEEE80211_COUNTRY_STRING_LEN);

	info->media_connected = priv->media_connected;

	info->max_घातer_level = priv->max_tx_घातer_level;
	info->min_घातer_level = priv->min_tx_घातer_level;

	info->adhoc_state = priv->adhoc_state;

	info->bcn_nf_last = priv->bcn_nf_last;

	अगर (priv->sec_info.wep_enabled)
		info->wep_status = true;
	अन्यथा
		info->wep_status = false;

	info->is_hs_configured = test_bit(MWIFIEX_IS_HS_CONFIGURED,
					  &adapter->work_flags);
	info->is_deep_sleep = adapter->is_deep_sleep;

	वापस 0;
पूर्ण

/*
 * The function disables स्वतः deep sleep mode.
 */
पूर्णांक mwअगरiex_disable_स्वतः_ds(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_ds_स्वतः_ds स्वतः_ds = अणु
		.स्वतः_ds = DEEP_SLEEP_OFF,
	पूर्ण;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_PS_MODE_ENH,
				DIS_AUTO_PS, BITMAP_AUTO_DS, &स्वतः_ds, true);
पूर्ण
EXPORT_SYMBOL_GPL(mwअगरiex_disable_स्वतः_ds);

/*
 * Sends IOCTL request to get the data rate.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक mwअगरiex_drv_get_data_rate(काष्ठा mwअगरiex_निजी *priv, u32 *rate)
अणु
	पूर्णांक ret;

	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_TX_RATE_QUERY,
			       HostCmd_ACT_GEN_GET, 0, शून्य, true);

	अगर (!ret) अणु
		अगर (priv->is_data_rate_स्वतः)
			*rate = mwअगरiex_index_to_data_rate(priv, priv->tx_rate,
							   priv->tx_htinfo);
		अन्यथा
			*rate = priv->data_rate;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * IOCTL request handler to set tx घातer configuration.
 *
 * This function prepares the correct firmware command and
 * issues it.
 *
 * For non-स्वतः घातer mode, all the following घातer groups are set -
 *      - Modulation class HR/DSSS
 *      - Modulation class OFDM
 *      - Modulation class HTBW20
 *      - Modulation class HTBW40
 */
पूर्णांक mwअगरiex_set_tx_घातer(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा mwअगरiex_घातer_cfg *घातer_cfg)
अणु
	पूर्णांक ret;
	काष्ठा host_cmd_ds_txpwr_cfg *txp_cfg;
	काष्ठा mwअगरiex_types_घातer_group *pg_tlv;
	काष्ठा mwअगरiex_घातer_group *pg;
	u8 *buf;
	u16 dbm = 0;

	अगर (!घातer_cfg->is_घातer_स्वतः) अणु
		dbm = (u16) घातer_cfg->घातer_level;
		अगर ((dbm < priv->min_tx_घातer_level) ||
		    (dbm > priv->max_tx_घातer_level)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "txpower value %d dBm\t"
				    "is out of range (%d dBm-%d dBm)\n",
				    dbm, priv->min_tx_घातer_level,
				    priv->max_tx_घातer_level);
			वापस -1;
		पूर्ण
	पूर्ण
	buf = kzalloc(MWIFIEX_SIZE_OF_CMD_BUFFER, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	txp_cfg = (काष्ठा host_cmd_ds_txpwr_cfg *) buf;
	txp_cfg->action = cpu_to_le16(HostCmd_ACT_GEN_SET);
	अगर (!घातer_cfg->is_घातer_स्वतः) अणु
		u16 dbm_min = घातer_cfg->is_घातer_fixed ?
			      dbm : priv->min_tx_घातer_level;

		txp_cfg->mode = cpu_to_le32(1);
		pg_tlv = (काष्ठा mwअगरiex_types_घातer_group *)
			 (buf + माप(काष्ठा host_cmd_ds_txpwr_cfg));
		pg_tlv->type = cpu_to_le16(TLV_TYPE_POWER_GROUP);
		pg_tlv->length =
			cpu_to_le16(4 * माप(काष्ठा mwअगरiex_घातer_group));
		pg = (काष्ठा mwअगरiex_घातer_group *)
		     (buf + माप(काष्ठा host_cmd_ds_txpwr_cfg)
		      + माप(काष्ठा mwअगरiex_types_घातer_group));
		/* Power group क्रम modulation class HR/DSSS */
		pg->first_rate_code = 0x00;
		pg->last_rate_code = 0x03;
		pg->modulation_class = MOD_CLASS_HR_DSSS;
		pg->घातer_step = 0;
		pg->घातer_min = (s8) dbm_min;
		pg->घातer_max = (s8) dbm;
		pg++;
		/* Power group क्रम modulation class OFDM */
		pg->first_rate_code = 0x00;
		pg->last_rate_code = 0x07;
		pg->modulation_class = MOD_CLASS_OFDM;
		pg->घातer_step = 0;
		pg->घातer_min = (s8) dbm_min;
		pg->घातer_max = (s8) dbm;
		pg++;
		/* Power group क्रम modulation class HTBW20 */
		pg->first_rate_code = 0x00;
		pg->last_rate_code = 0x20;
		pg->modulation_class = MOD_CLASS_HT;
		pg->घातer_step = 0;
		pg->घातer_min = (s8) dbm_min;
		pg->घातer_max = (s8) dbm;
		pg->ht_bandwidth = HT_BW_20;
		pg++;
		/* Power group क्रम modulation class HTBW40 */
		pg->first_rate_code = 0x00;
		pg->last_rate_code = 0x20;
		pg->modulation_class = MOD_CLASS_HT;
		pg->घातer_step = 0;
		pg->घातer_min = (s8) dbm_min;
		pg->घातer_max = (s8) dbm;
		pg->ht_bandwidth = HT_BW_40;
	पूर्ण
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_TXPWR_CFG,
			       HostCmd_ACT_GEN_SET, 0, buf, true);

	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 * IOCTL request handler to get घातer save mode.
 *
 * This function prepares the correct firmware command and
 * issues it.
 */
पूर्णांक mwअगरiex_drv_set_घातer(काष्ठा mwअगरiex_निजी *priv, u32 *ps_mode)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u16 sub_cmd;

	अगर (*ps_mode)
		adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_PSP;
	अन्यथा
		adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_CAM;
	sub_cmd = (*ps_mode) ? EN_AUTO_PS : DIS_AUTO_PS;
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_PS_MODE_ENH,
			       sub_cmd, BITMAP_STA_PS, शून्य, true);
	अगर ((!ret) && (sub_cmd == DIS_AUTO_PS))
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_PS_MODE_ENH,
				       GET_PS, 0, शून्य, false);

	वापस ret;
पूर्ण

/*
 * IOCTL request handler to set/reset WPA IE.
 *
 * The supplied WPA IE is treated as a opaque buffer. Only the first field
 * is checked to determine WPA version. If buffer length is zero, the existing
 * WPA IE is reset.
 */
अटल पूर्णांक mwअगरiex_set_wpa_ie(काष्ठा mwअगरiex_निजी *priv,
			      u8 *ie_data_ptr, u16 ie_len)
अणु
	अगर (ie_len) अणु
		अगर (ie_len > माप(priv->wpa_ie)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "failed to copy WPA IE, too big\n");
			वापस -1;
		पूर्ण
		स_नकल(priv->wpa_ie, ie_data_ptr, ie_len);
		priv->wpa_ie_len = ie_len;
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: Set Wpa_ie_len=%d IE=%#x\n",
			    priv->wpa_ie_len, priv->wpa_ie[0]);

		अगर (priv->wpa_ie[0] == WLAN_EID_VENDOR_SPECIFIC) अणु
			priv->sec_info.wpa_enabled = true;
		पूर्ण अन्यथा अगर (priv->wpa_ie[0] == WLAN_EID_RSN) अणु
			priv->sec_info.wpa2_enabled = true;
		पूर्ण अन्यथा अणु
			priv->sec_info.wpa_enabled = false;
			priv->sec_info.wpa2_enabled = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(priv->wpa_ie, 0, माप(priv->wpa_ie));
		priv->wpa_ie_len = 0;
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: reset wpa_ie_len=%d IE=%#x\n",
			    priv->wpa_ie_len, priv->wpa_ie[0]);
		priv->sec_info.wpa_enabled = false;
		priv->sec_info.wpa2_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * IOCTL request handler to set/reset WAPI IE.
 *
 * The supplied WAPI IE is treated as a opaque buffer. Only the first field
 * is checked to पूर्णांकernally enable WAPI. If buffer length is zero, the existing
 * WAPI IE is reset.
 */
अटल पूर्णांक mwअगरiex_set_wapi_ie(काष्ठा mwअगरiex_निजी *priv,
			       u8 *ie_data_ptr, u16 ie_len)
अणु
	अगर (ie_len) अणु
		अगर (ie_len > माप(priv->wapi_ie)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "info: failed to copy WAPI IE, too big\n");
			वापस -1;
		पूर्ण
		स_नकल(priv->wapi_ie, ie_data_ptr, ie_len);
		priv->wapi_ie_len = ie_len;
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: Set wapi_ie_len=%d IE=%#x\n",
			    priv->wapi_ie_len, priv->wapi_ie[0]);

		अगर (priv->wapi_ie[0] == WLAN_EID_BSS_AC_ACCESS_DELAY)
			priv->sec_info.wapi_enabled = true;
	पूर्ण अन्यथा अणु
		स_रखो(priv->wapi_ie, 0, माप(priv->wapi_ie));
		priv->wapi_ie_len = ie_len;
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: Reset wapi_ie_len=%d IE=%#x\n",
			    priv->wapi_ie_len, priv->wapi_ie[0]);
		priv->sec_info.wapi_enabled = false;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * IOCTL request handler to set/reset WPS IE.
 *
 * The supplied WPS IE is treated as a opaque buffer. Only the first field
 * is checked to पूर्णांकernally enable WPS. If buffer length is zero, the existing
 * WPS IE is reset.
 */
अटल पूर्णांक mwअगरiex_set_wps_ie(काष्ठा mwअगरiex_निजी *priv,
			       u8 *ie_data_ptr, u16 ie_len)
अणु
	अगर (ie_len) अणु
		अगर (ie_len > MWIFIEX_MAX_VSIE_LEN) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "info: failed to copy WPS IE, too big\n");
			वापस -1;
		पूर्ण

		priv->wps_ie = kzalloc(MWIFIEX_MAX_VSIE_LEN, GFP_KERNEL);
		अगर (!priv->wps_ie)
			वापस -ENOMEM;

		स_नकल(priv->wps_ie, ie_data_ptr, ie_len);
		priv->wps_ie_len = ie_len;
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: Set wps_ie_len=%d IE=%#x\n",
			    priv->wps_ie_len, priv->wps_ie[0]);
	पूर्ण अन्यथा अणु
		kमुक्त(priv->wps_ie);
		priv->wps_ie_len = ie_len;
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: Reset wps_ie_len=%d\n", priv->wps_ie_len);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * IOCTL request handler to set WAPI key.
 *
 * This function prepares the correct firmware command and
 * issues it.
 */
अटल पूर्णांक mwअगरiex_sec_ioctl_set_wapi_key(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा mwअगरiex_ds_encrypt_key *encrypt_key)
अणु

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				HostCmd_ACT_GEN_SET, KEY_INFO_ENABLED,
				encrypt_key, true);
पूर्ण

/*
 * IOCTL request handler to set WEP network key.
 *
 * This function prepares the correct firmware command and
 * issues it, after validation checks.
 */
अटल पूर्णांक mwअगरiex_sec_ioctl_set_wep_key(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ds_encrypt_key *encrypt_key)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret;
	काष्ठा mwअगरiex_wep_key *wep_key;
	पूर्णांक index;

	अगर (priv->wep_key_curr_index >= NUM_WEP_KEYS)
		priv->wep_key_curr_index = 0;
	wep_key = &priv->wep_key[priv->wep_key_curr_index];
	index = encrypt_key->key_index;
	अगर (encrypt_key->key_disable) अणु
		priv->sec_info.wep_enabled = 0;
	पूर्ण अन्यथा अगर (!encrypt_key->key_len) अणु
		/* Copy the required key as the current key */
		wep_key = &priv->wep_key[index];
		अगर (!wep_key->key_length) अणु
			mwअगरiex_dbg(adapter, ERROR,
				    "key not set, so cannot enable it\n");
			वापस -1;
		पूर्ण

		अगर (adapter->key_api_major_ver == KEY_API_VER_MAJOR_V2) अणु
			स_नकल(encrypt_key->key_material,
			       wep_key->key_material, wep_key->key_length);
			encrypt_key->key_len = wep_key->key_length;
		पूर्ण

		priv->wep_key_curr_index = (u16) index;
		priv->sec_info.wep_enabled = 1;
	पूर्ण अन्यथा अणु
		wep_key = &priv->wep_key[index];
		स_रखो(wep_key, 0, माप(काष्ठा mwअगरiex_wep_key));
		/* Copy the key in the driver */
		स_नकल(wep_key->key_material,
		       encrypt_key->key_material,
		       encrypt_key->key_len);
		wep_key->key_index = index;
		wep_key->key_length = encrypt_key->key_len;
		priv->sec_info.wep_enabled = 1;
	पूर्ण
	अगर (wep_key->key_length) अणु
		व्योम *enc_key;

		अगर (encrypt_key->key_disable) अणु
			स_रखो(&priv->wep_key[index], 0,
			       माप(काष्ठा mwअगरiex_wep_key));
			जाओ करोne;
		पूर्ण

		अगर (adapter->key_api_major_ver == KEY_API_VER_MAJOR_V2)
			enc_key = encrypt_key;
		अन्यथा
			enc_key = शून्य;

		/* Send request to firmware */
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				       HostCmd_ACT_GEN_SET, 0, enc_key, false);
		अगर (ret)
			वापस ret;
	पूर्ण

करोne:
	अगर (priv->sec_info.wep_enabled)
		priv->curr_pkt_filter |= HostCmd_ACT_MAC_WEP_ENABLE;
	अन्यथा
		priv->curr_pkt_filter &= ~HostCmd_ACT_MAC_WEP_ENABLE;

	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_MAC_CONTROL,
			       HostCmd_ACT_GEN_SET, 0,
			       &priv->curr_pkt_filter, true);

	वापस ret;
पूर्ण

/*
 * IOCTL request handler to set WPA key.
 *
 * This function prepares the correct firmware command and
 * issues it, after validation checks.
 *
 * Current driver only supports key length of up to 32 bytes.
 *
 * This function can also be used to disable a currently set key.
 */
अटल पूर्णांक mwअगरiex_sec_ioctl_set_wpa_key(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ds_encrypt_key *encrypt_key)
अणु
	पूर्णांक ret;
	u8 हटाओ_key = false;
	काष्ठा host_cmd_ds_802_11_key_material *ibss_key;

	/* Current driver only supports key length of up to 32 bytes */
	अगर (encrypt_key->key_len > WLAN_MAX_KEY_LEN) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "key length too long\n");
		वापस -1;
	पूर्ण

	अगर (priv->bss_mode == NL80211_IFTYPE_ADHOC) अणु
		/*
		 * IBSS/WPA-None uses only one key (Group) क्रम both receiving
		 * and sending unicast and multicast packets.
		 */
		/* Send the key as PTK to firmware */
		encrypt_key->key_index = MWIFIEX_KEY_INDEX_UNICAST;
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				       HostCmd_ACT_GEN_SET,
				       KEY_INFO_ENABLED, encrypt_key, false);
		अगर (ret)
			वापस ret;

		ibss_key = &priv->aes_key;
		स_रखो(ibss_key, 0,
		       माप(काष्ठा host_cmd_ds_802_11_key_material));
		/* Copy the key in the driver */
		स_नकल(ibss_key->key_param_set.key, encrypt_key->key_material,
		       encrypt_key->key_len);
		स_नकल(&ibss_key->key_param_set.key_len, &encrypt_key->key_len,
		       माप(ibss_key->key_param_set.key_len));
		ibss_key->key_param_set.key_type_id
			= cpu_to_le16(KEY_TYPE_ID_TKIP);
		ibss_key->key_param_set.key_info = cpu_to_le16(KEY_ENABLED);

		/* Send the key as GTK to firmware */
		encrypt_key->key_index = ~MWIFIEX_KEY_INDEX_UNICAST;
	पूर्ण

	अगर (!encrypt_key->key_index)
		encrypt_key->key_index = MWIFIEX_KEY_INDEX_UNICAST;

	अगर (हटाओ_key)
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				       HostCmd_ACT_GEN_SET,
				       !KEY_INFO_ENABLED, encrypt_key, true);
	अन्यथा
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_KEY_MATERIAL,
				       HostCmd_ACT_GEN_SET,
				       KEY_INFO_ENABLED, encrypt_key, true);

	वापस ret;
पूर्ण

/*
 * IOCTL request handler to set/get network keys.
 *
 * This is a generic key handling function which supports WEP, WPA
 * and WAPI.
 */
अटल पूर्णांक
mwअगरiex_sec_ioctl_encrypt_key(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ds_encrypt_key *encrypt_key)
अणु
	पूर्णांक status;

	अगर (encrypt_key->is_wapi_key)
		status = mwअगरiex_sec_ioctl_set_wapi_key(priv, encrypt_key);
	अन्यथा अगर (encrypt_key->key_len > WLAN_KEY_LEN_WEP104)
		status = mwअगरiex_sec_ioctl_set_wpa_key(priv, encrypt_key);
	अन्यथा
		status = mwअगरiex_sec_ioctl_set_wep_key(priv, encrypt_key);
	वापस status;
पूर्ण

/*
 * This function वापसs the driver version.
 */
पूर्णांक
mwअगरiex_drv_get_driver_version(काष्ठा mwअगरiex_adapter *adapter, अक्षर *version,
			       पूर्णांक max_len)
अणु
	जोड़ अणु
		__le32 l;
		u8 c[4];
	पूर्ण ver;
	अक्षर fw_ver[32];

	ver.l = cpu_to_le32(adapter->fw_release_number);
	प्र_लिखो(fw_ver, "%u.%u.%u.p%u", ver.c[2], ver.c[1], ver.c[0], ver.c[3]);

	snम_लिखो(version, max_len, driver_version, fw_ver);

	mwअगरiex_dbg(adapter, MSG, "info: MWIFIEX VERSION: %s\n", version);

	वापस 0;
पूर्ण

/*
 * Sends IOCTL request to set encoding parameters.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक mwअगरiex_set_encode(काष्ठा mwअगरiex_निजी *priv, काष्ठा key_params *kp,
		       स्थिर u8 *key, पूर्णांक key_len, u8 key_index,
		       स्थिर u8 *mac_addr, पूर्णांक disable)
अणु
	काष्ठा mwअगरiex_ds_encrypt_key encrypt_key;

	स_रखो(&encrypt_key, 0, माप(encrypt_key));
	encrypt_key.key_len = key_len;
	encrypt_key.key_index = key_index;

	अगर (kp && kp->cipher == WLAN_CIPHER_SUITE_AES_CMAC)
		encrypt_key.is_igtk_key = true;

	अगर (!disable) अणु
		अगर (key_len)
			स_नकल(encrypt_key.key_material, key, key_len);
		अन्यथा
			encrypt_key.is_current_wep_key = true;

		अगर (mac_addr)
			स_नकल(encrypt_key.mac_addr, mac_addr, ETH_ALEN);
		अगर (kp && kp->seq && kp->seq_len) अणु
			स_नकल(encrypt_key.pn, kp->seq, kp->seq_len);
			encrypt_key.pn_len = kp->seq_len;
			encrypt_key.is_rx_seq_valid = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		encrypt_key.key_disable = true;
		अगर (mac_addr)
			स_नकल(encrypt_key.mac_addr, mac_addr, ETH_ALEN);
	पूर्ण

	वापस mwअगरiex_sec_ioctl_encrypt_key(priv, &encrypt_key);
पूर्ण

/*
 * Sends IOCTL request to get extended version.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक
mwअगरiex_get_ver_ext(काष्ठा mwअगरiex_निजी *priv, u32 version_str_sel)
अणु
	काष्ठा mwअगरiex_ver_ext ver_ext;

	स_रखो(&ver_ext, 0, माप(ver_ext));
	ver_ext.version_str_sel = version_str_sel;
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_VERSION_EXT,
			     HostCmd_ACT_GEN_GET, 0, &ver_ext, true))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक
mwअगरiex_reमुख्य_on_chan_cfg(काष्ठा mwअगरiex_निजी *priv, u16 action,
			   काष्ठा ieee80211_channel *chan,
			   अचिन्हित पूर्णांक duration)
अणु
	काष्ठा host_cmd_ds_reमुख्य_on_chan roc_cfg;
	u8 sc;

	स_रखो(&roc_cfg, 0, माप(roc_cfg));
	roc_cfg.action = cpu_to_le16(action);
	अगर (action == HostCmd_ACT_GEN_SET) अणु
		roc_cfg.band_cfg = chan->band;
		sc = mwअगरiex_chan_type_to_sec_chan_offset(NL80211_CHAN_NO_HT);
		roc_cfg.band_cfg |= (sc << 2);

		roc_cfg.channel =
			ieee80211_frequency_to_channel(chan->center_freq);
		roc_cfg.duration = cpu_to_le32(duration);
	पूर्ण
	अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_REMAIN_ON_CHAN,
			     action, 0, &roc_cfg, true)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "failed to remain on channel\n");
		वापस -1;
	पूर्ण

	वापस roc_cfg.status;
पूर्ण

/*
 * Sends IOCTL request to get statistics inक्रमmation.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक
mwअगरiex_get_stats_info(काष्ठा mwअगरiex_निजी *priv,
		       काष्ठा mwअगरiex_ds_get_stats *log)
अणु
	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_GET_LOG,
				HostCmd_ACT_GEN_GET, 0, log, true);
पूर्ण

/*
 * IOCTL request handler to पढ़ो/ग_लिखो रेजिस्टर.
 *
 * This function prepares the correct firmware command and
 * issues it.
 *
 * Access to the following रेजिस्टरs are supported -
 *      - MAC
 *      - BBP
 *      - RF
 *      - PMIC
 *      - CAU
 */
अटल पूर्णांक mwअगरiex_reg_mem_ioctl_reg_rw(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा mwअगरiex_ds_reg_rw *reg_rw,
					u16 action)
अणु
	u16 cmd_no;

	चयन (reg_rw->type) अणु
	हाल MWIFIEX_REG_MAC:
		cmd_no = HostCmd_CMD_MAC_REG_ACCESS;
		अवरोध;
	हाल MWIFIEX_REG_BBP:
		cmd_no = HostCmd_CMD_BBP_REG_ACCESS;
		अवरोध;
	हाल MWIFIEX_REG_RF:
		cmd_no = HostCmd_CMD_RF_REG_ACCESS;
		अवरोध;
	हाल MWIFIEX_REG_PMIC:
		cmd_no = HostCmd_CMD_PMIC_REG_ACCESS;
		अवरोध;
	हाल MWIFIEX_REG_CAU:
		cmd_no = HostCmd_CMD_CAU_REG_ACCESS;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस mwअगरiex_send_cmd(priv, cmd_no, action, 0, reg_rw, true);
पूर्ण

/*
 * Sends IOCTL request to ग_लिखो to a रेजिस्टर.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक
mwअगरiex_reg_ग_लिखो(काष्ठा mwअगरiex_निजी *priv, u32 reg_type,
		  u32 reg_offset, u32 reg_value)
अणु
	काष्ठा mwअगरiex_ds_reg_rw reg_rw;

	reg_rw.type = reg_type;
	reg_rw.offset = reg_offset;
	reg_rw.value = reg_value;

	वापस mwअगरiex_reg_mem_ioctl_reg_rw(priv, &reg_rw, HostCmd_ACT_GEN_SET);
पूर्ण

/*
 * Sends IOCTL request to पढ़ो from a रेजिस्टर.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक
mwअगरiex_reg_पढ़ो(काष्ठा mwअगरiex_निजी *priv, u32 reg_type,
		 u32 reg_offset, u32 *value)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_ds_reg_rw reg_rw;

	reg_rw.type = reg_type;
	reg_rw.offset = reg_offset;
	ret = mwअगरiex_reg_mem_ioctl_reg_rw(priv, &reg_rw, HostCmd_ACT_GEN_GET);

	अगर (ret)
		जाओ करोne;

	*value = reg_rw.value;

करोne:
	वापस ret;
पूर्ण

/*
 * Sends IOCTL request to पढ़ो from EEPROM.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक
mwअगरiex_eeprom_पढ़ो(काष्ठा mwअगरiex_निजी *priv, u16 offset, u16 bytes,
		    u8 *value)
अणु
	पूर्णांक ret;
	काष्ठा mwअगरiex_ds_पढ़ो_eeprom rd_eeprom;

	rd_eeprom.offset =  offset;
	rd_eeprom.byte_count = bytes;

	/* Send request to firmware */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_EEPROM_ACCESS,
			       HostCmd_ACT_GEN_GET, 0, &rd_eeprom, true);

	अगर (!ret)
		स_नकल(value, rd_eeprom.value, min((u16)MAX_EEPROM_DATA,
		       rd_eeprom.byte_count));
	वापस ret;
पूर्ण

/*
 * This function sets a generic IE. In addition to generic IE, it can
 * also handle WPA, WPA2 and WAPI IEs.
 */
अटल पूर्णांक
mwअगरiex_set_gen_ie_helper(काष्ठा mwअगरiex_निजी *priv, u8 *ie_data_ptr,
			  u16 ie_len)
अणु
	काष्ठा ieee_types_venकरोr_header *pvenकरोr_ie;
	स्थिर u8 wpa_oui[] = अणु 0x00, 0x50, 0xf2, 0x01 पूर्ण;
	स्थिर u8 wps_oui[] = अणु 0x00, 0x50, 0xf2, 0x04 पूर्ण;
	u16 unparsed_len = ie_len, cur_ie_len;

	/* If the passed length is zero, reset the buffer */
	अगर (!ie_len) अणु
		priv->gen_ie_buf_len = 0;
		priv->wps.session_enable = false;
		वापस 0;
	पूर्ण अन्यथा अगर (!ie_data_ptr ||
		   ie_len <= माप(काष्ठा ieee_types_header)) अणु
		वापस -1;
	पूर्ण
	pvenकरोr_ie = (काष्ठा ieee_types_venकरोr_header *) ie_data_ptr;

	जबतक (pvenकरोr_ie) अणु
		cur_ie_len = pvenकरोr_ie->len + माप(काष्ठा ieee_types_header);

		अगर (pvenकरोr_ie->element_id == WLAN_EID_RSN) अणु
			/* IE is a WPA/WPA2 IE so call set_wpa function */
			mwअगरiex_set_wpa_ie(priv, (u8 *)pvenकरोr_ie, cur_ie_len);
			priv->wps.session_enable = false;
			जाओ next_ie;
		पूर्ण

		अगर (pvenकरोr_ie->element_id == WLAN_EID_BSS_AC_ACCESS_DELAY) अणु
			/* IE is a WAPI IE so call set_wapi function */
			mwअगरiex_set_wapi_ie(priv, (u8 *)pvenकरोr_ie,
					    cur_ie_len);
			जाओ next_ie;
		पूर्ण

		अगर (pvenकरोr_ie->element_id == WLAN_EID_VENDOR_SPECIFIC) अणु
			/* Test to see अगर it is a WPA IE, अगर not, then
			 * it is a gen IE
			 */
			अगर (!स_भेद(&pvenकरोr_ie->oui, wpa_oui,
				    माप(wpa_oui))) अणु
				/* IE is a WPA/WPA2 IE so call set_wpa function
				 */
				mwअगरiex_set_wpa_ie(priv, (u8 *)pvenकरोr_ie,
						   cur_ie_len);
				priv->wps.session_enable = false;
				जाओ next_ie;
			पूर्ण

			अगर (!स_भेद(&pvenकरोr_ie->oui, wps_oui,
				    माप(wps_oui))) अणु
				/* Test to see अगर it is a WPS IE,
				 * अगर so, enable wps session flag
				 */
				priv->wps.session_enable = true;
				mwअगरiex_dbg(priv->adapter, MSG,
					    "WPS Session Enabled.\n");
				mwअगरiex_set_wps_ie(priv, (u8 *)pvenकरोr_ie,
						   cur_ie_len);
				जाओ next_ie;
			पूर्ण
		पूर्ण

		/* Saved in gen_ie, such as P2P IE.etc.*/

		/* Verअगरy that the passed length is not larger than the
		 * available space reमुख्यing in the buffer
		 */
		अगर (cur_ie_len <
		    (माप(priv->gen_ie_buf) - priv->gen_ie_buf_len)) अणु
			/* Append the passed data to the end
			 * of the genIeBuffer
			 */
			स_नकल(priv->gen_ie_buf + priv->gen_ie_buf_len,
			       (u8 *)pvenकरोr_ie, cur_ie_len);
			/* Increment the stored buffer length by the
			 * size passed
			 */
			priv->gen_ie_buf_len += cur_ie_len;
		पूर्ण

next_ie:
		unparsed_len -= cur_ie_len;

		अगर (unparsed_len <= माप(काष्ठा ieee_types_header))
			pvenकरोr_ie = शून्य;
		अन्यथा
			pvenकरोr_ie = (काष्ठा ieee_types_venकरोr_header *)
				(((u8 *)pvenकरोr_ie) + cur_ie_len);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * IOCTL request handler to set/get generic IE.
 *
 * In addition to various generic IEs, this function can also be
 * used to set the ARP filter.
 */
अटल पूर्णांक mwअगरiex_misc_ioctl_gen_ie(काष्ठा mwअगरiex_निजी *priv,
				     काष्ठा mwअगरiex_ds_misc_gen_ie *gen_ie,
				     u16 action)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	चयन (gen_ie->type) अणु
	हाल MWIFIEX_IE_TYPE_GEN_IE:
		अगर (action == HostCmd_ACT_GEN_GET) अणु
			gen_ie->len = priv->wpa_ie_len;
			स_नकल(gen_ie->ie_data, priv->wpa_ie, gen_ie->len);
		पूर्ण अन्यथा अणु
			mwअगरiex_set_gen_ie_helper(priv, gen_ie->ie_data,
						  (u16) gen_ie->len);
		पूर्ण
		अवरोध;
	हाल MWIFIEX_IE_TYPE_ARP_FILTER:
		स_रखो(adapter->arp_filter, 0, माप(adapter->arp_filter));
		अगर (gen_ie->len > ARP_FILTER_MAX_BUF_SIZE) अणु
			adapter->arp_filter_size = 0;
			mwअगरiex_dbg(adapter, ERROR,
				    "invalid ARP filter size\n");
			वापस -1;
		पूर्ण अन्यथा अणु
			स_नकल(adapter->arp_filter, gen_ie->ie_data,
			       gen_ie->len);
			adapter->arp_filter_size = gen_ie->len;
		पूर्ण
		अवरोध;
	शेष:
		mwअगरiex_dbg(adapter, ERROR, "invalid IE type\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Sends IOCTL request to set a generic IE.
 *
 * This function allocates the IOCTL request buffer, fills it
 * with requisite parameters and calls the IOCTL handler.
 */
पूर्णांक
mwअगरiex_set_gen_ie(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ie, पूर्णांक ie_len)
अणु
	काष्ठा mwअगरiex_ds_misc_gen_ie gen_ie;

	अगर (ie_len > IEEE_MAX_IE_SIZE)
		वापस -EFAULT;

	gen_ie.type = MWIFIEX_IE_TYPE_GEN_IE;
	gen_ie.len = ie_len;
	स_नकल(gen_ie.ie_data, ie, ie_len);
	अगर (mwअगरiex_misc_ioctl_gen_ie(priv, &gen_ie, HostCmd_ACT_GEN_SET))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/* This function get Host Sleep wake up reason.
 *
 */
पूर्णांक mwअगरiex_get_wakeup_reason(काष्ठा mwअगरiex_निजी *priv, u16 action,
			      पूर्णांक cmd_type,
			      काष्ठा mwअगरiex_ds_wakeup_reason *wakeup_reason)
अणु
	पूर्णांक status = 0;

	status = mwअगरiex_send_cmd(priv, HostCmd_CMD_HS_WAKEUP_REASON,
				  HostCmd_ACT_GEN_GET, 0, wakeup_reason,
				  cmd_type == MWIFIEX_SYNC_CMD);

	वापस status;
पूर्ण

पूर्णांक mwअगरiex_get_chan_info(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा mwअगरiex_channel_band *channel_band)
अणु
	पूर्णांक status = 0;

	status = mwअगरiex_send_cmd(priv, HostCmd_CMD_STA_CONFIGURE,
				  HostCmd_ACT_GEN_GET, 0, channel_band,
				  MWIFIEX_SYNC_CMD);

	वापस status;
पूर्ण
