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

अटल u8 _rtl92ee_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb, u8 hw_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc) || ieee80211_is_ctl(fc))
		वापस QSLT_MGNT;

	वापस skb->priority;
पूर्ण

अटल व्योम _rtl92ee_query_rxphystatus(काष्ठा ieee80211_hw *hw,
				       काष्ठा rtl_stats *pstatus, u8 *pdesc,
				       काष्ठा rx_fwinfo *p_drvinfo,
				       bool bpacket_match_bssid,
				       bool bpacket_toself,
				       bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा phy_status_rpt *p_phystrpt = (काष्ठा phy_status_rpt *)p_drvinfo;
	s8 rx_pwr_all, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
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
		/* CCK Driver info Structure is not the same as OFDM packet. */
		cck_agc_rpt = p_phystrpt->cck_agc_rpt_ofdm_cfosho_a;

		/* (1)Hardware करोes not provide RSSI क्रम CCK
		 * (2)PWDB, Average PWDB cacluated by
		 * hardware (क्रम rate adaptive)
		 */
		cck_highpwr = (u8)rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2,
						 BIT(9));

		lan_idx = ((cck_agc_rpt & 0xE0) >> 5);
		vga_idx = (cck_agc_rpt & 0x1f);
		चयन (lan_idx) अणु
		हाल 7: /*VGA_idx = 27~2*/
				अगर (vga_idx <= 27)
					rx_pwr_all = -100 + 2 * (27 - vga_idx);
				अन्यथा
					rx_pwr_all = -100;
				अवरोध;
		हाल 6: /*VGA_idx = 2~0*/
				rx_pwr_all = -48 + 2 * (2 - vga_idx);
				अवरोध;
		हाल 5: /*VGA_idx = 7~5*/
				rx_pwr_all = -42 + 2 * (7 - vga_idx);
				अवरोध;
		हाल 4: /*VGA_idx = 7~4*/
				rx_pwr_all = -36 + 2 * (7 - vga_idx);
				अवरोध;
		हाल 3: /*VGA_idx = 7~0*/
				rx_pwr_all = -24 + 2 * (7 - vga_idx);
				अवरोध;
		हाल 2: /*VGA_idx = 5~0*/
				अगर (cck_highpwr)
					rx_pwr_all = -12 + 2 * (5 - vga_idx);
				अन्यथा
					rx_pwr_all = -6 + 2 * (5 - vga_idx);
				अवरोध;
		हाल 1:
				rx_pwr_all = 8 - 2 * vga_idx;
				अवरोध;
		हाल 0:
				rx_pwr_all = 14 - 2 * vga_idx;
				अवरोध;
		शेष:
				rx_pwr_all = 0;
				अवरोध;
		पूर्ण
		rx_pwr_all += 16;
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);

		अगर (!cck_highpwr) अणु
			अगर (pwdb_all >= 80)
				pwdb_all = ((pwdb_all - 80) << 1) +
					   ((pwdb_all - 80) >> 1) + 80;
			अन्यथा अगर ((pwdb_all <= 78) && (pwdb_all >= 20))
				pwdb_all += 3;
			अगर (pwdb_all > 100)
				pwdb_all = 100;
		पूर्ण

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
		rx_pwr_all = ((p_phystrpt->cck_sig_qual_ofdm_pwdb_all >> 1)
			      & 0x7f) - 110;

		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstatus->rx_pwdb_all = pwdb_all;
		pstatus->bt_rx_rssi_percentage = pwdb_all;
		pstatus->rxघातer = rx_pwr_all;
		pstatus->recvसंकेतघातer = rx_pwr_all;

		/* (3)EVM of HT rate */
		अगर (pstatus->rate >= DESC_RATEMCS8 &&
		    pstatus->rate <= DESC_RATEMCS15)
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
					pstatus->संकेतquality = (u8)(evm &
								       0xff);
				pstatus->rx_mimo_संकेतquality[i] = (u8)(evm &
									  0xff);
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

