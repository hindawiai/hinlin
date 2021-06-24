<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation.
 */

#अगर_अघोषित __RTW_BF_H_
#घोषणा __RTW_BF_H_

#घोषणा REG_TXBF_CTRL		0x042C
#घोषणा REG_RRSR		0x0440
#घोषणा REG_NDPA_OPT_CTRL	0x045F

#घोषणा REG_ASSOCIATED_BFMER0_INFO	0x06E4
#घोषणा REG_ASSOCIATED_BFMER1_INFO	0x06EC
#घोषणा REG_TX_CSI_RPT_PARAM_BW20	0x06F4
#घोषणा REG_SND_PTCL_CTRL		0x0718
#घोषणा REG_MU_TX_CTL			0x14C0
#घोषणा REG_MU_STA_GID_VLD		0x14C4
#घोषणा REG_MU_STA_USER_POS_INFO	0x14C8
#घोषणा REG_CSI_RRSR			0x1678
#घोषणा REG_WMAC_MU_BF_OPTION		0x167C
#घोषणा REG_WMAC_MU_BF_CTL		0x1680

#घोषणा BIT_WMAC_USE_NDPARATE			BIT(30)
#घोषणा BIT_WMAC_TXMU_ACKPOLICY_EN		BIT(6)
#घोषणा BIT_USE_NDPA_PARAMETER			BIT(30)
#घोषणा BIT_MU_P1_WAIT_STATE_EN			BIT(16)
#घोषणा BIT_EN_MU_MIMO				BIT(7)

#घोषणा R_MU_RL				0xf
#घोषणा BIT_SHIFT_R_MU_RL		12
#घोषणा BIT_SHIFT_WMAC_TXMU_ACKPOLICY	4
#घोषणा BIT_SHIFT_CSI_RATE		24

#घोषणा BIT_MASK_R_MU_RL (R_MU_RL << BIT_SHIFT_R_MU_RL)
#घोषणा BIT_MASK_R_MU_TABLE_VALID	0x3f
#घोषणा BIT_MASK_CSI_RATE_VAL		0x3F
#घोषणा BIT_MASK_CSI_RATE (BIT_MASK_CSI_RATE_VAL << BIT_SHIFT_CSI_RATE)

#घोषणा BIT_RXFLTMAP0_ACTIONNOACK	BIT(14)
#घोषणा BIT_RXFLTMAP1_BF		(BIT(4) | BIT(5))
#घोषणा BIT_RXFLTMAP1_BF_REPORT_POLL	BIT(4)
#घोषणा BIT_RXFLTMAP4_BF_REPORT_POLL	BIT(4)

#घोषणा RTW_NDP_RX_STANDBY_TIME	0x70
#घोषणा RTW_SND_CTRL_REMOVE	0xD8
#घोषणा RTW_SND_CTRL_SOUNDING	0xDB

क्रमागत csi_seg_len अणु
	HAL_CSI_SEG_4K = 0,
	HAL_CSI_SEG_8K = 1,
	HAL_CSI_SEG_11K = 2,
पूर्ण;

काष्ठा cfg_mumimo_para अणु
	u8 sounding_sts[6];
	u16 grouping_biपंचांगap;
	u8 mu_tx_en;
	u32 given_gid_tab[2];
	u32 given_user_pos[4];
पूर्ण;

काष्ठा mu_bfer_init_para अणु
	u16 paid;
	u16 csi_para;
	u16 my_aid;
	क्रमागत csi_seg_len csi_length_sel;
	u8 bfer_address[ETH_ALEN];
पूर्ण;

व्योम rtw_bf_disassoc(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_bss_conf *bss_conf);
व्योम rtw_bf_assoc(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_bss_conf *bss_conf);
व्योम rtw_bf_init_bfer_entry_mu(काष्ठा rtw_dev *rtwdev,
			       काष्ठा mu_bfer_init_para *param);
व्योम rtw_bf_cfg_sounding(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			 क्रमागत rtw_trx_desc_rate rate);
व्योम rtw_bf_cfg_mu_bfee(काष्ठा rtw_dev *rtwdev, काष्ठा cfg_mumimo_para *param);
व्योम rtw_bf_del_bfer_entry_mu(काष्ठा rtw_dev *rtwdev);
व्योम rtw_bf_del_sounding(काष्ठा rtw_dev *rtwdev);
व्योम rtw_bf_enable_bfee_su(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			   काष्ठा rtw_bfee *bfee);
व्योम rtw_bf_enable_bfee_mu(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
			   काष्ठा rtw_bfee *bfee);
व्योम rtw_bf_हटाओ_bfee_su(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_bfee *bfee);
व्योम rtw_bf_हटाओ_bfee_mu(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_bfee *bfee);
व्योम rtw_bf_set_gid_table(काष्ठा rtw_dev *rtwdev, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_bss_conf *conf);
व्योम rtw_bf_phy_init(काष्ठा rtw_dev *rtwdev);
व्योम rtw_bf_cfg_csi_rate(काष्ठा rtw_dev *rtwdev, u8 rssi, u8 cur_rate,
			 u8 fixrate_en, u8 *new_rate);
अटल अंतरभूत व्योम rtw_chip_config_bfee(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
					काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (rtwdev->chip->ops->config_bfee)
		rtwdev->chip->ops->config_bfee(rtwdev, vअगर, bfee, enable);
पूर्ण

अटल अंतरभूत व्योम rtw_chip_set_gid_table(काष्ठा rtw_dev *rtwdev,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा ieee80211_bss_conf *conf)
अणु
	अगर (rtwdev->chip->ops->set_gid_table)
		rtwdev->chip->ops->set_gid_table(rtwdev, vअगर, conf);
पूर्ण

अटल अंतरभूत व्योम rtw_chip_cfg_csi_rate(काष्ठा rtw_dev *rtwdev, u8 rssi, u8 cur_rate,
					 u8 fixrate_en, u8 *new_rate)
अणु
	अगर (rtwdev->chip->ops->cfg_csi_rate)
		rtwdev->chip->ops->cfg_csi_rate(rtwdev, rssi, cur_rate,
						fixrate_en, new_rate);
पूर्ण
#पूर्ण_अगर
