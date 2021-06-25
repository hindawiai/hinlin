<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "fw.h"
#समावेश "wow.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "mac.h"
#समावेश "ps.h"

अटल व्योम rtw_wow_show_wakeup_reason(काष्ठा rtw_dev *rtwdev)
अणु
	u8 reason;

	reason = rtw_पढ़ो8(rtwdev, REG_WOWLAN_WAKE_REASON);

	अगर (reason == RTW_WOW_RSN_RX_DEAUTH)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: Rx deauth\n");
	अन्यथा अगर (reason == RTW_WOW_RSN_DISCONNECT)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: AP is off\n");
	अन्यथा अगर (reason == RTW_WOW_RSN_RX_MAGIC_PKT)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: Rx magic packet\n");
	अन्यथा अगर (reason == RTW_WOW_RSN_RX_GTK_REKEY)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: Rx gtk rekey\n");
	अन्यथा अगर (reason == RTW_WOW_RSN_RX_PTK_REKEY)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: Rx ptk rekey\n");
	अन्यथा अगर (reason == RTW_WOW_RSN_RX_PATTERN_MATCH)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: Rx pattern match packet\n");
	अन्यथा अगर (reason == RTW_WOW_RSN_RX_NLO)
		rtw_dbg(rtwdev, RTW_DBG_WOW, "Rx NLO\n");
	अन्यथा
		rtw_warn(rtwdev, "Unknown wakeup reason %x\n", reason);
पूर्ण

अटल व्योम rtw_wow_pattern_ग_लिखो_cam(काष्ठा rtw_dev *rtwdev, u8 addr,
				      u32 wdata)
अणु
	rtw_ग_लिखो32(rtwdev, REG_WKFMCAM_RWD, wdata);
	rtw_ग_लिखो32(rtwdev, REG_WKFMCAM_CMD, BIT_WKFCAM_POLLING_V1 |
		    BIT_WKFCAM_WE | BIT_WKFCAM_ADDR_V2(addr));

	अगर (!check_hw_पढ़ोy(rtwdev, REG_WKFMCAM_CMD, BIT_WKFCAM_POLLING_V1, 0))
		rtw_err(rtwdev, "failed to write pattern cam\n");
पूर्ण

अटल व्योम rtw_wow_pattern_ग_लिखो_cam_ent(काष्ठा rtw_dev *rtwdev, u8 id,
					  काष्ठा rtw_wow_pattern *rtw_pattern)
अणु
	पूर्णांक i;
	u8 addr;
	u32 wdata;

	क्रम (i = 0; i < RTW_MAX_PATTERN_MASK_SIZE / 4; i++) अणु
		addr = (id << 3) + i;
		wdata = rtw_pattern->mask[i * 4];
		wdata |= rtw_pattern->mask[i * 4 + 1] << 8;
		wdata |= rtw_pattern->mask[i * 4 + 2] << 16;
		wdata |= rtw_pattern->mask[i * 4 + 3] << 24;
		rtw_wow_pattern_ग_लिखो_cam(rtwdev, addr, wdata);
	पूर्ण

	wdata = rtw_pattern->crc;
	addr = (id << 3) + RTW_MAX_PATTERN_MASK_SIZE / 4;

	चयन (rtw_pattern->type) अणु
	हाल RTW_PATTERN_BROADCAST:
		wdata |= BIT_WKFMCAM_BC | BIT_WKFMCAM_VALID;
		अवरोध;
	हाल RTW_PATTERN_MULTICAST:
		wdata |= BIT_WKFMCAM_MC | BIT_WKFMCAM_VALID;
		अवरोध;
	हाल RTW_PATTERN_UNICAST:
		wdata |= BIT_WKFMCAM_UC | BIT_WKFMCAM_VALID;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtw_wow_pattern_ग_लिखो_cam(rtwdev, addr, wdata);
पूर्ण