अटल व्योम _rtl92ee_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
					       काष्ठा sk_buff *skb,
					       काष्ठा rtl_stats *pstatus,
					       u8 *pdesc,
					       काष्ठा rx_fwinfo *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	u8 *psaddr;
	__le16 fc;
	bool packet_matchbssid, packet_toself, packet_beacon;

	पंचांगp_buf = skb->data + pstatus->rx_drvinfo_size +
		  pstatus->rx_bufshअगरt + 24;

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
				(!pstatus->hwerror) && (!pstatus->crc) &&
				(!pstatus->icv));

	packet_toself = packet_matchbssid &&
			 (ether_addr_equal(praddr, rtlefuse->dev_addr));

	अगर (ieee80211_is_beacon(fc))
		packet_beacon = true;
	अन्यथा
		packet_beacon = false;

	अगर (packet_beacon && packet_matchbssid)
		rtl_priv(hw)->dm.dbginfo.num_qry_beacon_pkt++;

	अगर (packet_matchbssid && ieee80211_is_data_qos(hdr->frame_control) &&
	    !is_multicast_ether_addr(ieee80211_get_DA(hdr))) अणु
		काष्ठा ieee80211_qos_hdr *hdr_qos =
					    (काष्ठा ieee80211_qos_hdr *)पंचांगp_buf;
		u16 tid = le16_to_cpu(hdr_qos->qos_ctrl) & 0xf;

		अगर (tid != 0 && tid != 3)
			rtl_priv(hw)->dm.dbginfo.num_non_be_pkt++;
	पूर्ण

	_rtl92ee_query_rxphystatus(hw, pstatus, pdesc, p_drvinfo,
				   packet_matchbssid, packet_toself,
				   packet_beacon);
	rtl_process_phyinfo(hw, पंचांगp_buf, pstatus);
पूर्ण

अटल व्योम _rtl92ee_insert_emcontent(काष्ठा rtl_tcb_desc *ptcb_desc,
				      u8 *भवaddress8)
अणु
	u32 dwपंचांगp;
	__le32 *भवaddress = (__le32 *)भवaddress8;

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

bool rtl92ee_rx_query_desc(काष्ठा ieee80211_hw *hw,
			   काष्ठा rtl_stats *status,
			   काष्ठा ieee80211_rx_status *rx_status,
			   u8 *pdesc8, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rx_fwinfo *p_drvinfo;
	काष्ठा ieee80211_hdr *hdr;
	__le32 *pdesc = (__le32 *)pdesc8;
	u32 phystatus = get_rx_desc_physt(pdesc);
	u8 wake_match;

	अगर (get_rx_status_desc_rpt_sel(pdesc) == 0)
		status->packet_report_type = NORMAL_RX;
	अन्यथा
		status->packet_report_type = C2H_PACKET;
	status->length = (u16)get_rx_desc_pkt_len(pdesc);
	status->rx_drvinfo_size = (u8)get_rx_desc_drv_info_size(pdesc) *
				  RX_DRV_INFO_SIZE_UNIT;
	status->rx_bufshअगरt = (u8)(get_rx_desc_shअगरt(pdesc) & 0x03);
	status->icv = (u16)get_rx_desc_icv(pdesc);
	status->crc = (u16)get_rx_desc_crc32(pdesc);
	status->hwerror = (status->crc | status->icv);
	status->decrypted = !get_rx_desc_swdec(pdesc);
	status->rate = (u8)get_rx_desc_rxmcs(pdesc);
	status->isampdu = (bool)(get_rx_desc_paggr(pdesc) == 1);
	status->बारtamp_low = get_rx_desc_tsfl(pdesc);
	status->is_cck = RTL92EE_RX_HAL_IS_CCK_RATE(status->rate);

	status->macid = get_rx_desc_macid(pdesc);
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
				       status->rx_bufshअगरt + 24);

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
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo *)(skb->data +
						 status->rx_bufshअगरt + 24);

		_rtl92ee_translate_rx_संकेत_stuff(hw, skb, status, pdesc8,
						   p_drvinfo);
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

