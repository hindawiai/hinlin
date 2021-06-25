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
#समावेश "trx.h"
#समावेश "led.h"

अटल u8 _rtl92ce_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb, u8 hw_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस QSLT_MGNT;

	वापस skb->priority;
पूर्ण

अटल व्योम _rtl92ce_query_rxphystatus(काष्ठा ieee80211_hw *hw,
				       काष्ठा rtl_stats *pstats,
				       काष्ठा rx_desc_92c *pdesc,
				       काष्ठा rx_fwinfo_92c *p_drvinfo,
				       bool packet_match_bssid,
				       bool packet_toself,
				       bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा phy_sts_cck_8192s_t *cck_buf;
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 evm, pwdb_all, rf_rx_num = 0;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck_rate;

	is_cck_rate = RX_HAL_IS_CCK_RATE(pdesc->rxmcs);
	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_toself = packet_toself;
	pstats->is_cck = is_cck_rate;
	pstats->packet_beacon = packet_beacon;
	pstats->rx_mimo_sig_qual[0] = -1;
	pstats->rx_mimo_sig_qual[1] = -1;

	अगर (is_cck_rate) अणु
		u8 report, cck_highpwr;

		cck_buf = (काष्ठा phy_sts_cck_8192s_t *)p_drvinfo;

		अगर (ppsc->rfpwr_state == ERFON)
			cck_highpwr = (u8) rtl_get_bbreg(hw,
						 RFPGA0_XA_HSSIPARAMETER2,
						 BIT(9));
		अन्यथा
			cck_highpwr = false;

		अगर (!cck_highpwr) अणु
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;

			report = cck_buf->cck_agc_rpt & 0xc0;
			report = report >> 6;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -46 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -26 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -12 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 16 - (cck_agc_rpt & 0x3e);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;

			report = p_drvinfo->cfosho[0] & 0x60;
			report = report >> 5;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -46 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -26 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -12 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 16 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			पूर्ण
		पूर्ण

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		/* CCK gain is smaller than OFDM/MCS gain,
		 * so we add gain dअगरf by experiences,
		 * the val is 6
		 */
		pwdb_all += 6;
		अगर (pwdb_all > 100)
			pwdb_all = 100;
		/* modअगरy the offset to make the same
		 * gain index with OFDM.
		 */
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

		/* (3) Get Signal Quality (EVM) */
		अगर (packet_match_bssid) अणु
			u8 sq;

			अगर (pstats->rx_pwdb_all > 40)
				sq = 100;
			अन्यथा अणु
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
		/* (1)Get RSSI क्रम HT rate */
		क्रम (i = RF90_PATH_A; i < RF90_PATH_MAX; i++) अणु
			/* we will judge RF RX path now. */
			अगर (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] =
			    ((p_drvinfo->gain_trsw[i] & 0x3f) * 2) - 110;
			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;
			/* Get Rx snr value in DB */
			rtlpriv->stats.rx_snr_db[i] =
			    (दीर्घ)(p_drvinfo->rxsnr[i] / 2);

			/* Record Signal Strength क्रम next packet */
			अगर (packet_match_bssid)
				pstats->rx_mimo_संकेतstrength[i] = (u8) rssi;
		पूर्ण

		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->rxघातer = rx_pwr_all;
		pstats->recvसंकेतघातer = rx_pwr_all;

		/* (3)EVM of HT rate */
		अगर (pstats->is_ht && pstats->rate >= DESC_RATEMCS8 &&
		    pstats->rate <= DESC_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);

			अगर (packet_match_bssid) अणु
				/* Fill value in RFD, Get the first
				 * spatial stream only
				 */
				अगर (i == 0)
					pstats->संकेतquality =
					    (u8)(evm & 0xff);
				pstats->rx_mimo_sig_qual[i] = (u8)(evm & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण

	/* UI BSS List संकेत strength(in percentage),
	 * make it good looking, from 0~100.
	 */
	अगर (is_cck_rate)
		pstats->संकेतstrength =
		    (u8)(rtl_संकेत_scale_mapping(hw, pwdb_all));
	अन्यथा अगर (rf_rx_num != 0)
		pstats->संकेतstrength =
		    (u8)(rtl_संकेत_scale_mapping(hw, total_rssi /= rf_rx_num));
पूर्ण

अटल व्योम _rtl92ce_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
					       काष्ठा sk_buff *skb,
					       काष्ठा rtl_stats *pstats,
					       काष्ठा rx_desc_92c *pdesc,
					       काष्ठा rx_fwinfo_92c *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	__le16 fc;
	u16 type, c_fc;
	bool packet_matchbssid, packet_toself, packet_beacon = false;

	पंचांगp_buf = skb->data + pstats->rx_drvinfo_size + pstats->rx_bufshअगरt;

	hdr = (काष्ठा ieee80211_hdr *)पंचांगp_buf;
	fc = hdr->frame_control;
	c_fc = le16_to_cpu(fc);
	type = WLAN_FC_GET_TYPE(fc);
	praddr = hdr->addr1;

	packet_matchbssid =
	    ((IEEE80211_FTYPE_CTL != type) &&
	     ether_addr_equal(mac->bssid,
			      (c_fc & IEEE80211_FCTL_TODS) ? hdr->addr1 :
			      (c_fc & IEEE80211_FCTL_FROMDS) ? hdr->addr2 :
			      hdr->addr3) &&
	     (!pstats->hwerror) && (!pstats->crc) && (!pstats->icv));

	packet_toself = packet_matchbssid &&
	     ether_addr_equal(praddr, rtlefuse->dev_addr);

	अगर (ieee80211_is_beacon(fc))
		packet_beacon = true;

	_rtl92ce_query_rxphystatus(hw, pstats, pdesc, p_drvinfo,
				   packet_matchbssid, packet_toself,
				   packet_beacon);

	rtl_process_phyinfo(hw, पंचांगp_buf, pstats);
पूर्ण

bool rtl92ce_rx_query_desc(काष्ठा ieee80211_hw *hw,
			   काष्ठा rtl_stats *stats,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *p_desc8, काष्ठा sk_buff *skb)
अणु
	काष्ठा rx_fwinfo_92c *p_drvinfo;
	काष्ठा rx_desc_92c *pdesc = (काष्ठा rx_desc_92c *)p_desc8;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *p_desc = (__le32 *)p_desc8;
	u32 phystatus = get_rx_desc_physt(p_desc);

	stats->length = (u16)get_rx_desc_pkt_len(p_desc);
	stats->rx_drvinfo_size = (u8)get_rx_desc_drv_info_size(p_desc) *
	    RX_DRV_INFO_SIZE_UNIT;
	stats->rx_bufshअगरt = (u8)(get_rx_desc_shअगरt(p_desc) & 0x03);
	stats->icv = (u16)get_rx_desc_icv(p_desc);
	stats->crc = (u16)get_rx_desc_crc32(p_desc);
	stats->hwerror = (stats->crc | stats->icv);
	stats->decrypted = !get_rx_desc_swdec(p_desc);
	stats->rate = (u8)get_rx_desc_rxmcs(p_desc);
	stats->लघुpreamble = (u16)get_rx_desc_splcp(p_desc);
	stats->isampdu = (bool)(get_rx_desc_paggr(p_desc) == 1);
	stats->isfirst_ampdu = (bool)((get_rx_desc_paggr(p_desc) == 1) &&
				      (get_rx_desc_faggr(p_desc) == 1));
	stats->बारtamp_low = get_rx_desc_tsfl(p_desc);
	stats->rx_is40mhzpacket = (bool)get_rx_desc_bw(p_desc);
	stats->is_ht = (bool)get_rx_desc_rxht(p_desc);

	stats->is_cck = RX_HAL_IS_CCK_RATE(pdesc->rxmcs);

	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + stats->rx_drvinfo_size
			+ stats->rx_bufshअगरt);

	अगर (stats->crc)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (stats->rx_is40mhzpacket)
		rx_status->bw = RATE_INFO_BW_40;

	अगर (stats->is_ht)
		rx_status->encoding = RX_ENC_HT;

	rx_status->flag |= RX_FLAG_MACTIME_START;

	/* hw will set stats->decrypted true, अगर it finds the
	 * frame is खोलो data frame or mgmt frame.
	 * So hw will not decryption robust managment frame
	 * क्रम IEEE80211w but still set status->decrypted
	 * true, so here we should set it back to undecrypted
	 * क्रम IEEE80211w frame, and mac80211 sw will help
	 * to decrypt it
	 */
	अगर (stats->decrypted) अणु
		अगर ((_ieee80211_is_robust_mgmt_frame(hdr)) &&
		    (ieee80211_has_रक्षित(hdr->frame_control)))
			rx_status->flag &= ~RX_FLAG_DECRYPTED;
		अन्यथा
			rx_status->flag |= RX_FLAG_DECRYPTED;
	पूर्ण
	/* rate_idx: index of data rate पूर्णांकo band's
	 * supported rates or MCS index अगर HT rates
	 * are use (RX_FLAG_HT)
	 * Notice: this is dअगरf with winकरोws define
	 */
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, stats->is_ht,
						   false, stats->rate);

	rx_status->maस_समय = stats->बारtamp_low;
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_92c *)(skb->data +
						     stats->rx_bufshअगरt);

		_rtl92ce_translate_rx_संकेत_stuff(hw,
						   skb, stats, pdesc,
						   p_drvinfo);
	पूर्ण

	/*rx_status->qual = stats->संकेत; */
	rx_status->संकेत = stats->recvसंकेतघातer + 10;

	वापस true;
