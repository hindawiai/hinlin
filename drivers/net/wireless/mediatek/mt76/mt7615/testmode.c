<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 Felix Fietkau <nbd@nbd.name> */

#समावेश "mt7615.h"
#समावेश "eeprom.h"
#समावेश "mcu.h"

क्रमागत अणु
	TM_CHANGED_TXPOWER_CTRL,
	TM_CHANGED_TXPOWER,
	TM_CHANGED_FREQ_OFFSET,

	/* must be last */
	NUM_TM_CHANGED
पूर्ण;


अटल स्थिर u8 पंचांग_change_map[] = अणु
	[TM_CHANGED_TXPOWER_CTRL] = MT76_TM_ATTR_TX_POWER_CONTROL,
	[TM_CHANGED_TXPOWER] = MT76_TM_ATTR_TX_POWER,
	[TM_CHANGED_FREQ_OFFSET] = MT76_TM_ATTR_FREQ_OFFSET,
पूर्ण;

अटल स्थिर u32 reg_backup_list[] = अणु
	MT_WF_PHY_RFINTF3_0(0),
	MT_WF_PHY_RFINTF3_0(1),
	MT_WF_PHY_RFINTF3_0(2),
	MT_WF_PHY_RFINTF3_0(3),
	MT_ANT_SWITCH_CON(2),
	MT_ANT_SWITCH_CON(3),
	MT_ANT_SWITCH_CON(4),
	MT_ANT_SWITCH_CON(6),
	MT_ANT_SWITCH_CON(7),
	MT_ANT_SWITCH_CON(8),
पूर्ण;

अटल स्थिर काष्ठा अणु
	u16 wf;
	u16 reg;
पूर्ण rf_backup_list[] = अणु
	अणु 0, 0x48 पूर्ण,
	अणु 1, 0x48 पूर्ण,
	अणु 2, 0x48 पूर्ण,
	अणु 3, 0x48 पूर्ण,
पूर्ण;

अटल पूर्णांक
mt7615_पंचांग_set_tx_घातer(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt76_phy *mphy = phy->mt76;
	पूर्णांक i, ret, n_chains = hweight8(mphy->antenna_mask);
	काष्ठा cfg80211_chan_def *chandef = &mphy->chandef;
	पूर्णांक freq = chandef->center_freq1, len, target_chains;
	u8 *data, *eep = (u8 *)dev->mt76.eeprom.data;
	क्रमागत nl80211_band band = chandef->chan->band;
	काष्ठा sk_buff *skb;
	काष्ठा अणु
		u8 center_chan;
		u8 dbdc_idx;
		u8 band;
		u8 rsv;
	पूर्ण __packed req_hdr = अणु
		.center_chan = ieee80211_frequency_to_channel(freq),
		.band = band,
		.dbdc_idx = phy != &dev->phy,
	पूर्ण;
	u8 *tx_घातer = शून्य;

	अगर (mphy->test.state != MT76_TM_STATE_OFF)
		tx_घातer = mphy->test.tx_घातer;

	len = MT7615_EE_MAX - MT_EE_NIC_CONF_0;
	skb = mt76_mcu_msg_alloc(&dev->mt76, शून्य, माप(req_hdr) + len);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &req_hdr, माप(req_hdr));
	data = skb_put_data(skb, eep + MT_EE_NIC_CONF_0, len);

	target_chains = mt7615_ext_pa_enabled(dev, band) ? 1 : n_chains;
	क्रम (i = 0; i < target_chains; i++) अणु
		ret = mt7615_eeprom_get_target_घातer_index(dev, chandef->chan, i);
		अगर (ret < 0) अणु
			dev_kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण

		अगर (tx_घातer && tx_घातer[i])
			data[ret - MT_EE_NIC_CONF_0] = tx_घातer[i];
	पूर्ण

	वापस mt76_mcu_skb_send_msg(&dev->mt76, skb,
				     MCU_EXT_CMD_SET_TX_POWER_CTRL, false);
पूर्ण

