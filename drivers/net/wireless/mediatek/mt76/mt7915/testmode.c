<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc. */

#समावेश "mt7915.h"
#समावेश "mac.h"
#समावेश "mcu.h"
#समावेश "testmode.h"

क्रमागत अणु
	TM_CHANGED_TXPOWER,
	TM_CHANGED_FREQ_OFFSET,

	/* must be last */
	NUM_TM_CHANGED
पूर्ण;

अटल स्थिर u8 पंचांग_change_map[] = अणु
	[TM_CHANGED_TXPOWER] = MT76_TM_ATTR_TX_POWER,
	[TM_CHANGED_FREQ_OFFSET] = MT76_TM_ATTR_FREQ_OFFSET,
पूर्ण;

काष्ठा reg_band अणु
	u32 band[2];
पूर्ण;

#घोषणा REG_BAND(_reg) \
	अणु .band[0] = MT_##_reg(0), .band[1] = MT_##_reg(1) पूर्ण
#घोषणा REG_BAND_IDX(_reg, _idx) \
	अणु .band[0] = MT_##_reg(0, _idx), .band[1] = MT_##_reg(1, _idx) पूर्ण

अटल स्थिर काष्ठा reg_band reg_backup_list[] = अणु
	REG_BAND_IDX(AGG_PCR0, 0),
	REG_BAND_IDX(AGG_PCR0, 1),
	REG_BAND_IDX(AGG_AWSCR0, 0),
	REG_BAND_IDX(AGG_AWSCR0, 1),
	REG_BAND_IDX(AGG_AWSCR0, 2),
	REG_BAND_IDX(AGG_AWSCR0, 3),
	REG_BAND(AGG_MRCR),
	REG_BAND(TMAC_TFCR0),
	REG_BAND(TMAC_TCR0),
	REG_BAND(AGG_ATCR1),
	REG_BAND(AGG_ATCR3),
	REG_BAND(TMAC_TRCR0),
	REG_BAND(TMAC_ICR0),
	REG_BAND_IDX(ARB_DRNGR0, 0),
	REG_BAND_IDX(ARB_DRNGR0, 1),
	REG_BAND(WF_RFCR),
	REG_BAND(WF_RFCR1),
पूर्ण;

अटल पूर्णांक
mt7915_पंचांग_set_tx_घातer(काष्ठा mt7915_phy *phy)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा cfg80211_chan_def *chandef = &mphy->chandef;
	पूर्णांक freq = chandef->center_freq1;
	पूर्णांक ret;
	काष्ठा अणु
		u8 क्रमmat_id;
		u8 dbdc_idx;
		s8 tx_घातer;
		u8 ant_idx;	/* Only 0 is valid */
		u8 center_chan;
		u8 rsv[3];
	पूर्ण __packed req = अणु
		.क्रमmat_id = 0xf,
		.dbdc_idx = phy != &dev->phy,
		.center_chan = ieee80211_frequency_to_channel(freq),
	पूर्ण;
	u8 *tx_घातer = शून्य;

	अगर (phy->mt76->test.state != MT76_TM_STATE_OFF)
		tx_घातer = phy->mt76->test.tx_घातer;

	/* Tx घातer of the other antennas are the same as antenna 0 */
	अगर (tx_घातer && tx_घातer[0])
		req.tx_घातer = tx_घातer[0];

	ret = mt76_mcu_send_msg(&dev->mt76,
				MCU_EXT_CMD(TX_POWER_FEATURE_CTRL),
				&req, माप(req), false);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_freq_offset(काष्ठा mt7915_phy *phy, bool en, u32 val)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_पंचांग_cmd req = अणु
		.tesपंचांगode_en = en,
		.param_idx = MCU_ATE_SET_FREQ_OFFSET,
		.param.freq.band = phy != &dev->phy,
		.param.freq.freq_offset = cpu_to_le32(val),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTRL), &req,
				 माप(req), false);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_mode_ctrl(काष्ठा mt7915_dev *dev, bool enable)
