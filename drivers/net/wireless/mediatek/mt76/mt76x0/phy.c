<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/etherdevice.h>

#समावेश "mt76x0.h"
#समावेश "mcu.h"
#समावेश "eeprom.h"
#समावेश "phy.h"
#समावेश "initvals.h"
#समावेश "initvals_phy.h"
#समावेश "../mt76x02_phy.h"

अटल पूर्णांक
mt76x0_rf_csr_wr(काष्ठा mt76x02_dev *dev, u32 offset, u8 value)
अणु
	पूर्णांक ret = 0;
	u8 bank, reg;

	अगर (test_bit(MT76_REMOVED, &dev->mphy.state))
		वापस -ENODEV;

	bank = MT_RF_BANK(offset);
	reg = MT_RF_REG(offset);

	अगर (WARN_ON_ONCE(reg > 127) || WARN_ON_ONCE(bank > 8))
		वापस -EINVAL;

	mutex_lock(&dev->phy_mutex);

	अगर (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100)) अणु
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	mt76_wr(dev, MT_RF_CSR_CFG,
		FIELD_PREP(MT_RF_CSR_CFG_DATA, value) |
		FIELD_PREP(MT_RF_CSR_CFG_REG_BANK, bank) |
		FIELD_PREP(MT_RF_CSR_CFG_REG_ID, reg) |
		MT_RF_CSR_CFG_WR |
		MT_RF_CSR_CFG_KICK);

out:
	mutex_unlock(&dev->phy_mutex);

	अगर (ret < 0)
		dev_err(dev->mt76.dev, "Error: RF write %d:%d failed:%d!!\n",
			bank, reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mt76x0_rf_csr_rr(काष्ठा mt76x02_dev *dev, u32 offset)
अणु
	पूर्णांक ret = -ETIMEDOUT;
	u32 val;
	u8 bank, reg;

	अगर (test_bit(MT76_REMOVED, &dev->mphy.state))
		वापस -ENODEV;

	bank = MT_RF_BANK(offset);
	reg = MT_RF_REG(offset);

	अगर (WARN_ON_ONCE(reg > 127) || WARN_ON_ONCE(bank > 8))
		वापस -EINVAL;

	mutex_lock(&dev->phy_mutex);

	अगर (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100))
		जाओ out;

	mt76_wr(dev, MT_RF_CSR_CFG,
		FIELD_PREP(MT_RF_CSR_CFG_REG_BANK, bank) |
		FIELD_PREP(MT_RF_CSR_CFG_REG_ID, reg) |
		MT_RF_CSR_CFG_KICK);

	अगर (!mt76_poll(dev, MT_RF_CSR_CFG, MT_RF_CSR_CFG_KICK, 0, 100))
		जाओ out;

	val = mt76_rr(dev, MT_RF_CSR_CFG);
	अगर (FIELD_GET(MT_RF_CSR_CFG_REG_ID, val) == reg &&
	    FIELD_GET(MT_RF_CSR_CFG_REG_BANK, val) == bank)
		ret = FIELD_GET(MT_RF_CSR_CFG_DATA, val);

