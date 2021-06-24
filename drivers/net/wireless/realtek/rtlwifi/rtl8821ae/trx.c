<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../stats.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "trx.h"
#समावेश "led.h"
#समावेश "dm.h"
#समावेश "phy.h"
#समावेश "fw.h"

अटल u8 _rtl8821ae_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb, u8 hw_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस QSLT_MGNT;

	वापस skb->priority;
पूर्ण

अटल u16 odm_cfo(s8 value)
अणु
	पूर्णांक ret_val;

	अगर (value < 0) अणु
		ret_val = 0 - value;
		ret_val = (ret_val << 1) + (ret_val >> 1);
		/* set bit12 as 1 क्रम negative cfo */
		ret_val = ret_val | BIT(12);
	पूर्ण अन्यथा अणु
		ret_val = value;
		ret_val = (ret_val << 1) + (ret_val >> 1);
	पूर्ण
	वापस ret_val;
पूर्ण

अटल u8 _rtl8821ae_evm_dbm_jaguar(s8 value)
अणु
	s8 ret_val = value;

	/* -33dB~0dB to 33dB ~ 0dB*/
	अगर (ret_val == -128)
		ret_val = 127;
	अन्यथा अगर (ret_val < 0)
		ret_val = 0 - ret_val;

	ret_val  = ret_val >> 1;
	वापस ret_val;
पूर्ण

