<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 */

#समावेश "mt7601u.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"
#समावेश "trace.h"
#समावेश "initvals_phy.h"

#समावेश <linux/etherdevice.h>

अटल व्योम mt7601u_agc_reset(काष्ठा mt7601u_dev *dev);

अटल पूर्णांक
mt7601u_rf_wr(काष्ठा mt7601u_dev *dev, u8 bank, u8 offset, u8 value)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON(!test_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state)) ||
	    WARN_ON(offset > 63))
		वापस -EINVAL;
	अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
		वापस 0;

	mutex_lock(&dev->reg_atomic_mutex);

	अगर (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	mt7601u_wr(dev, MT_RF_CSR_CFG,
		   FIELD_PREP(MT_RF_CSR_CFG_DATA, value) |
		   FIELD_PREP(MT_RF_CSR_CFG_REG_BANK, bank) |
		   FIELD_PREP(MT_RF_CSR_CFG_REG_ID, offset) |
		   MT_RF_CSR_CFG_WR |
		   MT_RF_CSR_CFG_KICK);
	trace_rf_ग_लिखो(dev, bank, offset, value);
out:
	mutex_unlock(&dev->reg_atomic_mutex);

	अगर (ret < 0)
		dev_err(dev->dev, "Error: RF write %02hhx:%02hhx failed:%d!!\n",
			bank, offset, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7601u_rf_rr(काष्ठा mt7601u_dev *dev, u8 bank, u8 offset)
अणु
	पूर्णांक ret = -ETIMEDOUT;
	u32 val;

	अगर (WARN_ON(!test_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state)) ||
	    WARN_ON(offset > 63))
		वापस -EINVAL;
	अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
		वापस 0xff;

	mutex_lock(&dev->reg_atomic_mutex);

	अगर (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100))
		जाओ out;

	mt7601u_wr(dev, MT_RF_CSR_CFG,
		   FIELD_PREP(MT_RF_CSR_CFG_REG_BANK, bank) |
		   FIELD_PREP(MT_RF_CSR_CFG_REG_ID, offset) |
		   MT_RF_CSR_CFG_KICK);

	अगर (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100))
		जाओ out;

	val = mt7601u_rr(dev, MT_RF_CSR_CFG);
	अगर (FIELD_GET(MT_RF_CSR_CFG_REG_ID, val) == offset &&
	    FIELD_GET(MT_RF_CSR_CFG_REG_BANK, val) == bank) अणु
		ret = FIELD_GET(MT_RF_CSR_CFG_DATA, val);
		trace_rf_पढ़ो(dev, bank, offset, ret);
	पूर्ण
