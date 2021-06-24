<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/iopoll.h>

#समावेश "main.h"
#समावेश "coex.h"
#समावेश "fw.h"
#समावेश "tx.h"
#समावेश "reg.h"
#समावेश "sec.h"
#समावेश "debug.h"
#समावेश "util.h"
#समावेश "wow.h"
#समावेश "ps.h"

अटल व्योम rtw_fw_c2h_cmd_handle_ext(काष्ठा rtw_dev *rtwdev,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_c2h_cmd *c2h;
	u8 sub_cmd_id;

	c2h = get_c2h_from_skb(skb);
	sub_cmd_id = c2h->payload[0];

	चयन (sub_cmd_id) अणु
	हाल C2H_CCX_RPT:
		rtw_tx_report_handle(rtwdev, skb, C2H_CCX_RPT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u16 get_max_amsdu_len(u32 bit_rate)
अणु
	/* lower than ofdm, करो not aggregate */
	अगर (bit_rate < 550)
		वापस 1;

	/* lower than 20M 2ss mcs8, make it small */
	अगर (bit_rate < 1800)
		वापस 1200;

	/* lower than 40M 2ss mcs9, make it medium */
	अगर (bit_rate < 4000)
		वापस 2600;

	/* not yet 80M 2ss mcs8/9, make it twice regular packet size */
	अगर (bit_rate < 7000)
		वापस 3500;

	/* unlimited */
	वापस 0;
पूर्ण

काष्ठा rtw_fw_iter_ra_data अणु
	काष्ठा rtw_dev *rtwdev;
	u8 *payload;
पूर्ण;

अटल व्योम rtw_fw_ra_report_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_fw_iter_ra_data *ra_data = data;
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	u8 mac_id, rate, sgi, bw;
	u8 mcs, nss;
	u32 bit_rate;

	mac_id = GET_RA_REPORT_MACID(ra_data->payload);
	अगर (si->mac_id != mac_id)
		वापस;

	si->ra_report.txrate.flags = 0;

	rate = GET_RA_REPORT_RATE(ra_data->payload);
	sgi = GET_RA_REPORT_SGI(ra_data->payload);
	bw = GET_RA_REPORT_BW(ra_data->payload);

	अगर (rate < DESC_RATEMCS0) अणु
		si->ra_report.txrate.legacy = rtw_desc_to_bitrate(rate);
		जाओ legacy;
	पूर्ण

	rtw_desc_to_mcsrate(rate, &mcs, &nss);
	अगर (rate >= DESC_RATEVHT1SS_MCS0)
		si->ra_report.txrate.flags |= RATE_INFO_FLAGS_VHT_MCS;
	अन्यथा अगर (rate >= DESC_RATEMCS0)
		si->ra_report.txrate.flags |= RATE_INFO_FLAGS_MCS;

	अगर (rate >= DESC_RATEMCS0) अणु
		si->ra_report.txrate.mcs = mcs;
		si->ra_report.txrate.nss = nss;
	पूर्ण

	अगर (sgi)
		si->ra_report.txrate.flags |= RATE_INFO_FLAGS_SHORT_GI;

	अगर (bw == RTW_CHANNEL_WIDTH_80)
		si->ra_report.txrate.bw = RATE_INFO_BW_80;
	अन्यथा अगर (bw == RTW_CHANNEL_WIDTH_40)
		si->ra_report.txrate.bw = RATE_INFO_BW_40;
	अन्यथा
		si->ra_report.txrate.bw = RATE_INFO_BW_20;

legacy:
	bit_rate = cfg80211_calculate_bitrate(&si->ra_report.txrate);

	si->ra_report.desc_rate = rate;
	si->ra_report.bit_rate = bit_rate;

	sta->max_rc_amsdu_len = get_max_amsdu_len(bit_rate);
पूर्ण

अटल व्योम rtw_fw_ra_report_handle(काष्ठा rtw_dev *rtwdev, u8 *payload,
				    u8 length)
अणु
	काष्ठा rtw_fw_iter_ra_data ra_data;

	अगर (WARN(length < 7, "invalid ra report c2h length\n"))
		वापस;

	rtwdev->dm_info.tx_rate = GET_RA_REPORT_RATE(payload);
	ra_data.rtwdev = rtwdev;
	ra_data.payload = payload;
	rtw_iterate_stas_atomic(rtwdev, rtw_fw_ra_report_iter, &ra_data);
पूर्ण

व्योम rtw_fw_c2h_cmd_handle(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_c2h_cmd *c2h;
	u32 pkt_offset;
	u8 len;

	pkt_offset = *((u32 *)skb->cb);
	c2h = (काष्ठा rtw_c2h_cmd *)(skb->data + pkt_offset);
	len = skb->len - pkt_offset - 2;

	mutex_lock(&rtwdev->mutex);

	अगर (!test_bit(RTW_FLAG_RUNNING, rtwdev->flags))
		जाओ unlock;

	चयन (c2h->id) अणु
	हाल C2H_CCX_TX_RPT:
		rtw_tx_report_handle(rtwdev, skb, C2H_CCX_TX_RPT);
		अवरोध;
	हाल C2H_BT_INFO:
		rtw_coex_bt_info_notअगरy(rtwdev, c2h->payload, len);
		अवरोध;
	हाल C2H_WLAN_INFO:
		rtw_coex_wl_fwdbginfo_notअगरy(rtwdev, c2h->payload, len);
		अवरोध;
	हाल C2H_HALMAC:
		rtw_fw_c2h_cmd_handle_ext(rtwdev, skb);
		अवरोध;
	हाल C2H_RA_RPT:
		rtw_fw_ra_report_handle(rtwdev, c2h->payload, len);
		अवरोध;
	शेष:
		rtw_dbg(rtwdev, RTW_DBG_FW, "C2H 0x%x isn't handled\n", c2h->id);
		अवरोध;
	पूर्ण

unlock:
	mutex_unlock(&rtwdev->mutex);
पूर्ण

व्योम rtw_fw_c2h_cmd_rx_irqsafe(काष्ठा rtw_dev *rtwdev, u32 pkt_offset,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_c2h_cmd *c2h;
	u8 len;

	c2h = (काष्ठा rtw_c2h_cmd *)(skb->data + pkt_offset);
	len = skb->len - pkt_offset - 2;
	*((u32 *)skb->cb) = pkt_offset;

	rtw_dbg(rtwdev, RTW_DBG_FW, "recv C2H, id=0x%02x, seq=0x%02x, len=%d\n",
		c2h->id, c2h->seq, len);

	चयन (c2h->id) अणु
	हाल C2H_BT_MP_INFO:
		rtw_coex_info_response(rtwdev, skb);
		अवरोध;
	हाल C2H_WLAN_RFON:
		complete(&rtwdev->lps_leave_check);
		अवरोध;
	शेष:
		/* pass offset क्रम further operation */
		*((u32 *)skb->cb) = pkt_offset;
		skb_queue_tail(&rtwdev->c2h_queue, skb);
		ieee80211_queue_work(rtwdev->hw, &rtwdev->c2h_work);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_fw_c2h_cmd_rx_irqsafe);

व्योम rtw_fw_c2h_cmd_isr(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtw_पढ़ो8(rtwdev, REG_MCU_TST_CFG) == VAL_FW_TRIGGER)
		rtw_fw_recovery(rtwdev);
	अन्यथा
		rtw_warn(rtwdev, "unhandled firmware c2h interrupt\n");
पूर्ण
EXPORT_SYMBOL(rtw_fw_c2h_cmd_isr);

अटल व्योम rtw_fw_send_h2c_command(काष्ठा rtw_dev *rtwdev,
				    u8 *h2c)
अणु
	u8 box;
	u8 box_state;
	u32 box_reg, box_ex_reg;
	पूर्णांक idx;
	पूर्णांक ret;

	rtw_dbg(rtwdev, RTW_DBG_FW,
		"send H2C content %02x%02x%02x%02x %02x%02x%02x%02x\n",
		h2c[3], h2c[2], h2c[1], h2c[0],
		h2c[7], h2c[6], h2c[5], h2c[4]);

	spin_lock(&rtwdev->h2c.lock);

	box = rtwdev->h2c.last_box_num;
	चयन (box) अणु
	हाल 0:
		box_reg = REG_HMEBOX0;
		box_ex_reg = REG_HMEBOX0_EX;
		अवरोध;
	हाल 1:
		box_reg = REG_HMEBOX1;
		box_ex_reg = REG_HMEBOX1_EX;
		अवरोध;
	हाल 2:
		box_reg = REG_HMEBOX2;
		box_ex_reg = REG_HMEBOX2_EX;
		अवरोध;
	हाल 3:
		box_reg = REG_HMEBOX3;
		box_ex_reg = REG_HMEBOX3_EX;
		अवरोध;
	शेष:
		WARN(1, "invalid h2c mail box number\n");
		जाओ out;
	पूर्ण

	ret = पढ़ो_poll_समयout_atomic(rtw_पढ़ो8, box_state,
				       !((box_state >> box) & 0x1), 100, 3000,
				       false, rtwdev, REG_HMETFR);

	अगर (ret) अणु
		rtw_err(rtwdev, "failed to send h2c command\n");
		जाओ out;
	पूर्ण

	क्रम (idx = 0; idx < 4; idx++)
		rtw_ग_लिखो8(rtwdev, box_reg + idx, h2c[idx]);
	क्रम (idx = 0; idx < 4; idx++)
		rtw_ग_लिखो8(rtwdev, box_ex_reg + idx, h2c[idx + 4]);

	अगर (++rtwdev->h2c.last_box_num >= 4)
		rtwdev->h2c.last_box_num = 0;

out:
	spin_unlock(&rtwdev->h2c.lock);
पूर्ण

व्योम rtw_fw_h2c_cmd_dbg(काष्ठा rtw_dev *rtwdev, u8 *h2c)
अणु
	rtw_fw_send_h2c_command(rtwdev, h2c);
पूर्ण

अटल व्योम rtw_fw_send_h2c_packet(काष्ठा rtw_dev *rtwdev, u8 *h2c_pkt)
अणु
	पूर्णांक ret;

	spin_lock(&rtwdev->h2c.lock);

	FW_OFFLOAD_H2C_SET_SEQ_NUM(h2c_pkt, rtwdev->h2c.seq);
	ret = rtw_hci_ग_लिखो_data_h2c(rtwdev, h2c_pkt, H2C_PKT_SIZE);
	अगर (ret)
		rtw_err(rtwdev, "failed to send h2c packet\n");
	rtwdev->h2c.seq++;

	spin_unlock(&rtwdev->h2c.lock);
पूर्ण

व्योम
rtw_fw_send_general_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fअगरo_conf *fअगरo = &rtwdev->fअगरo;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u16 total_size = H2C_PKT_HDR_SIZE + 4;

	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस;

	rtw_h2c_pkt_set_header(h2c_pkt, H2C_PKT_GENERAL_INFO);

	SET_PKT_H2C_TOTAL_LEN(h2c_pkt, total_size);

	GENERAL_INFO_SET_FW_TX_BOUNDARY(h2c_pkt,
					fअगरo->rsvd_fw_txbuf_addr -
					fअगरo->rsvd_boundary);

	rtw_fw_send_h2c_packet(rtwdev, h2c_pkt);
पूर्ण

व्योम
rtw_fw_send_phydm_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u16 total_size = H2C_PKT_HDR_SIZE + 8;
	u8 fw_rf_type = 0;

	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस;

	अगर (hal->rf_type == RF_1T1R)
		fw_rf_type = FW_RF_1T1R;
	अन्यथा अगर (hal->rf_type == RF_2T2R)
		fw_rf_type = FW_RF_2T2R;

	rtw_h2c_pkt_set_header(h2c_pkt, H2C_PKT_PHYDM_INFO);

	SET_PKT_H2C_TOTAL_LEN(h2c_pkt, total_size);
	PHYDM_INFO_SET_REF_TYPE(h2c_pkt, efuse->rfe_option);
	PHYDM_INFO_SET_RF_TYPE(h2c_pkt, fw_rf_type);
	PHYDM_INFO_SET_CUT_VER(h2c_pkt, hal->cut_version);
	PHYDM_INFO_SET_RX_ANT_STATUS(h2c_pkt, hal->antenna_tx);
	PHYDM_INFO_SET_TX_ANT_STATUS(h2c_pkt, hal->antenna_rx);

	rtw_fw_send_h2c_packet(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_करो_iqk(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_iqk_para *para)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u16 total_size = H2C_PKT_HDR_SIZE + 1;

	rtw_h2c_pkt_set_header(h2c_pkt, H2C_PKT_IQK);
	SET_PKT_H2C_TOTAL_LEN(h2c_pkt, total_size);
	IQK_SET_CLEAR(h2c_pkt, para->clear);
	IQK_SET_SEGMENT_IQK(h2c_pkt, para->segment_iqk);

	rtw_fw_send_h2c_packet(rtwdev, h2c_pkt);
पूर्ण
EXPORT_SYMBOL(rtw_fw_करो_iqk);

व्योम rtw_fw_inक्रमm_rfk_status(काष्ठा rtw_dev *rtwdev, bool start)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_WIFI_CALIBRATION);

	RFK_SET_INFORM_START(h2c_pkt, start);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण
EXPORT_SYMBOL(rtw_fw_inक्रमm_rfk_status);

व्योम rtw_fw_query_bt_info(काष्ठा rtw_dev *rtwdev)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_QUERY_BT_INFO);

	SET_QUERY_BT_INFO(h2c_pkt, true);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_wl_ch_info(काष्ठा rtw_dev *rtwdev, u8 link, u8 ch, u8 bw)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_WL_CH_INFO);

	SET_WL_CH_INFO_LINK(h2c_pkt, link);
	SET_WL_CH_INFO_CHNL(h2c_pkt, ch);
	SET_WL_CH_INFO_BW(h2c_pkt, bw);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_query_bt_mp_info(काष्ठा rtw_dev *rtwdev,
			     काष्ठा rtw_coex_info_req *req)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_QUERY_BT_MP_INFO);

	SET_BT_MP_INFO_SEQ(h2c_pkt, req->seq);
	SET_BT_MP_INFO_OP_CODE(h2c_pkt, req->op_code);
	SET_BT_MP_INFO_PARA1(h2c_pkt, req->para1);
	SET_BT_MP_INFO_PARA2(h2c_pkt, req->para2);
	SET_BT_MP_INFO_PARA3(h2c_pkt, req->para3);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_क्रमce_bt_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 bt_pwr_dec_lvl)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u8 index = 0 - bt_pwr_dec_lvl;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_FORCE_BT_TX_POWER);

	SET_BT_TX_POWER_INDEX(h2c_pkt, index);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_bt_ignore_wlan_action(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_IGNORE_WLAN_ACTION);

	SET_IGNORE_WLAN_ACTION_EN(h2c_pkt, enable);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_coex_tdma_type(काष्ठा rtw_dev *rtwdev,
			   u8 para1, u8 para2, u8 para3, u8 para4, u8 para5)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_COEX_TDMA_TYPE);

	SET_COEX_TDMA_TYPE_PARA1(h2c_pkt, para1);
	SET_COEX_TDMA_TYPE_PARA2(h2c_pkt, para2);
	SET_COEX_TDMA_TYPE_PARA3(h2c_pkt, para3);
	SET_COEX_TDMA_TYPE_PARA4(h2c_pkt, para4);
	SET_COEX_TDMA_TYPE_PARA5(h2c_pkt, para5);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_bt_wअगरi_control(काष्ठा rtw_dev *rtwdev, u8 op_code, u8 *data)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_BT_WIFI_CONTROL);

	SET_BT_WIFI_CONTROL_OP_CODE(h2c_pkt, op_code);

	SET_BT_WIFI_CONTROL_DATA1(h2c_pkt, *data);
	SET_BT_WIFI_CONTROL_DATA2(h2c_pkt, *(data + 1));
	SET_BT_WIFI_CONTROL_DATA3(h2c_pkt, *(data + 2));
	SET_BT_WIFI_CONTROL_DATA4(h2c_pkt, *(data + 3));
	SET_BT_WIFI_CONTROL_DATA5(h2c_pkt, *(data + 4));

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_send_rssi_info(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_sta_info *si)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u8 rssi = ewma_rssi_पढ़ो(&si->avg_rssi);
	bool stbc_en = si->stbc_en ? true : false;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_RSSI_MONITOR);

	SET_RSSI_INFO_MACID(h2c_pkt, si->mac_id);
	SET_RSSI_INFO_RSSI(h2c_pkt, rssi);
	SET_RSSI_INFO_STBC(h2c_pkt, stbc_en);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_send_ra_info(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_sta_info *si)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	bool no_update = si->updated;
	bool disable_pt = true;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_RA_INFO);

	SET_RA_INFO_MACID(h2c_pkt, si->mac_id);
	SET_RA_INFO_RATE_ID(h2c_pkt, si->rate_id);
	SET_RA_INFO_INIT_RA_LVL(h2c_pkt, si->init_ra_lv);
	SET_RA_INFO_SGI_EN(h2c_pkt, si->sgi_enable);
	SET_RA_INFO_BW_MODE(h2c_pkt, si->bw_mode);
	SET_RA_INFO_LDPC(h2c_pkt, !!si->ldpc_en);
	SET_RA_INFO_NO_UPDATE(h2c_pkt, no_update);
	SET_RA_INFO_VHT_EN(h2c_pkt, si->vht_enable);
	SET_RA_INFO_DIS_PT(h2c_pkt, disable_pt);
	SET_RA_INFO_RA_MASK0(h2c_pkt, (si->ra_mask & 0xff));
	SET_RA_INFO_RA_MASK1(h2c_pkt, (si->ra_mask & 0xff00) >> 8);
	SET_RA_INFO_RA_MASK2(h2c_pkt, (si->ra_mask & 0xff0000) >> 16);
	SET_RA_INFO_RA_MASK3(h2c_pkt, (si->ra_mask & 0xff000000) >> 24);

	si->init_ra_lv = 0;
	si->updated = true;

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_media_status_report(काष्ठा rtw_dev *rtwdev, u8 mac_id, bool connect)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_MEDIA_STATUS_RPT);
	MEDIA_STATUS_RPT_SET_OP_MODE(h2c_pkt, connect);
	MEDIA_STATUS_RPT_SET_MACID(h2c_pkt, mac_id);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_update_wl_phy_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_traffic_stats *stats = &rtwdev->stats;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_WL_PHY_INFO);
	SET_WL_PHY_INFO_TX_TP(h2c_pkt, stats->tx_throughput);
	SET_WL_PHY_INFO_RX_TP(h2c_pkt, stats->rx_throughput);
	SET_WL_PHY_INFO_TX_RATE_DESC(h2c_pkt, dm_info->tx_rate);
	SET_WL_PHY_INFO_RX_RATE_DESC(h2c_pkt, dm_info->curr_rx_rate);
	SET_WL_PHY_INFO_RX_EVM(h2c_pkt, dm_info->rx_evm_dbm[RF_PATH_A]);
	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_pwr_mode(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_SET_PWR_MODE);

	SET_PWR_MODE_SET_MODE(h2c_pkt, conf->mode);
	SET_PWR_MODE_SET_RLBM(h2c_pkt, conf->rlbm);
	SET_PWR_MODE_SET_SMART_PS(h2c_pkt, conf->smart_ps);
	SET_PWR_MODE_SET_AWAKE_INTERVAL(h2c_pkt, conf->awake_पूर्णांकerval);
	SET_PWR_MODE_SET_PORT_ID(h2c_pkt, conf->port_id);
	SET_PWR_MODE_SET_PWR_STATE(h2c_pkt, conf->state);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_keep_alive_cmd(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	काष्ठा rtw_fw_wow_keep_alive_para mode = अणु
		.aकरोpt = true,
		.pkt_type = KEEP_ALIVE_शून्य_PKT,
		.period = 5,
	पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_KEEP_ALIVE);
	SET_KEEP_ALIVE_ENABLE(h2c_pkt, enable);
	SET_KEEP_ALIVE_ADOPT(h2c_pkt, mode.aकरोpt);
	SET_KEEP_ALIVE_PKT_TYPE(h2c_pkt, mode.pkt_type);
	SET_KEEP_ALIVE_CHECK_PERIOD(h2c_pkt, mode.period);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_disconnect_decision_cmd(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	काष्ठा rtw_fw_wow_disconnect_para mode = अणु
		.aकरोpt = true,
		.period = 30,
		.retry_count = 5,
	पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_DISCONNECT_DECISION);

	अगर (test_bit(RTW_WOW_FLAG_EN_DISCONNECT, rtw_wow->flags)) अणु
		SET_DISCONNECT_DECISION_ENABLE(h2c_pkt, enable);
		SET_DISCONNECT_DECISION_ADOPT(h2c_pkt, mode.aकरोpt);
		SET_DISCONNECT_DECISION_CHECK_PERIOD(h2c_pkt, mode.period);
		SET_DISCONNECT_DECISION_TRY_PKT_NUM(h2c_pkt, mode.retry_count);
	पूर्ण

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_wowlan_ctrl_cmd(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_WOWLAN);

	SET_WOWLAN_FUNC_ENABLE(h2c_pkt, enable);
	अगर (rtw_wow_mgd_linked(rtwdev)) अणु
		अगर (test_bit(RTW_WOW_FLAG_EN_MAGIC_PKT, rtw_wow->flags))
			SET_WOWLAN_MAGIC_PKT_ENABLE(h2c_pkt, enable);
		अगर (test_bit(RTW_WOW_FLAG_EN_DISCONNECT, rtw_wow->flags))
			SET_WOWLAN_DEAUTH_WAKEUP_ENABLE(h2c_pkt, enable);
		अगर (test_bit(RTW_WOW_FLAG_EN_REKEY_PKT, rtw_wow->flags))
			SET_WOWLAN_REKEY_WAKEUP_ENABLE(h2c_pkt, enable);
		अगर (rtw_wow->pattern_cnt)
			SET_WOWLAN_PATTERN_MATCH_ENABLE(h2c_pkt, enable);
	पूर्ण

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_aoac_global_info_cmd(काष्ठा rtw_dev *rtwdev,
				     u8 pairwise_key_enc,
				     u8 group_key_enc)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_AOAC_GLOBAL_INFO);

	SET_AOAC_GLOBAL_INFO_PAIRWISE_ENC_ALG(h2c_pkt, pairwise_key_enc);
	SET_AOAC_GLOBAL_INFO_GROUP_ENC_ALG(h2c_pkt, group_key_enc);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_remote_wake_ctrl_cmd(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_REMOTE_WAKE_CTRL);

	SET_REMOTE_WAKECTRL_ENABLE(h2c_pkt, enable);

	अगर (rtw_wow_no_link(rtwdev))
		SET_REMOTE_WAKE_CTRL_NLO_OFFLOAD_EN(h2c_pkt, enable);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