अटल व्योम query_rxphystatus(काष्ठा ieee80211_hw *hw,
			      काष्ठा rtl_stats *pstatus, __le32 *pdesc,
			      काष्ठा rx_fwinfo_8821ae *p_drvinfo,
			      bool bpacket_match_bssid,
			      bool bpacket_toself, bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा phy_status_rpt *p_phystrpt = (काष्ठा phy_status_rpt *)p_drvinfo;
	काष्ठा rtl_dm *rtldm = rtl_dm(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, evmdbm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck = pstatus->is_cck;
	u8 lan_idx, vga_idx;

	/* Record it क्रम next packet processing */
	pstatus->packet_matchbssid = bpacket_match_bssid;
	pstatus->packet_toself = bpacket_toself;
	pstatus->packet_beacon = packet_beacon;
	pstatus->rx_mimo_संकेतquality[0] = -1;
	pstatus->rx_mimo_संकेतquality[1] = -1;

	अगर (is_cck) अणु
		u8 cck_highpwr;
		u8 cck_agc_rpt;

		cck_agc_rpt = p_phystrpt->cfosho[0];

		/* (1)Hardware करोes not provide RSSI क्रम CCK
		 * (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		cck_highpwr = (u8)rtlphy->cck_high_घातer;

		lan_idx = ((cck_agc_rpt & 0xE0) >> 5);
		vga_idx = (cck_agc_rpt & 0x1f);
		अगर (rtlpriv->rtlhal.hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			चयन (lan_idx) अणु
			हाल 7:
				अगर (vga_idx <= 27)
					/*VGA_idx = 27~2*/
					rx_pwr_all = -100 + 2*(27-vga_idx);
				अन्यथा
					rx_pwr_all = -100;
				अवरोध;
			हाल 6:
				/*VGA_idx = 2~0*/
				rx_pwr_all = -48 + 2*(2-vga_idx);
				अवरोध;
			हाल 5:
				/*VGA_idx = 7~5*/
				rx_pwr_all = -42 + 2*(7-vga_idx);
				अवरोध;
			हाल 4:
				/*VGA_idx = 7~4*/
				rx_pwr_all = -36 + 2*(7-vga_idx);
				अवरोध;
			हाल 3:
				/*VGA_idx = 7~0*/
				rx_pwr_all = -24 + 2*(7-vga_idx);
				अवरोध;
			हाल 2:
				अगर (cck_highpwr)
					/*VGA_idx = 5~0*/
					rx_pwr_all = -12 + 2*(5-vga_idx);
				अन्यथा
					rx_pwr_all = -6 + 2*(5-vga_idx);
				अवरोध;
			हाल 1:
				rx_pwr_all = 8-2*vga_idx;
				अवरोध;
			हाल 0:
				rx_pwr_all = 14-2*vga_idx;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			rx_pwr_all += 6;
			pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
			अगर (!cck_highpwr) अणु
				अगर (pwdb_all >= 80)
					pwdb_all =
					  ((pwdb_all - 80)<<1) +
					 ((pwdb_all - 80)>>1) + 80;
				अन्यथा अगर ((pwdb_all <= 78) && (pwdb_all >= 20))
					pwdb_all += 3;
				अगर (pwdb_all > 100)
					pwdb_all = 100;
			पूर्ण
		पूर्ण अन्यथा अणु /* 8821 */
			s8 pout = -6;

			चयन (lan_idx) अणु
			हाल 5:
				rx_pwr_all = pout - 32 - (2*vga_idx);
					अवरोध;
			हाल 4:
				rx_pwr_all = pout - 24 - (2*vga_idx);
					अवरोध;
			हाल 2:
				rx_pwr_all = pout - 11 - (2*vga_idx);
					अवरोध;
			हाल 1:
				rx_pwr_all = pout + 5 - (2*vga_idx);
					अवरोध;
			हाल 0:
				rx_pwr_all = pout + 21 - (2*vga_idx);
					अवरोध;
			पूर्ण
			pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		पूर्ण

		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->recvसंकेतघातer = rx_pwr_all;

		/* (3) Get Signal Quality (EVM) */
		अगर (bpacket_match_bssid) अणु
			u8 sq;

			अगर (pstatus->rx_pwdb_all > 40) अणु
				sq = 100;
			पूर्ण अन्यथा अणु
				sq = p_phystrpt->pwdb_all;
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
		/* (1)Get RSSI क्रम HT rate */
		क्रम (i = RF90_PATH_A; i < RF6052_MAX_PATH; i++) अणु
			/* we will judge RF RX path now. */
			अगर (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = (p_phystrpt->gain_trsw[i] & 0x7f) - 110;

			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;

			/* Get Rx snr value in DB */
			pstatus->rx_snr[i] = p_phystrpt->rxsnr[i] / 2;
			rtlpriv->stats.rx_snr_db[i] = p_phystrpt->rxsnr[i] / 2;

			pstatus->cfo_लघु[i] = odm_cfo(p_phystrpt->cfosho[i]);
			pstatus->cfo_tail[i] = odm_cfo(p_phystrpt->cfotail[i]);
			/* Record Signal Strength क्रम next packet */
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
		अगर ((pstatus->is_ht && pstatus->rate >= DESC_RATEMCS8 &&
		     pstatus->rate <= DESC_RATEMCS15) ||
		    (pstatus->is_vht &&
		     pstatus->rate >= DESC_RATEVHT2SS_MCS0 &&
		     pstatus->rate <= DESC_RATEVHT2SS_MCS9))
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(p_phystrpt->rxevm[i]);
			evmdbm = _rtl8821ae_evm_dbm_jaguar(p_phystrpt->rxevm[i]);

			अगर (bpacket_match_bssid) अणु
				/* Fill value in RFD, Get the first
				 * spatial stream only
				 */
				अगर (i == 0)
					pstatus->संकेतquality = evm;
				pstatus->rx_mimo_संकेतquality[i] = evm;
				pstatus->rx_mimo_evm_dbm[i] = evmdbm;
			पूर्ण
		पूर्ण
		अगर (bpacket_match_bssid) अणु
			क्रम (i = RF90_PATH_A; i <= RF90_PATH_B; i++)
				rtl_priv(hw)->dm.cfo_tail[i] =
					(s8)p_phystrpt->cfotail[i];

			rtl_priv(hw)->dm.packet_count++;
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
	/*HW antenna भागersity*/
	rtldm->fat_table.antsel_rx_keep_0 = p_phystrpt->antidx_anta;
	rtldm->fat_table.antsel_rx_keep_1 = p_phystrpt->antidx_antb;
पूर्ण

अटल व्योम translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
				      काष्ठा sk_buff *skb,
				      काष्ठा rtl_stats *pstatus, __le32 *pdesc,
				      काष्ठा rx_fwinfo_8821ae *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	u8 *psaddr;
	__le16 fc;
	bool packet_matchbssid, packet_toself, packet_beacon;

	पंचांगp_buf = skb->data + pstatus->rx_drvinfo_size + pstatus->rx_bufshअगरt;

	hdr = (काष्ठा ieee80211_hdr *)पंचांगp_buf;
	fc = hdr->frame_control;
	praddr = hdr->addr1;
	psaddr = ieee80211_get_SA(hdr);
	ether_addr_copy(pstatus->psaddr, psaddr);

	packet_matchbssid = (!ieee80211_is_ctl(fc) &&
			     (ether_addr_equal(mac->bssid,
					       ieee80211_has_tods(fc) ?
					       hdr->addr1 :
					       ieee80211_has_fromds(fc) ?
					       hdr->addr2 : hdr->addr3)) &&
			      (!pstatus->hwerror) &&
			      (!pstatus->crc) && (!pstatus->icv));

	packet_toself = packet_matchbssid &&
	    (ether_addr_equal(praddr, rtlefuse->dev_addr));

	अगर (ieee80211_is_beacon(hdr->frame_control))
		packet_beacon = true;
	अन्यथा
		packet_beacon = false;

	अगर (packet_beacon && packet_matchbssid)
		rtl_priv(hw)->dm.dbginfo.num_qry_beacon_pkt++;

	अगर (packet_matchbssid &&
	    ieee80211_is_data_qos(hdr->frame_control) &&
	    !is_multicast_ether_addr(ieee80211_get_DA(hdr))) अणु
		काष्ठा ieee80211_qos_hdr *hdr_qos =
			(काष्ठा ieee80211_qos_hdr *)पंचांगp_buf;
		u16 tid = le16_to_cpu(hdr_qos->qos_ctrl) & 0xf;

		अगर (tid != 0 && tid != 3)
			rtl_priv(hw)->dm.dbginfo.num_non_be_pkt++;
	पूर्ण

	query_rxphystatus(hw, pstatus, pdesc, p_drvinfo,
			  packet_matchbssid, packet_toself,
			  packet_beacon);
	/*_rtl8821ae_smart_antenna(hw, pstatus); */
	rtl_process_phyinfo(hw, पंचांगp_buf, pstatus);
पूर्ण

अटल व्योम rtl8821ae_insert_emcontent(काष्ठा rtl_tcb_desc *ptcb_desc,
				       __le32 *भवaddress)
अणु
	u32 dwपंचांगp = 0;

	स_रखो(भवaddress, 0, 8);

	set_earlymode_pktnum(भवaddress, ptcb_desc->empkt_num);
	अगर (ptcb_desc->empkt_num == 1) अणु
		dwपंचांगp = ptcb_desc->empkt_len[0];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[0];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0)+4;
		dwपंचांगp += ptcb_desc->empkt_len[1];
	पूर्ण
	set_earlymode_len0(भवaddress, dwपंचांगp);

	अगर (ptcb_desc->empkt_num <= 3) अणु
		dwपंचांगp = ptcb_desc->empkt_len[2];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[2];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0)+4;
		dwपंचांगp += ptcb_desc->empkt_len[3];
	पूर्ण
	set_earlymode_len1(भवaddress, dwपंचांगp);
	अगर (ptcb_desc->empkt_num <= 5) अणु
		dwपंचांगp = ptcb_desc->empkt_len[4];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[4];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0)+4;
		dwपंचांगp += ptcb_desc->empkt_len[5];
	पूर्ण
	set_earlymode_len2_1(भवaddress, dwपंचांगp & 0xF);
	set_earlymode_len2_2(भवaddress, dwपंचांगp >> 4);
	अगर (ptcb_desc->empkt_num <= 7) अणु
		dwपंचांगp = ptcb_desc->empkt_len[6];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[6];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0)+4;
		dwपंचांगp += ptcb_desc->empkt_len[7];
	पूर्ण
	set_earlymode_len3(भवaddress, dwपंचांगp);
	अगर (ptcb_desc->empkt_num <= 9) अणु
		dwपंचांगp = ptcb_desc->empkt_len[8];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[8];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0)+4;
		dwपंचांगp += ptcb_desc->empkt_len[9];
	पूर्ण
	set_earlymode_len4(भवaddress, dwपंचांगp);
