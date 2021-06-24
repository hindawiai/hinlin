<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/delay.h>
#समावेश "mt76x2.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"
#समावेश "../mt76x02_phy.h"

अटल bool
mt76x2_phy_tssi_init_cal(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	u32 flag = 0;

	अगर (!mt76x2_tssi_enabled(dev))
		वापस false;

	अगर (mt76x2_channel_silent(dev))
		वापस false;

	अगर (chan->band == NL80211_BAND_5GHZ)
		flag |= BIT(0);

	अगर (mt76x02_ext_pa_enabled(dev, chan->band))
		flag |= BIT(8);

	mt76x02_mcu_calibrate(dev, MCU_CAL_TSSI, flag);
	dev->cal.tssi_cal_करोne = true;
	वापस true;
पूर्ण

अटल व्योम
mt76x2_phy_channel_calibrate(काष्ठा mt76x02_dev *dev, bool mac_stopped)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	bool is_5ghz = chan->band == NL80211_BAND_5GHZ;

	अगर (dev->cal.channel_cal_करोne)
		वापस;

	अगर (mt76x2_channel_silent(dev))
		वापस;

	अगर (!dev->cal.tssi_cal_करोne)
		mt76x2_phy_tssi_init_cal(dev);

	अगर (!mac_stopped)
		mt76x2_mac_stop(dev, false);

	अगर (is_5ghz)
		mt76x02_mcu_calibrate(dev, MCU_CAL_LC, 0);

	mt76x02_mcu_calibrate(dev, MCU_CAL_TX_LOFT, is_5ghz);
	mt76x02_mcu_calibrate(dev, MCU_CAL_TXIQ, is_5ghz);
	mt76x02_mcu_calibrate(dev, MCU_CAL_RXIQC_FI, is_5ghz);
	mt76x02_mcu_calibrate(dev, MCU_CAL_TEMP_SENSOR, 0);
	mt76x02_mcu_calibrate(dev, MCU_CAL_TX_SHAPING, 0);

	अगर (!mac_stopped)
		mt76x2_mac_resume(dev);

	mt76x2_apply_gain_adj(dev);
	mt76x02_edcca_init(dev);

	dev->cal.channel_cal_करोne = true;
पूर्ण

व्योम mt76x2_phy_set_antenna(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	val = mt76_rr(dev, MT_BBP(AGC, 0));
	val &= ~(BIT(4) | BIT(1));
	चयन (dev->mphy.antenna_mask) अणु
	हाल 1:
		/* disable mac DAC control */
		mt76_clear(dev, MT_BBP(IBI, 9), BIT(11));
		mt76_clear(dev, MT_BBP(TXBE, 5), 3);
		mt76_rmw_field(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT, 0x3);
		mt76_rmw_field(dev, MT_BBP(CORE, 32), GENMASK(21, 20), 2);
		/* disable DAC 1 */
		mt76_rmw_field(dev, MT_BBP(CORE, 33), GENMASK(12, 9), 4);

		val &= ~(BIT(3) | BIT(0));
		अवरोध;
	हाल 2:
		/* disable mac DAC control */
		mt76_clear(dev, MT_BBP(IBI, 9), BIT(11));
		mt76_rmw_field(dev, MT_BBP(TXBE, 5), 3, 1);
		mt76_rmw_field(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT, 0xc);
		mt76_rmw_field(dev, MT_BBP(CORE, 32), GENMASK(21, 20), 1);
		/* disable DAC 0 */
		mt76_rmw_field(dev, MT_BBP(CORE, 33), GENMASK(12, 9), 1);

		val &= ~BIT(3);
		val |= BIT(0);
		अवरोध;
	हाल 3:
	शेष:
		/* enable mac DAC control */
		mt76_set(dev, MT_BBP(IBI, 9), BIT(11));
		mt76_set(dev, MT_BBP(TXBE, 5), 3);
		mt76_rmw_field(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT, 0xf);
		mt76_clear(dev, MT_BBP(CORE, 32), GENMASK(21, 20));
		mt76_clear(dev, MT_BBP(CORE, 33), GENMASK(12, 9));

		val &= ~BIT(0);
		val |= BIT(3);
		अवरोध;
	पूर्ण
	mt76_wr(dev, MT_BBP(AGC, 0), val);
पूर्ण

पूर्णांक mt76x2_phy_set_channel(काष्ठा mt76x02_dev *dev,
			   काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_channel *chan = chandef->chan;
	bool scan = test_bit(MT76_SCANNING, &dev->mphy.state);
	क्रमागत nl80211_band band = chan->band;
	u8 channel;

	u32 ext_cca_chan[4] = अणु
		[0] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(0)),
		[1] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(1)),
		[2] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(2)),
		[3] = FIELD_PREP(MT_EXT_CCA_CFG_CCA0, 3) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA1, 2) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIELD_PREP(MT_EXT_CCA_CFG_CCA_MASK, BIT(3)),
	पूर्ण;
	पूर्णांक ch_group_index;
	u8 bw, bw_index;
	पूर्णांक freq, freq1;
	पूर्णांक ret;

	dev->cal.channel_cal_करोne = false;
	freq = chandef->chan->center_freq;
	freq1 = chandef->center_freq1;
	channel = chan->hw_value;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		bw = 1;
		अगर (freq1 > freq) अणु
			bw_index = 1;
			ch_group_index = 0;
		पूर्ण अन्यथा अणु
			bw_index = 3;
			ch_group_index = 1;
		पूर्ण
		channel += 2 - ch_group_index * 4;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		ch_group_index = (freq - freq1 + 30) / 20;
		अगर (WARN_ON(ch_group_index < 0 || ch_group_index > 3))
			ch_group_index = 0;
		bw = 2;
		bw_index = ch_group_index;
		channel += 6 - ch_group_index * 4;
		अवरोध;
	शेष:
		bw = 0;
		bw_index = 0;
		ch_group_index = 0;
		अवरोध;
	पूर्ण

	mt76x2_पढ़ो_rx_gain(dev);
	mt76x2_phy_set_txघातer_regs(dev, band);
	mt76x2_configure_tx_delay(dev, band, bw);
	mt76x2_phy_set_txघातer(dev);

	mt76x02_phy_set_band(dev, chan->band, ch_group_index & 1);
	mt76x02_phy_set_bw(dev, chandef->width, ch_group_index);

	mt76_rmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_group_index]);

	ret = mt76x2_mcu_set_channel(dev, channel, bw, bw_index, scan);
	अगर (ret)
		वापस ret;

	mt76x2_mcu_init_gain(dev, channel, dev->cal.rx.mcu_gain, true);

	mt76x2_phy_set_antenna(dev);

	/* Enable LDPC Rx */
	अगर (mt76xx_rev(dev) >= MT76XX_REV_E3)
		mt76_set(dev, MT_BBP(RXO, 13), BIT(10));

	अगर (!dev->cal.init_cal_करोne) अणु
		u8 val = mt76x02_eeprom_get(dev, MT_EE_BT_RCAL_RESULT);

		अगर (val != 0xff)
			mt76x02_mcu_calibrate(dev, MCU_CAL_R, 0);
	पूर्ण

	mt76x02_mcu_calibrate(dev, MCU_CAL_RXDCOC, channel);

	/* Rx LPF calibration */
	अगर (!dev->cal.init_cal_करोne)
		mt76x02_mcu_calibrate(dev, MCU_CAL_RC, 0);

	dev->cal.init_cal_करोne = true;

	mt76_wr(dev, MT_BBP(AGC, 61), 0xFF64A4E2);
	mt76_wr(dev, MT_BBP(AGC, 7), 0x08081010);
	mt76_wr(dev, MT_BBP(AGC, 11), 0x00000404);
	mt76_wr(dev, MT_BBP(AGC, 2), 0x00007070);
	mt76_wr(dev, MT_TXOP_CTRL_CFG, 0x04101B3F);

	अगर (scan)
		वापस 0;

	mt76x2_phy_channel_calibrate(dev, true);
	mt76x02_init_agc_gain(dev);

	/* init शेष values क्रम temp compensation */
	अगर (mt76x2_tssi_enabled(dev)) अणु
		mt76_rmw_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP,
			       0x38);
		mt76_rmw_field(dev, MT_TX_ALC_CFG_2, MT_TX_ALC_CFG_2_TEMP_COMP,
			       0x38);
	पूर्ण

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);

	वापस 0;
