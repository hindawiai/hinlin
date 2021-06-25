<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../stats.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "fw.h"
#समावेश "trx.h"
#समावेश "led.h"

अटल u8 _rtl92se_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb,	u8 skb_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस QSLT_MGNT;
	अगर (ieee80211_is_nullfunc(fc))
		वापस QSLT_HIGH;

	/* Kernel commit 1bf4bbb4024dcdab changed EAPOL packets to use
	 * queue V0 at priority 7; however, the RTL8192SE appears to have
	 * that queue at priority 6
	 */
	अगर (skb->priority == 7)
		वापस QSLT_VO;
	वापस skb->priority;
पूर्ण

अटल व्योम _rtl92se_query_rxphystatus(काष्ठा ieee80211_hw *hw,
				       काष्ठा rtl_stats *pstats, __le32 *pdesc,
				       काष्ठा rx_fwinfo *p_drvinfo,
				       bool packet_match_bssid,
				       bool packet_toself,
				       bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा phy_sts_cck_8192s_t *cck_buf;
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck = pstats->is_cck;

	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_toself = packet_toself;
	pstats->packet_beacon = packet_beacon;
	pstats->rx_mimo_sig_qual[0] = -1;
	pstats->rx_mimo_sig_qual[1] = -1;

	अगर (is_cck) अणु
		u8 report, cck_highpwr;
		cck_buf = (काष्ठा phy_sts_cck_8192s_t *)p_drvinfo;

		अगर (ppsc->rfpwr_state == ERFON)
			cck_highpwr = (u8) rtl_get_bbreg(hw,
						RFPGA0_XA_HSSIPARAMETER2,
						0x200);
		अन्यथा
			cck_highpwr = false;

		अगर (!cck_highpwr) अणु
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;
			report = cck_buf->cck_agc_rpt & 0xc0;
			report = report >> 6;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -40 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -20 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -2 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 14 - (cck_agc_rpt & 0x3e);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;
			report = p_drvinfo->cfosho[0] & 0x60;
			report = report >> 5;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -40 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -20 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -2 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 14 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			पूर्ण
		पूर्ण

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);

		/* CCK gain is smaller than OFDM/MCS gain,  */
		/* so we add gain dअगरf by experiences, the val is 6 */
		pwdb_all += 6;
		अगर (pwdb_all > 100)
			pwdb_all = 100;
		/* modअगरy the offset to make the same gain index with OFDM. */
		अगर (pwdb_all > 34 && pwdb_all <= 42)
			pwdb_all -= 2;
		अन्यथा अगर (pwdb_all > 26 && pwdb_all <= 34)
			pwdb_all -= 6;
		अन्यथा अगर (pwdb_all > 14 && pwdb_all <= 26)
			pwdb_all -= 8;
		अन्यथा अगर (pwdb_all > 4 && pwdb_all <= 14)
			pwdb_all -= 4;

		pstats->rx_pwdb_all = pwdb_all;
		pstats->recvसंकेतघातer = rx_pwr_all;

		अगर (packet_match_bssid) अणु
			u8 sq;
			अगर (pstats->rx_pwdb_all > 40) अणु
				sq = 100;
			पूर्ण अन्यथा अणु
				sq = cck_buf->sq_rpt;
				अगर (sq > 64)
					sq = 0;
				अन्यथा अगर (sq < 20)
					sq = 100;
				अन्यथा
					sq = ((64 - sq) * 100) / 44;
			पूर्ण

			pstats->संकेतquality = sq;
			pstats->rx_mimo_sig_qual[0] = sq;
			pstats->rx_mimo_sig_qual[1] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
		क्रम (i = RF90_PATH_A; i < RF6052_MAX_PATH; i++) अणु
			अगर (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = ((p_drvinfo->gain_trsw[i] &
				    0x3f) * 2) - 110;
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;
			rtlpriv->stats.rx_snr_db[i] =
					 (दीर्घ)(p_drvinfo->rxsnr[i] / 2);

			अगर (packet_match_bssid)
				pstats->rx_mimo_संकेतstrength[i] = (u8) rssi;
		पूर्ण

		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->rxघातer = rx_pwr_all;
		pstats->recvसंकेतघातer = rx_pwr_all;

		अगर (pstats->is_ht && pstats->rate >= DESC_RATEMCS8 &&
		    pstats->rate <= DESC_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);

			अगर (packet_match_bssid) अणु
				अगर (i == 0)
					pstats->संकेतquality = (u8)(evm &
								 0xff);
				pstats->rx_mimo_sig_qual[i] = (u8) (evm & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (is_cck)
		pstats->संकेतstrength = (u8)(rtl_संकेत_scale_mapping(hw,
					 pwdb_all));
	अन्यथा अगर (rf_rx_num != 0)
		pstats->संकेतstrength = (u8) (rtl_संकेत_scale_mapping(hw,
				total_rssi /= rf_rx_num));
पूर्ण

अटल व्योम _rtl92se_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
		काष्ठा sk_buff *skb, काष्ठा rtl_stats *pstats,
		__le32 *pdesc, काष्ठा rx_fwinfo *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	__le16 fc;
	u16 type, cfc;
	bool packet_matchbssid, packet_toself, packet_beacon = false;

	पंचांगp_buf = skb->data + pstats->rx_drvinfo_size + pstats->rx_bufshअगरt;

	hdr = (काष्ठा ieee80211_hdr *)पंचांगp_buf;
	fc = hdr->frame_control;
	cfc = le16_to_cpu(fc);
	type = WLAN_FC_GET_TYPE(fc);
	praddr = hdr->addr1;

	packet_matchbssid = ((IEEE80211_FTYPE_CTL != type) &&
	     ether_addr_equal(mac->bssid,
			      (cfc & IEEE80211_FCTL_TODS) ? hdr->addr1 :
			      (cfc & IEEE80211_FCTL_FROMDS) ? hdr->addr2 :
			      hdr->addr3) &&
	     (!pstats->hwerror) && (!pstats->crc) && (!pstats->icv));

	packet_toself = packet_matchbssid &&
	    ether_addr_equal(praddr, rtlefuse->dev_addr);

	अगर (ieee80211_is_beacon(fc))
		packet_beacon = true;

	_rtl92se_query_rxphystatus(hw, pstats, pdesc, p_drvinfo,
			packet_matchbssid, packet_toself, packet_beacon);
	rtl_process_phyinfo(hw, पंचांगp_buf, pstats);
पूर्ण

bool rtl92se_rx_query_desc(काष्ठा ieee80211_hw *hw, काष्ठा rtl_stats *stats,
			   काष्ठा ieee80211_rx_status *rx_status, u8 *pdesc8,
			   काष्ठा sk_buff *skb)
अणु
	काष्ठा rx_fwinfo *p_drvinfo;
	__le32 *pdesc = (__le32 *)pdesc8;
	u32 phystatus = (u32)get_rx_status_desc_phy_status(pdesc);
	काष्ठा ieee80211_hdr *hdr;

	stats->length = (u16)get_rx_status_desc_pkt_len(pdesc);
	stats->rx_drvinfo_size = (u8)get_rx_status_desc_drvinfo_size(pdesc) * 8;
	stats->rx_bufshअगरt = (u8)(get_rx_status_desc_shअगरt(pdesc) & 0x03);
	stats->icv = (u16)get_rx_status_desc_icv(pdesc);
	stats->crc = (u16)get_rx_status_desc_crc32(pdesc);
	stats->hwerror = (u16)(stats->crc | stats->icv);
	stats->decrypted = !get_rx_status_desc_swdec(pdesc);

	stats->rate = (u8)get_rx_status_desc_rx_mcs(pdesc);
	stats->लघुpreamble = (u16)get_rx_status_desc_splcp(pdesc);
	stats->isampdu = (bool)(get_rx_status_desc_paggr(pdesc) == 1);
	stats->isfirst_ampdu = (bool)((get_rx_status_desc_paggr(pdesc) == 1) &&
				      (get_rx_status_desc_faggr(pdesc) == 1));
	stats->बारtamp_low = get_rx_status_desc_tsfl(pdesc);
	stats->rx_is40mhzpacket = (bool)get_rx_status_desc_bw(pdesc);
	stats->is_ht = (bool)get_rx_status_desc_rx_ht(pdesc);
	stats->is_cck = SE_RX_HAL_IS_CCK_RATE(pdesc);

	अगर (stats->hwerror)
		वापस false;

	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;

	अगर (stats->crc)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (stats->rx_is40mhzpacket)
		rx_status->bw = RATE_INFO_BW_40;

	अगर (stats->is_ht)
		rx_status->encoding = RX_ENC_HT;

	rx_status->flag |= RX_FLAG_MACTIME_START;

	/* hw will set stats->decrypted true, अगर it finds the
	 * frame is खोलो data frame or mgmt frame,
	 * hw will not decrypt robust managment frame
	 * क्रम IEEE80211w but still set stats->decrypted
	 * true, so here we should set it back to undecrypted
	 * क्रम IEEE80211w frame, and mac80211 sw will help
	 * to decrypt it */
	अगर (stats->decrypted) अणु
		hdr = (काष्ठा ieee80211_hdr *)(skb->data +
		       stats->rx_drvinfo_size + stats->rx_bufshअगरt);

		अगर ((_ieee80211_is_robust_mgmt_frame(hdr)) &&
			(ieee80211_has_रक्षित(hdr->frame_control)))
			rx_status->flag &= ~RX_FLAG_DECRYPTED;
		अन्यथा
			rx_status->flag |= RX_FLAG_DECRYPTED;
	पूर्ण

	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, stats->is_ht,
						   false, stats->rate);

	rx_status->maस_समय = stats->बारtamp_low;
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo *)(skb->data +
						 stats->rx_bufshअगरt);
		_rtl92se_translate_rx_संकेत_stuff(hw, skb, stats, pdesc,
						   p_drvinfo);
	पूर्ण

	/*rx_status->qual = stats->संकेत; */
	rx_status->संकेत = stats->recvसंकेतघातer + 10;

	वापस true;
