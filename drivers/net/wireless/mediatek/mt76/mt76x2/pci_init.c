<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <linux/delay.h>
#समावेश "mt76x2.h"
#समावेश "eeprom.h"
#समावेश "mcu.h"
#समावेश "../mt76x02_mac.h"

अटल व्योम
mt76x2_mac_pbf_init(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	val = MT_PBF_SYS_CTRL_MCU_RESET |
	      MT_PBF_SYS_CTRL_DMA_RESET |
	      MT_PBF_SYS_CTRL_MAC_RESET |
	      MT_PBF_SYS_CTRL_PBF_RESET |
	      MT_PBF_SYS_CTRL_ASY_RESET;

	mt76_set(dev, MT_PBF_SYS_CTRL, val);
	mt76_clear(dev, MT_PBF_SYS_CTRL, val);

	mt76_wr(dev, MT_PBF_TX_MAX_PCNT, 0xefef3f1f);
	mt76_wr(dev, MT_PBF_RX_MAX_PCNT, 0xfebf);
पूर्ण

अटल व्योम
mt76x2_fixup_xtal(काष्ठा mt76x02_dev *dev)
अणु
	u16 eep_val;
	s8 offset = 0;

	eep_val = mt76x02_eeprom_get(dev, MT_EE_XTAL_TRIM_2);

	offset = eep_val & 0x7f;
	अगर ((eep_val & 0xff) == 0xff)
		offset = 0;
	अन्यथा अगर (eep_val & 0x80)
		offset = 0 - offset;

	eep_val >>= 8;
	अगर (eep_val == 0x00 || eep_val == 0xff) अणु
		eep_val = mt76x02_eeprom_get(dev, MT_EE_XTAL_TRIM_1);
		eep_val &= 0xff;

		अगर (eep_val == 0x00 || eep_val == 0xff)
			eep_val = 0x14;
	पूर्ण

	eep_val &= 0x7f;
	mt76_rmw_field(dev, MT_XO_CTRL5, MT_XO_CTRL5_C2_VAL, eep_val + offset);
	mt76_set(dev, MT_XO_CTRL6, MT_XO_CTRL6_C2_CTRL);

	eep_val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_2);
	चयन (FIELD_GET(MT_EE_NIC_CONF_2_XTAL_OPTION, eep_val)) अणु
	हाल 0:
		mt76_wr(dev, MT_XO_CTRL7, 0x5c1fee80);
		अवरोध;
	हाल 1:
		mt76_wr(dev, MT_XO_CTRL7, 0x5c1feed0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक mt76x2_mac_reset(काष्ठा mt76x02_dev *dev, bool hard)
अणु
	स्थिर u8 *macaddr = dev->mphy.macaddr;
	u32 val;
	पूर्णांक i, k;

	अगर (!mt76x02_रुको_क्रम_mac(&dev->mt76))
		वापस -ETIMEDOUT;

	val = mt76_rr(dev, MT_WPDMA_GLO_CFG);

	val &= ~(MT_WPDMA_GLO_CFG_TX_DMA_EN |
		 MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		 MT_WPDMA_GLO_CFG_RX_DMA_EN |
		 MT_WPDMA_GLO_CFG_RX_DMA_BUSY |
		 MT_WPDMA_GLO_CFG_DMA_BURST_SIZE);
	val |= FIELD_PREP(MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 3);

	mt76_wr(dev, MT_WPDMA_GLO_CFG, val);

	mt76x2_mac_pbf_init(dev);
	mt76_ग_लिखो_mac_initvals(dev);
	mt76x2_fixup_xtal(dev);

	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_RESET_CSR |
		   MT_MAC_SYS_CTRL_RESET_BBP);

	अगर (is_mt7612(dev))
		mt76_clear(dev, MT_COEXCFG0, MT_COEXCFG0_COEX_EN);

	mt76_set(dev, MT_EXT_CCA_CFG, 0x0000f000);
	mt76_clear(dev, MT_TX_ALC_CFG_4, BIT(31));

	mt76_wr(dev, MT_RF_BYPASS_0, 0x06000000);
	mt76_wr(dev, MT_RF_SETTING_0, 0x08800000);
	usleep_range(5000, 10000);
	mt76_wr(dev, MT_RF_BYPASS_0, 0x00000000);

	mt76_wr(dev, MT_MCU_CLOCK_CTL, 0x1401);
	mt76_clear(dev, MT_FCE_L2_STUFF, MT_FCE_L2_STUFF_WR_MPDU_LEN_EN);

	mt76x02_mac_setaddr(dev, macaddr);
	mt76x02e_init_beacon_config(dev);
	अगर (!hard)
		वापस 0;

	क्रम (i = 0; i < 256 / 32; i++)
		mt76_wr(dev, MT_WCID_DROP_BASE + i * 4, 0);

	क्रम (i = 0; i < 256; i++) अणु
		mt76x02_mac_wcid_setup(dev, i, 0, शून्य);
		mt76_wr(dev, MT_WCID_TX_RATE(i), 0);
		mt76_wr(dev, MT_WCID_TX_RATE(i) + 4, 0);
	पूर्ण

	क्रम (i = 0; i < MT_MAX_VIFS; i++)
		mt76x02_mac_wcid_setup(dev, MT_VIF_WCID(i), i, शून्य);

	क्रम (i = 0; i < 16; i++)
		क्रम (k = 0; k < 4; k++)
			mt76x02_mac_shared_key_setup(dev, i, k, शून्य);

	क्रम (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_STAT_FIFO);

	mt76x02_set_tx_ackto(dev);

	वापस 0;
पूर्ण