/*in Winकरोws, this == Rx_92EE_Interrupt*/
व्योम rtl92ee_rx_check_dma_ok(काष्ठा ieee80211_hw *hw, u8 *header_desc8,
			     u8 queue_index)
अणु
	u8 first_seg = 0;
	u8 last_seg = 0;
	u16 total_len = 0;
	u16 पढ़ो_cnt = 0;
	__le32 *header_desc = (__le32 *)header_desc8;

	अगर (header_desc == शून्य)
		वापस;

	total_len = (u16)get_rx_buffer_desc_total_length(header_desc);

	first_seg = (u8)get_rx_buffer_desc_fs(header_desc);

	last_seg = (u8)get_rx_buffer_desc_ls(header_desc);

	जबतक (total_len == 0 && first_seg == 0 && last_seg == 0) अणु
		पढ़ो_cnt++;
		total_len = (u16)get_rx_buffer_desc_total_length(header_desc);
		first_seg = (u8)get_rx_buffer_desc_fs(header_desc);
		last_seg = (u8)get_rx_buffer_desc_ls(header_desc);

		अगर (पढ़ो_cnt > 20)
			अवरोध;
	पूर्ण
पूर्ण

u16 rtl92ee_rx_desc_buff_reमुख्यed_cnt(काष्ठा ieee80211_hw *hw, u8 queue_index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 पढ़ो_poपूर्णांक, ग_लिखो_poपूर्णांक, remind_cnt;
	u32 पंचांगp_4byte;
	अटल bool start_rx;

	पंचांगp_4byte = rtl_पढ़ो_dword(rtlpriv, REG_RXQ_TXBD_IDX);
	पढ़ो_poपूर्णांक = (u16)((पंचांगp_4byte>>16) & 0x7ff);
	ग_लिखो_poपूर्णांक = (u16)(पंचांगp_4byte & 0x7ff);

	अगर (ग_लिखो_poपूर्णांक != rtlpci->rx_ring[queue_index].next_rx_rp) अणु
		rtl_dbg(rtlpriv, COMP_RXDESC, DBG_DMESG,
			"!!!write point is 0x%x, reg 0x3B4 value is 0x%x\n",
			ग_लिखो_poपूर्णांक, पंचांगp_4byte);
		पंचांगp_4byte = rtl_पढ़ो_dword(rtlpriv, REG_RXQ_TXBD_IDX);
		पढ़ो_poपूर्णांक = (u16)((पंचांगp_4byte>>16) & 0x7ff);
		ग_लिखो_poपूर्णांक = (u16)(पंचांगp_4byte & 0x7ff);
	पूर्ण

	अगर (पढ़ो_poपूर्णांक > 0)
		start_rx = true;
	अगर (!start_rx)
		वापस 0;

	remind_cnt = calc_fअगरo_space(पढ़ो_poपूर्णांक, ग_लिखो_poपूर्णांक,
				     RTL_PCI_MAX_RX_COUNT);

	अगर (remind_cnt == 0)
		वापस 0;

	rtlpci->rx_ring[queue_index].next_rx_rp = ग_लिखो_poपूर्णांक;

	वापस remind_cnt;
पूर्ण

अटल u16 get_desc_addr_fr_q_idx(u16 queue_index)
अणु
	u16 desc_address;

	चयन (queue_index) अणु
	हाल BK_QUEUE:
		desc_address = REG_BKQ_TXBD_IDX;
		अवरोध;
	हाल BE_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		अवरोध;
	हाल VI_QUEUE:
		desc_address = REG_VIQ_TXBD_IDX;
		अवरोध;
	हाल VO_QUEUE:
		desc_address = REG_VOQ_TXBD_IDX;
		अवरोध;
	हाल BEACON_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		अवरोध;
	हाल TXCMD_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		अवरोध;
	हाल MGNT_QUEUE:
		desc_address = REG_MGQ_TXBD_IDX;
		अवरोध;
	हाल HIGH_QUEUE:
		desc_address = REG_HI0Q_TXBD_IDX;
		अवरोध;
	हाल HCCA_QUEUE:
		desc_address = REG_BEQ_TXBD_IDX;
		अवरोध;
	शेष:
		desc_address = REG_BEQ_TXBD_IDX;
		अवरोध;
	पूर्ण
	वापस desc_address;
पूर्ण

u16 rtl92ee_get_available_desc(काष्ठा ieee80211_hw *hw, u8 q_idx)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 poपूर्णांक_dअगरf = 0;
	u16 current_tx_पढ़ो_poपूर्णांक, current_tx_ग_लिखो_poपूर्णांक;
	u32 पंचांगp_4byte;

	पंचांगp_4byte = rtl_पढ़ो_dword(rtlpriv,
				   get_desc_addr_fr_q_idx(q_idx));
	current_tx_पढ़ो_poपूर्णांक = (u16)((पंचांगp_4byte >> 16) & 0x0fff);
	current_tx_ग_लिखो_poपूर्णांक = (u16)((पंचांगp_4byte) & 0x0fff);

	poपूर्णांक_dअगरf = calc_fअगरo_space(current_tx_पढ़ो_poपूर्णांक,
				     current_tx_ग_लिखो_poपूर्णांक,
				     TX_DESC_NUM_92E);

	वापस poपूर्णांक_dअगरf;
पूर्ण

व्योम rtl92ee_pre_fill_tx_bd_desc(काष्ठा ieee80211_hw *hw,
				 u8 *tx_bd_desc8, u8 *desc8, u8 queue_index,
				 काष्ठा sk_buff *skb, dma_addr_t addr)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u32 pkt_len = skb->len;
	u16 desc_size = 40; /*tx desc size*/
	u32 psblen = 0;
	u16 tx_page_size;
	u32 total_packet_size;
	u16 current_bd_desc;
	u8 i;
	u16 real_desc_size = 0x28;
	u16	append_early_mode_size = 0;
	u8 segmentnum = 1 << (RTL8192EE_SEG_NUM + 1);
	dma_addr_t desc_dma_addr;
	bool dma64 = rtlpriv->cfg->mod_params->dma64;
	__le32 *desc = (__le32 *)desc8;
	__le32 *tx_bd_desc = (__le32 *)tx_bd_desc8;

	tx_page_size = 2;
	current_bd_desc = rtlpci->tx_ring[queue_index].cur_tx_wp;

	total_packet_size = desc_size+pkt_len;

	अगर (rtlpriv->rtlhal.earlymode_enable)	अणु
		अगर (queue_index < BEACON_QUEUE) अणु
			append_early_mode_size = 8;
			total_packet_size += append_early_mode_size;
		पूर्ण
	पूर्ण

	अगर (tx_page_size > 0) अणु
		psblen = (pkt_len + real_desc_size + append_early_mode_size) /
			 (tx_page_size * 128);

		अगर (psblen * (tx_page_size * 128) < total_packet_size)
			psblen += 1;
	पूर्ण

	/* tx desc addr */
	desc_dma_addr = rtlpci->tx_ring[queue_index].dma +
			(current_bd_desc * TX_DESC_SIZE);

	/* Reset */
	set_tx_buff_desc_len_0(tx_bd_desc, 0);
	set_tx_buff_desc_psb(tx_bd_desc, 0);
	set_tx_buff_desc_own(tx_bd_desc, 0);

	क्रम (i = 1; i < segmentnum; i++) अणु
		set_txbuffer_desc_len_with_offset(tx_bd_desc, i, 0);
		set_txbuffer_desc_amsdu_with_offset(tx_bd_desc, i, 0);
		set_txbuffer_desc_add_low_with_offset(tx_bd_desc, i, 0);
		set_txbuffer_desc_add_high_with_offset(tx_bd_desc, i, 0, dma64);
	पूर्ण

	/* Clear all status */
	clear_pci_tx_desc_content(desc, TX_DESC_SIZE);

	अगर (rtlpriv->rtlhal.earlymode_enable) अणु
		अगर (queue_index < BEACON_QUEUE) अणु
			/* This अगर needs braces */
			set_tx_buff_desc_len_0(tx_bd_desc, desc_size + 8);
		पूर्ण अन्यथा अणु
			set_tx_buff_desc_len_0(tx_bd_desc, desc_size);
		पूर्ण
	पूर्ण अन्यथा अणु
		set_tx_buff_desc_len_0(tx_bd_desc, desc_size);
	पूर्ण
	set_tx_buff_desc_psb(tx_bd_desc, psblen);
	set_tx_buff_desc_addr_low_0(tx_bd_desc, desc_dma_addr);
	set_tx_buff_desc_addr_high_0(tx_bd_desc, ((u64)desc_dma_addr >> 32),
				     dma64);

	set_txbuffer_desc_len_with_offset(tx_bd_desc, 1, pkt_len);
	/* करोn't using extendsion mode. */
	set_txbuffer_desc_amsdu_with_offset(tx_bd_desc, 1, 0);
	set_txbuffer_desc_add_low_with_offset(tx_bd_desc, 1, addr);
	set_txbuffer_desc_add_high_with_offset(tx_bd_desc, 1,
					       ((u64)addr >> 32), dma64);

	set_tx_desc_pkt_size(desc, (u16)(pkt_len));
	set_tx_desc_tx_buffer_size(desc, (u16)(pkt_len));
पूर्ण

व्योम rtl92ee_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc8,
			  u8 *pbd_desc_tx,
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
	u8 fw_qsel = _rtl92ee_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			    cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);
	bool lastseg = ((hdr->frame_control &
			   cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);
	dma_addr_t mapping;
	u8 bw_40 = 0;
	__le32 *pdesc = (__le32 *)pdesc8;

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
	mapping = dma_map_single(&rtlpci->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण

	अगर (pbd_desc_tx != शून्य)
		rtl92ee_pre_fill_tx_bd_desc(hw, pbd_desc_tx, pdesc8, hw_queue,
					    skb, mapping);

	अगर (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) अणु
		firstseg = true;
		lastseg = true;
	पूर्ण
	अगर (firstseg) अणु
		अगर (rtlhal->earlymode_enable) अणु
			set_tx_desc_pkt_offset(pdesc, 1);
			set_tx_desc_offset(pdesc,
					   USB_HWDESC_HEADER_LEN + EM_HDR_LEN);
			अगर (ptcb_desc->empkt_num) अणु
				rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
					"Insert 8 byte.pTcb->EMPktNum:%d\n",
					ptcb_desc->empkt_num);
				_rtl92ee_insert_emcontent(ptcb_desc,
							  (u8 *)(skb->data));
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);
		पूर्ण


		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);

		अगर (ieee80211_is_mgmt(fc)) अणु
			ptcb_desc->use_driver_rate = true;
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->ra.is_special_data) अणु
				ptcb_desc->use_driver_rate = true;
				set_tx_desc_tx_rate(pdesc, DESC_RATE11M);
			पूर्ण अन्यथा अणु
				ptcb_desc->use_driver_rate = false;
			पूर्ण
		पूर्ण

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			set_tx_desc_agg_enable(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		पूर्ण
		set_tx_desc_seq(pdesc, seq_number);
		set_tx_desc_rts_enable(pdesc,
				       ((ptcb_desc->rts_enable &&
					 !ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_hw_rts_enable(pdesc, 0);
		set_tx_desc_cts2self(pdesc,
				     ((ptcb_desc->cts_enable) ? 1 : 0));

		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);
		set_tx_desc_rts_sc(pdesc, ptcb_desc->rts_sc);
		set_tx_desc_rts_लघु(pdesc,
				((ptcb_desc->rts_rate <= DESC_RATE54M) ?
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
				set_tx_desc_tx_sub_carrier(pdesc,
							   mac->cur_40_prime_sc);
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_data_bw(pdesc, 0);
			set_tx_desc_tx_sub_carrier(pdesc, 0);
		पूर्ण

		set_tx_desc_linip(pdesc, 0);
		अगर (sta) अणु
			u8 ampdu_density = sta->ht_cap.ampdu_density;

			set_tx_desc_ampdu_density(pdesc, ampdu_density);
		पूर्ण
		अगर (info->control.hw_key) अणु
			काष्ठा ieee80211_key_conf *key = info->control.hw_key;

			चयन (key->cipher) अणु
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
		set_tx_desc_disable_fb(pdesc,
				       ptcb_desc->disable_ratefallback ? 1 : 0);
		set_tx_desc_use_rate(pdesc, ptcb_desc->use_driver_rate ? 1 : 0);

		/*set_tx_desc_pwr_status(pdesc, pwr_status);*/
		/* Set TxRate and RTSRate in TxDesc  */
		/* This prevent Tx initial rate of new-coming packets */
		/* from being overwritten by retried  packet rate.*/
		अगर (!ptcb_desc->use_driver_rate) अणु
			/*set_tx_desc_rts_rate(pdesc, 0x08); */
			/* set_tx_desc_tx_rate(pdesc, 0x0b); */
		पूर्ण
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
	set_tx_desc_tx_buffer_address(pdesc, mapping);
	अगर (rtlpriv->dm.useramask) अणु
		set_tx_desc_rate_id(pdesc, ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	पूर्ण अन्यथा अणु
		set_tx_desc_rate_id(pdesc, 0xC + ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->ratr_index);
	पूर्ण

	set_tx_desc_more_frag(pdesc, (lastseg ? 0 : 1));
	अगर (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) अणु
		set_tx_desc_bmc(pdesc, 1);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl92ee_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
			     u8 *pdesc8, bool firstseg,
			     bool lastseg, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 fw_queue = QSLT_BEACON;
	dma_addr_t mapping = dma_map_single(&rtlpci->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);
	u8 txdesc_len = 40;
	__le32 *pdesc = (__le32 *)pdesc8;

	अगर (dma_mapping_error(&rtlpci->pdev->dev, mapping)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	clear_pci_tx_desc_content(pdesc, txdesc_len);

	अगर (firstseg)
		set_tx_desc_offset(pdesc, txdesc_len);

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

	set_tx_desc_offset(pdesc, 40);

	set_tx_desc_use_rate(pdesc, 1);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content\n", pdesc, txdesc_len);
पूर्ण

व्योम rtl92ee_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8, bool istx,
		      u8 desc_name, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 q_idx = *val;
	bool dma64 = rtlpriv->cfg->mod_params->dma64;
	__le32 *pdesc = (__le32 *)pdesc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_TX_NEXTDESC_ADDR:
			set_tx_desc_next_desc_address(pdesc, *(u32 *)val);
			अवरोध;
		हाल HW_DESC_OWN:अणु
			काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
			काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[q_idx];
			u16 max_tx_desc = ring->entries;

			अगर (q_idx == BEACON_QUEUE) अणु
				ring->cur_tx_wp = 0;
				ring->cur_tx_rp = 0;
				set_tx_buff_desc_own(pdesc, 1);
				वापस;
			पूर्ण

			/* make sure tx desc is available by caller */
			ring->cur_tx_wp = ((ring->cur_tx_wp + 1) % max_tx_desc);

			rtl_ग_लिखो_word(rtlpriv,
				       get_desc_addr_fr_q_idx(q_idx),
				       ring->cur_tx_wp);
		पूर्ण
		अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_name) अणु
		हाल HW_DESC_RX_PREPARE:
			set_rx_buffer_desc_ls(pdesc, 0);
			set_rx_buffer_desc_fs(pdesc, 0);
			set_rx_buffer_desc_total_length(pdesc, 0);

			set_rx_buffer_desc_data_length(pdesc,
						       MAX_RECEIVE_BUFFER_SIZE +
						       RX_DESC_SIZE);

			set_rx_buffer_physical_low(pdesc, (*(dma_addr_t *)val) &
						   DMA_BIT_MASK(32));
			set_rx_buffer_physical_high(pdesc,
						    ((u64)(*(dma_addr_t *)val)
						    >> 32),
						    dma64);
			अवरोध;
		हाल HW_DESC_RXERO:
			set_rx_desc_eor(pdesc, 1);
			अवरोध;
		शेष:
			WARN_ONCE(true,
				  "rtl8192ee: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl92ee_get_desc(काष्ठा ieee80211_hw *hw,
		     u8 *pdesc8, bool istx, u8 desc_name)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u64 ret = 0;
	bool dma64 = rtlpriv->cfg->mod_params->dma64;
	__le32 *pdesc = (__le32 *)pdesc8;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_tx_desc_own(pdesc);
			अवरोध;
		हाल HW_DESC_TXBUFF_ADDR:
			ret = get_txbuffer_desc_addr_low(pdesc, 1);
			ret |= (u64)get_txbuffer_desc_addr_high(pdesc, 1,
								dma64) << 32;
			अवरोध;
		शेष:
			WARN_ONCE(true,
				  "rtl8192ee: ERR txdesc :%d not processed\n",
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
				  "rtl8192ee: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool rtl92ee_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw, u8 hw_queue, u16 index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 पढ़ो_poपूर्णांक, ग_लिखो_poपूर्णांक;
	bool ret = false;
	अटल u8 stop_report_cnt;
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];

	अणु
		u16 cur_tx_rp;
		u32 पंचांगpu32;

		पंचांगpu32 =
		  rtl_पढ़ो_dword(rtlpriv,
				 get_desc_addr_fr_q_idx(hw_queue));
		cur_tx_rp = (u16)((पंचांगpu32 >> 16) & 0x0fff);

		/* करोn't need to update ring->cur_tx_wp */
		ring->cur_tx_rp = cur_tx_rp;
	पूर्ण

	पढ़ो_poपूर्णांक = ring->cur_tx_rp;
	ग_लिखो_poपूर्णांक = ring->cur_tx_wp;

	अगर (ग_लिखो_poपूर्णांक > पढ़ो_poपूर्णांक) अणु
		अगर (index < ग_लिखो_poपूर्णांक && index >= पढ़ो_poपूर्णांक)
			ret = false;
		अन्यथा
			ret = true;
	पूर्ण अन्यथा अगर (ग_लिखो_poपूर्णांक < पढ़ो_poपूर्णांक) अणु
		अगर (index > ग_लिखो_poपूर्णांक && index < पढ़ो_poपूर्णांक)
			ret = true;
		अन्यथा
			ret = false;
	पूर्ण अन्यथा अणु
		अगर (index != पढ़ो_poपूर्णांक)
			ret = true;
	पूर्ण

	अगर (hw_queue == BEACON_QUEUE)
		ret = true;

	अगर (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    rtlpriv->psc.rfoff_reason > RF_CHANGE_BY_PS)
		ret = true;

	अगर (hw_queue < BEACON_QUEUE) अणु
		अगर (!ret)
			stop_report_cnt++;
		अन्यथा
			stop_report_cnt = 0;
	पूर्ण

	वापस ret;
पूर्ण

व्योम rtl92ee_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
पूर्ण