अणु
	काष्ठा अणु
		u8 क्रमmat_id;
		bool enable;
		u8 rsv[2];
	पूर्ण __packed req = अणु
		.क्रमmat_id = 0x6,
		.enable = enable,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76,
				 MCU_EXT_CMD(TX_POWER_FEATURE_CTRL),
				 &req, माप(req), false);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_trx(काष्ठा mt7915_phy *phy, पूर्णांक type, bool en)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_पंचांग_cmd req = अणु
		.tesपंचांगode_en = 1,
		.param_idx = MCU_ATE_SET_TRX,
		.param.trx.type = type,
		.param.trx.enable = en,
		.param.trx.band = phy != &dev->phy,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTRL), &req,
				 माप(req), false);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_clean_hwq(काष्ठा mt7915_phy *phy, u8 wcid)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_पंचांग_cmd req = अणु
		.tesपंचांगode_en = 1,
		.param_idx = MCU_ATE_CLEAN_TXQUEUE,
		.param.clean.wcid = wcid,
		.param.clean.band = phy != &dev->phy,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTRL), &req,
				 माप(req), false);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_slot_समय(काष्ठा mt7915_phy *phy, u8 slot_समय, u8 sअगरs)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा mt7915_पंचांग_cmd req = अणु
		.tesपंचांगode_en = !(phy->mt76->test.state == MT76_TM_STATE_OFF),
		.param_idx = MCU_ATE_SET_SLOT_TIME,
		.param.slot.slot_समय = slot_समय,
		.param.slot.sअगरs = sअगरs,
		.param.slot.rअगरs = 2,
		.param.slot.eअगरs = cpu_to_le16(60),
		.param.slot.band = phy != &dev->phy,
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(ATE_CTRL), &req,
				 माप(req), false);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_wmm_qid(काष्ठा mt7915_dev *dev, u8 qid, u8 aअगरs, u8 cw_min,
		      u16 cw_max, u16 txop)
अणु
	काष्ठा mt7915_mcu_tx req = अणु .total = 1 पूर्ण;
	काष्ठा edca *e = &req.edca[0];

	e->queue = qid;
	e->set = WMM_PARAM_SET;

	e->aअगरs = aअगरs;
	e->cw_min = cw_min;
	e->cw_max = cpu_to_le16(cw_max);
	e->txop = cpu_to_le16(txop);

	वापस mt7915_mcu_update_edca(dev, &req);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_ipg_params(काष्ठा mt7915_phy *phy, u32 ipg, u8 mode)
अणु
#घोषणा TM_DEFAULT_SIFS	10
#घोषणा TM_MAX_SIFS	127
#घोषणा TM_MAX_AIFSN	0xf
#घोषणा TM_MIN_AIFSN	0x1
#घोषणा BBP_PROC_TIME	1500
	काष्ठा mt7915_dev *dev = phy->dev;
	u8 sig_ext = (mode == MT76_TM_TX_MODE_CCK) ? 0 : 6;
	u8 slot_समय = 9, sअगरs = TM_DEFAULT_SIFS;
	u8 aअगरsn = TM_MIN_AIFSN;
	u32 i2t_समय, tr2t_समय, txv_समय;
	bool ext_phy = phy != &dev->phy;
	u16 cw = 0;

	अगर (ipg < sig_ext + slot_समय + sअगरs)
		ipg = 0;

	अगर (!ipg)
		जाओ करोne;

	ipg -= sig_ext;

	अगर (ipg <= (TM_MAX_SIFS + slot_समय)) अणु
		sअगरs = ipg - slot_समय;
	पूर्ण अन्यथा अणु
		u32 val = (ipg + slot_समय) / slot_समय;

		जबतक (val >>= 1)
			cw++;

		अगर (cw > 16)
			cw = 16;

		ipg -= ((1 << cw) - 1) * slot_समय;

		aअगरsn = ipg / slot_समय;
		अगर (aअगरsn > TM_MAX_AIFSN)
			aअगरsn = TM_MAX_AIFSN;

		ipg -= aअगरsn * slot_समय;

		अगर (ipg > TM_DEFAULT_SIFS) अणु
			अगर (ipg < TM_MAX_SIFS)
				sअगरs = ipg;
			अन्यथा
				sअगरs = TM_MAX_SIFS;
		पूर्ण
	पूर्ण