out:
	mutex_unlock(&dev->reg_atomic_mutex);

	अगर (ret < 0)
		dev_err(dev->dev, "Error: RF read %02hhx:%02hhx failed:%d!!\n",
			bank, offset, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt7601u_rf_rmw(काष्ठा mt7601u_dev *dev, u8 bank, u8 offset, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	ret = mt7601u_rf_rr(dev, bank, offset);
	अगर (ret < 0)
		वापस ret;
	val |= ret & ~mask;
	ret = mt7601u_rf_wr(dev, bank, offset, val);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण

अटल पूर्णांक
mt7601u_rf_set(काष्ठा mt7601u_dev *dev, u8 bank, u8 offset, u8 val)
अणु
	वापस mt7601u_rf_rmw(dev, bank, offset, 0, val);
पूर्ण

अटल पूर्णांक
mt7601u_rf_clear(काष्ठा mt7601u_dev *dev, u8 bank, u8 offset, u8 mask)
अणु
	वापस mt7601u_rf_rmw(dev, bank, offset, mask, 0);
पूर्ण

अटल व्योम mt7601u_bbp_wr(काष्ठा mt7601u_dev *dev, u8 offset, u8 val)
अणु
	अगर (WARN_ON(!test_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state)) ||
	    test_bit(MT7601U_STATE_REMOVED, &dev->state))
		वापस;

	mutex_lock(&dev->reg_atomic_mutex);

	अगर (!mt76_poll(dev, MT_BBP_CSR_CFG, MT_BBP_CSR_CFG_BUSY, 0, 1000)) अणु
		dev_err(dev->dev, "Error: BBP write %02hhx failed!!\n", offset);
		जाओ out;
	पूर्ण

	mt7601u_wr(dev, MT_BBP_CSR_CFG,
		   FIELD_PREP(MT_BBP_CSR_CFG_VAL, val) |
		   FIELD_PREP(MT_BBP_CSR_CFG_REG_NUM, offset) |
		   MT_BBP_CSR_CFG_RW_MODE | MT_BBP_CSR_CFG_BUSY);
	trace_bbp_ग_लिखो(dev, offset, val);
out:
	mutex_unlock(&dev->reg_atomic_mutex);
पूर्ण

अटल पूर्णांक mt7601u_bbp_rr(काष्ठा mt7601u_dev *dev, u8 offset)
अणु
	u32 val;
	पूर्णांक ret = -ETIMEDOUT;

	अगर (WARN_ON(!test_bit(MT7601U_STATE_WLAN_RUNNING, &dev->state)))
		वापस -EINVAL;
	अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
		वापस 0xff;

	mutex_lock(&dev->reg_atomic_mutex);

	अगर (!mt76_poll(dev, MT_BBP_CSR_CFG, MT_BBP_CSR_CFG_BUSY, 0, 1000))
		जाओ out;

	mt7601u_wr(dev, MT_BBP_CSR_CFG,
		   FIELD_PREP(MT_BBP_CSR_CFG_REG_NUM, offset) |
		   MT_BBP_CSR_CFG_RW_MODE | MT_BBP_CSR_CFG_BUSY |
		   MT_BBP_CSR_CFG_READ);

	अगर (!mt76_poll(dev, MT_BBP_CSR_CFG, MT_BBP_CSR_CFG_BUSY, 0, 1000))
		जाओ out;

	val = mt7601u_rr(dev, MT_BBP_CSR_CFG);
	अगर (FIELD_GET(MT_BBP_CSR_CFG_REG_NUM, val) == offset) अणु
		ret = FIELD_GET(MT_BBP_CSR_CFG_VAL, val);
		trace_bbp_पढ़ो(dev, offset, ret);
	पूर्ण
out:
	mutex_unlock(&dev->reg_atomic_mutex);

	अगर (ret < 0)
		dev_err(dev->dev, "Error: BBP read %02hhx failed:%d!!\n",
			offset, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7601u_bbp_rmw(काष्ठा mt7601u_dev *dev, u8 offset, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	ret = mt7601u_bbp_rr(dev, offset);
	अगर (ret < 0)
		वापस ret;
	val |= ret & ~mask;
	mt7601u_bbp_wr(dev, offset, val);

	वापस val;
पूर्ण

अटल u8 mt7601u_bbp_rmc(काष्ठा mt7601u_dev *dev, u8 offset, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	ret = mt7601u_bbp_rr(dev, offset);
	अगर (ret < 0)
		वापस ret;
	val |= ret & ~mask;
	अगर (ret != val)
		mt7601u_bbp_wr(dev, offset, val);

	वापस val;
पूर्ण

पूर्णांक mt7601u_रुको_bbp_पढ़ोy(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i = 20;
	u8 val;

	करो अणु
		val = mt7601u_bbp_rr(dev, MT_BBP_REG_VERSION);
		अगर (val && val != 0xff)
			अवरोध;
	पूर्ण जबतक (--i);

	अगर (!i) अणु
		dev_err(dev->dev, "Error: BBP is not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

u32 mt7601u_bbp_set_ctrlch(काष्ठा mt7601u_dev *dev, bool below)
अणु
	वापस mt7601u_bbp_rmc(dev, 3, 0x20, below ? 0x20 : 0);
पूर्ण

पूर्णांक mt7601u_phy_get_rssi(काष्ठा mt7601u_dev *dev,
			 काष्ठा mt7601u_rxwi *rxwi, u16 rate)
अणु
	अटल स्थिर s8 lna[2][2][3] = अणु
		/* मुख्य LNA */ अणु
			/* bw20 */ अणु -2, 15, 33 पूर्ण,
			/* bw40 */ अणु  0, 16, 34 पूर्ण
		पूर्ण,
		/*  aux LNA */ अणु
			/* bw20 */ अणु -2, 15, 33 पूर्ण,
			/* bw40 */ अणु -2, 16, 34 पूर्ण
		पूर्ण
	पूर्ण;
	पूर्णांक bw = FIELD_GET(MT_RXWI_RATE_BW, rate);
	पूर्णांक aux_lna = FIELD_GET(MT_RXWI_ANT_AUX_LNA, rxwi->ant);
	पूर्णांक lna_id = FIELD_GET(MT_RXWI_GAIN_RSSI_LNA_ID, rxwi->gain);
	पूर्णांक val;

	अगर (lna_id) /* LNA id can be 0, 2, 3. */
		lna_id--;

	val = 8;
	val -= lna[aux_lna][bw][lna_id];
	val -= FIELD_GET(MT_RXWI_GAIN_RSSI_VAL, rxwi->gain);
	val -= dev->ee->lna_gain;
	val -= dev->ee->rssi_offset[0];

	वापस val;
पूर्ण

अटल व्योम mt7601u_vco_cal(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_rf_wr(dev, 0, 4, 0x0a);
	mt7601u_rf_wr(dev, 0, 5, 0x20);
	mt7601u_rf_set(dev, 0, 4, BIT(7));
	msleep(2);
पूर्ण

अटल पूर्णांक mt7601u_set_bw_filter(काष्ठा mt7601u_dev *dev, bool cal)
अणु
	u32 filter = 0;
	पूर्णांक ret;

	अगर (!cal)
		filter |= 0x10000;
	अगर (dev->bw != MT_BW_20)
		filter |= 0x00100;

	/* TX */
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_BW, filter | 1);
	अगर (ret)
		वापस ret;
	/* RX */
	वापस mt7601u_mcu_calibrate(dev, MCU_CAL_BW, filter);
पूर्ण

अटल पूर्णांक mt7601u_load_bbp_temp_table_bw(काष्ठा mt7601u_dev *dev)
अणु
	स्थिर काष्ठा reg_table *t;

	अगर (WARN_ON(dev->temp_mode > MT_TEMP_MODE_LOW))
		वापस -EINVAL;

	t = &bbp_mode_table[dev->temp_mode][dev->bw];

	वापस mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP, t->regs, t->n);
पूर्ण

अटल पूर्णांक mt7601u_bbp_temp(काष्ठा mt7601u_dev *dev, पूर्णांक mode, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा reg_table *t;
	पूर्णांक ret;

	अगर (dev->temp_mode == mode)
		वापस 0;

	dev->temp_mode = mode;
	trace_temp_mode(dev, mode);

	t = bbp_mode_table[dev->temp_mode];
	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				      t[2].regs, t[2].n);
	अगर (ret)
		वापस ret;

	वापस mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				       t[dev->bw].regs, t[dev->bw].n);
पूर्ण

अटल व्योम mt7601u_apply_ch14_fixup(काष्ठा mt7601u_dev *dev, पूर्णांक hw_chan)
अणु
	काष्ठा mt7601u_rate_घातer *t = &dev->ee->घातer_rate_table;

	अगर (hw_chan != 14 || dev->bw != MT_BW_20) अणु
		mt7601u_bbp_rmw(dev, 4, 0x20, 0);
		mt7601u_bbp_wr(dev, 178, 0xff);

		t->cck[0].bw20 = dev->ee->real_cck_bw20[0];
		t->cck[1].bw20 = dev->ee->real_cck_bw20[1];
	पूर्ण अन्यथा अणु /* Apply CH14 OBW fixup */
		mt7601u_bbp_wr(dev, 4, 0x60);
		mt7601u_bbp_wr(dev, 178, 0);

		/* Note: venकरोr code is buggy here क्रम negative values */
		t->cck[0].bw20 = dev->ee->real_cck_bw20[0] - 2;
		t->cck[1].bw20 = dev->ee->real_cck_bw20[1] - 2;
	पूर्ण
पूर्ण

अटल पूर्णांक __mt7601u_phy_set_channel(काष्ठा mt7601u_dev *dev,
				     काष्ठा cfg80211_chan_def *chandef)
अणु
#घोषणा FREQ_PLAN_REGS	4
	अटल स्थिर u8 freq_plan[14][FREQ_PLAN_REGS] = अणु
		अणु 0x99,	0x99,	0x09,	0x50 पूर्ण,
		अणु 0x46,	0x44,	0x0a,	0x50 पूर्ण,
		अणु 0xec,	0xee,	0x0a,	0x50 पूर्ण,
		अणु 0x99,	0x99,	0x0b,	0x50 पूर्ण,
		अणु 0x46,	0x44,	0x08,	0x51 पूर्ण,
		अणु 0xec,	0xee,	0x08,	0x51 पूर्ण,
		अणु 0x99,	0x99,	0x09,	0x51 पूर्ण,
		अणु 0x46,	0x44,	0x0a,	0x51 पूर्ण,
		अणु 0xec,	0xee,	0x0a,	0x51 पूर्ण,
		अणु 0x99,	0x99,	0x0b,	0x51 पूर्ण,
		अणु 0x46,	0x44,	0x08,	0x52 पूर्ण,
		अणु 0xec,	0xee,	0x08,	0x52 पूर्ण,
		अणु 0x99,	0x99,	0x09,	0x52 पूर्ण,
		अणु 0x33,	0x33,	0x0b,	0x52 पूर्ण,
	पूर्ण;
	काष्ठा mt76_reg_pair channel_freq_plan[FREQ_PLAN_REGS] = अणु
		अणु 17, 0 पूर्ण, अणु 18, 0 पूर्ण, अणु 19, 0 पूर्ण, अणु 20, 0 पूर्ण,
	पूर्ण;
	काष्ठा mt76_reg_pair bbp_settings[3] = अणु
		अणु 62, 0x37 - dev->ee->lna_gain पूर्ण,
		अणु 63, 0x37 - dev->ee->lna_gain पूर्ण,
		अणु 64, 0x37 - dev->ee->lna_gain पूर्ण,
	पूर्ण;

	काष्ठा ieee80211_channel *chan = chandef->chan;
	क्रमागत nl80211_channel_type chan_type =
		cfg80211_get_chandef_type(chandef);
	काष्ठा mt7601u_rate_घातer *t = &dev->ee->घातer_rate_table;
	पूर्णांक chan_idx;
	bool chan_ext_below;
	u8 bw;
	पूर्णांक i, ret;

	bw = MT_BW_20;
	chan_ext_below = (chan_type == NL80211_CHAN_HT40MINUS);
	chan_idx = chan->hw_value - 1;

	अगर (chandef->width == NL80211_CHAN_WIDTH_40) अणु
		bw = MT_BW_40;

		अगर (chan_idx > 1 && chan_type == NL80211_CHAN_HT40MINUS)
			chan_idx -= 2;
		अन्यथा अगर (chan_idx < 12 && chan_type == NL80211_CHAN_HT40PLUS)
			chan_idx += 2;
		अन्यथा
			dev_err(dev->dev, "Error: invalid 40MHz channel!!\n");
	पूर्ण

	अगर (bw != dev->bw || chan_ext_below != dev->chan_ext_below) अणु
		dev_dbg(dev->dev, "Info: switching HT mode bw:%d below:%d\n",
			bw, chan_ext_below);

		mt7601u_bbp_set_bw(dev, bw);

		mt7601u_bbp_set_ctrlch(dev, chan_ext_below);
		mt7601u_mac_set_ctrlch(dev, chan_ext_below);
		dev->chan_ext_below = chan_ext_below;
	पूर्ण

	क्रम (i = 0; i < FREQ_PLAN_REGS; i++)
		channel_freq_plan[i].value = freq_plan[chan_idx][i];

	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_RF,
				      channel_freq_plan, FREQ_PLAN_REGS);
	अगर (ret)
		वापस ret;

	mt7601u_rmw(dev, MT_TX_ALC_CFG_0, 0x3f3f,
		    dev->ee->chan_pwr[chan_idx] & 0x3f);

	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				      bbp_settings, ARRAY_SIZE(bbp_settings));
	अगर (ret)
		वापस ret;

	mt7601u_vco_cal(dev);
	mt7601u_bbp_set_bw(dev, bw);
	ret = mt7601u_set_bw_filter(dev, false);
	अगर (ret)
		वापस ret;

	mt7601u_apply_ch14_fixup(dev, chan->hw_value);
	mt7601u_wr(dev, MT_TX_PWR_CFG_0, पूर्णांक_to_s6(t->ofdm[1].bw20) << 24 |
					 पूर्णांक_to_s6(t->ofdm[0].bw20) << 16 |
					 पूर्णांक_to_s6(t->cck[1].bw20) << 8 |
					 पूर्णांक_to_s6(t->cck[0].bw20));

	अगर (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		mt7601u_agc_reset(dev);

	dev->chandef = *chandef;

	वापस 0;
पूर्ण

पूर्णांक mt7601u_phy_set_channel(काष्ठा mt7601u_dev *dev,
			    काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक ret;

	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->freq_cal.work);

	mutex_lock(&dev->hw_atomic_mutex);
	ret = __mt7601u_phy_set_channel(dev, chandef);
	mutex_unlock(&dev->hw_atomic_mutex);
	अगर (ret)
		वापस ret;

	अगर (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		वापस 0;

	ieee80211_queue_delayed_work(dev->hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
	अगर (dev->freq_cal.enabled)
		ieee80211_queue_delayed_work(dev->hw, &dev->freq_cal.work,
					     MT_FREQ_CAL_INIT_DELAY);
	वापस 0;
पूर्ण

#घोषणा BBP_R47_FLAG		GENMASK(2, 0)
#घोषणा BBP_R47_F_TSSI		0
#घोषणा BBP_R47_F_PKT_T		1
#घोषणा BBP_R47_F_TX_RATE	2
#घोषणा BBP_R47_F_TEMP		4
/**
 * mt7601u_bbp_r47_get - पढ़ो value through BBP R47/R49 pair
 * @dev:	poपूर्णांकer to adapter काष्ठाure
 * @reg:	value of BBP R47 beक्रमe the operation
 * @flag:	one of the BBP_R47_F_* flags
 *
 * Convenience helper क्रम पढ़ोing values through BBP R47/R49 pair.
 * Takes old value of BBP R47 as @reg, because callers usually have it
 * cached alपढ़ोy.
 *
 * Return: value of BBP R49.
 */
अटल u8 mt7601u_bbp_r47_get(काष्ठा mt7601u_dev *dev, u8 reg, u8 flag)
अणु
	flag |= reg & ~BBP_R47_FLAG;
	mt7601u_bbp_wr(dev, 47, flag);
	usleep_range(500, 700);
	वापस mt7601u_bbp_rr(dev, 49);
पूर्ण

अटल s8 mt7601u_पढ़ो_bootup_temp(काष्ठा mt7601u_dev *dev)
अणु
	u8 bbp_val, temp;
	u32 rf_bp, rf_set;
	पूर्णांक i;

	rf_set = mt7601u_rr(dev, MT_RF_SETTING_0);
	rf_bp = mt7601u_rr(dev, MT_RF_BYPASS_0);

	mt7601u_wr(dev, MT_RF_BYPASS_0, 0);
	mt7601u_wr(dev, MT_RF_SETTING_0, 0x00000010);
	mt7601u_wr(dev, MT_RF_BYPASS_0, 0x00000010);

	bbp_val = mt7601u_bbp_rmw(dev, 47, 0, 0x10);

	mt7601u_bbp_wr(dev, 22, 0x40);

	क्रम (i = 100; i && (bbp_val & 0x10); i--)
		bbp_val = mt7601u_bbp_rr(dev, 47);

	temp = mt7601u_bbp_r47_get(dev, bbp_val, BBP_R47_F_TEMP);

	mt7601u_bbp_wr(dev, 22, 0);

	bbp_val = mt7601u_bbp_rr(dev, 21);
	bbp_val |= 0x02;
	mt7601u_bbp_wr(dev, 21, bbp_val);
	bbp_val &= ~0x02;
	mt7601u_bbp_wr(dev, 21, bbp_val);

	mt7601u_wr(dev, MT_RF_BYPASS_0, 0);
	mt7601u_wr(dev, MT_RF_SETTING_0, rf_set);
	mt7601u_wr(dev, MT_RF_BYPASS_0, rf_bp);

	trace_पढ़ो_temp(dev, temp);
	वापस temp;
पूर्ण

अटल s8 mt7601u_पढ़ो_temp(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक i;
	u8 val;
	s8 temp;

	val = mt7601u_bbp_rmw(dev, 47, 0x7f, 0x10);

	/* Note: this rarely succeeds, temp can change even अगर it fails. */
	क्रम (i = 100; i && (val & 0x10); i--)
		val = mt7601u_bbp_rr(dev, 47);

	temp = mt7601u_bbp_r47_get(dev, val, BBP_R47_F_TEMP);

	trace_पढ़ो_temp(dev, temp);
	वापस temp;
पूर्ण

अटल व्योम mt7601u_rxdc_cal(काष्ठा mt7601u_dev *dev)
अणु
	अटल स्थिर काष्ठा mt76_reg_pair पूर्णांकro[] = अणु
		अणु 158, 0x8d पूर्ण, अणु 159, 0xfc पूर्ण,
		अणु 158, 0x8c पूर्ण, अणु 159, 0x4c पूर्ण,
	पूर्ण, outro[] = अणु
		अणु 158, 0x8d पूर्ण, अणु 159, 0xe0 पूर्ण,
	पूर्ण;
	u32 mac_ctrl;
	पूर्णांक i, ret;

	mac_ctrl = mt7601u_rr(dev, MT_MAC_SYS_CTRL);
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_RX);

	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				      पूर्णांकro, ARRAY_SIZE(पूर्णांकro));
	अगर (ret)
		dev_err(dev->dev, "%s intro failed:%d\n", __func__, ret);

	क्रम (i = 20; i; i--) अणु
		usleep_range(300, 500);

		mt7601u_bbp_wr(dev, 158, 0x8c);
		अगर (mt7601u_bbp_rr(dev, 159) == 0x0c)
			अवरोध;
	पूर्ण
	अगर (!i)
		dev_err(dev->dev, "%s timed out\n", __func__);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL, 0);

	ret = mt7601u_ग_लिखो_reg_pairs(dev, MT_MCU_MEMMAP_BBP,
				      outro, ARRAY_SIZE(outro));
	अगर (ret)
		dev_err(dev->dev, "%s outro failed:%d\n", __func__, ret);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL, mac_ctrl);
पूर्ण

व्योम mt7601u_phy_recalibrate_after_assoc(काष्ठा mt7601u_dev *dev)
अणु
	अगर (test_bit(MT7601U_STATE_REMOVED, &dev->state))
		वापस;

	mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->curr_temp);

	mt7601u_rxdc_cal(dev);
पूर्ण

/* Note: function copied from venकरोr driver */
अटल s16 lin2dBd(u16 linear)
अणु
	लघु exp = 0;
	अचिन्हित पूर्णांक mantisa;
	पूर्णांक app, dBd;

	अगर (WARN_ON(!linear))
		वापस -10000;

	mantisa = linear;

	exp = fls(mantisa) - 16;
	अगर (exp > 0)
		mantisa >>= exp;
	अन्यथा
		mantisa <<= असल(exp);

	अगर (mantisa <= 0xb800)
		app = (mantisa + (mantisa >> 3) + (mantisa >> 4) - 0x9600);
	अन्यथा
		app = (mantisa - (mantisa >> 3) - (mantisa >> 6) - 0x5a00);
	अगर (app < 0)
		app = 0;

	dBd = ((15 + exp) << 15) + app;
	dBd = (dBd << 2) + (dBd << 1) + (dBd >> 6) + (dBd >> 7);
	dBd = (dBd >> 10);

	वापस dBd;
पूर्ण

अटल व्योम
mt7601u_set_initial_tssi(काष्ठा mt7601u_dev *dev, s16 tssi_db, s16 tssi_hvga_db)
अणु
	काष्ठा tssi_data *d = &dev->ee->tssi_data;
	पूर्णांक init_offset;

	init_offset = -((tssi_db * d->slope + d->offset[1]) / 4096) + 10;

	mt76_rmw(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP,
		 पूर्णांक_to_s6(init_offset) & MT_TX_ALC_CFG_1_TEMP_COMP);
पूर्ण

अटल व्योम mt7601u_tssi_dc_gain_cal(काष्ठा mt7601u_dev *dev)
अणु
	u8 rf_vga, rf_mixer, bbp_r47;
	पूर्णांक i, j;
	s8 res[4];
	s16 tssi_init_db, tssi_init_hvga_db;

	mt7601u_wr(dev, MT_RF_SETTING_0, 0x00000030);
	mt7601u_wr(dev, MT_RF_BYPASS_0, 0x000c0030);
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, 0);

	mt7601u_bbp_wr(dev, 58, 0);
	mt7601u_bbp_wr(dev, 241, 0x2);
	mt7601u_bbp_wr(dev, 23, 0x8);
	bbp_r47 = mt7601u_bbp_rr(dev, 47);

	/* Set VGA gain */
	rf_vga = mt7601u_rf_rr(dev, 5, 3);
	mt7601u_rf_wr(dev, 5, 3, 8);

	/* Mixer disable */
	rf_mixer = mt7601u_rf_rr(dev, 4, 39);
	mt7601u_rf_wr(dev, 4, 39, 0);

	क्रम (i = 0; i < 4; i++) अणु
		mt7601u_rf_wr(dev, 4, 39, (i & 1) ? rf_mixer : 0);

		mt7601u_bbp_wr(dev, 23, (i < 2) ? 0x08 : 0x02);
		mt7601u_rf_wr(dev, 5, 3, (i < 2) ? 0x08 : 0x11);

		/* BBP TSSI initial and soft reset */
		mt7601u_bbp_wr(dev, 22, 0);
		mt7601u_bbp_wr(dev, 244, 0);

		mt7601u_bbp_wr(dev, 21, 1);
		udelay(1);
		mt7601u_bbp_wr(dev, 21, 0);

		/* TSSI measurement */
		mt7601u_bbp_wr(dev, 47, 0x50);
		mt7601u_bbp_wr(dev, (i & 1) ? 244 : 22, (i & 1) ? 0x31 : 0x40);

		क्रम (j = 20; j; j--)
			अगर (!(mt7601u_bbp_rr(dev, 47) & 0x10))
				अवरोध;
		अगर (!j)
			dev_err(dev->dev, "%s timed out\n", __func__);

		/* TSSI पढ़ो */
		mt7601u_bbp_wr(dev, 47, 0x40);
		res[i] = mt7601u_bbp_rr(dev, 49);
	पूर्ण

	tssi_init_db = lin2dBd((लघु)res[1] - res[0]);
	tssi_init_hvga_db = lin2dBd(((लघु)res[3] - res[2]) * 4);
	dev->tssi_init = res[0];
	dev->tssi_init_hvga = res[2];
	dev->tssi_init_hvga_offset_db = tssi_init_hvga_db - tssi_init_db;

	dev_dbg(dev->dev,
		"TSSI_init:%hhx db:%hx hvga:%hhx hvga_db:%hx off_db:%hx\n",
		dev->tssi_init, tssi_init_db, dev->tssi_init_hvga,
		tssi_init_hvga_db, dev->tssi_init_hvga_offset_db);

	mt7601u_bbp_wr(dev, 22, 0);
	mt7601u_bbp_wr(dev, 244, 0);

	mt7601u_bbp_wr(dev, 21, 1);
	udelay(1);
	mt7601u_bbp_wr(dev, 21, 0);

	mt7601u_wr(dev, MT_RF_BYPASS_0, 0);
	mt7601u_wr(dev, MT_RF_SETTING_0, 0);

	mt7601u_rf_wr(dev, 5, 3, rf_vga);
	mt7601u_rf_wr(dev, 4, 39, rf_mixer);
	mt7601u_bbp_wr(dev, 47, bbp_r47);

	mt7601u_set_initial_tssi(dev, tssi_init_db, tssi_init_hvga_db);