out:
	mutex_unlock(&dev->phy_mutex);

	अगर (ret < 0)
		dev_err(dev->mt76.dev, "Error: RF read %d:%d failed:%d!!\n",
			bank, reg, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक
mt76x0_rf_wr(काष्ठा mt76x02_dev *dev, u32 offset, u8 val)
अणु
	अगर (mt76_is_usb(&dev->mt76)) अणु
		काष्ठा mt76_reg_pair pair = अणु
			.reg = offset,
			.value = val,
		पूर्ण;

		WARN_ON_ONCE(!test_bit(MT76_STATE_MCU_RUNNING,
				       &dev->mphy.state));
		वापस mt76_wr_rp(dev, MT_MCU_MEMMAP_RF, &pair, 1);
	पूर्ण अन्यथा अणु
		वापस mt76x0_rf_csr_wr(dev, offset, val);
	पूर्ण
पूर्ण

अटल पूर्णांक mt76x0_rf_rr(काष्ठा mt76x02_dev *dev, u32 offset)
अणु
	पूर्णांक ret;
	u32 val;

	अगर (mt76_is_usb(&dev->mt76)) अणु
		काष्ठा mt76_reg_pair pair = अणु
			.reg = offset,
		पूर्ण;

		WARN_ON_ONCE(!test_bit(MT76_STATE_MCU_RUNNING,
				       &dev->mphy.state));
		ret = mt76_rd_rp(dev, MT_MCU_MEMMAP_RF, &pair, 1);
		val = pair.value;
	पूर्ण अन्यथा अणु
		ret = val = mt76x0_rf_csr_rr(dev, offset);
	पूर्ण

	वापस (ret < 0) ? ret : val;
पूर्ण

अटल पूर्णांक
mt76x0_rf_rmw(काष्ठा mt76x02_dev *dev, u32 offset, u8 mask, u8 val)
अणु
	पूर्णांक ret;

	ret = mt76x0_rf_rr(dev, offset);
	अगर (ret < 0)
		वापस ret;

	val |= ret & ~mask;

	ret = mt76x0_rf_wr(dev, offset, val);
	वापस ret ? ret : val;
पूर्ण

अटल पूर्णांक
mt76x0_rf_set(काष्ठा mt76x02_dev *dev, u32 offset, u8 val)
अणु
	वापस mt76x0_rf_rmw(dev, offset, 0, val);
पूर्ण

अटल पूर्णांक
mt76x0_rf_clear(काष्ठा mt76x02_dev *dev, u32 offset, u8 mask)
अणु
	वापस mt76x0_rf_rmw(dev, offset, mask, 0);
पूर्ण

अटल व्योम
mt76x0_phy_rf_csr_wr_rp(काष्ठा mt76x02_dev *dev,
			स्थिर काष्ठा mt76_reg_pair *data,
			पूर्णांक n)
अणु
	जबतक (n-- > 0) अणु
		mt76x0_rf_csr_wr(dev, data->reg, data->value);
		data++;
	पूर्ण
पूर्ण

#घोषणा RF_RANDOM_WRITE(dev, tab) करो अणु					\
	अगर (mt76_is_mmio(&dev->mt76))					\
		mt76x0_phy_rf_csr_wr_rp(dev, tab, ARRAY_SIZE(tab));	\
	अन्यथा								\
		mt76_wr_rp(dev, MT_MCU_MEMMAP_RF, tab, ARRAY_SIZE(tab));\
पूर्ण जबतक (0)

पूर्णांक mt76x0_phy_रुको_bbp_पढ़ोy(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i = 20;
	u32 val;

	करो अणु
		val = mt76_rr(dev, MT_BBP(CORE, 0));
		अगर (val && ~val)
			अवरोध;
	पूर्ण जबतक (--i);

	अगर (!i) अणु
		dev_err(dev->mt76.dev, "Error: BBP is not ready\n");
		वापस -EIO;
	पूर्ण

	dev_dbg(dev->mt76.dev, "BBP version %08x\n", val);
	वापस 0;
पूर्ण

अटल व्योम
mt76x0_phy_set_band(काष्ठा mt76x02_dev *dev, क्रमागत nl80211_band band)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		RF_RANDOM_WRITE(dev, mt76x0_rf_2g_channel_0_tab);

		mt76x0_rf_wr(dev, MT_RF(5, 0), 0x45);
		mt76x0_rf_wr(dev, MT_RF(6, 0), 0x44);

		mt76_wr(dev, MT_TX_ALC_VGA3, 0x00050007);
		mt76_wr(dev, MT_TX0_RF_GAIN_CORR, 0x003E0002);
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		RF_RANDOM_WRITE(dev, mt76x0_rf_5g_channel_0_tab);

		mt76x0_rf_wr(dev, MT_RF(5, 0), 0x44);
		mt76x0_rf_wr(dev, MT_RF(6, 0), 0x45);

		mt76_wr(dev, MT_TX_ALC_VGA3, 0x00000005);
		mt76_wr(dev, MT_TX0_RF_GAIN_CORR, 0x01010102);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mt76x0_phy_set_chan_rf_params(काष्ठा mt76x02_dev *dev, u8 channel,
			      u16 rf_bw_band)
अणु
	स्थिर काष्ठा mt76x0_freq_item *freq_item;
	u16 rf_band = rf_bw_band & 0xff00;
	u16 rf_bw = rf_bw_band & 0x00ff;
	क्रमागत nl80211_band band;
	bool b_sdm = false;
	u32 mac_reg;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_sdm_channel); i++) अणु
		अगर (channel == mt76x0_sdm_channel[i]) अणु
			b_sdm = true;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_frequency_plan); i++) अणु
		अगर (channel == mt76x0_frequency_plan[i].channel) अणु
			rf_band = mt76x0_frequency_plan[i].band;

			अगर (b_sdm)
				freq_item = &mt76x0_sdm_frequency_plan[i];
			अन्यथा
				freq_item = &mt76x0_frequency_plan[i];

			mt76x0_rf_wr(dev, MT_RF(0, 37), freq_item->pllR37);
			mt76x0_rf_wr(dev, MT_RF(0, 36), freq_item->pllR36);
			mt76x0_rf_wr(dev, MT_RF(0, 35), freq_item->pllR35);
			mt76x0_rf_wr(dev, MT_RF(0, 34), freq_item->pllR34);
			mt76x0_rf_wr(dev, MT_RF(0, 33), freq_item->pllR33);

			mt76x0_rf_rmw(dev, MT_RF(0, 32), 0xe0,
				      freq_item->pllR32_b7b5);

			/* R32<4:0> pll_den: (Denomina - 8) */
			mt76x0_rf_rmw(dev, MT_RF(0, 32), MT_RF_PLL_DEN_MASK,
				      freq_item->pllR32_b4b0);

			/* R31<7:5> */
			mt76x0_rf_rmw(dev, MT_RF(0, 31), 0xe0,
				      freq_item->pllR31_b7b5);

			/* R31<4:0> pll_k(Nominator) */
			mt76x0_rf_rmw(dev, MT_RF(0, 31), MT_RF_PLL_K_MASK,
				      freq_item->pllR31_b4b0);

			/* R30<7> sdm_reset_n */
			अगर (b_sdm) अणु
				mt76x0_rf_clear(dev, MT_RF(0, 30),
						MT_RF_SDM_RESET_MASK);
				mt76x0_rf_set(dev, MT_RF(0, 30),
					      MT_RF_SDM_RESET_MASK);
			पूर्ण अन्यथा अणु
				mt76x0_rf_rmw(dev, MT_RF(0, 30),
					      MT_RF_SDM_RESET_MASK,
					      freq_item->pllR30_b7);
			पूर्ण

			/* R30<6:2> sdmmash_prbs,sin */
			mt76x0_rf_rmw(dev, MT_RF(0, 30),
				      MT_RF_SDM_MASH_PRBS_MASK,
				      freq_item->pllR30_b6b2);

			/* R30<1> sdm_bp */
			mt76x0_rf_rmw(dev, MT_RF(0, 30), MT_RF_SDM_BP_MASK,
				      freq_item->pllR30_b1 << 1);

			/* R30<0> R29<7:0> (hex) pll_n */
			mt76x0_rf_wr(dev, MT_RF(0, 29),
				     freq_item->pll_n & 0xff);

			mt76x0_rf_rmw(dev, MT_RF(0, 30), 0x1,
				      (freq_item->pll_n >> 8) & 0x1);

			/* R28<7:6> isi_iso */
			mt76x0_rf_rmw(dev, MT_RF(0, 28), MT_RF_ISI_ISO_MASK,
				      freq_item->pllR28_b7b6);

			/* R28<5:4> pfd_dly */
			mt76x0_rf_rmw(dev, MT_RF(0, 28), MT_RF_PFD_DLY_MASK,
				      freq_item->pllR28_b5b4);

			/* R28<3:2> clksel option */
			mt76x0_rf_rmw(dev, MT_RF(0, 28), MT_RF_CLK_SEL_MASK,
				      freq_item->pllR28_b3b2);

			/* R28<1:0> R27<7:0> R26<7:0> (hex) sdm_k */
			mt76x0_rf_wr(dev, MT_RF(0, 26),
				     freq_item->pll_sdm_k & 0xff);
			mt76x0_rf_wr(dev, MT_RF(0, 27),
				     (freq_item->pll_sdm_k >> 8) & 0xff);

			mt76x0_rf_rmw(dev, MT_RF(0, 28), 0x3,
				      (freq_item->pll_sdm_k >> 16) & 0x3);

			/* R24<1:0> xo_भाग */
			mt76x0_rf_rmw(dev, MT_RF(0, 24), MT_RF_XO_DIV_MASK,
				      freq_item->pllR24_b1b0);

			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_rf_bw_चयन_tab); i++) अणु
		अगर (rf_bw == mt76x0_rf_bw_चयन_tab[i].bw_band) अणु
			mt76x0_rf_wr(dev,
				     mt76x0_rf_bw_चयन_tab[i].rf_bank_reg,
				     mt76x0_rf_bw_चयन_tab[i].value);
		पूर्ण अन्यथा अगर ((rf_bw == (mt76x0_rf_bw_चयन_tab[i].bw_band & 0xFF)) &&
			   (rf_band & mt76x0_rf_bw_चयन_tab[i].bw_band)) अणु
			mt76x0_rf_wr(dev,
				     mt76x0_rf_bw_चयन_tab[i].rf_bank_reg,
				     mt76x0_rf_bw_चयन_tab[i].value);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_rf_band_चयन_tab); i++) अणु
		अगर (mt76x0_rf_band_चयन_tab[i].bw_band & rf_band) अणु
			mt76x0_rf_wr(dev,
				     mt76x0_rf_band_चयन_tab[i].rf_bank_reg,
				     mt76x0_rf_band_चयन_tab[i].value);
		पूर्ण
	पूर्ण

	mt76_clear(dev, MT_RF_MISC, 0xc);

	band = (rf_band & RF_G_BAND) ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	अगर (mt76x02_ext_pa_enabled(dev, band)) अणु
		/* MT_RF_MISC (offset: 0x0518)
		 * [2]1'b1: enable बाह्यal A band PA
		 *    1'b0: disable बाह्यal A band PA
		 * [3]1'b1: enable बाह्यal G band PA
		 *    1'b0: disable बाह्यal G band PA
		 */
		अगर (rf_band & RF_A_BAND)
			mt76_set(dev, MT_RF_MISC, BIT(2));
		अन्यथा
			mt76_set(dev, MT_RF_MISC, BIT(3));

		/* External PA */
		क्रम (i = 0; i < ARRAY_SIZE(mt76x0_rf_ext_pa_tab); i++)
			अगर (mt76x0_rf_ext_pa_tab[i].bw_band & rf_band)
				mt76x0_rf_wr(dev,
					mt76x0_rf_ext_pa_tab[i].rf_bank_reg,
					mt76x0_rf_ext_pa_tab[i].value);
	पूर्ण

	अगर (rf_band & RF_G_BAND) अणु
		mt76_wr(dev, MT_TX0_RF_GAIN_ATTEN, 0x63707400);
		/* Set Atten mode = 2 For G band, Disable Tx Inc dcoc. */
		mac_reg = mt76_rr(dev, MT_TX_ALC_CFG_1);
		mac_reg &= 0x896400FF;
		mt76_wr(dev, MT_TX_ALC_CFG_1, mac_reg);
	पूर्ण अन्यथा अणु
		mt76_wr(dev, MT_TX0_RF_GAIN_ATTEN, 0x686A7800);
		/* Set Atten mode = 0
		 * For Ext A band, Disable Tx Inc dcoc Cal.
		 */
		mac_reg = mt76_rr(dev, MT_TX_ALC_CFG_1);
		mac_reg &= 0x890400FF;
		mt76_wr(dev, MT_TX_ALC_CFG_1, mac_reg);
	पूर्ण