पूर्ण

अटल bool rtl8821ae_get_rxdesc_is_ht(काष्ठा ieee80211_hw *hw, __le32 *pdesc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 rx_rate = 0;

	rx_rate = get_rx_desc_rxmcs(pdesc);

	rtl_dbg(rtlpriv, COMP_RXDESC, DBG_LOUD, "rx_rate=0x%02x.\n", rx_rate);

	अगर ((rx_rate >= DESC_RATEMCS0) && (rx_rate <= DESC_RATEMCS15))
		वापस true;
	वापस false;
पूर्ण

अटल bool rtl8821ae_get_rxdesc_is_vht(काष्ठा ieee80211_hw *hw, __le32 *pdesc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 rx_rate = 0;

	rx_rate = get_rx_desc_rxmcs(pdesc);

	rtl_dbg(rtlpriv, COMP_RXDESC, DBG_LOUD, "rx_rate=0x%02x.\n", rx_rate);

	अगर (rx_rate >= DESC_RATEVHT1SS_MCS0)
		वापस true;
	वापस false;
पूर्ण

अटल u8 rtl8821ae_get_rx_vht_nss(काष्ठा ieee80211_hw *hw, __le32 *pdesc)
अणु
	u8 rx_rate = 0;
	u8 vht_nss = 0;

	rx_rate = get_rx_desc_rxmcs(pdesc);
	अगर ((rx_rate >= DESC_RATEVHT1SS_MCS0) &&
	    (rx_rate <= DESC_RATEVHT1SS_MCS9))
		vht_nss = 1;
	अन्यथा अगर ((rx_rate >= DESC_RATEVHT2SS_MCS0) &&
		 (rx_rate <= DESC_RATEVHT2SS_MCS9))
		vht_nss = 2;

	वापस vht_nss;
पूर्ण

bool rtl8821ae_rx_query_desc(काष्ठा ieee80211_hw *hw,
			     काष्ठा rtl_stats *status,
			     काष्ठा ieee80211_rx_status *rx_status,
			     u8 *pdesc8, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rx_fwinfo_8821ae *p_drvinfo;
	काष्ठा ieee80211_hdr *hdr;
	u8 wake_match;
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
	status->isfirst_ampdu = (bool)(get_rx_desc_paggr(pdesc) == 1);
	status->बारtamp_low = get_rx_desc_tsfl(pdesc);
	status->rx_packet_bw = get_rx_desc_bw(pdesc);
	status->macid = get_rx_desc_macid(pdesc);
	status->is_लघु_gi = !(bool)get_rx_desc_splcp(pdesc);
	status->is_ht = rtl8821ae_get_rxdesc_is_ht(hw, pdesc);
	status->is_vht = rtl8821ae_get_rxdesc_is_vht(hw, pdesc);
	status->vht_nss = rtl8821ae_get_rx_vht_nss(hw, pdesc);
	status->is_cck = RTL8821AE_RX_HAL_IS_CCK_RATE(status->rate);

	rtl_dbg(rtlpriv, COMP_RXDESC, DBG_LOUD,
		"rx_packet_bw=%s,is_ht %d, is_vht %d, vht_nss=%d,is_short_gi %d.\n",
		(status->rx_packet_bw == 2) ? "80M" :
		(status->rx_packet_bw == 1) ? "40M" : "20M",
		status->is_ht, status->is_vht, status->vht_nss,
		status->is_लघु_gi);

	अगर (get_rx_status_desc_rpt_sel(pdesc))
		status->packet_report_type = C2H_PACKET;
	अन्यथा
		status->packet_report_type = NORMAL_RX;

	अगर (get_rx_status_desc_pattern_match(pdesc))
		wake_match = BIT(2);
	अन्यथा अगर (get_rx_status_desc_magic_match(pdesc))
		wake_match = BIT(1);
	अन्यथा अगर (get_rx_status_desc_unicast_match(pdesc))
		wake_match = BIT(0);
	अन्यथा
		wake_match = 0;

	अगर (wake_match)
		rtl_dbg(rtlpriv, COMP_RXDESC, DBG_LOUD,
			"GGGGGGGGGGGGGet Wakeup Packet!! WakeMatch=%d\n",
			wake_match);
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;

	hdr = (काष्ठा ieee80211_hdr *)(skb->data +
	      status->rx_drvinfo_size + status->rx_bufshअगरt);

	अगर (status->crc)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;

	अगर (status->rx_packet_bw == HT_CHANNEL_WIDTH_20_40)
		rx_status->bw = RATE_INFO_BW_40;
	अन्यथा अगर (status->rx_packet_bw == HT_CHANNEL_WIDTH_80)
		rx_status->bw = RATE_INFO_BW_80;
	अगर (status->is_ht)
		rx_status->encoding = RX_ENC_HT;
	अगर (status->is_vht)
		rx_status->encoding = RX_ENC_VHT;

	अगर (status->is_लघु_gi)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	rx_status->nss = status->vht_nss;
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
	 */
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, status->is_ht,
						   status->is_vht,
						   status->rate);

	rx_status->maस_समय = status->बारtamp_low;
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_8821ae *)(skb->data +
			    status->rx_bufshअगरt);

		translate_rx_संकेत_stuff(hw, skb, status, pdesc, p_drvinfo);
	पूर्ण
	rx_status->संकेत = status->recvसंकेतघातer + 10;
	अगर (status->packet_report_type == TX_REPORT2) अणु
		status->macid_valid_entry[0] =
		  get_rx_rpt2_desc_macid_valid_1(pdesc);
		status->macid_valid_entry[1] =
		  get_rx_rpt2_desc_macid_valid_2(pdesc);
	पूर्ण
	वापस true;
पूर्ण

अटल u8 rtl8821ae_bw_mapping(काष्ठा ieee80211_hw *hw,
			       काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 bw_setting_of_desc = 0;

	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
		"%s, current_chan_bw %d, packet_bw %d\n",
		__func__,
		rtlphy->current_chan_bw, ptcb_desc->packet_bw);

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) अणु
		अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_80)
			bw_setting_of_desc = 2;
		अन्यथा अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40)
			bw_setting_of_desc = 1;
		अन्यथा
			bw_setting_of_desc = 0;
	पूर्ण अन्यथा अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
		अगर ((ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) ||
		    (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_80))
			bw_setting_of_desc = 1;
		अन्यथा
			bw_setting_of_desc = 0;
	पूर्ण अन्यथा अणु
		bw_setting_of_desc = 0;
	पूर्ण
	वापस bw_setting_of_desc;