पूर्ण

अटल पूर्णांक mt7601u_temp_comp(काष्ठा mt7601u_dev *dev, bool on)
अणु
	पूर्णांक ret, temp, hi_temp = 400, lo_temp = -200;

	temp = (dev->raw_temp - dev->ee->ref_temp) * MT_EE_TEMPERATURE_SLOPE;
	dev->curr_temp = temp;

	/* DPD Calibration */
	अगर (temp - dev->dpd_temp > 450 || temp - dev->dpd_temp < -450) अणु
		dev->dpd_temp = temp;

		ret = mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->dpd_temp);
		अगर (ret)
			वापस ret;

		mt7601u_vco_cal(dev);

		dev_dbg(dev->dev, "Recalibrate DPD\n");
	पूर्ण

	/* PLL Lock Protect */
	अगर (temp < -50 && !dev->pll_lock_protect) अणु /* < 20C */
		dev->pll_lock_protect =  true;

		mt7601u_rf_wr(dev, 4, 4, 6);
		mt7601u_rf_clear(dev, 4, 10, 0x30);

		dev_dbg(dev->dev, "PLL lock protect on - too cold\n");
	पूर्ण अन्यथा अगर (temp > 50 && dev->pll_lock_protect) अणु /* > 30C */
		dev->pll_lock_protect = false;

		mt7601u_rf_wr(dev, 4, 4, 0);
		mt7601u_rf_rmw(dev, 4, 10, 0x30, 0x10);

		dev_dbg(dev->dev, "PLL lock protect off\n");
	पूर्ण

	अगर (on) अणु
		hi_temp -= 50;
		lo_temp -= 50;
	पूर्ण

	/* BBP CR क्रम H, L, N temperature */
	अगर (temp > hi_temp)
		वापस mt7601u_bbp_temp(dev, MT_TEMP_MODE_HIGH, "high");
	अन्यथा अगर (temp > lo_temp)
		वापस mt7601u_bbp_temp(dev, MT_TEMP_MODE_NORMAL, "normal");
	अन्यथा
		वापस mt7601u_bbp_temp(dev, MT_TEMP_MODE_LOW, "low");
