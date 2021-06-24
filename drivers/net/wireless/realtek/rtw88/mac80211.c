<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "sec.h"
#समावेश "tx.h"
#समावेश "fw.h"
#समावेश "mac.h"
#समावेश "coex.h"
#समावेश "ps.h"
#समावेश "reg.h"
#समावेश "bf.h"
#समावेश "debug.h"
#समावेश "wow.h"

अटल व्योम rtw_ops_tx(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	अगर (!test_bit(RTW_FLAG_RUNNING, rtwdev->flags)) अणु
		ieee80211_मुक्त_txskb(hw, skb);
		वापस;
	पूर्ण

	rtw_tx(rtwdev, control, skb);
पूर्ण

अटल व्योम rtw_ops_wake_tx_queue(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_txq *rtwtxq = (काष्ठा rtw_txq *)txq->drv_priv;

	अगर (!test_bit(RTW_FLAG_RUNNING, rtwdev->flags))
		वापस;

	spin_lock_bh(&rtwdev->txq_lock);
	अगर (list_empty(&rtwtxq->list))
		list_add_tail(&rtwtxq->list, &rtwdev->txqs);
	spin_unlock_bh(&rtwdev->txq_lock);

	queue_work(rtwdev->tx_wq, &rtwdev->tx_work);
पूर्ण

अटल पूर्णांक rtw_ops_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	पूर्णांक ret;

	mutex_lock(&rtwdev->mutex);
	ret = rtw_core_start(rtwdev);
	mutex_unlock(&rtwdev->mutex);

	वापस ret;
पूर्ण

अटल व्योम rtw_ops_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	rtw_core_stop(rtwdev);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल पूर्णांक rtw_ops_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	पूर्णांक ret = 0;

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	अगर ((changed & IEEE80211_CONF_CHANGE_IDLE) &&
	    !(hw->conf.flags & IEEE80211_CONF_IDLE)) अणु
		ret = rtw_leave_ips(rtwdev);
		अगर (ret) अणु
			rtw_err(rtwdev, "failed to leave idle state\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		अगर (hw->conf.flags & IEEE80211_CONF_PS) अणु
			rtwdev->ps_enabled = true;
		पूर्ण अन्यथा अणु
			rtwdev->ps_enabled = false;
			rtw_leave_lps(rtwdev);
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL)
		rtw_set_channel(rtwdev);

	अगर ((changed & IEEE80211_CONF_CHANGE_IDLE) &&
	    (hw->conf.flags & IEEE80211_CONF_IDLE))
		rtw_enter_ips(rtwdev);

out:
	mutex_unlock(&rtwdev->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rtw_vअगर_port rtw_vअगर_port[] = अणु
	[0] = अणु
		.mac_addr	= अणु.addr = 0x0610पूर्ण,
		.bssid		= अणु.addr = 0x0618पूर्ण,
		.net_type	= अणु.addr = 0x0100, .mask = 0x30000पूर्ण,
		.aid		= अणु.addr = 0x06a8, .mask = 0x7ffपूर्ण,
		.bcn_ctrl	= अणु.addr = 0x0550, .mask = 0xffपूर्ण,
	पूर्ण,
	[1] = अणु
		.mac_addr	= अणु.addr = 0x0700पूर्ण,
		.bssid		= अणु.addr = 0x0708पूर्ण,
		.net_type	= अणु.addr = 0x0100, .mask = 0xc0000पूर्ण,
		.aid		= अणु.addr = 0x0710, .mask = 0x7ffपूर्ण,
		.bcn_ctrl	= अणु.addr = 0x0551, .mask = 0xffपूर्ण,
	पूर्ण,
	[2] = अणु
		.mac_addr	= अणु.addr = 0x1620पूर्ण,
		.bssid		= अणु.addr = 0x1628पूर्ण,
		.net_type	= अणु.addr = 0x1100, .mask = 0x3पूर्ण,
		.aid		= अणु.addr = 0x1600, .mask = 0x7ffपूर्ण,
		.bcn_ctrl	= अणु.addr = 0x0578, .mask = 0xffपूर्ण,
	पूर्ण,
	[3] = अणु
		.mac_addr	= अणु.addr = 0x1630पूर्ण,
		.bssid		= अणु.addr = 0x1638पूर्ण,
		.net_type	= अणु.addr = 0x1100, .mask = 0xcपूर्ण,
		.aid		= अणु.addr = 0x1604, .mask = 0x7ffपूर्ण,
		.bcn_ctrl	= अणु.addr = 0x0579, .mask = 0xffपूर्ण,
	पूर्ण,
	[4] = अणु
		.mac_addr	= अणु.addr = 0x1640पूर्ण,
		.bssid		= अणु.addr = 0x1648पूर्ण,
		.net_type	= अणु.addr = 0x1100, .mask = 0x30पूर्ण,
		.aid		= अणु.addr = 0x1608, .mask = 0x7ffपूर्ण,
		.bcn_ctrl	= अणु.addr = 0x057a, .mask = 0xffपूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rtw_ops_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	क्रमागत rtw_net_type net_type;
	u32 config = 0;
	u8 port = 0;
	u8 bcn_ctrl = 0;

	rtwvअगर->port = port;
	rtwvअगर->stats.tx_unicast = 0;
	rtwvअगर->stats.rx_unicast = 0;
	rtwvअगर->stats.tx_cnt = 0;
	rtwvअगर->stats.rx_cnt = 0;
	स_रखो(&rtwvअगर->bfee, 0, माप(काष्ठा rtw_bfee));
	rtwvअगर->conf = &rtw_vअगर_port[port];
	rtw_txq_init(rtwdev, vअगर->txq);
	INIT_LIST_HEAD(&rtwvअगर->rsvd_page_list);

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
		rtw_add_rsvd_page_bcn(rtwdev, rtwvअगर);
		net_type = RTW_NET_AP_MODE;
		bcn_ctrl = BIT_EN_BCN_FUNCTION | BIT_DIS_TSF_UDT;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		rtw_add_rsvd_page_bcn(rtwdev, rtwvअगर);
		net_type = RTW_NET_AD_HOC;
		bcn_ctrl = BIT_EN_BCN_FUNCTION | BIT_DIS_TSF_UDT;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		rtw_add_rsvd_page_sta(rtwdev, rtwvअगर);
		net_type = RTW_NET_NO_LINK;
		bcn_ctrl = BIT_EN_BCN_FUNCTION;
		अवरोध;
	शेष:
		WARN_ON(1);
		mutex_unlock(&rtwdev->mutex);
		वापस -EINVAL;
	पूर्ण

	ether_addr_copy(rtwvअगर->mac_addr, vअगर->addr);
	config |= PORT_SET_MAC_ADDR;
	rtwvअगर->net_type = net_type;
	config |= PORT_SET_NET_TYPE;
	rtwvअगर->bcn_ctrl = bcn_ctrl;
	config |= PORT_SET_BCN_CTRL;
	rtw_vअगर_port_config(rtwdev, rtwvअगर, config);

	mutex_unlock(&rtwdev->mutex);

	rtw_info(rtwdev, "start vif %pM on port %d\n", vअगर->addr, rtwvअगर->port);
	वापस 0;
पूर्ण

अटल व्योम rtw_ops_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	u32 config = 0;

	rtw_info(rtwdev, "stop vif %pM on port %d\n", vअगर->addr, rtwvअगर->port);

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	rtw_txq_cleanup(rtwdev, vअगर->txq);
	rtw_हटाओ_rsvd_page(rtwdev, rtwvअगर);

	eth_zero_addr(rtwvअगर->mac_addr);
	config |= PORT_SET_MAC_ADDR;
	rtwvअगर->net_type = RTW_NET_NO_LINK;
	config |= PORT_SET_NET_TYPE;
	rtwvअगर->bcn_ctrl = 0;
	config |= PORT_SET_BCN_CTRL;
	rtw_vअगर_port_config(rtwdev, rtwvअगर, config);

	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल पूर्णांक rtw_ops_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    क्रमागत nl80211_अगरtype type, bool p2p)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	rtw_info(rtwdev, "change vif %pM (%d)->(%d), p2p (%d)->(%d)\n",
		 vअगर->addr, vअगर->type, type, vअगर->p2p, p2p);

	rtw_ops_हटाओ_पूर्णांकerface(hw, vअगर);

	vअगर->type = type;
	vअगर->p2p = p2p;

	वापस rtw_ops_add_पूर्णांकerface(hw, vअगर);
पूर्ण

अटल व्योम rtw_ops_configure_filter(काष्ठा ieee80211_hw *hw,
				     अचिन्हित पूर्णांक changed_flags,
				     अचिन्हित पूर्णांक *new_flags,
				     u64 multicast)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	*new_flags &= FIF_ALLMULTI | FIF_OTHER_BSS | FIF_FCSFAIL |
		      FIF_BCN_PRBRESP_PROMISC;

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	अगर (changed_flags & FIF_ALLMULTI) अणु
		अगर (*new_flags & FIF_ALLMULTI)
			rtwdev->hal.rcr |= BIT_AM | BIT_AB;
		अन्यथा
			rtwdev->hal.rcr &= ~(BIT_AM | BIT_AB);
	पूर्ण
	अगर (changed_flags & FIF_FCSFAIL) अणु
		अगर (*new_flags & FIF_FCSFAIL)
			rtwdev->hal.rcr |= BIT_ACRC32;
		अन्यथा
			rtwdev->hal.rcr &= ~(BIT_ACRC32);
	पूर्ण
	अगर (changed_flags & FIF_OTHER_BSS) अणु
		अगर (*new_flags & FIF_OTHER_BSS)
			rtwdev->hal.rcr |= BIT_AAP;
		अन्यथा
			rtwdev->hal.rcr &= ~(BIT_AAP);
	पूर्ण
	अगर (changed_flags & FIF_BCN_PRBRESP_PROMISC) अणु
		अगर (*new_flags & FIF_BCN_PRBRESP_PROMISC)
			rtwdev->hal.rcr &= ~(BIT_CBSSID_BCN | BIT_CBSSID_DATA);
		अन्यथा
			rtwdev->hal.rcr |= BIT_CBSSID_BCN;
	पूर्ण

	rtw_dbg(rtwdev, RTW_DBG_RX,
		"config rx filter, changed=0x%08x, new=0x%08x, rcr=0x%08x\n",
		changed_flags, *new_flags, rtwdev->hal.rcr);

	rtw_ग_लिखो32(rtwdev, REG_RCR, rtwdev->hal.rcr);

	mutex_unlock(&rtwdev->mutex);
पूर्ण

/* Only have one group of EDCA parameters now */
अटल स्थिर u32 ac_to_edca_param[IEEE80211_NUM_ACS] = अणु
	[IEEE80211_AC_VO] = REG_EDCA_VO_PARAM,
	[IEEE80211_AC_VI] = REG_EDCA_VI_PARAM,
	[IEEE80211_AC_BE] = REG_EDCA_BE_PARAM,
	[IEEE80211_AC_BK] = REG_EDCA_BK_PARAM,
पूर्ण;

अटल u8 rtw_aअगरsn_to_aअगरs(काष्ठा rtw_dev *rtwdev,
			    काष्ठा rtw_vअगर *rtwvअगर, u8 aअगरsn)
अणु
	काष्ठा ieee80211_vअगर *vअगर = rtwvअगर_to_vअगर(rtwvअगर);
	u8 slot_समय;
	u8 sअगरs;

	slot_समय = vअगर->bss_conf.use_लघु_slot ? 9 : 20;
	sअगरs = rtwdev->hal.current_band_type == RTW_BAND_5G ? 16 : 10;

	वापस aअगरsn * slot_समय + sअगरs;
पूर्ण

अटल व्योम __rtw_conf_tx(काष्ठा rtw_dev *rtwdev,
			  काष्ठा rtw_vअगर *rtwvअगर, u16 ac)
अणु
	काष्ठा ieee80211_tx_queue_params *params = &rtwvअगर->tx_params[ac];
	u32 edca_param = ac_to_edca_param[ac];
	u8 ecw_max, ecw_min;
	u8 aअगरs;

	/* 2^ecw - 1 = cw; ecw = log2(cw + 1) */
	ecw_max = ilog2(params->cw_max + 1);
	ecw_min = ilog2(params->cw_min + 1);
	aअगरs = rtw_aअगरsn_to_aअगरs(rtwdev, rtwvअगर, params->aअगरs);
	rtw_ग_लिखो32_mask(rtwdev, edca_param, BIT_MASK_TXOP_LMT, params->txop);
	rtw_ग_लिखो32_mask(rtwdev, edca_param, BIT_MASK_CWMAX, ecw_max);
	rtw_ग_लिखो32_mask(rtwdev, edca_param, BIT_MASK_CWMIN, ecw_min);
	rtw_ग_लिखो32_mask(rtwdev, edca_param, BIT_MASK_AIFS, aअगरs);
पूर्ण

अटल व्योम rtw_conf_tx(काष्ठा rtw_dev *rtwdev,
			काष्ठा rtw_vअगर *rtwvअगर)
अणु
	u16 ac;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		__rtw_conf_tx(rtwdev, rtwvअगर, ac);
पूर्ण

अटल व्योम rtw_ops_bss_info_changed(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_bss_conf *conf,
				     u32 changed)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	u32 config = 0;

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		rtw_vअगर_assoc_changed(rtwvअगर, conf);
		अगर (conf->assoc) अणु
			rtw_coex_connect_notअगरy(rtwdev, COEX_ASSOCIATE_FINISH);

			rtw_fw_करोwnload_rsvd_page(rtwdev);
			rtw_send_rsvd_page_h2c(rtwdev);
			rtw_coex_media_status_notअगरy(rtwdev, conf->assoc);
			अगर (rtw_bf_support)
				rtw_bf_assoc(rtwdev, vअगर, conf);
		पूर्ण अन्यथा अणु
			rtw_leave_lps(rtwdev);
			rtw_bf_disassoc(rtwdev, vअगर, conf);
		पूर्ण

		config |= PORT_SET_NET_TYPE;
		config |= PORT_SET_AID;
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID) अणु
		ether_addr_copy(rtwvअगर->bssid, conf->bssid);
		config |= PORT_SET_BSSID;
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		अगर (ieee80211_vअगर_type_p2p(vअगर) == NL80211_IFTYPE_STATION)
			coex_stat->wl_beacon_पूर्णांकerval = conf->beacon_पूर्णांक;
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON)
		rtw_fw_करोwnload_rsvd_page(rtwdev);

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		अगर (conf->enable_beacon)
			rtw_ग_लिखो32_set(rtwdev, REG_FWHW_TXQ_CTRL,
					BIT_EN_BCNQ_DL);
		अन्यथा
			rtw_ग_लिखो32_clr(rtwdev, REG_FWHW_TXQ_CTRL,
					BIT_EN_BCNQ_DL);
	पूर्ण

	अगर (changed & BSS_CHANGED_MU_GROUPS)
		rtw_chip_set_gid_table(rtwdev, vअगर, conf);

	अगर (changed & BSS_CHANGED_ERP_SLOT)
		rtw_conf_tx(rtwdev, rtwvअगर);

	rtw_vअगर_port_config(rtwdev, rtwvअगर, config);

	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल पूर्णांक rtw_ops_conf_tx(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर, u16 ac,
			   स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	rtwvअगर->tx_params[ac] = *params;
	__rtw_conf_tx(rtwdev, rtwvअगर, ac);

	mutex_unlock(&rtwdev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_ops_sta_add(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	पूर्णांक ret = 0;

	mutex_lock(&rtwdev->mutex);
	ret = rtw_sta_add(rtwdev, sta, vअगर);
	mutex_unlock(&rtwdev->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_ops_sta_हटाओ(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	rtw_sta_हटाओ(rtwdev, sta, true);
	mutex_unlock(&rtwdev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_ops_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			   काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
			   काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_sec_desc *sec = &rtwdev->sec;
	u8 hw_key_type;
	u8 hw_key_idx;
	पूर्णांक ret = 0;

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
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		/* suppress error messages */
		वापस -EOPNOTSUPP;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps_deep(rtwdev);

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
		hw_key_idx = rtw_sec_get_मुक्त_cam(sec);
	पूर्ण अन्यथा अणु
		/* multiple पूर्णांकerfaces? */
		hw_key_idx = key->keyidx;
	पूर्ण

	अगर (hw_key_idx > sec->total_cam_num) अणु
		ret = -ENOSPC;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल SET_KEY:
		/* need sw generated IV */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		key->hw_key_idx = hw_key_idx;
		rtw_sec_ग_लिखो_cam(rtwdev, sec, sta, key,
				  hw_key_type, hw_key_idx);
		अवरोध;
	हाल DISABLE_KEY:
		rtw_hci_flush_all_queues(rtwdev, false);
		rtw_mac_flush_all_queues(rtwdev, false);
		rtw_sec_clear_cam(rtwdev, sec, key->hw_key_idx);
		अवरोध;
	पूर्ण

	/* करोwnload new cam settings क्रम PG to backup */
	अगर (rtw_get_lps_deep_mode(rtwdev) == LPS_DEEP_MODE_PG)
		rtw_fw_करोwnload_rsvd_page(rtwdev);

out:
	mutex_unlock(&rtwdev->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_ops_ampdu_action(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ieee80211_sta *sta = params->sta;
	u16 tid = params->tid;
	काष्ठा ieee80211_txq *txq = sta->txq[tid];
	काष्ठा rtw_txq *rtwtxq = (काष्ठा rtw_txq *)txq->drv_priv;

	चयन (params->action) अणु
	हाल IEEE80211_AMPDU_TX_START:
		वापस IEEE80211_AMPDU_TX_START_IMMEDIATE;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		clear_bit(RTW_TXQ_AMPDU, &rtwtxq->flags);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		set_bit(RTW_TXQ_AMPDU, &rtwtxq->flags);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_START:
	हाल IEEE80211_AMPDU_RX_STOP:
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rtw_ops_can_aggregate_in_amsdu(काष्ठा ieee80211_hw *hw,
					   काष्ठा sk_buff *head,
					   काष्ठा sk_buff *skb)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_hal *hal = &rtwdev->hal;

	/* we करोn't want to enable TX AMSDU on 2.4G */
	अगर (hal->current_band_type == RTW_BAND_2G)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम rtw_ops_sw_scan_start(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  स्थिर u8 *mac_addr)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	u32 config = 0;

	mutex_lock(&rtwdev->mutex);

	rtw_leave_lps(rtwdev);

	ether_addr_copy(rtwvअगर->mac_addr, mac_addr);
	config |= PORT_SET_MAC_ADDR;
	rtw_vअगर_port_config(rtwdev, rtwvअगर, config);

	rtw_coex_scan_notअगरy(rtwdev, COEX_SCAN_START);

	set_bit(RTW_FLAG_DIG_DISABLE, rtwdev->flags);
	set_bit(RTW_FLAG_SCANNING, rtwdev->flags);

	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल व्योम rtw_ops_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	u32 config = 0;

	mutex_lock(&rtwdev->mutex);

	clear_bit(RTW_FLAG_SCANNING, rtwdev->flags);
	clear_bit(RTW_FLAG_DIG_DISABLE, rtwdev->flags);

	ether_addr_copy(rtwvअगर->mac_addr, vअगर->addr);
	config |= PORT_SET_MAC_ADDR;
	rtw_vअगर_port_config(rtwdev, rtwvअगर, config);

	rtw_coex_scan_notअगरy(rtwdev, COEX_SCAN_FINISH);

	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल व्योम rtw_ops_mgd_prepare_tx(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   u16 duration)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	rtw_leave_lps_deep(rtwdev);
	rtw_coex_connect_notअगरy(rtwdev, COEX_ASSOCIATE_START);
	rtw_chip_prepare_tx(rtwdev);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

अटल पूर्णांक rtw_ops_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	rtwdev->rts_threshold = value;
	mutex_unlock(&rtwdev->mutex);

	वापस 0;
पूर्ण

अटल व्योम rtw_ops_sta_statistics(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा station_info *sinfo)
अणु
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;

	sinfo->txrate = si->ra_report.txrate;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
पूर्ण

अटल व्योम rtw_ops_flush(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर,
			  u32 queues, bool drop)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	rtw_leave_lps_deep(rtwdev);

	rtw_hci_flush_queues(rtwdev, queues, drop);
	rtw_mac_flush_queues(rtwdev, queues, drop);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

काष्ठा rtw_iter_bitrate_mask_data अणु
	काष्ठा rtw_dev *rtwdev;
	काष्ठा ieee80211_vअगर *vअगर;
	स्थिर काष्ठा cfg80211_bitrate_mask *mask;
पूर्ण;

अटल व्योम rtw_ra_mask_info_update_iter(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtw_iter_bitrate_mask_data *br_data = data;
	काष्ठा rtw_sta_info *si = (काष्ठा rtw_sta_info *)sta->drv_priv;

	अगर (si->vअगर != br_data->vअगर)
		वापस;

	/* मुक्त previous mask setting */
	kमुक्त(si->mask);
	si->mask = kmemdup(br_data->mask, माप(काष्ठा cfg80211_bitrate_mask),
			   GFP_ATOMIC);
	अगर (!si->mask) अणु
		si->use_cfg_mask = false;
		वापस;
	पूर्ण

	si->use_cfg_mask = true;
	rtw_update_sta_info(br_data->rtwdev, si);
पूर्ण

अटल व्योम rtw_ra_mask_info_update(काष्ठा rtw_dev *rtwdev,
				    काष्ठा ieee80211_vअगर *vअगर,
				    स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा rtw_iter_bitrate_mask_data br_data;

	br_data.rtwdev = rtwdev;
	br_data.vअगर = vअगर;
	br_data.mask = mask;
	rtw_iterate_stas_atomic(rtwdev, rtw_ra_mask_info_update_iter, &br_data);
पूर्ण

अटल पूर्णांक rtw_ops_set_bitrate_mask(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	rtw_ra_mask_info_update(rtwdev, vअगर, mask);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_ops_set_antenna(काष्ठा ieee80211_hw *hw,
			       u32 tx_antenna,
			       u32 rx_antenna)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	पूर्णांक ret;

	अगर (!chip->ops->set_antenna)
		वापस -EOPNOTSUPP;

	mutex_lock(&rtwdev->mutex);
	ret = chip->ops->set_antenna(rtwdev, tx_antenna, rx_antenna);
	mutex_unlock(&rtwdev->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक rtw_ops_get_antenna(काष्ठा ieee80211_hw *hw,
			       u32 *tx_antenna,
			       u32 *rx_antenna)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	काष्ठा rtw_hal *hal = &rtwdev->hal;

	*tx_antenna = hal->antenna_tx;
	*rx_antenna = hal->antenna_rx;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rtw_ops_suspend(काष्ठा ieee80211_hw *hw,
			   काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	पूर्णांक ret;

	mutex_lock(&rtwdev->mutex);
	ret = rtw_wow_suspend(rtwdev, wowlan);
	अगर (ret)
		rtw_err(rtwdev, "failed to suspend for wow %d\n", ret);
	mutex_unlock(&rtwdev->mutex);

	वापस ret ? 1 : 0;
पूर्ण

अटल पूर्णांक rtw_ops_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;
	पूर्णांक ret;

	mutex_lock(&rtwdev->mutex);
	ret = rtw_wow_resume(rtwdev);
	अगर (ret)
		rtw_err(rtwdev, "failed to resume for wow %d\n", ret);
	mutex_unlock(&rtwdev->mutex);

	वापस ret ? 1 : 0;
पूर्ण

अटल व्योम rtw_ops_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	device_set_wakeup_enable(rtwdev->dev, enabled);
पूर्ण
#पूर्ण_अगर

अटल व्योम rtw_reconfig_complete(काष्ठा ieee80211_hw *hw,
				  क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	काष्ठा rtw_dev *rtwdev = hw->priv;

	mutex_lock(&rtwdev->mutex);
	अगर (reconfig_type == IEEE80211_RECONFIG_TYPE_RESTART)
		clear_bit(RTW_FLAG_RESTARTING, rtwdev->flags);
	mutex_unlock(&rtwdev->mutex);
पूर्ण

स्थिर काष्ठा ieee80211_ops rtw_ops = अणु
	.tx			= rtw_ops_tx,
	.wake_tx_queue		= rtw_ops_wake_tx_queue,
	.start			= rtw_ops_start,
	.stop			= rtw_ops_stop,
	.config			= rtw_ops_config,
	.add_पूर्णांकerface		= rtw_ops_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= rtw_ops_हटाओ_पूर्णांकerface,
	.change_पूर्णांकerface	= rtw_ops_change_पूर्णांकerface,
	.configure_filter	= rtw_ops_configure_filter,
	.bss_info_changed	= rtw_ops_bss_info_changed,
	.conf_tx		= rtw_ops_conf_tx,
	.sta_add		= rtw_ops_sta_add,
	.sta_हटाओ		= rtw_ops_sta_हटाओ,
	.set_key		= rtw_ops_set_key,
	.ampdu_action		= rtw_ops_ampdu_action,
	.can_aggregate_in_amsdu	= rtw_ops_can_aggregate_in_amsdu,
	.sw_scan_start		= rtw_ops_sw_scan_start,
	.sw_scan_complete	= rtw_ops_sw_scan_complete,
	.mgd_prepare_tx		= rtw_ops_mgd_prepare_tx,
	.set_rts_threshold	= rtw_ops_set_rts_threshold,
	.sta_statistics		= rtw_ops_sta_statistics,
	.flush			= rtw_ops_flush,
	.set_bitrate_mask	= rtw_ops_set_bitrate_mask,
	.set_antenna		= rtw_ops_set_antenna,
	.get_antenna		= rtw_ops_get_antenna,
	.reconfig_complete	= rtw_reconfig_complete,
#अगर_घोषित CONFIG_PM
	.suspend		= rtw_ops_suspend,
	.resume			= rtw_ops_resume,
	.set_wakeup		= rtw_ops_set_wakeup,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(rtw_ops);