अटल व्योम
mt7615_पंचांग_reg_backup_restore(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	u32 *b = phy->test.reg_backup;
	पूर्णांक n_regs = ARRAY_SIZE(reg_backup_list);
	पूर्णांक n_rf_regs = ARRAY_SIZE(rf_backup_list);
	पूर्णांक i;

	अगर (phy->mt76->test.state == MT76_TM_STATE_OFF) अणु
		क्रम (i = 0; i < n_regs; i++)
			mt76_wr(dev, reg_backup_list[i], b[i]);

		क्रम (i = 0; i < n_rf_regs; i++)
			mt7615_rf_wr(dev, rf_backup_list[i].wf,
				     rf_backup_list[i].reg, b[n_regs + i]);
		वापस;
	पूर्ण

	अगर (b)
		वापस;

	b = devm_kzalloc(dev->mt76.dev, 4 * (n_regs + n_rf_regs),
			 GFP_KERNEL);
	अगर (!b)
		वापस;

	phy->test.reg_backup = b;
	क्रम (i = 0; i < n_regs; i++)
		b[i] = mt76_rr(dev, reg_backup_list[i]);
	क्रम (i = 0; i < n_rf_regs; i++)
		b[n_regs + i] = mt7615_rf_rr(dev, rf_backup_list[i].wf,
					     rf_backup_list[i].reg);
पूर्ण

अटल व्योम
mt7615_पंचांग_init(काष्ठा mt7615_phy *phy)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	अचिन्हित पूर्णांक total_flags = ~0;

	अगर (!test_bit(MT76_STATE_RUNNING, &phy->mt76->state))
		वापस;

	mt7615_mcu_set_sku_en(phy, phy->mt76->test.state == MT76_TM_STATE_OFF);

	mutex_unlock(&dev->mt76.mutex);
	mt7615_set_channel(phy);
	mt7615_ops.configure_filter(phy->mt76->hw, 0, &total_flags, 0);
	mutex_lock(&dev->mt76.mutex);

	mt7615_पंचांग_reg_backup_restore(phy);
पूर्ण

अटल व्योम
mt7615_पंचांग_set_rx_enable(काष्ठा mt7615_dev *dev, bool en)
अणु
	u32 rqcr_mask = (MT_ARB_RQCR_RX_START |
			 MT_ARB_RQCR_RXV_START |
			 MT_ARB_RQCR_RXV_R_EN |
			 MT_ARB_RQCR_RXV_T_EN) *
			(BIT(0) | BIT(MT_ARB_RQCR_BAND_SHIFT));

	अगर (en) अणु
		mt76_clear(dev, MT_ARB_SCR,
			   MT_ARB_SCR_RX0_DISABLE | MT_ARB_SCR_RX1_DISABLE);
		mt76_set(dev, MT_ARB_RQCR, rqcr_mask);
	पूर्ण अन्यथा अणु
		mt76_set(dev, MT_ARB_SCR,
			 MT_ARB_SCR_RX0_DISABLE | MT_ARB_SCR_RX1_DISABLE);
		mt76_clear(dev, MT_ARB_RQCR, rqcr_mask);
	पूर्ण
पूर्ण

अटल व्योम
mt7615_पंचांग_set_tx_antenna(काष्ठा mt7615_phy *phy, bool en)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt76_tesपंचांगode_data *td = &phy->mt76->test;
	u8 mask = td->tx_antenna_mask;
	पूर्णांक i;

	अगर (!mask)
		वापस;

	अगर (!en)
		mask = phy->mt76->chainmask;

	क्रम (i = 0; i < 4; i++) अणु
		mt76_rmw_field(dev, MT_WF_PHY_RFINTF3_0(i),
			       MT_WF_PHY_RFINTF3_0_ANT,
			       (td->tx_antenna_mask & BIT(i)) ? 0 : 0xa);

	पूर्ण

	/* 2.4 GHz band */
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(3), MT_ANT_SWITCH_CON_MODE(0),
		       (td->tx_antenna_mask & BIT(0)) ? 0x8 : 0x1b);
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(4), MT_ANT_SWITCH_CON_MODE(2),
		       (td->tx_antenna_mask & BIT(1)) ? 0xe : 0x1b);
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(6), MT_ANT_SWITCH_CON_MODE1(0),
		       (td->tx_antenna_mask & BIT(2)) ? 0x0 : 0xf);
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(7), MT_ANT_SWITCH_CON_MODE1(2),
		       (td->tx_antenna_mask & BIT(3)) ? 0x6 : 0xf);

	/* 5 GHz band */
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(4), MT_ANT_SWITCH_CON_MODE(1),
		       (td->tx_antenna_mask & BIT(0)) ? 0xd : 0x1b);
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(2), MT_ANT_SWITCH_CON_MODE(3),
		       (td->tx_antenna_mask & BIT(1)) ? 0x13 : 0x1b);
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(7), MT_ANT_SWITCH_CON_MODE1(1),
		       (td->tx_antenna_mask & BIT(2)) ? 0x5 : 0xf);
	mt76_rmw_field(dev, MT_ANT_SWITCH_CON(8), MT_ANT_SWITCH_CON_MODE1(3),
		       (td->tx_antenna_mask & BIT(3)) ? 0xb : 0xf);

	क्रम (i = 0; i < 4; i++) अणु
		u32 val;

		val = mt7615_rf_rr(dev, i, 0x48);
		val &= ~(0x3ff << 20);
		अगर (td->tx_antenna_mask & BIT(i))
			val |= 3 << 20;
		अन्यथा
			val |= (2 << 28) | (2 << 26) | (8 << 20);
		mt7615_rf_wr(dev, i, 0x48, val);
	पूर्ण