पूर्ण

अटल व्योम
mt76x0_phy_set_chan_bbp_params(काष्ठा mt76x02_dev *dev, u16 rf_bw_band)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_bbp_चयन_tab); i++) अणु
		स्थिर काष्ठा mt76x0_bbp_चयन_item *item = &mt76x0_bbp_चयन_tab[i];
		स्थिर काष्ठा mt76_reg_pair *pair = &item->reg_pair;

		अगर ((rf_bw_band & item->bw_band) != rf_bw_band)
			जारी;

		अगर (pair->reg == MT_BBP(AGC, 8)) अणु
			u32 val = pair->value;
			u8 gain;

			gain = FIELD_GET(MT_BBP_AGC_GAIN, val);
			gain -= dev->cal.rx.lna_gain * 2;
			val &= ~MT_BBP_AGC_GAIN;
			val |= FIELD_PREP(MT_BBP_AGC_GAIN, gain);
			mt76_wr(dev, pair->reg, val);
		पूर्ण अन्यथा अणु
			mt76_wr(dev, pair->reg, pair->value);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mt76x0_phy_ant_select(काष्ठा mt76x02_dev *dev)
अणु
	u16 ee_ant = mt76x02_eeprom_get(dev, MT_EE_ANTENNA);
	u16 ee_cfg1 = mt76x02_eeprom_get(dev, MT_EE_CFG1_INIT);
	u16 nic_conf2 = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_2);
	u32 wlan, coex3;
	bool ant_भाग;

	wlan = mt76_rr(dev, MT_WLAN_FUN_CTRL);
	coex3 = mt76_rr(dev, MT_COEXCFG3);

	ee_ant &= ~(BIT(14) | BIT(12));
	wlan  &= ~(BIT(6) | BIT(5));
	coex3 &= ~GENMASK(5, 2);

	अगर (ee_ant & MT_EE_ANTENNA_DUAL) अणु
		/* dual antenna mode */
		ant_भाग = !(nic_conf2 & MT_EE_NIC_CONF_2_ANT_OPT) &&
			  (nic_conf2 & MT_EE_NIC_CONF_2_ANT_DIV);
		अगर (ant_भाग)
			ee_ant |= BIT(12);
		अन्यथा
			coex3 |= BIT(4);
		coex3 |= BIT(3);
		अगर (dev->mphy.cap.has_2ghz)
			wlan |= BIT(6);
	पूर्ण अन्यथा अणु
		/* sigle antenna mode */
		अगर (dev->mphy.cap.has_5ghz) अणु
			coex3 |= BIT(3) | BIT(4);
		पूर्ण अन्यथा अणु
			wlan |= BIT(6);
			coex3 |= BIT(1);
		पूर्ण
	पूर्ण

	अगर (is_mt7630(dev))
		ee_ant |= BIT(14) | BIT(11);

	mt76_wr(dev, MT_WLAN_FUN_CTRL, wlan);
	mt76_rmw(dev, MT_CMB_CTRL, GENMASK(15, 0), ee_ant);
	mt76_rmw(dev, MT_CSR_EE_CFG1, GENMASK(15, 0), ee_cfg1);
	mt76_clear(dev, MT_COEXCFG0, BIT(2));
	mt76_wr(dev, MT_COEXCFG3, coex3);