अटल u8 rtw_get_rsvd_page_location(काष्ठा rtw_dev *rtwdev,
				     क्रमागत rtw_rsvd_packet_type type)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt;
	u8 location = 0;

	list_क्रम_each_entry(rsvd_pkt, &rtwdev->rsvd_page_list, build_list) अणु
		अगर (type == rsvd_pkt->type)
			location = rsvd_pkt->page;
	पूर्ण

	वापस location;
पूर्ण

व्योम rtw_fw_set_nlo_info(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u8 loc_nlo;

	loc_nlo = rtw_get_rsvd_page_location(rtwdev, RSVD_NLO_INFO);

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_NLO_INFO);

	SET_NLO_FUN_EN(h2c_pkt, enable);
	अगर (enable) अणु
		अगर (rtw_get_lps_deep_mode(rtwdev) != LPS_DEEP_MODE_NONE)
			SET_NLO_PS_32K(h2c_pkt, enable);
		SET_NLO_IGNORE_SECURITY(h2c_pkt, enable);
		SET_NLO_LOC_NLO_INFO(h2c_pkt, loc_nlo);
	पूर्ण

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_set_pg_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u8 loc_pg, loc_dpk;

	loc_pg = rtw_get_rsvd_page_location(rtwdev, RSVD_LPS_PG_INFO);
	loc_dpk = rtw_get_rsvd_page_location(rtwdev, RSVD_LPS_PG_DPK);

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_LPS_PG_INFO);

	LPS_PG_INFO_LOC(h2c_pkt, loc_pg);
	LPS_PG_DPK_LOC(h2c_pkt, loc_dpk);
	LPS_PG_SEC_CAM_EN(h2c_pkt, conf->sec_cam_backup);
	LPS_PG_PATTERN_CAM_EN(h2c_pkt, conf->pattern_cam_backup);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

