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

अटल u8 _rtl92de_map_hwqueue_to_fwqueue(काष्ठा sk_buff *skb, u8 hw_queue)
अणु
	__le16 fc = rtl_get_fc(skb);

	अगर (unlikely(ieee80211_is_beacon(fc)))
		वापस QSLT_BEACON;
	अगर (ieee80211_is_mgmt(fc))
		वापस QSLT_MGNT;

	वापस skb->priority;
पूर्ण

अटल दीर्घ _rtl92de_translate_todbm(काष्ठा ieee80211_hw *hw,
				     u8 संकेत_strength_index)
अणु
	दीर्घ संकेत_घातer;

	संकेत_घातer = (दीर्घ)((संकेत_strength_index + 1) >> 1);
	संकेत_घातer -= 95;
	वापस संकेत_घातer;
पूर्ण

अटल व्योम _rtl92de_query_rxphystatus(काष्ठा ieee80211_hw *hw,
				       काष्ठा rtl_stats *pstats,
				       काष्ठा rx_desc_92d *pdesc,
				       काष्ठा rx_fwinfo_92d *p_drvinfo,
				       bool packet_match_bssid,
				       bool packet_toself,
				       bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	काष्ठा phy_sts_cck_8192d *cck_buf;
	s8 rx_pwr_all, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool is_cck_rate;

	is_cck_rate = RX_HAL_IS_CCK_RATE(pdesc->rxmcs);
	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_toself = packet_toself;
	pstats->packet_beacon = packet_beacon;
	pstats->is_cck = is_cck_rate;
	pstats->rx_mimo_sig_qual[0] = -1;
	pstats->rx_mimo_sig_qual[1] = -1;

	अगर (is_cck_rate) अणु
		u8 report, cck_highpwr;
		cck_buf = (काष्ठा phy_sts_cck_8192d *)p_drvinfo;
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
		rtlpriv->dm.rfpath_rxenable[0] = true;
		rtlpriv->dm.rfpath_rxenable[1] = true;
		क्रम (i = RF90_PATH_A; i < RF6052_MAX_PATH; i++) अणु
			अगर (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;
			rx_pwr[i] = ((p_drvinfo->gain_trsw[i] & 0x3f) * 2)
				    - 110;
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;
			rtlpriv->stats.rx_snr_db[i] =
					 (दीर्घ)(p_drvinfo->rxsnr[i] / 2);
			अगर (packet_match_bssid)
				pstats->rx_mimo_संकेतstrength[i] = (u8) rssi;
		पूर्ण
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 106;
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->rxघातer = rx_pwr_all;
		pstats->recvसंकेतघातer = rx_pwr_all;
		अगर (pdesc->rxht && pdesc->rxmcs >= DESC_RATEMCS8 &&
		    pdesc->rxmcs <= DESC_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;
		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);
			अगर (packet_match_bssid) अणु
				अगर (i == 0)
					pstats->संकेतquality =
						 (u8)(evm & 0xff);
				pstats->rx_mimo_sig_qual[i] =
						 (u8)(evm & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (is_cck_rate)
		pstats->संकेतstrength = (u8)(rtl_संकेत_scale_mapping(hw,
				pwdb_all));
	अन्यथा अगर (rf_rx_num != 0)
		pstats->संकेतstrength = (u8)(rtl_संकेत_scale_mapping(hw,
				total_rssi /= rf_rx_num));
पूर्ण

अटल व्योम rtl92d_loop_over_paths(काष्ठा ieee80211_hw *hw,
				   काष्ठा rtl_stats *pstats)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 rfpath;

	क्रम (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
	     rfpath++) अणु
		अगर (rtlpriv->stats.rx_rssi_percentage[rfpath] == 0) अणु
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    pstats->rx_mimo_संकेतstrength[rfpath];

		पूर्ण
		अगर (pstats->rx_mimo_संकेतstrength[rfpath] >
		    rtlpriv->stats.rx_rssi_percentage[rfpath]) अणु
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    ((rtlpriv->stats.rx_rssi_percentage[rfpath] *
			      (RX_SMOOTH_FACTOR - 1)) +
			     (pstats->rx_mimo_संकेतstrength[rfpath])) /
			    (RX_SMOOTH_FACTOR);
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    rtlpriv->stats.rx_rssi_percentage[rfpath] + 1;
		पूर्ण अन्यथा अणु
			rtlpriv->stats.rx_rssi_percentage[rfpath] =
			    ((rtlpriv->stats.rx_rssi_percentage[rfpath] *
			      (RX_SMOOTH_FACTOR - 1)) +
			     (pstats->rx_mimo_संकेतstrength[rfpath])) /
			    (RX_SMOOTH_FACTOR);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_process_ui_rssi(काष्ठा ieee80211_hw *hw,
				     काष्ठा rtl_stats *pstats)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 last_rssi, पंचांगpval;

	अगर (pstats->packet_toself || pstats->packet_beacon) अणु
		rtlpriv->stats.rssi_calculate_cnt++;
		अगर (rtlpriv->stats.ui_rssi.total_num++ >=
		    PHY_RSSI_SLID_WIN_MAX) अणु
			rtlpriv->stats.ui_rssi.total_num =
						 PHY_RSSI_SLID_WIN_MAX;
			last_rssi = rtlpriv->stats.ui_rssi.elements[
				rtlpriv->stats.ui_rssi.index];
			rtlpriv->stats.ui_rssi.total_val -= last_rssi;
		पूर्ण
		rtlpriv->stats.ui_rssi.total_val += pstats->संकेतstrength;
		rtlpriv->stats.ui_rssi.elements
			[rtlpriv->stats.ui_rssi.index++] =
			pstats->संकेतstrength;
		अगर (rtlpriv->stats.ui_rssi.index >= PHY_RSSI_SLID_WIN_MAX)
			rtlpriv->stats.ui_rssi.index = 0;
		पंचांगpval = rtlpriv->stats.ui_rssi.total_val /
			rtlpriv->stats.ui_rssi.total_num;
		rtlpriv->stats.संकेत_strength = _rtl92de_translate_todbm(hw,
			(u8) पंचांगpval);
		pstats->rssi = rtlpriv->stats.संकेत_strength;
	पूर्ण
	अगर (!pstats->is_cck && pstats->packet_toself)
		rtl92d_loop_over_paths(hw, pstats);
पूर्ण

अटल व्योम _rtl92de_update_rxसंकेतstatistics(काष्ठा ieee80211_hw *hw,
					       काष्ठा rtl_stats *pstats)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक weighting = 0;

	अगर (rtlpriv->stats.recv_संकेत_घातer == 0)
		rtlpriv->stats.recv_संकेत_घातer = pstats->recvसंकेतघातer;
	अगर (pstats->recvसंकेतघातer > rtlpriv->stats.recv_संकेत_घातer)
		weighting = 5;
	अन्यथा अगर (pstats->recvसंकेतघातer < rtlpriv->stats.recv_संकेत_घातer)
		weighting = (-5);
	rtlpriv->stats.recv_संकेत_घातer = (rtlpriv->stats.recv_संकेत_घातer *
		5 + pstats->recvसंकेतघातer + weighting) / 6;
पूर्ण

अटल व्योम _rtl92de_process_pwdb(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_stats *pstats)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ undec_sm_pwdb;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC	||
		mac->opmode == NL80211_IFTYPE_AP)
		वापस;
	अन्यथा
		undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;

	अगर (pstats->packet_toself || pstats->packet_beacon) अणु
		अगर (undec_sm_pwdb < 0)
			undec_sm_pwdb = pstats->rx_pwdb_all;
		अगर (pstats->rx_pwdb_all > (u32) undec_sm_pwdb) अणु
			undec_sm_pwdb = (((undec_sm_pwdb) *
			      (RX_SMOOTH_FACTOR - 1)) +
			      (pstats->rx_pwdb_all)) / (RX_SMOOTH_FACTOR);
			undec_sm_pwdb = undec_sm_pwdb + 1;
		पूर्ण अन्यथा अणु
			undec_sm_pwdb = (((undec_sm_pwdb) *
			      (RX_SMOOTH_FACTOR - 1)) +
			      (pstats->rx_pwdb_all)) / (RX_SMOOTH_FACTOR);
		पूर्ण
		rtlpriv->dm.undec_sm_pwdb = undec_sm_pwdb;
		_rtl92de_update_rxसंकेतstatistics(hw, pstats);
	पूर्ण
पूर्ण

अटल व्योम rtl92d_loop_over_streams(काष्ठा ieee80211_hw *hw,
				     काष्ठा rtl_stats *pstats)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक stream;

	क्रम (stream = 0; stream < 2; stream++) अणु
		अगर (pstats->rx_mimo_sig_qual[stream] != -1) अणु
			अगर (rtlpriv->stats.rx_evm_percentage[stream] == 0) अणु
				rtlpriv->stats.rx_evm_percentage[stream] =
				    pstats->rx_mimo_sig_qual[stream];
			पूर्ण
			rtlpriv->stats.rx_evm_percentage[stream] =
			    ((rtlpriv->stats.rx_evm_percentage[stream]
			      * (RX_SMOOTH_FACTOR - 1)) +
			     (pstats->rx_mimo_sig_qual[stream] * 1)) /
			    (RX_SMOOTH_FACTOR);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_process_ui_link_quality(काष्ठा ieee80211_hw *hw,
					     काष्ठा rtl_stats *pstats)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 last_evm, पंचांगpval;

	अगर (pstats->संकेतquality == 0)
		वापस;
	अगर (pstats->packet_toself || pstats->packet_beacon) अणु
		अगर (rtlpriv->stats.ui_link_quality.total_num++ >=
		    PHY_LINKQUALITY_SLID_WIN_MAX) अणु
			rtlpriv->stats.ui_link_quality.total_num =
			    PHY_LINKQUALITY_SLID_WIN_MAX;
			last_evm = rtlpriv->stats.ui_link_quality.elements[
				rtlpriv->stats.ui_link_quality.index];
			rtlpriv->stats.ui_link_quality.total_val -= last_evm;
		पूर्ण
		rtlpriv->stats.ui_link_quality.total_val +=
						 pstats->संकेतquality;
		rtlpriv->stats.ui_link_quality.elements[
			rtlpriv->stats.ui_link_quality.index++] =
						 pstats->संकेतquality;
		अगर (rtlpriv->stats.ui_link_quality.index >=
		    PHY_LINKQUALITY_SLID_WIN_MAX)
			rtlpriv->stats.ui_link_quality.index = 0;
		पंचांगpval = rtlpriv->stats.ui_link_quality.total_val /
		    rtlpriv->stats.ui_link_quality.total_num;
		rtlpriv->stats.संकेत_quality = पंचांगpval;
		rtlpriv->stats.last_sigstrength_inpercent = पंचांगpval;
		rtl92d_loop_over_streams(hw, pstats);
	पूर्ण
पूर्ण

अटल व्योम _rtl92de_process_phyinfo(काष्ठा ieee80211_hw *hw,
				     u8 *buffer,
				     काष्ठा rtl_stats *pcurrent_stats)
अणु

	अगर (!pcurrent_stats->packet_matchbssid &&
	    !pcurrent_stats->packet_beacon)
		वापस;

	_rtl92de_process_ui_rssi(hw, pcurrent_stats);
	_rtl92de_process_pwdb(hw, pcurrent_stats);
	_rtl92de_process_ui_link_quality(hw, pcurrent_stats);
पूर्ण

अटल व्योम _rtl92de_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
					       काष्ठा sk_buff *skb,
					       काष्ठा rtl_stats *pstats,
					       काष्ठा rx_desc_92d *pdesc,
					       काष्ठा rx_fwinfo_92d *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	u16 type, cfc;
	__le16 fc;
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
	_rtl92de_query_rxphystatus(hw, pstats, pdesc, p_drvinfo,
				   packet_matchbssid, packet_toself,
				   packet_beacon);
	_rtl92de_process_phyinfo(hw, पंचांगp_buf, pstats);
पूर्ण

bool rtl92de_rx_query_desc(काष्ठा ieee80211_hw *hw,	काष्ठा rtl_stats *stats,
		काष्ठा ieee80211_rx_status *rx_status,
		u8 *pdesc8, काष्ठा sk_buff *skb)
अणु
	__le32 *pdesc = (__le32 *)pdesc8;
	काष्ठा rx_fwinfo_92d *p_drvinfo;
	u32 phystatus = get_rx_desc_physt(pdesc);

	stats->length = (u16)get_rx_desc_pkt_len(pdesc);
	stats->rx_drvinfo_size = (u8)get_rx_desc_drv_info_size(pdesc) *
				 RX_DRV_INFO_SIZE_UNIT;
	stats->rx_bufshअगरt = (u8)(get_rx_desc_shअगरt(pdesc) & 0x03);
	stats->icv = (u16)get_rx_desc_icv(pdesc);
	stats->crc = (u16)get_rx_desc_crc32(pdesc);
	stats->hwerror = (stats->crc | stats->icv);
	stats->decrypted = !get_rx_desc_swdec(pdesc);
	stats->rate = (u8)get_rx_desc_rxmcs(pdesc);
	stats->लघुpreamble = (u16)get_rx_desc_splcp(pdesc);
	stats->isampdu = (bool)(get_rx_desc_paggr(pdesc) == 1);
	stats->isfirst_ampdu = (bool)((get_rx_desc_paggr(pdesc) == 1) &&
				      (get_rx_desc_faggr(pdesc) == 1));
	stats->बारtamp_low = get_rx_desc_tsfl(pdesc);
	stats->rx_is40mhzpacket = (bool)get_rx_desc_bw(pdesc);
	stats->is_ht = (bool)get_rx_desc_rxht(pdesc);
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;
	अगर (get_rx_desc_crc32(pdesc))
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	अगर (!get_rx_desc_swdec(pdesc))
		rx_status->flag |= RX_FLAG_DECRYPTED;
	अगर (get_rx_desc_bw(pdesc))
		rx_status->bw = RATE_INFO_BW_40;
	अगर (get_rx_desc_rxht(pdesc))
		rx_status->encoding = RX_ENC_HT;
	rx_status->flag |= RX_FLAG_MACTIME_START;
	अगर (stats->decrypted)
		rx_status->flag |= RX_FLAG_DECRYPTED;
	rx_status->rate_idx = rtlwअगरi_rate_mapping(hw, stats->is_ht,
						   false, stats->rate);
	rx_status->maस_समय = get_rx_desc_tsfl(pdesc);
	अगर (phystatus) अणु
		p_drvinfo = (काष्ठा rx_fwinfo_92d *)(skb->data +
						     stats->rx_bufshअगरt);
		_rtl92de_translate_rx_संकेत_stuff(hw,
						   skb, stats,
						   (काष्ठा rx_desc_92d *)pdesc,
						   p_drvinfo);
	पूर्ण
	/*rx_status->qual = stats->संकेत; */
	rx_status->संकेत = stats->recvसंकेतघातer + 10;
	वापस true;
पूर्ण

अटल व्योम _rtl92de_insert_emcontent(काष्ठा rtl_tcb_desc *ptcb_desc,
				      u8 *भवaddress8)
अणु
	__le32 *भवaddress = (__le32 *)भवaddress8;

	स_रखो(भवaddress, 0, 8);

	set_earlymode_pktnum(भवaddress, ptcb_desc->empkt_num);
	set_earlymode_len0(भवaddress, ptcb_desc->empkt_len[0]);
	set_earlymode_len1(भवaddress, ptcb_desc->empkt_len[1]);
	set_earlymode_len2_1(भवaddress, ptcb_desc->empkt_len[2] & 0xF);
	set_earlymode_len2_2(भवaddress, ptcb_desc->empkt_len[2] >> 4);
	set_earlymode_len3(भवaddress, ptcb_desc->empkt_len[3]);
	set_earlymode_len4(भवaddress, ptcb_desc->empkt_len[4]);
पूर्ण

व्योम rtl92de_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc8,
			  u8 *pbd_desc_tx, काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb,
			  u8 hw_queue, काष्ठा rtl_tcb_desc *ptcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	__le32 *pdesc = (__le32 *)pdesc8;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	अचिन्हित पूर्णांक buf_len = 0;
	अचिन्हित पूर्णांक skb_len = skb->len;
	u8 fw_qsel = _rtl92de_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);
	bool lastseg = ((hdr->frame_control &
			cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);
	dma_addr_t mapping;
	u8 bw_40 = 0;

	अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
		bw_40 = mac->bw_40;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC) अणु
		अगर (sta)
			bw_40 = sta->bandwidth >= IEEE80211_STA_RX_BW_40;
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
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"DMA mapping error\n");
		वापस;
	पूर्ण
	clear_pci_tx_desc_content(pdesc, माप(काष्ठा tx_desc_92d));
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
				rtl_dbg(rtlpriv, COMP_SEND, DBG_LOUD,
					"Insert 8 byte.pTcb->EMPktNum:%d\n",
					ptcb_desc->empkt_num);
				_rtl92de_insert_emcontent(ptcb_desc,
							  (u8 *)(skb->data));
			पूर्ण
		पूर्ण अन्यथा अणु
			set_tx_desc_offset(pdesc, USB_HWDESC_HEADER_LEN);
		पूर्ण
		/* 5G have no CCK rate */
		अगर (rtlhal->current_bandtype == BAND_ON_5G)
			अगर (ptcb_desc->hw_rate < DESC_RATE6M)
				ptcb_desc->hw_rate = DESC_RATE6M;
		set_tx_desc_tx_rate(pdesc, ptcb_desc->hw_rate);
		अगर (ptcb_desc->use_लघुgi || ptcb_desc->use_लघुpreamble)
			set_tx_desc_data_लघुgi(pdesc, 1);

		अगर (rtlhal->macphymode == DUALMAC_DUALPHY &&
			ptcb_desc->hw_rate == DESC_RATEMCS7)
			set_tx_desc_data_लघुgi(pdesc, 1);

		अगर (info->flags & IEEE80211_TX_CTL_AMPDU) अणु
			set_tx_desc_agg_enable(pdesc, 1);
			set_tx_desc_max_agg_num(pdesc, 0x14);
		पूर्ण
		set_tx_desc_seq(pdesc, seq_number);
		set_tx_desc_rts_enable(pdesc,
				       ((ptcb_desc->rts_enable &&
					!ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_hw_rts_enable(pdesc, ((ptcb_desc->rts_enable
					  || ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_cts2self(pdesc, ((ptcb_desc->cts_enable) ? 1 : 0));
		set_tx_desc_rts_stbc(pdesc, ((ptcb_desc->rts_stbc) ? 1 : 0));
		/* 5G have no CCK rate */
		अगर (rtlhal->current_bandtype == BAND_ON_5G)
			अगर (ptcb_desc->rts_rate < DESC_RATE6M)
				ptcb_desc->rts_rate = DESC_RATE6M;
		set_tx_desc_rts_rate(pdesc, ptcb_desc->rts_rate);
		set_tx_desc_rts_bw(pdesc, 0);
		set_tx_desc_rts_sc(pdesc, ptcb_desc->rts_sc);
		set_tx_desc_rts_लघु(pdesc, ((ptcb_desc->rts_rate <=
			DESC_RATE54M) ?
			(ptcb_desc->rts_use_लघुpreamble ? 1 : 0) :
			(ptcb_desc->rts_use_लघुgi ? 1 : 0)));
		अगर (bw_40) अणु
			अगर (ptcb_desc->packet_bw) अणु
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
		set_tx_desc_pkt_size(pdesc, (u16)skb_len);
		अगर (sta) अणु
			u8 ampdu_density = sta->ht_cap.ampdu_density;
			set_tx_desc_ampdu_density(pdesc, ampdu_density);
		पूर्ण
		अगर (info->control.hw_key) अणु
			काष्ठा ieee80211_key_conf *keyconf;

			keyconf = info->control.hw_key;
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
		set_tx_desc_disable_fb(pdesc, ptcb_desc->disable_ratefallback ?
				       1 : 0);
		set_tx_desc_use_rate(pdesc, ptcb_desc->use_driver_rate ? 1 : 0);

		/* Set TxRate and RTSRate in TxDesc  */
		/* This prevent Tx initial rate of new-coming packets */
		/* from being overwritten by retried  packet rate.*/
		अगर (!ptcb_desc->use_driver_rate) अणु
			set_tx_desc_rts_rate(pdesc, 0x08);
			/* set_tx_desc_tx_rate(pdesc, 0x0b); */
		पूर्ण
		अगर (ieee80211_is_data_qos(fc)) अणु
			अगर (mac->rdg_en) अणु
				rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
					"Enable RDG function\n");
				set_tx_desc_rdg_enable(pdesc, 1);
				set_tx_desc_htc(pdesc, 1);
			पूर्ण
		पूर्ण
	पूर्ण

	set_tx_desc_first_seg(pdesc, (firstseg ? 1 : 0));
	set_tx_desc_last_seg(pdesc, (lastseg ? 1 : 0));
	set_tx_desc_tx_buffer_size(pdesc, (u16)buf_len);
	set_tx_desc_tx_buffer_address(pdesc, mapping);
	अगर (rtlpriv->dm.useramask) अणु
		set_tx_desc_rate_id(pdesc, ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->mac_id);
	पूर्ण अन्यथा अणु
		set_tx_desc_rate_id(pdesc, 0xC + ptcb_desc->ratr_index);
		set_tx_desc_macid(pdesc, ptcb_desc->ratr_index);
	पूर्ण
	अगर (ieee80211_is_data_qos(fc))
		set_tx_desc_qos(pdesc, 1);

	अगर ((!ieee80211_is_data_qos(fc)) && ppsc->fwctrl_lps) अणु
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	पूर्ण
	set_tx_desc_more_frag(pdesc, (lastseg ? 0 : 1));
	rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
पूर्ण

व्योम rtl92de_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw,
			     u8 *pdesc8, bool firstseg,
			     bool lastseg, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 fw_queue = QSLT_BEACON;

	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	__le32 *pdesc = (__le32 *)pdesc8;

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
	/* 5G have no CCK rate
	 * Caution: The macros below are multi-line expansions.
	 * The braces are needed no matter what checkpatch says
	 */
	अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
		set_tx_desc_tx_rate(pdesc, DESC_RATE6M);
	पूर्ण अन्यथा अणु
		set_tx_desc_tx_rate(pdesc, DESC_RATE1M);
	पूर्ण
	set_tx_desc_seq(pdesc, 0);
	set_tx_desc_linip(pdesc, 0);
	set_tx_desc_queue_sel(pdesc, fw_queue);
	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);
	set_tx_desc_tx_buffer_size(pdesc, (u16)skb->len);
	set_tx_desc_tx_buffer_address(pdesc, mapping);
	set_tx_desc_rate_id(pdesc, 7);
	set_tx_desc_macid(pdesc, 0);
	set_tx_desc_pkt_size(pdesc, (u16)(skb->len));
	set_tx_desc_first_seg(pdesc, 1);
	set_tx_desc_last_seg(pdesc, 1);
	set_tx_desc_offset(pdesc, 0x20);
	set_tx_desc_use_rate(pdesc, 1);

	अगर (!ieee80211_is_data_qos(fc) && ppsc->fwctrl_lps) अणु
		set_tx_desc_hwseq_en(pdesc, 1);
		set_tx_desc_pkt_id(pdesc, 8);
	पूर्ण

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "H2C Tx Cmd Content", pdesc, TX_DESC_SIZE);
	wmb();
	set_tx_desc_own(pdesc, 1);
पूर्ण

व्योम rtl92de_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc8, bool istx,
		      u8 desc_name, u8 *val)
अणु
	__le32  *pdesc = (__le32 *)pdesc8;

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
			WARN_ONCE(true, "rtl8192de: ERR txdesc :%d not processed\n",
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
			WARN_ONCE(true, "rtl8192de: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u64 rtl92de_get_desc(काष्ठा ieee80211_hw *hw,
		     u8 *p_desc8, bool istx, u8 desc_name)
अणु
	__le32 *p_desc = (__le32 *)p_desc8;
	u32 ret = 0;

	अगर (istx) अणु
		चयन (desc_name) अणु
		हाल HW_DESC_OWN:
			ret = get_tx_desc_own(p_desc);
			अवरोध;
		हाल HW_DESC_TXBUFF_ADDR:
			ret = get_tx_desc_tx_buffer_address(p_desc);
			अवरोध;
		शेष:
			WARN_ONCE(true, "rtl8192de: ERR txdesc :%d not processed\n",
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
			WARN_ONCE(true, "rtl8192de: ERR rxdesc :%d not processed\n",
				  desc_name);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool rtl92de_is_tx_desc_बंदd(काष्ठा ieee80211_hw *hw,
			       u8 hw_queue, u16 index)
अणु
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring = &rtlpci->tx_ring[hw_queue];
	u8 *entry = (u8 *)(&ring->desc[ring->idx]);
	u8 own = (u8)rtl92de_get_desc(hw, entry, true, HW_DESC_OWN);

	/* a beacon packet will only use the first
	 * descriptor by defaut, and the own bit may not
	 * be cleared by the hardware
	 */
	अगर (own)
		वापस false;
	वापस true;
पूर्ण

व्योम rtl92de_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (hw_queue == BEACON_QUEUE)
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG, BIT(4));
	अन्यथा
		rtl_ग_लिखो_word(rtlpriv, REG_PCIE_CTRL_REG,
			       BIT(0) << (hw_queue));
पूर्ण