करोne:
	txv_समय = mt76_get_field(dev, MT_TMAC_ATCR(ext_phy),
				  MT_TMAC_ATCR_TXV_TOUT);
	txv_समय *= 50;	/* normal घड़ी समय */

	i2t_समय = (slot_समय * 1000 - txv_समय - BBP_PROC_TIME) / 50;
	tr2t_समय = (sअगरs * 1000 - txv_समय - BBP_PROC_TIME) / 50;

	mt76_set(dev, MT_TMAC_TRCR0(ext_phy),
		 FIELD_PREP(MT_TMAC_TRCR0_TR2T_CHK, tr2t_समय) |
		 FIELD_PREP(MT_TMAC_TRCR0_I2T_CHK, i2t_समय));

	mt7915_पंचांग_set_slot_समय(phy, slot_समय, sअगरs);

	वापस mt7915_पंचांग_set_wmm_qid(dev,
				     mt7915_lmac_mapping(dev, IEEE80211_AC_BE),
				     aअगरsn, cw, cw, 0);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_tx_len(काष्ठा mt7915_phy *phy, u32 tx_समय)
अणु
	काष्ठा mt76_phy *mphy = phy->mt76;
	काष्ठा mt76_tesपंचांगode_data *td = &mphy->test;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा rate_info rate = अणुपूर्ण;
	u16 flags = 0, tx_len;
	u32 bitrate;
	पूर्णांक ret;

	अगर (!tx_समय)
		वापस 0;

	rate.mcs = td->tx_rate_idx;
	rate.nss = td->tx_rate_nss;

	चयन (td->tx_rate_mode) अणु
	हाल MT76_TM_TX_MODE_CCK:
	हाल MT76_TM_TX_MODE_OFDM:
		अगर (mphy->chandef.chan->band == NL80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		अन्यथा
			sband = &mphy->sband_2g.sband;

		rate.legacy = sband->bitrates[rate.mcs].bitrate;
		अवरोध;
	हाल MT76_TM_TX_MODE_HT:
		rate.mcs += rate.nss * 8;
		flags |= RATE_INFO_FLAGS_MCS;

		अगर (td->tx_rate_sgi)
			flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT76_TM_TX_MODE_VHT:
		flags |= RATE_INFO_FLAGS_VHT_MCS;

		अगर (td->tx_rate_sgi)
			flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_SU:
	हाल MT76_TM_TX_MODE_HE_EXT_SU:
	हाल MT76_TM_TX_MODE_HE_TB:
	हाल MT76_TM_TX_MODE_HE_MU:
		rate.he_gi = td->tx_rate_sgi;
		flags |= RATE_INFO_FLAGS_HE_MCS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rate.flags = flags;

	चयन (mphy->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_160:
	हाल NL80211_CHAN_WIDTH_80P80:
		rate.bw = RATE_INFO_BW_160;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		rate.bw = RATE_INFO_BW_80;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		rate.bw = RATE_INFO_BW_40;
		अवरोध;
	शेष:
		rate.bw = RATE_INFO_BW_20;
		अवरोध;
	पूर्ण

	bitrate = cfg80211_calculate_bitrate(&rate);
	tx_len = bitrate * tx_समय / 10 / 8;

	ret = mt76_tesपंचांगode_alloc_skb(phy->mt76, tx_len);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
mt7915_पंचांग_reg_backup_restore(काष्ठा mt7915_phy *phy)
अणु
	पूर्णांक n_regs = ARRAY_SIZE(reg_backup_list);
	काष्ठा mt7915_dev *dev = phy->dev;
	bool ext_phy = phy != &dev->phy;
	u32 *b = phy->test.reg_backup;
	पूर्णांक i;

	अगर (phy->mt76->test.state == MT76_TM_STATE_OFF) अणु
		क्रम (i = 0; i < n_regs; i++)
			mt76_wr(dev, reg_backup_list[i].band[ext_phy], b[i]);
		वापस;
	पूर्ण

	अगर (b)
		वापस;

	b = devm_kzalloc(dev->mt76.dev, 4 * n_regs, GFP_KERNEL);
	अगर (!b)
		वापस;

	phy->test.reg_backup = b;
	क्रम (i = 0; i < n_regs; i++)
		b[i] = mt76_rr(dev, reg_backup_list[i].band[ext_phy]);

	mt76_clear(dev, MT_AGG_PCR0(ext_phy, 0), MT_AGG_PCR0_MM_PROT |
		   MT_AGG_PCR0_GF_PROT | MT_AGG_PCR0_ERP_PROT |
		   MT_AGG_PCR0_VHT_PROT | MT_AGG_PCR0_BW20_PROT |
		   MT_AGG_PCR0_BW40_PROT | MT_AGG_PCR0_BW80_PROT);
	mt76_set(dev, MT_AGG_PCR0(ext_phy, 0), MT_AGG_PCR0_PTA_WIN_DIS);

	mt76_wr(dev, MT_AGG_PCR0(ext_phy, 1), MT_AGG_PCR1_RTS0_NUM_THRES |
		MT_AGG_PCR1_RTS0_LEN_THRES);

	mt76_clear(dev, MT_AGG_MRCR(ext_phy), MT_AGG_MRCR_BAR_CNT_LIMIT |
		   MT_AGG_MRCR_LAST_RTS_CTS_RN | MT_AGG_MRCR_RTS_FAIL_LIMIT |
		   MT_AGG_MRCR_TXCMD_RTS_FAIL_LIMIT);

	mt76_rmw(dev, MT_AGG_MRCR(ext_phy), MT_AGG_MRCR_RTS_FAIL_LIMIT |
		 MT_AGG_MRCR_TXCMD_RTS_FAIL_LIMIT,
		 FIELD_PREP(MT_AGG_MRCR_RTS_FAIL_LIMIT, 1) |
		 FIELD_PREP(MT_AGG_MRCR_TXCMD_RTS_FAIL_LIMIT, 1));

	mt76_wr(dev, MT_TMAC_TFCR0(ext_phy), 0);
	mt76_clear(dev, MT_TMAC_TCR0(ext_phy), MT_TMAC_TCR0_TBTT_STOP_CTRL);

	/* config rx filter क्रम tesपंचांगode rx */
	mt76_wr(dev, MT_WF_RFCR(ext_phy), 0xcf70a);
	mt76_wr(dev, MT_WF_RFCR1(ext_phy), 0);
पूर्ण

अटल व्योम
mt7915_पंचांग_init(काष्ठा mt7915_phy *phy, bool en)
अणु
	काष्ठा mt7915_dev *dev = phy->dev;

	अगर (!test_bit(MT76_STATE_RUNNING, &phy->mt76->state))
		वापस;

	mt7915_mcu_set_sku_en(phy, !en);

	mt7915_पंचांग_mode_ctrl(dev, en);
	mt7915_पंचांग_reg_backup_restore(phy);
	mt7915_पंचांग_set_trx(phy, TM_MAC_TXRX, !en);

	mt7915_mcu_add_bss_info(phy, phy->monitor_vअगर, en);
पूर्ण

अटल व्योम
mt7915_पंचांग_update_channel(काष्ठा mt7915_phy *phy)
अणु
	mutex_unlock(&phy->dev->mt76.mutex);
	mt7915_set_channel(phy);
	mutex_lock(&phy->dev->mt76.mutex);

	mt7915_mcu_set_chan_info(phy, MCU_EXT_CMD(SET_RX_PATH));
पूर्ण

अटल व्योम
mt7915_पंचांग_set_tx_frames(काष्ठा mt7915_phy *phy, bool en)
अणु
	अटल स्थिर u8 spe_idx_map[] = अणु0, 0, 1, 0, 3, 2, 4, 0,
					 9, 8, 6, 10, 16, 12, 18, 0पूर्ण;
	काष्ठा mt76_tesपंचांगode_data *td = &phy->mt76->test;
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा ieee80211_tx_info *info;
	u8 duty_cycle = td->tx_duty_cycle;
	u32 tx_समय = td->tx_समय;
	u32 ipg = td->tx_ipg;

	mt7915_पंचांग_set_trx(phy, TM_MAC_RX_RXV, false);
	mt7915_पंचांग_clean_hwq(phy, dev->mt76.global_wcid.idx);

	अगर (en) अणु
		mt7915_पंचांग_update_channel(phy);

		अगर (td->tx_spe_idx) अणु
			phy->test.spe_idx = td->tx_spe_idx;
		पूर्ण अन्यथा अणु
			u8 tx_ant = td->tx_antenna_mask;

			अगर (phy != &dev->phy)
				tx_ant >>= 2;
			phy->test.spe_idx = spe_idx_map[tx_ant];
		पूर्ण
	पूर्ण

	/* अगर all three params are set, duty_cycle will be ignored */
	अगर (duty_cycle && tx_समय && !ipg) अणु
		ipg = tx_समय * 100 / duty_cycle - tx_समय;
	पूर्ण अन्यथा अगर (duty_cycle && !tx_समय && ipg) अणु
		अगर (duty_cycle < 100)
			tx_समय = duty_cycle * ipg / (100 - duty_cycle);
	पूर्ण

	mt7915_पंचांग_set_ipg_params(phy, ipg, td->tx_rate_mode);
	mt7915_पंचांग_set_tx_len(phy, tx_समय);

	अगर (ipg)
		td->tx_queued_limit = MT76_TM_TIMEOUT * 1000000 / ipg / 2;

	अगर (!en || !td->tx_skb)
		वापस;

	info = IEEE80211_SKB_CB(td->tx_skb);
	info->control.vअगर = phy->monitor_vअगर;

	mt7915_पंचांग_set_trx(phy, TM_MAC_TX, en);
पूर्ण

अटल व्योम
mt7915_पंचांग_set_rx_frames(काष्ठा mt7915_phy *phy, bool en)
अणु
	अगर (en)
		mt7915_पंचांग_update_channel(phy);

	mt7915_पंचांग_set_trx(phy, TM_MAC_RX_RXV, en);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_rf_चयन_mode(काष्ठा mt7915_dev *dev, u32 oper)
अणु
	काष्ठा mt7915_पंचांग_rf_test req = अणु
		.op.op_mode = cpu_to_le32(oper),
	पूर्ण;

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(RF_TEST), &req,
				 माप(req), true);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_tx_cont(काष्ठा mt7915_phy *phy, bool en)
अणु
#घोषणा TX_CONT_START	0x05
#घोषणा TX_CONT_STOP	0x06
	काष्ठा mt7915_dev *dev = phy->dev;
	काष्ठा cfg80211_chan_def *chandef = &phy->mt76->chandef;
	पूर्णांक freq1 = ieee80211_frequency_to_channel(chandef->center_freq1);
	काष्ठा mt76_tesपंचांगode_data *td = &phy->mt76->test;
	u32 func_idx = en ? TX_CONT_START : TX_CONT_STOP;
	u8 rate_idx = td->tx_rate_idx, mode;
	u16 rateval;
	काष्ठा mt7915_पंचांग_rf_test req = अणु
		.action = 1,
		.icap_len = 120,
		.op.rf.func_idx = cpu_to_le32(func_idx),
	पूर्ण;
	काष्ठा पंचांग_tx_cont *tx_cont = &req.op.rf.param.tx_cont;

	tx_cont->control_ch = chandef->chan->hw_value;
	tx_cont->center_ch = freq1;
	tx_cont->tx_ant = td->tx_antenna_mask;
	tx_cont->band = phy != &dev->phy;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		tx_cont->bw = CMD_CBW_40MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		tx_cont->bw = CMD_CBW_80MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		tx_cont->bw = CMD_CBW_8080MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		tx_cont->bw = CMD_CBW_160MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
		tx_cont->bw = CMD_CBW_5MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		tx_cont->bw = CMD_CBW_10MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
		tx_cont->bw = CMD_CBW_20MHZ;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		tx_cont->bw = CMD_CBW_20MHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!en) अणु
		req.op.rf.param.func_data = cpu_to_le32(phy != &dev->phy);
		जाओ out;
	पूर्ण

	अगर (td->tx_rate_mode <= MT76_TM_TX_MODE_OFDM) अणु
		काष्ठा ieee80211_supported_band *sband;
		u8 idx = rate_idx;

		अगर (chandef->chan->band == NL80211_BAND_5GHZ)
			sband = &phy->mt76->sband_5g.sband;
		अन्यथा
			sband = &phy->mt76->sband_2g.sband;

		अगर (td->tx_rate_mode == MT76_TM_TX_MODE_OFDM)
			idx += 4;
		rate_idx = sband->bitrates[idx].hw_value & 0xff;
	पूर्ण

	चयन (td->tx_rate_mode) अणु
	हाल MT76_TM_TX_MODE_CCK:
		mode = MT_PHY_TYPE_CCK;
		अवरोध;
	हाल MT76_TM_TX_MODE_OFDM:
		mode = MT_PHY_TYPE_OFDM;
		अवरोध;
	हाल MT76_TM_TX_MODE_HT:
		mode = MT_PHY_TYPE_HT;
		अवरोध;
	हाल MT76_TM_TX_MODE_VHT:
		mode = MT_PHY_TYPE_VHT;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_SU:
		mode = MT_PHY_TYPE_HE_SU;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_EXT_SU:
		mode = MT_PHY_TYPE_HE_EXT_SU;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_TB:
		mode = MT_PHY_TYPE_HE_TB;
		अवरोध;
	हाल MT76_TM_TX_MODE_HE_MU:
		mode = MT_PHY_TYPE_HE_MU;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rateval =  mode << 6 | rate_idx;
	tx_cont->rateval = cpu_to_le16(rateval);