पूर्ण

/* Note: this is used only with TSSI, we can just use trgt_pwr from eeprom. */
अटल पूर्णांक mt7601u_current_tx_घातer(काष्ठा mt7601u_dev *dev)
अणु
	वापस dev->ee->chan_pwr[dev->chandef.chan->hw_value - 1];
पूर्ण

अटल bool mt7601u_use_hvga(काष्ठा mt7601u_dev *dev)
अणु
	वापस !(mt7601u_current_tx_घातer(dev) > 20);
पूर्ण

अटल s16
mt7601u_phy_rf_pa_mode_val(काष्ठा mt7601u_dev *dev, पूर्णांक phy_mode, पूर्णांक tx_rate)
अणु
	अटल स्थिर s16 decode_tb[] = अणु 0, 8847, -5734, -5734 पूर्ण;
	u32 reg;

	चयन (phy_mode) अणु
	हाल MT_PHY_TYPE_OFDM:
		tx_rate += 4;
		fallthrough;
	हाल MT_PHY_TYPE_CCK:
		reg = dev->rf_pa_mode[0];
		अवरोध;
	शेष:
		reg = dev->rf_pa_mode[1];
		अवरोध;
	पूर्ण

	वापस decode_tb[(reg >> (tx_rate * 2)) & 0x3];
