<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation.
 */

#समावेश "main.h"
#समावेश "reg.h"
#समावेश "bf.h"
#समावेश "debug.h"

व्योम rtw_bf_disassoc(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा rtw_bfee *bfee = &rtwvअगर->bfee;
	काष्ठा rtw_bf_info *bfinfo = &rtwdev->bf_info;

	अगर (bfee->role == RTW_BFEE_NONE)
		वापस;

	अगर (bfee->role == RTW_BFEE_MU)
		bfinfo->bfer_mu_cnt--;
	अन्यथा अगर (bfee->role == RTW_BFEE_SU)
		bfinfo->bfer_su_cnt--;

	rtw_chip_config_bfee(rtwdev, rtwvअगर, bfee, false);

	bfee->role = RTW_BFEE_NONE;
पूर्ण

व्योम rtw_bf_assoc(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ieee80211_hw *hw = rtwdev->hw;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा rtw_bfee *bfee = &rtwvअगर->bfee;
	काष्ठा rtw_bf_info *bfinfo = &rtwdev->bf_info;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	काष्ठा ieee80211_sta_vht_cap *ic_vht_cap;
	स्थिर u8 *bssid = bss_conf->bssid;
	u32 sound_dim;
	u8 i;

	अगर (!(chip->band & RTW_BAND_5G))
		वापस;

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta(vअगर, bssid);
	अगर (!sta) अणु
		rtw_warn(rtwdev, "failed to find station entry for bss %pM\n",
			 bssid);
		जाओ out_unlock;
	पूर्ण

	ic_vht_cap = &hw->wiphy->bands[NL80211_BAND_5GHZ]->vht_cap;
	vht_cap = &sta->vht_cap;

	अगर ((ic_vht_cap->cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE) &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)) अणु
		अगर (bfinfo->bfer_mu_cnt >= chip->bfer_mu_max_num) अणु
			rtw_dbg(rtwdev, RTW_DBG_BF, "mu bfer number over limit\n");
			जाओ out_unlock;
		पूर्ण

		ether_addr_copy(bfee->mac_addr, bssid);
		bfee->role = RTW_BFEE_MU;
		bfee->p_aid = (bssid[5] << 1) | (bssid[4] >> 7);
		bfee->aid = bss_conf->aid;
		bfinfo->bfer_mu_cnt++;

		rtw_chip_config_bfee(rtwdev, rtwvअगर, bfee, true);
	पूर्ण अन्यथा अगर ((ic_vht_cap->cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE) &&
		   (vht_cap->cap & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)) अणु
		अगर (bfinfo->bfer_su_cnt >= chip->bfer_su_max_num) अणु
			rtw_dbg(rtwdev, RTW_DBG_BF, "su bfer number over limit\n");
			जाओ out_unlock;
		पूर्ण

		sound_dim = vht_cap->cap &
			    IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;
		sound_dim >>= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;

		ether_addr_copy(bfee->mac_addr, bssid);
		bfee->role = RTW_BFEE_SU;
		bfee->sound_dim = (u8)sound_dim;
		bfee->g_id = 0;
		bfee->p_aid = (bssid[5] << 1) | (bssid[4] >> 7);
		bfinfo->bfer_su_cnt++;
		क्रम (i = 0; i < chip->bfer_su_max_num; i++) अणु
			अगर (!test_bit(i, bfinfo->bfer_su_reg_maping)) अणु
				set_bit(i, bfinfo->bfer_su_reg_maping);
				bfee->su_reg_index = i;
				अवरोध;
			पूर्ण
		पूर्ण

		rtw_chip_config_bfee(rtwdev, rtwvअगर, bfee, true);
	पूर्ण

out_unlock:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम rtw_bf_init_bfer_entry_mu(काष्ठा rtw_dev *rtwdev,
			       काष्ठा mu_bfer_init_para *param)
अणु
	u16 mu_bf_ctl = 0;
	u8 *addr = param->bfer_address;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		rtw_ग_लिखो8(rtwdev, REG_ASSOCIATED_BFMER0_INFO + i, addr[i]);
	rtw_ग_लिखो16(rtwdev, REG_ASSOCIATED_BFMER0_INFO + 6, param->paid);
	rtw_ग_लिखो16(rtwdev, REG_TX_CSI_RPT_PARAM_BW20, param->csi_para);

	mu_bf_ctl = rtw_पढ़ो16(rtwdev, REG_WMAC_MU_BF_CTL) & 0xC000;
	mu_bf_ctl |= param->my_aid | (param->csi_length_sel << 12);
	rtw_ग_लिखो16(rtwdev, REG_WMAC_MU_BF_CTL, mu_bf_ctl);
पूर्ण

व्योम rtw_bf_cfg_sounding(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			 क्रमागत rtw_trx_desc_rate rate)
अणु
	u32 psf_ctl = 0;
	u8 csi_rsc = 0x1;

	psf_ctl = rtw_पढ़ो32(rtwdev, REG_BBPSF_CTRL) |
		  BIT_WMAC_USE_NDPARATE |
		  (csi_rsc << 13);

	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL, RTW_SND_CTRL_SOUNDING);
	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL + 3, 0x26);
	rtw_ग_लिखो8_clr(rtwdev, REG_RXFLTMAP1, BIT_RXFLTMAP1_BF_REPORT_POLL);
	rtw_ग_लिखो8_clr(rtwdev, REG_RXFLTMAP4, BIT_RXFLTMAP4_BF_REPORT_POLL);

	अगर (vअगर->net_type == RTW_NET_AP_MODE)
		rtw_ग_लिखो32(rtwdev, REG_BBPSF_CTRL, psf_ctl | BIT(12));
	अन्यथा
		rtw_ग_लिखो32(rtwdev, REG_BBPSF_CTRL, psf_ctl & ~BIT(12));
