<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <linux/ieee80211.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/tcp.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>

#समावेश "iwl-trans.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "mvm.h"
#समावेश "sta.h"

अटल व्योम
iwl_mvm_bar_check_trigger(काष्ठा iwl_mvm *mvm, स्थिर u8 *addr,
			  u16 tid, u16 ssn)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_ba *ba_trig;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, शून्य, FW_DBG_TRIGGER_BA);
	अगर (!trig)
		वापस;

	ba_trig = (व्योम *)trig->data;

	अगर (!(le16_to_cpu(ba_trig->tx_bar) & BIT(tid)))
		वापस;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
				"BAR sent to %pM, tid %d, ssn %d",
				addr, tid, ssn);
पूर्ण

#घोषणा OPT_HDR(type, skb, off) \
	(type *)(skb_network_header(skb) + (off))

अटल u16 iwl_mvm_tx_csum(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_hdr *hdr,
			   काष्ठा ieee80211_tx_info *info,
			   u16 offload_assist)
अणु
#अगर IS_ENABLED(CONFIG_INET)
	u16 mh_len = ieee80211_hdrlen(hdr->frame_control);
	u8 protocol = 0;

	/* Do not compute checksum अगर alपढ़ोy computed */
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		जाओ out;

	/* We करो not expect to be requested to csum stuff we करो not support */
	अगर (WARN_ONCE(!(mvm->hw->netdev_features & IWL_TX_CSUM_NETIF_FLAGS) ||
		      (skb->protocol != htons(ETH_P_IP) &&
		       skb->protocol != htons(ETH_P_IPV6)),
		      "No support for requested checksum\n")) अणु
		skb_checksum_help(skb);
		जाओ out;
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		protocol = ip_hdr(skb)->protocol;
	पूर्ण अन्यथा अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		काष्ठा ipv6hdr *ipv6h =
			(काष्ठा ipv6hdr *)skb_network_header(skb);
		अचिन्हित पूर्णांक off = माप(*ipv6h);

		protocol = ipv6h->nexthdr;
		जबतक (protocol != NEXTHDR_NONE && ipv6_ext_hdr(protocol)) अणु
			काष्ठा ipv6_opt_hdr *hp;

			/* only supported extension headers */
			अगर (protocol != NEXTHDR_ROUTING &&
			    protocol != NEXTHDR_HOP &&
			    protocol != NEXTHDR_DEST) अणु
				skb_checksum_help(skb);
				जाओ out;
			पूर्ण

			hp = OPT_HDR(काष्ठा ipv6_opt_hdr, skb, off);
			protocol = hp->nexthdr;
			off += ipv6_optlen(hp);
		पूर्ण
		/* अगर we get here - protocol now should be TCP/UDP */
#पूर्ण_अगर
	पूर्ण

	अगर (protocol != IPPROTO_TCP && protocol != IPPROTO_UDP) अणु
		WARN_ON_ONCE(1);
		skb_checksum_help(skb);
		जाओ out;
	पूर्ण

	/* enable L4 csum */
	offload_assist |= BIT(TX_CMD_OFFLD_L4_EN);

	/*
	 * Set offset to IP header (snap).
	 * We करोn't support tunneling so no need to take care of inner header.
	 * Size is in words.
	 */
	offload_assist |= (4 << TX_CMD_OFFLD_IP_HDR);

	/* Do IPv4 csum क्रम AMSDU only (no IP csum क्रम Ipv6) */
	अगर (skb->protocol == htons(ETH_P_IP) &&
	    (offload_assist & BIT(TX_CMD_OFFLD_AMSDU))) अणु
		ip_hdr(skb)->check = 0;
		offload_assist |= BIT(TX_CMD_OFFLD_L3_EN);
	पूर्ण

	/* reset UDP/TCP header csum */
	अगर (protocol == IPPROTO_TCP)
		tcp_hdr(skb)->check = 0;
	अन्यथा
		udp_hdr(skb)->check = 0;

	/*
	 * mac header len should include IV, size is in words unless
	 * the IV is added by the firmware like in WEP.
	 * In new Tx API, the IV is always added by the firmware.
	 */
	अगर (!iwl_mvm_has_new_tx_api(mvm) && info->control.hw_key &&
	    info->control.hw_key->cipher != WLAN_CIPHER_SUITE_WEP40 &&
	    info->control.hw_key->cipher != WLAN_CIPHER_SUITE_WEP104)
		mh_len += info->control.hw_key->iv_len;
	mh_len /= 2;
	offload_assist |= mh_len << TX_CMD_OFFLD_MH_SIZE;

out:
#पूर्ण_अगर
	वापस offload_assist;
पूर्ण

/*
 * Sets most of the Tx cmd's fields
 */
व्योम iwl_mvm_set_tx_cmd(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			काष्ठा iwl_tx_cmd *tx_cmd,
			काष्ठा ieee80211_tx_info *info, u8 sta_id)