पूर्ण

अटल काष्ठा mt7601u_tssi_params
mt7601u_tssi_params_get(काष्ठा mt7601u_dev *dev)
अणु
	अटल स्थिर u8 ofdm_pkt2rate[8] = अणु 6, 4, 2, 0, 7, 5, 3, 1 पूर्ण;
	अटल स्थिर पूर्णांक अटल_घातer[4] = अणु 0, -49152, -98304, 49152 पूर्ण;
	काष्ठा mt7601u_tssi_params p;
	u8 bbp_r47, pkt_type, tx_rate;
	काष्ठा घातer_per_rate *rate_table;

	bbp_r47 = mt7601u_bbp_rr(dev, 47);

	p.tssi0 = mt7601u_bbp_r47_get(dev, bbp_r47, BBP_R47_F_TSSI);
	dev->raw_temp = mt7601u_bbp_r47_get(dev, bbp_r47, BBP_R47_F_TEMP);
	pkt_type = mt7601u_bbp_r47_get(dev, bbp_r47, BBP_R47_F_PKT_T);

	p.trgt_घातer = mt7601u_current_tx_घातer(dev);

	चयन (pkt_type & 0x03) अणु
	हाल MT_PHY_TYPE_CCK:
		tx_rate = (pkt_type >> 4) & 0x03;
		rate_table = dev->ee->घातer_rate_table.cck;
		अवरोध;

	हाल MT_PHY_TYPE_OFDM:
		tx_rate = ofdm_pkt2rate[(pkt_type >> 4) & 0x07];
		rate_table = dev->ee->घातer_rate_table.ofdm;
		अवरोध;

	शेष:
		tx_rate = mt7601u_bbp_r47_get(dev, bbp_r47, BBP_R47_F_TX_RATE);
		tx_rate &= 0x7f;
		rate_table = dev->ee->घातer_rate_table.ht;
		अवरोध;
	पूर्ण

	अगर (dev->bw == MT_BW_20)
		p.trgt_घातer += rate_table[tx_rate / 2].bw20;
	अन्यथा
		p.trgt_घातer += rate_table[tx_rate / 2].bw40;

	p.trgt_घातer <<= 12;

	dev_dbg(dev->dev, "tx_rate:%02hhx pwr:%08x\n", tx_rate, p.trgt_घातer);

	p.trgt_घातer += mt7601u_phy_rf_pa_mode_val(dev, pkt_type & 0x03,
						   tx_rate);

	/* Channel 14, cck, bw20 */
	अगर ((pkt_type & 0x03) == MT_PHY_TYPE_CCK) अणु
		अगर (mt7601u_bbp_rr(dev, 4) & 0x20)
			p.trgt_घातer += mt7601u_bbp_rr(dev, 178) ? 18022 : 9830;
		अन्यथा
			p.trgt_घातer += mt7601u_bbp_rr(dev, 178) ? 819 : 24576;
	पूर्ण

	p.trgt_घातer += अटल_घातer[mt7601u_bbp_rr(dev, 1) & 0x03];

	p.trgt_घातer += dev->ee->tssi_data.tx0_delta_offset;

	dev_dbg(dev->dev,
		"tssi:%02hhx t_power:%08x temp:%02hhx pkt_type:%02hhx\n",
		p.tssi0, p.trgt_घातer, dev->raw_temp, pkt_type);

	वापस p;