अटल u8 rtw_get_rsvd_page_probe_req_location(काष्ठा rtw_dev *rtwdev,
					       काष्ठा cfg80211_ssid *ssid)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt;
	u8 location = 0;

	list_क्रम_each_entry(rsvd_pkt, &rtwdev->rsvd_page_list, build_list) अणु
		अगर (rsvd_pkt->type != RSVD_PROBE_REQ)
			जारी;
		अगर ((!ssid && !rsvd_pkt->ssid) ||
		    rtw_ssid_equal(rsvd_pkt->ssid, ssid))
			location = rsvd_pkt->page;
	पूर्ण

	वापस location;
पूर्ण

अटल u16 rtw_get_rsvd_page_probe_req_size(काष्ठा rtw_dev *rtwdev,
					    काष्ठा cfg80211_ssid *ssid)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt;
	u16 size = 0;

	list_क्रम_each_entry(rsvd_pkt, &rtwdev->rsvd_page_list, build_list) अणु
		अगर (rsvd_pkt->type != RSVD_PROBE_REQ)
			जारी;
		अगर ((!ssid && !rsvd_pkt->ssid) ||
		    rtw_ssid_equal(rsvd_pkt->ssid, ssid))
			size = rsvd_pkt->skb->len;
	पूर्ण

	वापस size;