पूर्ण

व्योम rtl92se_tx_fill_desc(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_hdr *hdr, u8 *pdesc8,
		u8 *pbd_desc_tx, काष्ठा ieee80211_tx_info *info,
		काष्ठा ieee80211_sta *sta,
		काष्ठा sk_buff *skb,
		u8 hw_queue, काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	__le32 *pdesc = (__le32 *)pdesc8;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 reserved_macid = 0;
	u8 fw_qsel = _rtl92se_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = (!(hdr->seq_ctrl & cpu_to_le16(IEEE80211_SCTL_FRAG)));
	bool lastseg = (!(hdr->frame_control &
			cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)));
	dma_addr_t mapping = dma_map_single(&rtlpci->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);
	u8 bw_40 = 0;

	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
		bw_40 = mac->bw_40;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC) अणु
		अगर (sta)
			bw_40 = sta->bandwidth >= IEEE80211_STA_RX_BW_40;
	पूर्ण

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	rtl_get_tcb_desc(hw, info, sta, skb, ptcb_desc);

	CLEAR_PCI_TX_DESC_CONTENT(pdesc, TX_DESC_SIZE_RTL8192S);

	अगर (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) अणु
		firstseg = true;
		lastseg = true;
	पूर्ण

	अगर (firstseg) अणु
		अगर (rtlpriv->dm.useramask) अणु
			/* set txdesc macId */
			अगर (ptcb_desc->mac_id < 32) अणु
				set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
				reserved_macid |= ptcb_desc->mac_id;
			पूर्ण
		पूर्ण
		set_tx_desc_rsvd_macid(pdesc, reserved_macid);

		set_tx_desc_txht(pdesc, ((ptcb_desc->hw_rate >=
				 DESC_RATEMCS0) ? 1 : 0));

		अगर (rtlhal->version == VERSION_8192S_ACUT) अणु
			अगर (ptcb_desc->hw_rate == DESC_RATE1M ||
			    ptcb_desc->hw_rate  == DESC_RATE2M ||
			    ptcb_desc->hw_rate == DESC_RATE5_5M ||
			    ptcb_desc->hw_rate == DESC_RATE11M) अणु
				ptcb_desc->hw_rate = DESC_RATE12M;
			पूर्ण
		पूर्ण

		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);

		अगर (ptcb_desc->use_लघुgi || ptcb_desc->use_लघुpreamble)
			set_tx_desc_tx_लघु(pdesc, 0);

		/* Aggregation related */
		अगर (info->flags & IEEE80211_TX_CTL_AMPDU)
			set_tx_desc_agg_enable(pdesc, 1);

		/* For AMPDU, we must insert SSN पूर्णांकo TX_DESC */
		set_tx_desc_seq(pdesc, seq_number);

		/* Protection mode related */
		/* For 92S, अगर RTS/CTS are set, HW will execute RTS. */
		/* We choose only one protection mode to execute */
		set_tx_desc_rts_enable(pdesc, ((ptcb_desc->rts_enable &&
						!ptcb_desc->cts_enable) ?
					       1 : 0));
		set_tx_desc_cts_enable(pdesc, ((ptcb_desc->cts_enable) ?
				       1 : 0));
		set_tx_desc_rts_stbc(pdesc, ((ptcb_desc->rts_stbc) ? 1 : 0));

		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);
		set_tx_desc_rts_bandwidth(pdesc, 0);
		set_tx_desc_rts_sub_carrier(pdesc, ptcb_desc->rts_sc);
		set_tx_desc_rts_लघु(pdesc, ((ptcb_desc->rts_rate <=
		       DESC_RATE54M) ?
		       (ptcb_desc->rts_use_लघुpreamble ? 1 : 0)
		       : (ptcb_desc->rts_use_लघुgi ? 1 : 0)));


		/* Set Bandwidth and sub-channel settings. */
		अगर (bw_40) अणु
			अगर (ptcb_desc->packet_bw) अणु
				set_tx_desc_tx_bandwidth(pdesc, 1);
				/* use duplicated mode */
				set_tx_desc_tx_sub_carrier(pdesc, 0);
			पूर्ण अन्यथा अणु
				set_tx_desc_tx_bandwidth(pdesc, 0);
				set_tx_desc_tx_sub_carrier(pdesc,
						   mac->cur_40_prime_sc);
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_tx_bandwidth(pdesc, 0);
			set_tx_desc_tx_sub_carrier(pdesc, 0);
		पूर्ण

		/* 3 Fill necessary field in First Descriptor */
		/*DWORD 0*/
		set_tx_desc_linip(pdesc, 0);
		set_tx_desc_offset(pdesc, 32);
		set_tx_desc_pkt_size(pdesc, (u16)skb->len);

		/*DWORD 1*/
		set_tx_desc_ra_brsr_id(pdesc, ptcb_desc->ratr_index);

		/* Fill security related */
		अगर (info->control.hw_key) अणु
			काष्ठा ieee80211_key_conf *keyconf;

			keyconf = info->control.hw_key;
			चयन (keyconf->cipher) अणु
			हाल WLAN_CIPHER_SUITE_WEP40:
			हाल WLAN_CIPHER_SUITE_WEP104:
				set_tx_desc_sec_type(pdesc, 0x1);
				अवरोध;
			हाल WLAN_CIPHER_SUITE_TKIP:
				set_tx_desc_sec_type(pdesc, 0x2);
				अवरोध;
			हाल WLAN_CIPHER_SUITE_CCMP:
				set_tx_desc_sec_type(pdesc, 0x3);
				अवरोध;
			शेष:
				set_tx_desc_sec_type(pdesc, 0x0);
				अवरोध;

			पूर्ण
		पूर्ण

		/* Set Packet ID */
		set_tx_desc_packet_id(pdesc, 0);

		/* We will assign magement queue to BK. */
		set_tx_desc_queue_sel(pdesc, fw_qsel);

		/* Alwasy enable all rate fallback range */
		set_tx_desc_data_rate_fb_limit(pdesc, 0x1F);

		/* Fix: I करोn't kown why hw use 6.5M to tx when set it */
		set_tx_desc_user_rate(pdesc,
				      ptcb_desc->use_driver_rate ? 1 : 0);

		/* Set NON_QOS bit. */
		अगर (!ieee80211_is_data_qos(fc))
			set_tx_desc_non_qos(pdesc, 1);

	पूर्ण

	/* Fill fields that are required to be initialized
	 * in all of the descriptors */
	/*DWORD 0 */
	set_tx_desc_first_seg(pdesc, (firstseg ? 1 : 0));
	set_tx_desc_last_seg(pdesc, (lastseg ? 1 : 0));

	/* DWORD 7 */
	set_tx_desc_tx_buffer_size(pdesc, (u16)skb->len);

	/* DOWRD 8 */
	set_tx_desc_tx_buffer_address(pdesc, mapping);

	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl92se_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw, u8 *pdesc8,
			     bool firstseg, bool lastseg, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_tcb_desc *tcb_desc = (काष्ठा rtl_tcb_desc *)(skb->cb);
	__le32 *pdesc = (__le32 *)pdesc8;

	dma_addr_t mapping = dma_map_single(&rtlpci->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);

	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	/* Clear all status	*/
	CLEAR_PCI_TX_DESC_CONTENT(pdesc, TX_CMDDESC_SIZE_RTL8192S);

	/* This bit indicate this packet is used क्रम FW करोwnload. */
	अगर (tcb_desc->cmd_or_init == DESC_PACKET_TYPE_INIT) अणु
		/* For firmware करोwnlaod we only need to set LINIP */
		set_tx_desc_linip(pdesc, tcb_desc->last_inipkt);

		/* 92SE must set as 1 क्रम firmware करोwnload HW DMA error */
		set_tx_desc_first_seg(pdesc, 1);
		set_tx_desc_last_seg(pdesc, 1);

		/* 92SE need not to set TX packet size when firmware करोwnload */
		set_tx_desc_pkt_size(pdesc, (u16)(skb->len));
		set_tx_desc_tx_buffer_size(pdesc, (u16)(skb->len));
		set_tx_desc_tx_buffer_address(pdesc, mapping);

		wmb();
		set_tx_desc_own(pdesc, 1);
	पूर्ण अन्यथा अणु /* H2C Command Desc क्रमmat (Host TXCMD) */
		/* 92SE must set as 1 क्रम firmware करोwnload HW DMA error */
		set_tx_desc_first_seg(pdesc, 1);
		set_tx_desc_last_seg(pdesc, 1);

		set_tx_desc_offset(pdesc, 0x20);

		/* Buffer size + command header */
		set_tx_desc_pkt_size(pdesc, (u16)(skb->len));
		/* Fixed queue of H2C command */
		set_tx_desc_queue_sel(pdesc, 0x13);

		le32p_replace_bits((__le32 *)skb->data, rtlhal->h2c_txcmd_seq,
				   GENMASK(30, 24));
		set_tx_desc_tx_buffer_size(pdesc, (u16)(skb->len));
		set_tx_desc_tx_buffer_address(pdesc, mapping);

		wmb();
		set_tx_desc_own(pdesc, 1);

	पूर्ण