पूर्ण

व्योम rtw_bf_cfg_mu_bfee(काष्ठा rtw_dev *rtwdev, काष्ठा cfg_mumimo_para *param)
अणु
	u8 mu_tbl_sel;
	u8 mu_valid;

	mu_valid = rtw_पढ़ो8(rtwdev, REG_MU_TX_CTL) &
		   ~BIT_MASK_R_MU_TABLE_VALID;

	rtw_ग_लिखो8(rtwdev, REG_MU_TX_CTL,
		   (mu_valid | BIT(0) | BIT(1)) & ~(BIT(7)));

	mu_tbl_sel = rtw_पढ़ो8(rtwdev, REG_MU_TX_CTL + 1) & 0xF8;

	rtw_ग_लिखो8(rtwdev, REG_MU_TX_CTL + 1, mu_tbl_sel);
	rtw_ग_लिखो32(rtwdev, REG_MU_STA_GID_VLD, param->given_gid_tab[0]);
	rtw_ग_लिखो32(rtwdev, REG_MU_STA_USER_POS_INFO, param->given_user_pos[0]);
	rtw_ग_लिखो32(rtwdev, REG_MU_STA_USER_POS_INFO + 4,
		    param->given_user_pos[1]);

	rtw_ग_लिखो8(rtwdev, REG_MU_TX_CTL + 1, mu_tbl_sel | 1);
	rtw_ग_लिखो32(rtwdev, REG_MU_STA_GID_VLD, param->given_gid_tab[1]);
	rtw_ग_लिखो32(rtwdev, REG_MU_STA_USER_POS_INFO, param->given_user_pos[2]);
	rtw_ग_लिखो32(rtwdev, REG_MU_STA_USER_POS_INFO + 4,
		    param->given_user_pos[3]);
पूर्ण