पूर्ण

अटल व्योम
mt7615_पंचांग_set_tx_frames(काष्ठा mt7615_phy *phy, bool en)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb = phy->mt76->test.tx_skb;

	mt7615_mcu_set_chan_info(phy, MCU_EXT_CMD_SET_RX_PATH);
	mt7615_पंचांग_set_tx_antenna(phy, en);
	mt7615_पंचांग_set_rx_enable(dev, !en);
	अगर (!en || !skb)
		वापस;

	info = IEEE80211_SKB_CB(skb);
	info->control.vअगर = phy->monitor_vअगर;
पूर्ण

अटल व्योम
mt7615_पंचांग_update_params(काष्ठा mt7615_phy *phy, u32 changed)
अणु
	काष्ठा mt7615_dev *dev = phy->dev;
	काष्ठा mt76_tesपंचांगode_data *td = &phy->mt76->test;
	bool en = phy->mt76->test.state != MT76_TM_STATE_OFF;

	अगर (changed & BIT(TM_CHANGED_TXPOWER_CTRL))
		mt7615_mcu_set_test_param(dev, MCU_ATE_SET_TX_POWER_CONTROL,
					  en, en && td->tx_घातer_control);
	अगर (changed & BIT(TM_CHANGED_FREQ_OFFSET))
		mt7615_mcu_set_test_param(dev, MCU_ATE_SET_FREQ_OFFSET,
					  en, en ? td->freq_offset : 0);
	अगर (changed & BIT(TM_CHANGED_TXPOWER))
		mt7615_पंचांग_set_tx_घातer(phy);
पूर्ण

अटल पूर्णांक
mt7615_पंचांग_set_state(काष्ठा mt76_phy *mphy, क्रमागत mt76_tesपंचांगode_state state)
अणु
	काष्ठा mt7615_phy *phy = mphy->priv;
	काष्ठा mt76_tesपंचांगode_data *td = &mphy->test;
	क्रमागत mt76_tesपंचांगode_state prev_state = td->state;

	mphy->test.state = state;

	अगर (prev_state == MT76_TM_STATE_TX_FRAMES)
		mt7615_पंचांग_set_tx_frames(phy, false);
	अन्यथा अगर (state == MT76_TM_STATE_TX_FRAMES)
		mt7615_पंचांग_set_tx_frames(phy, true);

	अगर (state <= MT76_TM_STATE_IDLE)
		mt7615_पंचांग_init(phy);

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

		mt7615_पंचांग_update_params(phy, changed);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_पंचांग_set_params(काष्ठा mt76_phy *mphy, काष्ठा nlattr **tb,
		     क्रमागत mt76_tesपंचांगode_state new_state)
अणु
	काष्ठा mt76_tesपंचांगode_data *td = &mphy->test;
	काष्ठा mt7615_phy *phy = mphy->priv;
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

	mt7615_पंचांग_update_params(phy, changed);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt7615_पंचांग_dump_stats(काष्ठा mt76_phy *mphy, काष्ठा sk_buff *msg)
अणु
	काष्ठा mt7615_phy *phy = mphy->priv;
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

	nla_nest_end(msg, rx);

	वापस 0;
पूर्ण

स्थिर काष्ठा mt76_tesपंचांगode_ops mt7615_tesपंचांगode_ops = अणु
	.set_state = mt7615_पंचांग_set_state,
	.set_params = mt7615_पंचांग_set_params,
	.dump_stats = mt7615_पंचांग_dump_stats,
पूर्ण;
