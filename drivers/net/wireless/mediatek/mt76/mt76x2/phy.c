<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश "mt76x2.h"
#समावेश "eeprom.h"
#समावेश "mcu.h"
#समावेश "../mt76x02_phy.h"

अटल व्योम
mt76x2_adjust_high_lna_gain(काष्ठा mt76x02_dev *dev, पूर्णांक reg, s8 offset)
अणु
	s8 gain;

	gain = FIELD_GET(MT_BBP_AGC_LNA_HIGH_GAIN,
			 mt76_rr(dev, MT_BBP(AGC, reg)));
	gain -= offset / 2;
	mt76_rmw_field(dev, MT_BBP(AGC, reg), MT_BBP_AGC_LNA_HIGH_GAIN, gain);
पूर्ण

अटल व्योम
mt76x2_adjust_agc_gain(काष्ठा mt76x02_dev *dev, पूर्णांक reg, s8 offset)
अणु
	s8 gain;

	gain = FIELD_GET(MT_BBP_AGC_GAIN, mt76_rr(dev, MT_BBP(AGC, reg)));
	gain += offset;
	mt76_rmw_field(dev, MT_BBP(AGC, reg), MT_BBP_AGC_GAIN, gain);
पूर्ण

व्योम mt76x2_apply_gain_adj(काष्ठा mt76x02_dev *dev)
अणु
	s8 *gain_adj = dev->cal.rx.high_gain;

	mt76x2_adjust_high_lna_gain(dev, 4, gain_adj[0]);
	mt76x2_adjust_high_lna_gain(dev, 5, gain_adj[1]);

	mt76x2_adjust_agc_gain(dev, 8, gain_adj[0]);
	mt76x2_adjust_agc_gain(dev, 9, gain_adj[1]);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_apply_gain_adj);

व्योम mt76x2_phy_set_txघातer_regs(काष्ठा mt76x02_dev *dev,
				 क्रमागत nl80211_band band)
अणु
	u32 pa_mode[2];
	u32 pa_mode_adj;

	अगर (band == NL80211_BAND_2GHZ) अणु
		pa_mode[0] = 0x010055ff;
		pa_mode[1] = 0x00550055;

		mt76_wr(dev, MT_TX_ALC_CFG_2, 0x35160a00);
		mt76_wr(dev, MT_TX_ALC_CFG_3, 0x35160a06);

		अगर (mt76x02_ext_pa_enabled(dev, band)) अणु
			mt76_wr(dev, MT_RF_PA_MODE_ADJ0, 0x0000ec00);
			mt76_wr(dev, MT_RF_PA_MODE_ADJ1, 0x0000ec00);
		पूर्ण अन्यथा अणु
			mt76_wr(dev, MT_RF_PA_MODE_ADJ0, 0xf4000200);
			mt76_wr(dev, MT_RF_PA_MODE_ADJ1, 0xfa000200);
		पूर्ण
	पूर्ण अन्यथा अणु
		pa_mode[0] = 0x0000ffff;
		pa_mode[1] = 0x00ff00ff;

		अगर (mt76x02_ext_pa_enabled(dev, band)) अणु
			mt76_wr(dev, MT_TX_ALC_CFG_2, 0x2f0f0400);
			mt76_wr(dev, MT_TX_ALC_CFG_3, 0x2f0f0476);
		पूर्ण अन्यथा अणु
			mt76_wr(dev, MT_TX_ALC_CFG_2, 0x1b0f0400);
			mt76_wr(dev, MT_TX_ALC_CFG_3, 0x1b0f0476);
		पूर्ण

		अगर (mt76x02_ext_pa_enabled(dev, band))
			pa_mode_adj = 0x04000000;
		अन्यथा
			pa_mode_adj = 0;

		mt76_wr(dev, MT_RF_PA_MODE_ADJ0, pa_mode_adj);
		mt76_wr(dev, MT_RF_PA_MODE_ADJ1, pa_mode_adj);
	पूर्ण

	mt76_wr(dev, MT_BB_PA_MODE_CFG0, pa_mode[0]);
	mt76_wr(dev, MT_BB_PA_MODE_CFG1, pa_mode[1]);
	mt76_wr(dev, MT_RF_PA_MODE_CFG0, pa_mode[0]);
	mt76_wr(dev, MT_RF_PA_MODE_CFG1, pa_mode[1]);

	अगर (mt76x02_ext_pa_enabled(dev, band)) अणु
		u32 val;

		अगर (band == NL80211_BAND_2GHZ)
			val = 0x3c3c023c;
		अन्यथा
			val = 0x363c023c;

		mt76_wr(dev, MT_TX0_RF_GAIN_CORR, val);
		mt76_wr(dev, MT_TX1_RF_GAIN_CORR, val);
		mt76_wr(dev, MT_TX_ALC_CFG_4, 0x00001818);
	पूर्ण अन्यथा अणु
		अगर (band == NL80211_BAND_2GHZ) अणु
			u32 val = 0x0f3c3c3c;

			mt76_wr(dev, MT_TX0_RF_GAIN_CORR, val);
			mt76_wr(dev, MT_TX1_RF_GAIN_CORR, val);
			mt76_wr(dev, MT_TX_ALC_CFG_4, 0x00000606);
		पूर्ण अन्यथा अणु
			mt76_wr(dev, MT_TX0_RF_GAIN_CORR, 0x383c023c);
			mt76_wr(dev, MT_TX1_RF_GAIN_CORR, 0x24282e28);
			mt76_wr(dev, MT_TX_ALC_CFG_4, 0);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_phy_set_txघातer_regs);