अटल व्योम
mt76x2_घातer_on_rf_patch(काष्ठा mt76x02_dev *dev)
अणु
	mt76_set(dev, 0x10130, BIT(0) | BIT(16));
	udelay(1);

	mt76_clear(dev, 0x1001c, 0xff);
	mt76_set(dev, 0x1001c, 0x30);

	mt76_wr(dev, 0x10014, 0x484f);
	udelay(1);

	mt76_set(dev, 0x10130, BIT(17));
	udelay(125);

	mt76_clear(dev, 0x10130, BIT(16));
	udelay(50);

	mt76_set(dev, 0x1014c, BIT(19) | BIT(20));
पूर्ण

अटल व्योम
mt76x2_घातer_on_rf(काष्ठा mt76x02_dev *dev, पूर्णांक unit)
अणु
	पूर्णांक shअगरt = unit ? 8 : 0;

	/* Enable RF BG */
	mt76_set(dev, 0x10130, BIT(0) << shअगरt);
	udelay(10);

	/* Enable RFDIG LDO/AFE/ABB/ADDA */
	mt76_set(dev, 0x10130, (BIT(1) | BIT(3) | BIT(4) | BIT(5)) << shअगरt);
	udelay(10);

	/* Switch RFDIG घातer to पूर्णांकernal LDO */
	mt76_clear(dev, 0x10130, BIT(2) << shअगरt);
	udelay(10);

	mt76x2_घातer_on_rf_patch(dev);

	mt76_set(dev, 0x530, 0xf);
पूर्ण

अटल व्योम
mt76x2_घातer_on(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	/* Turn on WL MTCMOS */
	mt76_set(dev, MT_WLAN_MTC_CTRL, MT_WLAN_MTC_CTRL_MTCMOS_PWR_UP);

	val = MT_WLAN_MTC_CTRL_STATE_UP |
	      MT_WLAN_MTC_CTRL_PWR_ACK |
	      MT_WLAN_MTC_CTRL_PWR_ACK_S;

	mt76_poll(dev, MT_WLAN_MTC_CTRL, val, val, 1000);

	mt76_clear(dev, MT_WLAN_MTC_CTRL, 0x7f << 16);
	udelay(10);

	mt76_clear(dev, MT_WLAN_MTC_CTRL, 0xf << 24);
	udelay(10);

	mt76_set(dev, MT_WLAN_MTC_CTRL, 0xf << 24);
	mt76_clear(dev, MT_WLAN_MTC_CTRL, 0xfff);

	/* Turn on AD/DA घातer करोwn */
	mt76_clear(dev, 0x11204, BIT(3));

	/* WLAN function enable */
	mt76_set(dev, 0x10080, BIT(0));

	/* Release BBP software reset */
	mt76_clear(dev, 0x10064, BIT(18));

	mt76x2_घातer_on_rf(dev, 0);
	mt76x2_घातer_on_rf(dev, 1);
पूर्ण

पूर्णांक mt76x2_resume_device(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक err;

	mt76x02_dma_disable(dev);
	mt76x2_reset_wlan(dev, true);
	mt76x2_घातer_on(dev);

	err = mt76x2_mac_reset(dev, true);
	अगर (err)
		वापस err;

	mt76x02_mac_start(dev);

	वापस mt76x2_mcu_init(dev);
पूर्ण

अटल पूर्णांक mt76x2_init_hardware(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret;

	mt76x02_dma_disable(dev);
	mt76x2_reset_wlan(dev, true);
	mt76x2_घातer_on(dev);

	ret = mt76x2_eeprom_init(dev);
	अगर (ret)
		वापस ret;

	ret = mt76x2_mac_reset(dev, true);
	अगर (ret)
		वापस ret;

	dev->mt76.rxfilter = mt76_rr(dev, MT_RX_FILTR_CFG);

	ret = mt76x02_dma_init(dev);
	अगर (ret)
		वापस ret;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);
	mt76x02_mac_start(dev);

	ret = mt76x2_mcu_init(dev);
	अगर (ret)
		वापस ret;

	mt76x2_mac_stop(dev, false);

	वापस 0;
पूर्ण

व्योम mt76x2_stop_hardware(काष्ठा mt76x02_dev *dev)
अणु
	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	cancel_delayed_work_sync(&dev->wdt_work);
	clear_bit(MT76_RESTART, &dev->mphy.state);
	mt76x02_mcu_set_radio_state(dev, false);
	mt76x2_mac_stop(dev, false);
पूर्ण

व्योम mt76x2_cleanup(काष्ठा mt76x02_dev *dev)
अणु
	tasklet_disable(&dev->dfs_pd.dfs_tasklet);
	tasklet_disable(&dev->mt76.pre_tbtt_tasklet);
	mt76x2_stop_hardware(dev);
	mt76_dma_cleanup(&dev->mt76);
	mt76x02_mcu_cleanup(dev);
पूर्ण

पूर्णांक mt76x2_रेजिस्टर_device(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक ret;

	INIT_DELAYED_WORK(&dev->cal_work, mt76x2_phy_calibrate);

	mt76x02_init_device(dev);

	ret = mt76x2_init_hardware(dev);
	अगर (ret)
		वापस ret;

	mt76x02_config_mac_addr_list(dev);

	ret = mt76_रेजिस्टर_device(&dev->mt76, true, mt76x02_rates,
				   ARRAY_SIZE(mt76x02_rates));
	अगर (ret)
		जाओ fail;

	mt76x02_init_debugfs(dev);
	mt76x2_init_txघातer(dev, &dev->mphy.sband_2g.sband);
	mt76x2_init_txघातer(dev, &dev->mphy.sband_5g.sband);

	वापस 0;

fail:
	mt76x2_stop_hardware(dev);
	वापस ret;
पूर्ण