पूर्ण

अटल व्योम
mt76x0_phy_bbp_set_bw(काष्ठा mt76x02_dev *dev, क्रमागत nl80211_chan_width width)
अणु
	क्रमागत अणु BW_20 = 0, BW_40 = 1, BW_80 = 2, BW_10 = 4पूर्ण;
	पूर्णांक bw;

	चयन (width) अणु
	शेष:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		bw = BW_20;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		bw = BW_40;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		bw = BW_80;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		bw = BW_10;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
	हाल NL80211_CHAN_WIDTH_5:
		/* TODO error */
		वापस;
	पूर्ण

	mt76x02_mcu_function_select(dev, BW_SETTING, bw);
पूर्ण

अटल व्योम mt76x0_phy_tssi_dc_calibrate(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	u32 val;

	अगर (chan->band == NL80211_BAND_5GHZ)
		mt76x0_rf_clear(dev, MT_RF(0, 67), 0xf);

	/* bypass ADDA control */
	mt76_wr(dev, MT_RF_SETTING_0, 0x60002237);
	mt76_wr(dev, MT_RF_BYPASS_0, 0xffffffff);

	/* bbp sw reset */
	mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
	usleep_range(500, 1000);
	mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));

	val = (chan->band == NL80211_BAND_5GHZ) ? 0x80055 : 0x80050;
	mt76_wr(dev, MT_BBP(CORE, 34), val);

	/* enable TX with DAC0 input */
	mt76_wr(dev, MT_BBP(TXBE, 6), BIT(31));

	mt76_poll_msec(dev, MT_BBP(CORE, 34), BIT(4), 0, 200);
	dev->cal.tssi_dc = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	/* stop bypass ADDA */
	mt76_wr(dev, MT_RF_BYPASS_0, 0);
	/* stop TX */
	mt76_wr(dev, MT_BBP(TXBE, 6), 0);
	/* bbp sw reset */
	mt76_set(dev, MT_BBP(CORE, 4), BIT(0));
	usleep_range(500, 1000);
	mt76_clear(dev, MT_BBP(CORE, 4), BIT(0));

	अगर (chan->band == NL80211_BAND_5GHZ)
		mt76x0_rf_rmw(dev, MT_RF(0, 67), 0xf, 0x4);
पूर्ण

अटल पूर्णांक
mt76x0_phy_tssi_adc_calibrate(काष्ठा mt76x02_dev *dev, s16 *ltssi,
			      u8 *info)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	u32 val;

	val = (chan->band == NL80211_BAND_5GHZ) ? 0x80055 : 0x80050;
	mt76_wr(dev, MT_BBP(CORE, 34), val);

	अगर (!mt76_poll_msec(dev, MT_BBP(CORE, 34), BIT(4), 0, 200)) अणु
		mt76_clear(dev, MT_BBP(CORE, 34), BIT(4));
		वापस -ETIMEDOUT;
	पूर्ण

	*ltssi = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;
	अगर (chan->band == NL80211_BAND_5GHZ)
		*ltssi += 128;

	/* set packet info#1 mode */
	mt76_wr(dev, MT_BBP(CORE, 34), 0x80041);
	info[0] = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	/* set packet info#2 mode */
	mt76_wr(dev, MT_BBP(CORE, 34), 0x80042);
	info[1] = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	/* set packet info#3 mode */
	mt76_wr(dev, MT_BBP(CORE, 34), 0x80043);
	info[2] = mt76_rr(dev, MT_BBP(CORE, 35)) & 0xff;

	वापस 0;
पूर्ण

अटल u8 mt76x0_phy_get_rf_pa_mode(काष्ठा mt76x02_dev *dev,
				    पूर्णांक index, u8 tx_rate)