अटल पूर्णांक
mt76x2_get_min_rate_घातer(काष्ठा mt76_rate_घातer *r)
अणु
	पूर्णांक i;
	s8 ret = 0;

	क्रम (i = 0; i < माप(r->all); i++) अणु
		अगर (!r->all[i])
			जारी;

		अगर (ret)
			ret = min(ret, r->all[i]);
		अन्यथा
			ret = r->all[i];
	पूर्ण

	वापस ret;
पूर्ण

व्योम mt76x2_phy_set_txघातer(काष्ठा mt76x02_dev *dev)
अणु
	क्रमागत nl80211_chan_width width = dev->mphy.chandef.width;
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	काष्ठा mt76x2_tx_घातer_info txp;
	पूर्णांक txp_0, txp_1, delta = 0;
	काष्ठा mt76_rate_घातer t = अणुपूर्ण;
	पूर्णांक base_घातer, gain;

	mt76x2_get_घातer_info(dev, &txp, chan);

	अगर (width == NL80211_CHAN_WIDTH_40)
		delta = txp.delta_bw40;
	अन्यथा अगर (width == NL80211_CHAN_WIDTH_80)
		delta = txp.delta_bw80;

	mt76x2_get_rate_घातer(dev, &t, chan);
	mt76x02_add_rate_घातer_offset(&t, txp.target_घातer + delta);
	mt76x02_limit_rate_घातer(&t, dev->txघातer_conf);
	dev->mphy.txघातer_cur = mt76x02_get_max_rate_घातer(&t);

	base_घातer = mt76x2_get_min_rate_घातer(&t);
	delta = base_घातer - txp.target_घातer;
	txp_0 = txp.chain[0].target_घातer + txp.chain[0].delta + delta;
	txp_1 = txp.chain[1].target_घातer + txp.chain[1].delta + delta;

	gain = min(txp_0, txp_1);
	अगर (gain < 0) अणु
		base_घातer -= gain;
		txp_0 -= gain;
		txp_1 -= gain;
	पूर्ण अन्यथा अगर (gain > 0x2f) अणु
		base_घातer -= gain - 0x2f;
		txp_0 = 0x2f;
		txp_1 = 0x2f;
	पूर्ण

	mt76x02_add_rate_घातer_offset(&t, -base_घातer);
	dev->target_घातer = txp.target_घातer;
	dev->target_घातer_delta[0] = txp_0 - txp.chain[0].target_घातer;
	dev->target_घातer_delta[1] = txp_1 - txp.chain[0].target_घातer;
	dev->mt76.rate_घातer = t;

	mt76x02_phy_set_txघातer(dev, txp_0, txp_1);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_phy_set_txघातer);