पूर्ण

व्योम rtw_send_rsvd_page_h2c(काष्ठा rtw_dev *rtwdev)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u8 location = 0;

	SET_H2C_CMD_ID_CLASS(h2c_pkt, H2C_CMD_RSVD_PAGE);

	location = rtw_get_rsvd_page_location(rtwdev, RSVD_PROBE_RESP);
	*(h2c_pkt + 1) = location;
	rtw_dbg(rtwdev, RTW_DBG_FW, "RSVD_PROBE_RESP loc: %d\n", location);

	location = rtw_get_rsvd_page_location(rtwdev, RSVD_PS_POLL);
	*(h2c_pkt + 2) = location;
	rtw_dbg(rtwdev, RTW_DBG_FW, "RSVD_PS_POLL loc: %d\n", location);

	location = rtw_get_rsvd_page_location(rtwdev, RSVD_शून्य);
	*(h2c_pkt + 3) = location;
	rtw_dbg(rtwdev, RTW_DBG_FW, "RSVD_NULL loc: %d\n", location);

	location = rtw_get_rsvd_page_location(rtwdev, RSVD_QOS_शून्य);
	*(h2c_pkt + 4) = location;
	rtw_dbg(rtwdev, RTW_DBG_FW, "RSVD_QOS_NULL loc: %d\n", location);

	rtw_fw_send_h2c_command(rtwdev, h2c_pkt);
पूर्ण