पूर्ण

अटल व्योम
mt76x2_phy_temp_compensate(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76x2_temp_comp t;
	पूर्णांक temp, db_dअगरf;

	अगर (mt76x2_get_temp_comp(dev, &t))
		वापस;

	temp = mt76_get_field(dev, MT_TEMP_SENSOR, MT_TEMP_SENSOR_VAL);
	temp -= t.temp_25_ref;
	temp = (temp * 1789) / 1000 + 25;
	dev->cal.temp = temp;

	अगर (temp > 25)
		db_dअगरf = (temp - 25) / t.high_slope;
	अन्यथा
		db_dअगरf = (25 - temp) / t.low_slope;

	db_dअगरf = min(db_dअगरf, t.upper_bound);
	db_dअगरf = max(db_dअगरf, t.lower_bound);

	mt76_rmw_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP,
		       db_dअगरf * 2);
	mt76_rmw_field(dev, MT_TX_ALC_CFG_2, MT_TX_ALC_CFG_2_TEMP_COMP,
		       db_dअगरf * 2);
पूर्ण

व्योम mt76x2_phy_calibrate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76x02_dev *dev;

	dev = container_of(work, काष्ठा mt76x02_dev, cal_work.work);

	mutex_lock(&dev->mt76.mutex);

	mt76x2_phy_channel_calibrate(dev, false);
	mt76x2_phy_tssi_compensate(dev);
	mt76x2_phy_temp_compensate(dev);
	mt76x2_phy_update_channel_gain(dev);

	mutex_unlock(&dev->mt76.mutex);

	ieee80211_queue_delayed_work(mt76_hw(dev), &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
पूर्ण

पूर्णांक mt76x2_phy_start(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret;

	ret = mt76x02_mcu_set_radio_state(dev, true);
	अगर (ret)
		वापस ret;

	mt76x2_mcu_load_cr(dev, MT_RF_BBP_CR, 0, 0);

	वापस ret;
पूर्ण
