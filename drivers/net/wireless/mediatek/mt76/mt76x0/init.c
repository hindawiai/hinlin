<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) Copyright 2002-2010, Ralink Technology, Inc.
 * Copyright (C) 2014 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2015 Jakub Kicinski <kubakici@wp.pl>
 * Copyright (C) 2018 Stanislaw Gruszka <stf_xl@wp.pl>
 */

#समावेश "mt76x0.h"
#समावेश "eeprom.h"
#समावेश "mcu.h"
#समावेश "initvals.h"
#समावेश "initvals_init.h"
#समावेश "../mt76x02_phy.h"

अटल व्योम
mt76x0_set_wlan_state(काष्ठा mt76x02_dev *dev, u32 val, bool enable)
अणु
	u32 mask = MT_CMB_CTRL_XTAL_RDY | MT_CMB_CTRL_PLL_LD;

	/* Note: we करोn't turn off WLAN_CLK because that makes the device
	 *	 not respond properly on the probe path.
	 *	 In हाल anyone (PSM?) wants to use this function we can
	 *	 bring the घड़ी stuff back and fixup the probe path.
	 */

	अगर (enable)
		val |= (MT_WLAN_FUN_CTRL_WLAN_EN |
			MT_WLAN_FUN_CTRL_WLAN_CLK_EN);
	अन्यथा
		val &= ~(MT_WLAN_FUN_CTRL_WLAN_EN);

	mt76_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	/* Note: venकरोr driver tries to disable/enable wlan here and retry
	 *       but the code which करोes it is so buggy it must have never
	 *       triggered, so करोn't bother.
	 */
	अगर (enable && !mt76_poll(dev, MT_CMB_CTRL, mask, mask, 2000))
		dev_err(dev->mt76.dev, "PLL and XTAL check failed\n");
पूर्ण

व्योम mt76x0_chip_onoff(काष्ठा mt76x02_dev *dev, bool enable, bool reset)
अणु
	u32 val;

	val = mt76_rr(dev, MT_WLAN_FUN_CTRL);

	अगर (reset) अणु
		val |= MT_WLAN_FUN_CTRL_GPIO_OUT_EN;
		val &= ~MT_WLAN_FUN_CTRL_FRC_WL_ANT_SEL;

		अगर (val & MT_WLAN_FUN_CTRL_WLAN_EN) अणु
			val |= (MT_WLAN_FUN_CTRL_WLAN_RESET |
				MT_WLAN_FUN_CTRL_WLAN_RESET_RF);
			mt76_wr(dev, MT_WLAN_FUN_CTRL, val);
			udelay(20);

			val &= ~(MT_WLAN_FUN_CTRL_WLAN_RESET |
				 MT_WLAN_FUN_CTRL_WLAN_RESET_RF);
		पूर्ण
	पूर्ण

	mt76_wr(dev, MT_WLAN_FUN_CTRL, val);
	udelay(20);

	mt76x0_set_wlan_state(dev, val, enable);
पूर्ण
EXPORT_SYMBOL_GPL(mt76x0_chip_onoff);

अटल व्योम mt76x0_reset_csr_bbp(काष्ठा mt76x02_dev *dev)
अणु
	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_RESET_CSR |
		MT_MAC_SYS_CTRL_RESET_BBP);
	msleep(200);
	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_RESET_CSR |
		   MT_MAC_SYS_CTRL_RESET_BBP);
पूर्ण

#घोषणा RANDOM_WRITE(dev, tab)			\
	mt76_wr_rp(dev, MT_MCU_MEMMAP_WLAN,	\
		   tab, ARRAY_SIZE(tab))

