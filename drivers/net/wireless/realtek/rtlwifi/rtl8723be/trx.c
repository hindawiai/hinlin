<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../stats.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "trx.h"
#समावेश "led.h"
#समावेश "dm.h"
#समावेश "fw.h"

अटल u8 _rtl8723be_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb, u8 hw_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस QSLT_MGNT;

	वापस skb->priority;
पूर्ण

अटल व्योम _rtl8723be_query_rxphystatus(काष्ठा ieee80211_hw *hw,
					 काष्ठा rtl_stats *pstatus,
					 __le32 *pdesc,
					 काष्ठा rx_fwinfo_8723be *p_drvinfo,
					 bool bpacket_match_bssid,
					 bool bpacket_toself,
					 bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा phy_status_rpt *p_phystrpt = (काष्ठा phy_status_rpt *)p_drvinfo;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all, pwdb_all_bt = 0;
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
		u8 cck_agc_rpt;

		cck_agc_rpt = p_phystrpt->cck_agc_rpt_ofdm_cfosho_a;

		/* (1)Hardware करोes not provide RSSI क्रम CCK */
		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, BIT(9));

		lan_idx = ((cck_agc_rpt & 0xE0) >> 5);
		vga_idx = (cck_agc_rpt & 0x1f);

		चयन (lan_idx) अणु
		/* 46 53 73 95 201301231630 */
		/* 46 53 77 99 201301241630 */
		हाल 6:
			rx_pwr_all = -34 - (2 * vga_idx);
			अवरोध;
		हाल 4:
			rx_pwr_all = -14 - (2 * vga_idx);
			अवरोध;
		हाल 1:
			rx_pwr_all = 6 - (2 * vga_idx);
			अवरोध;
		हाल 0:
			rx_pwr_all = 16 - (2 * vga_idx);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		अगर (pwdb_all > 100)
			pwdb_all = 100;

		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->bt_rx_rssi_percentage = pwdb_all;
		pstatus->recvसंकेतघातer = rx_pwr_all;

		/* (3) Get Signal Quality (EVM) */
		अगर (bpacket_match_bssid) अणु
			u8 sq, sq_rpt;
			अगर (pstatus->rx_pwdb_all > 40) अणु
				sq = 100;
			पूर्ण अन्यथा अणु
				sq_rpt = p_phystrpt->cck_sig_qual_ofdm_pwdb_all;
				अगर (sq_rpt > 64)
					sq = 0;
				अन्यथा अगर (sq_rpt < 20)
					sq = 100;
				अन्यथा
					sq = ((64 - sq_rpt) * 100) / 44;
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

			rx_pwr[i] = ((p_phystrpt->path_agc[i].gain & 0x3f) * 2)
				    - 110;

			pstatus->rx_pwr[i] = rx_pwr[i];
			/* Translate DBM to percentage. */
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;

			pstatus->rx_mimo_संकेतstrength[i] = (u8)rssi;
		पूर्ण

		/* (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		rx_pwr_all = ((p_phystrpt->cck_sig_qual_ofdm_pwdb_all >> 1) &
			     0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pwdb_all_bt = pwdb_all;
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->bt_rx_rssi_percentage = pwdb_all_bt;
		pstatus->rxघातer = rx_pwr_all;
		pstatus->recvसंकेतघातer = rx_pwr_all;

		/* (3)EVM of HT rate */
		अगर (pstatus->rate >= DESC92C_RATEMCS8 &&
		    pstatus->rate <= DESC92C_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(
						p_phystrpt->stream_rxevm[i]);

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

		अगर (bpacket_match_bssid) अणु
			क्रम (i = RF90_PATH_A; i <= RF90_PATH_B; i++)
				rtl_priv(hw)->dm.cfo_tail[i] =
					(पूर्णांक)p_phystrpt->path_cfotail[i];

			अगर (rtl_priv(hw)->dm.packet_count == 0xffffffff)
				rtl_priv(hw)->dm.packet_count = 0;
			अन्यथा
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
पूर्ण

अटल व्योम _rtl8723be_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
					काष्ठा sk_buff *skb,
					काष्ठा rtl_stats *pstatus,
					__le32 *pdesc,
					काष्ठा rx_fwinfo_8723be *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	u8 *psaddr;
	u16 fc, type;
	bool packet_matchbssid, packet_toself, packet_beacon;

	पंचांगp_buf = skb->data + pstatus->rx_drvinfo_size + pstatus->rx_bufshअगरt;

	hdr = (काष्ठा ieee80211_hdr *)पंचांगp_buf;
	fc = le16_to_cpu(hdr->frame_control);
	type = WLAN_FC_GET_TYPE(hdr->frame_control);
	praddr = hdr->addr1;
	psaddr = ieee80211_get_SA(hdr);
	स_नकल(pstatus->psaddr, psaddr, ETH_ALEN);

	packet_matchbssid = ((IEEE80211_FTYPE_CTL != type) &&
	     (ether_addr_equal(mac->bssid, (fc & IEEE80211_FCTL_TODS) ?
				  hdr->addr1 : (fc & IEEE80211_FCTL_FROMDS) ?
				  hdr->addr2 : hdr->addr3)) &&
				  (!pstatus->hwerror) &&
				  (!pstatus->crc) && (!pstatus->icv));

	packet_toself = packet_matchbssid &&
	    (ether_addr_equal(praddr, rtlefuse->dev_addr));

	/* YP: packet_beacon is not initialized,
	 * this assignment is neccesary,
	 * otherwise it counld be true in this हाल
	 * the situation is much worse in Kernel 3.10
	 */
	अगर (ieee80211_is_beacon(hdr->frame_control))
		packet_beacon = true;
	अन्यथा
		packet_beacon = false;

	अगर (packet_beacon && packet_matchbssid)
		rtl_priv(hw)->dm.dbginfo.num_qry_beacon_pkt++;

	_rtl8723be_query_rxphystatus(hw, pstatus, pdesc, p_drvinfo,
				     packet_matchbssid,
				     packet_toself,
				     packet_beacon);

	rtl_process_phyinfo(hw, पंचांगp_buf, pstatus);
पूर्ण

अटल व्योम _rtl8723be_insert_emcontent(काष्ठा rtl_tcb_desc *ptcb_desc,
					__le32 *भवaddress)
अणु
	u32 dwपंचांगp = 0;
	स_रखो(भवaddress, 0, 8);

	set_earlymode_pktnum(भवaddress, ptcb_desc->empkt_num);
	अगर (ptcb_desc->empkt_num == 1) अणु
		dwपंचांगp = ptcb_desc->empkt_len[0];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[0];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0) + 4;
		dwपंचांगp += ptcb_desc->empkt_len[1];
	पूर्ण
	set_earlymode_len0(भवaddress, dwपंचांगp);

	अगर (ptcb_desc->empkt_num <= 3) अणु
		dwपंचांगp = ptcb_desc->empkt_len[2];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[2];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0) + 4;
		dwपंचांगp += ptcb_desc->empkt_len[3];
	पूर्ण
	set_earlymode_len1(भवaddress, dwपंचांगp);
	अगर (ptcb_desc->empkt_num <= 5) अणु
		dwपंचांगp = ptcb_desc->empkt_len[4];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[4];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0) + 4;
		dwपंचांगp += ptcb_desc->empkt_len[5];
	पूर्ण
	set_earlymode_len2_1(भवaddress, dwपंचांगp & 0xF);
	set_earlymode_len2_2(भवaddress, dwपंचांगp >> 4);
	अगर (ptcb_desc->empkt_num <= 7) अणु
		dwपंचांगp = ptcb_desc->empkt_len[6];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[6];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0) + 4;
		dwपंचांगp += ptcb_desc->empkt_len[7];
	पूर्ण
	set_earlymode_len3(भवaddress, dwपंचांगp);
	अगर (ptcb_desc->empkt_num <= 9) अणु
		dwपंचांगp = ptcb_desc->empkt_len[8];
	पूर्ण अन्यथा अणु
		dwपंचांगp = ptcb_desc->empkt_len[8];
		dwपंचांगp += ((dwपंचांगp % 4) ? (4 - dwपंचांगp % 4) : 0) + 4;
		dwपंचांगp += ptcb_desc->empkt_len[9];
	पूर्ण
	set_earlymode_len4(भवaddress, dwपंचांगp);