व्योम rtw_bf_del_bfer_entry_mu(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32(rtwdev, REG_ASSOCIATED_BFMER0_INFO, 0);
	rtw_ग_लिखो32(rtwdev, REG_ASSOCIATED_BFMER0_INFO + 4, 0);
	rtw_ग_लिखो16(rtwdev, REG_WMAC_MU_BF_CTL, 0);
	rtw_ग_लिखो8(rtwdev, REG_MU_TX_CTL, 0);
पूर्ण

व्योम rtw_bf_del_sounding(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL, 0);
पूर्ण

व्योम rtw_bf_enable_bfee_su(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			   काष्ठा rtw_bfee *bfee)
अणु
	u8 nc_index = hweight8(rtwdev->hal.antenna_rx) - 1;
	u8 nr_index = bfee->sound_dim;
	u8 grouping = 0, codebookinfo = 1, coefficientsize = 3;
	u32 addr_bfer_info, addr_csi_rpt, csi_param;
	u8 i;

	rtw_dbg(rtwdev, RTW_DBG_BF, "config as an su bfee\n");

	चयन (bfee->su_reg_index) अणु
	हाल 1:
		addr_bfer_info = REG_ASSOCIATED_BFMER1_INFO;
		addr_csi_rpt = REG_TX_CSI_RPT_PARAM_BW20 + 2;
		अवरोध;
	हाल 0:
	शेष:
		addr_bfer_info = REG_ASSOCIATED_BFMER0_INFO;
		addr_csi_rpt = REG_TX_CSI_RPT_PARAM_BW20;
		अवरोध;
	पूर्ण

	/* Sounding protocol control */
	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL, RTW_SND_CTRL_SOUNDING);

	/* MAC address/Partial AID of Beamक्रमmer */
	क्रम (i = 0; i < ETH_ALEN; i++)
		rtw_ग_लिखो8(rtwdev, addr_bfer_info + i, bfee->mac_addr[i]);

	csi_param = (u16)((coefficientsize << 10) |
			  (codebookinfo << 8) |
			  (grouping << 6) |
			  (nr_index << 3) |
			  nc_index);
	rtw_ग_लिखो16(rtwdev, addr_csi_rpt, csi_param);

	/* ndp rx standby समयr */
	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL + 3, RTW_NDP_RX_STANDBY_TIME);
पूर्ण
EXPORT_SYMBOL(rtw_bf_enable_bfee_su);

/* nc index: 1 2T2R 0 1T1R
 * nr index: 1 use Nsts 0 use reg setting
 * codebookinfo: 1 802.11ac 3 802.11n
 */
व्योम rtw_bf_enable_bfee_mu(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			   काष्ठा rtw_bfee *bfee)
अणु
	काष्ठा rtw_bf_info *bf_info = &rtwdev->bf_info;
	काष्ठा mu_bfer_init_para param;
	u8 nc_index = hweight8(rtwdev->hal.antenna_rx) - 1;
	u8 nr_index = 1;
	u8 grouping = 0, codebookinfo = 1, coefficientsize = 0;
	u32 csi_param;

	rtw_dbg(rtwdev, RTW_DBG_BF, "config as an mu bfee\n");

	csi_param = (u16)((coefficientsize << 10) |
			  (codebookinfo << 8) |
			  (grouping << 6) |
			  (nr_index << 3) |
			  nc_index);

	rtw_dbg(rtwdev, RTW_DBG_BF, "nc=%d nr=%d group=%d codebookinfo=%d coefficientsize=%d\n",
		nc_index, nr_index, grouping, codebookinfo,
		coefficientsize);

	param.paid = bfee->p_aid;
	param.csi_para = csi_param;
	param.my_aid = bfee->aid & 0xfff;
	param.csi_length_sel = HAL_CSI_SEG_4K;
	ether_addr_copy(param.bfer_address, bfee->mac_addr);

	rtw_bf_init_bfer_entry_mu(rtwdev, &param);

	bf_info->cur_csi_rpt_rate = DESC_RATE6M;
	rtw_bf_cfg_sounding(rtwdev, vअगर, DESC_RATE6M);

	/* accept action_no_ack */
	rtw_ग_लिखो16_set(rtwdev, REG_RXFLTMAP0, BIT_RXFLTMAP0_ACTIONNOACK);

	/* accept NDPA and BF report poll */
	rtw_ग_लिखो16_set(rtwdev, REG_RXFLTMAP1, BIT_RXFLTMAP1_BF);