/* RTK पूर्णांकernal CRC16 क्रम Pattern Cam */
अटल u16 __rtw_cal_crc16(u8 data, u16 crc)
अणु
	u8 shअगरt_in, data_bit;
	u8 crc_bit4, crc_bit11, crc_bit15;
	u16 crc_result;
	पूर्णांक index;

	क्रम (index = 0; index < 8; index++) अणु
		crc_bit15 = ((crc & BIT(15)) ? 1 : 0);
		data_bit = (data & (BIT(0) << index) ? 1 : 0);
		shअगरt_in = crc_bit15 ^ data_bit;

		crc_result = crc << 1;

		अगर (shअगरt_in == 0)
			crc_result &= (~BIT(0));
		अन्यथा
			crc_result |= BIT(0);

		crc_bit11 = ((crc & BIT(11)) ? 1 : 0) ^ shअगरt_in;

		अगर (crc_bit11 == 0)
			crc_result &= (~BIT(12));
		अन्यथा
			crc_result |= BIT(12);

		crc_bit4 = ((crc & BIT(4)) ? 1 : 0) ^ shअगरt_in;

		अगर (crc_bit4 == 0)
			crc_result &= (~BIT(5));
		अन्यथा
			crc_result |= BIT(5);

		crc = crc_result;
	पूर्ण
	वापस crc;
पूर्ण

अटल u16 rtw_calc_crc(u8 *pdata, पूर्णांक length)
अणु
	u16 crc = 0xffff;
	पूर्णांक i;

	क्रम (i = 0; i < length; i++)
		crc = __rtw_cal_crc16(pdata[i], crc);

	/* get 1' complement */
	वापस ~crc;
पूर्ण

अटल व्योम rtw_wow_pattern_generate(काष्ठा rtw_dev *rtwdev,
				     काष्ठा rtw_vअगर *rtwvअगर,
				     स्थिर काष्ठा cfg80211_pkt_pattern *pkt_pattern,
				     काष्ठा rtw_wow_pattern *rtw_pattern)
अणु
	स्थिर u8 *mask;
	स्थिर u8 *pattern;
	u8 mask_hw[RTW_MAX_PATTERN_MASK_SIZE] = अणु0पूर्ण;
	u8 content[RTW_MAX_PATTERN_SIZE] = अणु0पूर्ण;
	u8 mac_addr[ETH_ALEN] = अणु0पूर्ण;
	u8 mask_len;
	u16 count;
	पूर्णांक len;
	पूर्णांक i;

	pattern = pkt_pattern->pattern;
	len = pkt_pattern->pattern_len;
	mask = pkt_pattern->mask;

	ether_addr_copy(mac_addr, rtwvअगर->mac_addr);
	स_रखो(rtw_pattern, 0, माप(*rtw_pattern));

	mask_len = DIV_ROUND_UP(len, 8);

	अगर (is_broadcast_ether_addr(pattern))
		rtw_pattern->type = RTW_PATTERN_BROADCAST;
	अन्यथा अगर (is_multicast_ether_addr(pattern))
		rtw_pattern->type = RTW_PATTERN_MULTICAST;
	अन्यथा अगर (ether_addr_equal(pattern, mac_addr))
		rtw_pattern->type = RTW_PATTERN_UNICAST;
	अन्यथा
		rtw_pattern->type = RTW_PATTERN_INVALID;

	/* translate mask from os to mask क्रम hw
	 * pattern from OS uses 'ethenet frame', like this:
	 * |    6   |    6   |   2  |     20    |  Variable  |  4  |
	 * |--------+--------+------+-----------+------------+-----|
	 * |    802.3 Mac Header    | IP Header | TCP Packet | FCS |
	 * |   DA   |   SA   | Type |
	 *
	 * BUT, packet catched by our HW is in '802.11 frame', begin from LLC
	 * |     24 or 30      |    6   |   2  |     20    |  Variable  |  4  |
	 * |-------------------+--------+------+-----------+------------+-----|
	 * | 802.11 MAC Header |       LLC     | IP Header | TCP Packet | FCS |
	 *		       | Others | Tpye |
	 *
	 * Thereक्रमe, we need translate mask_from_OS to mask_to_hw.
	 * We should left-shअगरt mask by 6 bits, then set the new bit[0~5] = 0,
	 * because new mask[0~5] means 'SA', but our HW packet begins from LLC,
	 * bit[0~5] corresponds to first 6 Bytes in LLC, they just करोn't match.
	 */

	/* Shअगरt 6 bits */
	क्रम (i = 0; i < mask_len - 1; i++) अणु
		mask_hw[i] = u8_get_bits(mask[i], GENMASK(7, 6));
		mask_hw[i] |= u8_get_bits(mask[i + 1], GENMASK(5, 0)) << 2;
	पूर्ण
	mask_hw[i] = u8_get_bits(mask[i], GENMASK(7, 6));

	/* Set bit 0-5 to zero */
	mask_hw[0] &= (~GENMASK(5, 0));

	स_नकल(rtw_pattern->mask, mask_hw, RTW_MAX_PATTERN_MASK_SIZE);

	/* To get the wake up pattern from the mask.
	 * We करो not count first 12 bits which means
	 * DA[6] and SA[6] in the pattern to match HW design.
	 */
	count = 0;
	क्रम (i = 12; i < len; i++) अणु
		अगर ((mask[i / 8] >> (i % 8)) & 0x01) अणु
			content[count] = pattern[i];
			count++;
		पूर्ण
	पूर्ण

	rtw_pattern->crc = rtw_calc_crc(content, count);