अटल काष्ठा sk_buff *rtw_nlo_info_get(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_pno_request *pno_req = &rtwdev->wow.pno_req;
	काष्ठा rtw_nlo_info_hdr *nlo_hdr;
	काष्ठा cfg80211_ssid *ssid;
	काष्ठा sk_buff *skb;
	u8 *pos, loc;
	u32 size;
	पूर्णांक i;

	अगर (!pno_req->inited || !pno_req->match_set_cnt)
		वापस शून्य;

	size = माप(काष्ठा rtw_nlo_info_hdr) + pno_req->match_set_cnt *
		      IEEE80211_MAX_SSID_LEN + chip->tx_pkt_desc_sz;

	skb = alloc_skb(size, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, chip->tx_pkt_desc_sz);

	nlo_hdr = skb_put_zero(skb, माप(काष्ठा rtw_nlo_info_hdr));

	nlo_hdr->nlo_count = pno_req->match_set_cnt;
	nlo_hdr->hidden_ap_count = pno_req->match_set_cnt;

	/* pattern check क्रम firmware */
	स_रखो(nlo_hdr->pattern_check, 0xA5, FW_NLO_INFO_CHECK_SIZE);

	क्रम (i = 0; i < pno_req->match_set_cnt; i++)
		nlo_hdr->ssid_len[i] = pno_req->match_sets[i].ssid.ssid_len;

	क्रम (i = 0; i < pno_req->match_set_cnt; i++) अणु
		ssid = &pno_req->match_sets[i].ssid;
		loc  = rtw_get_rsvd_page_probe_req_location(rtwdev, ssid);
		अगर (!loc) अणु
			rtw_err(rtwdev, "failed to get probe req rsvd loc\n");
			kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
		nlo_hdr->location[i] = loc;
	पूर्ण

	क्रम (i = 0; i < pno_req->match_set_cnt; i++) अणु
		pos = skb_put_zero(skb, IEEE80211_MAX_SSID_LEN);
		स_नकल(pos, pno_req->match_sets[i].ssid.ssid,
		       pno_req->match_sets[i].ssid.ssid_len);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtw_cs_channel_info_get(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_pno_request *pno_req = &rtwdev->wow.pno_req;
	काष्ठा ieee80211_channel *channels = pno_req->channels;
	काष्ठा sk_buff *skb;
	पूर्णांक count =  pno_req->channel_cnt;
	u8 *pos;
	पूर्णांक i = 0;

	skb = alloc_skb(4 * count + chip->tx_pkt_desc_sz, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, chip->tx_pkt_desc_sz);

	क्रम (i = 0; i < count; i++) अणु
		pos = skb_put_zero(skb, 4);

		CHSW_INFO_SET_CH(pos, channels[i].hw_value);

		अगर (channels[i].flags & IEEE80211_CHAN_RADAR)
			CHSW_INFO_SET_ACTION_ID(pos, 0);
		अन्यथा
			CHSW_INFO_SET_ACTION_ID(pos, 1);
		CHSW_INFO_SET_TIMEOUT(pos, 1);
		CHSW_INFO_SET_PRI_CH_IDX(pos, 1);
		CHSW_INFO_SET_BW(pos, 0);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtw_lps_pg_dpk_get(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	काष्ठा rtw_lps_pg_dpk_hdr *dpk_hdr;
	काष्ठा sk_buff *skb;
	u32 size;

	size = chip->tx_pkt_desc_sz + माप(*dpk_hdr);
	skb = alloc_skb(size, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, chip->tx_pkt_desc_sz);
	dpk_hdr = skb_put_zero(skb, माप(*dpk_hdr));
	dpk_hdr->dpk_ch = dpk_info->dpk_ch;
	dpk_hdr->dpk_path_ok = dpk_info->dpk_path_ok[0];
	स_नकल(dpk_hdr->dpk_txagc, dpk_info->dpk_txagc, 2);
	स_नकल(dpk_hdr->dpk_gs, dpk_info->dpk_gs, 4);
	स_नकल(dpk_hdr->coef, dpk_info->coef, 160);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtw_lps_pg_info_get(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_lps_conf *conf = &rtwdev->lps_conf;
	काष्ठा rtw_lps_pg_info_hdr *pg_info_hdr;
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा sk_buff *skb;
	u32 size;

	size = chip->tx_pkt_desc_sz + माप(*pg_info_hdr);
	skb = alloc_skb(size, GFP_KERNEL);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, chip->tx_pkt_desc_sz);
	pg_info_hdr = skb_put_zero(skb, माप(*pg_info_hdr));
	pg_info_hdr->tx_bu_page_count = rtwdev->fअगरo.rsvd_drv_pg_num;
	pg_info_hdr->macid = find_first_bit(rtwdev->mac_id_map, RTW_MAX_MAC_ID_NUM);
	pg_info_hdr->sec_cam_count =
		rtw_sec_cam_pg_backup(rtwdev, pg_info_hdr->sec_cam);
	pg_info_hdr->pattern_count = rtw_wow->pattern_cnt;

	conf->sec_cam_backup = pg_info_hdr->sec_cam_count != 0;
	conf->pattern_cam_backup = rtw_wow->pattern_cnt != 0;

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *rtw_get_rsvd_page_skb(काष्ठा ieee80211_hw *hw,
					     काष्ठा rtw_rsvd_page *rsvd_pkt)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा rtw_vअगर *rtwvअगर;
	काष्ठा sk_buff *skb_new;
	काष्ठा cfg80211_ssid *ssid;

	अगर (rsvd_pkt->type == RSVD_DUMMY) अणु
		skb_new = alloc_skb(1, GFP_KERNEL);
		अगर (!skb_new)
			वापस शून्य;

		skb_put(skb_new, 1);
		वापस skb_new;
	पूर्ण

	rtwvअगर = rsvd_pkt->rtwvअगर;
	अगर (!rtwvअगर)
		वापस शून्य;

	vअगर = rtwvअगर_to_vअगर(rtwvअगर);

	चयन (rsvd_pkt->type) अणु
	हाल RSVD_BEACON:
		skb_new = ieee80211_beacon_get(hw, vअगर);
		अवरोध;
	हाल RSVD_PS_POLL:
		skb_new = ieee80211_pspoll_get(hw, vअगर);
		अवरोध;
	हाल RSVD_PROBE_RESP:
		skb_new = ieee80211_proberesp_get(hw, vअगर);
		अवरोध;
	हाल RSVD_शून्य:
		skb_new = ieee80211_nullfunc_get(hw, vअगर, false);
		अवरोध;
	हाल RSVD_QOS_शून्य:
		skb_new = ieee80211_nullfunc_get(hw, vअगर, true);
		अवरोध;
	हाल RSVD_LPS_PG_DPK:
		skb_new = rtw_lps_pg_dpk_get(hw);
		अवरोध;
	हाल RSVD_LPS_PG_INFO:
		skb_new = rtw_lps_pg_info_get(hw);
		अवरोध;
	हाल RSVD_PROBE_REQ:
		ssid = (काष्ठा cfg80211_ssid *)rsvd_pkt->ssid;
		अगर (ssid)
			skb_new = ieee80211_probereq_get(hw, vअगर->addr,
							 ssid->ssid,
							 ssid->ssid_len, 0);
		अन्यथा
			skb_new = ieee80211_probereq_get(hw, vअगर->addr, शून्य, 0, 0);
		अवरोध;
	हाल RSVD_NLO_INFO:
		skb_new = rtw_nlo_info_get(hw);
		अवरोध;
	हाल RSVD_CH_INFO:
		skb_new = rtw_cs_channel_info_get(hw);
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	अगर (!skb_new)
		वापस शून्य;

	वापस skb_new;
पूर्ण

अटल व्योम rtw_fill_rsvd_page_desc(काष्ठा rtw_dev *rtwdev, काष्ठा sk_buff *skb,
				    क्रमागत rtw_rsvd_packet_type type)
अणु
	काष्ठा rtw_tx_pkt_info pkt_info = अणु0पूर्ण;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u8 *pkt_desc;

	rtw_tx_rsvd_page_pkt_info_update(rtwdev, &pkt_info, skb, type);
	pkt_desc = skb_push(skb, chip->tx_pkt_desc_sz);
	स_रखो(pkt_desc, 0, chip->tx_pkt_desc_sz);
	rtw_tx_fill_tx_desc(&pkt_info, skb);
पूर्ण

अटल अंतरभूत u8 rtw_len_to_page(अचिन्हित पूर्णांक len, u8 page_size)
अणु
	वापस DIV_ROUND_UP(len, page_size);
पूर्ण

अटल व्योम rtw_rsvd_page_list_to_buf(काष्ठा rtw_dev *rtwdev, u8 page_size,
				      u8 page_margin, u32 page, u8 *buf,
				      काष्ठा rtw_rsvd_page *rsvd_pkt)
अणु
	काष्ठा sk_buff *skb = rsvd_pkt->skb;

	अगर (page >= 1)
		स_नकल(buf + page_margin + page_size * (page - 1),
		       skb->data, skb->len);
	अन्यथा
		स_नकल(buf, skb->data, skb->len);
पूर्ण

अटल काष्ठा rtw_rsvd_page *rtw_alloc_rsvd_page(काष्ठा rtw_dev *rtwdev,
						 क्रमागत rtw_rsvd_packet_type type,
						 bool txdesc)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt = शून्य;

	rsvd_pkt = kzalloc(माप(*rsvd_pkt), GFP_KERNEL);

	अगर (!rsvd_pkt)
		वापस शून्य;

	INIT_LIST_HEAD(&rsvd_pkt->vअगर_list);
	INIT_LIST_HEAD(&rsvd_pkt->build_list);
	rsvd_pkt->type = type;
	rsvd_pkt->add_txdesc = txdesc;

	वापस rsvd_pkt;
पूर्ण

अटल व्योम rtw_insert_rsvd_page(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw_vअगर *rtwvअगर,
				 काष्ठा rtw_rsvd_page *rsvd_pkt)
अणु
	lockdep_निश्चित_held(&rtwdev->mutex);

	list_add_tail(&rsvd_pkt->vअगर_list, &rtwvअगर->rsvd_page_list);
पूर्ण

अटल व्योम rtw_add_rsvd_page(काष्ठा rtw_dev *rtwdev,
			      काष्ठा rtw_vअगर *rtwvअगर,
			      क्रमागत rtw_rsvd_packet_type type,
			      bool txdesc)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt;

	rsvd_pkt = rtw_alloc_rsvd_page(rtwdev, type, txdesc);
	अगर (!rsvd_pkt) अणु
		rtw_err(rtwdev, "failed to alloc rsvd page %d\n", type);
		वापस;
	पूर्ण

	rsvd_pkt->rtwvअगर = rtwvअगर;
	rtw_insert_rsvd_page(rtwdev, rtwvअगर, rsvd_pkt);
पूर्ण

अटल व्योम rtw_add_rsvd_page_probe_req(काष्ठा rtw_dev *rtwdev,
					काष्ठा rtw_vअगर *rtwvअगर,
					काष्ठा cfg80211_ssid *ssid)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt;

	rsvd_pkt = rtw_alloc_rsvd_page(rtwdev, RSVD_PROBE_REQ, true);
	अगर (!rsvd_pkt) अणु
		rtw_err(rtwdev, "failed to alloc probe req rsvd page\n");
		वापस;
	पूर्ण

	rsvd_pkt->rtwvअगर = rtwvअगर;
	rsvd_pkt->ssid = ssid;
	rtw_insert_rsvd_page(rtwdev, rtwvअगर, rsvd_pkt);
पूर्ण

व्योम rtw_हटाओ_rsvd_page(काष्ठा rtw_dev *rtwdev,
			  काष्ठा rtw_vअगर *rtwvअगर)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt, *पंचांगp;

	lockdep_निश्चित_held(&rtwdev->mutex);

	/* हटाओ all of the rsvd pages क्रम vअगर */
	list_क्रम_each_entry_safe(rsvd_pkt, पंचांगp, &rtwvअगर->rsvd_page_list,
				 vअगर_list) अणु
		list_del(&rsvd_pkt->vअगर_list);
		अगर (!list_empty(&rsvd_pkt->build_list))
			list_del(&rsvd_pkt->build_list);
		kमुक्त(rsvd_pkt);
	पूर्ण
पूर्ण

व्योम rtw_add_rsvd_page_bcn(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_vअगर *rtwvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = rtwvअगर_to_vअगर(rtwvअगर);

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_ADHOC &&
	    vअगर->type != NL80211_IFTYPE_MESH_POINT) अणु
		rtw_warn(rtwdev, "Cannot add beacon rsvd page for %d\n",
			 vअगर->type);
		वापस;
	पूर्ण

	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_BEACON, false);
पूर्ण

व्योम rtw_add_rsvd_page_pno(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_vअगर *rtwvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = rtwvअगर_to_vअगर(rtwvअगर);
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा rtw_pno_request *rtw_pno_req = &rtw_wow->pno_req;
	काष्ठा cfg80211_ssid *ssid;
	पूर्णांक i;

	अगर (vअगर->type != NL80211_IFTYPE_STATION) अणु
		rtw_warn(rtwdev, "Cannot add PNO rsvd page for %d\n",
			 vअगर->type);
		वापस;
	पूर्ण

	क्रम (i = 0 ; i < rtw_pno_req->match_set_cnt; i++) अणु
		ssid = &rtw_pno_req->match_sets[i].ssid;
		rtw_add_rsvd_page_probe_req(rtwdev, rtwvअगर, ssid);
	पूर्ण

	rtw_add_rsvd_page_probe_req(rtwdev, rtwvअगर, शून्य);
	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_NLO_INFO, false);
	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_CH_INFO, true);
पूर्ण

व्योम rtw_add_rsvd_page_sta(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_vअगर *rtwvअगर)
अणु
	काष्ठा ieee80211_vअगर *vअगर = rtwvअगर_to_vअगर(rtwvअगर);

	अगर (vअगर->type != NL80211_IFTYPE_STATION) अणु
		rtw_warn(rtwdev, "Cannot add sta rsvd page for %d\n",
			 vअगर->type);
		वापस;
	पूर्ण

	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_PS_POLL, true);
	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_QOS_शून्य, true);
	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_शून्य, true);
	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_LPS_PG_DPK, true);
	rtw_add_rsvd_page(rtwdev, rtwvअगर, RSVD_LPS_PG_INFO, true);