पूर्ण

व्योम rtl92se_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8, bool istx,
		      u8 desc_name, u8 *val)
अणु
	__le32 *pdesc = (__le32 *)pdesc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			wmb();
			set_tx_desc_own(pdesc, 1);
			अवरोध;
		हाल HW_DESC_TX_NEXTDESC_ADDR:
			set_tx_desc_next_desc_address(pdesc, *(u32 *)val);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192se: ERR txdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_RXOWN:
			wmb();
			set_rx_status_desc_own(pdesc, 1);
			अवरोध;
		हाल HW_DESC_RXBUFF_ADDR:
			set_rx_status__desc_buff_addr(pdesc, *(u32 *)val);
			अवरोध;
		हाल HW_DESC_RXPKT_LEN:
			set_rx_status_desc_pkt_len(pdesc, *(u32 *)val);
			अवरोध;
		हाल HW_DESC_RXERO:
			set_rx_status_desc_eor(pdesc, 1);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192se: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl92se_get_desc(काष्ठा ieee80211_hw *hw,
		     u8 *desc8, bool istx, u8 desc_name)
अणु
	u32 ret = 0;
	__le32 *desc = (__le32 *)desc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_tx_desc_own(desc);
			अवरोध;
		हाल HW_DESC_TXBUFF_ADDR:
			ret = get_tx_desc_tx_buffer_address(desc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192se: ERR txdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_rx_status_desc_own(desc);
			अवरोध;
		हाल HW_DESC_RXPKT_LEN:
			ret = get_rx_status_desc_pkt_len(desc);
			अवरोध;
		हाल HW_DESC_RXBUFF_ADDR:
			ret = get_rx_status_desc_buff_addr(desc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192se: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम rtl92se_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtl_ग_लिखो_word(rtlpriv, TP_POLL, BIT(0) << (hw_queue));
पूर्ण