पूर्ण

व्योम rtl92ce_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc8,
			  u8 *pbd_desc_tx, काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb,
			  u8 hw_queue, काष्ठा rtl_tcb_desc *tcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool शेषadapter = true;
	__le32 *pdesc = (__le32 *)pdesc8;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 fw_qsel = _rtl92ce_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			  cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);

	bool lastseg = ((hdr->frame_control &
			 cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);

	dma_addr_t mapping = dma_map_single(&rtlpci->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);

	u8 bw_40 = 0;

	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	rcu_पढ़ो_lock();
	sta = get_sta(hw, mac->vअगर, mac->bssid);
	अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
		bw_40 = mac->bw_40;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		   mac->opmode == NL80211_IFTYPE_ADHOC ||
		   mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		अगर (sta)
			bw_40 = sta->bandwidth >= IEEE80211_STA_RX_BW_40;
	पूर्ण

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	rtl_get_tcb_desc(hw, info, sta, skb, tcb_desc);

	clear_pci_tx_desc_content(pdesc, माप(काष्ठा tx_desc_92c));

	अगर (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) अणु
		firstseg = true;
		lastseg = true;
	पूर्ण
	अगर (firstseg) अणु
		set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

		set_tx_desc_tx_rate(pdesc, tcb_desc->hw_rate);

		अगर (tcb_desc->use_लघुgi || tcb_desc->use_लघुpreamble)
			set_tx_desc_data_लघुgi(pdesc, 1);

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			set_tx_desc_agg_अवरोध(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		पूर्ण
		set_tx_desc_seq(pdesc, seq_number);

		set_tx_desc_rts_enable(pdesc, ((tcb_desc->rts_enable &&
						!tcb_desc->
						cts_enable) ? 1 : 0));
		set_tx_desc_hw_rts_enable(pdesc,
					  ((tcb_desc->rts_enable
					    || tcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_cts2self(pdesc, ((tcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_rts_stbc(pdesc, ((tcb_desc->rts_stbc) ? 1 : 0));

		set_tx_desc_rts_rate(pdesc, tcb_desc->rts_rate);
		set_tx_desc_rts_bw(pdesc, 0);
		set_tx_desc_rts_sc(pdesc, tcb_desc->rts_sc);
		set_tx_desc_rts_लघु(pdesc,
				      ((tcb_desc->rts_rate <= DESC_RATE54M) ?
				       (tcb_desc->rts_use_लघुpreamble ? 1 : 0)
				       : (tcb_desc->rts_use_लघुgi ? 1 : 0)));

		अगर (bw_40) अणु
			अगर (tcb_desc->packet_bw) अणु
				set_tx_desc_data_bw(pdesc, 1);
				set_tx_desc_tx_sub_carrier(pdesc, 3);
			पूर्ण अन्यथा अणु
				set_tx_desc_data_bw(pdesc, 0);
				set_tx_desc_tx_sub_carrier(pdesc,
						 mac->cur_40_prime_sc);
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_data_bw(pdesc, 0);
			set_tx_desc_tx_sub_carrier(pdesc, 0);
		पूर्ण

		set_tx_desc_linip(pdesc, 0);
		set_tx_desc_pkt_size(pdesc, (u16)skb->len);

		अगर (sta) अणु
			u8 ampdu_density = sta->ht_cap.ampdu_density;

			set_tx_desc_ampdu_density(pdesc, ampdu_density);
		पूर्ण

		अगर (info->control.hw_key) अणु
			काष्ठा ieee80211_key_conf *keyconf =
			    info->control.hw_key;

			चयन (keyconf->cipher) अणु
			हाल WLAN_CIPHER_SUITE_WEP40:
			हाल WLAN_CIPHER_SUITE_WEP104:
			हाल WLAN_CIPHER_SUITE_TKIP:
				set_tx_desc_sec_type(pdesc, 0x1);
				अवरोध;
			हाल WLAN_CIPHER_SUITE_CCMP:
				set_tx_desc_sec_type(pdesc, 0x3);
				अवरोध;
			शेष:
				set_tx_desc_sec_type(pdesc, 0x0);
				अवरोध;

			पूर्ण
		पूर्ण

		set_tx_desc_pkt_id(pdesc, 0);
		set_tx_desc_queue_sel(pdesc, fw_qsel);

		set_tx_desc_data_rate_fb_limit(pdesc, 0x1F);
		set_tx_desc_rts_rate_fb_limit(pdesc, 0xF);
		set_tx_desc_disable_fb(pdesc, 0);
		set_tx_desc_use_rate(pdesc, tcb_desc->use_driver_rate ? 1 : 0);

		अगर (ieee80211_is_data_qos(fc)) अणु
			अगर (mac->rdg_en) अणु
				rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
					"Enable RDG function\n");
				set_tx_desc_rdg_enable(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	set_tx_desc_first_seg(pdesc, (firstseg ? 1 : 0));
	set_tx_desc_last_seg(pdesc, (lastseg ? 1 : 0));

	set_tx_desc_tx_buffer_size(pdesc, (u16)skb->len);

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	अगर (rtlpriv->dm.useramask) अणु
		set_tx_desc_rate_id(pdesc, tcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, tcb_desc->mac_id);
	पूर्ण अन्यथा अणु
		set_tx_desc_rate_id(pdesc, 0xC + tcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, tcb_desc->ratr_index);
	पूर्ण

	अगर ((!ieee80211_is_data_qos(fc)) && ppsc->fwctrl_lps) अणु
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);

		अगर (!शेषadapter)
			set_tx_desc_qos(pdesc, 1);
	पूर्ण

	set_tx_desc_more_frag(pdesc, (lastseg ? 0 : 1));

	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) अणु
		set_tx_desc_bmc(pdesc, 1);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl92ce_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
			     u8 *pdesc8, bool firstseg,
			     bool lastseg, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 fw_queue = QSLT_BEACON;
	__le32 *pdesc = (__le32 *)pdesc8;

	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;

	dma_addr_t mapping = dma_map_single(&rtlpci->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);

	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	clear_pci_tx_desc_content(pdesc, TX_DESC_SIZE);

	अगर (firstseg)
		set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

	set_tx_desc_tx_rate(pdesc, DESC_RATE1M);

	set_tx_desc_seq(pdesc, 0);

	set_tx_desc_linip(pdesc, 0);

	set_tx_desc_queue_sel(pdesc, fw_queue);

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_tx_buffer_size(pdesc, (u16)(skb->len));

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	set_tx_desc_rate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);

	set_tx_desc_own(pdesc, 1);

	set_tx_desc_pkt_size(pdesc, (u16)(skb->len));

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_offset(pdesc, 0x20);

	set_tx_desc_use_rate(pdesc, 1);

	अगर (!ieee80211_is_data_qos(fc)) अणु
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	पूर्ण

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content", pdesc, TX_DESC_SIZE);
पूर्ण

व्योम rtl92ce_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8, bool istx,
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
			WARN_ONCE(true, "rtl8192ce: ERR txdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_RXOWN:
			wmb();
			set_rx_desc_own(pdesc, 1);
			अवरोध;
		हाल HW_DESC_RXBUFF_ADDR:
			set_rx_desc_buff_addr(pdesc, *(u32 *)val);
			अवरोध;
		हाल HW_DESC_RXPKT_LEN:
			set_rx_desc_pkt_len(pdesc, *(u32 *)val);
			अवरोध;
		हाल HW_DESC_RXERO:
			set_rx_desc_eor(pdesc, 1);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192ce: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl92ce_get_desc(काष्ठा ieee80211_hw *hw, u8 *p_desc8,
		     bool istx, u8 desc_name)
अणु
	u32 ret = 0;
	__le32 *p_desc = (__le32 *)p_desc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_tx_desc_own(p_desc);
			अवरोध;
		हाल HW_DESC_TXBUFF_ADDR:
			ret = get_tx_desc_tx_buffer_address(p_desc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192ce: ERR txdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_rx_desc_own(p_desc);
			अवरोध;
		हाल HW_DESC_RXPKT_LEN:
			ret = get_rx_desc_pkt_len(p_desc);
			अवरोध;
		हाल HW_DESC_RXBUFF_ADDR:
			ret = get_rx_desc_buff_addr(p_desc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192ce: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool rtl92ce_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw,
			       u8 hw_queue, u16 index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u8 *entry = (u8 *)(&ring->desc[ring->idx]);
	u8 own = (u8)rtl92ce_get_desc(hw, entry, true, HW_DESC_OWN);

	/*beacon packet will only use the first
	 *descriptor defautly,and the own may not
	 *be cleared by the hardware
	 */
	अगर (own)
		वापस false;
	वापस true;
पूर्ण

व्योम rtl92ce_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (hw_queue == BEACON_QUEUE) अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG, BIT(4));
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG,
			       BIT(0) << (hw_queue));
	पूर्ण
पूर्ण