पूर्ण

पूर्णांक rtw_fw_ग_लिखो_data_rsvd_page(काष्ठा rtw_dev *rtwdev, u16 pg_addr,
				u8 *buf, u32 size)
अणु
	u8 bckp[2];
	u8 val;
	u16 rsvd_pg_head;
	u32 bcn_valid_addr;
	u32 bcn_valid_mask;
	पूर्णांक ret;

	lockdep_निश्चित_held(&rtwdev->mutex);

	अगर (!size)
		वापस -EINVAL;

	अगर (rtw_chip_wcpu_11n(rtwdev)) अणु
		rtw_ग_लिखो32_set(rtwdev, REG_DWBCN0_CTRL, BIT_BCN_VALID);
	पूर्ण अन्यथा अणु
		pg_addr &= BIT_MASK_BCN_HEAD_1_V1;
		pg_addr |= BIT_BCN_VALID_V1;
		rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_CTRL_2, pg_addr);
	पूर्ण

	val = rtw_पढ़ो8(rtwdev, REG_CR + 1);
	bckp[0] = val;
	val |= BIT_ENSWBCN >> 8;
	rtw_ग_लिखो8(rtwdev, REG_CR + 1, val);

	val = rtw_पढ़ो8(rtwdev, REG_FWHW_TXQ_CTRL + 2);
	bckp[1] = val;
	val &= ~(BIT_EN_BCNQ_DL >> 16);
	rtw_ग_लिखो8(rtwdev, REG_FWHW_TXQ_CTRL + 2, val);

	ret = rtw_hci_ग_लिखो_data_rsvd_page(rtwdev, buf, size);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to write data to rsvd page\n");
		जाओ restore;
	पूर्ण

	अगर (rtw_chip_wcpu_11n(rtwdev)) अणु
		bcn_valid_addr = REG_DWBCN0_CTRL;
		bcn_valid_mask = BIT_BCN_VALID;
	पूर्ण अन्यथा अणु
		bcn_valid_addr = REG_FIFOPAGE_CTRL_2;
		bcn_valid_mask = BIT_BCN_VALID_V1;
	पूर्ण

	अगर (!check_hw_पढ़ोy(rtwdev, bcn_valid_addr, bcn_valid_mask, 1)) अणु
		rtw_err(rtwdev, "error beacon valid\n");
		ret = -EBUSY;
	पूर्ण

restore:
	rsvd_pg_head = rtwdev->fअगरo.rsvd_boundary;
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_CTRL_2,
		    rsvd_pg_head | BIT_BCN_VALID_V1);
	rtw_ग_लिखो8(rtwdev, REG_FWHW_TXQ_CTRL + 2, bckp[1]);
	rtw_ग_लिखो8(rtwdev, REG_CR + 1, bckp[0]);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_करोwnload_drv_rsvd_page(काष्ठा rtw_dev *rtwdev, u8 *buf, u32 size)
अणु
	u32 pg_size;
	u32 pg_num = 0;
	u16 pg_addr = 0;

	pg_size = rtwdev->chip->page_size;
	pg_num = size / pg_size + ((size & (pg_size - 1)) ? 1 : 0);
	अगर (pg_num > rtwdev->fअगरo.rsvd_drv_pg_num)
		वापस -ENOMEM;

	pg_addr = rtwdev->fअगरo.rsvd_drv_addr;

	वापस rtw_fw_ग_लिखो_data_rsvd_page(rtwdev, pg_addr, buf, size);
पूर्ण