पूर्ण

अटल bool mt7601u_tssi_पढ़ो_पढ़ोy(काष्ठा mt7601u_dev *dev)
अणु
	वापस !(mt7601u_bbp_rr(dev, 47) & 0x10);
पूर्ण

अटल पूर्णांक mt7601u_tssi_cal(काष्ठा mt7601u_dev *dev)
अणु
	काष्ठा mt7601u_tssi_params params;
	पूर्णांक curr_pwr, dअगरf_pwr;
	अक्षर tssi_offset;
	s8 tssi_init;
	s16 tssi_m_dc, tssi_db;
	bool hvga;
	u32 val;

	अगर (!dev->ee->tssi_enabled)
		वापस 0;

	hvga = mt7601u_use_hvga(dev);
	अगर (!dev->tssi_पढ़ो_trig)
		वापस mt7601u_mcu_tssi_पढ़ो_kick(dev, hvga);

	अगर (!mt7601u_tssi_पढ़ो_पढ़ोy(dev))
		वापस 0;

	params = mt7601u_tssi_params_get(dev);

	tssi_init = (hvga ? dev->tssi_init_hvga : dev->tssi_init);
	tssi_m_dc = params.tssi0 - tssi_init;
	tssi_db = lin2dBd(tssi_m_dc);
	dev_dbg(dev->dev, "tssi dc:%04hx db:%04hx hvga:%d\n",
		tssi_m_dc, tssi_db, hvga);

	अगर (dev->chandef.chan->hw_value < 5)
		tssi_offset = dev->ee->tssi_data.offset[0];
	अन्यथा अगर (dev->chandef.chan->hw_value < 9)
		tssi_offset = dev->ee->tssi_data.offset[1];
	अन्यथा
		tssi_offset = dev->ee->tssi_data.offset[2];

	अगर (hvga)
		tssi_db -= dev->tssi_init_hvga_offset_db;

	curr_pwr = tssi_db * dev->ee->tssi_data.slope + (tssi_offset << 9);
	dअगरf_pwr = params.trgt_घातer - curr_pwr;
	dev_dbg(dev->dev, "Power curr:%08x diff:%08x\n", curr_pwr, dअगरf_pwr);

	अगर (params.tssi0 > 126 && dअगरf_pwr > 0) अणु
		dev_err(dev->dev, "Error: TSSI upper saturation\n");
		dअगरf_pwr = 0;
	पूर्ण
	अगर (params.tssi0 - tssi_init < 1 && dअगरf_pwr < 0) अणु
		dev_err(dev->dev, "Error: TSSI lower saturation\n");
		dअगरf_pwr = 0;
	पूर्ण

	अगर ((dev->prev_pwr_dअगरf ^ dअगरf_pwr) < 0 && असल(dअगरf_pwr) < 4096 &&
	    (असल(dअगरf_pwr) > असल(dev->prev_pwr_dअगरf) ||
	     (dअगरf_pwr > 0 && dअगरf_pwr == -dev->prev_pwr_dअगरf)))
		dअगरf_pwr = 0;
	अन्यथा
		dev->prev_pwr_dअगरf = dअगरf_pwr;

	dअगरf_pwr += (dअगरf_pwr > 0) ? 2048 : -2048;
	dअगरf_pwr /= 4096;

	dev_dbg(dev->dev, "final diff: %08x\n", dअगरf_pwr);

	val = mt7601u_rr(dev, MT_TX_ALC_CFG_1);
	curr_pwr = s6_to_पूर्णांक(FIELD_GET(MT_TX_ALC_CFG_1_TEMP_COMP, val));
	dअगरf_pwr += curr_pwr;
	val = (val & ~MT_TX_ALC_CFG_1_TEMP_COMP) | पूर्णांक_to_s6(dअगरf_pwr);
	mt7601u_wr(dev, MT_TX_ALC_CFG_1, val);

	वापस mt7601u_mcu_tssi_पढ़ो_kick(dev, hvga);
