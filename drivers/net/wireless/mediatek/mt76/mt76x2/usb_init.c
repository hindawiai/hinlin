<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/delay.h>

#समावेश "mt76x2u.h"
#समावेश "eeprom.h"
#समावेश "../mt76x02_phy.h"
#समावेश "../mt76x02_usb.h"

अटल व्योम mt76x2u_init_dma(काष्ठा mt76x02_dev *dev)
अणु
	u32 val = mt76_rr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG));

	val |= MT_USB_DMA_CFG_RX_DROP_OR_PAD |
	       MT_USB_DMA_CFG_RX_BULK_EN |
	       MT_USB_DMA_CFG_TX_BULK_EN;

	/* disable AGGR_BULK_RX in order to receive one
	 * frame in each rx urb and aव्योम copies
	 */
	val &= ~MT_USB_DMA_CFG_RX_BULK_AGG_EN;
	mt76_wr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG), val);
पूर्ण

अटल व्योम mt76x2u_घातer_on_rf_patch(काष्ठा mt76x02_dev *dev)
अणु
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x130), BIT(0) | BIT(16));
	udelay(1);

	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x1c), 0xff);
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x1c), 0x30);

	mt76_wr(dev, MT_VEND_ADDR(CFG, 0x14), 0x484f);
	udelay(1);

	mt76_set(dev, MT_VEND_ADDR(CFG, 0x130), BIT(17));
	usleep_range(150, 200);

	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x130), BIT(16));
	usleep_range(50, 100);

	mt76_set(dev, MT_VEND_ADDR(CFG, 0x14c), BIT(19) | BIT(20));
पूर्ण

अटल व्योम mt76x2u_घातer_on_rf(काष्ठा mt76x02_dev *dev, पूर्णांक unit)
अणु
	पूर्णांक shअगरt = unit ? 8 : 0;
	u32 val = (BIT(1) | BIT(3) | BIT(4) | BIT(5)) << shअगरt;

	/* Enable RF BG */
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x130), BIT(0) << shअगरt);
	usleep_range(10, 20);

	/* Enable RFDIG LDO/AFE/ABB/ADDA */
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x130), val);
	usleep_range(10, 20);

	/* Switch RFDIG घातer to पूर्णांकernal LDO */
	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x130), BIT(2) << shअगरt);
	usleep_range(10, 20);

	mt76x2u_घातer_on_rf_patch(dev);

	mt76_set(dev, 0x530, 0xf);
पूर्ण

अटल व्योम mt76x2u_घातer_on(काष्ठा mt76x02_dev *dev)
अणु
	u32 val;

	/* Turn on WL MTCMOS */
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x148),
		 MT_WLAN_MTC_CTRL_MTCMOS_PWR_UP);

	val = MT_WLAN_MTC_CTRL_STATE_UP |
	      MT_WLAN_MTC_CTRL_PWR_ACK |
	      MT_WLAN_MTC_CTRL_PWR_ACK_S;

	mt76_poll(dev, MT_VEND_ADDR(CFG, 0x148), val, val, 1000);

	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x148), 0x7f << 16);
	usleep_range(10, 20);

	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x148), 0xf << 24);
	usleep_range(10, 20);

	mt76_set(dev, MT_VEND_ADDR(CFG, 0x148), 0xf << 24);
	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x148), 0xfff);

	/* Turn on AD/DA घातer करोwn */
	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x1204), BIT(3));

	/* WLAN function enable */
	mt76_set(dev, MT_VEND_ADDR(CFG, 0x80), BIT(0));

	/* Release BBP software reset */
	mt76_clear(dev, MT_VEND_ADDR(CFG, 0x64), BIT(18));

	mt76x2u_घातer_on_rf(dev, 0);
	mt76x2u_घातer_on_rf(dev, 1);
पूर्ण

अटल पूर्णांक mt76x2u_init_eeprom(काष्ठा mt76x02_dev *dev)
अणु
	u32 val, i;

	dev->mt76.eeprom.data = devm_kzalloc(dev->mt76.dev,
					     MT7612U_EEPROM_SIZE,
					     GFP_KERNEL);
	dev->mt76.eeprom.size = MT7612U_EEPROM_SIZE;
	अगर (!dev->mt76.eeprom.data)
		वापस -ENOMEM;

	क्रम (i = 0; i + 4 <= MT7612U_EEPROM_SIZE; i += 4) अणु
		val = mt76_rr(dev, MT_VEND_ADDR(EEPROM, i));
		put_unaligned_le32(val, dev->mt76.eeprom.data + i);
	पूर्ण

	mt76x02_eeprom_parse_hw_cap(dev);
	वापस 0;