अणु
	u32 val, reg;

	reg = (index == 1) ? MT_RF_PA_MODE_CFG1 : MT_RF_PA_MODE_CFG0;
	val = mt76_rr(dev, reg);
	वापस (val & (3 << (tx_rate * 2))) >> (tx_rate * 2);
पूर्ण

अटल पूर्णांक
mt76x0_phy_get_target_घातer(काष्ठा mt76x02_dev *dev, u8 tx_mode,
			    u8 *info, s8 *target_घातer,
			    s8 *target_pa_घातer)
अणु
	u8 tx_rate, cur_घातer;

	cur_घातer = mt76_rr(dev, MT_TX_ALC_CFG_0) & MT_TX_ALC_CFG_0_CH_INIT_0;
	चयन (tx_mode) अणु
	हाल 0:
		/* cck rates */
		tx_rate = (info[0] & 0x60) >> 5;
		अगर (tx_rate > 3)
			वापस -EINVAL;

		*target_घातer = cur_घातer + dev->mt76.rate_घातer.cck[tx_rate];
		*target_pa_घातer = mt76x0_phy_get_rf_pa_mode(dev, 0, tx_rate);
		अवरोध;
	हाल 1: अणु
		u8 index;

		/* ofdm rates */
		tx_rate = (info[0] & 0xf0) >> 4;
		चयन (tx_rate) अणु
		हाल 0xb:
			index = 0;
			अवरोध;
		हाल 0xf:
			index = 1;
			अवरोध;
		हाल 0xa:
			index = 2;
			अवरोध;
		हाल 0xe:
			index = 3;
			अवरोध;
		हाल 0x9:
			index = 4;
			अवरोध;
		हाल 0xd:
			index = 5;
			अवरोध;
		हाल 0x8:
			index = 6;
			अवरोध;
		हाल 0xc:
			index = 7;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		*target_घातer = cur_घातer + dev->mt76.rate_घातer.ofdm[index];
		*target_pa_घातer = mt76x0_phy_get_rf_pa_mode(dev, 0, index + 4);
		अवरोध;
	पूर्ण
	हाल 4:
		/* vht rates */
		tx_rate = info[1] & 0xf;
		अगर (tx_rate > 9)
			वापस -EINVAL;

		*target_घातer = cur_घातer + dev->mt76.rate_घातer.vht[tx_rate];
		*target_pa_घातer = mt76x0_phy_get_rf_pa_mode(dev, 1, tx_rate);
		अवरोध;
	शेष:
		/* ht rates */
		tx_rate = info[1] & 0x7f;
		अगर (tx_rate > 9)
			वापस -EINVAL;

		*target_घातer = cur_घातer + dev->mt76.rate_घातer.ht[tx_rate];
		*target_pa_घातer = mt76x0_phy_get_rf_pa_mode(dev, 1, tx_rate);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल s16 mt76x0_phy_lin2db(u16 val)
अणु
	u32 mantissa = val << 4;
	पूर्णांक ret, data;
	s16 exp = -4;

	जबतक (mantissa < BIT(15)) अणु
		mantissa <<= 1;
		अगर (--exp < -20)
			वापस -10000;
	पूर्ण
	जबतक (mantissa > 0xffff) अणु
		mantissa >>= 1;
		अगर (++exp > 20)
			वापस -10000;
	पूर्ण

	/* s(15,0) */
	अगर (mantissa <= 47104)
		data = mantissa + (mantissa >> 3) + (mantissa >> 4) - 38400;
	अन्यथा
		data = mantissa - (mantissa >> 3) - (mantissa >> 6) - 23040;
	data = max_t(पूर्णांक, 0, data);

	ret = ((15 + exp) << 15) + data;
	ret = (ret << 2) + (ret << 1) + (ret >> 6) + (ret >> 7);
	वापस ret >> 10;
पूर्ण