अणु
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	__le16 fc = hdr->frame_control;
	u32 tx_flags = le32_to_cpu(tx_cmd->tx_flags);
	u32 len = skb->len + FCS_LEN;
	u16 offload_assist = 0;
	u8 ac;

	अगर (!(info->flags & IEEE80211_TX_CTL_NO_ACK) ||
	    (ieee80211_is_probe_resp(fc) &&
	     !is_multicast_ether_addr(hdr->addr1)))
		tx_flags |= TX_CMD_FLG_ACK;
	अन्यथा
		tx_flags &= ~TX_CMD_FLG_ACK;

	अगर (ieee80211_is_probe_resp(fc))
		tx_flags |= TX_CMD_FLG_TSF;

	अगर (ieee80211_has_morefrags(fc))
		tx_flags |= TX_CMD_FLG_MORE_FRAG;

	अगर (ieee80211_is_data_qos(fc)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tx_cmd->tid_tspec = qc[0] & 0xf;
		tx_flags &= ~TX_CMD_FLG_SEQ_CTL;
		अगर (*qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			offload_assist |= BIT(TX_CMD_OFFLD_AMSDU);
	पूर्ण अन्यथा अगर (ieee80211_is_back_req(fc)) अणु
		काष्ठा ieee80211_bar *bar = (व्योम *)skb->data;
		u16 control = le16_to_cpu(bar->control);
		u16 ssn = le16_to_cpu(bar->start_seq_num);

		tx_flags |= TX_CMD_FLG_ACK | TX_CMD_FLG_BAR;
		tx_cmd->tid_tspec = (control &
				     IEEE80211_BAR_CTRL_TID_INFO_MASK) >>
			IEEE80211_BAR_CTRL_TID_INFO_SHIFT;
		WARN_ON_ONCE(tx_cmd->tid_tspec >= IWL_MAX_TID_COUNT);
		iwl_mvm_bar_check_trigger(mvm, bar->ra, tx_cmd->tid_tspec,
					  ssn);
	पूर्ण अन्यथा अणु
		अगर (ieee80211_is_data(fc))
			tx_cmd->tid_tspec = IWL_TID_NON_QOS;
		अन्यथा
			tx_cmd->tid_tspec = IWL_MAX_TID_COUNT;

		अगर (info->flags & IEEE80211_TX_CTL_ASSIGN_SEQ)
			tx_flags |= TX_CMD_FLG_SEQ_CTL;
		अन्यथा
			tx_flags &= ~TX_CMD_FLG_SEQ_CTL;
	पूर्ण

	/* Default to 0 (BE) when tid_spec is set to IWL_MAX_TID_COUNT */
	अगर (tx_cmd->tid_tspec < IWL_MAX_TID_COUNT)
		ac = tid_to_mac80211_ac[tx_cmd->tid_tspec];
	अन्यथा
		ac = tid_to_mac80211_ac[0];

	tx_flags |= iwl_mvm_bt_coex_tx_prio(mvm, hdr, info, ac) <<
			TX_CMD_FLG_BT_PRIO_POS;

	अगर (ieee80211_is_mgmt(fc)) अणु
		अगर (ieee80211_is_assoc_req(fc) || ieee80211_is_reassoc_req(fc))
			tx_cmd->pm_frame_समयout = cpu_to_le16(PM_FRAME_ASSOC);
		अन्यथा अगर (ieee80211_is_action(fc))
			tx_cmd->pm_frame_समयout = cpu_to_le16(PM_FRAME_NONE);
		अन्यथा
			tx_cmd->pm_frame_समयout = cpu_to_le16(PM_FRAME_MGMT);

		/* The spec allows Action frames in A-MPDU, we करोn't support
		 * it
		 */
		WARN_ON_ONCE(info->flags & IEEE80211_TX_CTL_AMPDU);
	पूर्ण अन्यथा अगर (info->control.flags & IEEE80211_TX_CTRL_PORT_CTRL_PROTO) अणु
		tx_cmd->pm_frame_समयout = cpu_to_le16(PM_FRAME_MGMT);
	पूर्ण अन्यथा अणु
		tx_cmd->pm_frame_समयout = cpu_to_le16(PM_FRAME_NONE);
	पूर्ण

	अगर (ieee80211_is_data(fc) && len > mvm->rts_threshold &&
	    !is_multicast_ether_addr(hdr->addr1))
		tx_flags |= TX_CMD_FLG_PROT_REQUIRE;

	अगर (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TXPOWER_INSERTION_SUPPORT) &&
	    ieee80211_action_contains_tpc(skb))
		tx_flags |= TX_CMD_FLG_WRITE_TX_POWER;

	tx_cmd->tx_flags = cpu_to_le32(tx_flags);
	/* Total # bytes to be transmitted - PCIe code will adjust क्रम A-MSDU */
	tx_cmd->len = cpu_to_le16((u16)skb->len);
	tx_cmd->lअगरe_समय = cpu_to_le32(TX_CMD_LIFE_TIME_INFINITE);
	tx_cmd->sta_id = sta_id;

	/* padding is inserted later in transport */
	अगर (ieee80211_hdrlen(fc) % 4 &&
	    !(offload_assist & BIT(TX_CMD_OFFLD_AMSDU)))
		offload_assist |= BIT(TX_CMD_OFFLD_PAD);

	tx_cmd->offload_assist |=
		cpu_to_le16(iwl_mvm_tx_csum(mvm, skb, hdr, info,
					    offload_assist));
पूर्ण

अटल u32 iwl_mvm_get_tx_ant(काष्ठा iwl_mvm *mvm,
			      काष्ठा ieee80211_tx_info *info,
			      काष्ठा ieee80211_sta *sta, __le16 fc)
अणु
	अगर (info->band == NL80211_BAND_2GHZ &&
	    !iwl_mvm_bt_coex_is_shared_ant_avail(mvm))
		वापस mvm->cfg->non_shared_ant << RATE_MCS_ANT_POS;

	अगर (sta && ieee80211_is_data(fc)) अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

		वापस BIT(mvmsta->tx_ant) << RATE_MCS_ANT_POS;
	पूर्ण

	वापस BIT(mvm->mgmt_last_antenna_idx) << RATE_MCS_ANT_POS;
पूर्ण

अटल u32 iwl_mvm_get_tx_rate(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_tx_info *info,
			       काष्ठा ieee80211_sta *sta, __le16 fc)
अणु
	पूर्णांक rate_idx = -1;
	u8 rate_plcp;
	u32 rate_flags = 0;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	/* info->control is only relevant क्रम non HW rate control */
	अगर (!ieee80211_hw_check(mvm->hw, HAS_RATE_CONTROL)) अणु
		/* HT rate करोesn't make sense क्रम a non data frame */
		WARN_ONCE(info->control.rates[0].flags & IEEE80211_TX_RC_MCS &&
			  !ieee80211_is_data(fc),
			  "Got a HT rate (flags:0x%x/mcs:%d/fc:0x%x/state:%d) for a non data frame\n",
			  info->control.rates[0].flags,
			  info->control.rates[0].idx,
			  le16_to_cpu(fc), mvmsta->sta_state);

		rate_idx = info->control.rates[0].idx;
	पूर्ण

	/* अगर the rate isn't a well known legacy rate, take the lowest one */
	अगर (rate_idx < 0 || rate_idx >= IWL_RATE_COUNT_LEGACY)
		rate_idx = rate_lowest_index(
				&mvm->nvm_data->bands[info->band], sta);

	/*
	 * For non 2 GHZ band, remap mac80211 rate
	 * indices पूर्णांकo driver indices
	 */
	अगर (info->band != NL80211_BAND_2GHZ)
		rate_idx += IWL_FIRST_OFDM_RATE;

	/* For 2.4 GHZ band, check that there is no need to remap */
	BUILD_BUG_ON(IWL_FIRST_CCK_RATE != 0);

	/* Get PLCP rate क्रम tx_cmd->rate_n_flags */
	rate_plcp = iwl_mvm_mac80211_idx_to_hwrate(rate_idx);

	/* Set CCK flag as needed */
	अगर ((rate_idx >= IWL_FIRST_CCK_RATE) && (rate_idx <= IWL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;

	वापस (u32)rate_plcp | rate_flags;
पूर्ण

अटल u32 iwl_mvm_get_tx_rate_n_flags(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_tx_info *info,
				       काष्ठा ieee80211_sta *sta, __le16 fc)
अणु
	वापस iwl_mvm_get_tx_rate(mvm, info, sta, fc) |
		iwl_mvm_get_tx_ant(mvm, info, sta, fc);
पूर्ण

/*
 * Sets the fields in the Tx cmd that are rate related
 */
व्योम iwl_mvm_set_tx_cmd_rate(काष्ठा iwl_mvm *mvm, काष्ठा iwl_tx_cmd *tx_cmd,
			    काष्ठा ieee80211_tx_info *info,
			    काष्ठा ieee80211_sta *sta, __le16 fc)
अणु
	/* Set retry limit on RTS packets */
	tx_cmd->rts_retry_limit = IWL_RTS_DFAULT_RETRY_LIMIT;

	/* Set retry limit on DATA packets and Probe Responses*/
	अगर (ieee80211_is_probe_resp(fc)) अणु
		tx_cmd->data_retry_limit = IWL_MGMT_DFAULT_RETRY_LIMIT;
		tx_cmd->rts_retry_limit =
			min(tx_cmd->data_retry_limit, tx_cmd->rts_retry_limit);
	पूर्ण अन्यथा अगर (ieee80211_is_back_req(fc)) अणु
		tx_cmd->data_retry_limit = IWL_BAR_DFAULT_RETRY_LIMIT;
	पूर्ण अन्यथा अणु
		tx_cmd->data_retry_limit = IWL_DEFAULT_TX_RETRY;
	पूर्ण

	/*
	 * क्रम data packets, rate info comes from the table inside the fw. This
	 * table is controlled by LINK_QUALITY commands
	 */

	अगर (ieee80211_is_data(fc) && sta) अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

		अगर (mvmsta->sta_state >= IEEE80211_STA_AUTHORIZED) अणु
			tx_cmd->initial_rate_index = 0;
			tx_cmd->tx_flags |= cpu_to_le32(TX_CMD_FLG_STA_RATE);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (ieee80211_is_back_req(fc)) अणु
		tx_cmd->tx_flags |=
			cpu_to_le32(TX_CMD_FLG_ACK | TX_CMD_FLG_BAR);
	पूर्ण

	/* Set the rate in the TX cmd */
	tx_cmd->rate_n_flags =
		cpu_to_le32(iwl_mvm_get_tx_rate_n_flags(mvm, info, sta, fc));
पूर्ण

अटल अंतरभूत व्योम iwl_mvm_set_tx_cmd_pn(काष्ठा ieee80211_tx_info *info,
					 u8 *crypto_hdr)
अणु
	काष्ठा ieee80211_key_conf *keyconf = info->control.hw_key;
	u64 pn;

	pn = atomic64_inc_वापस(&keyconf->tx_pn);
	crypto_hdr[0] = pn;
	crypto_hdr[2] = 0;
	crypto_hdr[3] = 0x20 | (keyconf->keyidx << 6);
	crypto_hdr[1] = pn >> 8;
	crypto_hdr[4] = pn >> 16;
	crypto_hdr[5] = pn >> 24;
	crypto_hdr[6] = pn >> 32;
	crypto_hdr[7] = pn >> 40;
पूर्ण

/*
 * Sets the fields in the Tx cmd that are crypto related
 */
अटल व्योम iwl_mvm_set_tx_cmd_crypto(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_tx_info *info,
				      काष्ठा iwl_tx_cmd *tx_cmd,
				      काष्ठा sk_buff *skb_frag,
				      पूर्णांक hdrlen)
अणु
	काष्ठा ieee80211_key_conf *keyconf = info->control.hw_key;
	u8 *crypto_hdr = skb_frag->data + hdrlen;
	क्रमागत iwl_tx_cmd_sec_ctrl type = TX_CMD_SEC_CCM;
	u64 pn;

	चयन (keyconf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		iwl_mvm_set_tx_cmd_ccmp(info, tx_cmd);
		iwl_mvm_set_tx_cmd_pn(info, crypto_hdr);
		अवरोध;

	हाल WLAN_CIPHER_SUITE_TKIP:
		tx_cmd->sec_ctl = TX_CMD_SEC_TKIP;
		pn = atomic64_inc_वापस(&keyconf->tx_pn);
		ieee80211_tkip_add_iv(crypto_hdr, keyconf, pn);
		ieee80211_get_tkip_p2k(keyconf, skb_frag, tx_cmd->key);
		अवरोध;

	हाल WLAN_CIPHER_SUITE_WEP104:
		tx_cmd->sec_ctl |= TX_CMD_SEC_KEY128;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_WEP40:
		tx_cmd->sec_ctl |= TX_CMD_SEC_WEP |
			((keyconf->keyidx << TX_CMD_SEC_WEP_KEY_IDX_POS) &
			  TX_CMD_SEC_WEP_KEY_IDX_MSK);

		स_नकल(&tx_cmd->key[3], keyconf->key, keyconf->keylen);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		type = TX_CMD_SEC_GCMP;
		fallthrough;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		/* TODO: Taking the key from the table might पूर्णांकroduce a race
		 * when PTK rekeying is करोne, having an old packets with a PN
		 * based on the old key but the message encrypted with a new
		 * one.
		 * Need to handle this.
		 */
		tx_cmd->sec_ctl |= type | TX_CMD_SEC_KEY_FROM_TABLE;
		tx_cmd->key[0] = keyconf->hw_key_idx;
		iwl_mvm_set_tx_cmd_pn(info, crypto_hdr);
		अवरोध;
	शेष:
		tx_cmd->sec_ctl |= TX_CMD_SEC_EXT;
	पूर्ण
पूर्ण

/*
 * Allocates and sets the Tx cmd the driver data poपूर्णांकers in the skb
 */
अटल काष्ठा iwl_device_tx_cmd *
iwl_mvm_set_tx_params(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
		      काष्ठा ieee80211_tx_info *info, पूर्णांक hdrlen,
		      काष्ठा ieee80211_sta *sta, u8 sta_id)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा iwl_device_tx_cmd *dev_cmd;
	काष्ठा iwl_tx_cmd *tx_cmd;

	dev_cmd = iwl_trans_alloc_tx_cmd(mvm->trans);

	अगर (unlikely(!dev_cmd))
		वापस शून्य;

	dev_cmd->hdr.cmd = TX_CMD;

	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		u16 offload_assist = 0;
		u32 rate_n_flags = 0;
		u16 flags = 0;
		काष्ठा iwl_mvm_sta *mvmsta = sta ?
			iwl_mvm_sta_from_mac80211(sta) : शून्य;

		अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
			u8 *qc = ieee80211_get_qos_ctl(hdr);

			अगर (*qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
				offload_assist |= BIT(TX_CMD_OFFLD_AMSDU);
		पूर्ण

		offload_assist = iwl_mvm_tx_csum(mvm, skb, hdr, info,
						 offload_assist);

		/* padding is inserted later in transport */
		अगर (ieee80211_hdrlen(hdr->frame_control) % 4 &&
		    !(offload_assist & BIT(TX_CMD_OFFLD_AMSDU)))
			offload_assist |= BIT(TX_CMD_OFFLD_PAD);

		अगर (!info->control.hw_key)
			flags |= IWL_TX_FLAGS_ENCRYPT_DIS;

		/*
		 * For data packets rate info comes from the fw. Only
		 * set rate/antenna during connection establishment or in हाल
		 * no station is given.
		 */
		अगर (!sta || !ieee80211_is_data(hdr->frame_control) ||
		    mvmsta->sta_state < IEEE80211_STA_AUTHORIZED) अणु
			flags |= IWL_TX_FLAGS_CMD_RATE;
			rate_n_flags =
				iwl_mvm_get_tx_rate_n_flags(mvm, info, sta,
							    hdr->frame_control);
		पूर्ण

		अगर (mvm->trans->trans_cfg->device_family >=
		    IWL_DEVICE_FAMILY_AX210) अणु
			काष्ठा iwl_tx_cmd_gen3 *cmd = (व्योम *)dev_cmd->payload;

			cmd->offload_assist |= cpu_to_le32(offload_assist);

			/* Total # bytes to be transmitted */
			cmd->len = cpu_to_le16((u16)skb->len);

			/* Copy MAC header from skb पूर्णांकo command buffer */
			स_नकल(cmd->hdr, hdr, hdrlen);

			cmd->flags = cpu_to_le16(flags);
			cmd->rate_n_flags = cpu_to_le32(rate_n_flags);
		पूर्ण अन्यथा अणु
			काष्ठा iwl_tx_cmd_gen2 *cmd = (व्योम *)dev_cmd->payload;

			cmd->offload_assist |= cpu_to_le16(offload_assist);

			/* Total # bytes to be transmitted */
			cmd->len = cpu_to_le16((u16)skb->len);

			/* Copy MAC header from skb पूर्णांकo command buffer */
			स_नकल(cmd->hdr, hdr, hdrlen);

			cmd->flags = cpu_to_le32(flags);
			cmd->rate_n_flags = cpu_to_le32(rate_n_flags);
		पूर्ण
		जाओ out;
	पूर्ण

	tx_cmd = (काष्ठा iwl_tx_cmd *)dev_cmd->payload;

	अगर (info->control.hw_key)
		iwl_mvm_set_tx_cmd_crypto(mvm, info, tx_cmd, skb, hdrlen);

	iwl_mvm_set_tx_cmd(mvm, skb, tx_cmd, info, sta_id);

	iwl_mvm_set_tx_cmd_rate(mvm, tx_cmd, info, sta, hdr->frame_control);

	/* Copy MAC header from skb पूर्णांकo command buffer */
	स_नकल(tx_cmd->hdr, hdr, hdrlen);

out:
	वापस dev_cmd;
पूर्ण

अटल व्योम iwl_mvm_skb_prepare_status(काष्ठा sk_buff *skb,
				       काष्ठा iwl_device_tx_cmd *cmd)
अणु
	काष्ठा ieee80211_tx_info *skb_info = IEEE80211_SKB_CB(skb);

	स_रखो(&skb_info->status, 0, माप(skb_info->status));
	स_रखो(skb_info->driver_data, 0, माप(skb_info->driver_data));

	skb_info->driver_data[1] = cmd;
पूर्ण

अटल पूर्णांक iwl_mvm_get_ctrl_vअगर_queue(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_tx_info *info,
				      काष्ठा ieee80211_hdr *hdr)
अणु
	काष्ठा iwl_mvm_vअगर *mvmvअगर =
		iwl_mvm_vअगर_from_mac80211(info->control.vअगर);
	__le16 fc = hdr->frame_control;

	चयन (info->control.vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
		/*
		 * Non-bufferable frames use the broadcast station, thus they
		 * use the probe queue.
		 * Also take care of the हाल where we send a deauth to a
		 * station that we करोn't have, or similarly an association
		 * response (with non-success status) क्रम a station we can't
		 * accept.
		 * Also, disassociate frames might happen, particular with
		 * reason 7 ("Class 3 frame received from nonassociated STA").
		 */
		अगर (ieee80211_is_mgmt(fc) &&
		    (!ieee80211_is_bufferable_mmpdu(fc) ||
		     ieee80211_is_deauth(fc) || ieee80211_is_disassoc(fc)))
			वापस mvm->probe_queue;

		अगर (!ieee80211_has_order(fc) && !ieee80211_is_probe_req(fc) &&
		    is_multicast_ether_addr(hdr->addr1))
			वापस mvmvअगर->cab_queue;

		WARN_ONCE(info->control.vअगर->type != NL80211_IFTYPE_ADHOC,
			  "fc=0x%02x", le16_to_cpu(fc));
		वापस mvm->probe_queue;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		अगर (ieee80211_is_mgmt(fc))
			वापस mvm->p2p_dev_queue;

		WARN_ON_ONCE(1);
		वापस mvm->p2p_dev_queue;
	शेष:
		WARN_ONCE(1, "Not a ctrl vif, no available queue\n");
		वापस -1;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_probe_resp_set_noa(काष्ठा iwl_mvm *mvm,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा iwl_mvm_vअगर *mvmvअगर =
		iwl_mvm_vअगर_from_mac80211(info->control.vअगर);
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	पूर्णांक base_len = (u8 *)mgmt->u.probe_resp.variable - (u8 *)mgmt;
	काष्ठा iwl_probe_resp_data *resp_data;
	u8 *ie, *pos;
	u8 match[] = अणु
		(WLAN_OUI_WFA >> 16) & 0xff,
		(WLAN_OUI_WFA >> 8) & 0xff,
		WLAN_OUI_WFA & 0xff,
		WLAN_OUI_TYPE_WFA_P2P,
	पूर्ण;

	rcu_पढ़ो_lock();

	resp_data = rcu_dereference(mvmvअगर->probe_resp_data);
	अगर (!resp_data)
		जाओ out;

	अगर (!resp_data->notअगर.noa_active)
		जाओ out;

	ie = (u8 *)cfg80211_find_ie_match(WLAN_EID_VENDOR_SPECIFIC,
					  mgmt->u.probe_resp.variable,
					  skb->len - base_len,
					  match, 4, 2);
	अगर (!ie) अणु
		IWL_DEBUG_TX(mvm, "probe resp doesn't have P2P IE\n");
		जाओ out;
	पूर्ण

	अगर (skb_tailroom(skb) < resp_data->noa_len) अणु
		अगर (pskb_expand_head(skb, 0, resp_data->noa_len, GFP_ATOMIC)) अणु
			IWL_ERR(mvm,
				"Failed to reallocate probe resp\n");
			जाओ out;
		पूर्ण
	पूर्ण

	pos = skb_put(skb, resp_data->noa_len);

	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	/* Set length of IE body (not including ID and length itself) */
	*pos++ = resp_data->noa_len - 2;
	*pos++ = (WLAN_OUI_WFA >> 16) & 0xff;
	*pos++ = (WLAN_OUI_WFA >> 8) & 0xff;
	*pos++ = WLAN_OUI_WFA & 0xff;
	*pos++ = WLAN_OUI_TYPE_WFA_P2P;

	स_नकल(pos, &resp_data->notअगर.noa_attr,
	       resp_data->noa_len - माप(काष्ठा ieee80211_venकरोr_ie));

out:
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक iwl_mvm_tx_skb_non_sta(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info info;
	काष्ठा iwl_device_tx_cmd *dev_cmd;
	u8 sta_id;
	पूर्णांक hdrlen = ieee80211_hdrlen(hdr->frame_control);
	__le16 fc = hdr->frame_control;
	bool offchannel = IEEE80211_SKB_CB(skb)->flags &
		IEEE80211_TX_CTL_TX_OFFCHAN;
	पूर्णांक queue = -1;

	अगर (IWL_MVM_NON_TRANSMITTING_AP && ieee80211_is_probe_resp(fc))
		वापस -1;

	स_नकल(&info, skb->cb, माप(info));

	अगर (WARN_ON_ONCE(skb->len > IEEE80211_MAX_DATA_LEN + hdrlen))
		वापस -1;

	अगर (WARN_ON_ONCE(info.flags & IEEE80211_TX_CTL_AMPDU))
		वापस -1;

	अगर (info.control.vअगर) अणु
		काष्ठा iwl_mvm_vअगर *mvmvअगर =
			iwl_mvm_vअगर_from_mac80211(info.control.vअगर);

		अगर (info.control.vअगर->type == NL80211_IFTYPE_P2P_DEVICE ||
		    info.control.vअगर->type == NL80211_IFTYPE_AP ||
		    info.control.vअगर->type == NL80211_IFTYPE_ADHOC) अणु
			अगर (!ieee80211_is_data(hdr->frame_control))
				sta_id = mvmvअगर->bcast_sta.sta_id;
			अन्यथा
				sta_id = mvmvअगर->mcast_sta.sta_id;

			queue = iwl_mvm_get_ctrl_vअगर_queue(mvm, &info, hdr);
		पूर्ण अन्यथा अगर (info.control.vअगर->type == NL80211_IFTYPE_MONITOR) अणु
			queue = mvm->snअगर_queue;
			sta_id = mvm->snअगर_sta.sta_id;
		पूर्ण अन्यथा अगर (info.control.vअगर->type == NL80211_IFTYPE_STATION &&
			   offchannel) अणु
			/*
			 * IWL_MVM_OFFCHANNEL_QUEUE is used क्रम ROC packets
			 * that can be used in 2 dअगरferent types of vअगरs, P2P &
			 * STATION.
			 * P2P uses the offchannel queue.
			 * STATION (HS2.0) uses the auxiliary context of the FW,
			 * and hence needs to be sent on the aux queue.
			 */
			sta_id = mvm->aux_sta.sta_id;
			queue = mvm->aux_queue;
		पूर्ण
	पूर्ण

	अगर (queue < 0) अणु
		IWL_ERR(mvm, "No queue was found. Dropping TX\n");
		वापस -1;
	पूर्ण

	अगर (unlikely(ieee80211_is_probe_resp(fc)))
		iwl_mvm_probe_resp_set_noa(mvm, skb);

	IWL_DEBUG_TX(mvm, "station Id %d, queue=%d\n", sta_id, queue);

	dev_cmd = iwl_mvm_set_tx_params(mvm, skb, &info, hdrlen, शून्य, sta_id);
	अगर (!dev_cmd)
		वापस -1;

	/* From now on, we cannot access info->control */
	iwl_mvm_skb_prepare_status(skb, dev_cmd);

	अगर (iwl_trans_tx(mvm->trans, skb, dev_cmd, queue)) अणु
		iwl_trans_मुक्त_tx_cmd(mvm->trans, dev_cmd);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक iwl_mvm_max_amsdu_size(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_sta *sta, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	क्रमागत nl80211_band band = mvmsta->vअगर->bss_conf.chandef.chan->band;
	u8 ac = tid_to_mac80211_ac[tid];
	अचिन्हित पूर्णांक txf;
	पूर्णांक lmac = iwl_mvm_get_lmac_id(mvm->fw, band);

	/* For HE redirect to trigger based fअगरos */
	अगर (sta->he_cap.has_he && !WARN_ON(!iwl_mvm_has_new_tx_api(mvm)))
		ac += 4;

	txf = iwl_mvm_mac_ac_to_tx_fअगरo(mvm, ac);

	/*
	 * Don't send an AMSDU that will be दीर्घer than the TXF.
	 * Add a security margin of 256 क्रम the TX command + headers.
	 * We also want to have the start of the next packet inside the
	 * fअगरo to be able to send bursts.
	 */
	वापस min_t(अचिन्हित पूर्णांक, mvmsta->max_amsdu_len,
		     mvm->fwrt.smem_cfg.lmac[lmac].txfअगरo_size[txf] - 256);
पूर्ण

#अगर_घोषित CONFIG_INET

अटल पूर्णांक
iwl_mvm_tx_tso_segment(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक num_subframes,
		       netdev_features_t netdev_flags,
		       काष्ठा sk_buff_head *mpdus_skb)
अणु
	काष्ठा sk_buff *पंचांगp, *next;
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	अक्षर cb[माप(skb->cb)];
	u16 i = 0;
	अचिन्हित पूर्णांक tcp_payload_len;
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;
	bool ipv4 = (skb->protocol == htons(ETH_P_IP));
	bool qos = ieee80211_is_data_qos(hdr->frame_control);
	u16 ip_base_id = ipv4 ? ntohs(ip_hdr(skb)->id) : 0;

	skb_shinfo(skb)->gso_size = num_subframes * mss;
	स_नकल(cb, skb->cb, माप(cb));

	next = skb_gso_segment(skb, netdev_flags);
	skb_shinfo(skb)->gso_size = mss;
	skb_shinfo(skb)->gso_type = ipv4 ? SKB_GSO_TCPV4 : SKB_GSO_TCPV6;
	अगर (WARN_ON_ONCE(IS_ERR(next)))
		वापस -EINVAL;
	अन्यथा अगर (next)
		consume_skb(skb);

	skb_list_walk_safe(next, पंचांगp, next) अणु
		स_नकल(पंचांगp->cb, cb, माप(पंचांगp->cb));
		/*
		 * Compute the length of all the data added क्रम the A-MSDU.
		 * This will be used to compute the length to ग_लिखो in the TX
		 * command. We have: SNAP + IP + TCP क्रम n -1 subframes and
		 * ETH header क्रम n subframes.
		 */
		tcp_payload_len = skb_tail_poपूर्णांकer(पंचांगp) -
			skb_transport_header(पंचांगp) -
			tcp_hdrlen(पंचांगp) + पंचांगp->data_len;

		अगर (ipv4)
			ip_hdr(पंचांगp)->id = htons(ip_base_id + i * num_subframes);

		अगर (tcp_payload_len > mss) अणु
			skb_shinfo(पंचांगp)->gso_size = mss;
			skb_shinfo(पंचांगp)->gso_type = ipv4 ? SKB_GSO_TCPV4 :
							   SKB_GSO_TCPV6;
		पूर्ण अन्यथा अणु
			अगर (qos) अणु
				u8 *qc;

				अगर (ipv4)
					ip_send_check(ip_hdr(पंचांगp));

				qc = ieee80211_get_qos_ctl((व्योम *)पंचांगp->data);
				*qc &= ~IEEE80211_QOS_CTL_A_MSDU_PRESENT;
			पूर्ण
			skb_shinfo(पंचांगp)->gso_size = 0;
		पूर्ण

		skb_mark_not_on_list(पंचांगp);
		__skb_queue_tail(mpdus_skb, पंचांगp);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iwl_mvm_tx_tso(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			  काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff_head *mpdus_skb)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
	अचिन्हित पूर्णांक mss = skb_shinfo(skb)->gso_size;
	अचिन्हित पूर्णांक num_subframes, tcp_payload_len, subf_len, max_amsdu_len;
	u16 snap_ip_tcp, pad;
	netdev_features_t netdev_flags = NETIF_F_CSUM_MASK | NETIF_F_SG;
	u8 tid;

	snap_ip_tcp = 8 + skb_transport_header(skb) - skb_network_header(skb) +
		tcp_hdrlen(skb);

	अगर (!mvmsta->max_amsdu_len ||
	    !ieee80211_is_data_qos(hdr->frame_control) ||
	    !mvmsta->amsdu_enabled)
		वापस iwl_mvm_tx_tso_segment(skb, 1, netdev_flags, mpdus_skb);

	/*
	 * Do not build AMSDU क्रम IPv6 with extension headers.
	 * ask stack to segment and checkum the generated MPDUs क्रम us.
	 */
	अगर (skb->protocol == htons(ETH_P_IPV6) &&
	    ((काष्ठा ipv6hdr *)skb_network_header(skb))->nexthdr !=
	    IPPROTO_TCP) अणु
		netdev_flags &= ~NETIF_F_CSUM_MASK;
		वापस iwl_mvm_tx_tso_segment(skb, 1, netdev_flags, mpdus_skb);
	पूर्ण

	tid = ieee80211_get_tid(hdr);
	अगर (WARN_ON_ONCE(tid >= IWL_MAX_TID_COUNT))
		वापस -EINVAL;

	/*
	 * No need to lock amsdu_in_ampdu_allowed since it can't be modअगरied
	 * during an BA session.
	 */
	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU &&
	     !mvmsta->tid_data[tid].amsdu_in_ampdu_allowed) ||
	    !(mvmsta->amsdu_enabled & BIT(tid)))
		वापस iwl_mvm_tx_tso_segment(skb, 1, netdev_flags, mpdus_skb);

	/*
	 * Take the min of ieee80211 station and mvm station
	 */
	max_amsdu_len =
		min_t(अचिन्हित पूर्णांक, sta->max_amsdu_len,
		      iwl_mvm_max_amsdu_size(mvm, sta, tid));

	/*
	 * Limit A-MSDU in A-MPDU to 4095 bytes when VHT is not
	 * supported. This is a spec requirement (IEEE 802.11-2015
	 * section 8.7.3 NOTE 3).
	 */
	अगर (info->flags & IEEE80211_TX_CTL_AMPDU &&
	    !sta->vht_cap.vht_supported)
		max_amsdu_len = min_t(अचिन्हित पूर्णांक, max_amsdu_len, 4095);

	/* Sub frame header + SNAP + IP header + TCP header + MSS */
	subf_len = माप(काष्ठा ethhdr) + snap_ip_tcp + mss;
	pad = (4 - subf_len) & 0x3;

	/*
	 * If we have N subframes in the A-MSDU, then the A-MSDU's size is
	 * N * subf_len + (N - 1) * pad.
	 */
	num_subframes = (max_amsdu_len + pad) / (subf_len + pad);

	अगर (sta->max_amsdu_subframes &&
	    num_subframes > sta->max_amsdu_subframes)
		num_subframes = sta->max_amsdu_subframes;

	tcp_payload_len = skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb) -
		tcp_hdrlen(skb) + skb->data_len;

	/*
	 * Make sure we have enough TBs क्रम the A-MSDU:
	 *	2 क्रम each subframe
	 *	1 more क्रम each fragment
	 *	1 more क्रम the potential data in the header
	 */
	अगर ((num_subframes * 2 + skb_shinfo(skb)->nr_frags + 1) >
	    mvm->trans->max_skb_frags)
		num_subframes = 1;

	अगर (num_subframes > 1)
		*ieee80211_get_qos_ctl(hdr) |= IEEE80211_QOS_CTL_A_MSDU_PRESENT;

	/* This skb fits in one single A-MSDU */
	अगर (num_subframes * mss >= tcp_payload_len) अणु
		__skb_queue_tail(mpdus_skb, skb);
		वापस 0;
	पूर्ण

	/*
	 * Trick the segmentation function to make it
	 * create SKBs that can fit पूर्णांकo one A-MSDU.
	 */
	वापस iwl_mvm_tx_tso_segment(skb, num_subframes, netdev_flags,
				      mpdus_skb);
पूर्ण
#अन्यथा /* CONFIG_INET */
अटल पूर्णांक iwl_mvm_tx_tso(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			  काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff_head *mpdus_skb)
अणु
	/* Impossible to get TSO with CONFIG_INET */
	WARN_ON(1);

	वापस -1;
पूर्ण
#पूर्ण_अगर

/* Check अगर there are any समयd-out TIDs on a given shared TXQ */
अटल bool iwl_mvm_txq_should_update(काष्ठा iwl_mvm *mvm, पूर्णांक txq_id)
अणु
	अचिन्हित दीर्घ queue_tid_biपंचांगap = mvm->queue_info[txq_id].tid_biपंचांगap;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक tid;

	अगर (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		वापस false;

	क्रम_each_set_bit(tid, &queue_tid_biपंचांगap, IWL_MAX_TID_COUNT + 1) अणु
		अगर (समय_beक्रमe(mvm->queue_info[txq_id].last_frame_समय[tid] +
				IWL_MVM_DQA_QUEUE_TIMEOUT, now))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम iwl_mvm_tx_airसमय(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_mvm_sta *mvmsta,
			       पूर्णांक airसमय)
अणु
	पूर्णांक mac = mvmsta->mac_id_n_color & FW_CTXT_ID_MSK;
	काष्ठा iwl_mvm_tcm_mac *mdata;

	अगर (mac >= NUM_MAC_INDEX_DRIVER)
		वापस;

	mdata = &mvm->tcm.data[mac];

	अगर (mvm->tcm.छोड़ोd)
		वापस;

	अगर (समय_after(jअगरfies, mvm->tcm.ts + MVM_TCM_PERIOD))
		schedule_delayed_work(&mvm->tcm.work, 0);

	mdata->tx.airसमय += airसमय;
पूर्ण

अटल पूर्णांक iwl_mvm_tx_pkt_queued(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_mvm_sta *mvmsta, पूर्णांक tid)
अणु
	u32 ac = tid_to_mac80211_ac[tid];
	पूर्णांक mac = mvmsta->mac_id_n_color & FW_CTXT_ID_MSK;
	काष्ठा iwl_mvm_tcm_mac *mdata;

	अगर (mac >= NUM_MAC_INDEX_DRIVER)
		वापस -EINVAL;

	mdata = &mvm->tcm.data[mac];

	mdata->tx.pkts[ac]++;

	वापस 0;
पूर्ण

/*
 * Sets the fields in the Tx cmd that are crypto related.
 *
 * This function must be called with BHs disabled.
 */
अटल पूर्णांक iwl_mvm_tx_mpdu(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			   काष्ठा ieee80211_tx_info *info,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा iwl_device_tx_cmd *dev_cmd;
	__le16 fc;
	u16 seq_number = 0;
	u8 tid = IWL_MAX_TID_COUNT;
	u16 txq_id;
	bool is_ampdu = false;
	पूर्णांक hdrlen;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	fc = hdr->frame_control;
	hdrlen = ieee80211_hdrlen(fc);

	अगर (IWL_MVM_NON_TRANSMITTING_AP && ieee80211_is_probe_resp(fc))
		वापस -1;

	अगर (WARN_ON_ONCE(!mvmsta))
		वापस -1;

	अगर (WARN_ON_ONCE(mvmsta->sta_id == IWL_MVM_INVALID_STA))
		वापस -1;

	अगर (unlikely(ieee80211_is_probe_resp(fc)))
		iwl_mvm_probe_resp_set_noa(mvm, skb);

	dev_cmd = iwl_mvm_set_tx_params(mvm, skb, info, hdrlen,
					sta, mvmsta->sta_id);
	अगर (!dev_cmd)
		जाओ drop;

	/*
	 * we handle that entirely ourselves -- क्रम uAPSD the firmware
	 * will always send a notअगरication, and क्रम PS-Poll responses
	 * we'll notअगरy mac80211 when getting frame status
	 */
	info->flags &= ~IEEE80211_TX_STATUS_EOSP;

	spin_lock(&mvmsta->lock);

	/* nullfunc frames should go to the MGMT queue regardless of QOS,
	 * the condition of !ieee80211_is_qos_nullfunc(fc) keeps the शेष
	 * assignment of MGMT TID
	 */
	अगर (ieee80211_is_data_qos(fc) && !ieee80211_is_qos_nullfunc(fc)) अणु
		tid = ieee80211_get_tid(hdr);
		अगर (WARN_ONCE(tid >= IWL_MAX_TID_COUNT, "Invalid TID %d", tid))
			जाओ drop_unlock_sta;

		is_ampdu = info->flags & IEEE80211_TX_CTL_AMPDU;
		अगर (WARN_ONCE(is_ampdu &&
			      mvmsta->tid_data[tid].state != IWL_AGG_ON,
			      "Invalid internal agg state %d for TID %d",
			       mvmsta->tid_data[tid].state, tid))
			जाओ drop_unlock_sta;

		seq_number = mvmsta->tid_data[tid].seq_number;
		seq_number &= IEEE80211_SCTL_SEQ;

		अगर (!iwl_mvm_has_new_tx_api(mvm)) अणु
			काष्ठा iwl_tx_cmd *tx_cmd = (व्योम *)dev_cmd->payload;

			hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
			hdr->seq_ctrl |= cpu_to_le16(seq_number);
			/* update the tx_cmd hdr as it was alपढ़ोy copied */
			tx_cmd->hdr->seq_ctrl = hdr->seq_ctrl;
		पूर्ण
	पूर्ण अन्यथा अगर (ieee80211_is_data(fc) && !ieee80211_is_data_qos(fc)) अणु
		tid = IWL_TID_NON_QOS;
	पूर्ण

	txq_id = mvmsta->tid_data[tid].txq_id;

	WARN_ON_ONCE(info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM);

	अगर (WARN_ONCE(txq_id == IWL_MVM_INVALID_QUEUE, "Invalid TXQ id")) अणु
		iwl_trans_मुक्त_tx_cmd(mvm->trans, dev_cmd);
		spin_unlock(&mvmsta->lock);
		वापस -1;
	पूर्ण

	अगर (!iwl_mvm_has_new_tx_api(mvm)) अणु
		/* Keep track of the समय of the last frame क्रम this RA/TID */
		mvm->queue_info[txq_id].last_frame_समय[tid] = jअगरfies;

		/*
		 * If we have समयd-out TIDs - schedule the worker that will
		 * reconfig the queues and update them
		 *
		 * Note that the no lock is taken here in order to not serialize
		 * the TX flow. This isn't dangerous because scheduling
		 * mvm->add_stream_wk can't ruin the state, and if we DON'T
		 * schedule it due to some race condition then next TX we get
		 * here we will.
		 */
		अगर (unlikely(mvm->queue_info[txq_id].status ==
			     IWL_MVM_QUEUE_SHARED &&
			     iwl_mvm_txq_should_update(mvm, txq_id)))
			schedule_work(&mvm->add_stream_wk);
	पूर्ण

	IWL_DEBUG_TX(mvm, "TX to [%d|%d] Q:%d - seq: 0x%x len %d\n",
		     mvmsta->sta_id, tid, txq_id,
		     IEEE80211_SEQ_TO_SN(seq_number), skb->len);

	/* From now on, we cannot access info->control */
	iwl_mvm_skb_prepare_status(skb, dev_cmd);

	अगर (iwl_trans_tx(mvm->trans, skb, dev_cmd, txq_id))
		जाओ drop_unlock_sta;

	अगर (tid < IWL_MAX_TID_COUNT && !ieee80211_has_morefrags(fc))
		mvmsta->tid_data[tid].seq_number = seq_number + 0x10;

	spin_unlock(&mvmsta->lock);

	अगर (iwl_mvm_tx_pkt_queued(mvm, mvmsta,
				  tid == IWL_MAX_TID_COUNT ? 0 : tid))
		जाओ drop;

	वापस 0;

drop_unlock_sta:
	iwl_trans_मुक्त_tx_cmd(mvm->trans, dev_cmd);
	spin_unlock(&mvmsta->lock);
drop:
	IWL_DEBUG_TX(mvm, "TX to [%d|%d] dropped\n", mvmsta->sta_id, tid);
	वापस -1;
पूर्ण

पूर्णांक iwl_mvm_tx_skb_sta(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
		       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा ieee80211_tx_info info;
	काष्ठा sk_buff_head mpdus_skbs;
	अचिन्हित पूर्णांक payload_len;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(!mvmsta))
		वापस -1;

	अगर (WARN_ON_ONCE(mvmsta->sta_id == IWL_MVM_INVALID_STA))
		वापस -1;

	स_नकल(&info, skb->cb, माप(info));

	अगर (!skb_is_gso(skb))
		वापस iwl_mvm_tx_mpdu(mvm, skb, &info, sta);

	payload_len = skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb) -
		tcp_hdrlen(skb) + skb->data_len;

	अगर (payload_len <= skb_shinfo(skb)->gso_size)
		वापस iwl_mvm_tx_mpdu(mvm, skb, &info, sta);

	__skb_queue_head_init(&mpdus_skbs);

	ret = iwl_mvm_tx_tso(mvm, skb, &info, sta, &mpdus_skbs);
	अगर (ret)
		वापस ret;

	अगर (WARN_ON(skb_queue_empty(&mpdus_skbs)))
		वापस ret;

	जबतक (!skb_queue_empty(&mpdus_skbs)) अणु
		skb = __skb_dequeue(&mpdus_skbs);

		ret = iwl_mvm_tx_mpdu(mvm, skb, &info, sta);
		अगर (ret) अणु
			__skb_queue_purge(&mpdus_skbs);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_check_ratid_empty(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_sta *sta, u8 tid)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];
	काष्ठा ieee80211_vअगर *vअगर = mvmsta->vअगर;
	u16 normalized_ssn;

	lockdep_निश्चित_held(&mvmsta->lock);

	अगर ((tid_data->state == IWL_AGG_ON ||
	     tid_data->state == IWL_EMPTYING_HW_QUEUE_DELBA) &&
	    iwl_mvm_tid_queued(mvm, tid_data) == 0) अणु
		/*
		 * Now that this aggregation or DQA queue is empty tell
		 * mac80211 so it knows we no दीर्घer have frames buffered क्रम
		 * the station on this TID (क्रम the TIM biपंचांगap calculation.)
		 */
		ieee80211_sta_set_buffered(sta, tid, false);
	पूर्ण

	/*
	 * In 22000 HW, the next_reclaimed index is only 8 bit, so we'll need
	 * to align the wrap around of ssn so we compare relevant values.
	 */
	normalized_ssn = tid_data->ssn;
	अगर (mvm->trans->trans_cfg->gen2)
		normalized_ssn &= 0xff;

	अगर (normalized_ssn != tid_data->next_reclaimed)
		वापस;

	चयन (tid_data->state) अणु
	हाल IWL_EMPTYING_HW_QUEUE_ADDBA:
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Can continue addBA flow ssn = next_recl = %d\n",
				    tid_data->next_reclaimed);
		tid_data->state = IWL_AGG_STARTING;
		ieee80211_start_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;

	हाल IWL_EMPTYING_HW_QUEUE_DELBA:
		IWL_DEBUG_TX_QUEUES(mvm,
				    "Can continue DELBA flow ssn = next_recl = %d\n",
				    tid_data->next_reclaimed);
		tid_data->state = IWL_AGG_OFF;
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
स्थिर अक्षर *iwl_mvm_get_tx_fail_reason(u32 status)
अणु
#घोषणा TX_STATUS_FAIL(x) हाल TX_STATUS_FAIL_ ## x: वापस #x
#घोषणा TX_STATUS_POSTPONE(x) हाल TX_STATUS_POSTPONE_ ## x: वापस #x

	चयन (status & TX_STATUS_MSK) अणु
	हाल TX_STATUS_SUCCESS:
		वापस "SUCCESS";
	TX_STATUS_POSTPONE(DELAY);
	TX_STATUS_POSTPONE(FEW_BYTES);
	TX_STATUS_POSTPONE(BT_PRIO);
	TX_STATUS_POSTPONE(QUIET_PERIOD);
	TX_STATUS_POSTPONE(CALC_TTAK);
	TX_STATUS_FAIL(INTERNAL_CROSSED_RETRY);
	TX_STATUS_FAIL(SHORT_LIMIT);
	TX_STATUS_FAIL(LONG_LIMIT);
	TX_STATUS_FAIL(UNDERRUN);
	TX_STATUS_FAIL(DRAIN_FLOW);
	TX_STATUS_FAIL(RFKILL_FLUSH);
	TX_STATUS_FAIL(LIFE_EXPIRE);
	TX_STATUS_FAIL(DEST_PS);
	TX_STATUS_FAIL(HOST_ABORTED);
	TX_STATUS_FAIL(BT_RETRY);
	TX_STATUS_FAIL(STA_INVALID);
	TX_STATUS_FAIL(FRAG_DROPPED);
	TX_STATUS_FAIL(TID_DISABLE);
	TX_STATUS_FAIL(FIFO_FLUSHED);
	TX_STATUS_FAIL(SMALL_CF_POLL);
	TX_STATUS_FAIL(FW_DROP);
	TX_STATUS_FAIL(STA_COLOR_MISMATCH);
	पूर्ण

	वापस "UNKNOWN";

#अघोषित TX_STATUS_FAIL
#अघोषित TX_STATUS_POSTPONE
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUG */

व्योम iwl_mvm_hwrate_to_tx_rate(u32 rate_n_flags,
			       क्रमागत nl80211_band band,
			       काष्ठा ieee80211_tx_rate *r)
अणु
	अगर (rate_n_flags & RATE_HT_MCS_GF_MSK)
		r->flags |= IEEE80211_TX_RC_GREEN_FIELD;
	चयन (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) अणु
	हाल RATE_MCS_CHAN_WIDTH_20:
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_40:
		r->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_80:
		r->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_160:
		r->flags |= IEEE80211_TX_RC_160_MHZ_WIDTH;
		अवरोध;
	पूर्ण
	अगर (rate_n_flags & RATE_MCS_SGI_MSK)
		r->flags |= IEEE80211_TX_RC_SHORT_GI;
	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		r->flags |= IEEE80211_TX_RC_MCS;
		r->idx = rate_n_flags & RATE_HT_MCS_INDEX_MSK;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_VHT_MSK) अणु
		ieee80211_rate_set_vht(
			r, rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK,
			((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
						RATE_VHT_MCS_NSS_POS) + 1);
		r->flags |= IEEE80211_TX_RC_VHT_MCS;
	पूर्ण अन्यथा अणु
		r->idx = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							     band);
	पूर्ण
पूर्ण

/*
 * translate ucode response to mac80211 tx status control values
 */
अटल व्योम iwl_mvm_hwrate_to_tx_status(u32 rate_n_flags,
					काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा ieee80211_tx_rate *r = &info->status.rates[0];

	info->status.antenna =
		((rate_n_flags & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS);
	iwl_mvm_hwrate_to_tx_rate(rate_n_flags, info->band, r);
पूर्ण

अटल व्योम iwl_mvm_tx_status_check_trigger(काष्ठा iwl_mvm *mvm,
					    u32 status, __le16 frame_control)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_tx_status *status_trig;
	पूर्णांक i;

	अगर ((status & TX_STATUS_MSK) != TX_STATUS_SUCCESS) अणु
		क्रमागत iwl_fw_ini_समय_poपूर्णांक tp =
			IWL_FW_INI_TIME_POINT_TX_FAILED;

		अगर (ieee80211_is_action(frame_control))
			tp = IWL_FW_INI_TIME_POINT_TX_WFD_ACTION_FRAME_FAILED;

		iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
				       tp, शून्य);
		वापस;
	पूर्ण

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, शून्य,
				     FW_DBG_TRIGGER_TX_STATUS);
	अगर (!trig)
		वापस;

	status_trig = (व्योम *)trig->data;

	क्रम (i = 0; i < ARRAY_SIZE(status_trig->statuses); i++) अणु
		/* करोn't collect on status 0 */
		अगर (!status_trig->statuses[i].status)
			अवरोध;

		अगर (status_trig->statuses[i].status != (status & TX_STATUS_MSK))
			जारी;

		iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
					"Tx status %d was received",
					status & TX_STATUS_MSK);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * iwl_mvm_get_scd_ssn - वापसs the SSN of the SCD
 * @tx_resp: the Tx response from the fw (agg or non-agg)
 *
 * When the fw sends an AMPDU, it fetches the MPDUs one after the other. Since
 * it can't know that everything will go well until the end of the AMPDU, it
 * can't know in advance the number of MPDUs that will be sent in the current
 * batch. This is why it ग_लिखोs the agg Tx response जबतक it fetches the MPDUs.
 * Hence, it can't know in advance what the SSN of the SCD will be at the end
 * of the batch. This is why the SSN of the SCD is written at the end of the
 * whole काष्ठा at a variable offset. This function knows how to cope with the
 * variable offset and वापसs the SSN of the SCD.
 */
अटल अंतरभूत u32 iwl_mvm_get_scd_ssn(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_mvm_tx_resp *tx_resp)
अणु
	वापस le32_to_cpup((__le32 *)iwl_mvm_get_agg_status(mvm, tx_resp) +
			    tx_resp->frame_count) & 0xfff;
पूर्ण

अटल व्योम iwl_mvm_rx_tx_cmd_single(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा ieee80211_sta *sta;
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	पूर्णांक txq_id = SEQ_TO_QUEUE(sequence);
	/* काष्ठा iwl_mvm_tx_resp_v3 is almost the same */
	काष्ठा iwl_mvm_tx_resp *tx_resp = (व्योम *)pkt->data;
	पूर्णांक sta_id = IWL_MVM_TX_RES_GET_RA(tx_resp->ra_tid);
	पूर्णांक tid = IWL_MVM_TX_RES_GET_TID(tx_resp->ra_tid);
	काष्ठा agg_tx_status *agg_status =
		iwl_mvm_get_agg_status(mvm, tx_resp);
	u32 status = le16_to_cpu(agg_status->status);
	u16 ssn = iwl_mvm_get_scd_ssn(mvm, tx_resp);
	काष्ठा sk_buff_head skbs;
	u8 skb_मुक्तd = 0;
	u8 lq_color;
	u16 next_reclaimed, seq_ctl;
	bool is_ndp = false;

	__skb_queue_head_init(&skbs);

	अगर (iwl_mvm_has_new_tx_api(mvm))
		txq_id = le16_to_cpu(tx_resp->tx_queue);

	seq_ctl = le16_to_cpu(tx_resp->seq_ctl);

	/* we can मुक्त until ssn % q.n_bd not inclusive */
	iwl_trans_reclaim(mvm->trans, txq_id, ssn, &skbs);

	जबतक (!skb_queue_empty(&skbs)) अणु
		काष्ठा sk_buff *skb = __skb_dequeue(&skbs);
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
		bool flushed = false;

		skb_मुक्तd++;

		iwl_trans_मुक्त_tx_cmd(mvm->trans, info->driver_data[1]);

		स_रखो(&info->status, 0, माप(info->status));

		/* inक्रमm mac80211 about what happened with the frame */
		चयन (status & TX_STATUS_MSK) अणु
		हाल TX_STATUS_SUCCESS:
		हाल TX_STATUS_सूचीECT_DONE:
			info->flags |= IEEE80211_TX_STAT_ACK;
			अवरोध;
		हाल TX_STATUS_FAIL_FIFO_FLUSHED:
		हाल TX_STATUS_FAIL_DRAIN_FLOW:
			flushed = true;
			अवरोध;
		हाल TX_STATUS_FAIL_DEST_PS:
			/* the FW should have stopped the queue and not
			 * वापस this status
			 */
			WARN_ON(1);
			info->flags |= IEEE80211_TX_STAT_TX_FILTERED;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर ((status & TX_STATUS_MSK) != TX_STATUS_SUCCESS &&
		    ieee80211_is_mgmt(hdr->frame_control))
			iwl_mvm_toggle_tx_ant(mvm, &mvm->mgmt_last_antenna_idx);

		/*
		 * If we are मुक्तing multiple frames, mark all the frames
		 * but the first one as acked, since they were acknowledged
		 * beक्रमe
		 * */
		अगर (skb_मुक्तd > 1)
			info->flags |= IEEE80211_TX_STAT_ACK;

		iwl_mvm_tx_status_check_trigger(mvm, status, hdr->frame_control);

		info->status.rates[0].count = tx_resp->failure_frame + 1;
		iwl_mvm_hwrate_to_tx_status(le32_to_cpu(tx_resp->initial_rate),
					    info);
		info->status.status_driver_data[1] =
			(व्योम *)(uपूर्णांकptr_t)le32_to_cpu(tx_resp->initial_rate);

		/* Single frame failure in an AMPDU queue => send BAR */
		अगर (info->flags & IEEE80211_TX_CTL_AMPDU &&
		    !(info->flags & IEEE80211_TX_STAT_ACK) &&
		    !(info->flags & IEEE80211_TX_STAT_TX_FILTERED) && !flushed)
			info->flags |= IEEE80211_TX_STAT_AMPDU_NO_BACK;
		info->flags &= ~IEEE80211_TX_CTL_AMPDU;

		/* W/A FW bug: seq_ctl is wrong upon failure / BAR frame */
		अगर (ieee80211_is_back_req(hdr->frame_control))
			seq_ctl = 0;
		अन्यथा अगर (status != TX_STATUS_SUCCESS)
			seq_ctl = le16_to_cpu(hdr->seq_ctrl);

		अगर (unlikely(!seq_ctl)) अणु
			काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;

			/*
			 * If it is an NDP, we can't update next_reclaim since
			 * its sequence control is 0. Note that क्रम that same
			 * reason, NDPs are never sent to A-MPDU'able queues
			 * so that we can never have more than one मुक्तd frame
			 * क्रम a single Tx resonse (see WARN_ON below).
			 */
			अगर (ieee80211_is_qos_nullfunc(hdr->frame_control))
				is_ndp = true;
		पूर्ण

		/*
		 * TODO: this is not accurate अगर we are मुक्तing more than one
		 * packet.
		 */
		info->status.tx_समय =
			le16_to_cpu(tx_resp->wireless_media_समय);
		BUILD_BUG_ON(ARRAY_SIZE(info->status.status_driver_data) < 1);
		lq_color = TX_RES_RATE_TABLE_COL_GET(tx_resp->tlc_info);
		info->status.status_driver_data[0] =
			RS_DRV_DATA_PACK(lq_color, tx_resp->reduced_tpc);

		ieee80211_tx_status(mvm->hw, skb);
	पूर्ण

	/* This is an aggregation queue or might become one, so we use
	 * the ssn since: ssn = wअगरi seq_num % 256.
	 * The seq_ctl is the sequence control of the packet to which
	 * this Tx response relates. But अगर there is a hole in the
	 * biपंचांगap of the BA we received, this Tx response may allow to
	 * reclaim the hole and all the subsequent packets that were
	 * alपढ़ोy acked. In that हाल, seq_ctl != ssn, and the next
	 * packet to be reclaimed will be ssn and not seq_ctl. In that
	 * हाल, several packets will be reclaimed even अगर
	 * frame_count = 1.
	 *
	 * The ssn is the index (% 256) of the latest packet that has
	 * treated (acked / dropped) + 1.
	 */
	next_reclaimed = ssn;

	IWL_DEBUG_TX_REPLY(mvm,
			   "TXQ %d status %s (0x%08x)\n",
			   txq_id, iwl_mvm_get_tx_fail_reason(status), status);

	IWL_DEBUG_TX_REPLY(mvm,
			   "\t\t\t\tinitial_rate 0x%x retries %d, idx=%d ssn=%d next_reclaimed=0x%x seq_ctl=0x%x\n",
			   le32_to_cpu(tx_resp->initial_rate),
			   tx_resp->failure_frame, SEQ_TO_INDEX(sequence),
			   ssn, next_reclaimed, seq_ctl);

	rcu_पढ़ो_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
	/*
	 * sta can't be NULL otherwise it'd mean that the sta has been मुक्तd in
	 * the firmware जबतक we still have packets क्रम it in the Tx queues.
	 */
	अगर (WARN_ON_ONCE(!sta))
		जाओ out;

	अगर (!IS_ERR(sta)) अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

		iwl_mvm_tx_airसमय(mvm, mvmsta,
				   le16_to_cpu(tx_resp->wireless_media_समय));

		अगर ((status & TX_STATUS_MSK) != TX_STATUS_SUCCESS &&
		    mvmsta->sta_state < IEEE80211_STA_AUTHORIZED)
			iwl_mvm_toggle_tx_ant(mvm, &mvmsta->tx_ant);

		अगर (sta->wme && tid != IWL_MGMT_TID) अणु
			काष्ठा iwl_mvm_tid_data *tid_data =
				&mvmsta->tid_data[tid];
			bool send_eosp_ndp = false;

			spin_lock_bh(&mvmsta->lock);

			अगर (!is_ndp) अणु
				tid_data->next_reclaimed = next_reclaimed;
				IWL_DEBUG_TX_REPLY(mvm,
						   "Next reclaimed packet:%d\n",
						   next_reclaimed);
			पूर्ण अन्यथा अणु
				IWL_DEBUG_TX_REPLY(mvm,
						   "NDP - don't update next_reclaimed\n");
			पूर्ण

			iwl_mvm_check_ratid_empty(mvm, sta, tid);

			अगर (mvmsta->sleep_tx_count) अणु
				mvmsta->sleep_tx_count--;
				अगर (mvmsta->sleep_tx_count &&
				    !iwl_mvm_tid_queued(mvm, tid_data)) अणु
					/*
					 * The number of frames in the queue
					 * dropped to 0 even अगर we sent less
					 * frames than we thought we had on the
					 * Tx queue.
					 * This means we had holes in the BA
					 * winकरोw that we just filled, ask
					 * mac80211 to send EOSP since the
					 * firmware won't know how to करो that.
					 * Send NDP and the firmware will send
					 * EOSP notअगरication that will trigger
					 * a call to ieee80211_sta_eosp().
					 */
					send_eosp_ndp = true;
				पूर्ण
			पूर्ण

			spin_unlock_bh(&mvmsta->lock);
			अगर (send_eosp_ndp) अणु
				iwl_mvm_sta_modअगरy_sleep_tx_count(mvm, sta,
					IEEE80211_FRAME_RELEASE_UAPSD,
					1, tid, false, false);
				mvmsta->sleep_tx_count = 0;
				ieee80211_send_eosp_nullfunc(sta, tid);
			पूर्ण
		पूर्ण

		अगर (mvmsta->next_status_eosp) अणु
			mvmsta->next_status_eosp = false;
			ieee80211_sta_eosp(sta);
		पूर्ण
	पूर्ण
out:
	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
#घोषणा AGG_TX_STATE_(x) हाल AGG_TX_STATE_ ## x: वापस #x
अटल स्थिर अक्षर *iwl_get_agg_tx_status(u16 status)
अणु
	चयन (status & AGG_TX_STATE_STATUS_MSK) अणु
	AGG_TX_STATE_(TRANSMITTED);
	AGG_TX_STATE_(UNDERRUN);
	AGG_TX_STATE_(BT_PRIO);
	AGG_TX_STATE_(FEW_BYTES);
	AGG_TX_STATE_(ABORT);
	AGG_TX_STATE_(TX_ON_AIR_DROP);
	AGG_TX_STATE_(LAST_SENT_TRY_CNT);
	AGG_TX_STATE_(LAST_SENT_BT_KILL);
	AGG_TX_STATE_(SCD_QUERY);
	AGG_TX_STATE_(TEST_BAD_CRC32);
	AGG_TX_STATE_(RESPONSE);
	AGG_TX_STATE_(DUMP_TX);
	AGG_TX_STATE_(DELAY_TX);
	पूर्ण

	वापस "UNKNOWN";
पूर्ण

अटल व्योम iwl_mvm_rx_tx_cmd_agg_dbg(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_mvm_tx_resp *tx_resp = (व्योम *)pkt->data;
	काष्ठा agg_tx_status *frame_status =
		iwl_mvm_get_agg_status(mvm, tx_resp);
	पूर्णांक i;
	bool tirgger_समयpoपूर्णांक = false;

	क्रम (i = 0; i < tx_resp->frame_count; i++) अणु
		u16 ख_स्थितिus = le16_to_cpu(frame_status[i].status);
		/* In हाल one frame wasn't transmitted trigger समय poपूर्णांक */
		tirgger_समयpoपूर्णांक |= ((ख_स्थितिus & AGG_TX_STATE_STATUS_MSK) !=
				      AGG_TX_STATE_TRANSMITTED);
		IWL_DEBUG_TX_REPLY(mvm,
				   "status %s (0x%04x), try-count (%d) seq (0x%x)\n",
				   iwl_get_agg_tx_status(ख_स्थितिus),
				   ख_स्थितिus & AGG_TX_STATE_STATUS_MSK,
				   (ख_स्थितिus & AGG_TX_STATE_TRY_CNT_MSK) >>
					AGG_TX_STATE_TRY_CNT_POS,
				   le16_to_cpu(frame_status[i].sequence));
	पूर्ण

	अगर (tirgger_समयpoपूर्णांक)
		iwl_dbg_tlv_समय_poपूर्णांक(&mvm->fwrt,
				       IWL_FW_INI_TIME_POINT_TX_FAILED, शून्य);

पूर्ण
#अन्यथा
अटल व्योम iwl_mvm_rx_tx_cmd_agg_dbg(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_rx_packet *pkt)
अणुपूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUG */

अटल व्योम iwl_mvm_rx_tx_cmd_agg(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_mvm_tx_resp *tx_resp = (व्योम *)pkt->data;
	पूर्णांक sta_id = IWL_MVM_TX_RES_GET_RA(tx_resp->ra_tid);
	पूर्णांक tid = IWL_MVM_TX_RES_GET_TID(tx_resp->ra_tid);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	काष्ठा iwl_mvm_sta *mvmsta;
	पूर्णांक queue = SEQ_TO_QUEUE(sequence);
	काष्ठा ieee80211_sta *sta;

	अगर (WARN_ON_ONCE(queue < IWL_MVM_DQA_MIN_DATA_QUEUE &&
			 (queue != IWL_MVM_DQA_BSS_CLIENT_QUEUE)))
		वापस;

	iwl_mvm_rx_tx_cmd_agg_dbg(mvm, pkt);

	rcu_पढ़ो_lock();

	mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, sta_id);

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
	अगर (WARN_ON_ONCE(!sta || !sta->wme)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	अगर (!WARN_ON_ONCE(!mvmsta)) अणु
		mvmsta->tid_data[tid].rate_n_flags =
			le32_to_cpu(tx_resp->initial_rate);
		mvmsta->tid_data[tid].tx_समय =
			le16_to_cpu(tx_resp->wireless_media_समय);
		mvmsta->tid_data[tid].lq_color =
			TX_RES_RATE_TABLE_COL_GET(tx_resp->tlc_info);
		iwl_mvm_tx_airसमय(mvm, mvmsta,
				   le16_to_cpu(tx_resp->wireless_media_समय));
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_rx_tx_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_mvm_tx_resp *tx_resp = (व्योम *)pkt->data;

	अगर (tx_resp->frame_count == 1)
		iwl_mvm_rx_tx_cmd_single(mvm, pkt);
	अन्यथा
		iwl_mvm_rx_tx_cmd_agg(mvm, pkt);
पूर्ण

अटल व्योम iwl_mvm_tx_reclaim(काष्ठा iwl_mvm *mvm, पूर्णांक sta_id, पूर्णांक tid,
			       पूर्णांक txq, पूर्णांक index,
			       काष्ठा ieee80211_tx_info *tx_info, u32 rate,
			       bool is_flush)
अणु
	काष्ठा sk_buff_head reclaimed_skbs;
	काष्ठा iwl_mvm_tid_data *tid_data = शून्य;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_sta *mvmsta = शून्य;
	काष्ठा sk_buff *skb;
	पूर्णांक मुक्तd;

	अगर (WARN_ONCE(sta_id >= mvm->fw->ucode_capa.num_stations ||
		      tid > IWL_MAX_TID_COUNT,
		      "sta_id %d tid %d", sta_id, tid))
		वापस;

	rcu_पढ़ो_lock();

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

	/* Reclaiming frames क्रम a station that has been deleted ? */
	अगर (WARN_ON_ONCE(!sta)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	__skb_queue_head_init(&reclaimed_skbs);

	/*
	 * Release all TFDs beक्रमe the SSN, i.e. all TFDs in front of
	 * block-ack winकरोw (we assume that they've been successfully
	 * transmitted ... अगर not, it's too late anyway).
	 */
	iwl_trans_reclaim(mvm->trans, txq, index, &reclaimed_skbs);

	skb_queue_walk(&reclaimed_skbs, skb) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		iwl_trans_मुक्त_tx_cmd(mvm->trans, info->driver_data[1]);

		स_रखो(&info->status, 0, माप(info->status));
		/* Packet was transmitted successfully, failures come as single
		 * frames because beक्रमe failing a frame the firmware transmits
		 * it without aggregation at least once.
		 */
		अगर (!is_flush)
			info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण

	/*
	 * It's possible to get a BA response after invalidating the rcu (rcu is
	 * invalidated in order to prevent new Tx from being sent, but there may
	 * be some frames alपढ़ोy in-flight).
	 * In this हाल we just want to reclaim, and could skip all the
	 * sta-dependent stuff since it's in the middle of being हटाओd
	 * anyways.
	 */
	अगर (IS_ERR(sta))
		जाओ out;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	tid_data = &mvmsta->tid_data[tid];

	अगर (tid_data->txq_id != txq) अणु
		IWL_ERR(mvm,
			"invalid reclaim request: Q %d, tid %d\n",
			tid_data->txq_id, tid);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	spin_lock_bh(&mvmsta->lock);

	tid_data->next_reclaimed = index;

	iwl_mvm_check_ratid_empty(mvm, sta, tid);

	मुक्तd = 0;

	/* pack lq color from tid_data aदीर्घ the reduced txp */
	tx_info->status.status_driver_data[0] =
		RS_DRV_DATA_PACK(tid_data->lq_color,
				 tx_info->status.status_driver_data[0]);
	tx_info->status.status_driver_data[1] = (व्योम *)(uपूर्णांकptr_t)rate;

	skb_queue_walk(&reclaimed_skbs, skb) अणु
		काष्ठा ieee80211_hdr *hdr = (व्योम *)skb->data;
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		अगर (!is_flush) अणु
			अगर (ieee80211_is_data_qos(hdr->frame_control))
				मुक्तd++;
			अन्यथा
				WARN_ON_ONCE(tid != IWL_MAX_TID_COUNT);
		पूर्ण

		/* this is the first skb we deliver in this batch */
		/* put the rate scaling data there */
		अगर (मुक्तd == 1) अणु
			info->flags |= IEEE80211_TX_STAT_AMPDU;
			स_नकल(&info->status, &tx_info->status,
			       माप(tx_info->status));
			iwl_mvm_hwrate_to_tx_status(rate, info);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&mvmsta->lock);

	/* We got a BA notअगर with 0 acked or scd_ssn didn't progress which is
	 * possible (i.e. first MPDU in the aggregation wasn't acked)
	 * Still it's important to update RS about sent vs. acked.
	 */
	अगर (!is_flush && skb_queue_empty(&reclaimed_skbs)) अणु
		काष्ठा ieee80211_chanctx_conf *chanctx_conf = शून्य;

		अगर (mvmsta->vअगर)
			chanctx_conf =
				rcu_dereference(mvmsta->vअगर->chanctx_conf);

		अगर (WARN_ON_ONCE(!chanctx_conf))
			जाओ out;

		tx_info->band = chanctx_conf->def.chan->band;
		iwl_mvm_hwrate_to_tx_status(rate, tx_info);

		अगर (!iwl_mvm_has_tlc_offload(mvm)) अणु
			IWL_DEBUG_TX_REPLY(mvm,
					   "No reclaim. Update rs directly\n");
			iwl_mvm_rs_tx_status(mvm, sta, tid, tx_info, false);
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	जबतक (!skb_queue_empty(&reclaimed_skbs)) अणु
		skb = __skb_dequeue(&reclaimed_skbs);
		ieee80211_tx_status(mvm->hw, skb);
	पूर्ण
पूर्ण

व्योम iwl_mvm_rx_ba_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);
	पूर्णांक sta_id, tid, txq, index;
	काष्ठा ieee80211_tx_info ba_info = अणुपूर्ण;
	काष्ठा iwl_mvm_ba_notअगर *ba_notअगर;
	काष्ठा iwl_mvm_tid_data *tid_data;
	काष्ठा iwl_mvm_sta *mvmsta;

	ba_info.flags = IEEE80211_TX_STAT_AMPDU;

	अगर (iwl_mvm_has_new_tx_api(mvm)) अणु
		काष्ठा iwl_mvm_compressed_ba_notअगर *ba_res =
			(व्योम *)pkt->data;
		u8 lq_color = TX_RES_RATE_TABLE_COL_GET(ba_res->tlc_rate_info);
		u16 tfd_cnt;
		पूर्णांक i;

		अगर (unlikely(माप(*ba_res) > pkt_len))
			वापस;

		sta_id = ba_res->sta_id;
		ba_info.status.ampdu_ack_len = (u8)le16_to_cpu(ba_res->करोne);
		ba_info.status.ampdu_len = (u8)le16_to_cpu(ba_res->txed);
		ba_info.status.tx_समय =
			(u16)le32_to_cpu(ba_res->wireless_समय);
		ba_info.status.status_driver_data[0] =
			(व्योम *)(uपूर्णांकptr_t)ba_res->reduced_txp;

		tfd_cnt = le16_to_cpu(ba_res->tfd_cnt);
		अगर (!tfd_cnt || काष्ठा_size(ba_res, tfd, tfd_cnt) > pkt_len)
			वापस;

		rcu_पढ़ो_lock();

		mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, sta_id);
		/*
		 * It's possible to get a BA response after invalidating the rcu
		 * (rcu is invalidated in order to prevent new Tx from being
		 * sent, but there may be some frames alपढ़ोy in-flight).
		 * In this हाल we just want to reclaim, and could skip all the
		 * sta-dependent stuff since it's in the middle of being हटाओd
		 * anyways.
		 */

		/* Free per TID */
		क्रम (i = 0; i < tfd_cnt; i++) अणु
			काष्ठा iwl_mvm_compressed_ba_tfd *ba_tfd =
				&ba_res->tfd[i];

			tid = ba_tfd->tid;
			अगर (tid == IWL_MGMT_TID)
				tid = IWL_MAX_TID_COUNT;

			अगर (mvmsta)
				mvmsta->tid_data[i].lq_color = lq_color;

			iwl_mvm_tx_reclaim(mvm, sta_id, tid,
					   (पूर्णांक)(le16_to_cpu(ba_tfd->q_num)),
					   le16_to_cpu(ba_tfd->tfd_index),
					   &ba_info,
					   le32_to_cpu(ba_res->tx_rate), false);
		पूर्ण

		अगर (mvmsta)
			iwl_mvm_tx_airसमय(mvm, mvmsta,
					   le32_to_cpu(ba_res->wireless_समय));
		rcu_पढ़ो_unlock();

		IWL_DEBUG_TX_REPLY(mvm,
				   "BA_NOTIFICATION Received from sta_id = %d, flags %x, sent:%d, acked:%d\n",
				   sta_id, le32_to_cpu(ba_res->flags),
				   le16_to_cpu(ba_res->txed),
				   le16_to_cpu(ba_res->करोne));
		वापस;
	पूर्ण

	ba_notअगर = (व्योम *)pkt->data;
	sta_id = ba_notअगर->sta_id;
	tid = ba_notअगर->tid;
	/* "flow" corresponds to Tx queue */
	txq = le16_to_cpu(ba_notअगर->scd_flow);
	/* "ssn" is start of block-ack Tx winकरोw, corresponds to index
	 * (in Tx queue's circular buffer) of first TFD/frame in winकरोw */
	index = le16_to_cpu(ba_notअगर->scd_ssn);

	rcu_पढ़ो_lock();
	mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, sta_id);
	अगर (WARN_ON_ONCE(!mvmsta)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	tid_data = &mvmsta->tid_data[tid];

	ba_info.status.ampdu_ack_len = ba_notअगर->txed_2_करोne;
	ba_info.status.ampdu_len = ba_notअगर->txed;
	ba_info.status.tx_समय = tid_data->tx_समय;
	ba_info.status.status_driver_data[0] =
		(व्योम *)(uपूर्णांकptr_t)ba_notअगर->reduced_txp;

	rcu_पढ़ो_unlock();

	iwl_mvm_tx_reclaim(mvm, sta_id, tid, txq, index, &ba_info,
			   tid_data->rate_n_flags, false);

	IWL_DEBUG_TX_REPLY(mvm,
			   "BA_NOTIFICATION Received from %pM, sta_id = %d\n",
			   ba_notअगर->sta_addr, ba_notअगर->sta_id);

	IWL_DEBUG_TX_REPLY(mvm,
			   "TID = %d, SeqCtl = %d, bitmap = 0x%llx, scd_flow = %d, scd_ssn = %d sent:%d, acked:%d\n",
			   ba_notअगर->tid, le16_to_cpu(ba_notअगर->seq_ctl),
			   le64_to_cpu(ba_notअगर->biपंचांगap), txq, index,
			   ba_notअगर->txed, ba_notअगर->txed_2_करोne);

	IWL_DEBUG_TX_REPLY(mvm, "reduced txp from ba notif %d\n",
			   ba_notअगर->reduced_txp);
पूर्ण

/*
 * Note that there are transports that buffer frames beक्रमe they reach
 * the firmware. This means that after flush_tx_path is called, the
 * queue might not be empty. The race-मुक्त way to handle this is to:
 * 1) set the station as draining
 * 2) flush the Tx path
 * 3) रुको क्रम the transport queues to be empty
 */
पूर्णांक iwl_mvm_flush_tx_path(काष्ठा iwl_mvm *mvm, u32 tfd_msk)
अणु
	पूर्णांक ret;
	काष्ठा iwl_tx_path_flush_cmd_v1 flush_cmd = अणु
		.queues_ctl = cpu_to_le32(tfd_msk),
		.flush_ctl = cpu_to_le16(DUMP_TX_FIFO_FLUSH),
	पूर्ण;

	WARN_ON(iwl_mvm_has_new_tx_api(mvm));
	ret = iwl_mvm_send_cmd_pdu(mvm, TXPATH_FLUSH, 0,
				   माप(flush_cmd), &flush_cmd);
	अगर (ret)
		IWL_ERR(mvm, "Failed to send flush command (%d)\n", ret);
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_flush_sta_tids(काष्ठा iwl_mvm *mvm, u32 sta_id, u16 tids)
अणु
	पूर्णांक ret;
	काष्ठा iwl_tx_path_flush_cmd_rsp *rsp;
	काष्ठा iwl_tx_path_flush_cmd flush_cmd = अणु
		.sta_id = cpu_to_le32(sta_id),
		.tid_mask = cpu_to_le16(tids),
	पूर्ण;

	काष्ठा iwl_host_cmd cmd = अणु
		.id = TXPATH_FLUSH,
		.len = अणु माप(flush_cmd), पूर्ण,
		.data = अणु &flush_cmd, पूर्ण,
	पूर्ण;

	WARN_ON(!iwl_mvm_has_new_tx_api(mvm));

	अगर (iwl_fw_lookup_notअगर_ver(mvm->fw, LONG_GROUP, TXPATH_FLUSH, 0) > 0)
		cmd.flags |= CMD_WANT_SKB;

	IWL_DEBUG_TX_QUEUES(mvm, "flush for sta id %d tid mask 0x%x\n",
			    sta_id, tids);

	ret = iwl_mvm_send_cmd(mvm, &cmd);

	अगर (ret) अणु
		IWL_ERR(mvm, "Failed to send flush command (%d)\n", ret);
		वापस ret;
	पूर्ण

	अगर (cmd.flags & CMD_WANT_SKB) अणु
		पूर्णांक i;
		पूर्णांक num_flushed_queues;

		अगर (WARN_ON_ONCE(iwl_rx_packet_payload_len(cmd.resp_pkt) != माप(*rsp))) अणु
			ret = -EIO;
			जाओ मुक्त_rsp;
		पूर्ण

		rsp = (व्योम *)cmd.resp_pkt->data;

		अगर (WARN_ONCE(le16_to_cpu(rsp->sta_id) != sta_id,
			      "sta_id %d != rsp_sta_id %d",
			      sta_id, le16_to_cpu(rsp->sta_id))) अणु
			ret = -EIO;
			जाओ मुक्त_rsp;
		पूर्ण

		num_flushed_queues = le16_to_cpu(rsp->num_flushed_queues);
		अगर (WARN_ONCE(num_flushed_queues > IWL_TX_FLUSH_QUEUE_RSP,
			      "num_flushed_queues %d", num_flushed_queues)) अणु
			ret = -EIO;
			जाओ मुक्त_rsp;
		पूर्ण

		क्रम (i = 0; i < num_flushed_queues; i++) अणु
			काष्ठा ieee80211_tx_info tx_info = अणुपूर्ण;
			काष्ठा iwl_flush_queue_info *queue_info = &rsp->queues[i];
			पूर्णांक tid = le16_to_cpu(queue_info->tid);
			पूर्णांक पढ़ो_beक्रमe = le16_to_cpu(queue_info->पढ़ो_beक्रमe_flush);
			पूर्णांक पढ़ो_after = le16_to_cpu(queue_info->पढ़ो_after_flush);
			पूर्णांक queue_num = le16_to_cpu(queue_info->queue_num);

			अगर (tid == IWL_MGMT_TID)
				tid = IWL_MAX_TID_COUNT;

			IWL_DEBUG_TX_QUEUES(mvm,
					    "tid %d queue_id %d read-before %d read-after %d\n",
					    tid, queue_num, पढ़ो_beक्रमe, पढ़ो_after);

			iwl_mvm_tx_reclaim(mvm, sta_id, tid, queue_num, पढ़ो_after,
					   &tx_info, 0, true);
		पूर्ण
मुक्त_rsp:
		iwl_मुक्त_resp(&cmd);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक iwl_mvm_flush_sta(काष्ठा iwl_mvm *mvm, व्योम *sta, bool पूर्णांकernal)
अणु
	काष्ठा iwl_mvm_पूर्णांक_sta *पूर्णांक_sta = sta;
	काष्ठा iwl_mvm_sta *mvm_sta = sta;

	BUILD_BUG_ON(दुरत्व(काष्ठा iwl_mvm_पूर्णांक_sta, sta_id) !=
		     दुरत्व(काष्ठा iwl_mvm_sta, sta_id));

	अगर (iwl_mvm_has_new_tx_api(mvm))
		वापस iwl_mvm_flush_sta_tids(mvm, mvm_sta->sta_id, 0xffff);

	अगर (पूर्णांकernal)
		वापस iwl_mvm_flush_tx_path(mvm, पूर्णांक_sta->tfd_queue_msk);

	वापस iwl_mvm_flush_tx_path(mvm, mvm_sta->tfd_queue_msk);
पूर्ण