out:
	अगर (!en) अणु
		पूर्णांक ret;

		ret = mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(RF_TEST), &req,
					माप(req), true);
		अगर (ret)
			वापस ret;

		वापस mt7915_पंचांग_rf_चयन_mode(dev, RF_OPER_NORMAL);
	पूर्ण

	mt7915_पंचांग_rf_चयन_mode(dev, RF_OPER_RF_TEST);
	mt7915_पंचांग_update_channel(phy);

	वापस mt76_mcu_send_msg(&dev->mt76, MCU_EXT_CMD(RF_TEST), &req,
				 माप(req), true);
पूर्ण

अटल व्योम
mt7915_पंचांग_update_params(काष्ठा mt7915_phy *phy, u32 changed)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &phy->mt76->test;
	bool en = phy->mt76->test.state != MT76_TM_STATE_OFF;

	अगर (changed & BIT(TM_CHANGED_FREQ_OFFSET))
		mt7915_पंचांग_set_freq_offset(phy, en, en ? td->freq_offset : 0);
	अगर (changed & BIT(TM_CHANGED_TXPOWER))
		mt7915_पंचांग_set_tx_घातer(phy);
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_state(काष्ठा mt76_phy *mphy, क्रमागत mt76_tesपंचांगode_state state)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &mphy->test;
	काष्ठा mt7915_phy *phy = mphy->priv;
	क्रमागत mt76_tesपंचांगode_state prev_state = td->state;

	mphy->test.state = state;

	अगर (prev_state == MT76_TM_STATE_TX_FRAMES ||
	    state == MT76_TM_STATE_TX_FRAMES)
		mt7915_पंचांग_set_tx_frames(phy, state == MT76_TM_STATE_TX_FRAMES);
	अन्यथा अगर (prev_state == MT76_TM_STATE_RX_FRAMES ||
		 state == MT76_TM_STATE_RX_FRAMES)
		mt7915_पंचांग_set_rx_frames(phy, state == MT76_TM_STATE_RX_FRAMES);
	अन्यथा अगर (prev_state == MT76_TM_STATE_TX_CONT ||
		 state == MT76_TM_STATE_TX_CONT)
		mt7915_पंचांग_set_tx_cont(phy, state == MT76_TM_STATE_TX_CONT);
	अन्यथा अगर (prev_state == MT76_TM_STATE_OFF ||
		 state == MT76_TM_STATE_OFF)
		mt7915_पंचांग_init(phy, !(state == MT76_TM_STATE_OFF));

	अगर ((state == MT76_TM_STATE_IDLE &&
	     prev_state == MT76_TM_STATE_OFF) ||
	    (state == MT76_TM_STATE_OFF &&
	     prev_state == MT76_TM_STATE_IDLE)) अणु
		u32 changed = 0;
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(पंचांग_change_map); i++) अणु
			u16 cur = पंचांग_change_map[i];

			अगर (td->param_set[cur / 32] & BIT(cur % 32))
				changed |= BIT(i);
		पूर्ण

		mt7915_पंचांग_update_params(phy, changed);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_set_params(काष्ठा mt76_phy *mphy, काष्ठा nlattr **tb,
		     क्रमागत mt76_tesपंचांगode_state new_state)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &mphy->test;
	काष्ठा mt7915_phy *phy = mphy->priv;
	u32 changed = 0;
	पूर्णांक i;

	BUILD_BUG_ON(NUM_TM_CHANGED >= 32);

	अगर (new_state == MT76_TM_STATE_OFF ||
	    td->state == MT76_TM_STATE_OFF)
		वापस 0;

	अगर (td->tx_antenna_mask & ~mphy->chainmask)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(पंचांग_change_map); i++) अणु
		अगर (tb[पंचांग_change_map[i]])
			changed |= BIT(i);
	पूर्ण

	mt7915_पंचांग_update_params(phy, changed);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7915_पंचांग_dump_stats(काष्ठा mt76_phy *mphy, काष्ठा sk_buff *msg)