अटल व्योम __rtw_build_rsvd_page_reset(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt, *पंचांगp;

	list_क्रम_each_entry_safe(rsvd_pkt, पंचांगp, &rtwdev->rsvd_page_list,
				 build_list) अणु
		list_del_init(&rsvd_pkt->build_list);

		/* Don't मुक्त except क्रम the dummy rsvd page,
		 * others will be मुक्तd when removing vअगर
		 */
		अगर (rsvd_pkt->type == RSVD_DUMMY)
			kमुक्त(rsvd_pkt);
	पूर्ण
पूर्ण

अटल व्योम rtw_build_rsvd_page_iter(व्योम *data, u8 *mac,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = data;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा rtw_rsvd_page *rsvd_pkt;

	list_क्रम_each_entry(rsvd_pkt, &rtwvअगर->rsvd_page_list, vअगर_list) अणु
		अगर (rsvd_pkt->type == RSVD_BEACON)
			list_add(&rsvd_pkt->build_list,
				 &rtwdev->rsvd_page_list);
		अन्यथा
			list_add_tail(&rsvd_pkt->build_list,
				      &rtwdev->rsvd_page_list);
	पूर्ण
पूर्ण

अटल पूर्णांक  __rtw_build_rsvd_page_from_vअगरs(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_rsvd_page *rsvd_pkt;

	__rtw_build_rsvd_page_reset(rtwdev);

	/* gather rsvd page from vअगरs */
	rtw_iterate_vअगरs_atomic(rtwdev, rtw_build_rsvd_page_iter, rtwdev);

	rsvd_pkt = list_first_entry_or_null(&rtwdev->rsvd_page_list,
					    काष्ठा rtw_rsvd_page, build_list);
	अगर (!rsvd_pkt) अणु
		WARN(1, "Should not have an empty reserved page\n");
		वापस -EINVAL;
	पूर्ण

	/* the first rsvd should be beacon, otherwise add a dummy one */
	अगर (rsvd_pkt->type != RSVD_BEACON) अणु
		काष्ठा rtw_rsvd_page *dummy_pkt;

		dummy_pkt = rtw_alloc_rsvd_page(rtwdev, RSVD_DUMMY, false);
		अगर (!dummy_pkt) अणु
			rtw_err(rtwdev, "failed to alloc dummy rsvd page\n");
			वापस -ENOMEM;
		पूर्ण

		list_add(&dummy_pkt->build_list, &rtwdev->rsvd_page_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 *rtw_build_rsvd_page(काष्ठा rtw_dev *rtwdev, u32 *size)
अणु
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा sk_buff *iter;
	काष्ठा rtw_rsvd_page *rsvd_pkt;
	u32 page = 0;
	u8 total_page = 0;
	u8 page_size, page_margin, tx_desc_sz;
	u8 *buf;
	पूर्णांक ret;

	page_size = chip->page_size;
	tx_desc_sz = chip->tx_pkt_desc_sz;
	page_margin = page_size - tx_desc_sz;

	ret = __rtw_build_rsvd_page_from_vअगरs(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev,
			"failed to build rsvd page from vifs, ret %d\n", ret);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(rsvd_pkt, &rtwdev->rsvd_page_list, build_list) अणु
		iter = rtw_get_rsvd_page_skb(hw, rsvd_pkt);
		अगर (!iter) अणु
			rtw_err(rtwdev, "failed to build rsvd packet\n");
			जाओ release_skb;
		पूर्ण

		/* Fill the tx_desc क्रम the rsvd pkt that requires one.
		 * And iter->len will be added with size of tx_desc_sz.
		 */
		अगर (rsvd_pkt->add_txdesc)
			rtw_fill_rsvd_page_desc(rtwdev, iter, rsvd_pkt->type);

		rsvd_pkt->skb = iter;
		rsvd_pkt->page = total_page;

		/* Reserved page is करोwnloaded via TX path, and TX path will
		 * generate a tx_desc at the header to describe length of
		 * the buffer. If we are not counting page numbers with the
		 * size of tx_desc added at the first rsvd_pkt (usually a
		 * beacon, firmware शेष refer to the first page as the
		 * content of beacon), we could generate a buffer which size
		 * is smaller than the actual size of the whole rsvd_page
		 */
		अगर (total_page == 0) अणु
			अगर (rsvd_pkt->type != RSVD_BEACON &&
			    rsvd_pkt->type != RSVD_DUMMY) अणु
				rtw_err(rtwdev, "first page should be a beacon\n");
				जाओ release_skb;
			पूर्ण
			total_page += rtw_len_to_page(iter->len + tx_desc_sz,
						      page_size);
		पूर्ण अन्यथा अणु
			total_page += rtw_len_to_page(iter->len, page_size);
		पूर्ण
	पूर्ण

	अगर (total_page > rtwdev->fअगरo.rsvd_drv_pg_num) अणु
		rtw_err(rtwdev, "rsvd page over size: %d\n", total_page);
		जाओ release_skb;
	पूर्ण

	*size = (total_page - 1) * page_size + page_margin;
	buf = kzalloc(*size, GFP_KERNEL);
	अगर (!buf)
		जाओ release_skb;

	/* Copy the content of each rsvd_pkt to the buf, and they should
	 * be aligned to the pages.
	 *
	 * Note that the first rsvd_pkt is a beacon no matter what vअगर->type.
	 * And that rsvd_pkt करोes not require tx_desc because when it goes
	 * through TX path, the TX path will generate one क्रम it.
	 */
	list_क्रम_each_entry(rsvd_pkt, &rtwdev->rsvd_page_list, build_list) अणु
		rtw_rsvd_page_list_to_buf(rtwdev, page_size, page_margin,
					  page, buf, rsvd_pkt);
		अगर (page == 0)
			page += rtw_len_to_page(rsvd_pkt->skb->len +
						tx_desc_sz, page_size);
		अन्यथा
			page += rtw_len_to_page(rsvd_pkt->skb->len, page_size);

		kमुक्त_skb(rsvd_pkt->skb);
		rsvd_pkt->skb = शून्य;
	पूर्ण

	वापस buf;

release_skb:
	list_क्रम_each_entry(rsvd_pkt, &rtwdev->rsvd_page_list, build_list) अणु
		kमुक्त_skb(rsvd_pkt->skb);
		rsvd_pkt->skb = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक rtw_करोwnload_beacon(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	काष्ठा rtw_rsvd_page *rsvd_pkt;
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 0;

	rsvd_pkt = list_first_entry_or_null(&rtwdev->rsvd_page_list,
					    काष्ठा rtw_rsvd_page, build_list);
	अगर (!rsvd_pkt) अणु
		rtw_err(rtwdev, "failed to get rsvd page from build list\n");
		वापस -ENOENT;
	पूर्ण

	अगर (rsvd_pkt->type != RSVD_BEACON &&
	    rsvd_pkt->type != RSVD_DUMMY) अणु
		rtw_err(rtwdev, "invalid rsvd page type %d, should be beacon or dummy\n",
			rsvd_pkt->type);
		वापस -EINVAL;
	पूर्ण

	skb = rtw_get_rsvd_page_skb(hw, rsvd_pkt);
	अगर (!skb) अणु
		rtw_err(rtwdev, "failed to get beacon skb\n");
		वापस -ENOMEM;
	पूर्ण

	ret = rtw_करोwnload_drv_rsvd_page(rtwdev, skb->data, skb->len);
	अगर (ret)
		rtw_err(rtwdev, "failed to download drv rsvd page\n");

	dev_kमुक्त_skb(skb);

	वापस ret;
पूर्ण

पूर्णांक rtw_fw_करोwnload_rsvd_page(काष्ठा rtw_dev *rtwdev)
अणु
	u8 *buf;
	u32 size;
	पूर्णांक ret;

	buf = rtw_build_rsvd_page(rtwdev, &size);
	अगर (!buf) अणु
		rtw_err(rtwdev, "failed to build rsvd page pkt\n");
		वापस -ENOMEM;
	पूर्ण

	ret = rtw_करोwnload_drv_rsvd_page(rtwdev, buf, size);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to download drv rsvd page\n");
		जाओ मुक्त;
	पूर्ण

	/* The last thing is to करोwnload the *ONLY* beacon again, because
	 * the previous tx_desc is to describe the total rsvd page. Download
	 * the beacon again to replace the TX desc header, and we will get
	 * a correct tx_desc क्रम the beacon in the rsvd page.
	 */
	ret = rtw_करोwnload_beacon(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to download beacon\n");
		जाओ मुक्त;
	पूर्ण

मुक्त:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल व्योम rtw_fw_पढ़ो_fअगरo_page(काष्ठा rtw_dev *rtwdev, u32 offset, u32 size,
				  u32 *buf, u32 residue, u16 start_pg)
अणु
	u32 i;
	u16 idx = 0;
	u16 ctl;
	u8 rcr;

	rcr = rtw_पढ़ो8(rtwdev, REG_RCR + 2);
	ctl = rtw_पढ़ो16(rtwdev, REG_PKTBUF_DBG_CTRL) & 0xf000;
	/* disable rx घड़ी gate */
	rtw_ग_लिखो8(rtwdev, REG_RCR, rcr | BIT(3));

	करो अणु
		rtw_ग_लिखो16(rtwdev, REG_PKTBUF_DBG_CTRL, start_pg | ctl);

		क्रम (i = FIFO_DUMP_ADDR + residue;
		     i < FIFO_DUMP_ADDR + FIFO_PAGE_SIZE; i += 4) अणु
			buf[idx++] = rtw_पढ़ो32(rtwdev, i);
			size -= 4;
			अगर (size == 0)
				जाओ out;
		पूर्ण

		residue = 0;
		start_pg++;
	पूर्ण जबतक (size);

out:
	rtw_ग_लिखो16(rtwdev, REG_PKTBUF_DBG_CTRL, ctl);
	rtw_ग_लिखो8(rtwdev, REG_RCR + 2, rcr);
पूर्ण

अटल व्योम rtw_fw_पढ़ो_fअगरo(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_fw_fअगरo_sel sel,
			     u32 offset, u32 size, u32 *buf)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u32 start_pg, residue;

	अगर (sel >= RTW_FW_FIFO_MAX) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "wrong fw fifo sel\n");
		वापस;
	पूर्ण
	अगर (sel == RTW_FW_FIFO_SEL_RSVD_PAGE)
		offset += rtwdev->fअगरo.rsvd_boundary << TX_PAGE_SIZE_SHIFT;
	residue = offset & (FIFO_PAGE_SIZE - 1);
	start_pg = (offset >> FIFO_PAGE_SIZE_SHIFT) + chip->fw_fअगरo_addr[sel];

	rtw_fw_पढ़ो_fअगरo_page(rtwdev, offset, size, buf, residue, start_pg);
पूर्ण

अटल bool rtw_fw_dump_check_size(काष्ठा rtw_dev *rtwdev,
				   क्रमागत rtw_fw_fअगरo_sel sel,
				   u32 start_addr, u32 size)
अणु
	चयन (sel) अणु
	हाल RTW_FW_FIFO_SEL_TX:
	हाल RTW_FW_FIFO_SEL_RX:
		अगर ((start_addr + size) > rtwdev->chip->fw_fअगरo_addr[sel])
			वापस false;
		fallthrough;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

पूर्णांक rtw_fw_dump_fअगरo(काष्ठा rtw_dev *rtwdev, u8 fअगरo_sel, u32 addr, u32 size,
		     u32 *buffer)
अणु
	अगर (!rtwdev->chip->fw_fअगरo_addr[0]) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "chip not support dump fw fifo\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (size == 0 || !buffer)
		वापस -EINVAL;

	अगर (size & 0x3) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "not 4byte alignment\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!rtw_fw_dump_check_size(rtwdev, fअगरo_sel, addr, size)) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "fw fifo dump size overflow\n");
		वापस -EINVAL;
	पूर्ण

	rtw_fw_पढ़ो_fअगरo(rtwdev, fअगरo_sel, addr, size, buffer);

	वापस 0;
पूर्ण

अटल व्योम __rtw_fw_update_pkt(काष्ठा rtw_dev *rtwdev, u8 pkt_id, u16 size,
				u8 location)
अणु
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u16 total_size = H2C_PKT_HDR_SIZE + H2C_PKT_UPDATE_PKT_LEN;

	rtw_h2c_pkt_set_header(h2c_pkt, H2C_PKT_UPDATE_PKT);

	SET_PKT_H2C_TOTAL_LEN(h2c_pkt, total_size);
	UPDATE_PKT_SET_PKT_ID(h2c_pkt, pkt_id);
	UPDATE_PKT_SET_LOCATION(h2c_pkt, location);

	/* include txdesc size */
	UPDATE_PKT_SET_SIZE(h2c_pkt, size);

	rtw_fw_send_h2c_packet(rtwdev, h2c_pkt);
पूर्ण

व्योम rtw_fw_update_pkt_probe_req(काष्ठा rtw_dev *rtwdev,
				 काष्ठा cfg80211_ssid *ssid)
अणु
	u8 loc;
	u32 size;

	loc = rtw_get_rsvd_page_probe_req_location(rtwdev, ssid);
	अगर (!loc) अणु
		rtw_err(rtwdev, "failed to get probe_req rsvd loc\n");
		वापस;
	पूर्ण

	size = rtw_get_rsvd_page_probe_req_size(rtwdev, ssid);
	अगर (!size) अणु
		rtw_err(rtwdev, "failed to get probe_req rsvd size\n");
		वापस;
	पूर्ण

	__rtw_fw_update_pkt(rtwdev, RTW_PACKET_PROBE_REQ, size, loc);
पूर्ण

व्योम rtw_fw_channel_चयन(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	काष्ठा rtw_pno_request *rtw_pno_req = &rtwdev->wow.pno_req;
	u8 h2c_pkt[H2C_PKT_SIZE] = अणु0पूर्ण;
	u16 total_size = H2C_PKT_HDR_SIZE + H2C_PKT_CH_SWITCH_LEN;
	u8 loc_ch_info;
	स्थिर काष्ठा rtw_ch_चयन_option cs_option = अणु
		.dest_ch_en = 1,
		.dest_ch = 1,
		.periodic_option = 2,
		.normal_period = 5,
		.normal_period_sel = 0,
		.normal_cycle = 10,
		.slow_period = 1,
		.slow_period_sel = 1,
	पूर्ण;

	rtw_h2c_pkt_set_header(h2c_pkt, H2C_PKT_CH_SWITCH);
	SET_PKT_H2C_TOTAL_LEN(h2c_pkt, total_size);

	CH_SWITCH_SET_START(h2c_pkt, enable);
	CH_SWITCH_SET_DEST_CH_EN(h2c_pkt, cs_option.dest_ch_en);
	CH_SWITCH_SET_DEST_CH(h2c_pkt, cs_option.dest_ch);
	CH_SWITCH_SET_NORMAL_PERIOD(h2c_pkt, cs_option.normal_period);
	CH_SWITCH_SET_NORMAL_PERIOD_SEL(h2c_pkt, cs_option.normal_period_sel);
	CH_SWITCH_SET_SLOW_PERIOD(h2c_pkt, cs_option.slow_period);
	CH_SWITCH_SET_SLOW_PERIOD_SEL(h2c_pkt, cs_option.slow_period_sel);
	CH_SWITCH_SET_NORMAL_CYCLE(h2c_pkt, cs_option.normal_cycle);
	CH_SWITCH_SET_PERIODIC_OPT(h2c_pkt, cs_option.periodic_option);

	CH_SWITCH_SET_CH_NUM(h2c_pkt, rtw_pno_req->channel_cnt);
	CH_SWITCH_SET_INFO_SIZE(h2c_pkt, rtw_pno_req->channel_cnt * 4);

	loc_ch_info = rtw_get_rsvd_page_location(rtwdev, RSVD_CH_INFO);
	CH_SWITCH_SET_INFO_LOC(h2c_pkt, loc_ch_info);

	rtw_fw_send_h2c_packet(rtwdev, h2c_pkt);
पूर्ण