अटल पूर्णांक
mt76x0_phy_get_delta_घातer(काष्ठा mt76x02_dev *dev, u8 tx_mode,
			   s8 target_घातer, s8 target_pa_घातer,
			   s16 ltssi)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	पूर्णांक tssi_target = target_घातer << 12, tssi_slope;
	पूर्णांक tssi_offset, tssi_db, ret;
	u32 data;
	u16 val;

	अगर (chan->band == NL80211_BAND_5GHZ) अणु
		u8 bound[7];
		पूर्णांक i, err;

		err = mt76x02_eeprom_copy(dev, MT_EE_TSSI_BOUND1, bound,
					  माप(bound));
		अगर (err < 0)
			वापस err;

		क्रम (i = 0; i < ARRAY_SIZE(bound); i++) अणु
			अगर (chan->hw_value <= bound[i] || !bound[i])
				अवरोध;
		पूर्ण
		val = mt76x02_eeprom_get(dev, MT_EE_TSSI_SLOPE_5G + i * 2);

		tssi_offset = val >> 8;
		अगर ((tssi_offset >= 64 && tssi_offset <= 127) ||
		    (tssi_offset & BIT(7)))
			tssi_offset -= BIT(8);
	पूर्ण अन्यथा अणु
		val = mt76x02_eeprom_get(dev, MT_EE_TSSI_SLOPE_2G);

		tssi_offset = val >> 8;
		अगर (tssi_offset & BIT(7))
			tssi_offset -= BIT(8);
	पूर्ण
	tssi_slope = val & 0xff;

	चयन (target_pa_घातer) अणु
	हाल 1:
		अगर (chan->band == NL80211_BAND_2GHZ)
			tssi_target += 29491; /* 3.6 * 8192 */
		fallthrough;
	हाल 0:
		अवरोध;
	शेष:
		tssi_target += 4424; /* 0.54 * 8192 */
		अवरोध;
	पूर्ण

	अगर (!tx_mode) अणु
		data = mt76_rr(dev, MT_BBP(CORE, 1));
		अगर (is_mt7630(dev) && mt76_is_mmio(&dev->mt76)) अणु
			पूर्णांक offset;

			/* 2.3 * 8192 or 1.5 * 8192 */
			offset = (data & BIT(5)) ? 18841 : 12288;
			tssi_target += offset;
		पूर्ण अन्यथा अगर (data & BIT(5)) अणु
			/* 0.8 * 8192 */
			tssi_target += 6554;
		पूर्ण
	पूर्ण

	data = mt76_rr(dev, MT_BBP(TXBE, 4));
	चयन (data & 0x3) अणु
	हाल 1:
		tssi_target -= 49152; /* -6db * 8192 */
		अवरोध;
	हाल 2:
		tssi_target -= 98304; /* -12db * 8192 */
		अवरोध;
	हाल 3:
		tssi_target += 49152; /* 6db * 8192 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tssi_db = mt76x0_phy_lin2db(ltssi - dev->cal.tssi_dc) * tssi_slope;
	अगर (chan->band == NL80211_BAND_5GHZ) अणु
		tssi_db += ((tssi_offset - 50) << 10); /* offset s4.3 */
		tssi_target -= tssi_db;
		अगर (ltssi > 254 && tssi_target > 0) अणु
			/* upper saturate */
			tssi_target = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		tssi_db += (tssi_offset << 9); /* offset s3.4 */
		tssi_target -= tssi_db;
		/* upper-lower saturate */
		अगर ((ltssi > 126 && tssi_target > 0) ||
		    ((ltssi - dev->cal.tssi_dc) < 1 && tssi_target < 0)) अणु
			tssi_target = 0;
		पूर्ण
	पूर्ण

	अगर ((dev->cal.tssi_target ^ tssi_target) < 0 &&
	    dev->cal.tssi_target > -4096 && dev->cal.tssi_target < 4096 &&
	    tssi_target > -4096 && tssi_target < 4096) अणु
		अगर ((tssi_target < 0 &&
		     tssi_target + dev->cal.tssi_target > 0) ||
		    (tssi_target > 0 &&
		     tssi_target + dev->cal.tssi_target <= 0))
			tssi_target = 0;
		अन्यथा
			dev->cal.tssi_target = tssi_target;
	पूर्ण अन्यथा अणु
		dev->cal.tssi_target = tssi_target;
	पूर्ण

	/* make the compensate value to the nearest compensate code */
	अगर (tssi_target > 0)
		tssi_target += 2048;
	अन्यथा
		tssi_target -= 2048;
	tssi_target >>= 12;

	ret = mt76_get_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP);
	अगर (ret & BIT(5))
		ret -= BIT(6);
	ret += tssi_target;

	ret = min_t(पूर्णांक, 31, ret);
	वापस max_t(पूर्णांक, -32, ret);
पूर्ण

अटल व्योम mt76x0_phy_tssi_calibrate(काष्ठा mt76x02_dev *dev)
अणु
	s8 target_घातer, target_pa_घातer;
	u8 tssi_info[3], tx_mode;
	s16 ltssi;
	s8 val;

	अगर (mt76x0_phy_tssi_adc_calibrate(dev, &ltssi, tssi_info) < 0)
		वापस;

	tx_mode = tssi_info[0] & 0x7;
	अगर (mt76x0_phy_get_target_घातer(dev, tx_mode, tssi_info,
					&target_घातer, &target_pa_घातer) < 0)
		वापस;

	val = mt76x0_phy_get_delta_घातer(dev, tx_mode, target_घातer,
					 target_pa_घातer, ltssi);
	mt76_rmw_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP, val);
पूर्ण

व्योम mt76x0_phy_set_txघातer(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा mt76_rate_घातer *t = &dev->mt76.rate_घातer;
	s8 info;

	mt76x0_get_tx_घातer_per_rate(dev, dev->mphy.chandef.chan, t);
	mt76x0_get_घातer_info(dev, dev->mphy.chandef.chan, &info);

	mt76x02_add_rate_घातer_offset(t, info);
	mt76x02_limit_rate_घातer(t, dev->txघातer_conf);
	dev->mphy.txघातer_cur = mt76x02_get_max_rate_घातer(t);
	mt76x02_add_rate_घातer_offset(t, -info);

	dev->target_घातer = info;
	mt76x02_phy_set_txघातer(dev, info, info);
पूर्ण

व्योम mt76x0_phy_calibrate(काष्ठा mt76x02_dev *dev, bool घातer_on)
अणु
	काष्ठा ieee80211_channel *chan = dev->mphy.chandef.chan;
	पूर्णांक is_5ghz = (chan->band == NL80211_BAND_5GHZ) ? 1 : 0;
	u32 val, tx_alc, reg_val;

	अगर (is_mt7630(dev))
		वापस;

	अगर (घातer_on) अणु
		mt76x02_mcu_calibrate(dev, MCU_CAL_R, 0);
		mt76x02_mcu_calibrate(dev, MCU_CAL_VCO, chan->hw_value);
		usleep_range(10, 20);

		अगर (mt76x0_tssi_enabled(dev)) अणु
			mt76_wr(dev, MT_MAC_SYS_CTRL,
				MT_MAC_SYS_CTRL_ENABLE_RX);
			mt76x0_phy_tssi_dc_calibrate(dev);
			mt76_wr(dev, MT_MAC_SYS_CTRL,
				MT_MAC_SYS_CTRL_ENABLE_TX |
				MT_MAC_SYS_CTRL_ENABLE_RX);
		पूर्ण
	पूर्ण

	tx_alc = mt76_rr(dev, MT_TX_ALC_CFG_0);
	mt76_wr(dev, MT_TX_ALC_CFG_0, 0);
	usleep_range(500, 700);

	reg_val = mt76_rr(dev, MT_BBP(IBI, 9));
	mt76_wr(dev, MT_BBP(IBI, 9), 0xffffff7e);

	अगर (is_5ghz) अणु
		अगर (chan->hw_value < 100)
			val = 0x701;
		अन्यथा अगर (chan->hw_value < 140)
			val = 0x801;
		अन्यथा
			val = 0x901;
	पूर्ण अन्यथा अणु
		val = 0x600;
	पूर्ण

	mt76x02_mcu_calibrate(dev, MCU_CAL_FULL, val);
	mt76x02_mcu_calibrate(dev, MCU_CAL_LC, is_5ghz);
	usleep_range(15000, 20000);

	mt76_wr(dev, MT_BBP(IBI, 9), reg_val);
	mt76_wr(dev, MT_TX_ALC_CFG_0, tx_alc);
	mt76x02_mcu_calibrate(dev, MCU_CAL_RXDCOC, 1);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x0_phy_calibrate);