पूर्ण

अटल u8 mt7601u_agc_शेष(काष्ठा mt7601u_dev *dev)
अणु
	वापस (dev->ee->lna_gain - 8) * 2 + 0x34;
पूर्ण

अटल व्योम mt7601u_agc_reset(काष्ठा mt7601u_dev *dev)
अणु
	u8 agc = mt7601u_agc_शेष(dev);

	mt7601u_bbp_wr(dev, 66,	agc);
पूर्ण

व्योम mt7601u_agc_save(काष्ठा mt7601u_dev *dev)
अणु
	dev->agc_save = mt7601u_bbp_rr(dev, 66);
पूर्ण

व्योम mt7601u_agc_restore(काष्ठा mt7601u_dev *dev)
अणु
	mt7601u_bbp_wr(dev, 66, dev->agc_save);
पूर्ण

अटल व्योम mt7601u_agc_tune(काष्ठा mt7601u_dev *dev)
अणु
	u8 val = mt7601u_agc_शेष(dev);
	दीर्घ avg_rssi;

	अगर (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		वापस;

	/* Note: only in STA mode and not करोzing; perhaps करो this only अगर
	 *	 there is enough rssi updates since last run?
	 *	 Rssi updates are only on beacons and U2M so should work...
	 */
	spin_lock_bh(&dev->con_mon_lock);
	avg_rssi = ewma_rssi_पढ़ो(&dev->avg_rssi);
	spin_unlock_bh(&dev->con_mon_lock);
	अगर (avg_rssi == 0)
		वापस;

	avg_rssi = -avg_rssi;
	अगर (avg_rssi <= -70)
		val -= 0x20;
	अन्यथा अगर (avg_rssi <= -60)
		val -= 0x10;

	अगर (val != mt7601u_bbp_rr(dev, 66))
		mt7601u_bbp_wr(dev, 66, val);

	/* TODO: also अगर lost a lot of beacons try resetting
	 *       (see RTMPSetAGCInitValue() call in mlme.c).
	 */
पूर्ण

अटल व्योम mt7601u_phy_calibrate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7601u_dev *dev = container_of(work, काष्ठा mt7601u_dev,
					    cal_work.work);

	mt7601u_agc_tune(dev);
	mt7601u_tssi_cal(dev);
	/* If TSSI calibration was run it alपढ़ोy updated temperature. */
	अगर (!dev->ee->tssi_enabled)
		dev->raw_temp = mt7601u_पढ़ो_temp(dev);
	mt7601u_temp_comp(dev, true); /* TODO: find right value क्रम @on */

	ieee80211_queue_delayed_work(dev->hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
पूर्ण

अटल अचिन्हित दीर्घ
__mt7601u_phy_freq_cal(काष्ठा mt7601u_dev *dev, s8 last_offset, u8 phy_mode)
अणु
	u8 activate_threshold, deactivate_threshold;

	trace_freq_cal_offset(dev, phy_mode, last_offset);

	/* No beacons received - reschedule soon */
	अगर (last_offset == MT_FREQ_OFFSET_INVALID)
		वापस MT_FREQ_CAL_ADJ_INTERVAL;

	चयन (phy_mode) अणु
	हाल MT_PHY_TYPE_CCK:
		activate_threshold = 19;
		deactivate_threshold = 5;
		अवरोध;
	हाल MT_PHY_TYPE_OFDM:
		activate_threshold = 102;
		deactivate_threshold = 32;
		अवरोध;
	हाल MT_PHY_TYPE_HT:
	हाल MT_PHY_TYPE_HT_GF:
		activate_threshold = 82;
		deactivate_threshold = 20;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस MT_FREQ_CAL_CHECK_INTERVAL;
	पूर्ण

	अगर (असल(last_offset) >= activate_threshold)
		dev->freq_cal.adjusting = true;
	अन्यथा अगर (असल(last_offset) <= deactivate_threshold)
		dev->freq_cal.adjusting = false;

	अगर (!dev->freq_cal.adjusting)
		वापस MT_FREQ_CAL_CHECK_INTERVAL;

	अगर (last_offset > deactivate_threshold) अणु
		अगर (dev->freq_cal.freq > 0)
			dev->freq_cal.freq--;
		अन्यथा
			dev->freq_cal.adjusting = false;
	पूर्ण अन्यथा अगर (last_offset < -deactivate_threshold) अणु
		अगर (dev->freq_cal.freq < 0xbf)
			dev->freq_cal.freq++;
		अन्यथा
			dev->freq_cal.adjusting = false;
	पूर्ण

	trace_freq_cal_adjust(dev, dev->freq_cal.freq);
	mt7601u_rf_wr(dev, 0, 12, dev->freq_cal.freq);
	mt7601u_vco_cal(dev);

	वापस dev->freq_cal.adjusting ? MT_FREQ_CAL_ADJ_INTERVAL :
					 MT_FREQ_CAL_CHECK_INTERVAL;
पूर्ण

अटल व्योम mt7601u_phy_freq_cal(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt7601u_dev *dev = container_of(work, काष्ठा mt7601u_dev,
					       freq_cal.work.work);
	s8 last_offset;
	u8 phy_mode;
	अचिन्हित दीर्घ delay;

	spin_lock_bh(&dev->con_mon_lock);
	last_offset = dev->bcn_freq_off;
	phy_mode = dev->bcn_phy_mode;
	spin_unlock_bh(&dev->con_mon_lock);

	delay = __mt7601u_phy_freq_cal(dev, last_offset, phy_mode);
	ieee80211_queue_delayed_work(dev->hw, &dev->freq_cal.work, delay);

	spin_lock_bh(&dev->con_mon_lock);
	dev->bcn_freq_off = MT_FREQ_OFFSET_INVALID;
	spin_unlock_bh(&dev->con_mon_lock);
पूर्ण

व्योम mt7601u_phy_con_cal_onoff(काष्ठा mt7601u_dev *dev,
			       काष्ठा ieee80211_bss_conf *info)
अणु
	अगर (!info->assoc)
		cancel_delayed_work_sync(&dev->freq_cal.work);

	/* Start/stop collecting beacon data */
	spin_lock_bh(&dev->con_mon_lock);
	ether_addr_copy(dev->ap_bssid, info->bssid);
	ewma_rssi_init(&dev->avg_rssi);
	dev->bcn_freq_off = MT_FREQ_OFFSET_INVALID;
	spin_unlock_bh(&dev->con_mon_lock);

	dev->freq_cal.freq = dev->ee->rf_freq_off;
	dev->freq_cal.enabled = info->assoc;
	dev->freq_cal.adjusting = false;

	अगर (info->assoc)
		ieee80211_queue_delayed_work(dev->hw, &dev->freq_cal.work,
					     MT_FREQ_CAL_INIT_DELAY);
पूर्ण

अटल पूर्णांक mt7601u_init_cal(काष्ठा mt7601u_dev *dev)
अणु
	u32 mac_ctrl;
	पूर्णांक ret;

	dev->raw_temp = mt7601u_पढ़ो_bootup_temp(dev);
	dev->curr_temp = (dev->raw_temp - dev->ee->ref_temp) *
		MT_EE_TEMPERATURE_SLOPE;
	dev->dpd_temp = dev->curr_temp;

	mac_ctrl = mt7601u_rr(dev, MT_MAC_SYS_CTRL);

	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_R, 0);
	अगर (ret)
		वापस ret;

	ret = mt7601u_rf_rr(dev, 0, 4);
	अगर (ret < 0)
		वापस ret;
	ret |= 0x80;
	ret = mt7601u_rf_wr(dev, 0, 4, ret);
	अगर (ret)
		वापस ret;
	msleep(2);

	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_TXDCOC, 0);
	अगर (ret)
		वापस ret;

	mt7601u_rxdc_cal(dev);

	ret = mt7601u_set_bw_filter(dev, true);
	अगर (ret)
		वापस ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_LOFT, 0);
	अगर (ret)
		वापस ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_TXIQ, 0);
	अगर (ret)
		वापस ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_RXIQ, 0);
	अगर (ret)
		वापस ret;
	ret = mt7601u_mcu_calibrate(dev, MCU_CAL_DPD, dev->dpd_temp);
	अगर (ret)
		वापस ret;

	mt7601u_rxdc_cal(dev);

	mt7601u_tssi_dc_gain_cal(dev);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL, mac_ctrl);

	mt7601u_temp_comp(dev, true);

	वापस 0;