पूर्ण

अटल u8 rtl8821ae_sc_mapping(काष्ठा ieee80211_hw *hw,
			       काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	u8 sc_setting_of_desc = 0;

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) अणु
		अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_80) अणु
			sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
		पूर्ण अन्यथा अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) अणु
			अगर (mac->cur_80_prime_sc ==
			    HAL_PRIME_CHNL_OFFSET_LOWER)
				sc_setting_of_desc =
					VHT_DATA_SC_40_LOWER_OF_80MHZ;
			अन्यथा अगर (mac->cur_80_prime_sc ==
				 HAL_PRIME_CHNL_OFFSET_UPPER)
				sc_setting_of_desc =
					VHT_DATA_SC_40_UPPER_OF_80MHZ;
			अन्यथा
				rtl_dbg(rtlpriv, COMP_SEND, DBG_LOUD,
					"%s: Not Correct Primary40MHz Setting\n",
					__func__);
		पूर्ण अन्यथा अणु
			अगर ((mac->cur_40_prime_sc ==
			     HAL_PRIME_CHNL_OFFSET_LOWER) &&
			    (mac->cur_80_prime_sc  ==
			     HAL_PRIME_CHNL_OFFSET_LOWER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_LOWEST_OF_80MHZ;
			अन्यथा अगर ((mac->cur_40_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER) &&
				 (mac->cur_80_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_LOWER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_LOWER_OF_80MHZ;
			अन्यथा अगर ((mac->cur_40_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_LOWER) &&
				 (mac->cur_80_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_UPPER_OF_80MHZ;
			अन्यथा अगर ((mac->cur_40_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER) &&
				 (mac->cur_80_prime_sc ==
				  HAL_PRIME_CHNL_OFFSET_UPPER))
				sc_setting_of_desc =
					VHT_DATA_SC_20_UPPERST_OF_80MHZ;
			अन्यथा
				rtl_dbg(rtlpriv, COMP_SEND, DBG_LOUD,
					"%s: Not Correct Primary40MHz Setting\n",
					__func__);
		पूर्ण
	पूर्ण अन्यथा अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
		अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) अणु
			sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
		पूर्ण अन्यथा अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20) अणु
			अगर (mac->cur_40_prime_sc ==
				HAL_PRIME_CHNL_OFFSET_UPPER) अणु
				sc_setting_of_desc =
					VHT_DATA_SC_20_UPPER_OF_80MHZ;
			पूर्ण अन्यथा अगर (mac->cur_40_prime_sc ==
				HAL_PRIME_CHNL_OFFSET_LOWER)अणु
				sc_setting_of_desc =
					VHT_DATA_SC_20_LOWER_OF_80MHZ;
			पूर्ण अन्यथा अणु
				sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		sc_setting_of_desc = VHT_DATA_SC_DONOT_CARE;
	पूर्ण

	वापस sc_setting_of_desc;
पूर्ण

व्योम rtl8821ae_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_hdr *hdr, u8 *pdesc8, u8 *txbd,
			    काष्ठा ieee80211_tx_info *info,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb,
			    u8 hw_queue, काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtlwअगरi_tx_info *tx_info = rtl_tx_skb_cb_info(skb);
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	अचिन्हित पूर्णांक buf_len = 0;
	अचिन्हित पूर्णांक skb_len = skb->len;
	u8 fw_qsel = _rtl8821ae_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			  cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);
	bool lastseg = ((hdr->frame_control &
			 cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);
	dma_addr_t mapping;
	u8 लघु_gi = 0;
	bool पंचांगp_bool;
	__le32 *pdesc = (__le32 *)pdesc8;

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;
	rtl_get_tcb_desc(hw, info, sta, skb, ptcb_desc);
	/* reserve 8 byte क्रम AMPDU early mode */
	अगर (rtlhal->earlymode_enable) अणु
		skb_push(skb, EM_HDR_LEN);
		स_रखो(skb->data, 0, EM_HDR_LEN);
	पूर्ण
	buf_len = skb->len;
	mapping = dma_map_single(&rtlpci->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	clear_pci_tx_desc_content(pdesc, माप(काष्ठा tx_desc_8821ae));
	अगर (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) अणु
		firstseg = true;
		lastseg = true;
	पूर्ण
	अगर (firstseg) अणु
		अगर (rtlhal->earlymode_enable) अणु
			set_tx_desc_pkt_offset(pdesc, 1);
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN +
					   EM_HDR_LEN);
			अगर (ptcb_desc->empkt_num) अणु
				rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
					"Insert 8 byte.pTcb->EMPktNum:%d\n",
					ptcb_desc->empkt_num);
				rtl8821ae_insert_emcontent(ptcb_desc,
							   (__le32 *)skb->data);
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);
		पूर्ण


		/* ptcb_desc->use_driver_rate = true; */
		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);
		अगर (ptcb_desc->hw_rate > DESC_RATEMCS0)
			लघु_gi = (ptcb_desc->use_लघुgi) ? 1 : 0;
		अन्यथा
			लघु_gi = (ptcb_desc->use_लघुpreamble) ? 1 : 0;

		set_tx_desc_data_लघुgi(pdesc, लघु_gi);

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			set_tx_desc_agg_enable(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x1f);
		पूर्ण
		set_tx_desc_seq(pdesc, seq_number);
		set_tx_desc_rts_enable(pdesc,
				       ((ptcb_desc->rts_enable &&
					!ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_hw_rts_enable(pdesc, 0);
		set_tx_desc_cts2self(pdesc, ((ptcb_desc->cts_enable) ? 1 : 0));

		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);
		set_tx_desc_rts_sc(pdesc, ptcb_desc->rts_sc);
		पंचांगp_bool = ((ptcb_desc->rts_rate <= DESC_RATE54M) ?
			    (ptcb_desc->rts_use_लघुpreamble ? 1 : 0) :
			    (ptcb_desc->rts_use_लघुgi ? 1 : 0));
		set_tx_desc_rts_लघु(pdesc, पंचांगp_bool);

		अगर (ptcb_desc->tx_enable_sw_calc_duration)
			set_tx_desc_nav_use_hdr(pdesc, 1);

		set_tx_desc_data_bw(pdesc,
				    rtl8821ae_bw_mapping(hw, ptcb_desc));

		set_tx_desc_tx_sub_carrier(pdesc,
					   rtl8821ae_sc_mapping(hw, ptcb_desc));

		set_tx_desc_linip(pdesc, 0);
		set_tx_desc_pkt_size(pdesc, (u16)skb_len);
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

		set_tx_desc_queue_sel(pdesc, fw_qsel);
		set_tx_desc_data_rate_fb_limit(pdesc, 0x1F);
		set_tx_desc_rts_rate_fb_limit(pdesc, 0xF);
		set_tx_desc_disable_fb(pdesc, ptcb_desc->disable_ratefallback ?
				       1 : 0);
		set_tx_desc_use_rate(pdesc, ptcb_desc->use_driver_rate ? 1 : 0);

		अगर (ieee80211_is_data_qos(fc)) अणु
			अगर (mac->rdg_en) अणु
				rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
					"Enable RDG function.\n");
				set_tx_desc_rdg_enable(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			पूर्ण
		पूर्ण
		/* tx report */
		rtl_set_tx_report(ptcb_desc, pdesc8, hw, tx_info);
	पूर्ण

	set_tx_desc_first_seg(pdesc, (firstseg ? 1 : 0));
	set_tx_desc_last_seg(pdesc, (lastseg ? 1 : 0));
	set_tx_desc_tx_buffer_size(pdesc, buf_len);
	set_tx_desc_tx_buffer_address(pdesc, mapping);
	/* अगर (rtlpriv->dm.useramask) अणु */
	अगर (1) अणु
		set_tx_desc_rate_id(pdesc, ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	पूर्ण अन्यथा अणु
		set_tx_desc_rate_id(pdesc, 0xC + ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	पूर्ण
	अगर (!ieee80211_is_data_qos(fc))  अणु
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_hwseq_sel(pdesc, 0);
	पूर्ण
	set_tx_desc_more_frag(pdesc, (lastseg ? 0 : 1));
	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) अणु
		set_tx_desc_bmc(pdesc, 1);
	पूर्ण

	rtl8821ae_dm_set_tx_ant_by_tx_info(hw, pdesc8, ptcb_desc->mac_id);
	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl8821ae_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
			       u8 *pdesc8, bool firstseg,
			       bool lastseg, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 fw_queue = QSLT_BEACON;
	__le32 *pdesc = (__le32 *)pdesc8;

	dma_addr_t mapping = dma_map_single(&rtlpci->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);

	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	clear_pci_tx_desc_content(pdesc, TX_DESC_SIZE);

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_pkt_size(pdesc, (u16)(skb->len));

	set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

	set_tx_desc_use_rate(pdesc, 1);
	set_tx_desc_tx_rate(pdesc, DESC_RATE1M);
	set_tx_desc_disable_fb(pdesc, 1);

	set_tx_desc_data_bw(pdesc, 0);

	set_tx_desc_hwseq_en(pdesc, 1);

	set_tx_desc_queue_sel(pdesc, fw_queue);

	set_tx_desc_tx_buffer_size(pdesc, skb->len);

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	set_tx_desc_macid(pdesc, 0);

	set_tx_desc_own(pdesc, 1);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content\n",
		      pdesc8, TX_DESC_SIZE);
पूर्ण

व्योम rtl8821ae_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8,
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
			WARN_ONCE(true,
				  "rtl8821ae: ERR txdesc :%d not processed\n",
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
			WARN_ONCE(true,
				  "rtl8821ae: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl8821ae_get_desc(काष्ठा ieee80211_hw *hw,
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
			WARN_ONCE(true,
				  "rtl8821ae: ERR txdesc :%d not processed\n",
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
			WARN_ONCE(true,
				  "rtl8821ae: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool rtl8821ae_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw,
				 u8 hw_queue, u16 index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u8 *entry = (u8 *)(&ring->desc[ring->idx]);
	u8 own = (u8)rtl8821ae_get_desc(hw, entry, true, HW_DESC_OWN);

	/**
	 *beacon packet will only use the first
	 *descriptor defautly,and the own may not
	 *be cleared by the hardware
	 */
	अगर (own)
		वापस false;
	वापस true;
पूर्ण

व्योम rtl8821ae_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (hw_queue == BEACON_QUEUE) अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG, BIT(4));
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG,
			       BIT(0) << (hw_queue));
	पूर्ण
पूर्ण