व्योम mt76x0_phy_set_channel(काष्ठा mt76x02_dev *dev,
			    काष्ठा cfg80211_chan_def *chandef)
अणु
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
	bool scan = test_bit(MT76_SCANNING, &dev->mphy.state);
	पूर्णांक ch_group_index, freq, freq1;
	u8 channel;
	u32 val;
	u16 rf_bw_band;

	freq = chandef->chan->center_freq;
	freq1 = chandef->center_freq1;
	channel = chandef->chan->hw_value;
	rf_bw_band = (channel <= 14) ? RF_G_BAND : RF_A_BAND;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		अगर (freq1 > freq)
			ch_group_index = 0;
		अन्यथा
			ch_group_index = 1;
		channel += 2 - ch_group_index * 4;
		rf_bw_band |= RF_BW_40;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		ch_group_index = (freq - freq1 + 30) / 20;
		अगर (WARN_ON(ch_group_index < 0 || ch_group_index > 3))
			ch_group_index = 0;
		channel += 6 - ch_group_index * 4;
		rf_bw_band |= RF_BW_80;
		अवरोध;
	शेष:
		ch_group_index = 0;
		rf_bw_band |= RF_BW_20;
		अवरोध;
	पूर्ण

	अगर (mt76_is_usb(&dev->mt76)) अणु
		mt76x0_phy_bbp_set_bw(dev, chandef->width);
	पूर्ण अन्यथा अणु
		अगर (chandef->width == NL80211_CHAN_WIDTH_80 ||
		    chandef->width == NL80211_CHAN_WIDTH_40)
			val = 0x201;
		अन्यथा
			val = 0x601;
		mt76_wr(dev, MT_TX_SW_CFG0, val);
	पूर्ण
	mt76x02_phy_set_bw(dev, chandef->width, ch_group_index);
	mt76x02_phy_set_band(dev, chandef->chan->band,
			     ch_group_index & 1);

	mt76_rmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_group_index]);

	mt76x0_phy_set_band(dev, chandef->chan->band);
	mt76x0_phy_set_chan_rf_params(dev, channel, rf_bw_band);

	/* set Japan Tx filter at channel 14 */
	अगर (channel == 14)
		mt76_set(dev, MT_BBP(CORE, 1), 0x20);
	अन्यथा
		mt76_clear(dev, MT_BBP(CORE, 1), 0x20);

	mt76x0_पढ़ो_rx_gain(dev);
	mt76x0_phy_set_chan_bbp_params(dev, rf_bw_band);

	/* enable vco */
	mt76x0_rf_set(dev, MT_RF(0, 4), BIT(7));
	अगर (scan)
		वापस;

	mt76x02_init_agc_gain(dev);
	mt76x0_phy_calibrate(dev, false);
	mt76x0_phy_set_txघातer(dev);

	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     MT_CALIBRATE_INTERVAL);
पूर्ण

अटल व्योम mt76x0_phy_temp_sensor(काष्ठा mt76x02_dev *dev)
अणु
	u8 rf_b7_73, rf_b0_66, rf_b0_67;
	s8 val;

	rf_b7_73 = mt76x0_rf_rr(dev, MT_RF(7, 73));
	rf_b0_66 = mt76x0_rf_rr(dev, MT_RF(0, 66));
	rf_b0_67 = mt76x0_rf_rr(dev, MT_RF(0, 67));

	mt76x0_rf_wr(dev, MT_RF(7, 73), 0x02);
	mt76x0_rf_wr(dev, MT_RF(0, 66), 0x23);
	mt76x0_rf_wr(dev, MT_RF(0, 67), 0x01);

	mt76_wr(dev, MT_BBP(CORE, 34), 0x00080055);
	अगर (!mt76_poll_msec(dev, MT_BBP(CORE, 34), BIT(4), 0, 200)) अणु
		mt76_clear(dev, MT_BBP(CORE, 34), BIT(4));
		जाओ करोne;
	पूर्ण

	val = mt76_rr(dev, MT_BBP(CORE, 35));
	val = (35 * (val - dev->cal.rx.temp_offset)) / 10 + 25;

	अगर (असल(val - dev->cal.temp_vco) > 20) अणु
		mt76x02_mcu_calibrate(dev, MCU_CAL_VCO,
				      dev->mphy.chandef.chan->hw_value);
		dev->cal.temp_vco = val;
	पूर्ण
	अगर (असल(val - dev->cal.temp) > 30) अणु
		mt76x0_phy_calibrate(dev, false);
		dev->cal.temp = val;
	पूर्ण

करोne:
	mt76x0_rf_wr(dev, MT_RF(7, 73), rf_b7_73);
	mt76x0_rf_wr(dev, MT_RF(0, 66), rf_b0_66);
	mt76x0_rf_wr(dev, MT_RF(0, 67), rf_b0_67);
पूर्ण

