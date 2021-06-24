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

अटल u8 _rtl8723e_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb, u8 hw_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस QSLT_MGNT;

	वापस skb->priority;
पूर्ण

अटल व्योम _rtl8723e_query_rxphystatus(काष्ठा ieee80211_hw *hw,
					काष्ठा rtl_stats *pstatus, u8 *pdesc,
					काष्ठा rx_fwinfo_8723e *p_drvinfo,
					bool bpacket_match_bssid,
					bool bpacket_toself, bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	काष्ठा phy_sts_cck_8723e_t *cck_buf;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck = pstatus->is_cck;

	/* Record it क्रम next packet processing */
	pstatus->packet_matchbssid = bpacket_match_bssid;
	pstatus->packet_toself = bpacket_toself;
	pstatus->packet_beacon = packet_beacon;
	pstatus->rx_mimo_संकेतquality[0] = -1;
	pstatus->rx_mimo_संकेतquality[1] = -1;

	अगर (is_cck) अणु
		u8 report, cck_highpwr;

		/* CCK Driver info Structure is not the same as OFDM packet. */
		cck_buf = (काष्ठा phy_sts_cck_8723e_t *)p_drvinfo;

		/* (1)Hardware करोes not provide RSSI क्रम CCK */
		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		अगर (ppsc->rfpwr_state == ERFON)
			cck_highpwr = (u8)rtl_get_bbreg(hw,
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
		/* CCK gain is smaller than OFDM/MCS gain,  */
		/* so we add gain dअगरf by experiences,
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

		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->recvसंकेतघातer = rx_pwr_all;

		/* (3) Get Signal Quality (EVM) */
		अगर (bpacket_match_bssid) अणु
			u8 sq;

			अगर (pstatus->rx_pwdb_all > 40)
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

			pstatus->संकेतquality = sq;
			pstatus->rx_mimo_संकेतquality[0] = sq;
			pstatus->rx_mimo_संकेतquality[1] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;

		/* (1)Get RSSI क्रम HT rate */
		क्रम (i = RF90_PATH_A; i < RF6052_MAX_PATH; i++) अणु

			/* we will judge RF RX path now. */
			अगर (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = ((p_drvinfo->gain_trsw[i] &
				      0x3f) * 2) - 110;

			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;

			/* Get Rx snr value in DB */
			rtlpriv->stats.rx_snr_db[i] =
				(दीर्घ)(p_drvinfo->rxsnr[i] / 2);

			/* Record Signal Strength क्रम next packet */
			अगर (bpacket_match_bssid)
				pstatus->rx_mimo_संकेतstrength[i] = (u8)rssi;
		पूर्ण

		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->rxघातer = rx_pwr_all;
		pstatus->recvसंकेतघातer = rx_pwr_all;

		/* (3)EVM of HT rate */
		अगर (pstatus->is_ht && pstatus->rate >= DESC92C_RATEMCS8 &&
		    pstatus->rate <= DESC92C_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);

			अगर (bpacket_match_bssid) अणु
				/* Fill value in RFD, Get the first
				 * spatial stream only
				 */
				अगर (i == 0)
					pstatus->संकेतquality =
						(u8)(evm & 0xff);
				pstatus->rx_mimo_संकेतquality[i] =
					(u8)(evm & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण

	/* UI BSS List संकेत strength(in percentage),
	 * make it good looking, from 0~100.
	 */
	अगर (is_cck)
		pstatus->संकेतstrength = (u8)(rtl_संकेत_scale_mapping(hw,
			pwdb_all));
	अन्यथा अगर (rf_rx_num != 0)
		pstatus->संकेतstrength = (u8)(rtl_संकेत_scale_mapping(hw,
			total_rssi /= rf_rx_num));
पूर्ण

अटल व्योम translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
				      काष्ठा sk_buff *skb,
				      काष्ठा rtl_stats *pstatus, u8 *pdesc,
				      काष्ठा rx_fwinfo_8723e *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	/*u8 *psaddr;*/
	u16 fc, type;
	bool packet_matchbssid, packet_toself, packet_beacon;

	पंचांगp_buf = skb->data + pstatus->rx_drvinfo_size + pstatus->rx_bufshअगरt;

	hdr = (काष्ठा ieee80211_hdr *)पंचांगp_buf;
	fc = le16_to_cpu(hdr->frame_control);
	type = WLAN_FC_GET_TYPE(hdr->frame_control);
	praddr = hdr->addr1;

	packet_matchbssid = ((IEEE80211_FTYPE_CTL != type) &&
		(ether_addr_equal(mac->bssid, (fc & IEEE80211_FCTL_TODS) ?
		 hdr->addr1 : (fc & IEEE80211_FCTL_FROMDS) ?
		 hdr->addr2 : hdr->addr3)) &&
		 (!pstatus->hwerror) &&
		 (!pstatus->crc) && (!pstatus->icv));

	packet_toself = packet_matchbssid &&
	    (ether_addr_equal(praddr, rtlefuse->dev_addr));

	अगर (ieee80211_is_beacon(hdr->frame_control))
		packet_beacon = true;
	अन्यथा
		packet_beacon = false;

	_rtl8723e_query_rxphystatus(hw, pstatus, pdesc, p_drvinfo,
				    packet_matchbssid, packet_toself,
				    packet_beacon);

	rtl_process_phyinfo(hw, पंचांगp_buf, pstatus);
पूर्ण

bool rtl8723e_rx_query_desc(काष्ठा ieee80211_hw *hw,
			    काष्ठा rtl_stats *status,
			    काष्ठा ieee80211_rx_status *rx_status,
			    u8 *pdesc8, काष्ठा sk_buff *skb)
अणु
	काष्ठा rx_fwinfo_8723e *p_drvinfo;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *pdesc = (__le32 *)pdesc8;
	u32 phystatus = get_rx_desc_physt(pdesc);

	status->length = (u16)get_rx_desc_pkt_len(pdesc);
	status->rx_drvinfo_size = (u8)get_rx_desc_drv_info_size(pdesc) *
	    RX_DRV_INFO_SIZE_UNIT;
	status->rx_bufshअगरt = (u8)(get_rx_desc_shअगरt(pdesc) & 0x03);
	status->icv = (u16)get_rx_desc_icv(pdesc);
	status->crc = (u16)get_rx_desc_crc32(pdesc);
	status->hwerror = (status->crc | status->icv);
	status->decrypted = !get_rx_desc_swdec(pdesc);
	status->rate = (u8)get_rx_desc_rxmcs(pdesc);
	status->लघुpreamble = (u16)get_rx_desc_splcp(pdesc);
	status->isampdu = (bool)(get_rx_desc_paggr(pdesc) == 1);
	status->isfirst_ampdu = (bool)((get_rx_desc_paggr(pdesc) == 1) &&
				       (get_rx_desc_faggr(pdesc) == 1));
	status->बारtamp_low = get_rx_desc_tsfl(pdesc);
	status->rx_is40mhzpacket = (bool)get_rx_desc_bw(pdesc);
	status->is_ht = (bool)get_rx_desc_rxht(pdesc);

	status->is_cck = RX_HAL_IS_CCK_RATE(status->rate);

	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + status->rx_drvinfo_size
			+ status->rx_bufshअगरt);

	अगर (status->crc)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (status->rx_is40mhzpacket)
		rx_status->bw = RATE_INFO_BW_40;

	अगर (status->is_ht)
		rx_status->encoding = RX_ENC_HT;

	rx_status->flag |= RX_FLAG_MACTIME_START;

	/* hw will set status->decrypted true, अगर it finds the
	 * frame is खोलो data frame or mgmt frame.
	 * So hw will not decryption robust managment frame
	 * क्रम IEEE80211w but still set status->decrypted
	 * true, so here we should set it back to undecrypted
	 * क्रम IEEE80211w frame, and mac80211 sw will help
	 * to decrypt it
	 */
	अगर (status->decrypted) अणु
		अगर ((!_ieee80211_is_robust_mgmt_frame(hdr)) &&
		    (ieee80211_has_रक्षित(hdr->frame_control)))
			rx_status->flag |= RX_FLAG_DECRYPTED;
		अन्यथा
			rx_status->flag &= ~RX_FLAG_DECRYPTED;
	पूर्ण

	/* rate_idx: index of data rate पूर्णांकo band's
	 * supported rates or MCS index अगर HT rates
	 * are use (RX_FLAG_HT)
	 * Notice: this is dअगरf with winकरोws define
	 */
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, status->is_ht,
						   false, status->rate);

	rx_status->maस_समय = status->बारtamp_low;
	अगर (phystatus == true) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_8723e *)(skb->data +
						     status->rx_bufshअगरt);

		translate_rx_संकेत_stuff(hw, skb, status, pdesc8, p_drvinfo);
	पूर्ण
	rx_status->संकेत = status->recvसंकेतघातer + 10;
	वापस true;
पूर्ण

व्योम rtl8723e_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_hdr *hdr, u8 *pdesc_tx,
			   u8 *txbd, काष्ठा ieee80211_tx_info *info,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा sk_buff *skb,
			   u8 hw_queue, काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool b_शेषadapter = true;
	/* bool b_trigger_ac = false; */
	u8 *pdesc8 = (u8 *)pdesc_tx;
	__le32 *pdesc = (__le32 *)pdesc8;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 fw_qsel = _rtl8723e_map_hwqueue_to_fwqueue(skb, hw_queue);
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
	अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
		bw_40 = mac->bw_40;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC) अणु
		अगर (sta)
			bw_40 = sta->ht_cap.cap &
				IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	पूर्ण

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	rtl_get_tcb_desc(hw, info, sta, skb, ptcb_desc);

	clear_pci_tx_desc_content(pdesc, माप(काष्ठा tx_desc_8723e));

	अगर (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) अणु
		firstseg = true;
		lastseg = true;
	पूर्ण

	अगर (firstseg) अणु
		set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);

		अगर (ptcb_desc->use_लघुgi || ptcb_desc->use_लघुpreamble)
			set_tx_desc_data_लघुgi(pdesc, 1);

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			set_tx_desc_agg_अवरोध(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		पूर्ण
		set_tx_desc_seq(pdesc, seq_number);

		set_tx_desc_rts_enable(pdesc,
				       ((ptcb_desc->rts_enable &&
					!ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_hw_rts_enable(pdesc,
					  ((ptcb_desc->rts_enable ||
					  ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_cts2self(pdesc,
				     ((ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_rts_stbc(pdesc,
				     ((ptcb_desc->rts_stbc) ? 1 : 0));

		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);
		set_tx_desc_rts_bw(pdesc, 0);
		set_tx_desc_rts_sc(pdesc, ptcb_desc->rts_sc);
		set_tx_desc_rts_लघु(pdesc,
				((ptcb_desc->rts_rate <= DESC92C_RATE54M) ?
				(ptcb_desc->rts_use_लघुpreamble ? 1 : 0)
				: (ptcb_desc->rts_use_लघुgi ? 1 : 0)));

		अगर (bw_40) अणु
			अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) अणु
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
		set_tx_desc_use_rate(pdesc, ptcb_desc->use_driver_rate ? 1 : 0);

		अगर (ieee80211_is_data_qos(fc)) अणु
			अगर (mac->rdg_en) अणु
				rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
					"Enable RDG function.\n");
				set_tx_desc_rdg_enable(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			पूर्ण
		पूर्ण
	पूर्ण

	set_tx_desc_first_seg(pdesc, (firstseg ? 1 : 0));
	set_tx_desc_last_seg(pdesc, (lastseg ? 1 : 0));

	set_tx_desc_tx_buffer_size(pdesc, (u16)skb->len);

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	अगर (rtlpriv->dm.useramask) अणु
		set_tx_desc_rate_id(pdesc, ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	पूर्ण अन्यथा अणु
		set_tx_desc_rate_id(pdesc, 0xC + ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->ratr_index);
	पूर्ण

	अगर ((!ieee80211_is_data_qos(fc)) && ppsc->fwctrl_lps) अणु
		set_tx_desc_hwseq_en_8723(pdesc, 1);
		/* set_tx_desc_hwseq_en(pdesc, 1); */
		/* set_tx_desc_pkt_id(pdesc, 8); */

		अगर (!b_शेषadapter)
			set_tx_desc_hwseq_sel_8723(pdesc, 1);
	/* set_tx_desc_qos(pdesc, 1); */
	पूर्ण

	set_tx_desc_more_frag(pdesc, (lastseg ? 0 : 1));

	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) अणु
		set_tx_desc_bmc(pdesc, 1);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl8723e_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
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

	set_tx_desc_tx_rate(pdesc, DESC92C_RATE1M);

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
		set_tx_desc_hwseq_en_8723(pdesc, 1);
		/* set_tx_desc_hwseq_en(pdesc, 1); */
		/* set_tx_desc_pkt_id(pdesc, 8); */
	पूर्ण

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content\n",
		      pdesc, TX_DESC_SIZE);
पूर्ण

व्योम rtl8723e_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8,
		       bool istx, u8 desc_name, u8 *val)
अणु
	__le32 *pdesc = (__le32 *)pdesc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			set_tx_desc_own(pdesc, 1);
			अवरोध;
		हाल HW_DESC_TX_NEXTDESC_ADDR:
			set_tx_desc_next_desc_address(pdesc, *(u32 *)val);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8723ae: ERR txdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_RXOWN:
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
			WARN_ONCE(true, "rtl8723ae: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl8723e_get_desc(काष्ठा ieee80211_hw *hw,
		      u8 *pdesc8, bool istx, u8 desc_name)
अणु
	u32 ret = 0;
	__le32 *pdesc = (__le32 *)pdesc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_tx_desc_own(pdesc);
			अवरोध;
		हाल HW_DESC_TXBUFF_ADDR:
			ret = get_tx_desc_tx_buffer_address(pdesc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8723ae: ERR txdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_rx_desc_own(pdesc);
			अवरोध;
		हाल HW_DESC_RXPKT_LEN:
			ret = get_rx_desc_pkt_len(pdesc);
			अवरोध;
		हाल HW_DESC_RXBUFF_ADDR:
			ret = get_rx_desc_buff_addr(pdesc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8723ae: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool rtl8723e_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw,
				u8 hw_queue, u16 index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u8 *entry = (u8 *)(&ring->desc[ring->idx]);
	u8 own = (u8)rtl8723e_get_desc(hw, entry, true, HW_DESC_OWN);

	/**
	 *beacon packet will only use the first
	 *descriptor defautly,and the own may not
	 *be cleared by the hardware
	 */
	अगर (own)
		वापस false;
	वापस true;
पूर्ण

व्योम rtl8723e_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (hw_queue == BEACON_QUEUE) अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG, BIT(4));
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG,
			       BIT(0) << (hw_queue));
	पूर्ण
पूर्ण