पूर्ण

अटल व्योम rtw_wow_pattern_clear_cam(काष्ठा rtw_dev *rtwdev)
अणु
	bool ret;

	rtw_ग_लिखो32(rtwdev, REG_WKFMCAM_CMD, BIT_WKFCAM_POLLING_V1 |
		    BIT_WKFCAM_CLR_V1);

	ret = check_hw_पढ़ोy(rtwdev, REG_WKFMCAM_CMD, BIT_WKFCAM_POLLING_V1, 0);
	अगर (!ret)
		rtw_err(rtwdev, "failed to clean pattern cam\n");
पूर्ण

अटल व्योम rtw_wow_pattern_ग_लिखो(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा rtw_wow_pattern *rtw_pattern = rtw_wow->patterns;
	पूर्णांक i = 0;

	क्रम (i = 0; i < rtw_wow->pattern_cnt; i++)
		rtw_wow_pattern_ग_लिखो_cam_ent(rtwdev, i, rtw_pattern + i);
पूर्ण

अटल व्योम rtw_wow_pattern_clear(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;

	rtw_wow_pattern_clear_cam(rtwdev);

	rtw_wow->pattern_cnt = 0;
	स_रखो(rtw_wow->patterns, 0, माप(rtw_wow->patterns));
पूर्ण

अटल व्योम rtw_wow_bb_stop(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;

	/* रुको 100ms क्रम firmware to finish TX */
	msleep(100);

	अगर (!rtw_पढ़ो32_mask(rtwdev, REG_BCNQ_INFO, BIT_MGQ_CPU_EMPTY))
		rtw_warn(rtwdev, "Wrong status of MGQ_CPU empty!\n");

	rtw_wow->txछोड़ो = rtw_पढ़ो8(rtwdev, REG_TXPAUSE);
	rtw_ग_लिखो8(rtwdev, REG_TXPAUSE, 0xff);
	rtw_ग_लिखो8_clr(rtwdev, REG_SYS_FUNC_EN, BIT_FEN_BB_RSTB);
पूर्ण

अटल व्योम rtw_wow_bb_start(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;

	rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN, BIT_FEN_BB_RSTB);
	rtw_ग_लिखो8(rtwdev, REG_TXPAUSE, rtw_wow->txछोड़ो);
पूर्ण

अटल व्योम rtw_wow_rx_dma_stop(काष्ठा rtw_dev *rtwdev)
अणु
	/* रुको 100ms क्रम HW to finish rx dma */
	msleep(100);

	rtw_ग_लिखो32_set(rtwdev, REG_RXPKT_NUM, BIT_RW_RELEASE);

	अगर (!check_hw_पढ़ोy(rtwdev, REG_RXPKT_NUM, BIT_RXDMA_IDLE, 1))
		rtw_err(rtwdev, "failed to stop rx dma\n");
पूर्ण

अटल व्योम rtw_wow_rx_dma_start(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32_clr(rtwdev, REG_RXPKT_NUM, BIT_RW_RELEASE);
पूर्ण

अटल पूर्णांक rtw_wow_check_fw_status(काष्ठा rtw_dev *rtwdev, bool wow_enable)
अणु
	/* रुको 100ms क्रम wow firmware to finish work */
	msleep(100);

	अगर (wow_enable) अणु
		अगर (rtw_पढ़ो8(rtwdev, REG_WOWLAN_WAKE_REASON))
			जाओ wow_fail;
	पूर्ण अन्यथा अणु
		अगर (rtw_पढ़ो32_mask(rtwdev, REG_FE1IMR, BIT_FS_RXDONE) ||
		    rtw_पढ़ो32_mask(rtwdev, REG_RXPKT_NUM, BIT_RW_RELEASE))
			जाओ wow_fail;
	पूर्ण

	वापस 0;

wow_fail:
	rtw_err(rtwdev, "failed to check wow status %s\n",
		wow_enable ? "enabled" : "disabled");
	वापस -EBUSY;
पूर्ण

अटल व्योम rtw_wow_fw_security_type_iter(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा ieee80211_sta *sta,
					  काष्ठा ieee80211_key_conf *key,
					  व्योम *data)
अणु
	काष्ठा rtw_fw_key_type_iter_data *iter_data = data;
	काष्ठा rtw_dev *rtwdev = hw->priv;
	u8 hw_key_type;

	अगर (vअगर != rtwdev->wow.wow_vअगर)
		वापस;

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		hw_key_type = RTW_CAM_WEP40;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		hw_key_type = RTW_CAM_WEP104;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		hw_key_type = RTW_CAM_TKIP;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		hw_key_type = RTW_CAM_AES;
		key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
		अवरोध;
	शेष:
		rtw_err(rtwdev, "Unsupported key type for wowlan mode: %#x\n",
			key->cipher);
		hw_key_type = 0;
		अवरोध;
	पूर्ण

	अगर (sta)
		iter_data->pairwise_key_type = hw_key_type;
	अन्यथा
		iter_data->group_key_type = hw_key_type;
पूर्ण

अटल व्योम rtw_wow_fw_security_type(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fw_key_type_iter_data data = अणुपूर्ण;
	काष्ठा ieee80211_vअगर *wow_vअगर = rtwdev->wow.wow_vअगर;

	data.rtwdev = rtwdev;
	rtw_iterate_keys(rtwdev, wow_vअगर,
			 rtw_wow_fw_security_type_iter, &data);
	rtw_fw_set_aoac_global_info_cmd(rtwdev, data.pairwise_key_type,
					data.group_key_type);
पूर्ण

अटल पूर्णांक rtw_wow_fw_start(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtw_wow_mgd_linked(rtwdev)) अणु
		rtw_send_rsvd_page_h2c(rtwdev);
		rtw_wow_pattern_ग_लिखो(rtwdev);
		rtw_wow_fw_security_type(rtwdev);
		rtw_fw_set_disconnect_decision_cmd(rtwdev, true);
		rtw_fw_set_keep_alive_cmd(rtwdev, true);
	पूर्ण अन्यथा अगर (rtw_wow_no_link(rtwdev)) अणु
		rtw_fw_set_nlo_info(rtwdev, true);
		rtw_fw_update_pkt_probe_req(rtwdev, शून्य);
		rtw_fw_channel_चयन(rtwdev, true);
	पूर्ण

	rtw_fw_set_wowlan_ctrl_cmd(rtwdev, true);
	rtw_fw_set_remote_wake_ctrl_cmd(rtwdev, true);

	वापस rtw_wow_check_fw_status(rtwdev, true);
पूर्ण

अटल पूर्णांक rtw_wow_fw_stop(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtw_wow_mgd_linked(rtwdev)) अणु
		rtw_fw_set_disconnect_decision_cmd(rtwdev, false);
		rtw_fw_set_keep_alive_cmd(rtwdev, false);
		rtw_wow_pattern_clear(rtwdev);
	पूर्ण अन्यथा अगर (rtw_wow_no_link(rtwdev)) अणु
		rtw_fw_channel_चयन(rtwdev, false);
		rtw_fw_set_nlo_info(rtwdev, false);
	पूर्ण

	rtw_fw_set_wowlan_ctrl_cmd(rtwdev, false);
	rtw_fw_set_remote_wake_ctrl_cmd(rtwdev, false);

	वापस rtw_wow_check_fw_status(rtwdev, false);
पूर्ण

अटल व्योम rtw_wow_aव्योम_reset_mac(काष्ठा rtw_dev *rtwdev)
अणु
	/* When resuming from wowlan mode, some hosts issue संकेत
	 * (PCIE: PREST, USB: SE0RST) to device, and lead to reset
	 * mac core. If it happens, the connection to AP will be lost.
	 * Setting REG_RSV_CTRL Register can aव्योम this process.
	 */
	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
	हाल RTW_HCI_TYPE_USB:
		rtw_ग_लिखो8(rtwdev, REG_RSV_CTRL, BIT_WLOCK_1C_B6);
		rtw_ग_लिखो8(rtwdev, REG_RSV_CTRL,
			   BIT_WLOCK_1C_B6 | BIT_R_DIS_PRST);
		अवरोध;
	शेष:
		rtw_warn(rtwdev, "Unsupported hci type to disable reset MAC\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw_wow_fw_media_status_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;
	काष्ठा rtw_fw_media_status_iter_data *iter_data = data;
	काष्ठा rtw_dev *rtwdev = iter_data->rtwdev;

	rtw_fw_media_status_report(rtwdev, si->mac_id, iter_data->connect);
पूर्ण

अटल व्योम rtw_wow_fw_media_status(काष्ठा rtw_dev *rtwdev, bool connect)
अणु
	काष्ठा rtw_fw_media_status_iter_data data;

	data.rtwdev = rtwdev;
	data.connect = connect;

	rtw_iterate_stas_atomic(rtwdev, rtw_wow_fw_media_status_iter, &data);
पूर्ण

अटल व्योम rtw_wow_config_pno_rsvd_page(काष्ठा rtw_dev *rtwdev,
					 काष्ठा rtw_vअगर *rtwvअगर)
अणु
	rtw_add_rsvd_page_pno(rtwdev, rtwvअगर);
पूर्ण

अटल व्योम rtw_wow_config_linked_rsvd_page(काष्ठा rtw_dev *rtwdev,
					   काष्ठा rtw_vअगर *rtwvअगर)
अणु
	rtw_add_rsvd_page_sta(rtwdev, rtwvअगर);
पूर्ण

अटल व्योम rtw_wow_config_rsvd_page(काष्ठा rtw_dev *rtwdev,
				     काष्ठा rtw_vअगर *rtwvअगर)
अणु
	rtw_हटाओ_rsvd_page(rtwdev, rtwvअगर);

	अगर (rtw_wow_mgd_linked(rtwdev)) अणु
		rtw_wow_config_linked_rsvd_page(rtwdev, rtwvअगर);
	पूर्ण अन्यथा अगर (test_bit(RTW_FLAG_WOWLAN, rtwdev->flags) &&
		   rtw_wow_no_link(rtwdev)) अणु
		rtw_wow_config_pno_rsvd_page(rtwdev, rtwvअगर);
	पूर्ण
पूर्ण

अटल पूर्णांक rtw_wow_dl_fw_rsvd_page(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा ieee80211_vअगर *wow_vअगर = rtwdev->wow.wow_vअगर;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)wow_vअगर->drv_priv;

	rtw_wow_config_rsvd_page(rtwdev, rtwvअगर);

	वापस rtw_fw_करोwnload_rsvd_page(rtwdev);
पूर्ण

अटल पूर्णांक rtw_wow_swap_fw(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_fw_type type)
अणु
	काष्ठा rtw_fw_state *fw;
	पूर्णांक ret;

	चयन (type) अणु
	हाल RTW_WOWLAN_FW:
		fw = &rtwdev->wow_fw;
		अवरोध;

	हाल RTW_NORMAL_FW:
		fw = &rtwdev->fw;
		अवरोध;

	शेष:
		rtw_warn(rtwdev, "unsupported firmware type to swap\n");
		वापस -ENOENT;
	पूर्ण

	ret = rtw_करोwnload_firmware(rtwdev, fw);
	अगर (ret)
		जाओ out;

	rtw_fw_send_general_info(rtwdev);
	rtw_fw_send_phydm_info(rtwdev);
	rtw_wow_fw_media_status(rtwdev, true);

out:
	वापस ret;
पूर्ण

अटल व्योम rtw_wow_check_pno(काष्ठा rtw_dev *rtwdev,
			      काष्ठा cfg80211_sched_scan_request *nd_config)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा rtw_pno_request *pno_req = &rtw_wow->pno_req;
	काष्ठा ieee80211_channel *channel;
	पूर्णांक i, size;

	अगर (!nd_config->n_match_sets || !nd_config->n_channels)
		जाओ err;

	pno_req->match_set_cnt = nd_config->n_match_sets;
	size = माप(*pno_req->match_sets) * pno_req->match_set_cnt;
	pno_req->match_sets = kmemdup(nd_config->match_sets, size, GFP_KERNEL);
	अगर (!pno_req->match_sets)
		जाओ err;

	pno_req->channel_cnt = nd_config->n_channels;
	size = माप(*nd_config->channels[0]) * nd_config->n_channels;
	pno_req->channels = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!pno_req->channels)
		जाओ channel_err;

	क्रम (i = 0 ; i < pno_req->channel_cnt; i++) अणु
		channel = pno_req->channels + i;
		स_नकल(channel, nd_config->channels[i], माप(*channel));
	पूर्ण

	pno_req->scan_plan = *nd_config->scan_plans;
	pno_req->inited = true;

	rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: net-detect is enabled\n");

	वापस;

channel_err:
	kमुक्त(pno_req->match_sets);

err:
	rtw_dbg(rtwdev, RTW_DBG_WOW, "WOW: net-detect is disabled\n");
पूर्ण

अटल पूर्णांक rtw_wow_leave_linked_ps(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (!test_bit(RTW_FLAG_WOWLAN, rtwdev->flags))
		cancel_delayed_work_sync(&rtwdev->watch_करोg_work);

	rtw_leave_lps(rtwdev);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wow_leave_no_link_ps(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	पूर्णांक ret = 0;

	अगर (test_bit(RTW_FLAG_WOWLAN, rtwdev->flags)) अणु
		अगर (rtw_get_lps_deep_mode(rtwdev) != LPS_DEEP_MODE_NONE)
			rtw_leave_lps_deep(rtwdev);
	पूर्ण अन्यथा अणु
		अगर (test_bit(RTW_FLAG_INACTIVE_PS, rtwdev->flags)) अणु
			rtw_wow->ips_enabled = true;
			ret = rtw_leave_ips(rtwdev);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wow_leave_ps(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret = 0;

	अगर (rtw_wow_mgd_linked(rtwdev))
		ret = rtw_wow_leave_linked_ps(rtwdev);
	अन्यथा अगर (rtw_wow_no_link(rtwdev))
		ret = rtw_wow_leave_no_link_ps(rtwdev);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wow_restore_ps(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret = 0;

	अगर (rtw_wow_no_link(rtwdev) && rtwdev->wow.ips_enabled)
		ret = rtw_enter_ips(rtwdev);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wow_enter_linked_ps(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा ieee80211_vअगर *wow_vअगर = rtw_wow->wow_vअगर;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)wow_vअगर->drv_priv;

	rtw_enter_lps(rtwdev, rtwvअगर->port);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wow_enter_no_link_ps(काष्ठा rtw_dev *rtwdev)
अणु
	/* firmware enters deep ps by itself अगर supported */
	set_bit(RTW_FLAG_LEISURE_PS_DEEP, rtwdev->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_wow_enter_ps(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret = 0;

	अगर (rtw_wow_mgd_linked(rtwdev))
		ret = rtw_wow_enter_linked_ps(rtwdev);
	अन्यथा अगर (rtw_wow_no_link(rtwdev) &&
		 rtw_get_lps_deep_mode(rtwdev) != LPS_DEEP_MODE_NONE)
		ret = rtw_wow_enter_no_link_ps(rtwdev);

	वापस ret;
पूर्ण

अटल व्योम rtw_wow_stop_trx(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_wow_bb_stop(rtwdev);
	rtw_wow_rx_dma_stop(rtwdev);
पूर्ण

अटल पूर्णांक rtw_wow_start(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	ret = rtw_wow_fw_start(rtwdev);
	अगर (ret)
		जाओ out;

	rtw_hci_stop(rtwdev);
	rtw_wow_bb_start(rtwdev);
	rtw_wow_aव्योम_reset_mac(rtwdev);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wow_enable(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret = 0;

	rtw_wow_stop_trx(rtwdev);

	ret = rtw_wow_swap_fw(rtwdev, RTW_WOWLAN_FW);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to swap wow fw\n");
		जाओ error;
	पूर्ण

	set_bit(RTW_FLAG_WOWLAN, rtwdev->flags);

	ret = rtw_wow_dl_fw_rsvd_page(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to download wowlan rsvd page\n");
		जाओ error;
	पूर्ण

	ret = rtw_wow_start(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to start wow\n");
		जाओ error;
	पूर्ण

	वापस ret;

error:
	clear_bit(RTW_FLAG_WOWLAN, rtwdev->flags);
	वापस ret;
पूर्ण

अटल पूर्णांक rtw_wow_stop(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	/* some HCI related रेजिस्टरs will be reset after resume,
	 * need to set them again.
	 */
	ret = rtw_hci_setup(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to setup hci\n");
		वापस ret;
	पूर्ण

	ret = rtw_hci_start(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to start hci\n");
		वापस ret;
	पूर्ण

	ret = rtw_wow_fw_stop(rtwdev);
	अगर (ret)
		rtw_err(rtwdev, "failed to stop wowlan fw\n");

	rtw_wow_bb_stop(rtwdev);

	वापस ret;
पूर्ण

अटल व्योम rtw_wow_resume_trx(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_wow_rx_dma_start(rtwdev);
	rtw_wow_bb_start(rtwdev);
	ieee80211_queue_delayed_work(rtwdev->hw, &rtwdev->watch_करोg_work,
				     RTW_WATCH_DOG_DELAY_TIME);
पूर्ण

अटल पूर्णांक rtw_wow_disable(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	clear_bit(RTW_FLAG_WOWLAN, rtwdev->flags);

	ret = rtw_wow_stop(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to stop wow\n");
		जाओ out;
	पूर्ण

	ret = rtw_wow_swap_fw(rtwdev, RTW_NORMAL_FW);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to swap normal fw\n");
		जाओ out;
	पूर्ण

	ret = rtw_wow_dl_fw_rsvd_page(rtwdev);
	अगर (ret)
		rtw_err(rtwdev, "failed to download normal rsvd page\n");

out:
	rtw_wow_resume_trx(rtwdev);
	वापस ret;
पूर्ण

अटल व्योम rtw_wow_vअगर_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = data;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;

	/* Current wowlan function support setting of only one STATION vअगर.
	 * So when one suitable vअगर is found, stop the iteration.
	 */
	अगर (rtw_wow->wow_vअगर || vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	चयन (rtwvअगर->net_type) अणु
	हाल RTW_NET_MGD_LINKED:
		rtw_wow->wow_vअगर = vअगर;
		अवरोध;
	हाल RTW_NET_NO_LINK:
		अगर (rtw_wow->pno_req.inited)
			rtwdev->wow.wow_vअगर = vअगर;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rtw_wow_set_wakeups(काष्ठा rtw_dev *rtwdev,
			       काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा rtw_wow_pattern *rtw_patterns = rtw_wow->patterns;
	काष्ठा rtw_vअगर *rtwvअगर;
	पूर्णांक i;

	अगर (wowlan->disconnect)
		set_bit(RTW_WOW_FLAG_EN_DISCONNECT, rtw_wow->flags);
	अगर (wowlan->magic_pkt)
		set_bit(RTW_WOW_FLAG_EN_MAGIC_PKT, rtw_wow->flags);
	अगर (wowlan->gtk_rekey_failure)
		set_bit(RTW_WOW_FLAG_EN_REKEY_PKT, rtw_wow->flags);

	अगर (wowlan->nd_config)
		rtw_wow_check_pno(rtwdev, wowlan->nd_config);

	rtw_iterate_vअगरs_atomic(rtwdev, rtw_wow_vअगर_iter, rtwdev);
	अगर (!rtw_wow->wow_vअगर)
		वापस -EPERM;

	rtwvअगर = (काष्ठा rtw_vअगर *)rtw_wow->wow_vअगर->drv_priv;
	अगर (wowlan->n_patterns && wowlan->patterns) अणु
		rtw_wow->pattern_cnt = wowlan->n_patterns;
		क्रम (i = 0; i < wowlan->n_patterns; i++)
			rtw_wow_pattern_generate(rtwdev, rtwvअगर,
						 wowlan->patterns + i,
						 rtw_patterns + i);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtw_wow_clear_wakeups(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_wow_param *rtw_wow = &rtwdev->wow;
	काष्ठा rtw_pno_request *pno_req = &rtw_wow->pno_req;

	अगर (pno_req->inited) अणु
		kमुक्त(pno_req->channels);
		kमुक्त(pno_req->match_sets);
	पूर्ण

	स_रखो(rtw_wow, 0, माप(rtwdev->wow));
पूर्ण

पूर्णांक rtw_wow_suspend(काष्ठा rtw_dev *rtwdev, काष्ठा cfg80211_wowlan *wowlan)
अणु
	पूर्णांक ret = 0;

	ret = rtw_wow_set_wakeups(rtwdev, wowlan);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to set wakeup event\n");
		जाओ out;
	पूर्ण

	ret = rtw_wow_leave_ps(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to leave ps from normal mode\n");
		जाओ out;
	पूर्ण

	ret = rtw_wow_enable(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to enable wow\n");
		rtw_wow_restore_ps(rtwdev);
		जाओ out;
	पूर्ण

	ret = rtw_wow_enter_ps(rtwdev);
	अगर (ret)
		rtw_err(rtwdev, "failed to enter ps for wow\n");

out:
	वापस ret;
पूर्ण

पूर्णांक rtw_wow_resume(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	/* If wowlan mode is not enabled, करो nothing */
	अगर (!test_bit(RTW_FLAG_WOWLAN, rtwdev->flags)) अणु
		rtw_err(rtwdev, "wow is not enabled\n");
		ret = -EPERM;
		जाओ out;
	पूर्ण

	ret = rtw_wow_leave_ps(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to leave ps from wowlan mode\n");
		जाओ out;
	पूर्ण

	rtw_wow_show_wakeup_reason(rtwdev);

	ret = rtw_wow_disable(rtwdev);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to disable wow\n");
		जाओ out;
	पूर्ण

	ret = rtw_wow_restore_ps(rtwdev);
	अगर (ret)
		rtw_err(rtwdev, "failed to restore ps to normal mode\n");

out:
	rtw_wow_clear_wakeups(rtwdev);
	वापस ret;
पूर्ण