अटल व्योम mt76x0_phy_set_gain_val(काष्ठा mt76x02_dev *dev)
अणु
	u8 gain = dev->cal.agc_gain_cur[0] - dev->cal.agc_gain_adjust;

	mt76_rmw_field(dev, MT_BBP(AGC, 8), MT_BBP_AGC_GAIN, gain);

	अगर ((dev->mphy.chandef.chan->flags & IEEE80211_CHAN_RADAR) &&
	    !is_mt7630(dev))
		mt76x02_phy_dfs_adjust_agc(dev);
पूर्ण

अटल व्योम
mt76x0_phy_update_channel_gain(काष्ठा mt76x02_dev *dev)
अणु
	bool gain_change;
	u8 gain_delta;
	पूर्णांक low_gain;

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
			mt76x0_phy_set_gain_val(dev);
		वापस;
	पूर्ण

	dev->cal.agc_gain_adjust = (low_gain == 2) ? 0 : 10;
	gain_delta = (low_gain == 2) ? 10 : 0;

	dev->cal.agc_gain_cur[0] = dev->cal.agc_gain_init[0] - gain_delta;
	mt76x0_phy_set_gain_val(dev);

	/* clear false CCA counters */
	mt76_rr(dev, MT_RX_STAT_1);
पूर्ण

अटल व्योम mt76x0_phy_calibration_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mt76x02_dev *dev = container_of(work, काष्ठा mt76x02_dev,
					       cal_work.work);

	mt76x0_phy_update_channel_gain(dev);
	अगर (mt76x0_tssi_enabled(dev))
		mt76x0_phy_tssi_calibrate(dev);
	अन्यथा
		mt76x0_phy_temp_sensor(dev);

	ieee80211_queue_delayed_work(dev->mt76.hw, &dev->cal_work,
				     4 * MT_CALIBRATE_INTERVAL);
पूर्ण

अटल व्योम mt76x0_rf_patch_reg_array(काष्ठा mt76x02_dev *dev,
				      स्थिर काष्ठा mt76_reg_pair *rp, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		u32 reg = rp[i].reg;
		u8 val = rp[i].value;

		चयन (reg) अणु
		हाल MT_RF(0, 3):
			अगर (mt76_is_mmio(&dev->mt76)) अणु
				अगर (is_mt7630(dev))
					val = 0x70;
				अन्यथा
					val = 0x63;
			पूर्ण अन्यथा अणु
				val = 0x73;
			पूर्ण
			अवरोध;
		हाल MT_RF(0, 21):
			अगर (is_mt7610e(dev))
				val = 0x10;
			अन्यथा
				val = 0x12;
			अवरोध;
		हाल MT_RF(5, 2):
			अगर (is_mt7630(dev))
				val = 0x1d;
			अन्यथा अगर (is_mt7610e(dev))
				val = 0x00;
			अन्यथा
				val = 0x0c;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		mt76x0_rf_wr(dev, reg, val);
	पूर्ण
पूर्ण

अटल व्योम mt76x0_phy_rf_init(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i;

	mt76x0_rf_patch_reg_array(dev, mt76x0_rf_central_tab,
				  ARRAY_SIZE(mt76x0_rf_central_tab));
	mt76x0_rf_patch_reg_array(dev, mt76x0_rf_2g_channel_0_tab,
				  ARRAY_SIZE(mt76x0_rf_2g_channel_0_tab));
	RF_RANDOM_WRITE(dev, mt76x0_rf_5g_channel_0_tab);
	RF_RANDOM_WRITE(dev, mt76x0_rf_vga_channel_0_tab);

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_rf_bw_चयन_tab); i++) अणु
		स्थिर काष्ठा mt76x0_rf_चयन_item *item = &mt76x0_rf_bw_चयन_tab[i];

		अगर (item->bw_band == RF_BW_20)
			mt76x0_rf_wr(dev, item->rf_bank_reg, item->value);
		अन्यथा अगर (((RF_G_BAND | RF_BW_20) & item->bw_band) ==
			  (RF_G_BAND | RF_BW_20))
			mt76x0_rf_wr(dev, item->rf_bank_reg, item->value);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_rf_band_चयन_tab); i++) अणु
		अगर (mt76x0_rf_band_चयन_tab[i].bw_band & RF_G_BAND) अणु
			mt76x0_rf_wr(dev,
				     mt76x0_rf_band_चयन_tab[i].rf_bank_reg,
				     mt76x0_rf_band_चयन_tab[i].value);
		पूर्ण
	पूर्ण

	/* Frequency calibration
	 * E1: B0.R22<6:0>: xo_cxo<6:0>
	 * E2: B0.R21<0>: xo_cxo<0>, B0.R22<7:0>: xo_cxo<8:1>
	 */
	mt76x0_rf_wr(dev, MT_RF(0, 22),
		     min_t(u8, dev->cal.rx.freq_offset, 0xbf));
	mt76x0_rf_rr(dev, MT_RF(0, 22));

	/* Reset procedure DAC during घातer-up:
	 * - set B0.R73<7>
	 * - clear B0.R73<7>
	 * - set B0.R73<7>
	 */
	mt76x0_rf_set(dev, MT_RF(0, 73), BIT(7));
	mt76x0_rf_clear(dev, MT_RF(0, 73), BIT(7));
	mt76x0_rf_set(dev, MT_RF(0, 73), BIT(7));

	/* vcocal_en: initiate VCO calibration (reset after completion)) */
	mt76x0_rf_set(dev, MT_RF(0, 4), 0x80);
पूर्ण

व्योम mt76x0_phy_init(काष्ठा mt76x02_dev *dev)
अणु
	INIT_DELAYED_WORK(&dev->cal_work, mt76x0_phy_calibration_work);

	mt76x0_phy_ant_select(dev);
	mt76x0_phy_rf_init(dev);
	mt76x02_phy_set_rxpath(dev);
	mt76x02_phy_set_txdac(dev);
पूर्ण