व्योम mt76x2_configure_tx_delay(काष्ठा mt76x02_dev *dev,
			       क्रमागत nl80211_band band, u8 bw)
अणु
	u32 cfg0, cfg1;

	अगर (mt76x02_ext_pa_enabled(dev, band)) अणु
		cfg0 = bw ? 0x000b0c01 : 0x00101101;
		cfg1 = 0x00011414;
	पूर्ण अन्यथा अणु
		cfg0 = bw ? 0x000b0b01 : 0x00101001;
		cfg1 = 0x00021414;
	पूर्ण
	mt76_wr(dev, MT_TX_SW_CFG0, cfg0);
	mt76_wr(dev, MT_TX_SW_CFG1, cfg1);

	mt76_rmw_field(dev, MT_XIFS_TIME_CFG, MT_XIFS_TIME_CFG_OFDM_SIFS, 15);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_configure_tx_delay);

व्योम mt76x2_phy_tssi_compensate(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	काष्ठा mt76x2_tx_घातer_info txp;
	काष्ठा mt76x2_tssi_comp t = अणुपूर्ण;

	अगर (!dev->cal.tssi_cal_करोne)
		वापस;

	अगर (!dev->cal.tssi_comp_pending) अणु
		/* TSSI trigger */
		t.cal_mode = BIT(0);
		mt76x2_mcu_tssi_comp(dev, &t);
		dev->cal.tssi_comp_pending = true;
	पूर्ण अन्यथा अणु
		अगर (mt76_rr(dev, MT_BBP(CORE, 34)) & BIT(4))
			वापस;

		dev->cal.tssi_comp_pending = false;
		mt76x2_get_घातer_info(dev, &txp, chan);

		अगर (mt76x02_ext_pa_enabled(dev, chan->band))
			t.pa_mode = 1;

		t.cal_mode = BIT(1);
		t.slope0 = txp.chain[0].tssi_slope;
		t.offset0 = txp.chain[0].tssi_offset;
		t.slope1 = txp.chain[1].tssi_slope;
		t.offset1 = txp.chain[1].tssi_offset;
		mt76x2_mcu_tssi_comp(dev, &t);

		अगर (t.pa_mode || dev->cal.dpd_cal_करोne || dev->ed_tx_blocked)
			वापस;

		usleep_range(10000, 20000);
		mt76x02_mcu_calibrate(dev, MCU_CAL_DPD, chan->hw_value);
		dev->cal.dpd_cal_करोne = true;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_phy_tssi_compensate);