अणु
	काष्ठा mt7915_phy *phy = mphy->priv;
	व्योम *rx, *rssi;
	पूर्णांक i;

	rx = nla_nest_start(msg, MT76_TM_STATS_ATTR_LAST_RX);
	अगर (!rx)
		वापस -ENOMEM;

	अगर (nla_put_s32(msg, MT76_TM_RX_ATTR_FREQ_OFFSET, phy->test.last_freq_offset))
		वापस -ENOMEM;

	rssi = nla_nest_start(msg, MT76_TM_RX_ATTR_RCPI);
	अगर (!rssi)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(phy->test.last_rcpi); i++)
		अगर (nla_put_u8(msg, i, phy->test.last_rcpi[i]))
			वापस -ENOMEM;

	nla_nest_end(msg, rssi);

	rssi = nla_nest_start(msg, MT76_TM_RX_ATTR_IB_RSSI);
	अगर (!rssi)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(phy->test.last_ib_rssi); i++)
		अगर (nla_put_s8(msg, i, phy->test.last_ib_rssi[i]))
			वापस -ENOMEM;

	nla_nest_end(msg, rssi);

	rssi = nla_nest_start(msg, MT76_TM_RX_ATTR_WB_RSSI);
	अगर (!rssi)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(phy->test.last_wb_rssi); i++)
		अगर (nla_put_s8(msg, i, phy->test.last_wb_rssi[i]))
			वापस -ENOMEM;

	nla_nest_end(msg, rssi);

	अगर (nla_put_u8(msg, MT76_TM_RX_ATTR_SNR, phy->test.last_snr))
		वापस -ENOMEM;

	nla_nest_end(msg, rx);

	वापस 0;
पूर्ण

स्थिर काष्ठा mt76_tesपंचांगode_ops mt7915_tesपंचांगode_ops = अणु
	.set_state = mt7915_पंचांग_set_state,
	.set_params = mt7915_पंचांग_set_params,
	.dump_stats = mt7915_पंचांग_dump_stats,
पूर्ण;