पूर्ण

पूर्णांक mt7601u_bbp_set_bw(काष्ठा mt7601u_dev *dev, पूर्णांक bw)
अणु
	u32 val, old;

	अगर (bw == dev->bw) अणु
		/* Venकरोr driver करोes the rmc even when no change is needed. */
		mt7601u_bbp_rmc(dev, 4, 0x18, bw == MT_BW_20 ? 0 : 0x10);

		वापस 0;
	पूर्ण
	dev->bw = bw;

	/* Stop MAC क्रम the समय of bw change */
	old = mt7601u_rr(dev, MT_MAC_SYS_CTRL);
	val = old & ~(MT_MAC_SYS_CTRL_ENABLE_TX | MT_MAC_SYS_CTRL_ENABLE_RX);
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, val);
	mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_TX | MT_MAC_STATUS_RX,
		  0, 500000);

	mt7601u_bbp_rmc(dev, 4, 0x18, bw == MT_BW_20 ? 0 : 0x10);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL, old);

	वापस mt7601u_load_bbp_temp_table_bw(dev);
पूर्ण

/**
 * mt7601u_set_rx_path - set rx path in BBP
 * @dev:	poपूर्णांकer to adapter काष्ठाure
 * @path:	rx path to set values are 0-based
 */
व्योम mt7601u_set_rx_path(काष्ठा mt7601u_dev *dev, u8 path)
अणु
	mt7601u_bbp_rmw(dev, 3, 0x18, path << 3);
पूर्ण

/**
 * mt7601u_set_tx_dac - set which tx DAC to use
 * @dev:	poपूर्णांकer to adapter काष्ठाure
 * @dac:	DAC index, values are 0-based
 */
व्योम mt7601u_set_tx_dac(काष्ठा mt7601u_dev *dev, u8 dac)
अणु
	mt7601u_bbp_rmc(dev, 1, 0x18, dac << 3);
पूर्ण

पूर्णांक mt7601u_phy_init(काष्ठा mt7601u_dev *dev)
अणु
	पूर्णांक ret;

	dev->rf_pa_mode[0] = mt7601u_rr(dev, MT_RF_PA_MODE_CFG0);
	dev->rf_pa_mode[1] = mt7601u_rr(dev, MT_RF_PA_MODE_CFG1);

	ret = mt7601u_rf_wr(dev, 0, 12, dev->ee->rf_freq_off);
	अगर (ret)
		वापस ret;
	ret = mt7601u_ग_लिखो_reg_pairs(dev, 0, rf_central,
				      ARRAY_SIZE(rf_central));
	अगर (ret)
		वापस ret;
	ret = mt7601u_ग_लिखो_reg_pairs(dev, 0, rf_channel,
				      ARRAY_SIZE(rf_channel));
	अगर (ret)
		वापस ret;
	ret = mt7601u_ग_लिखो_reg_pairs(dev, 0, rf_vga, ARRAY_SIZE(rf_vga));
	अगर (ret)
		वापस ret;

	ret = mt7601u_init_cal(dev);
	अगर (ret)
		वापस ret;

	dev->prev_pwr_dअगरf = 100;

	INIT_DELAYED_WORK(&dev->cal_work, mt7601u_phy_calibrate);
	INIT_DELAYED_WORK(&dev->freq_cal.work, mt7601u_phy_freq_cal);

	वापस 0;
पूर्ण