अटल व्योम
mt76x2_phy_set_gain_val(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;
	u8 gain_val[2];

	gain_val[0] = dev->cal.agc_gain_cur[0] - dev->cal.agc_gain_adjust;
	gain_val[1] = dev->cal.agc_gain_cur[1] - dev->cal.agc_gain_adjust;

	val = 0x1836 << 16;
	अगर (!mt76x2_has_ext_lna(dev) &&
	    dev->mphy.chandef.width >= NL80211_CHAN_WIDTH_40)
		val = 0x1e42 << 16;

	अगर (mt76x2_has_ext_lna(dev) &&
	    dev->mphy.chandef.chan->band == NL80211_BAND_2GHZ &&
	    dev->mphy.chandef.width < NL80211_CHAN_WIDTH_40)
		val = 0x0f36 << 16;

	val |= 0xf8;

	mt76_wr(dev, MT_BBP(AGC, 8),
		val | FIELD_PREP(MT_BBP_AGC_GAIN, gain_val[0]));
	mt76_wr(dev, MT_BBP(AGC, 9),
		val | FIELD_PREP(MT_BBP_AGC_GAIN, gain_val[1]));

	अगर (dev->mphy.chandef.chan->flags & IEEE80211_CHAN_RADAR)
		mt76x02_phy_dfs_adjust_agc(dev);
पूर्ण

व्योम mt76x2_phy_update_channel_gain(काष्ठा mt76x02_dev *dev)
अणु
	u8 *gain = dev->cal.agc_gain_init;
	u8 low_gain_delta, gain_delta;
	u32 agc_35, agc_37;
	bool gain_change;
	पूर्णांक low_gain;
	u32 val;

	dev->cal.avg_rssi_all = mt76_get_min_avg_rssi(&dev->mt76, false);
	अगर (!dev->cal.avg_rssi_all)
		dev->cal.avg_rssi_all = -75;

	low_gain = (dev->cal.avg_rssi_all > mt76x02_get_rssi_gain_thresh(dev)) +
		(dev->cal.avg_rssi_all > mt76x02_get_low_rssi_gain_thresh(dev));

	gain_change = dev->cal.low_gain < 0 ||
		      (dev->cal.low_gain & 2) ^ (low_gain & 2);
	dev->cal.low_gain = low_gain;

	अगर (!gain_change) अणु
		अगर (mt76x02_phy_adjust_vga_gain(dev))
			mt76x2_phy_set_gain_val(dev);
		वापस;
	पूर्ण

	अगर (dev->mphy.chandef.width == NL80211_CHAN_WIDTH_80) अणु
		mt76_wr(dev, MT_BBP(RXO, 14), 0x00560211);
		val = mt76_rr(dev, MT_BBP(AGC, 26)) & ~0xf;
		अगर (low_gain == 2)
			val |= 0x3;
		अन्यथा
			val |= 0x5;
		mt76_wr(dev, MT_BBP(AGC, 26), val);
	पूर्ण अन्यथा अणु
		mt76_wr(dev, MT_BBP(RXO, 14), 0x00560423);
	पूर्ण

	अगर (mt76x2_has_ext_lna(dev))
		low_gain_delta = 10;
	अन्यथा
		low_gain_delta = 14;

	agc_37 = 0x2121262c;
	अगर (dev->mphy.chandef.chan->band == NL80211_BAND_2GHZ)
		agc_35 = 0x11111516;
	अन्यथा अगर (low_gain == 2)
		agc_35 = agc_37 = 0x08080808;
	अन्यथा अगर (dev->mphy.chandef.width == NL80211_CHAN_WIDTH_80)
		agc_35 = 0x10101014;
	अन्यथा
		agc_35 = 0x11111116;

	अगर (low_gain == 2) अणु
		mt76_wr(dev, MT_BBP(RXO, 18), 0xf000a990);
		mt76_wr(dev, MT_BBP(AGC, 35), 0x08080808);
		mt76_wr(dev, MT_BBP(AGC, 37), 0x08080808);
		gain_delta = low_gain_delta;
		dev->cal.agc_gain_adjust = 0;
	पूर्ण अन्यथा अणु
		mt76_wr(dev, MT_BBP(RXO, 18), 0xf000a991);
		gain_delta = 0;
		dev->cal.agc_gain_adjust = low_gain_delta;
	पूर्ण

	mt76_wr(dev, MT_BBP(AGC, 35), agc_35);
	mt76_wr(dev, MT_BBP(AGC, 37), agc_37);

	dev->cal.agc_gain_cur[0] = gain[0] - gain_delta;
	dev->cal.agc_gain_cur[1] = gain[1] - gain_delta;
	mt76x2_phy_set_gain_val(dev);

	/* clear false CCA counters */
	mt76_rr(dev, MT_RX_STAT_1);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x2_phy_update_channel_gain);