अटल पूर्णांक mt76x0_init_bbp(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret, i;

	ret = mt76x0_phy_रुको_bbp_पढ़ोy(dev);
	अगर (ret)
		वापस ret;

	RANDOM_WRITE(dev, mt76x0_bbp_init_tab);

	क्रम (i = 0; i < ARRAY_SIZE(mt76x0_bbp_चयन_tab); i++) अणु
		स्थिर काष्ठा mt76x0_bbp_चयन_item *item = &mt76x0_bbp_चयन_tab[i];
		स्थिर काष्ठा mt76_reg_pair *pair = &item->reg_pair;

		अगर (((RF_G_BAND | RF_BW_20) & item->bw_band) == (RF_G_BAND | RF_BW_20))
			mt76_wr(dev, pair->reg, pair->value);
	पूर्ण

	RANDOM_WRITE(dev, mt76x0_dcoc_tab);

	वापस 0;
पूर्ण

अटल व्योम mt76x0_init_mac_रेजिस्टरs(काष्ठा mt76x02_dev *dev)
अणु
	RANDOM_WRITE(dev, common_mac_reg_table);

	/* Enable PBF and MAC घड़ी SYS_CTRL[11:10] = 0x3 */
	RANDOM_WRITE(dev, mt76x0_mac_reg_table);

	/* Release BBP and MAC reset MAC_SYS_CTRL[1:0] = 0x0 */
	mt76_clear(dev, MT_MAC_SYS_CTRL, 0x3);

	/* Set 0x141C[15:12]=0xF */
	mt76_set(dev, MT_EXT_CCA_CFG, 0xf000);

	mt76_clear(dev, MT_FCE_L2_STUFF, MT_FCE_L2_STUFF_WR_MPDU_LEN_EN);

	/*
	 * tx_ring 9 is क्रम mgmt frame
	 * tx_ring 8 is क्रम in-band command frame.
	 * WMM_RG0_TXQMA: this रेजिस्टर setting is क्रम FCE to
	 *		  define the rule of tx_ring 9
	 * WMM_RG1_TXQMA: this रेजिस्टर setting is क्रम FCE to
	 *		  define the rule of tx_ring 8
	 */
	mt76_rmw(dev, MT_WMM_CTRL, 0x3ff, 0x201);
पूर्ण

व्योम mt76x0_mac_stop(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i = 200, ok = 0;

	mt76_clear(dev, MT_TXOP_CTRL_CFG, MT_TXOP_ED_CCA_EN);

	/* Page count on TxQ */
	जबतक (i-- && ((mt76_rr(dev, 0x0438) & 0xffffffff) ||
		       (mt76_rr(dev, 0x0a30) & 0x000000ff) ||
		       (mt76_rr(dev, 0x0a34) & 0x00ff00ff)))
		msleep(10);

	अगर (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_TX, 0, 1000))
		dev_warn(dev->mt76.dev, "Warning: MAC TX did not stop!\n");

	mt76_clear(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_RX |
					 MT_MAC_SYS_CTRL_ENABLE_TX);

	/* Page count on RxQ */
	क्रम (i = 0; i < 200; i++) अणु
		अगर (!(mt76_rr(dev, MT_RXQ_STA) & 0x00ff0000) &&
		    !mt76_rr(dev, 0x0a30) &&
		    !mt76_rr(dev, 0x0a34)) अणु
			अगर (ok++ > 5)
				अवरोध;
			जारी;
		पूर्ण
		msleep(1);
	पूर्ण

	अगर (!mt76_poll(dev, MT_MAC_STATUS, MT_MAC_STATUS_RX, 0, 1000))
		dev_warn(dev->mt76.dev, "Warning: MAC RX did not stop!\n");
पूर्ण
EXPORT_SYMBOL_GPL(mt76x0_mac_stop);

पूर्णांक mt76x0_init_hardware(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret, i, k;

	अगर (!mt76x02_रुको_क्रम_wpdma(&dev->mt76, 1000))
		वापस -EIO;

	/* Wait क्रम ASIC पढ़ोy after FW load. */
	अगर (!mt76x02_रुको_क्रम_mac(&dev->mt76))
		वापस -ETIMEDOUT;

	mt76x0_reset_csr_bbp(dev);
	ret = mt76x02_mcu_function_select(dev, Q_SELECT, 1);
	अगर (ret)
		वापस ret;

	mt76x0_init_mac_रेजिस्टरs(dev);

	अगर (!mt76x02_रुको_क्रम_txrx_idle(&dev->mt76))
		वापस -EIO;

	ret = mt76x0_init_bbp(dev);
	अगर (ret)
		वापस ret;

	dev->mt76.rxfilter = mt76_rr(dev, MT_RX_FILTR_CFG);

	क्रम (i = 0; i < 16; i++)
		क्रम (k = 0; k < 4; k++)
			mt76x02_mac_shared_key_setup(dev, i, k, शून्य);

	क्रम (i = 0; i < 256; i++)
		mt76x02_mac_wcid_setup(dev, i, 0, शून्य);

	ret = mt76x0_eeprom_init(dev);
	अगर (ret)
		वापस ret;

	mt76x0_phy_init(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x0_init_hardware);

अटल व्योम
mt76x0_init_txघातer(काष्ठा mt76x02_dev *dev,
		    काष्ठा ieee80211_supported_band *sband)
अणु
	काष्ठा ieee80211_channel *chan;
	काष्ठा mt76_rate_घातer t;
	s8 tp;
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		chan = &sband->channels[i];

		mt76x0_get_tx_घातer_per_rate(dev, chan, &t);
		mt76x0_get_घातer_info(dev, chan, &tp);

		chan->orig_mpwr = (mt76x02_get_max_rate_घातer(&t) + tp) / 2;
		chan->max_घातer = min_t(पूर्णांक, chan->max_reg_घातer,
					chan->orig_mpwr);
	पूर्ण
पूर्ण

पूर्णांक mt76x0_रेजिस्टर_device(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret;

	mt76x02_init_device(dev);
	mt76x02_config_mac_addr_list(dev);

	ret = mt76_रेजिस्टर_device(&dev->mt76, true, mt76x02_rates,
				   ARRAY_SIZE(mt76x02_rates));
	अगर (ret)
		वापस ret;

	अगर (dev->mphy.cap.has_5ghz) अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = &dev->mphy.sband_5g.sband;
		sband->vht_cap.cap &= ~IEEE80211_VHT_CAP_RXLDPC;
		mt76x0_init_txघातer(dev, sband);
	पूर्ण

	अगर (dev->mphy.cap.has_2ghz)
		mt76x0_init_txघातer(dev, &dev->mphy.sband_2g.sband);

	mt76x02_init_debugfs(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76x0_रेजिस्टर_device);