पूर्ण
EXPORT_SYMBOL(rtw_bf_enable_bfee_mu);

व्योम rtw_bf_हटाओ_bfee_su(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_bfee *bfee)
अणु
	काष्ठा rtw_bf_info *bfinfo = &rtwdev->bf_info;

	rtw_dbg(rtwdev, RTW_DBG_BF, "remove as a su bfee\n");
	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL, RTW_SND_CTRL_REMOVE);

	चयन (bfee->su_reg_index) अणु
	हाल 0:
		rtw_ग_लिखो32(rtwdev, REG_ASSOCIATED_BFMER0_INFO, 0);
		rtw_ग_लिखो16(rtwdev, REG_ASSOCIATED_BFMER0_INFO + 4, 0);
		rtw_ग_लिखो16(rtwdev, REG_TX_CSI_RPT_PARAM_BW20, 0);
		अवरोध;
	हाल 1:
		rtw_ग_लिखो32(rtwdev, REG_ASSOCIATED_BFMER1_INFO, 0);
		rtw_ग_लिखो16(rtwdev, REG_ASSOCIATED_BFMER1_INFO + 4, 0);
		rtw_ग_लिखो16(rtwdev, REG_TX_CSI_RPT_PARAM_BW20 + 2, 0);
		अवरोध;
	पूर्ण

	clear_bit(bfee->su_reg_index, bfinfo->bfer_su_reg_maping);
	bfee->su_reg_index = 0xFF;
पूर्ण
EXPORT_SYMBOL(rtw_bf_हटाओ_bfee_su);

व्योम rtw_bf_हटाओ_bfee_mu(काष्ठा rtw_dev *rtwdev,
			   काष्ठा rtw_bfee *bfee)
अणु
	काष्ठा rtw_bf_info *bfinfo = &rtwdev->bf_info;

	rtw_ग_लिखो8(rtwdev, REG_SND_PTCL_CTRL, RTW_SND_CTRL_REMOVE);

	rtw_bf_del_bfer_entry_mu(rtwdev);

	अगर (bfinfo->bfer_su_cnt == 0 && bfinfo->bfer_mu_cnt == 0)
		rtw_bf_del_sounding(rtwdev);
पूर्ण
EXPORT_SYMBOL(rtw_bf_हटाओ_bfee_mu);

व्योम rtw_bf_set_gid_table(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_bss_conf *conf)
अणु
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)vअगर->drv_priv;
	काष्ठा rtw_bfee *bfee = &rtwvअगर->bfee;
	काष्ठा cfg_mumimo_para param;

	अगर (bfee->role != RTW_BFEE_MU) अणु
		rtw_dbg(rtwdev, RTW_DBG_BF, "this vif is not mu bfee\n");
		वापस;
	पूर्ण

	param.grouping_biपंचांगap = 0;
	param.mu_tx_en = 0;
	स_रखो(param.sounding_sts, 0, 6);
	स_नकल(param.given_gid_tab, conf->mu_group.membership, 8);
	स_नकल(param.given_user_pos, conf->mu_group.position, 16);
	rtw_dbg(rtwdev, RTW_DBG_BF, "STA0: gid_valid=0x%x, user_position_l=0x%x, user_position_h=0x%x\n",
		param.given_gid_tab[0], param.given_user_pos[0],
		param.given_user_pos[1]);

	rtw_dbg(rtwdev, RTW_DBG_BF, "STA1: gid_valid=0x%x, user_position_l=0x%x, user_position_h=0x%x\n",
		param.given_gid_tab[1], param.given_user_pos[2],
		param.given_user_pos[3]);

	rtw_bf_cfg_mu_bfee(rtwdev, &param);
पूर्ण
EXPORT_SYMBOL(rtw_bf_set_gid_table);