पूर्ण

bool rtl8723be_rx_query_desc(काष्ठा ieee80211_hw *hw,
			     काष्ठा rtl_stats *status,
			     काष्ठा ieee80211_rx_status *rx_status,
			     u8 *pdesc8, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rx_fwinfo_8723be *p_drvinfo;
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
	status->rx_is40mhzpacket = (bool)get_rx_desc_bw(pdesc);
	status->bandwidth = (u8)get_rx_desc_bw(pdesc);
	status->macid = get_rx_desc_macid(pdesc);
	status->is_ht = (bool)get_rx_desc_rxht(pdesc);

	status->is_cck = RX_HAL_IS_CCK_RATE(status->rate);

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

	hdr = (काष्ठा ieee80211_hdr *)(skb->data + status->rx_drvinfo_size +
				       status->rx_bufshअगरt);

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
	 */
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, status->is_ht,
						   false, status->rate);

	rx_status->maस_समय = status->बारtamp_low;
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_8723be *)(skb->data +
							status->rx_bufshअगरt);

		_rtl8723be_translate_rx_संकेत_stuff(hw, skb, status,
						     pdesc, p_drvinfo);
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

व्योम rtl8723be_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_hdr *hdr, u8 *pdesc8,
			    u8 *txbd, काष्ठा ieee80211_tx_info *info,
			    काष्ठा ieee80211_sta *sta, काष्ठा sk_buff *skb,
			    u8 hw_queue, काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtlwअगरi_tx_info *tx_info = rtl_tx_skb_cb_info(skb);
	__le32 *pdesc = (__le32 *)pdesc8;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	अचिन्हित पूर्णांक buf_len = 0;
	अचिन्हित पूर्णांक skb_len = skb->len;
	u8 fw_qsel = _rtl8723be_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			    cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);
	bool lastseg = ((hdr->frame_control &
			   cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);
	dma_addr_t mapping;
	u8 bw_40 = 0;
	u8 लघु_gi = 0;

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
	/* reserve 8 byte क्रम AMPDU early mode */
	अगर (rtlhal->earlymode_enable) अणु
		skb_push(skb, EM_HDR_LEN);
		स_रखो(skb->data, 0, EM_HDR_LEN);
	पूर्ण
	buf_len = skb->len;
	mapping = dma_map_single(&rtlpci->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "DMA mapping error\n");
		वापस;
	पूर्ण
	clear_pci_tx_desc_content(pdesc, माप(काष्ठा tx_desc_8723be));
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
				_rtl8723be_insert_emcontent(ptcb_desc,
							    (__le32 *)(skb->data));
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);
		पूर्ण


		/* ptcb_desc->use_driver_rate = true; */
		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);
		अगर (ptcb_desc->hw_rate > DESC92C_RATEMCS0)
			लघु_gi = (ptcb_desc->use_लघुgi) ? 1 : 0;
		अन्यथा
			लघु_gi = (ptcb_desc->use_लघुpreamble) ? 1 : 0;

		set_tx_desc_data_लघुgi(pdesc, लघु_gi);

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			set_tx_desc_agg_enable(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		पूर्ण
		set_tx_desc_seq(pdesc, seq_number);
		set_tx_desc_rts_enable(pdesc, ((ptcb_desc->rts_enable &&
						!ptcb_desc->cts_enable) ?
						1 : 0));
		set_tx_desc_hw_rts_enable(pdesc, 0);
		set_tx_desc_cts2self(pdesc, ((ptcb_desc->cts_enable) ?
					      1 : 0));

		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);

		set_tx_desc_rts_sc(pdesc, ptcb_desc->rts_sc);
		set_tx_desc_rts_लघु(pdesc,
			((ptcb_desc->rts_rate <= DESC92C_RATE54M) ?
			 (ptcb_desc->rts_use_लघुpreamble ? 1 : 0) :
			 (ptcb_desc->rts_use_लघुgi ? 1 : 0)));

		अगर (ptcb_desc->tx_enable_sw_calc_duration)
			set_tx_desc_nav_use_hdr(pdesc, 1);

		अगर (bw_40) अणु
			अगर (ptcb_desc->packet_bw == HT_CHANNEL_WIDTH_20_40) अणु
				set_tx_desc_data_bw(pdesc, 1);
				set_tx_desc_tx_sub_carrier(pdesc, 3);
			पूर्ण अन्यथा अणु
				set_tx_desc_data_bw(pdesc, 0);
				set_tx_desc_tx_sub_carrier(pdesc, mac->cur_40_prime_sc);
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_data_bw(pdesc, 0);
			set_tx_desc_tx_sub_carrier(pdesc, 0);
		पूर्ण

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

		/* Set TxRate and RTSRate in TxDesc  */
		/* This prevent Tx initial rate of new-coming packets */
		/* from being overwritten by retried  packet rate.*/
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
	set_tx_desc_tx_buffer_size(pdesc, (u16)buf_len);
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

	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl8723be_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw, u8 *pdesc8,
			       bool firstseg, bool lastseg,
			       काष्ठा sk_buff *skb)
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

	set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);

	set_tx_desc_tx_rate(pdesc, DESC92C_RATE1M);

	set_tx_desc_seq(pdesc, 0);

	set_tx_desc_linip(pdesc, 0);

	set_tx_desc_queue_sel(pdesc, fw_queue);

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_tx_buffer_size(pdesc, (u16)(skb->len));

	set_tx_desc_tx_buffer_address(pdesc, mapping);

	set_tx_desc_rate_id(pdesc, 0);
	set_tx_desc_macid(pdesc, 0);

	set_tx_desc_own(pdesc, 1);

	set_tx_desc_pkt_size(pdesc, (u16)(skb->len));

	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);

	set_tx_desc_use_rate(pdesc, 1);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content\n", pdesc, TX_DESC_SIZE);
पूर्ण

व्योम rtl8723be_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8,
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
			WARN_ONCE(true, "rtl8723be: ERR txdesc :%d not processed\n",
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
			WARN_ONCE(true, "rtl8723be: ERR rxdesc :%d not process\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl8723be_get_desc(काष्ठा ieee80211_hw *hw,
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
			WARN_ONCE(true, "rtl8723be: ERR txdesc :%d not process\n",
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
			WARN_ONCE(true, "rtl8723be: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool rtl8723be_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw,
				 u8 hw_queue, u16 index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u8 *entry = (u8 *)(&ring->desc[ring->idx]);
	u8 own = (u8)rtl8723be_get_desc(hw, entry, true, HW_DESC_OWN);

	/*beacon packet will only use the first
	 *descriptor defautly,and the own may not
	 *be cleared by the hardware
	 */
	अगर (own)
		वापस false;
	वापस true;
पूर्ण

व्योम rtl8723be_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (hw_queue == BEACON_QUEUE) अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG, BIT(4));
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG,
			       BIT(0) << (hw_queue));
	पूर्ण
पूर्ण