पूर्ण

पूर्णांक mt76x2u_init_hardware(काष्ठा mt76x02_dev *dev)
अणु
	पूर्णांक i, k, err;

	mt76x2_reset_wlan(dev, true);
	mt76x2u_घातer_on(dev);

	अगर (!mt76x02_रुको_क्रम_mac(&dev->mt76))
		वापस -ETIMEDOUT;

	err = mt76x2u_mcu_fw_init(dev);
	अगर (err < 0)
		वापस err;

	अगर (!mt76_poll_msec(dev, MT_WPDMA_GLO_CFG,
			    MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
			    MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 100))
		वापस -EIO;

	/* रुको क्रम asic पढ़ोy after fw load. */
	अगर (!mt76x02_रुको_क्रम_mac(&dev->mt76))
		वापस -ETIMEDOUT;

	mt76x2u_init_dma(dev);

	err = mt76x2u_mcu_init(dev);
	अगर (err < 0)
		वापस err;

	err = mt76x2u_mac_reset(dev);
	अगर (err < 0)
		वापस err;

	mt76x02_mac_setaddr(dev, dev->mt76.eeprom.data + MT_EE_MAC_ADDR);
	dev->mt76.rxfilter = mt76_rr(dev, MT_RX_FILTR_CFG);

	अगर (!mt76x02_रुको_क्रम_txrx_idle(&dev->mt76))
		वापस -ETIMEDOUT;

	/* reset wcid table */
	क्रम (i = 0; i < 256; i++)
		mt76x02_mac_wcid_setup(dev, i, 0, शून्य);

	/* reset shared key table and pairwise key table */
	क्रम (i = 0; i < 16; i++) अणु
		क्रम (k = 0; k < 4; k++)
			mt76x02_mac_shared_key_setup(dev, i, k, शून्य);
	पूर्ण

	mt76x02u_init_beacon_config(dev);

	mt76_rmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);
	mt76_wr(dev, MT_TXOP_CTRL_CFG, 0x583f);

	err = mt76x2_mcu_load_cr(dev, MT_RF_BBP_CR, 0, 0);
	अगर (err < 0)
		वापस err;

	mt76x02_phy_set_rxpath(dev);
	mt76x02_phy_set_txdac(dev);

	वापस mt76x2u_mac_stop(dev);
पूर्ण

पूर्णांक mt76x2u_रेजिस्टर_device(काष्ठा mt76x02_dev *dev)
अणु
	काष्ठा ieee80211_hw *hw = mt76_hw(dev);
	काष्ठा mt76_usb *usb = &dev->mt76.usb;
	पूर्णांक err;

	INIT_DELAYED_WORK(&dev->cal_work, mt76x2u_phy_calibrate);
	mt76x02_init_device(dev);

	err = mt76x2u_init_eeprom(dev);
	अगर (err < 0)
		वापस err;

	usb->mcu.data = devm_kदो_स्मृति(dev->mt76.dev, MCU_RESP_URB_SIZE,
				     GFP_KERNEL);
	अगर (!usb->mcu.data)
		वापस -ENOMEM;

	err = mt76u_alloc_queues(&dev->mt76);
	अगर (err < 0)
		जाओ fail;

	err = mt76x2u_init_hardware(dev);
	अगर (err < 0)
		जाओ fail;

	/* check hw sg support in order to enable AMSDU */
	hw->max_tx_fragments = dev->mt76.usb.sg_en ? MT_TX_SG_MAX_SIZE : 1;
	err = mt76_रेजिस्टर_device(&dev->mt76, true, mt76x02_rates,
				   ARRAY_SIZE(mt76x02_rates));
	अगर (err)
		जाओ fail;

	set_bit(MT76_STATE_INITIALIZED, &dev->mphy.state);

	mt76x02_init_debugfs(dev);
	mt76x2_init_txघातer(dev, &dev->mphy.sband_2g.sband);
	mt76x2_init_txघातer(dev, &dev->mphy.sband_5g.sband);

	वापस 0;

fail:
	mt76x2u_cleanup(dev);
	वापस err;
पूर्ण

व्योम mt76x2u_stop_hw(काष्ठा mt76x02_dev *dev)
अणु
	cancel_delayed_work_sync(&dev->cal_work);
	cancel_delayed_work_sync(&dev->mphy.mac_work);
	mt76x2u_mac_stop(dev);
पूर्ण

व्योम mt76x2u_cleanup(काष्ठा mt76x02_dev *dev)
अणु
	mt76x02_mcu_set_radio_state(dev, false);
	mt76x2u_stop_hw(dev);
	mt76u_queues_deinit(&dev->mt76);
पूर्ण