व्योम rtw_bf_phy_init(काष्ठा rtw_dev *rtwdev)
अणु
	u8 पंचांगp8;
	u32 पंचांगp32;
	u8 retry_limit = 0xA;
	u8 ndpa_rate = 0x10;
	u8 ack_policy = 3;

	पंचांगp32 = rtw_पढ़ो32(rtwdev, REG_MU_TX_CTL);
	/* Enable P1 aggr new packet according to P0 transfer समय */
	पंचांगp32 |= BIT_MU_P1_WAIT_STATE_EN;
	/* MU Retry Limit */
	पंचांगp32 &= ~BIT_MASK_R_MU_RL;
	पंचांगp32 |= (retry_limit << BIT_SHIFT_R_MU_RL) & BIT_MASK_R_MU_RL;
	/* Disable Tx MU-MIMO until sounding करोne */
	पंचांगp32 &= ~BIT_EN_MU_MIMO;
	/* Clear validity of MU STAs */
	पंचांगp32 &= ~BIT_MASK_R_MU_TABLE_VALID;
	rtw_ग_लिखो32(rtwdev, REG_MU_TX_CTL, पंचांगp32);

	/* MU-MIMO Option as शेष value */
	पंचांगp8 = ack_policy << BIT_SHIFT_WMAC_TXMU_ACKPOLICY;
	पंचांगp8 |= BIT_WMAC_TXMU_ACKPOLICY_EN;
	rtw_ग_लिखो8(rtwdev, REG_WMAC_MU_BF_OPTION, पंचांगp8);

	/* MU-MIMO Control as शेष value */
	rtw_ग_लिखो16(rtwdev, REG_WMAC_MU_BF_CTL, 0);
	/* Set MU NDPA rate & BW source */
	rtw_ग_लिखो32_set(rtwdev, REG_TXBF_CTRL, BIT_USE_NDPA_PARAMETER);
	/* Set NDPA Rate */
	rtw_ग_लिखो8(rtwdev, REG_NDPA_OPT_CTRL, ndpa_rate);

	rtw_ग_लिखो32_mask(rtwdev, REG_BBPSF_CTRL, BIT_MASK_CSI_RATE,
			 DESC_RATE6M);
पूर्ण
EXPORT_SYMBOL(rtw_bf_phy_init);

व्योम rtw_bf_cfg_csi_rate(काष्ठा rtw_dev *rtwdev, u8 rssi, u8 cur_rate,
			 u8 fixrate_en, u8 *new_rate)
अणु
	u32 csi_cfg;
	u16 cur_rrsr;

	csi_cfg = rtw_पढ़ो32(rtwdev, REG_BBPSF_CTRL) & ~BIT_MASK_CSI_RATE;
	cur_rrsr = rtw_पढ़ो16(rtwdev, REG_RRSR);

	अगर (rssi >= 40) अणु
		अगर (cur_rate != DESC_RATE54M) अणु
			cur_rrsr |= BIT(DESC_RATE54M);
			csi_cfg |= (DESC_RATE54M & BIT_MASK_CSI_RATE_VAL) <<
				   BIT_SHIFT_CSI_RATE;
			rtw_ग_लिखो16(rtwdev, REG_RRSR, cur_rrsr);
			rtw_ग_लिखो32(rtwdev, REG_BBPSF_CTRL, csi_cfg);
		पूर्ण
		*new_rate = DESC_RATE54M;
	पूर्ण अन्यथा अणु
		अगर (cur_rate != DESC_RATE24M) अणु
			cur_rrsr &= ~BIT(DESC_RATE54M);
			csi_cfg |= (DESC_RATE54M & BIT_MASK_CSI_RATE_VAL) <<
				   BIT_SHIFT_CSI_RATE;
			rtw_ग_लिखो16(rtwdev, REG_RRSR, cur_rrsr);
			rtw_ग_लिखो32(rtwdev, REG_BBPSF_CTRL, csi_cfg);
		पूर्ण
		*new_rate = DESC_RATE24M;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_bf_cfg_csi_rate);
